/******************************************************************************
*       SOFA, Simulation Open-Framework Architecture, development version     *
*                (c) 2006-2017 INRIA, USTL, UJF, CNRS, MGH                    *
*                                                                             *
* This program is free software; you can redistribute it and/or modify it     *
* under the terms of the GNU General Public License as published by the Free  *
* Software Foundation; either version 2 of the License, or (at your option)   *
* any later version.                                                          *
*                                                                             *
* This program is distributed in the hope that it will be useful, but WITHOUT *
* ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or       *
* FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for    *
* more details.                                                               *
*                                                                             *
* You should have received a copy of the GNU General Public License along     *
* with this program. If not, see <http://www.gnu.org/licenses/>.              *
*******************************************************************************
* Authors: The SOFA Team and external contributors (see Authors.txt)          *
*                                                                             *
* Contact information: contact@sofa-framework.org                             *
******************************************************************************/
#include <sofa/helper/system/FileSystem.h>
#include <sofa/helper/Utils.h>

#include <SofaSimulationTree/init.h>
#include <SofaSimulationTree/TreeSimulation.h>

#include <QApplication>

#include "Tutorials.h"


int main(int argc, char** argv)
{
    QApplication application(argc, argv);

    sofa::simulation::tree::init();
    sofa::simulation::setSimulation(new sofa::simulation::tree::TreeSimulation());

    const std::string etcDir = sofa::helper::Utils::getSofaPathPrefix() + "/etc";
    const std::string sofaIniFilePath = etcDir + "/sofa.ini";
    std::map<std::string, std::string> iniFileValues = sofa::helper::Utils::readBasicIniFile(sofaIniFilePath);

    if (iniFileValues.find("SHARE_DIR") != iniFileValues.end())
    {
        std::string shareDir = iniFileValues["SHARE_DIR"];
        if (!sofa::helper::system::FileSystem::isAbsolute(shareDir))
            shareDir = etcDir + "/" + shareDir;
        sofa::helper::system::DataRepository.addFirstPath(shareDir);
    }

    if (iniFileValues.find("EXAMPLES_DIR") != iniFileValues.end())
    {
        std::string examplesDir = iniFileValues["EXAMPLES_DIR"];
        if (!sofa::helper::system::FileSystem::isAbsolute(examplesDir))
            examplesDir = etcDir + "/" + examplesDir;
        sofa::helper::system::DataRepository.addFirstPath(examplesDir);
    }

    Q_INIT_RESOURCE(icons);

    sofa::gui::qt::Tutorials tuto;
    tuto.show();

    int appReturnCode = application.exec();
    sofa::simulation::tree::cleanup();
    return appReturnCode;
}
