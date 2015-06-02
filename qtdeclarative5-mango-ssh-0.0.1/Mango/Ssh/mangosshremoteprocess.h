#ifndef MANGOSSHREMOTEPROCESS_H
#define MANGOSSHREMOTEPROCESS_H

#include <QObject>
#include <QByteArray>
#include <QProcess>
#include <QObject>
#include <QSharedPointer>

#include "QSsh/src/libs/ssh/sshremoteprocess.h"
#include "QSsh/src/libs/ssh/sshconnection.h"
#include "QSsh/src/libs/ssh/sshconnection_p.h"

//SshConnectionParameters
class MangoSshRemoteProcess : public QObject
{
    Q_OBJECT

public:
    explicit MangoSshRemoteProcess(QObject *parent = 0);
    Q_PROPERTY(QString username READ username WRITE setUsername NOTIFY usernameChanged)
    Q_PROPERTY(QString hostName READ hostName WRITE setHostName NOTIFY hostNameChanged)
    Q_PROPERTY(QString passwd READ passwd WRITE setPasswd NOTIFY passwdChanged)
    Q_PROPERTY(int sshPort READ sshPort WRITE setSshPort NOTIFY sshPortChanged)
    Q_PROPERTY(bool needsTerminal READ needsTerminal WRITE setNeedsTerminal NOTIFY needsTerminalChanged)
    Q_PROPERTY(QString command READ command WRITE setCommand NOTIFY commandChanged)
    Q_PROPERTY(QString authenticationType READ authenticationType WRITE setAuthenticationType NOTIFY authenticationTypeChanged)
    Q_PROPERTY(int timeout READ timeout WRITE setTimeout NOTIFY timeoutChanged)
    Q_PROPERTY(QString getStderr READ getStderr)
    Q_PROPERTY(QString getStdout READ getStdout)
    Q_PROPERTY(QString  proxyType READ proxyType)
    Q_PROPERTY(QString privateKey READ privateKey WRITE setPrivateKey)
    Q_PROPERTY(QString errorString READ errorString)
    Q_PROPERTY(bool exit READ exit)
    //Q_PROPERTY(State state READ state NOTIFY stateChanged)

    Q_PROPERTY(enum ExitStatus getProcessExitStatus READ getProcessExitStatus)

    Q_ENUMS(ExitStatus)

    enum State{
        Connected,
        Unconnected,
        Connecting,
        UserAuthServiceRequested,
        UserAuthRequested
    };

    enum ProxyType {
        DefaultProxy,
        NoProxy
    };
    enum AuthenticationType {
        AuthenticationByPassword,
        AuthenticationByKey
    };

    enum ExitStatus {
        FailedToStart,
        CrashExit,
        NormalExit
    };
    enum Signal {
        AbrtSignal,
        AlrmSignal,
        FpeSignal,
        HupSignal,
        IllSignal,
        IntSignal,
        KillSignal,
        PipeSignal,
        QuitSignal,
        SegvSignal,
        TermSignal,
        Usr1Signal,
        Usr2Signal,
        NoSignal
    };


    Q_INVOKABLE void close();
    Q_INVOKABLE void kill();




    // qml property set up
    QString username();
    void setUsername(const QString &username);

    QString hostName();
    void setHostName(const QString &hostName);

    QString passwd();
    void setPasswd(const QString &passwd);

    int sshPort();
    void setSshPort(int &sshPort);

    QString command();
    void setCommand(const QString &command);

    bool needsTerminal();
    void setNeedsTerminal(bool &needsTerminal);

    int timeout();
    void setTimeout(int &timeout);
    Q_INVOKABLE void runCommand();

    QString getStderr();
    QString getStdout();

    QString authenticationType();
    void setAuthenticationType(const QString &authenticationType);

    QString proxyType();

    QString privateKey();
    void setPrivateKey(const QString &privateKey);
    QString errorString(){return m_errorString; }
    bool exit();

    void setProcessExitStatus(int exitStatus);
    ExitStatus getProcessExitStatus();

//    void setSshExitStatus(int exitStatus);
//    ExitStatus getSshExitStatus();


   // MangoSshRemoteProcess::State state() const;

signals:
    void finished(QString,int);
    void started();
    void readyReadStandardError();
    void closed(int);
    void exitStatusChanged();
    void signalChanged();
    void needsTerminalChanged();
    void usernameChanged();
    void hostNameChanged();
    void passwdChanged();
    void sshPortChanged();
    void commandChanged();
    void timeoutChanged();
    void authenticationTypeChanged();
    void running(bool);
    void error(QString);
    //void stateChanged();

private slots:
    void onConnected();
    void onConnectionError(QSsh::SshError);
    void onChannelError(const QString &err);
    void onChannelStarted();
    void handleProcessFinished(int exitStatus);
    void readyReadStandardOutput();
    void processFinished(int code);

private:
    bool m_needsTerminal;
    int m_timeout;
    QString m_username;
    QString m_hostName;
    QString m_passwd;
    int m_sshPort;
    QString m_authenticationType;
    QString m_command;
    QString m_stderr;
    QString m_stdout;
    QString m_proxyType;
    QString m_privateKey;
    QString m_errorString;
    bool m_exit;
    int m_exitScore;
    ExitStatus m_exitStatus;
    QSsh::SshRemoteProcess::Ptr remoteProc;
    QSsh::SshConnection *m_connection;
};
//}// namespace QSsh
#endif // MANGOSSHREMOTEPROCESS_H
