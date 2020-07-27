#ifndef DUNMCONFIG_H
#define DUNMCONFIG_H
#include "llsrsmanager.h"

#define U8QSTRING(STRING)  QString(u8##STRING).toUtf8().constData()

#define LLS_TITLE_START "【"
#define LLS_TITLE_END "】"


/**
    * @brief 由于远程传输输出日志局限性，部分调试还得用qDebug
*/

#ifdef USEREMOTELOG
#define LDEBUG(REMAND)  LLSRS->write(QString("===>LLS<===")   \
                                    + QString("%1%2%3").arg(U8QSTRING("【")).arg(U8QSTRING("远程调试")).arg(U8QSTRING("】"))  \
                                    + QString("%1").arg(__FUNCTION__)     \
                                    + QString(REMAND));
#else
#define LDEBUG(REMAND)  qDebug() << QString("===>LLS<===")   \
                                     << QString("%1%2%3").arg(U8QSTRING("【")).arg(U8QSTRING("远程调试")).arg(U8QSTRING("】"))  \
                                     << QString("%1").arg(__FUNCTION__)     \
                                     << QString(REMAND);
#endif

#endif // DUNMCONFIG_H
