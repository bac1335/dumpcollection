#ifndef EMULATORMANAGER_H
#define EMULATORMANAGER_H
#include <QDebug>

class QQmlApplicationEngine;
class QTcpSocket;
class EmulatorManager : public QObject{
    Q_OBJECT
public:
    explicit EmulatorManager(QQmlApplicationEngine* engine,QObject* parent = nullptr);
    explicit EmulatorManager(QObject* parent = nullptr);
    Q_INVOKABLE void startConnect(QString ip,quint16 port);
    Q_INVOKABLE void disConnect();

private:
    void init();

signals:
    void sigSendQmlWorld(QByteArray array);

private slots:
    void onReadText();

private:
    QQmlApplicationEngine*      m_pQmlEngine = nullptr;
    QTcpSocket*                 m_pTcpSocket = nullptr;
};

#endif // EMULATORMANAGER_H
