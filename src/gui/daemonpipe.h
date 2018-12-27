#ifndef DAEMONPIPE_H
#define DAEMONPIPE_H
#include <QFile>
#include <QLocalSocket>
#include <QByteArray>

#ifdef Q_OS_WIN
class DaemonPipe : public QLocalSocket {
#else
class DaemonPipe : public QFile {
#endif
Q_OBJECT
public:
#ifdef Q_OS_WIN
    DaemonPipe(const QString &name) : QLocalSocket() {
        pipeName = name.mid(name.lastIndexOf("ckb")).replace(QChar('/'),QChar('\\'));
        pipeName.prepend("\\\\.\\pipe\\ckb-next\\");
        qDebug() << pipeName;
    }
    inline bool open(QIODevice::OpenMode mode) { return open(0, mode, 0); }
    bool open(int fd, QIODevice::OpenMode mode, QFileDevice::FileHandleFlags handleFlags);
    QByteArray readLine(qint64 maxSize = 0);

private:
    //void initPipe(QString str);
    QString pipeName;
#else
    DaemonPipe(const QString &name) : QFile(name) {}
#endif
};

#endif // DAEMONPIPE_H
