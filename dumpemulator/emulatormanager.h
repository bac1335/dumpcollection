#ifndef EMULATORMANAGER_H
#define EMULATORMANAGER_H
#include <QDebug>
#include <QMutex>

class QQmlApplicationEngine;
class QTcpSocket;
class QTimer;
class EmulatorManager : public QObject{
    Q_OBJECT
public:
    explicit EmulatorManager(QQmlApplicationEngine* engine,QObject* parent = nullptr);
    explicit EmulatorManager(QObject* parent = nullptr);
    Q_INVOKABLE void startConnect(QString ip,quint16 port);
    Q_INVOKABLE void disConnect();
    Q_INVOKABLE void saveFile(QByteArray bytearray,QString path);

private:
    void init();
    inline void ParsingData(QByteArray& data);

signals:
    void sigSendQmlWorld(QByteArray array);
    void sigSendConnetState(bool state);

private slots:
    void onReadText();

private:
    QQmlApplicationEngine*      m_pQmlEngine = nullptr;
    QTcpSocket*                 m_pTcpSocket = nullptr;
    bool                        m_connectState = false;
    QByteArray                  m_lastArray;            //没有数据尾部的字段
    QMutex                      m_mutex;
    bool                        m_first = true;
};

#endif // EMULATORMANAGER_H
