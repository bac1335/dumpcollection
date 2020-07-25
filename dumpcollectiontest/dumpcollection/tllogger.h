#ifndef TLLOGGER_H
#define TLLOGGER_H

#include <QtCore/qmutex.h>
#include <QStringList>

/****************************************************************************
 * @date    :2018.07.12
 * @brief   :debug输出到日志文件
 * @other   :测试使用这个功能，正式版请屏蔽(不调用installLog即可)
****************************************************************************/
class  TLLogger
{
public:
    TLLogger();

public:
    static void installLog();
    static void installLog(QString logPath);

private:
    static void AdjustPrivilege();

    static void messageOutput(QtMsgType type,
                              const QMessageLogContext &context,
                              const QString &msg);
    static bool ignore(const QString& msg);

private:
    static QStringList m_ignore;
    static QMutex loggerMutex;
    static QString logFilePath;
    static QtMessageHandler m_preHandler;
};

#endif // TLLOGGER_H
