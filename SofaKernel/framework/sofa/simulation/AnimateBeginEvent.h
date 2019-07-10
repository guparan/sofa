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
//
// C++ Interface: AnimateBeginEvent
//
// Description:
//
//
// Author: Jeremie Allard, MGH/CIMIT, (C) 2006
//
// Copyright: See COPYING file that comes with this distribution
//
//
#ifndef SOFA_SIMULATION_ANIMATEBEGINEVENT_H
#define SOFA_SIMULATION_ANIMATEBEGINEVENT_H

#include <sofa/core/objectmodel/Event.h>
#include <sofa/simulation/config.h>

namespace sofa
{

namespace simulation
{

/**
  Event fired by Simulation::animate() before computing a new animation step.
  @author Jeremie Allard
*/
class SOFA_SOFASIMULATIONCORE_API AnimateBeginEvent : public sofa::core::objectmodel::Event
{
public:

    SOFA_EVENT_H( AnimateBeginEvent )

    AnimateBeginEvent( SReal dt );

    ~AnimateBeginEvent() override;

    SReal getDt() const { return dt; }
    const char* getClassName() const override { return "AnimateBeginEvent"; }
protected:
    SReal dt;
};


} // namespace simulation

} // namespace sofa

#endif
