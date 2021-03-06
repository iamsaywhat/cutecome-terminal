#ifndef LOGGER_H
#define LOGGER_H

#include <QObject>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QTime>
#include <QDate>
#include <QDebug>
#include "serialgui.h"

class Logger : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool enabled READ enabled WRITE setEnabled NOTIFY enabledChanged)
    Q_PROPERTY(QString path READ path WRITE setPath NOTIFY pathChanged)
    Q_PROPERTY(int bytesInRow READ bytesInRow WRITE setBytesInRow NOTIFY bytesInRowChanged)
    Q_PROPERTY(int columnSpace READ columnSpace WRITE setColumnSpace NOTIFY columnSpaceChanged)

public:
    explicit Logger(QObject *parent = nullptr,
                    SerialGui *port = nullptr);
    ~Logger(void);
    bool enabled(void) const;
    QString path(void) const;
    int bytesInRow(void) const;
    int columnSpace(void) const;
    enum DirectionType{
        INCOMING,   // Исходящее
        OUTGOING    // Входящее
    };

private:
    QString _path;
    bool _enabled = false;
    QFile *file = nullptr;
    SerialGui *_port = nullptr;
    int _bytesInRow = 5;
    int _columnSpace = 2;



    void toHexStrings(QStringList& list, QByteArray& data, int length);
    void toAsciiStrings(QStringList& list, QByteArray& data, int length);
    void write(DirectionType direction, QByteArray& data);

signals:
    void enabledChanged(bool);
    void pathChanged(QString&);
    void bytesInRowChanged(int);
    void columnSpaceChanged(int);

public slots:
    void setEnabled(bool);
    void setPath(QString);
    void setBytesInRow(int);
    void setColumnSpace(int);
    void incoming(QByteArray);
    void outgoing(QByteArray);
    void openFile(void);
    void closeFile(void);
};

#endif // LOGGER_H
