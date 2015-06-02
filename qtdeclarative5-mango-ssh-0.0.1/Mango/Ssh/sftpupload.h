#ifndef SFTPUPLOAD_H
#define SFTPUPLOAD_H
#include "QSsh/src/libs/ssh/sftpchannel.h"
#include "QSsh/src/libs/ssh/sshconnection.h"
#include <QFileInfo>
#include <QDebug>
#include <QObject>

class SftpUpload : public QObject
{
    Q_OBJECT
public:
    Q_PROPERTY(QString localFile READ localFile WRITE setLocalFile NOTIFY localFileChanged)
    Q_PROPERTY(QString destination READ destination WRITE setDestination NOTIFY destinationChanged)
    Q_PROPERTY(QString username READ username WRITE setUsername NOTIFY usernameChanged)
    Q_PROPERTY(QString hostName READ hostName WRITE setHostName NOTIFY hostNameChanged)
    Q_PROPERTY(QString passwd READ passwd WRITE setPasswd NOTIFY passwdChanged)
    Q_PROPERTY(int sshPort READ sshPort WRITE setSshPort NOTIFY sshPortChanged)
    Q_PROPERTY(int timeout READ timeout WRITE setTimeout)


    Q_INVOKABLE void upload();

    Q_ENUMS(SshError)

    enum SshError {
        SshNoError,
        SshSocketError,
        SshTimeoutError,
        SshProtocolError,
        SshHostKeyError,
        SshKeyFileError,
        SshAuthenticationError,
        SshClosedByServerError,
        SshInternalError
    };





    explicit SftpUpload(QObject *parent = 0);
    QString localFile();
    void setLocalFile(const QString &localFIle);

    QString destination();
    void setDestination(const QString &destination);

    QString username();
    void setUsername(const QString &username);

    QString hostName();
    void setHostName(const QString &hostName);


    QString passwd();
    void setPasswd(const QString &passwd);

    int sshPort();
    void setSshPort(int &sshPort);

    int timeout();
    void setTimeout(int &timeout);
signals:
  void localFileChanged();
  void destinationChanged();
  void usernameChanged();
  void hostNameChanged();
  void passwdChanged();
  void sshPortChanged();
  void done();
  void error();
private slots:
    void onConnected();
    void onConnectionError(QSsh::SshError);
    void onChannelInitialized();
    void onChannelError(const QString &err);
    void onOpfinished(QSsh::SftpJobId job, const QString & error = QString());

private:
    QString m_localFilename;
    QString m_remoteFilename;
    //for setting qml
    QString m_localfile;
    QString m_destination;
    QString m_username;
    QString m_hostName;
    QString m_passwd;
    int m_sshPort;
    int m_timeout;

    QSsh::SftpChannel::Ptr m_channel;
    QSsh::SshConnection *m_connection;

    void parseDestination(const QString &dest);
};

#endif // SFTPUPLOAD_H


//#ifndef SFTPUPLOAD_H
//#define SFTPUPLOAD_H
//#include "QSsh/src/libs/ssh/sftpchannel.h"
//#include "QSsh/src/libs/ssh/sshconnection.h"
//#include <QFileInfo>
//#include <QDebug>
//#include <QObject>

//class SftpUpload : public QObject
//{
//    Q_OBJECT
//public:
//    Q_PROPERTY(QString localFile READ localFile WRITE setLocalFile NOTIFY localFileChanged)
//    Q_PROPERTY(QString destination READ destination WRITE setDestination NOTIFY destinationChanged)
//    Q_PROPERTY(QString username READ username WRITE setUsername NOTIFY usernameChanged)
//    Q_PROPERTY(QString hostName READ hostName WRITE setHostName NOTIFY hostNameChanged)
//    Q_PROPERTY(QString passwd READ passwd WRITE setPasswd NOTIFY passwdChanged)
//    Q_PROPERTY(int sshPort READ sshPort WRITE setSshPort NOTIFY sshPortChanged)
//    Q_PROPERTY(int timeout READ timeout WRITE setTimeout)


//    Q_INVOKABLE void upload();

//    Q_ENUMS(SshError)

//    enum SshError {
//        SshNoError,
//        SshSocketError,
//        SshTimeoutError,
//        SshProtocolError,
//        SshHostKeyError,
//        SshKeyFileError,
//        SshAuthenticationError,
//        SshClosedByServerError,
//        SshInternalError
//    };


//    explicit SftpUpload(QObject *parent = 0);
//    QString localFile();
//    void setLocalFile(const QString &localFIle);

//    QString destination();
//    void setDestination(const QString &destination);

//    QString username();
//    void setUsername(const QString &username);

//    QString hostName();
//    void setHostName(const QString &hostName);


//    QString passwd();
//    void setPasswd(const QString &passwd);

//    int sshPort();
//    void setSshPort(int &sshPort);

//    int timeout();
//    void setTimeout(int &timeout);
//signals:
//  void localFileChanged();
//  void destinationChanged();
//  void usernameChanged();
//  void hostNameChanged();
//  void passwdChanged();
//  void sshPortChanged();
//  void done();
//private slots:
//    void onConnected();
//    void onConnectionError(QSsh::SshError);
//    void onChannelInitialized();
//    void onChannelError(const QString &err);
//    void onOpfinished(QSsh::SftpJobId job, const QString & error = QString());

//private:
//    QString m_localFilename;
//    QString m_remoteFilename;
//    //for setting qml
//    QString m_localfile;
//    QString m_destination;
//    QString m_username;
//    QString m_hostName;
//    QString m_passwd;
//    int m_sshPort;
//    int m_timeout;

//    QSsh::SftpChannel::Ptr m_channel;
//    QSsh::SshConnection *m_connection;

//    void parseDestination(const QString &dest);
//};

//#endif // SFTPUPLOAD_H
