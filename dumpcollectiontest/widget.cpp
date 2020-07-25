#include "widget.h"
#include <QDebug>
#include "dunmconfig.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    qDebug()<<"--->lls<---" << __FUNCTION__;
    init();
}

Widget::~Widget()
{

}


void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug() << "--->lls<---" << __FUNCTION__ << "=================";

    QByteArray array = QString::number(++m_iTest).toUtf8();

    LLS_DEBUG("===============================================================================================================================" + array);

}

void Widget::init()
{
    char* a[5] = {nullptr,nullptr,nullptr,nullptr,nullptr};
    int a111 = 23;
    char* m1 = nullptr;
}
