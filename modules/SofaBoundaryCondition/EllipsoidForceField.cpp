/******************************************************************************
*       SOFA, Simulation Open-Framework Architecture, development version     *
*                (c) 2006-2019 INRIA, USTL, UJF, CNRS, MGH                    *
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
#define SOFA_COMPONENT_FORCEFIELD_ELLIPSOIDFORCEFIELD_CPP

#include <SofaBoundaryCondition/EllipsoidForceField.inl>
#include <sofa/defaulttype/VecTypes.h>
#include <sofa/core/ObjectFactory.h>

namespace sofa
{

namespace component
{

namespace forcefield
{

using namespace sofa::defaulttype;

int EllipsoidForceFieldClass = core::RegisterObject("Repulsion applied by an ellipsoid toward the exterior or the interior")

        .add< EllipsoidForceField<Vec3Types> >()
        .add< EllipsoidForceField<Vec2Types> >()
        .add< EllipsoidForceField<Vec1Types> >()

        ;
template class SOFA_SOFABOUNDARYCONDITION_API EllipsoidForceField<Vec3Types>;
template class SOFA_SOFABOUNDARYCONDITION_API EllipsoidForceField<Vec2Types>;
template class SOFA_SOFABOUNDARYCONDITION_API EllipsoidForceField<Vec1Types>;


} // namespace forcefield

} // namespace component

} // namespace sofa
