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
#ifndef _OGL_TEXCOORD_MAPPING_ENGINE_INL_
#define _OGL_TEXCOORD_MAPPING_ENGINE_INL_

#include <SofaOpenglVisual/TexcoordMappingEngine.h>
#include <sofa/core/visual/VisualParams.h>
#include <sofa/core/topology/TopologyChange.h>
#include <sofa/core/ObjectFactory.h>

namespace sofa
{

namespace component
{

namespace visualmodel
{

template<typename DataTypes, typename MappedDataTypes>
TexcoordMappingEngine<DataTypes, MappedDataTypes>::TexcoordMappingEngine()
    : core::DataEngine()
    , d_inputPosition(initData(&d_inputPosition, "inputPosition", "Position where Texcoords are known"))
    , d_inputTexcoord(initData(&d_inputTexcoord, "inputTexcoord", "Defined texcoords"))
    , d_inputMappedPosition(initData(&d_inputMappedPosition, "inputMappedPosition", "Position on which Texcoords are unknown"))
    , d_outputMappedTexcoord(initData(&d_outputMappedTexcoord, "outputMappedTexcoord", "Resulting mapped texcoords"))
{
    this->addInput(&d_inputPosition);
    this->addInput(&d_inputTexcoord);
    this->addInput(&d_inputMappedPosition);

    this->addOutput(&d_outputMappedTexcoord);
}


template<typename DataTypes, typename MappedDataTypes>
void TexcoordMappingEngine<DataTypes, MappedDataTypes>::init()
{

}

template<typename DataTypes, typename MappedDataTypes>
void TexcoordMappingEngine<DataTypes, MappedDataTypes>::doUpdate()
{
    const VecCoord& inputPosition = d_inputPosition.getValue();
    const VecTexCoord& inputTexcoord = d_inputTexcoord.getValue();
    const MappedVecCoord& inputMappedPosition = d_inputMappedPosition.getValue();

    VecTexCoord& outputMappedTexcoord = *d_outputMappedTexcoord.beginEdit();

    if(inputPosition.size() != inputTexcoord.size() && inputPosition.size() < 1)
    {
        msg_error(this) << "Input vectors size inconsistent...";
        return;
    }

    outputMappedTexcoord.clear();

    for(size_t i=0 ; i< inputMappedPosition.size() ; i++)
    {
        const MappedCoord& mappedPosition = inputMappedPosition[i];

        //get closest input position
        size_t indexMinPosition = 0;
        double minDist2 = std::numeric_limits<double>::max();
        for(size_t j=0 ; j< inputPosition.size() ; j++)
        {
            const Coord& position = inputPosition[j];

            double dist2 = 0.0;
            //Assert that the position are in the same coord system type
            for(size_t k = 0 ; k < DataTypes::spatial_dimensions ; k++)
                dist2 += (position[k] - mappedPosition[k]) * (position[k] - mappedPosition[k]);

            if(dist2 < minDist2)
            {
                minDist2 = dist2;
                indexMinPosition = j;
            }
        }

        //get corresponding texcoord (without any interpolation, TODO)
        const TexCoord& tex = inputTexcoord[indexMinPosition];
        outputMappedTexcoord.push_back(tex);
    }


    d_outputMappedTexcoord.endEdit();
}

} // namespace visual

} // namespace component

} // namespace sofa

#endif // _OGL_TEXCOORD_MAPPING_ENGINE_INL_
