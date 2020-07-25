#ifndef DUNMCONFIG_H
#define DUNMCONFIG_H
#include "llsrsmanager.h"

#define U8QSTRING(STRING)  QString(u8##STRING).toUtf8().constData()

#define LLS_TITLE_START "【"
#define LLS_TITLE_END "】"

//#define LLS_DEBUG(REMAND)  qDebug() << QString("===>LLS<===")   \
//                                    << QString("%1%2%3").arg(U8QSTRING("【")).arg(U8QSTRING("远程调试")).arg(U8QSTRING("】"))  \
//                                    << QString("%1").arg(__FUNCTION__)     \
//                                    << QString(REMAND);     \
//                                    LLSRS->write(REMAND)

#define LLS_DEBUG(REMAND)   LLSRS->write(REMAND)

#endif // DUNMCONFIG_H
