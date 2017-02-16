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
#ifndef SOFA_SOFATUTORIALMANAGER_H
#define SOFA_SOFATUTORIALMANAGER_H

#include "TutorialSelector.h"
#include "GraphModeler.h"

#include <QMainWindow>
#include <QTextBrowser>
#include <QAction>
#include <QKeyEvent>
#include <QUrl>
#include <QComboBox>
#include <QProcess>


namespace sofa
{

namespace gui
{

namespace qt
{


class SofaTutorialsManager : public QMainWindow
{
    Q_OBJECT
public:
    SofaTutorialsManager(QWidget* parent = 0, const char *name = "");
    SofaTutorialsManager::~SofaTutorialsManager();
    GraphModeler *getGraph() {return graph;}

    void keyPressEvent ( QKeyEvent * e );

public slots:
    void openMainCategory();
    void openCategory(const std::string &);
    void openTutorial(const std::string &filename);
    void openHTML(const std::string &filename);
    void dynamicChangeOfScene( const QUrl&);

    void launchScene();
    void editScene();

    void runInSofa(const std::string& sceneFilename, Node *root);
    void runInModeler(const std::string &sceneFilename, Node* root);

    void changeSofaBinary();
    void childProcessExited(int exitCode, QProcess::ExitStatus exitStatus);

protected:
    TutorialSelector *selector;
    GraphModeler *graph;
    QTextBrowser* descriptionPage;
    QPushButton *buttonRunInSofa;
    QComboBox *tutorialList;
    QPushButton* buttonEditInModeler;
    QPushButton *buttonHome;

    std::list<QProcess*> runSofaProcesses;

protected slots:
    void redirectStderr();
    void redirectStdout();

signals:
    void undo();
    void redo();
    void editInModeler(const std::string& sceneFilename);

private:
    std::string sofaBinary;
    std::string modelerBinary;
    std::string binPath;
    char count;
    bool debug;

};

}
}
}

#endif
