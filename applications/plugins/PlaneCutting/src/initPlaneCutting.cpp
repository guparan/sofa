/******************************************************************************
*       SOFA, Simulation Open-Framework Architecture, development version     *
*                (c) 2006-2017 INRIA, USTL, UJF, CNRS, MGH                    *
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
#include "config.h"

namespace sofa
{

namespace component
{

//Here are just several convenient functions to help user to know what contains the plugin

extern "C" {
PLANECUTTING_API void initExternalModule();
PLANECUTTING_API const char* getModuleName();
PLANECUTTING_API const char* getModuleVersion();
PLANECUTTING_API const char* getModuleLicense();
PLANECUTTING_API const char* getModuleDescription();
PLANECUTTING_API const char* getModuleComponentList();
}

void initExternalModule()
{
    static bool first = true;
    if (first) {
        first = false;
    }
}

const char* getModuleName()
{
    return "Plugin Plane Cutting";
}

const char* getModuleVersion()
{
    return "alpa 1.0";
}

const char* getModuleLicense()
{
    return "LGPL";
}

const char* getModuleDescription()
{
    return "Cutting with SOFA Framework's connectivity";
}

const char* getModuleComponentList()
{
    return "controllers ";
}

}

}
