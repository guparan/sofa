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

#ifndef _OGL_TEXCOORD_MAPPING_ENGINE_H_
#define _OGL_TEXCOORD_MAPPING_ENGINE_H_
#include "config.h"

#include <sofa/defaulttype/VecTypes.h>
#include <sofa/core/DataEngine.h>
#include <SofaBaseVisual/VisualModelImpl.h>

namespace sofa
{

namespace component
{

namespace visualmodel
{

template<typename DataTypes, typename MappedDataTypes>
class TexcoordMappingEngine: public core::DataEngine
{
public:
    SOFA_CLASS(SOFA_TEMPLATE2(TexcoordMappingEngine, DataTypes, MappedDataTypes), core::DataEngine);

    typedef VisualModelImpl::TexCoord TexCoord;
    typedef VisualModelImpl::VecTexCoord VecTexCoord;

    typedef typename DataTypes::Coord Coord;
    typedef typename DataTypes::VecCoord VecCoord;
    typedef typename MappedDataTypes::Coord MappedCoord;
    typedef typename MappedDataTypes::VecCoord MappedVecCoord;

protected:
    TexcoordMappingEngine();
    virtual ~TexcoordMappingEngine() override {}
public:
    void init() override;

    void doUpdate() override;

    /// Pre-construction check method called by ObjectFactory.
    /// Check that DataTypes matches the MechanicalState.
    template<class T>
    static bool canCreate(T*& obj, sofa::core::objectmodel::BaseContext* context, sofa::core::objectmodel::BaseObjectDescription* arg)
    {
        return BaseObject::canCreate(obj, context, arg);
    }

    /// Construction method called by ObjectFactory.
    template<class T>
    static typename T::SPtr create(T* tObj, sofa::core::objectmodel::BaseContext* context, sofa::core::objectmodel::BaseObjectDescription* arg)
    {
        return BaseObject::create(tObj, context, arg);
    }

    virtual std::string getTemplateName() const override
    {
        return templateName(this);
    }

    static std::string templateName(const TexcoordMappingEngine<DataTypes, MappedDataTypes>* = nullptr)
    {
        return DataTypes::Name();
    }

    Data<VecCoord> d_inputPosition;
    Data<VecTexCoord> d_inputTexcoord;
    Data<MappedVecCoord> d_inputMappedPosition;
    Data<VecTexCoord> d_outputMappedTexcoord;

protected:

};


} // namespace visual

} // namespace component

} // namespace sofa

#endif
