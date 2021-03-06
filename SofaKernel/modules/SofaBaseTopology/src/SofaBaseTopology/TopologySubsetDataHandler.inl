/******************************************************************************
*                 SOFA, Simulation Open-Framework Architecture                *
*                    (c) 2006 INRIA, USTL, UJF, CNRS, MGH                     *
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
#pragma once
#include <SofaBaseTopology/TopologySubsetDataHandler.h>

namespace sofa::component::topology
{

///////////////////// Private functions on TopologySubsetDataHandler changes /////////////////////////////
template <typename TopologyElementType, typename VecT>
void TopologySubsetDataHandler <TopologyElementType, VecT>::swap( Index i1, Index i2 )
{
    container_type& data = *(m_topologyData->beginEdit());

    iterator it= std::find(data.begin(),data.end(),i1);
    if (it!=data.end())
        (*it)=i2;
    m_topologyData->endEdit();
}


template <typename TopologyElementType, typename VecT>
void TopologySubsetDataHandler <TopologyElementType, VecT>::add(sofa::Size nbElements,
        const sofa::helper::vector<sofa::helper::vector<Index> > &ancestors,
        const sofa::helper::vector<sofa::helper::vector<double> > &coefs)
{
    // Using default values
    container_type& data = *(m_topologyData->beginEdit());

    size_t size = data.size();
    bool test;
    for (std::size_t i = 0; i < nbElements; ++i)
    {
        if (ancestors.empty() || coefs.empty())
        {
            const sofa::helper::vector< Index > empty_vecint;
            const sofa::helper::vector< double > empty_vecdouble;
            test = this->applyTestCreateFunction(Index(size + i), empty_vecint, empty_vecdouble);
        }
        else
            test = this->applyTestCreateFunction(Index(size + i), ancestors[i], coefs[i]);

        if (test)
            data.push_back((size+i) );
    }
    this->lastElementIndex+=nbElements;
}


template <typename TopologyElementType, typename VecT>
void TopologySubsetDataHandler <TopologyElementType, VecT>::add(sofa::Size nbElements,
        const sofa::helper::vector< TopologyElementType >& ,
        const sofa::helper::vector<sofa::helper::vector<Index> > &ancestors,
        const sofa::helper::vector<sofa::helper::vector<double> > &coefs)
{
    this->add(nbElements, ancestors, coefs);
}


template <typename TopologyElementType, typename VecT>
void TopologySubsetDataHandler <TopologyElementType, VecT>::move( const sofa::helper::vector<Index> &,
        const sofa::helper::vector< sofa::helper::vector< Index > >& ,
        const sofa::helper::vector< sofa::helper::vector< double > >& )
{

}


template <typename TopologyElementType, typename VecT>
void TopologySubsetDataHandler <TopologyElementType, VecT>::remove( const sofa::helper::vector<Index> &index )
{
    container_type& data = *(m_topologyData->beginEdit());
    std::size_t it1;
    std::size_t it2;

    for (std::size_t i = 0; i < index.size(); ++i)
    {
        it1=0;
        while(it1<data.size())
        {
            if(data[it1]==index[i])
                break;
            else
                it1+=1;
        }


        if (it1<data.size())
        {
            it2=0;
            while(it2<data.size())
            {
                if(data[it2]==this->lastElementIndex)
                    break;
                else
                    it2+=1;
            }

            if (it2<data.size())
                data[it2]=index[i];

            data[it1]=data[data.size()-1];
           size_t size_before = data.size();

            // Call destroy function implemented in specific component
            this->applyDestroyFunction(index[i], data[data.size()-1]);

            // As applyDestroyFunction could already perfom the suppression, if implemented. Size is checked again. If no change this handler really perform the suppresion
            if (size_before == data.size())
                data.resize(data.size() - 1);
        }
        else
        {
            it2=0;
            while(it2<data.size())
            {
                if(data[it2]==this->lastElementIndex)
                    break;
                else
                    it2+=1;
            }

            if (it2<data.size())
            {
                data[it2]=index[i];
            }
        }
        --this->lastElementIndex;
    }

    m_topologyData->endEdit();
}


template <typename TopologyElementType, typename VecT>
void TopologySubsetDataHandler <TopologyElementType, VecT>::renumber( const sofa::helper::vector<Index> &index )
{
    container_type& data = *(m_topologyData->beginEdit());
    container_type copy = m_topologyData->getValue(); // not very efficient memory-wise, but I can see no better solution...

    for (std::size_t i = 0; i < data.size(); ++i)
    {
        data[i] = copy[ index[i] ];
    }
    m_topologyData->endEdit();
}


template <typename TopologyElementType, typename VecT>
void TopologySubsetDataHandler <TopologyElementType, VecT>::addOnMovedPosition(const sofa::helper::vector<Index> &,
        const sofa::helper::vector<TopologyElementType> &)
{
    dmsg_error("TopologySubsetDataHandler") << "addOnMovedPosition event on topology subsetData is not yet handled." ;
}


template <typename TopologyElementType, typename VecT>
void TopologySubsetDataHandler <TopologyElementType, VecT>::removeOnMovedPosition(const sofa::helper::vector<Index> &)
{
    dmsg_error("TopologySubsetDataHandler") << "removeOnMovedPosition event on topology subsetData is not yet handled" ;
}


} //namespace sofa::component::topology
