#include "emulatormanager.h"
#include <QQmlApplicationEngine>
#include <QTcpSocket>
#include <QQmlContext>
#include <QFile>
#include <stdio.h>
#include <QTimer>

EmulatorManager::EmulatorManager(QQmlApplicationEngine *engine, QObject *parent):
    QObject (parent),m_pQmlEngine(engine)
{

}

EmulatorManager::EmulatorManager(QObject *parent):
    QObject (parent)
{
    init();
}
#include <QThread>
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
    if(m_pTcpSocket){
        qDebug()<<"--->lls<---" << __FUNCTION__<< m_pTcpSocket->isOpen();
        if(m_pTcpSocket->isOpen()){
           m_pTcpSocket->disconnectFromHost();
           m_connectState = false;
           emit sigSendConnetState(false);
        }
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

void EmulatorManager::ParsingData(QByteArray &data)
{
    m_mutex.lock();
    QByteArray da = m_lastArray + data;
    m_lastArray.clear();
    while(da.contains("$start$")){
        da.remove(da.indexOf("$start$"),7);  //去除文件头
        if(da.contains("$end$")){            //尾部一定存在情况
            int heard = da.indexOf("$start$");
            int tail = da.indexOf("$end$");

            if(tail < heard){  //获取到数据
                QByteArray newData = da.left(tail);
                da.remove(tail,5); //存在尾部先去掉
                if(newData.isEmpty()){//心跳数据
                    if(!m_connectState){
                        m_connectState = true;
                        emit sigSendConnetState(true);
                    }
                }
                else{
                    emit sigSendQmlWorld(newData);
                }

                 da.remove(0,newData.size());
                 continue; //数据处理完，重新解析
            }
            else if(tail > heard){
                if(heard  != -1){  //类似"$start$54545ad$start$*****$end$******"  数据丢失
                     da.remove(0,heard);
                     continue;   //数据处理完，重新解析
                }
                else{    //类似"$start$54545ad*****$end$******"
                    QByteArray newData = da.left(tail);
                    da.remove(tail,5); //存在尾部先去掉
                    if(newData.isEmpty()){//心跳数据
                        if(!m_connectState){
                            m_connectState = true;
                            emit sigSendConnetState(true);
                        }
                    }
                    else{
                        emit sigSendQmlWorld(newData);
                    }
                    break;    //*********  *不管有没有数据都做丢失处理
                }

            }
            else{  //头部等于尾部只有一种情况，都不存在，类似"adsa1321" //数据丢失
                    break;
            }

        }
        else{   //尾部不存在情况
           m_lastArray = da;
           break;
        }

    }

    m_mutex.unlock();

}

void EmulatorManager::onReadText()
{
    QTcpSocket* socker = qobject_cast<QTcpSocket*>(sender());
    QByteArray array = socker->readAll();

    ParsingData(array);
}
