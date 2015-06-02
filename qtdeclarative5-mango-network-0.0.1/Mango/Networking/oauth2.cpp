#include "oauth2.h"
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QStringList>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonDocument>
/*!
  \qmltype OAuth2
  \inqmlmodule Mango.Networking 0.1
  \ingroup Mango.Networking
  \inherits Item
  \since 5.3
  This qml plugin is used to contact googles oauth2 services get a key and many more things.
 */
OAuth2::OAuth2(QObject *parent)
    : QObject(parent)
{
    m_pNetworkAccessManager = new QNetworkAccessManager(this);
    connect(m_pNetworkAccessManager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replyFinished(QNetworkReply*)));
}
/*!
 \qmlproperty string OAuth2::clientID
 Set the Client id of which you wish to use with google's oauth 2 services
*/
QString OAuth2::clientId()const
{
    return m_strClientID;
}
void OAuth2::setClientId(const QString &clientId)
{
    m_strClientID = clientId;
}
/*!
 \qmlproperty string OAuth2::clientSecert
 set the clientSecert key that google gives to the user for there app
*/
QString OAuth2::clientSecert()const
{
    return m_strClientSecret;
}
void OAuth2::setClientSecert( const QString &clientSecert)
{
    m_strClientSecret = clientSecert;
}

/*!
 \qmlproperty string OAuth2::redirectURI
 set the redirction url for after the client call
*/
QString OAuth2::redirectURI()const
{
    return m_strRedirectURI;
}
void OAuth2::setRedirectURI(const QString &redirectURI)
{
    m_strRedirectURI = redirectURI;
}
/*! 
 \qmlproperty string OAuth2::scopes
 set all the scopes that one wishes to get back from google
*/
QString OAuth2::scopes()const
{
    return m_strScope;
}
void OAuth2::setScopes(const QString &scope)
{
    m_strScope = scope;
}
/*!
 \qmlproperty string OAuth2::endPoint
 set the endpoint of which you wish to use with gogle's oauth service
*/
QString OAuth2::endPoint()const
{
    return m_strEndPoint;
}
void OAuth2::setEndPoint(const QString &endPoint)
{
    m_strEndPoint = endPoint;
}

/*!
  \qmlsignal OAuth2::accessTokenObtained()
  signal sent when the plugin has obtained a token
 */
void OAuth2::accessTokenObtained()
{
    emit loginDone();
}

void OAuth2::codeObtained()
{
    QUrl url("https://accounts.google.com/o/oauth2/token");
    QNetworkRequest request;
    request.setUrl(url);
    request.setRawHeader("Content-Type", "application/x-www-form-urlencoded");

    QString str = "client_id=" + m_strClientID;
    str += "&redirect_uri=" + m_strRedirectURI;
    str += "&client_secret=" + m_strClientSecret;
    str += "&grant_type=authorization_code";
    str += "&code=" + m_strCode;

    QByteArray params = str.toLatin1();
    m_pNetworkAccessManager->post(request, params);
}
//parse the json from google 
void OAuth2::replyFinished(QNetworkReply* reply)
{
    QString json = reply->readAll();
//    qDebug() << "Reply = " << json;
    QJsonDocument jsonDocument  = QJsonDocument::fromJson(json.toUtf8());
    if( jsonDocument.isEmpty() )
    {
        emit errorOccured(QString("Some thing went wrong with creating the json document"));
        return;
    }
    QJsonObject jsonObject = jsonDocument.object();

    QString atId;
    atId = "access_token";
    m_strAccessToken =  jsonObject.value(QString(atId) ).toString();

    QString refToken;
    refToken = "refresh_token";
    m_strRefreshToken = jsonObject.value(QString(refToken)).toString();

    QString tokenType;
    tokenType = "token_type";
    m_strTokenType = jsonObject.value(QString(tokenType)).toString();

    QString exIn;
    exIn= "expires_in";
    m_strExpiresIn = jsonObject.value(QString(exIn)).toDouble();

    QString idToken;
    idToken = "id_token";
    m_strIdToken = jsonObject.value(QString(idToken)).toString();

    emit loginDone();
}

