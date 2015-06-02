/*
 * Copyright (C) 2014 Joseph Mills.
 *
 */
#include "applicationlauncher.h"


/*!
    \qmltype Application
    \inqmlmodule Mango.System
    \ingroup Mango.System
    \since 5.3
    \brief  Qml Plugin to run extrenal commands and or applicaions.

    Contains classes for running extrenal apps or commands from QML .

    The mango application module provides classes to
    run extrneal applications and or commands from within qml
    This is a QML plugin.  One can read the output and there command
    also many different qmlsignals that get used in this modual.
    */
Application::Application(QObject *parent) :
    QObject(parent),
    m_isApp(false),
    m_startDetached(false)
{
    connect(&m_process,SIGNAL(readyReadStandardError()),this,SLOT(processReadyRead()));
    connect(&m_process,SIGNAL(started()),this,SLOT(processStarted()));
    connect(&m_process,SIGNAL(finished(int)),this,SLOT(processFinished(int)));
    connect(&m_process,SIGNAL(readyRead()),this,SLOT(processReadyRead()));
    connect(&m_process,SIGNAL(error(QProcess::ProcessError)),this,SLOT(processError(QProcess::ProcessError)));
}

/*!
    \qmlproperty string Application::appName
    used in qml to set a application name and or command.
    Example:
    \code
    Application{
        appName: "vlc"
    }
    \endcode
*/

QString Application::appName() const
{
    return m_AppName;
}

/*!
  \qmlproperty string Application::setAppName
  used to set the applications and or command from the c++ side of things
 */
void Application::setAppName(const QString &appName)
{
    m_AppName = appName;
}

/*!
  \qmlproperty string Application::arguments
  set arguments to a command.  This is only used when running commands and need to add
  extra arguments to the command. Please see isApp.
  All white spaces sould be escaped
  \code
  Application {
  appName: "tar"
  arguments: "\-czf\ some.tar.gz\ some/"
  }
  \endcode
*/
QString Application::arguments() const
{
    return m_Arguments;
}

/*!
 * \qmlproperty string Application::setArguments
 * used on the c++ side of things to set the appliction arguments
 */
void Application::setArguments(const QString &arguments)
{
    m_Arguments = arguments;
}

//ProcessChannelMode Application::processMode() const
//{
//    return m_processMode;

//}

//void Application::setProcessMode(const ProcessChannelMode &processMode)
//{
//    m_process.setProcessChannelMode(processMode);
//}

/*!
 * \qmlproperty bool Application::isApp
 *
 * bool property that is used in qml to tell the Application module if it is a application or a command
 * Example For a Application:
 * \code
 * Application{
 *	isApp: true
 *	appName: "vlc"
 *	}
 * \endcode
 * Example for a command:
 * \code
 * Application {
 *	isApp: false
 *	appName: "echo\ \"Hello\ World\""
 *    }
 * \endcode
 */

bool Application::isApp()const
{
    return m_isApp;
}


/*!
 * \qmlproperty bool Application::setIsApp
 *
 * used on the cpp side of things to set the isApp parma
 */
void Application::setIsApp(bool &isApp)
{
    if (m_isApp == isApp)
        return;
    m_isApp = isApp;
    emit isAppChanged();
}

/*!
 * \qmlproperty bool Application::startDetached
 *
 * qml property to tell the Application if it should be launched extrenal and not intrenal with in the qml app. default is set to false
 */
bool Application::startDetached()
{
    return m_startDetached;
}

/*!
 * \qmlproperty bool Application::setStartDetached
 *
 * used on the cpp side of things to set startDetached in QML
 */

void Application::setStartDetached(bool startDetached)
{
    m_startDetached = startDetached;
}

/*!
 * \qmlproperty bool Application::running
 *
 * returns true if a application and or command is running
 * returns false if it is not.
 * can be put on qml signals also
 *\code
 *Application {
 * ...
 * .......
 * onRunning: console.log("I am a running application " + appName )
 * }
 * \endcode
 */

bool Application::running()
{
    if(m_process.state() != 0)
    {
        m_running = true;
        return m_running;
    }
    else
    {
        m_running = false ;
        return m_running;
    }
}

