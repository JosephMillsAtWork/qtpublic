#include "texttospeech.h"
/*!
  \qmltype TextToSpeech
  \inqmlmodule Mango.Utils 0.1
  \ingroup Mango.Utils
  \inherits Item
  \since 5.3
  A translator and also a text to speech engine that uses googles api for all of this
 */
 
 //FIXME make so that th user sets the tranlation type from qml
TextToSpeech::TextToSpeech(QObject *parent) :
    QObject(parent)
{
    m_url = "http://translate.google.com/translate_tts?ie=UTF-8&tl=%1&q=%2";
    m_playlist = new QMediaPlaylist;
    m_player = new QMediaPlayer;
    QObject::connect(m_player, SIGNAL(error(QMediaPlayer::Error)),
                     this, SLOT(errorSlot()) );
    QObject::connect(m_player, SIGNAL(stateChanged(QMediaPlayer::State)),
                     this, SLOT(errorSlot()) );
}
/*!
 \qmlproperty string TextToSpeech::language
 set the language that one wihes to use for translations
*/
QString TextToSpeech::language()const
{
    return  m_language;
}
void TextToSpeech::setLanguage(const QString &language)
{
    m_language = language;
}
/*!
 \qmlproperty string TextToSpeech::text
 The text that one wants to either tranlate and or get back as a voice recording.
*/
QString  TextToSpeech::text()const
{
        return m_text;
}

void TextToSpeech::setText(const QString &text)
{
    m_text = text;
}
/*!
 \qmlsignal TextToSpeech::speech()
 get back the text in spoken word
*/
void TextToSpeech::speech()
{
    if (QMultimedia::Available == 0)  {
        QString i;
        m_text.replace(" ","+");
        m_playlist->clear();
        m_playlist->addMedia(QUrl(m_url.arg(m_language).arg(m_text)));
        m_player->setPlaylist(m_playlist);
        m_player->play();
    } else {
        emit error();
    }
}
// a error slot that can be use in qml 
void TextToSpeech::errorSlot()
{
    emit error();
}
// a state machine that is here to return any kinda state that qtmultimedia is using. 
void TextToSpeech::state(QMediaPlayer::State state)
{
    if (state == QMediaPlayer::StoppedState)
        emit stopped();
}
