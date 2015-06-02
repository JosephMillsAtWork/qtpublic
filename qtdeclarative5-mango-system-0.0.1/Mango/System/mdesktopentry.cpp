/***************************************************************************
** This file was derived from the MDesktopEntry implementation in the
** libmeegotouch library.
**
** Copyright (C) 2010, 2011 Nokia Corporation and/or its subsidiary(-ies).
** Copyright (C) 2011 Intel Corp.
** Copyright (C) 2012, 2013 Jolla Ltd.
**
** This library is free software; you can redistribute it and/or
** modify it under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation
** and appearing in the file LICENSE.LGPL included in the packaging
** of this file.
**
****************************************************************************/

#include <QRegExp>
#include <QFile>
#include <QStringList>
#include <QCoreApplication>
#include <QTranslator>
#include <QTextStream>
#include <QTextCodec>
#include <QDebug>

#include "mdesktopentry.h"
#include "mdesktopentry_p.h"

const QString TypeKey("Desktop Entry/Type");
const QString VersionKey("Desktop Entry/Version");
const QString NameKey("Desktop Entry/Name");
const QString GenericNameKey("Desktop Entry/GenericName");
const QString NoDisplayKey("Desktop Entry/NoDisplay");
const QString CommentKey("Desktop Entry/Comment");
const QString IconKey("Desktop Entry/Icon");
const QString HiddenKey("Desktop Entry/Hidden");
const QString OnlyShowInKey("Desktop Entry/OnlyShowIn");
const QString NotShowInKey("Desktop Entry/NotShowIn");
const QString TryExecKey("Desktop Entry/TryExec");
const QString ExecKey("Desktop Entry/Exec");
const QString PathKey("Desktop Entry/Path");
const QString TerminalKey("Desktop Entry/Terminal");
const QString MimeTypeKey("Desktop Entry/MimeType");
const QString CategoriesKey("Desktop Entry/Categories");
const QString StartupNotifyKey("Desktop Entry/StartupNotify");
const QString StartupWMClassKey("Desktop Entry/StartupWMClass");
const QString URLKey("Desktop Entry/URL");
const QString LogicalIdKey("Desktop Entry/X-MeeGo-Logical-Id");
const QString TranslationCatalogKey("Desktop Entry/X-MeeGo-Translation-Catalog");
const QString XMaemoServiceKey("Desktop Entry/X-Maemo-Service");
QMap<QString, QSharedPointer<QTranslator> > MDesktopEntryPrivate::translators;

// The syntax of the locale string in the POSIX environment variables
// related to locale is:
//
//    [language[_territory][.codeset][@modifier]]
//
// (see: http://www.opengroup.org/onlinepubs/000095399/basedefs/xbd_chap08.html)
//
// language is usually lower case in Linux but according to the above specification
// it may start with uppercase as well (i.e. LANG=Fr_FR is allowed).
//
void parsePosixLang(const QString &localeString, QString *language, QString *country, QString *script)
{
    // we do not need the encoding and therefore use non-capturing
    // parentheses for the encoding part here.
    // The country part is usually a 2 letter uppercase code
    // as in the above example, but there is the exception
    // es_419, i.e. Spanish in Latin America where the “country code”
    // is “419”. es_419 isn’t really a valid value for LANG, but for consistency
    // let’s make this behave the same way as the icu locale names work for es_419,
    // we only use LANG as a fallback to specify a locale when gconf isn’t available
    // or doesn’t work.
    QRegExp regexp("([a-z]{2,3})(_([A-Z]{2,2}|419))?(?:.(?:[a-zA-Z0-9-]+))?(@([A-Z][a-z]+))?");

    if (regexp.indexIn(localeString) == 0 &&
            regexp.capturedTexts().size() == 6) { // size of regexp pattern above
        *language = regexp.capturedTexts().at(1);
        *script = regexp.capturedTexts().at(5);
        *country = regexp.capturedTexts().at(3);
    } else {
        *language = QString();
        *script = QString();
        *country = QString();
    }
}

MDesktopEntryPrivate::MDesktopEntryPrivate(const QString &fileName) :
    sourceFileName(fileName),
    valid(true),
    q_ptr(NULL)
{
    QFile file(fileName);

    //Checks if the file exists and opens it in readonly mode
    if (file.exists() && file.open(QIODevice::ReadOnly)) {
        if (readDesktopFile(file, desktopEntriesMap)) {
            // Load the translation catalog if it has been defined for the entry.
            if (desktopEntriesMap.contains(TranslationCatalogKey)) {
                // Load the catalog from disk if it's not yet loaded
                QString catalog = desktopEntriesMap.value(TranslationCatalogKey);
                QString engineeringEnglishCatalog = catalog + "_eng_en";
                if (!translators.contains(engineeringEnglishCatalog)) {
                    QTranslator *translator = new QTranslator;
                    if (translator->load(engineeringEnglishCatalog, "/usr/share/translations")) {
                        translators[engineeringEnglishCatalog] = QSharedPointer<QTranslator>(translator);
                        qApp->installTranslator(translator);
                    } else {
                        delete translator;
                    }
                }

                if (!translators.contains(catalog)) {
                    QTranslator *translator = new QTranslator;
                    if (translator->load(QLocale(), catalog, "-", "/usr/share/translations")) {
                        translators[catalog] = QSharedPointer<QTranslator>(translator);
                        qApp->installTranslator(translator);
                    } else {
                        qDebug() << "Unable to load catalog" << catalog;
                        delete translator;
                    }
                }
            }
        }
    } else {
        qDebug() << "Specified Desktop file does not exist" << fileName;
    }
}

