﻿/******************************************************************************
*       SOFA, Simulation Open-Framework Architecture, version 1.0 RC 1        *
*                (c) 2006-2011 MGH, INRIA, USTL, UJF, CNRS                    *
*                                                                             *
* This library is free software; you can redistribute it and/or modify it     *
* under the terms of the GNU Lesser General Public License as published by    *
* the Free Software Foundation; either version 2.1 of the License, or (at     *
* your option) any later version.                                             *
*                                                                             *
* This library is distributed in the hope that it will be useful, but WITHOUT *
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or       *
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public License *
* for more details.                                                           *
*                                                                             *
* You should have received a copy of the GNU Lesser General Public License    *
* along with this library; if not, write to the Free Software Foundation,     *
* Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301 USA.          *
*******************************************************************************
*                               SOFA :: Modules                               *
*                                                                             *
* Authors: The SOFA Team and external contributors (see Authors.txt)          *
*                                                                             *
* Contact information: contact@sofa-framework.org                             *
******************************************************************************/
#define SOFA_COMPONENT_FORCEFIELD_HEXA_FEM_FF_CPP

#include "HexaFEMForceField.inl"
#include <sofa/defaulttype/Vec3Types.h>
#include <SofaBaseMechanics/MechanicalObject.h>
#include <sofa/core/ObjectFactory.h>
//#include <typeinfo>

namespace sofa
{

namespace component
{

namespace forcefield
{

using namespace sofa::defaulttype;

const unsigned int HexaFF_Order::ind[8] = {0, 1, 2, 3, 4, 5, 6, 7};

SOFA_DECL_CLASS(HexaFEMForceField)

// Register in the Factory
int HexaFEMForceFieldClass = core::RegisterObject("Corotational FEM Hexahedral finite elements")
#ifndef SOFA_FLOAT
                                 .add< HexaFEMForceField< Vec3dTypes > >()
#endif
#ifndef SOFA_DOUBLE
                                 .add< HexaFEMForceField< Vec3fTypes > >()
#endif
    ;

#ifndef SOFA_FLOAT
template class SOFA_MISC_FEM_API HexaFEMForceField< Vec3dTypes >;
#endif
#ifndef SOFA_DOUBLE
template class SOFA_MISC_FEM_API HexaFEMForceField< Vec3fTypes >;

#endif

} // namespace forcefield

} // namespace component

} // namespace sofa
