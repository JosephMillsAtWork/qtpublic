#include "mangosshremoteprocess.h"

/*!
  \qmltype MangoSshRemoteProcess
  \inqmlmodule Mango.Ssh 0.1
  \ingroup Mango.Ssh
  \inherits Item
  \since 5.3
  This qml plugin implements an SSH channel for running a remote process.
    The process is started via the runCommand()
    member function. If the process needs a pseudo terminal, you can setone one via needsTerminal: true
    Note that this class does not support QIODevice's waitFor*() functions,

    \b{i.e. it has no synchronous mode}

    Example:

    \code
         MangoSshRemoteProcess{
            id: sshRemoteProcess
            // Set the ssh property's
            username: "user"
            hostName: "aFQDN"
            passwd: "a pass"
            timeout: 20

            //set up application that will run on the remote machine.
            needsTerminal: true
            command: "uname -a"

            // Check to see if the process is running on the Remote machine and get back the shells output
            onRunning:{
                // get the stdout back
                console.log(getStdout)

                // get the stderr back
                console.log(getStderr)
            }
        }
        Compoonent.onCompleded:{
            sshRemoteProcess.runCommand()
    }
    \endcode
 */

MangoSshRemoteProcess::MangoSshRemoteProcess(QObject *parent) :
    QObject(parent),
    m_needsTerminal(false),
    m_timeout(20),
    m_sshPort(22),
    m_authenticationType("password"),
    m_proxyType("none")
{

}

/*!
  \qmlproperty bool MangoSshRemoteProcess::needsTerminal
    bool property that is used to launch things with a terminal emulator,
*/
bool MangoSshRemoteProcess::needsTerminal()
{
    return m_needsTerminal;
}

void MangoSshRemoteProcess::setNeedsTerminal(bool &needsTerminal)
{
    m_needsTerminal = needsTerminal;
}
/*!
 \qmlproperty int MangoSshRemoteProcess::timeout
 sets the timeout for connection this is in seconds.
*/
int MangoSshRemoteProcess::timeout()
{
    return m_timeout;
}

void MangoSshRemoteProcess::setTimeout(int &timeout)
{
    m_timeout = timeout;
}

/*!
  \qmlproperty strinn MangoSshRemoteProcess::username
  This is the Username of the remote machine that you would like to upload to.
 */

QString MangoSshRemoteProcess::username()
{
    return m_username;
}

void MangoSshRemoteProcess::setUsername(const QString &username)
{
    m_username = username;
}

/*!
 \qmlproperty string MangoSshRemoteProcess::hostName
 This is the hostname of the remote machine that you would like to upload your files too.Used with the ssh connection to upload the file.
 */
QString MangoSshRemoteProcess::hostName()
{
    return m_hostName;
}

void MangoSshRemoteProcess::setHostName(const QString &hostName)
{
    m_hostName = hostName;

}
/*!
 \qmlproperty string MangoSshRemoteProcess::passwd
 The Password for the remote machine that you would like to upload the file to.
 */
QString MangoSshRemoteProcess::passwd()
{
    return m_passwd;
}

void MangoSshRemoteProcess::setPasswd(const QString &passwd)
{
    m_passwd = passwd;
}
/*!
  \qmlproperty int MangoSshRemoteProcess::sshPort
 This is used to set the port that ssh is listening on,  By default this is set to port 22
 */
int MangoSshRemoteProcess::sshPort()
{
    return m_sshPort;
}

void MangoSshRemoteProcess::setSshPort(int &sshPort)
{
    m_sshPort = sshPort;
}
/*!
 \qmlproperty string MangoSshRemoteProcess::command
  This is the command that you want to run after you are connected via ssh
 */
QString MangoSshRemoteProcess::command()
{
    return m_command;
}