MDesktopEntryPrivate::~MDesktopEntryPrivate()
{
}

bool MDesktopEntryPrivate::readDesktopFile(QIODevice &device, QMap<QString, QString> &desktopEntriesMap)
{
    valid = MDesktopEntry::readDesktopFile(device, desktopEntriesMap);
    return valid;
}

bool MDesktopEntry::readDesktopFile(QIODevice &device, QMap<QString, QString> &desktopEntriesMap)
{
    bool valid = true;
    // Group header is of form [groupname]
    // The group name is captured
    // Group names may contain all ASCII characters except for [ and ] and control characters
    QRegExp groupHeaderRE("\\[([\\0040-\\0132\\0134\\0136-\\0176]+)\\]");
    // Key-value pair is of form Key=Value or Key[localization]=Value
    // The first capture is the key and the second capture is the value
    QRegExp keyValueRE("([A-Za-z0-9-]+"                // key
                       "(?:\\[[A-Za-z0-9_@.-]+\\])?"   // optional localization
                       ")"                             // end key capturing
                       "\\s*=\\s*"                     // equals
                       "(.*)");                        // value
    QString currentGroup;
    QStringList groupNames;
    QTextStream stream(&device);
    stream.setCodec(QTextCodec::codecForName("UTF-8"));
    while (!stream.atEnd()) {
        QString line = stream.readLine().trimmed();


        if (!line.isEmpty() && !line.startsWith('#')) {
            if (keyValueRE.exactMatch(line) && !currentGroup.isEmpty()) {
                // A key-value line was found. Prepend the key with the current group name.
                QString desktopKey = currentGroup + '/' + keyValueRE.cap(1);

                // Check whether it's already in the map
                if (!desktopEntriesMap.contains(desktopKey)) {
                    QString value = keyValueRE.cap(2);

                    // Check whether this is a known multivalue key
                    if (desktopKey == CategoriesKey || desktopKey == OnlyShowInKey ||
                            desktopKey == NotShowInKey || desktopKey == MimeTypeKey) {

                        if (value.endsWith("\\;") || !value.endsWith(';')) {
                            // Multivalue doesn't end with a semicolon so mark the desktop entry invalid
                            qDebug() << "Value for multivalue key" << desktopKey << "does not end in a semicolon";
                            valid = false;
                        }
                    }

                    // Add the value to the desktop entries map
                    desktopEntriesMap.insert(desktopKey, value);
                } else {
                    // Key is already present in the map so issue a warning
                    qDebug() << "Key" << desktopKey << "already defined. Value" << keyValueRE.cap(2) << "is ignored";
                }
            } else if (groupHeaderRE.exactMatch(line)) {
                // A group header line was found and if it's not already defined, set it as current group
                if (!groupNames.contains(groupHeaderRE.cap(1), Qt::CaseSensitive)) {
                    if (groupNames.isEmpty() && groupHeaderRE.cap(1) != "Desktop Entry") {
                        qDebug() << "Desktop entry should start with group name \"Desktop Entry\" ";
                        valid = false;
                    } else {
                        groupNames.push_back(groupHeaderRE.cap(1));
                        currentGroup = groupHeaderRE.cap(1);
                    }
                }
                // Redefining a group name will cause the desktop entry to become invalid but still parsed by the parser.
                else {
                    currentGroup = groupHeaderRE.cap(1);
                    qDebug() << "Multiple definitions of group" << groupHeaderRE.cap(1);
                    valid = false;
                }
            } else {

//                qDebug() << "Invalid .desktop entry line:" << line;
            }
        }
    }
    return valid;
}

bool MDesktopEntryPrivate::boolValue(const QString &key) const
{
    return desktopEntriesMap.value(key) == "true";
}

QStringList MDesktopEntryPrivate::stringListValue(const QString &key) const
{
    QStringList list;
    QString value = desktopEntriesMap.value(key);

    // Split the string using ; but not \; as the separator
    const int valueLength = value.length();
    for (int current = 0; current < valueLength;) {
        bool previousIsBackslash = false;
        const int start = current;
        for (int end = current; end < valueLength; ++current, ++end) {
            if (value.at(end) == ';' && !previousIsBackslash) {
                // Replace \; with ;
                list.append(value.mid(start, end - start).replace("\\;", ";"));
                current++;
                break;
            }

            previousIsBackslash = value.at(end) == '\\';
        }
    }

    return list;
}

