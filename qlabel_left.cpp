#include "qlabel_left.h"
#include <mainwindow.h>

QLabel_left::QLabel_left()
{

}

void Qlabel_left::mousePressEvent(QMouseEvent *event)
{
    MainWindow mw;
    QPixmap pixOld, pixNew;
    int A;

     qDebug() << "Hello mouse: " << event->pos();
     // emit clicked(event->pos().x());
    m_posX = event->pos().x();
    m_posY = event->pos().y();

    mw.getAA(A);
    mw.getPixs(pixOld, pixNew);
    int a=mw.getA();
    // pixOld=mw.getPixOld();
    // pixNew=mw.getPixNew();
    mw.set_on_Pix_FillRectDraw(m_posX, m_posY, 200, 200, pixOld, pixNew);
}
