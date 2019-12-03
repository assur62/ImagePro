#ifndef LABEL_LEFT_H
#define LABEL_LEFT_H

#include <QLabel>
#include <QMouseEvent>
#include <QDebug>
// #include <QPixmap>
#include <mainwindow.h>
#include <myglobals.h>
#include <QObject>

/*namespace Ui {
class Label_left;
}*/

class Label_left : public QLabel
{
    Q_OBJECT

public:
    explicit Label_left(QWidget *parent= 0);
    // ~Label_left();

    // MainWindow mw;
    // void mousePressEvent(QMouseEvent *event);
    // int BBB;
     // int AAA;
     // MainWindow *mw;

private slots:
    // void mousePressEvent(QMouseEvent *event);
    // friend int MainWindow::getA();

private:
    // Ui::Label_left *ui;

    // QPixmap &pixOld, &pixNew;
    QPixmap *pixOld;
    // int m_posX, m_posY;
    // MainWindow mw;

signals:
  void changeValue(int x, int y);

public slots:
  void mousePressEvent(QMouseEvent *event);
   // int getBBB(int AAA);
};


#endif // LABEL_LEFT_H
