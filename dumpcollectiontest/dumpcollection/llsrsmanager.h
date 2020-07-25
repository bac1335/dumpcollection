#ifndef LLSRSMANAGER_H
#define LLSRSMANAGER_H

#include <QObject>
/**
    * @brief         与模拟器进行数据通信
    * @date          2020-07-24
    */

class QTcpServer;
class QTcpSocket;
class QTimer;
#define LLSRS LLSRSManager::instance()

class LLSRSManager : public QObject{
    enum{
        STATE_OFFLINE,
        STATE_ONLINE
    };
public:
    static void initRemoteTransmission();
    static LLSRSManager* instance();
    void write(QByteArray array);

private:
    explicit LLSRSManager(QObject* parent = nullptr):QObject(parent){}
    void init();
    /**
    * @brief   发送心跳到客户端，返回-1表示客户端不在线
    * @parame  QTcpSocket  客户端地址
    */
    bool send_WakeHand(QTcpSocket *currSocket);
    void clearSocket(QTcpSocket*);

private slots:
    /**
    * @brief    客户端连接
    */
    void onNewConnection();
    /**
    * @brief    定时更新设备连接状态，清理释放过期的SOCKET
    */
    void onUpdate_DeviceNetState();

private:
    QTcpServer*            m_pTcpServer = nullptr;
    static LLSRSManager*   m_pLLSSRManager;
    QList<QTcpSocket*>     m_listClient;
    QTimer*                m_pTimer = nullptr;
};

#endif // LLSRSMANAGER_H
