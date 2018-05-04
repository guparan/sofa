/******************************************************************************
*       SOFA, Simulation Open-Framework Architecture, development version     *
*                (c) 2006-2018 INRIA, USTL, UJF, CNRS, MGH                    *
*                                                                             *
* This program is free software; you can redistribute it and/or modify it     *
* under the terms of the GNU Lesser General Public License as published by    *
* the Free Software Foundation; either version 2.1 of the License, or (at     *
* your option) any later version.                                             *
*                                                                             *
* This program is distributed in the hope that it will be useful, but WITHOUT *
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or       *
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License *
* for more details.                                                           *
*                                                                             *
* You should have received a copy of the GNU Lesser General Public License    *
* along with this program. If not, see <http://www.gnu.org/licenses/>.        *
*******************************************************************************
* Authors: The SOFA Team and external contributors (see Authors.txt)          *
*                                                                             *
* Contact information: contact@sofa-framework.org                             *
******************************************************************************/

#ifndef FLEXIBLE_NeoHookeanMaterialBlock_H
#define FLEXIBLE_NeoHookeanMaterialBlock_H


#include "../material/BaseMaterial.h"
#include "../BaseJacobian.h"
#include "NeoHookeanMaterialBlock.h"
#include <sofa/defaulttype/Vec.h>
#include <sofa/defaulttype/Mat.h>
#include "../types/StrainTypes.h"
#include <sofa/helper/decompose.h>


