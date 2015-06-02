/*
 * Copyright (C) 2014 Joseph Mills.
 *
 */
#include "randompassword.h"
RandomPassword::RandomPassword(QObject *parent) :
    QObject(parent),
    i_number(10)
{
}
/*!
 \qmlsignal RandomPassword::getRandomPassword()
 get back the random string.
 */
QString RandomPassword::getRandomPassword()
{
    return m_pass;
}

/*!
  \qmlproperty string RandomPassword::numberOfCharecters
  How many charecters the password will be.
 */
int RandomPassword::numberOfCharecters()
{
    return i_number;
}

void RandomPassword::setNumberOfCharecters(const int &numberOfCharecters)
{
   i_number = numberOfCharecters;
}

/*!
  \qmlsignal RandomPassword::generateRandomPassword()
  This is used to intailize the random string and return it slash set it to the m_pass
 */

QString RandomPassword::generateRandomPassword()
{
   QString possibleCharacters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";
   int randomStringLength = i_number;

   qsrand(QTime::currentTime().msec());

   QString rString;
   for(int i=0; i<randomStringLength; ++i)
   {

       int index = qrand() % possibleCharacters.length();
       QChar nextChar = possibleCharacters.at(index);
       rString.append(nextChar);
   }
   m_pass = rString;
   return m_pass;
}
