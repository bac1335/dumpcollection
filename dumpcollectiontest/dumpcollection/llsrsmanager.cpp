#include "llsrsmanager.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>
#include "dunmconfig.h"

LLSRSManager* LLSRSManager::m_pLLSSRManager = nullptr;

void LLSRSManager::initRemoteTransmission()
{
    if(!m_pLLSSRManager){
        m_pLLSSRManager = new LLSRSManager;
        m_pLLSSRManager->init();

    }

}

LLSRSManager *LLSRSManager::instance()
{
    return m_pLLSSRManager;
}

void LLSRSManager::write(QByteArray array)
{
    for(auto item : m_listClient){
        item->write("$start$" + array +"$end$");
    }
}

void LLSRSManager::init()
{
    if(!m_pTcpServer){
        m_pTcpServer = new QTcpServer(this);
        connect(m_pTcpServer,&QTcpServer::newConnection,this,&LLSRSManager::onNewConnection);
        m_pTcpServer->listen(QHostAddress::Any,quint16(10241));

        //断线检测
        m_pTimer = new QTimer(this);
        m_pTimer->setInterval(1000);
        connect(m_pTimer,&QTimer::timeout,this,&LLSRSManager::onUpdate_DeviceNetState);
        m_pTimer->start();
    }

}

bool LLSRSManager::send_WakeHand(QTcpSocket *currSocket)
{
    int ret = currSocket->write("$start$$end$");
    qDebug()<<"ret ="<<ret;
    if(ret == -1)
        return STATE_OFFLINE;
    return STATE_ONLINE;
}

void LLSRSManager::clearSocket(QTcpSocket *socket)
{
    if(m_listClient.contains(socket)){
        m_listClient.removeOne(socket);
        delete socket;
        socket = nullptr;
    }
}

void LLSRSManager::onUpdate_DeviceNetState()
{
    int count = m_listClient.count();
#ifdef QT_DEBUG
//    qDebug()<<"Line-658 当前在线设备数量:"<<count;
    LLS_DEBUG(QString("%1%2").arg("Line-658 当前在线设备数量:").arg(QString::number(count)).toUtf8());
#endif
    for(int i = 0;i<count;i++)
    {
        QTcpSocket* client = m_listClient.at(i);
        bool netState = send_WakeHand(client);
        if(netState == STATE_OFFLINE)
        {
            clearSocket(client);
        }
    }
}


void LLSRSManager::onNewConnection()
{
    if(m_pTcpServer->hasPendingConnections()){
        QTcpSocket* client = m_pTcpServer->nextPendingConnection();
        m_listClient.push_back(client);
    }
}
