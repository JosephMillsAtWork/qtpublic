#ifndef SOUNDRECORDER
#define SOUNDRECORDER_H
#include <QtQml/qqmlparserstatus.h>
#include <QtQml/qqml.h>
#include <QAudioRecorder>
#include <QMediaRecorder>
#include <QMultimedia>
#include <QUrl>

class SoundRecorder : public QObject
{
    Q_OBJECT
    Q_PROPERTY  (QString path READ path WRITE setPath NOTIFY pathChanged)
    Q_PROPERTY  (QString codec READ codec  WRITE setCodec NOTIFY codecChanged)
    Q_PROPERTY  (int quality READ quality WRITE setQuality NOTIFY qualityChanged)
    Q_PROPERTY  (qreal volume READ volume WRITE setVolume NOTIFY volumeChanged)
    Q_PROPERTY  (qint64  duration READ duration NOTIFY durationChanged)
    Q_PROPERTY  (Error error READ error NOTIFY errorChanged)
    Q_PROPERTY  (QString errorString READ errorString  NOTIFY errorChanged)
    Q_PROPERTY  (State state READ state NOTIFY stateChanged)
    Q_ENUMS(Error)
    Q_ENUMS(State)

public:
    enum Error
    {
         NoError = QMediaRecorder::NoError,
         ResourceError = QMediaRecorder::ResourceError,
         FormatError = QMediaRecorder::FormatError,
         OutOfSpaceError = QMediaRecorder::OutOfSpaceError
    };

    enum State
    {
        StoppedState = QAudioRecorder::StoppedState,
        RecordingState = QAudioRecorder::RecordingState,
        PausedState = QAudioRecorder::PausedState
    };

    SoundRecorder(QObject *parent = 0);
    ~SoundRecorder();

    QString path() const;
    void setPath(const QString &path);

    QString codec() const;
    void setCodec(const QString &codec);

    int quality() const;
    void setQuality(const int &quality);

    qreal volume() const;
    void setVolume(const qreal &volume);

    qint64 duration() const;

    Error error() const;
    QString errorString() const;

    State state() const;

    Q_INVOKABLE QStringList getSupportedCodecs();
    Q_INVOKABLE QString getFilePath();

public Q_SLOTS:
    void start();
    void stop();
    void pause();
    void resume();

Q_SIGNALS:
    void pathChanged();

    void codecChanged();
    void qualityChanged();
    void volumeChanged();

    void durationChanged();

    void stateChanged();
    void recording();
    void stopped();
    void paused();
    void resumed();

    void errorChanged();

private Q_SLOTS:
    void _q_stateChanged();
    void _q_error();
    void _q_durationChanged();

private:
    QAudioRecorder *audioRecorder;
    QString cPath;

    QString m_path;
    QString m_codec;
    int m_quality;
    qreal m_volume;

    qint64 m_duration;

    QMediaRecorder::State m_state;

    QMediaRecorder::Error m_error;
    QString m_errorString;

    QString getContainerFromCodec(QString codec);
    QString getExtensionFromCodec(QString codec);

};
#endif //SoundRecorder_H


