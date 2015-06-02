/*
 * Joseph Mills
*/
#ifndef MANGOSSL_H
#define MANGOSSL_H

#include <QtCore>
#include <QSsl>

class MangoSsl : public QObject
{
    Q_OBJECT
    Q_ENUMS(KeyType
            EncodingFormat
            KeyAlgorithm
            AlternativeNameEntryType
            SslProtocol
            SslOption)

public:
    explicit MangoSsl(QObject *parent = 0);
    enum KeyType {
        PrivateKey,
        PublicKey
    };

    enum EncodingFormat {
        Pem,
        Der
    };

    enum KeyAlgorithm {
        Opaque,
        Rsa,
        Dsa
    };

    enum AlternativeNameEntryType {
        EmailEntry,
        DnsEntry
    };

    enum SslProtocol {
        SslV3,
        SslV2,
        TlsV1_0,
        TlsV1_1,
        TlsV1_2,
        AnyProtocol,
        TlsV1SslV3,
        SecureProtocols,
        UnknownProtocol = -1
    };

    enum SslOption {
        SslOptionDisableEmptyFragments = 0x01,
        SslOptionDisableSessionTickets = 0x02,
        SslOptionDisableCompression = 0x04,
        SslOptionDisableServerNameIndication = 0x08,
        SslOptionDisableLegacyRenegotiation = 0x10,
        SslOptionDisableSessionSharing = 0x20,
        SslOptionDisableSessionPersistence = 0x40
    };
};

#endif // MANGOSSL_H
