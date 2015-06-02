/*
 * Copyright (C) 2014 Joseph Mills.
 *
 */
#ifndef RANDOMPASSWORD_H
#define RANDOMPASSWORD_H
#include <QString>
#include <QDebug>
#include <QObject>
#include <QTime>
#include <QtGlobal>

class RandomPassword : public QObject
{
    Q_OBJECT
public:
    explicit RandomPassword(QObject *parent = 0);
    Q_PROPERTY(int numberOfCharecters READ numberOfCharecters WRITE setNumberOfCharecters)

    Q_INVOKABLE QString getRandomPassword();

    int numberOfCharecters();

    void setNumberOfCharecters(const int &numberOfCharecters);

    Q_INVOKABLE QString generateRandomPassword() ;

private:
    QString m_pass;
    int i_number;

};

#endif // RANDOMPASSWORD_H
