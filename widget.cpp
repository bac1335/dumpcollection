#include "widget.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    qDebug()<<"--->lls<---" << __FUNCTION__;
    init();
}

Widget::~Widget()
{

}

void Widget::init()
{
    char* a[5] = {nullptr,nullptr,nullptr,nullptr,nullptr};
    int a111 = 23;
    char* m1 = nullptr;
//    qDebug() << "================================================" << *m1;

//    for(int i = 0;i<5;i++){
//        qDebug() << "================================================" << *a[i];
//    }

}
