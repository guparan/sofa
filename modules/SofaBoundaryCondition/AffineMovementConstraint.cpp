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
#define SOFABOUNDARYCONDITION_AFFINEMOVEMENT_CONSTRAINT_CPP

#include <sofa/core/ObjectFactory.h>
#include <sofa/defaulttype/Vec3Types.h>
#include <sofa/defaulttype/RigidTypes.h>

#include <sofa/simulation/Node.h>

#include <SofaBoundaryCondition/AffineMovementConstraint.inl>

namespace sofa
{

namespace component
{

namespace projectiveconstraintset
{

int AffineMovementConstraintRegister = core::RegisterObject("Constraint the movement by a rigid transform.")
#ifdef SOFA_WITH_DOUBLE
        .add< AffineMovementConstraint<defaulttype::Vec3dTypes> >()
        .add< AffineMovementConstraint<defaulttype::Rigid3dTypes> >()
#endif // SOFA_WITH_DOUBLE
#ifdef SOFA_WITH_FLOAT
        .add< AffineMovementConstraint<defaulttype::Vec3fTypes> >()
        .add< AffineMovementConstraint<defaulttype::Rigid3fTypes> >()
#endif // SOFA_WITH_FLOAT
        ;

#ifdef SOFA_WITH_DOUBLE
template class SOFA_BOUNDARY_CONDITION_API AffineMovementConstraint<defaulttype::Vec3dTypes>;
template class SOFA_BOUNDARY_CONDITION_API AffineMovementConstraint<defaulttype::Rigid3dTypes>;
#endif // SOFA_WITH_DOUBLE

#ifdef SOFA_WITH_FLOAT
template class SOFA_BOUNDARY_CONDITION_API AffineMovementConstraint<defaulttype::Vec3fTypes>;
template class SOFA_BOUNDARY_CONDITION_API AffineMovementConstraint<defaulttype::Rigid3fTypes>;
#endif // SOFA_WITH_FLOAT

} // namespace projectiveconstraintset

} // namespace component

} // namespace sofa
