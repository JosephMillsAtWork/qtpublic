/*
 * Copyright (C) 2012-2013 Joseph Mills.
 *
 */
#ifndef APPLICATION_H
#define APPLICTION_H
#include <QObject>
#include <QProcess>
#include <QString>
#include <QStringList>
#include <QDebug>
#include <QList>
class QProcess;
class Application : public QObject
{
    Q_OBJECT
    Q_PROPERTY( QString appName READ appName WRITE setAppName)
    Q_PROPERTY( QString arguments READ arguments WRITE setArguments )
    Q_PROPERTY(bool  isApp READ isApp WRITE setIsApp NOTIFY isAppChanged)
    Q_PROPERTY(bool  startDetached  READ startDetached WRITE setStartDetached)
    Q_PROPERTY(bool running READ running)
    Q_PROPERTY(QString getOutPut READ getOutPut NOTIFY getOutPutChanged)
    Q_PROPERTY(ProcessChannelMode processMode READ processMode WRITE setProcessMode NOTIFY processModeChanged)


    Q_ENUMS(ProcessChannelMode)

public:
    explicit Application(QObject *parent = 0);


    enum InputChannelMode{
        ManagedInputChannel,
        ForwardedInputChannel
    };
    enum ProcessChannel{
        StandardOutput,
        StandardError
    };
    enum	ProcessError{
        FailedToStart,
        Crashed,
        Timedout,
        WriteError,
        ReadError,
        UnknownError
    };
    enum ProcessState{
        NotRunning,
        Starting,
        Running
    };
    enum ProcessChannelMode{
        SeparateChannels,
        MergedChannels,
        ForwardedChannels,
        ForwardedErrorChannel,
        ForwardedOutputChannel
    };
    QString getOutPut()const;
    QString appName() const;
    void setAppName(const QString &appName);
    QString arguments() const;
    void setArguments(const QString &arguments);
    ProcessChannelMode processMode() const{
        return m_processMode ;
    }
    void setProcessMode(ProcessChannelMode &processMode){
        if (m_processMode == processMode)
            return ;
        m_processMode = processMode;

        if (m_processMode == Application::SeparateChannels)
        {
            m_process.setProcessChannelMode(QProcess::SeparateChannels);
            emit processModeChanged(Application::SeparateChannels);
        }
        else if (m_processMode == Application::MergedChannels)
        {
            m_process.setProcessChannelMode(QProcess::MergedChannels);
            emit processModeChanged(Application::MergedChannels);

        }
        else if (m_processMode == Application::ForwardedChannels)
        {
            m_process.setProcessChannelMode(QProcess::ForwardedChannels);
            emit processModeChanged(Application::ForwardedChannels);

        }
        else if (m_processMode == Application::ForwardedErrorChannel)
        {
            m_process.setProcessChannelMode(QProcess::ForwardedErrorChannel);
            emit processModeChanged(Application::ForwardedErrorChannel);

        }
        else if (m_processMode == Application::ForwardedOutputChannel)
        {
            m_process.setProcessChannelMode(QProcess::ForwardedOutputChannel);
            emit processModeChanged(Application::ForwardedOutputChannel);

        }
//        m_process.setProcessChannelMode(m_processMode);
        emit processModeChanged(processMode);
    }
    bool isApp()const;

    void setIsApp(bool &isApp);
    bool startDetached();
    void setStartDetached(bool startDetached);
    bool running();
    void clear() { m_pendingProcesses.clear(); }
    QProcess::ProcessState state() { return m_process.state(); }

signals:
    void message(QString);
    void error(QString);
    void finished(QString,int);
    void started(QString);
    void isAppChanged();
    void running(bool);
    void getOutPutChanged();
    void processModeChanged(Application::ProcessChannelMode);
public slots:
    void stop();
    void start();
protected slots:
    void processStarted();
    void processReadyRead();
    void processFinished(int code);
    void processError(QProcess::ProcessError error);
    void processCmdQueue();

private:
    QProcess m_process;
    QString m_AppName;
    QString m_Arguments;
    QString m_Out;
    QList<QStringList> m_pendingProcesses;
    bool m_isApp;
    bool m_startDetached;
    bool m_running ;
    QString m_getOutPut;
    ProcessChannelMode m_processMode;
protected:
    void close();
    void kill();
};
#endif //APPLICATION_H