/*!
 \qmlsignal OAuth2::getloginUrl()
 returns the full login that will be used with googles oauth system
*/
QString OAuth2::getloginUrl()
{
    QString str = QString("%1?client_id=%2&redirect_uri=%3&response_type=code&scope=%4&approval_prompt=force&access_type=offline").arg(m_strEndPoint).arg(m_strClientID).
            arg(m_strRedirectURI).arg(m_strScope);
            return str;
}

/*!
 \qmlsignal OAuth2::getaccessToken()
 signal to get the access token
*/
QString OAuth2::getaccessToken()
{
    return m_strAccessToken;
}
/*!
 \qmlsignal OAuth2::getTokenType()
 returns the type of toen that one recived
*/
QString OAuth2::getTokenType()
{
    return m_strTokenType;
}
/*!
 \qmlsignal OAuth2::getExperationTime()
 return the amount of time left on the token that one is using
*/
double OAuth2::getExperationTime()
{
    return m_strExpiresIn;
}
/*!
 \qmlsignal OAuth2::getTokenId()
 returns the token ID that was requested
*/
QString OAuth2::getTokenId()
{
    return m_strIdToken;
}
/*!
 \qmlsignal OAuth2::getRefreshToken()
 asks google for a new Token
*/
QString OAuth2::getRefreshToken()
{
    return m_strRefreshToken;
}
/*!
 qmlsignal OAuth2::isAuthorized()
 returns a bool property that looks to see if the user is has authorization code
*/
bool OAuth2::isAuthorized()
{
    return m_strAccessToken != "";
}
/*!
 /qmlsignal OAuth2::startLogin()
 used to start the hole login.
*/
void OAuth2::startLogin()
{
//    qDebug() << "OAuth2::startLogin";
    //FIXME add a switch here that sees if all is filled out correctly
    //        qDebug() << "Warning" << "To work with application you need to register your own application in <b>Google</b>.\n" << "Learn more from <a href=\"http://code.google.com/p/qt-google-plus/wiki/HowToRegisterYourApplicationInGoogle\">here</a>";
    //        return;
    //    }
        getAccessTokenFromRefreshToken();
}

void OAuth2::getAccessTokenFromRefreshToken()
{
    QUrl url("https://accounts.google.com/o/oauth2/token");
    QNetworkRequest request;
    request.setUrl(url);
    request.setRawHeader("Content-Type", "application/x-www-form-urlencoded");

    QString str = "client_id=" + m_strClientID;
    str += "&client_secret=" + m_strClientSecret;
    str += "&grant_type=refresh_token";
    str += "&refresh_token=" + m_strRefreshToken;

    QByteArray params = str.toLatin1();
    m_pNetworkAccessManager->post(request, params);
}
/*!
 \qmlsignal OAuth2::urlChanged()
 helper to let one know if the url has changed
*/
void OAuth2::urlChanged(const QUrl &url)
{
    QString str = url.toString();
    if(str.indexOf("access_token") != -1)
    {
        QStringList query = str.split("#");
        QStringList lst = query[1].split("&");
        for (int i=0; i<lst.count(); i++ )
        {
            QStringList pair = lst[i].split("=");
            if (pair[0] == "access_token")
            {
                m_strAccessToken = pair[1];
                emit accessTokenObtained();
            }
        }
    }
    else if(str.indexOf("code=") != -1)
    {
        QStringList query = str.split("?");
        QStringList lst = query[1].split("&");
        for (int i=0; i<lst.count(); i++ )
        {
            QStringList pair = lst[i].split("=");
            if (pair[0] == "code")
            {
                m_strCode = pair[1];
                emit codeObtained();
            }
        }
    }
}
