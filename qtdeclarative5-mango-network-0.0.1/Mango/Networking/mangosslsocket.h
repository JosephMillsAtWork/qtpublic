/*
 * Joseph Mills
 */

#ifndef MANGOSSLSOCKET_H
#define MANGOSSLSOCKET_H

#include "mangossl.h"

#include <QtNetwork>
#include <QSslSocket>

class MangoSslSocket : public QSslSocket
{
    Q_OBJECT
    Q_ENUMS( SslMode PeerVerifyMode
             OpenMode NetworkLayerProtocol
             SocketState
             QAbstractSocket::SocketOption
             ServicePorts
             )

 public:

    enum ServicePorts {
        NOT_SET = 0,
        HTTPS = 443,
        HTTP = 80
    };

    Q_INVOKABLE void resume() { QSslSocket::resume(); }
    Q_INVOKABLE void connectToHostEncrypted(const QString &hostName, quint16 port, OpenMode mode = ReadWrite, NetworkLayerProtocol protocol = AnyIPProtocol) {
        QSslSocket::connectToHostEncrypted(hostName,port, mode, protocol);
    }

    Q_INVOKABLE void connectToHostEncrypted(const QString &hostName, quint16 port, const QString &sslPeerName, OpenMode mode = ReadWrite, NetworkLayerProtocol protocol = AnyIPProtocol) {
        QSslSocket::connectToHostEncrypted(hostName,port,sslPeerName,mode,protocol);
    }
    Q_INVOKABLE bool setSocketDescriptor(qintptr socketDescriptor, SocketState state = ConnectedState,
                             OpenMode openMode = ReadWrite) {
       return QSslSocket::setSocketDescriptor(socketDescriptor,state,openMode);
    }

    Q_INVOKABLE void connectToHost(const QString &hostName, quint16 port, OpenMode openMode = ReadWrite, NetworkLayerProtocol protocol = AnyIPProtocol) {
        QSslSocket::connectToHost(hostName,port,openMode,protocol);
    }

    Q_INVOKABLE void disconnectFromHost() { QSslSocket::disconnectFromHost(); }

    Q_INVOKABLE virtual void setSocketOption(QAbstractSocket::SocketOption option, const QVariant &value) {
        QSslSocket::setSocketOption(option,value);
    }

    Q_INVOKABLE virtual QVariant socketOption(QAbstractSocket::SocketOption option) {
        return QSslSocket::socketOption(option);
    }

    Q_INVOKABLE SslMode mode() const { return QSslSocket::mode(); }
    Q_INVOKABLE bool isEncrypted() const { return QSslSocket::isEncrypted(); }

    Q_INVOKABLE MangoSsl::SslProtocol protocol() const { return (MangoSsl::SslProtocol)QSslSocket::protocol(); }
    Q_INVOKABLE void setProtocol(QSsl::SslProtocol protocol) { QSslSocket::setProtocol(protocol); }

    Q_INVOKABLE PeerVerifyMode peerVerifyMode() const { return QSslSocket::peerVerifyMode(); }
    Q_INVOKABLE void setPeerVerifyMode(PeerVerifyMode mode) { QSslSocket::setPeerVerifyMode(mode); }

    Q_INVOKABLE int peerVerifyDepth() const { return QSslSocket::peerVerifyDepth(); }
    Q_INVOKABLE void setPeerVerifyDepth(int depth) { QSslSocket::setPeerVerifyDepth(depth); }

    Q_INVOKABLE QString peerVerifyName() const { return QSslSocket::peerVerifyName(); }
    Q_INVOKABLE void setPeerVerifyName(const QString &hostName) { QSslSocket::setPeerVerifyName(hostName); }