void MangoSshRemoteProcess::setCommand(const QString &command)
{
    m_command = command;
}
/*!
  \qmlsignal MangoSshRemoteProcess::runCommand()
   sets up the connection and runs the command .
*/
void MangoSshRemoteProcess::runCommand()
{
    QSsh::SshConnectionParameters params;

    if (m_proxyType == "none")
    {
//        params.proxyType = QSsh::SshConnectionParameters::NoProxy;
        params.host = m_hostName;
        params.userName = m_username;
        params.password = m_passwd;
        params.timeout = m_timeout;
        if (m_authenticationType == "password")
        {
            params.authenticationType = QSsh::SshConnectionParameters::AuthenticationTypePassword;
        }else if (m_authenticationType == "key")
        {
            params.authenticationType = QSsh::SshConnectionParameters::AuthenticationTypePublicKey;
            params.privateKeyFile = m_privateKey;
        }
        params.port = m_sshPort;
    }
    else if (m_proxyType == "default ")
    {
//    params.proxyType = QSsh::SshConnectionParameters::DefaultProxy;
    params.host = m_hostName;
    params.userName = m_username;
    params.password = m_passwd;
    params.timeout = m_timeout;
    if (m_authenticationType == "password")
    {
        params.authenticationType = QSsh::SshConnectionParameters::AuthenticationTypePassword;
    }
    else if (m_authenticationType == "key")
    {
        params.authenticationType = QSsh::SshConnectionParameters::AuthenticationTypePublicKey;
        params.privateKeyFile = m_privateKey;
    }
    params.port = m_sshPort;

    }

    // TODO free this pointer!
    m_connection = new QSsh::SshConnection(params, this);

    connect(m_connection, SIGNAL(connected()), SLOT(onConnected()));
    connect(m_connection, SIGNAL(error(QSsh::SshError)), SLOT(onConnectionError(QSsh::SshError)));
//    connect(m_connection,Signal(cl))

    m_connection->connectToHost();
}

QString MangoSshRemoteProcess::getStderr()
{
    return m_stderr;
}

QString MangoSshRemoteProcess::getStdout()
{
    return m_stdout;
}

/*!
  \qmlproperty string MangoSshRemoteProcess::authenticationType
  \b{under heavey development}

    This is used to change the authenticationType from password (default) or key these are the only 2 options.
    if you change from password to keys you must set the publicKey,

    see also publicKey

 */
QString MangoSshRemoteProcess::authenticationType()
{
    return m_authenticationType;
}

void MangoSshRemoteProcess::setAuthenticationType(const QString &authenticationType)
{
    m_authenticationType = authenticationType;
}

QString MangoSshRemoteProcess::proxyType()
{
    return m_proxyType;
}

/*!
  \qmlproperty string MangoSshRemoteProcess::privateKey
  This is used to set the private key that one would like to use if there going to set the authenticationType to \b{key}
  by default authenticationType is set to \b{password} so this does not need to be set.  But if you are to use keys to login
  then one must set the private key that there going to useconds_t

  \b{see also} authenticationType

 */
QString MangoSshRemoteProcess::privateKey()
{
    return m_privateKey;

}

void MangoSshRemoteProcess::setPrivateKey(const QString &privateKey)
{
    m_privateKey = privateKey;
}

/*!
 \qmlproperty readonly MangoSshRemoteProcess::exit
 returns true if the ssh connection is over, else returns false

 see also kill() close()
 */
bool MangoSshRemoteProcess::exit()
{
    return m_exit;
}



void MangoSshRemoteProcess::onConnected()
{
    qDebug() << "SshRemoteProcess Connected: to " << m_hostName;
    emit running(true);
    emit closed(false);
    qDebug() << "SshRemoteProcess Running Commands...   \t " << m_command;

    QByteArray ba =  m_command.toLatin1();
      const QByteArray comman(ba);
      remoteProc = m_connection->createRemoteProcess(comman);

      if(remoteProc){
          connect(remoteProc.data(), SIGNAL(started()), SLOT(onChannelStarted()) );
          connect(remoteProc.data(), SIGNAL(readyReadStandardOutput()), SLOT(readyReadStandardOutput()));
          connect(remoteProc.data(), SIGNAL(closed(int)), SLOT(handleProcessFinished(int)));
          remoteProc->start();
      }
}

void MangoSshRemoteProcess::onConnectionError(QSsh::SshError)
{
    m_errorString =  m_connection->errorString();
    emit error(m_errorString);
    emit running(false);
    qDebug() << "SshRemoteProcess Connection error" << m_connection->errorString();
}

void MangoSshRemoteProcess::onChannelStarted(){
    qDebug() << "SshRemoteProcess Channel Started";
    emit running(true);
}


