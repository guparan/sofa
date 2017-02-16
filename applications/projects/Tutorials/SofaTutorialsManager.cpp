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

#include "SofaTutorialsManager.h"

#include <sofa/helper/system/FileRepository.h>
#include <sofa/helper/system/SetDirectory.h>
#include <SofaSimulationTree/TreeSimulation.h>
#include <sofa/simulation/XMLPrintVisitor.h>

#include <sofa/gui/GUIManager.h>
#include <sofa/gui/Main.h>
#include <sofa/gui/BaseGUI.h>
#include <sofa/gui/qt/FileManagement.h>
#include <sofa/helper/system/PluginManager.h>
#include <sofa/helper/Utils.h>
#include <sofa/helper/cast.h>

#include <SofaSimulationCommon/xml/XML.h>

#include <QHBoxLayout>
#include <QUrl>
#include <QToolBar>
#include <QSplitter>
#include <QMenuBar>
#include <QMessageBox>

namespace sofa
{

namespace gui
{

namespace qt
{

SofaTutorialsManager::SofaTutorialsManager(QWidget* parent, const char* name)
    :QMainWindow(parent), tutorialList(0)
{
    this->setObjectName(name);

    QWidget *mainWidget = new QWidget(this);
    QGridLayout *mainLayout = new QGridLayout(mainWidget);
    QSplitter *mainSplitter = new QSplitter(mainWidget);

    this->setCentralWidget(mainWidget);
    this->setAcceptDrops(true);
    this->setWindowTitle(QString("Sofa Tutorials"));

    //Add list of tutorials
    tutorialList = new QComboBox(mainWidget);

    //Add button to launch a scene in runSofa
    buttonRunInSofa = new QPushButton(QString("Launch scene in Sofa"), mainWidget);
    connect(buttonRunInSofa, SIGNAL(clicked()), this, SLOT(launchScene()));

    //Add button to edit a scene in Modeler
    buttonEditInModeler = new QPushButton(QString("Edit in Modeler"), mainWidget);
    connect(buttonEditInModeler, SIGNAL(clicked()), this, SLOT(editScene()));

    //Add home button
    buttonHome = new QPushButton(QString("Home"), mainWidget);
    connect(buttonHome, SIGNAL(clicked()), this, SLOT(openMainCategory()));

    //Create the tree containing the tutorials
    selector = new TutorialSelector(mainWidget);

    connect(selector, SIGNAL(openCategory(const std::string&)),
            this, SLOT(openCategory(const std::string&)));
    connect(selector, SIGNAL(openTutorial(const std::string&)),
            this, SLOT(openTutorial(const std::string&)));
    connect(selector, SIGNAL(openHTML(const std::string&)),
            this, SLOT(openHTML(const std::string&)));


    //Create the HTML Browser to display the information
    descriptionPage = new QTextBrowser(mainWidget);
    connect(descriptionPage, SIGNAL(anchorClicked(const QUrl&)), this, SLOT(dynamicChangeOfScene(const QUrl&)));

    //Create the Graph
    graph = new GraphModeler(mainWidget);
    graph->setAcceptDrops(true);

    //Setup sizes
    buttonHome->setMaximumWidth(50);
    selector->resize(250, selector->height());
    selector->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    descriptionPage->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    graph->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);

    //Setup the layout
    mainSplitter->addWidget(selector);
    mainSplitter->addWidget(descriptionPage);
    mainSplitter->addWidget(graph);
    mainLayout->addWidget(buttonHome, 0, 0);
    mainLayout->addWidget(tutorialList, 0, 1);
    mainLayout->addWidget(buttonRunInSofa, 0, 2);
    mainLayout->addWidget(buttonEditInModeler, 0, 3);
    mainLayout->addWidget(mainSplitter, 1, 0, 1, 4);

    //Set up the list of tutorials
    selector->init();

    const std::list<std::string> &listTuto=selector->getCategories();
    for (std::list<std::string>::const_reverse_iterator it=listTuto.rbegin(); it!=listTuto.rend(); ++it)
    {
        tutorialList->addItem(QString(it->c_str()));
    }
//    connect(tutorialList, SIGNAL(activated(const QString&)), selector, SLOT(openCategory(const QString &)));
    connect(tutorialList, SIGNAL(currentIndexChanged(QString)), selector, SLOT(openCategory(const QString &)));

    //Select All Sofa Tutorials as selected set
    tutorialList->setCurrentIndex(tutorialList->count()-1);


    this->resize(1000,600);
    QPalette p ;
    p.setColor(QPalette::Base, QColor(255,180,120));
    this->setPalette(p);
    QString pathIcon=(sofa::helper::system::DataRepository.getFirstPath() + std::string( "/icons/SOFATUTORIALS.png" )).c_str();
    this->setWindowIcon(QIcon(pathIcon));