namespace sofa
{

namespace defaulttype
{

//////////////////////////////////////////////////////////////////////////////////
////  default implementation for U331
//////////////////////////////////////////////////////////////////////////////////

template<class _T>
class NeoHookeanMaterialBlock:
    public  BaseMaterialBlock< _T >
{
public:
    typedef _T T;

    typedef BaseMaterialBlock<T> Inherit;
    typedef typename Inherit::Coord Coord;
    typedef typename Inherit::Deriv Deriv;
    typedef typename Inherit::MatBlock MatBlock;
    typedef typename Inherit::Real Real;

    /**
      * DOFs: principal stretches U1,U2,U3   J=U1*U2*U3
      *
      * classic Neo-Hookean
      *     - W = vol * [ mu/2 ( (U1^2+U2^2+U3^2)/J^{2/3} - 3)  + bulk/2 (J-1)^2]
      * see maple file ./doc/NeoHookean_principalStretches.mw for derivative
      */

    static const bool constantK=false;

    Real mimuVol;  ///< 0.5 * shear modulus * volume
    Real bulkVol;   ///<  bulk modulus * volume
    bool stabilization;

    mutable MatBlock _K;

    void init(const Real &youngM,const Real &poissonR, bool _stabilization)
    {
        Real vol=1.;
        if(this->volume) vol=(*this->volume)[0];

        Real mu = 0.5* youngM/(1+poissonR);
        Real bulk = youngM/(3*(1-2*poissonR));

        mimuVol = mu*0.5*vol;
        bulkVol = bulk*vol;
        stabilization = _stabilization;
    }

    Real getPotentialEnergy(const Coord& x) const override
    {
        const Real& U1 = x.getStrain()[0];
        const Real& U2 = x.getStrain()[1];
        const Real& U3 = x.getStrain()[2];

        Real J = U1*U2*U3;
        Real Jm1 = J-1;
        Real squareU[3] = { U1*U1, U2*U2, U3*U3 };
        return mimuVol*((squareU[0]+squareU[1]+squareU[2])*pow(J,-2.0/3.0)-(Real)3.) +
                0.5*bulkVol*Jm1*Jm1;
    }

    void addForce( Deriv& f, const Coord& x, const Deriv& /*v*/) const override
    {
        const Real& U1 = x.getStrain()[0];
        const Real& U2 = x.getStrain()[1];
        const Real& U3 = x.getStrain()[2];

        Real squareU[3] = { U1*U1, U2*U2, U3*U3 };

        // TODO optimize this crappy code generated by maple
        // there are redondencies between computation of f and K

        Real t1 =  U1 *  U2;

        Real J = t1 * U3;

        Real Jm1 = J-1;

        Real Jm23 = pow(J,-2.0/3.0);
        Real Jm53 = pow(J,-5.0/3.0);
        Real Jm83 = pow(J,-8.0/3.0);

        Real I1 = squareU[0]+squareU[1]+squareU[2];

        Real t4 = -0.2e1 / 0.3e1 * I1 * Jm53;
        Real t2 = bulkVol * Jm1;


        Real t9 = U2 * U3;
        Real t15 = U1 * U3;

        f.getStrain()[0] -= mimuVol * (0.2e1 * U1 * Jm23 + t4 * U2 * U3) + t2 * t9;
        f.getStrain()[1] -= mimuVol * (0.2e1 * U2 * Jm23 + t4 * U1 * U3) + t2 * t15;
        f.getStrain()[2] -= mimuVol * (0.2e1 * U3 * Jm23 + t4 * t1) + t2 * t1;

        Real t10 = 0.2e1 * Jm23;
        Real t11 = bulkVol * squareU[1];
        Real t12 = (0.10e2 / 0.9e1 * J * Jm83 - 0.2e1 / 0.3e1 * Jm53) * I1;
        t2 = 0.2e1 * Jm1;
        Real t13 = bulkVol * U3 * t2 + mimuVol * U3 * (t12 - 0.4e1 / 0.3e1 * Jm53 * (squareU[0] + squareU[1]));
        Real t14 = bulkVol * U2 * t2 + mimuVol * U2 * (t12 - 0.4e1 / 0.3e1 * Jm53 * (squareU[0] + squareU[2]));
        Real t16 = -0.8e1 / 0.3e1 * Jm53;
        t2 = bulkVol * U1 * t2 + mimuVol * U1 * (t12 - 0.4e1 / 0.3e1 * Jm53 * (squareU[1] + squareU[2]));
        _K[0][0] = mimuVol * (t9 * (-0.8e1 / 0.3e1 * U1 * Jm53 + 0.10e2 / 0.9e1 * t9 * I1 * Jm83) + t10) + t11 * squareU[2];
        _K[0][1] = t13;
        _K[0][2] = t14;
        _K[1][0] = _K[0][1];
        _K[1][1] = mimuVol * (t15 * (t16 * U2 + 0.10e2 / 0.9e1 * t15 * I1 * Jm83) + t10) + bulkVol * squareU[0] * squareU[2];
        _K[1][2] = t2;
        _K[2][0] = _K[0][2];
        _K[2][1] = _K[1][2];
        _K[2][2] = mimuVol * (t1 * (t16 * U3 + 0.10e2 / 0.9e1 * t1 * I1 * Jm83) + t10) + t11 * squareU[0];

        // ensure _K is symmetric positive semi-definite (even if it is not as good as positive definite) as suggested in [Teran05]
        if( stabilization ) helper::Decompose<Real>::PSDProjection( _K );
    }

    void addDForce( Deriv& df, const Deriv& dx, const SReal& kfactor, const SReal& /*bfactor*/ ) const override
    {
        df.getStrain() -= _K * dx.getStrain() * kfactor;
    }

    MatBlock getK() const override
    {
        return -_K;
    }

    MatBlock getC() const override
    {
        MatBlock C = MatBlock();
        C.invert( -_K );
        return -C;
    }

    MatBlock getB() const override
    {
        return MatBlock();
    }
};




//////////////////////////////////////////////////////////////////////////////////
////  specialization for U321
//////////////////////////////////////////////////////////////////////////////////

template<class _Real>
class NeoHookeanMaterialBlock< U321(_Real) >:
    public  BaseMaterialBlock< U321(_Real) >
{
public:
    typedef U321(_Real) T;

    typedef BaseMaterialBlock<T> Inherit;
    typedef typename Inherit::Coord Coord;
    typedef typename Inherit::Deriv Deriv;
    typedef typename Inherit::MatBlock MatBlock;
    typedef typename Inherit::Real Real;

    /**
      * DOFs: principal stretches U1,U2   J=U1*U2
      *
      * classic Neo-Hookean
      *     - W = vol * [ mu/2 ( (U1^2+U2^2+1)/J^{2/3} - 3)  + bulk/2 (J-1)^2]
      * see maple file ./doc/NeoHookean_principalStretches.mw for derivative
      */

    static const bool constantK=false;

    Real mimuVol;  ///< 0.5 * shear modulus * volume
    Real bulkVol;   ///<  bulk modulus * volume
    bool stabilization;

    mutable MatBlock _K;

    void init(const Real &youngM,const Real &poissonR, bool _stabilization)
    {
        Real vol=1.;
        if(this->volume) vol=(*this->volume)[0];

        Real mu = 0.5* youngM/(1+poissonR);
        Real bulk = youngM/(3*(1-2*poissonR));

        mimuVol = mu*0.5*vol;
        bulkVol = bulk*vol;
        stabilization = _stabilization;
    }

    Real getPotentialEnergy(const Coord& x) const override
    {
        const Real& U1 = x.getStrain()[0];
        const Real& U2 = x.getStrain()[1];

        Real J = U1*U2;
        Real Jm1 = J-1;
        Real squareU[2] = { U1*U1, U2*U2 };
        return mimuVol*((squareU[0]+squareU[1]+1)*pow(J,-2.0/3.0)-(Real)3.) +
                0.5*bulkVol*Jm1*Jm1;
    }

    void addForce( Deriv& f, const Coord& x, const Deriv& /*v*/) const override
    {
        const Real& U1 = x.getStrain()[0];
        const Real& U2 = x.getStrain()[1];

        Real squareU[2] = { U1*U1, U2*U2 };

        const Real J =  U1 *  U2;
        const Real Jm1 = J-1;

        const Real Jm23 = pow(J,-2.0/3.0);
        const Real Jm53 = pow(J,-5.0/3.0);
        const Real Jm83 = pow(J,-8.0/3.0);

        const Real I1 = squareU[0] + squareU[1] + 1;

        Real firstInv = 2 * Jm23;
        Real secondInv = -2.0/3.0 * I1 * Jm53;
        Real thirdInv = bulkVol * Jm1;

        f.getStrain()[0] -= mimuVol * (firstInv * U1 + secondInv * U2) + thirdInv * U2;
        f.getStrain()[1] -= mimuVol * (firstInv * U2 + secondInv * U1) + thirdInv * U1;


        firstInv += -8.0/3.0 * J * Jm53;
        secondInv = 10.0/9.0 * I1 * Jm83;

        _K[0][0] = mimuVol * ( firstInv + secondInv*squareU[1] ) + bulkVol * squareU[1];
        _K[0][1] = mimuVol * ( -4.0/3.0 * Jm53 * ( squareU[0] + squareU[1] + 0.5*I1 ) + secondInv*J ) + bulkVol * J;
        _K[1][0] = _K[0][1];
        _K[1][1] = mimuVol * ( firstInv + secondInv*squareU[0] ) + bulkVol * squareU[0];

        // ensure _K is symmetric positive semi-definite (even if it is not as good as positive definite) as suggested in [Teran05]
        if( stabilization ) helper::Decompose<Real>::PSDProjection( _K );
    }

    void addDForce( Deriv& df, const Deriv& dx, const SReal& kfactor, const SReal& /*bfactor*/ ) const override
    {
        df.getStrain() -= _K * dx.getStrain() * kfactor;
    }

    MatBlock getK() const override
    {
        return -_K;
    }

    MatBlock getC() const override
    {
        MatBlock C = MatBlock();
        C.invert( _K );
        return C;
    }

    MatBlock getB() const override
    {
        return MatBlock();
    }
};


//////////////////////////////////////////////////////////////////////////////////
////  I331
//////////////////////////////////////////////////////////////////////////////////

template<class _Real>
class NeoHookeanMaterialBlock< I331(_Real) > :
    public  BaseMaterialBlock< I331(_Real) >
{
public:
    typedef I331(_Real) T;

    typedef BaseMaterialBlock<T> Inherit;
    typedef typename Inherit::Coord Coord;
    typedef typename Inherit::Deriv Deriv;
    typedef typename Inherit::MatBlock MatBlock;
    typedef typename Inherit::Real Real;

    /**
      * DOFs: sqrt(I1), sqrt(I2), J
      *
      * classic Mooney rivlin
      *     - W = vol* [ lambda/2 ( I1 - 3)  + bulk/2 (I3 -1)^2 ]
      *     - f = -vol [ 2*C1*sqrt(I1) , 0 , bulk*(J-1) ]
      *     - df =  -vol [ 2*C1 , 0 , bulk*dJ ]
      */

    static const bool constantK=false;

    Real mimuVol;  ///<  first coef * volume * 2
    Real bulkVol; ///< bulk modulus * volume

    void init(const Real &youngM,const Real &poissonR,bool)
    {
        Real vol=1.;
        if(this->volume) vol=(*this->volume)[0];

        Real mu = 0.5* youngM/(1+poissonR);
        Real bulk = youngM/(3*(1-2*poissonR));

        mimuVol = mu*0.5*vol;
        bulkVol = bulk*vol;
    }

    Real getPotentialEnergy(const Coord& x) const override
    {
        Real Jm1 = x.getStrain()[2]-(Real)1;
        return mimuVol*(Real)0.5*(x.getStrain()[0]*x.getStrain()[0]-(Real)3.) +
               bulkVol*(Real)0.5*Jm1*Jm1;
    }

    void addForce( Deriv& f , const Coord& x , const Deriv& /*v*/) const override
    {
        f.getStrain()[0]-=mimuVol*x.getStrain()[0];
        f.getStrain()[2]-=bulkVol*(x.getStrain()[2]-(Real)1.);
    }

    void addDForce( Deriv&   df, const Deriv&   dx, const SReal& kfactor, const SReal& /*bfactor*/ ) const override
    {
        df.getStrain()[0]-=mimuVol*dx.getStrain()[0]*kfactor;
        df.getStrain()[2]-=bulkVol*dx.getStrain()[2]*kfactor;
    }

    MatBlock getK() const override
    {
        MatBlock K = MatBlock();
        K[0][0]=-mimuVol;
        K[2][2]=-bulkVol;
        return K;
    }

    MatBlock getC() const override
    {
        MatBlock C = MatBlock();
        C[0][0]=1./mimuVol;
        C[2][2]=1./bulkVol;
        return C;
    }

    MatBlock getB() const override
    {
        return MatBlock();
    }
};







} // namespace defaulttype
} // namespace sofa



#endif

