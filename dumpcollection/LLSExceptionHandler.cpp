#include "LLSExceptionHandler.h"
#include <QDebug>
#include <QTime>
#include <QMessageBox>
#include <DbgHelp.h>
#include <QMessageBox>
#include <QStandardPaths>
#include <QApplication>
#include <QDir>
#include "tllogger.h"
#include "llsrsmanager.h"

#pragma execution_character_set("utf-8")

QString LLSExceptionHandler::m_standCasePath;

void LLSExceptionHandler::initExceptionHandler()
{
    m_standCasePath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation) + "/dmpCash/";
    QDir dir(m_standCasePath);
    if(!dir.exists()){
        dir.mkpath(m_standCasePath);
    }
    else{

    }

    SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)MSJUnhandledExceptionFilter);//注冊异常捕获函数
}

void LLSExceptionHandler::initLogHandler()
{
    TLLogger::installLog(QStandardPaths::writableLocation(QStandardPaths::AppDataLocation)+ "/log/");//初始化日志收集
}

void LLSExceptionHandler::initRemoteTransmission()
{
    LLSRSManager::initRemoteTransmission();
}

LONG LLSExceptionHandler::MSJUnhandledExceptionFilter(PEXCEPTION_POINTERS pException)
{
    QString time = QTime::currentTime().toString("HHmmsszzz");
    //创建 Dump 文件
    QString strPath = m_standCasePath + time;

    QDir dir(strPath);
    if(!dir.exists()){
        dir.mkpath(strPath);
    }

    QString str2 = strPath + "/" + QApplication::applicationName();

    std::wstring wlpstr = str2.toStdWString()+L".dmp";
    LPCWSTR lpcwStr = wlpstr.c_str();
    qDebug()<<__FUNCTION__<<lpcwStr;
    HANDLE hDumpFile = CreateFile(lpcwStr,
                                  GENERIC_WRITE,
                                  0,
                                  NULL,
                                  CREATE_ALWAYS,
                                  FILE_ATTRIBUTE_NORMAL,
                                  NULL);

    if( hDumpFile != INVALID_HANDLE_VALUE){
        //Dump信息
        MINIDUMP_EXCEPTION_INFORMATION dumpInfo;
        dumpInfo.ExceptionPointers = pException;
        dumpInfo.ThreadId = GetCurrentThreadId();
        dumpInfo.ClientPointers = TRUE;
        //写入Dump文件内容
        MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hDumpFile, MiniDumpNormal, &dumpInfo, NULL, NULL);
    }

    QString dpbFile = QString("%1/%2.pdb")
                     .arg(QApplication::applicationDirPath())
                     .arg(QApplication::applicationName());

    QFile file(dpbFile);
    if(file.exists()){
        file.copy(QString("%1/%2.pdb")
                  .arg(strPath)
                  .arg(QApplication::applicationName()));
    }

    //这里弹出一个错误对话框并退出程序
    EXCEPTION_RECORD* record = pException->ExceptionRecord;
    QString errCode(QString::number(record->ExceptionCode,16)),errAdr(QString::number((uint)record->ExceptionAddress,16)),errMod;
    QMessageBox::critical(NULL,"程式崩溃","<FONT size=4><div><b>发生的错误</b><br/></div>"+
        QString("<div>错误代码：%1</div><div>错误地址：%2</div></FONT>").arg(errCode).arg(errAdr),
        QMessageBox::Ok);

    return EXCEPTION_EXECUTE_HANDLER;
}