// get the standered output
void MangoSshRemoteProcess::readyReadStandardOutput()
{
    QString stderr = QString::fromLatin1(remoteProc->readAllStandardOutput());
    QString stdout = QString::fromLatin1(remoteProc->readAll());
    QString sterr = QString::fromLatin1(remoteProc->readAllStandardError());
    if (!stderr.isEmpty())
    {
        qDebug() <<  "SshRemoteProcess Remote Command output stderr: " << stderr;
        m_stderr = stderr.trimmed();
        emit running(false);
    }
    if (!stdout.isEmpty())
    {
        qDebug() << "SshRemoteProcess Remote Command output stdout : " << stdout;
        //m_stdout = "";
        m_stdout = stdout.trimmed();
        emit running(false);
    }
    if (!sterr.isEmpty())
    {
        qDebug() <<  "SshRemoteProcess Remote Command output sterr : " << sterr.trimmed();
        emit error(sterr.trimmed());
    }
    // I Should kill the pointer here.?.?.?
}

/*!
  \qmlsignal MangoSshRemoteProcess::close()
  This closes the process that is running but not the ssh connection

see also kill() exit
 */
void MangoSshRemoteProcess::close()
{
    remoteProc->close();
    emit running(false);
    emit closed(remoteProc->exitCode());
    m_exit = true;
}

/*!
 \qmlsignal MangoSshRemoteProcess::kill()
 This kills the process that is running then stops the ssh connection.

see also close() exit
*/
void MangoSshRemoteProcess::kill()
{
    remoteProc->close() ;
    m_connection->disconnectFromHost();
    emit running(false);
    emit closed(remoteProc->exitCode());
    m_exit = true ;
}


void MangoSshRemoteProcess::handleProcessFinished(int exitStatus)
{
//        qDebug() << "SSH This is the exit status:   "<< exitStatus;

    switch(exitStatus){
    // This is failed to start
    case 0:
        qDebug() << "SshRemoteProcess handleProcessFinished number"<< exitStatus << "also know as FailedToStart";
        break;
    // This is crash Like if a script is not working or the process is not yet don compleating because something is not right ?
    case 1:
        qDebug() << "SshRemoteProcess handleProcessFinished number "<< exitStatus << "also know as CrashExit ";
        kill();
        break;
    // This is normal
    case 2:
        qDebug() << "SshRemoteProcess handleProcessFinished number "<< exitStatus << " also know as NormalExit";
        kill();
        break;
    default:
        qDebug() << "SshRemoteProcess handleProcessFinished Impossible exit status.";
    }

    if (m_exitScore == exitStatus)
        return;
    m_exitScore = exitStatus;
    emit exitStatusChanged();
    setProcessExitStatus(exitStatus);
}
void MangoSshRemoteProcess::setProcessExitStatus(int exitStatus)
{

    switch(exitStatus)
    {
    case 0:
        m_exitStatus = FailedToStart;
        break;
    case 1:
        m_exitStatus = CrashExit;
        break;
    case 2:
        m_exitStatus = NormalExit;
        break;
    }
}

/*!
 * \qmlproperty MangoSshRemoteProcess::getProcessExitStatus
 Read only property that is used to get the last exit status from the Qprocess that is
 running in the Ssh connection.  This can be useful when combined with something like
 onExitStatusChanged

 Example:

 \code
    MangoSshRemoteProcess{
        id: sshRemoteProcessCopyFile
        // Set the ssh property's
        username: "UserName"
        hostName: "192.168.1.31"
        passwd: "Password"
        sshPort: 22
        timeout: 20
        command:"cp -r ~/Downloads ~/Downloads_bak"
        onExitStatusChanged: {
            if (getExitStatus === MangoSshRemoteProcess.NormalExit){
                console.log("[QML] sshRemoteProcessCopyFile normal exit")
            }
            else if (getExitStatus === MangoSshRemoteProcess.CrashExit){
                console.log("[QML] sshRemoteProcessCopyFile crash exit")
            }
            else if (getExitStatus === MangoSshRemoteProcess.FailedToStart){
                console.log("[QML] sshRemoteProcessCopyFile failed to start")
            }
            else {
                console.log("[QML] sshRemoteProcessCopyFile Impossible to understand")
            }
        }
    }


    see also:  onError() errorString
 \endcode
 */
MangoSshRemoteProcess::ExitStatus MangoSshRemoteProcess::getProcessExitStatus()
{
    return m_exitStatus;
}