    Q_INVOKABLE qint64 bytesAvailable() const { return QSslSocket::bytesAvailable(); }
    Q_INVOKABLE qint64 bytesToWrite() const { return QSslSocket::bytesToWrite(); }
    Q_INVOKABLE bool canReadLine() const { return QSslSocket::canReadLine(); }
    Q_INVOKABLE void close() { QSslSocket::close(); }
    Q_INVOKABLE bool atEnd() const { return QSslSocket::atEnd(); }
    Q_INVOKABLE bool flush() { return QSslSocket::flush(); }
    Q_INVOKABLE void abort() { QSslSocket::abort(); }

    Q_INVOKABLE void setReadBufferSize(qint64 size) { QSslSocket::setReadBufferSize(size); }

    Q_INVOKABLE qint64 encryptedBytesAvailable() const { return QSslSocket::encryptedBytesAvailable(); }
    Q_INVOKABLE qint64 encryptedBytesToWrite() const { return QSslSocket::encryptedBytesToWrite(); }

    Q_INVOKABLE QSslConfiguration sslConfiguration() const { return QSslSocket::sslConfiguration(); }
    Q_INVOKABLE void setSslConfiguration(const QSslConfiguration &config) { QSslSocket::setSslConfiguration(config); }

    Q_INVOKABLE void setLocalCertificateChain(const QList<QSslCertificate> &localChain) { QSslSocket::setLocalCertificateChain(localChain); }
    Q_INVOKABLE QList<QSslCertificate> localCertificateChain() const { return QSslSocket::localCertificateChain(); }

    Q_INVOKABLE void setLocalCertificate(const QSslCertificate &certificate) { QSslSocket::setLocalCertificate(certificate); }
    Q_INVOKABLE void setLocalCertificate(const QString &fileName, QSsl::EncodingFormat format = QSsl::Pem) { QSslSocket::setLocalCertificate(fileName,format); }
    Q_INVOKABLE QSslCertificate localCertificate() const { return  QSslSocket::localCertificate(); }
    Q_INVOKABLE QSslCertificate peerCertificate() const { return QSslSocket::peerCertificate(); }
    Q_INVOKABLE QList<QSslCertificate> peerCertificateChain() const { return QSslSocket::peerCertificateChain(); }
    Q_INVOKABLE QSslCipher sessionCipher() const { return QSslSocket::sessionCipher(); }

    Q_INVOKABLE void setPrivateKey(const QSslKey &key) { QSslSocket::setPrivateKey(key); }
    Q_INVOKABLE void setPrivateKey(const QString &fileName, QSsl::KeyAlgorithm algorithm = QSsl::Rsa,
                       QSsl::EncodingFormat format = QSsl::Pem,
                       const QByteArray &passPhrase = QByteArray()) { QSslSocket::setPrivateKey(fileName,algorithm,format,passPhrase);
    }
    Q_INVOKABLE QSslKey privateKey() const {
        return QSslSocket::privateKey();
    }

    Q_INVOKABLE QList<QSslCipher> ciphers() const {
        return QSslSocket::ciphers();
    }
    Q_INVOKABLE void setCiphers(const QList<QSslCipher> &ciphers) {
        QSslSocket::setCiphers(ciphers);
    }

    Q_INVOKABLE void setCiphers(const QString &ciphers) {
        QSslSocket::setCiphers(ciphers);
    }

    Q_INVOKABLE static void setDefaultCiphers(const QList<QSslCipher> &ciphers) {
        QSslSocket::setDefaultCiphers(ciphers);
    }

    Q_INVOKABLE static QList<QSslCipher> defaultCiphers() {
        return QSslSocket::defaultCiphers();
    }

    Q_INVOKABLE static QList<QSslCipher> supportedCiphers() {
        return QSslSocket::supportedCiphers();
    }

    Q_INVOKABLE bool addCaCertificates(const QString &path, QSsl::EncodingFormat format = QSsl::Pem,
                           QRegExp::PatternSyntax syntax = QRegExp::FixedString) {
        return QSslSocket::addCaCertificates(path,format,syntax);
    }

    Q_INVOKABLE void addCaCertificate(const QSslCertificate &certificate) {
        QSslSocket::addCaCertificate(certificate);
    }