/*!
 * \qmlsignal Application::getOutPut()
 *
 * a function that is used to return the output (string) of the command or program that is curently running.
 * \code
 * Application{
 * id: applauncher
 * ....
 * .......
 * }
 * Button{
 * onClicked: applauncher.running ? console.log("the debug message of the extrenal app " applauncher.getOutPut() ) : console.log("the application " + applauncher.appName + " Is not running ")
 * }
 * \endcode
 */

QString Application::getOutPut() const
{
    return m_getOutPut;
}


/*!
 * \qmlsignal  Application::close()
 * used to close the application and or command nicley
 */
void Application::close() {
    m_process.close();
    m_process.waitForFinished();
    emit running(false);
}

/*!
 * \qmlsignal Application::stop()
 * used to stop the application.  This is used only if close is not working
 * also see kill()
 */
void Application::stop() {
    kill();
    emit running(false);
}

/*!
 * \qmlsignal Application::processStarted()
 * used to tell the user if the command and or application has started
 */
void Application::processStarted() {
    emit started(m_process.program());
    emit running(true);
}
/*!
 * \qmlsignal  Application::kill()
 *  used to kill a application that is not responding. also see close() and stop()
 */
void Application::kill() {
    this->clear();
    m_process.kill();
    m_process.waitForFinished();
    emit running(false);
}

/*!
 * \qmlsignal Application::processError()
 *
 * used to qmlsignal to qml if there is a error that happens and returns the error string to QML
 */

void Application::processError(QProcess::ProcessError err) {
    Q_UNUSED(err);
    if (m_process.exitCode() == 0) { return; }
    emit error(QString(QLatin1String("ERROR: (%0) %1")).arg(m_AppName).arg(m_process.errorString()));
    m_pendingProcesses.clear();
    emit running(false);
}


/*!
 * \qmlsignal Application::start()
 *
 * used to start the application and or command
 * Example
 * \code
 * Application{
 *      id: app
 *      isApp: true
 *      appName: "echo\ \"Hello\ World\""
 *
 * }
 * Button{
 *      onClicked: app.start();
 * }
 * \endcode
 */
void Application::start() {
    processCmdQueue();
    emit running(true);
}

/*!
 * \qmlsignal Application::processFinished()
 *
 * used to tell QML if the application and or command is done and finshed. see also finshed()
 */
void Application::processFinished(int code) {
    if (code != 0) {
        emit error(QString(QLatin1String(m_process.readAllStandardError())));
        m_pendingProcesses.clear();
        emit running(false);
        return;
    }
    QString errorMsg = QString::fromLatin1(m_process.readAllStandardError());
    if (errorMsg.trimmed().length()>0) emit error(errorMsg);
    QString msg = QString::fromLatin1(m_process.readAllStandardOutput());
    if (msg.trimmed().length()>0) emit message(msg);
    emit finished(m_process.program(), code);
    emit running(false);
}

/*!
 * \qmlsignal Application::processReadyRead()
 *
 * Used by Qml to tell if the application and or command is ready to start reading the output. see also
 * message()
 * getOutPut()
 */
void Application::processReadyRead() {
    QString stderr = QString::fromLatin1(m_process.readAllStandardError());
    QString stdout = QString::fromLatin1(m_process.readAll());

    if (!stderr.isEmpty()) {
        m_getOutPut = stderr;
        emit message(stderr);
        emit running(false);
    }
    if (!stdout.isEmpty()) {
        m_getOutPut = "";
        m_getOutPut = stdout;
        emit getOutPutChanged();
        emit message(stdout);
        emit running(false);
    }
}

/*!
 * Application::processCmdQueue()
 * used on the cpp side of things to check to see if it is a app or a command and to see if it is swtarted extrnal ect
 */
void Application::processCmdQueue() {
    QString args;
    args = m_Arguments;
    m_process.setProperty("command",m_AppName);
    if (m_isApp) {
        m_process.start(m_AppName);
        emit running(true);
    }
    else if (m_startDetached)  {
        m_process.startDetached(m_AppName);
        emit running(false);
    }
    else {
        m_process.execute(m_AppName);
        emit running(true);;
    }
}
