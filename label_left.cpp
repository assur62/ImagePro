#include "label_left.h"
#include "mainwindow.h"
#include "myglobals.h"
// #include "ui_label_left.h"

Label_left::Label_left(QWidget *parent) :
      QLabel(parent)
  /*, ui(new Ui::Label_left)*/
{
    // ui->setUi(this);

    // MainWindow mw;
    // connect(this, SIGNAL(changeValue(int,int)), &mw, SLOT(slotRect(int, int)));
}

/*Label_left::~Label_left()
{
    delete ui;
}*/

// int label_left::getBBB(int AAA) {return AAA;}


void Label_left::mousePressEvent(QMouseEvent *event)
{
   MainWindow mw;

    qDebug() << "Hello mouse: " << event->pos();

    int m_posX = event->pos().x();
    int m_posY = event->pos().y();

    int BBB=AAA+1;
    // BBB=(*mw.CCC);
    // BBB=GB::instance;
    pixOld=pix1;

    qDebug() << "Hello mouse: " << BBB;

   // connect(this, SIGNAL(changeValue(int,int)), &mw, SLOT(slotRect(int, int)));
   // connect(this, &label_left::changeValue, &mw, &MainWindow::slotRect);

  // emit changeValue(m_posX, m_posY);

    mw.set_on_Pix_FillRectDraw(m_posX, m_posY, 200, 200, *pix1, *pix1_5);
}