    QMenu *settingsMenu = new QMenu(this);
    settingsMenu->setTitle(QString(tr("&Settings")));
    settingsMenu->addAction("Change Sofa Binary...", this, SLOT(changeSofaBinary()));
    this->menuBar()->addMenu(settingsMenu);
}

SofaTutorialsManager::~SofaTutorialsManager()
{
    std::cout << "destructor: runSofaProcesses.size() = " << runSofaProcesses.size() << std::endl;
    for (QProcess* process : runSofaProcesses)
    {
        if (process->state() == QProcess::ProcessState::Running)
        {
            std::cout << "Problem" << std::endl;
        }
    }
}




void SofaTutorialsManager::openTutorial(const std::string& filename)
{
    graph->closeDialogs();

    if (filename.empty())
    {
        graph->hide();
        buttonRunInSofa->hide();
        buttonEditInModeler->hide();
        return;
    }
    buttonRunInSofa->show();
    buttonEditInModeler->show();
    graph->show();
    std::string file=filename;
    const std::string &dirSofa = sofa::helper::system::SetDirectory::GetParentDir(sofa::helper::system::DataRepository.getFirstPath().c_str());
    std::string::size_type found=filename.find(dirSofa);
    if (found == 0) file = filename.substr(dirSofa.size()+1);

    buttonRunInSofa->setText( QString(" Launch ") + QString(file.c_str()) + QString(" in Sofa ") );

    //Set the Graph
    xml::BaseElement* newXML = xml::loadFromFile ( filename.c_str() );
    if (newXML == NULL) return;
    if (!newXML->init()) std::cerr<< "Objects initialization failed.\n";
    Node *root = down_cast<Node>( newXML->getObject()->toBaseNode() );
    graph->setRoot(root, false);
    graph->setFilename(filename);
    selector->usingScene(filename);
}

void SofaTutorialsManager::openHTML(const std::string &filename)
{
    if (filename.empty())
    {
        static std::string defaultHTML(sofa::helper::system::SetDirectory::GetProcessFullPath(sofa::helper::system::DataRepository.getFile( "Tutorials/Tutorials.html" ).c_str()));
        openHTML(defaultHTML);
        return;
    }

#ifdef WIN32
    descriptionPage->setSource(QUrl(QString("file:///")+QString(filename.c_str())));
#else
    descriptionPage->setSource(QUrl(QString(filename.c_str())));
#endif
}

void SofaTutorialsManager::openMainCategory()
{
    if (tutorialList)
    {
        tutorialList->setCurrentIndex(tutorialList->count()-1);
    }
}

void SofaTutorialsManager::openCategory(const std::string& filename)
{
    if (tutorialList)
    {
        tutorialList->setCurrentIndex(tutorialList->findText(QString(filename.c_str())));
    }
}

void SofaTutorialsManager::dynamicChangeOfScene( const QUrl& u)
{
    std::string path=u.path().toStdString();
#ifdef WIN32
    path = path.substr(1);
#endif
    path  = sofa::helper::system::DataRepository.getFile(path);
    std::string extension=sofa::helper::system::SetDirectory::GetExtension(path.c_str());

    if (extension == "xml" || extension == "scn")
    {
        openTutorial(path);
    }
    else if (extension == "html")
    {
        openHTML(path);
    }
}

void SofaTutorialsManager::keyPressEvent ( QKeyEvent * e )
{
    if (e->modifiers() == Qt::ControlModifier )
    {
        switch(e->key())
        {
        case Qt::Key_R:
        {
            //Pressed CTRL+R
            launchScene();
            return;
        }
        case Qt::Key_Y:
        {
            emit redo();
            return;
        }
        case Qt::Key_Z:
        {
            emit undo();
            return;
        }
        default: ;
        }
    }
    e->ignore();
}




void SofaTutorialsManager::editScene()
{
//    emit( editInModeler(graph->getFilename() ) );
    Node* root=graph->getRoot();
    runInModeler(graph->getFilename(), root);
}

void SofaTutorialsManager::launchScene()
{
//    if (sceneTab->count() == 0) return;
    Node* root=graph->getRoot();
    runInSofa(graph->getFilename(), root);
}



void SofaTutorialsManager::runInSofa(const std::string &sceneFilename, Node* root)
{
    if (!root) return;
    if (sceneFilename.empty()) return;

    // Init the scene
    sofa::gui::GUIManager::Init("Modeler");

    QString messageLaunch;
    QStringList argv;
    //=======================================
    // Run Sofa
    if (sofaBinary.empty()) //If no specific binary is specified, we use runSofa
    {
        std::string binaryName="runSofa";
#ifndef NDEBUG
        binaryName+="_d";
#endif

#ifdef WIN32
        sofaBinary = binPath + binaryName + ".exe";
#else
        sofaBinary = binPath + binaryName;
#endif
    }

    argv << QString(sceneFilename.c_str());

    QProcess *p = new QProcess(this);

    p->setWorkingDirectory(QString(binPath.c_str()) );
    p->setObjectName(QString(sceneFilename.c_str()) );

//    connect(this, SIGNAL(destroyed()), p, SLOT(kill()));
//    connect(p, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(childProcessExited(int, QProcess::ExitStatus)));
    connect(p, SIGNAL(readyReadStandardOutput()), this, SLOT(redirectStdout()) );
    connect(p, SIGNAL(readyReadStandardError()), this, SLOT(redirectStderr()) );

    p->start(QString(sofaBinary.c_str()), argv);

    runSofaProcesses.push_back(p);
    std::cout << "runInModeler: runSofaProcesses.size() = " << runSofaProcesses.size() << std::endl;

//    statusBar()->showMessage(messageLaunch,5000);
}

void SofaTutorialsManager::runInModeler(const std::string &sceneFilename, Node* root)
{
    if (!root) return;
    if (sceneFilename.empty()) return;

    QStringList argv;
    //=======================================
    // Run Sofa
    if (modelerBinary.empty())
    {
        std::string binaryName="Modeler";
#ifndef NDEBUG
        binaryName+="_d";
#endif

#ifdef WIN32
        modelerBinary = binPath + binaryName + ".exe";
#else
        modelerBinary = binPath + binaryName;
#endif
    }

    argv << QString::fromStdString(sceneFilename);
//    argv << "-g" << "default";
//    argv << "-t";

    QProcess *p = new QProcess(this);

    p->setWorkingDirectory(QString(binPath.c_str()) );
    p->setObjectName(QString(sceneFilename.c_str()) );

    std::cout << "runInModeler: runSofaProcesses.size() = " << runSofaProcesses.size() << std::endl;
    connect(this, SIGNAL(destroyed()), p, SLOT(terminate()));
//    connect(p, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(childProcessExited(int, QProcess::ExitStatus)));
    connect(p, SIGNAL(readyReadStandardOutput()), this, SLOT(redirectStdout()) );
    connect(p, SIGNAL(readyReadStandardError()), this, SLOT(redirectStderr()) );

    p->start(QString(modelerBinary.c_str()), argv);

//    runSofaProcesses.push_back(p);

//    statusBar()->showMessage(messageLaunch,5000);
}


void SofaTutorialsManager::redirectStdout()
{
    QProcess* p = ((QProcess*) sender());
    if( p && p->waitForStarted(-1) )
    {
        std::cout << "FROM SOFA [OUT] >> " << QString(p->readAllStandardOutput()).toStdString() << std::endl;
    }
}

void SofaTutorialsManager::redirectStderr()
{
    QProcess* p = ((QProcess*) sender());
    if( p && p->waitForStarted(-1))
    {
        std::cerr << "FROM SOFA [ERR] >> " << QString(p->readAllStandardError()).toStdString() << std::endl;
    }
}


void SofaTutorialsManager::childProcessExited(int exitCode, QProcess::ExitStatus exitStatus)
{
    QProcess *p = ((QProcess*) sender());
    std::string programName;

    programName = p->objectName().toStdString();

//    removeTemporaryFiles(programName);
    if (exitStatus == QProcess::NormalExit )
    {
        p->closeWriteChannel();
        disconnect(p, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(childProcessExited(int, QProcess::ExitStatus)));
        disconnect(p, SIGNAL( readyReadStandardOutput () ), this , SLOT ( redirectStdout() ) );
        disconnect(p, SIGNAL( readyReadStandardError () ), this , SLOT ( redirectStderr() ) );
        if(p->atEnd())
            std::cout << "Sofa exited safely." << std::endl;
        else
            std::cout << "Chelou." << std::endl;
        p->kill();
        return;
    }
    for (QProcess* process : runSofaProcesses)
    {
        if (process == p)
        {
            const QString caption("Problem");
            const QString warning("Error running Sofa, error code ");
            QMessageBox::critical( this, caption,warning + QString(exitCode), QMessageBox::Ok | QMessageBox::Escape, QMessageBox::NoButton );
            return;
        }
    }
}

/*****************************************************************************************************************/
//runSofa Options
void SofaTutorialsManager::changeSofaBinary()
{

    QString s = getOpenFileName ( this, QString(binPath.c_str()),
#ifdef WIN32
            "All Files(*.exe)",
#else
            "All Files(*)",
#endif
            "Open SOFA binary",  "Choose a binary to use" );
    if (s.length() >0)
    {
        sofaBinary=s.toStdString();
        binPath=sofa::helper::system::SetDirectory::GetParentDir(sofaBinary.c_str());
    }
    else
    {
        sofaBinary.clear();
    }
}



}
}
}