    Q_INVOKABLE void addCaCertificates(const QList<QSslCertificate> &certificates) {
        QSslSocket::addCaCertificates(certificates);
    }

    Q_INVOKABLE void setCaCertificates(const QList<QSslCertificate> &certificates) {
        QSslSocket::setCaCertificates(certificates);
    }

    Q_INVOKABLE QList<QSslCertificate> caCertificates() const {
        return QSslSocket::caCertificates();
    }
    Q_INVOKABLE static bool addDefaultCaCertificates(const QString &path, QSsl::EncodingFormat format = QSsl::Pem,
                                         QRegExp::PatternSyntax syntax = QRegExp::FixedString) {
        return QSslSocket::addDefaultCaCertificates(path,format,syntax);
    }

    Q_INVOKABLE static void addDefaultCaCertificate(const QSslCertificate &certificate) {
        QSslSocket::addDefaultCaCertificate(certificate);
    }

    Q_INVOKABLE static void addDefaultCaCertificates(const QList<QSslCertificate> &certificates) {
        QSslSocket::addDefaultCaCertificates(certificates);
    }

    Q_INVOKABLE static void setDefaultCaCertificates(const QList<QSslCertificate> &certificates) {
        QSslSocket::setDefaultCaCertificates(certificates);
    }

    Q_INVOKABLE static QList<QSslCertificate> defaultCaCertificates() {
        return QSslSocket::defaultCaCertificates();
    }

    Q_INVOKABLE static QList<QSslCertificate> systemCaCertificates() {
        return QSslSocket::systemCaCertificates();
    }

    Q_INVOKABLE bool waitForConnected(int msecs = 30000) { return QSslSocket::waitForConnected(msecs); }
    Q_INVOKABLE bool waitForEncrypted(int msecs = 30000) { return QSslSocket::waitForEncrypted(msecs); }
    Q_INVOKABLE bool waitForReadyRead(int msecs = 30000) { return QSslSocket::waitForReadyRead(msecs); }
    Q_INVOKABLE bool waitForBytesWritten(int msecs = 30000) { return QSslSocket::waitForBytesWritten(msecs); }
    Q_INVOKABLE bool waitForDisconnected(int msecs = 30000) { return QSslSocket::waitForDisconnected(msecs); }

    Q_INVOKABLE QList<QSslError> sslErrors() const { return QSslSocket::sslErrors(); }

    Q_INVOKABLE static bool supportsSsl() { return QSslSocket::supportsSsl(); }
    Q_INVOKABLE static long sslLibraryVersionNumber() { return QSslSocket::sslLibraryVersionNumber(); }
    Q_INVOKABLE static QString sslLibraryVersionString() { return QSslSocket::sslLibraryVersionString(); }

    Q_INVOKABLE void ignoreSslErrors(const QList<QSslError> &errors) { QSslSocket::ignoreSslErrors(errors); }


    Q_INVOKABLE qint64 read(char *data, qint64 maxlen) { return QSslSocket::read(data,maxlen); }
    Q_INVOKABLE QByteArray read(qint64 maxlen) { return QSslSocket::read(maxlen); }
    Q_INVOKABLE QByteArray readAll() { return QSslSocket::readAll(); }
    Q_INVOKABLE qint64 readLine(char *data, qint64 maxlen) { return QSslSocket::readLine(data,maxlen); }
    Q_INVOKABLE QByteArray readLine(qint64 maxlen = 0) { return QSslSocket::readLine(maxlen); }

    Q_INVOKABLE inline qint64 write(const QByteArray &data)
    { return QSslSocket::write(data.constData(), data.size()); }

    Q_INVOKABLE QString errorString() const { return QSslSocket::errorString(); }

    Q_INVOKABLE SocketType socketType() const { return QSslSocket::socketType(); }
    Q_INVOKABLE SocketState state() const { return QSslSocket::state(); }
    Q_INVOKABLE SocketError error() const { return QSslSocket::error(); }


};

#endif // MANGOSSLSOCKET_H
