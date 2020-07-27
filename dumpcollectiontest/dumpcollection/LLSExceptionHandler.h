// msjexhnd.h
#ifndef LLSEXCEPTIONHANDLER_H
#define LLSEXCEPTIONHANDLER_H
#include <Windows.h>
#include <QString>

class Q_DECL_EXPORT LLSExceptionHandler
{  
public:
    /**
    * @brief  启动异常收集
    */
    static void initExceptionHandler();
    /**
    * @brief  启动日志收集，正式版取消
    */
    static void initLogHandler();
    /**
    * @brief  开启日志远程传输
    */
    static void initRemoteTransmission();


private:
    static LONG  MSJUnhandledExceptionFilter(PEXCEPTION_POINTERS pExceptionInfo );

private:
    static QString     m_standCasePath;
};  


#endif  //LLSEXCEPTIONHANDLER_H
