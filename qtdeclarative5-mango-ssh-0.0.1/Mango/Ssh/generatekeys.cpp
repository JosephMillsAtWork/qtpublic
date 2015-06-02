#include "generatekeys.h"

/*!
  \qmltype GenerateKeys
  \inqmlmodule Mango.Ssh 0.1
  \ingroup Mango.Ssh
  \inherits Item
  \since 5.3

  This Qml Plugin is used to generate gpg keys that can be used to authentacate with remote machines with out a password,

  Example:

  \code

  TextField{id: pass ; onTextChanged: }
  Button{onClicked:{genKey.password = pass.text; genKeys.generateKeys()(}}
    GenerateKeys{
        id: genKeys
        keyType: GenerateKeys.Rsa
        format: GenerateKeys.OpenSsl
        encryptionMode: GenerateKeys.DoNotOfferEncryption
        keySize: 2048
    }


  \code

*/
GenerateKeys::GenerateKeys(QObject *parent) :
    QObject(parent),
    m_keyType(Rsa),
    m_format()
{
}

QString GenerateKeys::getPassword() const
{
    return m_password;
}
void GenerateKeys::setPassword(const QString &password)
{
    m_password = password;
}



bool GenerateKeys::generateKeys()
{
    try {
        Botan::AutoSeeded_RNG rng;
        KeyPtr key;
        if (m_keyType == Rsa)
            key = KeyPtr(new Botan::RSA_PrivateKey(rng, m_keySize));
        else
            key = KeyPtr(new Botan::DSA_PrivateKey(rng, Botan::DL_Group(rng, Botan::DL_Group::DSA_Kosherizer, m_keySize)));
        switch (m_format) {
        case Pkcs8:
            generatePkcs8KeyStrings(key, rng);
            break;
        case OpenSsl:
            generateOpenSslKeyStrings(key);
            break;
        case Mixed:
        default:
            generatePkcs8KeyString(key, true, rng);
            generateOpenSslPublicKeyString(key);
        }
        return true;
    } catch (Botan::Exception &e) {
        m_error = tr("Error generating key: %1").arg(QString::fromLatin1(e.what()));
        return false;
    }
}





void GenerateKeys::generatePkcs8KeyStrings(const KeyPtr &key, Botan::RandomNumberGenerator &rng)
{
    generatePkcs8KeyString(key, false, rng);
    generatePkcs8KeyString(key, true, rng);
}

void GenerateKeys::generatePkcs8KeyString(const KeyPtr &key, bool privateKey,
    Botan::RandomNumberGenerator &rng)
{
    Botan::Pipe pipe;
    pipe.start_msg();
    QByteArray *keyData;
    if (privateKey) {
        QString password;
        if (m_encryptionMode == DoOfferEncryption)
            password = getPassword();
        if (!password.isEmpty())
            pipe.write(Botan::PKCS8::PEM_encode(*key, rng, password.toLocal8Bit().data()));
        else
            pipe.write(Botan::PKCS8::PEM_encode(*key));
        keyData = &m_privateKey;
    } else {
        pipe.write(Botan::X509::PEM_encode(*key));
        keyData = &m_publicKey;
    }
    pipe.end_msg();
    keyData->resize(pipe.remaining(pipe.message_count() - 1));
    pipe.read(QSsh::Internal::convertByteArray(*keyData), keyData->size(),
        pipe.message_count() - 1);
}

void GenerateKeys::generateOpenSslKeyStrings(const KeyPtr &key)
{
    generateOpenSslPublicKeyString(key);
    generateOpenSslPrivateKeyString(key);
}

void GenerateKeys::generateOpenSslPublicKeyString(const KeyPtr &key)
{
    QList<Botan::BigInt> params;
    QByteArray keyId;
    if (m_keyType == Rsa) {
        const QSharedPointer<Botan::RSA_PrivateKey> rsaKey = key.dynamicCast<Botan::RSA_PrivateKey>();
        params << rsaKey->get_e() << rsaKey->get_n();
        keyId = QSsh::Internal::SshCapabilities::PubKeyRsa;
    } else {
        const QSharedPointer<Botan::DSA_PrivateKey> dsaKey = key.dynamicCast<Botan::DSA_PrivateKey>();
        params << dsaKey->group_p() << dsaKey->group_q() << dsaKey->group_g() << dsaKey->get_y();
        keyId = QSsh::Internal::SshCapabilities::PubKeyDss;
    }

    QByteArray publicKeyBlob = QSsh::Internal::AbstractSshPacket::encodeString(keyId);
    foreach (const Botan::BigInt &b, params)
        publicKeyBlob += QSsh::Internal::AbstractSshPacket::encodeMpInt(b);
    publicKeyBlob = publicKeyBlob.toBase64();
    const QByteArray id = "MangoAutomation/"
        + QDateTime::currentDateTime().toString(Qt::ISODate).toUtf8();
    m_publicKey = keyId + ' ' + publicKeyBlob + ' ' + id;
}

void GenerateKeys::generateOpenSslPrivateKeyString(const KeyPtr &key)
{
    QList<Botan::BigInt> params;
    QByteArray keyId;
    const char *label;
    if (m_keyType == Rsa) {
        const QSharedPointer<Botan::RSA_PrivateKey> rsaKey
            = key.dynamicCast<Botan::RSA_PrivateKey>();
        params << rsaKey->get_n() << rsaKey->get_e() << rsaKey->get_d() << rsaKey->get_p()
            << rsaKey->get_q();
        keyId = QSsh::Internal::SshCapabilities::PubKeyRsa;
        label = "RSA PRIVATE KEY";
    } else {
        const QSharedPointer<Botan::DSA_PrivateKey> dsaKey = key.dynamicCast<Botan::DSA_PrivateKey>();
        params << dsaKey->group_p() << dsaKey->group_q() << dsaKey->group_g() << dsaKey->get_y()
            << dsaKey->get_x();
        keyId = QSsh::Internal::SshCapabilities::PubKeyDss;
        label = "DSA PRIVATE KEY";
    }

    Botan::DER_Encoder encoder;
    encoder.start_cons(Botan::SEQUENCE).encode(size_t(0));
    foreach (const Botan::BigInt &b, params)
        encoder.encode(b);
    encoder.end_cons();
    m_privateKey = QByteArray(Botan::PEM_Code::encode (encoder.get_contents(), label).c_str());
}



