#ifndef OAUTH2_H
#define OAUTH2_H

#include <QString>
#include <QObject>

class QNetworkAccessManager;
class QNetworkReply;

class OAuth2 : public QObject
{
    Q_OBJECT
    Q_PROPERTY( QString clientSecert READ clientSecert WRITE setClientSecert  )
    Q_PROPERTY( QString clientId READ clientId WRITE setClientId )
    Q_PROPERTY( QString redirectURI READ redirectURI WRITE setRedirectURI  )
    Q_PROPERTY( QString scopes READ scopes WRITE  setScopes  )
    Q_PROPERTY( QString endPoint READ endPoint WRITE  setEndPoint  )

    Q_PROPERTY(QString  getaccessToken READ getaccessToken)
    Q_PROPERTY(QString getTokenType READ getTokenType)
    Q_PROPERTY(double getExperationTime  READ getExperationTime)
    Q_PROPERTY(QString getTokenId READ getTokenId)
    Q_PROPERTY(QString getRefreshToken READ getRefreshToken)

    // add more propertys and make more dynamic so it works across all services;

public:
   explicit OAuth2(QObject *parent = 0);
    bool isAuthorized();
     Q_INVOKABLE   void startLogin();
    Q_INVOKABLE QString getloginUrl();
    Q_INVOKABLE void urlChanged(const QUrl &url);

    QString clientSecert()const;
    void setClientSecert(const QString &clientSecert);

    QString clientId()const;
    void setClientId(const QString &clientId);

    QString redirectURI()const;
    void setRedirectURI(const QString &redirectURI);

    QString endPoint()const;
    void setEndPoint(const QString &endPoint);

    QString scopes()const;
    void setScopes(const QString &scopes);

    QString getaccessToken();
    QString getTokenType();
    double getExperationTime();
    QString getTokenId();
    QString getRefreshToken();

signals:
    void loginDone();
    void errorOccured(const QString&);
    void getExperation(const QString &ex);
private slots:
    void accessTokenObtained();
    void codeObtained();
    void replyFinished(QNetworkReply*);

private:
    void getAccessTokenFromRefreshToken();
private:
    QString m_strAccessToken;
    QString m_strRefreshToken;
    QString m_strCode;
    QString m_strEndPoint;
    QString m_strScope;
    QString m_strClientID;
    QString m_strClientSecret;
    QString m_strRedirectURI;
    QString m_strResponseType;
    QString m_strCompanyName;
    QString m_strAppName;
    QString m_strTokenType;
    double m_strExpiresIn;
    QString m_strIdToken;
    QNetworkAccessManager * m_pNetworkAccessManager;
};

#endif // OAUTH2_H
