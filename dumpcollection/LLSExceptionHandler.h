// msjexhnd.h
#ifndef __MSJEXHND_H__  
#define __MSJEXHND_H__  
#include <Windows.h>
#include <QString>

class LLSExceptionHandler
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

private:
    static LONG  MSJUnhandledExceptionFilter(PEXCEPTION_POINTERS pExceptionInfo );

private:
    static QString     m_standCasePath;
};  


#endif  
