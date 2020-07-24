#include "emulatormanager.h"
#include <QQmlApplicationEngine>
#include <QTcpSocket>
#include <QQmlContext>
#include <QFile>
#include <stdio.h>

EmulatorManager::EmulatorManager(QQmlApplicationEngine *engine, QObject *parent):
    QObject (parent),m_pQmlEngine(engine)
{

}

EmulatorManager::EmulatorManager(QObject *parent):
    QObject (parent)
{
    init();
}

void EmulatorManager::startConnect(QString ip,quint16 port)
{

    qDebug() << "--->lls<---" << __FUNCTION__ << ip << ":" << port;
    if(!m_pTcpSocket){
        m_pTcpSocket = new QTcpSocket(this);
        connect(m_pTcpSocket,&QTcpSocket::readyRead,this,&EmulatorManager::onReadText);
    }

    m_pTcpSocket->connectToHost(ip,port);

}

void EmulatorManager::disConnect()
{
    qDebug()<<"--->lls<---" << __FUNCTION__<< m_pTcpSocket->isOpen();
    if(m_pTcpSocket->isOpen()){
       m_pTcpSocket->disconnectFromHost();
    }
}

void EmulatorManager::saveFile(QByteArray bytearray, QString path)
{
    QString path2 = path;
    if(path2.contains("file:///")){
        path2.replace("file:///","");
    }

    QFile file(path2,parent());
    qDebug() << "--->lls<---" << __FUNCTION__  << path2;
    if(file.exists()){
        file.remove();
    }

    FILE* fp;

    fp = fopen(path2.toUtf8().constData(),"w");
    std::fwrite(bytearray,bytearray.size(),1,fp);
    fclose(fp);

}

void EmulatorManager::init()
{
    m_pQmlEngine = new QQmlApplicationEngine(this);
    m_pQmlEngine->rootContext()->setContextProperty("EmulatorManager",this);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    m_pQmlEngine->load(url);
}

void EmulatorManager::onReadText()
{
    QTcpSocket* socker = qobject_cast<QTcpSocket*>(sender());
    QByteArray array = socker->readAll();

    emit sigSendQmlWorld(array);
}
