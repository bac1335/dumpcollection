#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

protected:
     void mouseReleaseEvent(QMouseEvent *event);

private:
    void init();
    int  m_iTest = 0;
};

#endif // WIDGET_H
