#include "tllogger.h"

#include <QtGlobal>
#include <QtCore/qdatetime.h>
#include <QtCore/qfile.h>
#include <QtCore/qtextstream.h>
#include <QtCore/qdir.h>
#include <QtWidgets/qapplication.h>

#include "Windows.h"
#include <QDebug>

QMutex TLLogger::loggerMutex;
QString TLLogger::logFilePath;
QStringList TLLogger::m_ignore;//需要过滤的字符串
QtMessageHandler TLLogger::m_preHandler;

void TLLogger::AdjustPrivilege()
{
#if 0
    HANDLE hToken;
    if (OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken))
    {
        TOKEN_PRIVILEGES tp;
        tp.PrivilegeCount = 1;
        tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
        if (LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &tp.Privileges[0].Luid))
        {
            AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(tp), NULL, NULL);
        }
        CloseHandle(hToken);
    }
#endif
}


/**
 * @brief TLLogger::installLog
 * 初始化日志
 */
void TLLogger::installLog()
{
#ifdef QT_DEBUG //Qt运行debug直接返回
    return;
#endif
//    AdjustPrivilege();
    QDateTime datetime(QDateTime::currentDateTime());
    #if 0
    QString logFilePath = QApplication::applicationDirPath()
            + "/log/" + datetime.toString("yyyy-MM-dd");//c盘可能写不了
    if (!QDir(logFilePath).exists()) {
        QDir().mkpath(logFilePath);
    }
    logFilePath += "/" + QString("%1-%2.log")
            .arg(qAppName())
            .arg (datetime.toString ("hh-mm-ss"));

    TLLogger::logFilePath = logFilePath;
#endif

    QString logFilePath ="D:/log/" + datetime.toString("yyyy-MM-dd");
    if (!QDir(logFilePath).exists()) {
        QDir().mkpath(logFilePath);
    }
    logFilePath += "/" + QString("%1-%2.log")
            .arg(qAppName())
            .arg (datetime.toString ("hh-mm-ss"));

    TLLogger::logFilePath = logFilePath;

    m_preHandler = qInstallMessageHandler(TLLogger::messageOutput);//设置回调
}

void TLLogger::installLog(QString logPath)
{
//    C7Tools::deleteFolderOverTime(logPath,15*24*60*60); //删除15天以后的日志
    QDateTime datetime(QDateTime::currentDateTime());
    logPath += datetime.toString("yyyy-MM-dd");
    if (!QDir(logPath).exists()) {
        QDir().mkpath(logPath);
    }
    if(!logPath.endsWith(QDir::separator())){
        logPath += QDir::separator();
    }
    logPath += QString("%1-%2.log")
            .arg(qApp->applicationName())
            .arg (datetime.toString ("hh-mm-ss"));
    TLLogger::logFilePath = logPath;
    m_preHandler = qInstallMessageHandler(TLLogger::messageOutput);//设置回调
}
/**
 * @brief TLLogger::messageOutput
 * @param type 消息类型
 * @param context 消息的上下文
 * @param msg 消息内容
 */
void TLLogger::messageOutput(QtMsgType type,const QMessageLogContext &context,const QString &msg)
{
//    if (-1 != msg.indexOf("libpng warning")) {
//        return;
//    }
    if(ignore(msg)){
        return;
    }

    QMutexLocker locker(&TLLogger::loggerMutex);//加锁

    QString levelValue;
    switch (type) {
    case QtDebugMsg:
        levelValue = "Debug";
        break;
    case QtInfoMsg:
        levelValue = "Info";
        break;
    case QtWarningMsg:
        levelValue = "Warning";
        break;
    case QtCriticalMsg:
        levelValue = "Critical";
        break;
    case QtFatalMsg:
        levelValue = "Fatal";
        break;
    }

#if 0 //重新格式调试信息，丢到stderr。可以显示行号等
    fprintf(stderr, "Debug: %s (%s:%u, %s)\n", msg.toLocal8Bit().constData(), context.file, context.line, context.function);
#endif

    QDateTime dateTime(QDateTime::currentDateTime());
    QString timeValue(dateTime.toString("dd-MM-yyyy HH:mm:ss:zzz"));

    QByteArray localMsg = msg.toUtf8();
    QString contextString;
    if(type>QtDebugMsg){
        contextString = QString("%1 %2: %3---file:%4,line:%5,function:%6\n").arg(timeValue).arg(levelValue)
                .arg(localMsg.constData()).arg(context.file).arg(context.line).arg(context.function);
    }else{
        contextString = QString("%1 %2: %3\n").arg(timeValue).arg(levelValue)
                .arg(localMsg.constData())/*.arg(context.file).arg(context.line).arg(context.function)*/;
    }



    QFile outFile(TLLogger::logFilePath);
    if(outFile.open(QIODevice::WriteOnly | QIODevice::Append)){
        QTextStream stream(&outFile);
        stream << contextString << endl;

        if (QtFatalMsg == type) {
            abort();
        }
    }else{
    }
    if(m_preHandler){
        m_preHandler(type,context,msg);
    }
}
/**
 * @brief TLLogger::ignore
 * @param msg
 * @return 是否忽略这条消息
 */
bool TLLogger::ignore(const QString &msg)
{
    foreach (QString s, m_ignore) {
        if (-1 != msg.indexOf(s)) {
            return true;
        }
    }
    return false;
}