MDesktopEntry::MDesktopEntry(const QString &fileName) :
    d_ptr(new MDesktopEntryPrivate(fileName))
{
}

MDesktopEntry::MDesktopEntry(MDesktopEntryPrivate &dd) :
    d_ptr(&dd)
{
}

MDesktopEntry::~MDesktopEntry()
{
    delete d_ptr;
}

QString MDesktopEntry::fileName() const
{
    return d_ptr->sourceFileName;
}

bool MDesktopEntry::contains(const QString &key) const
{
    return d_ptr->desktopEntriesMap.contains(key);
}

bool MDesktopEntry::contains(const QString &group, const QString &key) const
{
    return d_ptr->desktopEntriesMap.contains(group + '/' + key);
}

QString MDesktopEntry::value(const QString &key) const
{
    return d_ptr->desktopEntriesMap.value(key);
}

QString MDesktopEntry::value(const QString &group, const QString &key) const
{
    return d_ptr->desktopEntriesMap.value(group + '/' + key);
}

QStringList MDesktopEntry::stringListValue(const QString &key) const
{
    return d_ptr->stringListValue(key);
}

QStringList MDesktopEntry::stringListValue(const QString &group, const QString &key) const
{
    return d_ptr->stringListValue(group + '/' + key);
}

bool MDesktopEntry::isValid() const
{
    // The Type and Name keys always have to be present
    if (!contains(TypeKey)) {
        return false;
    }

    if (!contains(NameKey)) {
        return false;
    }

    // In case of an application the Exec key needs to be present
    if (type() == "Application" && !contains(ExecKey)) {
        return false;
    }

    // In case of a link the URL key needs to be present
    if (type() == "Link" && !contains(URLKey)) {
        return false;
    }

    // In case the desktop entry is invalid for some explicit reason
    // Some cases are:
    // 1. Group name defined multiple times
    // 2. Desktop entry's first group should be "Desktop Entry"
    if (!d_ptr->valid) {
        return false;
    }
    return true;
}

uint MDesktopEntry::hash() const
{
    return qHash(type() + name());
}

QString MDesktopEntry::type() const
{
    return value(TypeKey);
}

QString MDesktopEntry::version() const
{
    return value(VersionKey);
}

QString MDesktopEntry::name() const
{
    QString name = value(NameKey);

    if (contains(LogicalIdKey)) {
        QString key = value(LogicalIdKey);
        QString translation = qtTrId(key.toLatin1().data());
        if (!translation.isEmpty() && translation != key) {
            name = translation;
        }
    } else {
        QString lang, variant, country, postfixKey;

        parsePosixLang(getenv("LANG"), &lang, &country, &variant);
        if (contains(postfixKey = NameKey + '[' + lang + '_' +
                                  country  + '@' +
                                  variant  + ']') ||
                contains(postfixKey = NameKey + '[' + lang + '_' +
                                      country  + ']') ||
                contains(postfixKey = NameKey + '[' + lang + '@' +
                                      variant  + ']') ||
                contains(postfixKey = NameKey + '[' + lang + ']')) {
            // Use the freedesktop.org standard localization style
            name = value(postfixKey);
        }
    }

    return name;
}

QString MDesktopEntry::nameUnlocalized() const
{
    return value(NameKey);
}

QString MDesktopEntry::genericName() const
{
    return value(GenericNameKey);
}

bool MDesktopEntry::noDisplay() const
{
    return d_ptr->boolValue(NoDisplayKey);
}

QString MDesktopEntry::comment() const
{
    return value(CommentKey);
}

QString MDesktopEntry::icon() const
{
    return value(IconKey);
}

bool MDesktopEntry::hidden() const
{
    return d_ptr->boolValue(HiddenKey);
}

QStringList MDesktopEntry::onlyShowIn() const
{
    return d_ptr->stringListValue(OnlyShowInKey);
}

QStringList MDesktopEntry::notShowIn() const
{
    return d_ptr->stringListValue(NotShowInKey);
}

QString MDesktopEntry::tryExec() const
{
    return value(TryExecKey);
}

QString MDesktopEntry::exec() const
{
    return value(ExecKey);
}

QString MDesktopEntry::xMaemoService() const
{
    return value(XMaemoServiceKey);
}

QString MDesktopEntry::path() const
{
    return value(PathKey);
}

bool MDesktopEntry::terminal() const
{
    return d_ptr->boolValue(TerminalKey);
}

QStringList MDesktopEntry::mimeType() const
{
    return d_ptr->stringListValue(MimeTypeKey);
}

QStringList MDesktopEntry::categories() const
{
    return d_ptr->stringListValue(CategoriesKey);
}

bool MDesktopEntry::startupNotify() const
{
    return d_ptr->boolValue(StartupNotifyKey);
}

QString MDesktopEntry::startupWMClass() const
{
    return value(StartupWMClassKey);
}

QString MDesktopEntry::url() const
{
    return value(URLKey);
}
