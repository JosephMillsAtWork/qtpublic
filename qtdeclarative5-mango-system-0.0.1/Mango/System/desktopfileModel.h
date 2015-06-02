/*
 * Copyright (C) 2014 Joseph Mills.
 *
 */
#include <QAbstractListModel>
#include <QStringList>

class DesktopFile
{
public:
    DesktopFile(const QString &name, const QString &comment, const QString &exec,const QString &type, bool &terminal,const QString &icon);
    QString name() const;
    QString comment() const;
    QString exec() const;
    QString type() const;
    bool terminal() const;
    QString icon() const;

private:
    QString m_name;
    QString m_comment;
    QString m_exec;
    QString m_type;
    bool m_terminal;
    QString m_icon;
};

class DesktopFileModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum DesktopFileRoles {
        NameRole = Qt::UserRole + 1,
        CommentRole,
        ExecRole,
        TypeRole,
        TerminalRole,
        IconRole
    };

    DesktopFileModel(QObject *parent = 0);
    void addDesktopFile(const DesktopFile &desktopFile);
    int rowCount(const QModelIndex & parent = QModelIndex()) const;
    QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;
    QHash<int,QByteArray> roleNames() const;

private:
    QList<DesktopFile> m_desktopFiles;
};


