#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QPainter>

// #include <thread>
// #include <omp.h>
// #include <math.h>

using namespace cv;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    StatLabel1 = new QLabel(this);
    StatLabel2 = new QLabel(this);

    StatProgress = new QProgressBar(this);

    ui->statusBar->addPermanentWidget(StatLabel1);
    ui->statusBar->addPermanentWidget(StatLabel2);
    // ui->statusBar->addPermanentWidget(StatLabel3);
    ui->statusBar->addPermanentWidget(StatProgress);

    // ui->mainToolBar->addSeparator();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showEvent(QShowEvent *event)
{
   // ui->toolButton->setIcon(QIcon(":/arrow_right_15596"));
   // ui->toolButton_2->setIcon(QIcon(":/camera-diaphragm_icon-icons.com_72829.png"));
   // ui->toolButton_3->setIcon(QIcon(":/arrow_left_15601"));
   // ui->toolButton_4->setIcon(QIcon(":/arrow_left_15601"));

    // ui->statusBar->setStyle(QStyle::PE_FrameFocusRect);

     setGeometry(300, 100, 1436, 770); // main window

     StatLabel1->setLineWidth(1);
     StatLabel1->setFrameStyle(QFrame::Panel | QFrame::Sunken);
     StatLabel1->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

     StatLabel2->setLineWidth(1);
     StatLabel2->setFrameStyle(QFrame::Panel | QFrame::Sunken);
     StatLabel2->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);

     /*StatLabel3->setLineWidth(1);
     StatLabel3->setFrameStyle(QFrame::Panel | QFrame::Sunken);
     StatLabel3->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Fixed);*/

     StatProgress->setFixedHeight(18);
     StatProgress->setFixedWidth(200);
     StatProgress->setValue(0);

     ui->toolButton_12->setEnabled(false);
     ui->toolButton_13->setEnabled(false);

     int x14=qRound(0.70*ui->frame_6->width());
     ui->toolButton_14->setGeometry(x14, 2, 60, 25);

     /*int x8=qRound(0.15*ui->frame_6->width());
     ui->toolButton_8->setGeometry(x8, 2, 60, 25);
     ui->toolButton_9->setGeometry(x8+50, 2, 60, 25);
     ui->toolButton_10->setGeometry(x8+100, 2, 60, 25);*/

     // ui->mainToolBar->addSeparator();
     ui->action_2->setText(" ");
     ui->action_3->setText(" ");    

     Hm[0][0]=1.0; Hr[0][0]=1.0;    

     // unsigned nthreads = std::thread::hardware_concurrency(); // кол-во потоков

}

void MainWindow::resizeEvent(QResizeEvent *event)
{ // изменение размеров

    ui->verticalSlider_7->setFixedHeight(ui->frame_10->height());

    // pix1 = &pix0; // ???
    w1 = ui->label->width();
    h1 = ui->label->height();
    ui->label->setPixmap(pix1.scaled(w1, h1, Qt::KeepAspectRatio));

    // pix2 = &pix0; // ?????
    w2 = ui->label_2->width();
    h2 = ui->label_2->height();
    ui->label_2->setPixmap(pix2.scaled(w2, h2, Qt::KeepAspectRatio));

    kw1=qreal(wi1)/qreal(w1);
    kh1=qreal(hi1)/qreal(h1);

    if (visibleRect) {set_on_Pix_FillRectDraw(1, xrect, yrect, wrect, hrect, 1.0, 1.0, 0.0, 0.4, pix1);
                     cutImage(xrect, yrect, wrect, hrect);}

     int x14=qRound(0.7*ui->frame_6->width());
     ui->toolButton_14->setGeometry(x14, 2, 60, 25);
    /* int x9=qRound(0.21*ui->frame_6->width());
     ui->toolButton_8->setGeometry(x9-50, 2, 30, 25);
     ui->toolButton_9->setGeometry(x9, 2, 30, 25);
     ui->toolButton_10->setGeometry(x9+50, 2, 30, 25);    */
}

void MainWindow::SliderPosInit(int pos)
{  // метод SliderPosInit, возвращающий Slider в исходное положение

   // sliderPosInit=true;
   ui->verticalSlider->setValue(pos);
   ui->verticalSlider->setSliderPosition(pos);
   ui->verticalSlider_2 ->setValue(pos);
   ui->verticalSlider_2->setSliderPosition(pos);
   ui->verticalSlider_3 ->setValue(pos);
   ui->verticalSlider_3->setSliderPosition(pos);
   ui->verticalSlider_4 ->setValue(pos);
   ui->verticalSlider_4->setSliderPosition(pos);

   /*ui->verticalSlider_5 ->setValue(pos);
   ui->verticalSlider_5->setSliderPosition(pos);*/
}

void MainWindow::ImMatrixFill(int width, int height, int v)
{ // инициализация матриц
  // QColor color;

  for (int y = 0; y < height; y++)
  {
          QRgb *deltLineC = reinterpret_cast<QRgb*>(ImC.scanLine(y));
          QRgb *deltLineG = reinterpret_cast<QRgb*>(ImG.scanLine(y));

          for (int x = 0; x < width; x++)
          {
            *deltLineC++ = qRgba(v,
                                 v,
                                 v,
                                 255);
            *deltLineG++ = qRgba(v,
                                 v,
                                 v,
                                 255);
          }
  }
  /*for (int x = 0; x < width; x++)
  {
      for (int y = 0; y < height; y++)
      {         
         color.setHslF(v,v,v);
         ImL.setPixelColor(x, y, color);
         ImC.setPixelColor(x, y, color);
         ImG.setPixelColor(x, y, color);
         // color.setHslF(0,v,0);
         ImS.setPixelColor(x, y, color);
       }
   }*/
}

void MainWindow::whiteLeft()
{
    clearLayout(ui->verticalLayout_5, true);
    QChartView *myChart0 = new QChartView();
    ui->verticalLayout_5->addWidget(myChart0);   
}

void MainWindow::whiteRight()
{
   clearLayout(ui->verticalLayout_6, true);
   QChartView *myChart0 = new QChartView();
   ui->verticalLayout_6->addWidget(myChart0);
}

void MainWindow::on_actionOpen_triggered()
{// открытие файла
    // QColor color;
    QString path; // лучше в глобальные переменные

    // QString mFileName=QFileDialog::getOpenFileName ( this, " open file...", QDir::currentPath(), " Image files ( *.png *.jpg *.bmp ); All files ( *.* ) " );
     QString mFileName=QFileDialog::getOpenFileName ( this, " open file...", path, " Image files ( *.png *.jpg *.bmp ); All files ( *.* ) " );
    if ( mFileName.isEmpty ( ) ) //Если пользователь не выбрал ни одного файла
        {
            return; //выйти из метода
        } 
     path = QFileInfo(mFileName).path();
    // whiteLeft();
    // whiteRight();

    pix0.load(mFileName);   
    // QImage Image(mFileName);

    pix1 = pix0; // вывод изображения в окно 1
    w1 = ui->label->width(); // размеры лейбла 1
    h1 = ui->label->height();

    // Image = pix0.toImage(); // подгон окон под изображения
    /*int wi0 = Image.width();
    int hi0 = Image.height();
    int add_h=66;
    int add_w=195/;
    if (wi0>hi0) {
       qreal kh =(qreal)w1*(qreal)hi0/wi0;
        this->setGeometry(400,200, ceil(2.0*w1)+add_w, kh+add_h);
    }
    else {
        qreal kw =(qreal)(h1)*(qreal)wi0/hi0;
        this->setGeometry(400,200, ceil(2.0*kw)+add_w, h1+add_h);
    }*/

    ui->label->setPixmap(pix1.scaled(w1, h1, Qt::KeepAspectRatio));

    pix2=pix0;

    // QPixmap pix00; // очистка окна 2
    // ui->label_2->setPixmap(pix00.scaled(w1, h1, Qt::KeepAspectRatio));

    ImC = pix0.toImage();  //  матрица добавок RGB контрастностей
    ImC.fill(0);
    ImG = ImC; //  гамма-коррекции
    ImS = ImC; //  матрица S

    wi1 = ImC.width();
    hi1 = ImC.height();
    ImMatrixFill(wi1, hi1, 127);

    kw1=qreal(wi1)/qreal(w1);
    kh1=qreal(hi1)/qreal(h1);

    wrect=qCeil(0.2*wi1); // прямоугольник-линза
    hrect=qCeil(0.2*hi1);

    QFileInfo file(mFileName);
    QString base = file.baseName();
    statusBar()->showMessage(base/*mFileName*/);

    wi2 = wi1;
    hi2 = hi1;
    on_toolButton_clicked(); // передача изображения на второй экран

    ui->verticalSlider_6->setEnabled(false);

    ui->verticalSlider_7->setFixedHeight(ui->frame_10->height());
    ui->verticalSlider_7->setMaximum(hi1-1);
    ui->verticalSlider_7->setVisible(false);

    keyCtrl=false;

    on_toolButton_21_clicked();
}


void MainWindow::closeEvent(QCloseEvent *event)
  {
     // painter->end();
  }

void MainWindow::on_toolButton_7_clicked()
{ // восстановление исходного изображения
  pix1 = pix0;
  QImage Image = pix1.toImage();
  // int wi1 = Image.width();
  // int hi1 = Image.height();
  ui->label->setPixmap(pix1.scaled(w1, h1, Qt::KeepAspectRatio));
  ui->verticalSlider_7->setMaximum(Image.height()-1);

  if (ui->checkBox_3->isChecked()) on_verticalSlider_7_valueChanged(ValSld_7); // строка
}

void MainWindow::on_toolButton_clicked()
{
    if (ui->checkBox_2->isChecked()) ui->checkBox_2->setChecked(false);

    // передача pix1 на второй экран (pix2)
    pix2 = pix1; // pix2 - результат обработки pix1
    pix3 = pix1; // pix3 - результат обработки pix2 (выводится на экран 2)

    Image2 = pix2.toImage(); // ?????????????????
    wi2 = Image2.width();
    hi2 = Image2.height();

    SliderPosInit(0);
    ImMatrixFill(wi1, hi1, 127);
    ui->spinBox->setValue(0);

    w2 = ui->label_2->width(); // размеры лейбла 2
    h2 = ui->label_2->height();
    ui->label_2->setPixmap(pix2.scaled(w2, h2, Qt::KeepAspectRatio));

    if (ui->checkBox_3->isChecked()) on_verticalSlider_7_valueChanged(ValSld_7); // строка
}

void MainWindow::on_toolButton_2_clicked()
{     // негатив

        ui->spinBox->setValue(0);
        SliderPosInit(0);

        QImage Image = pix1.toImage();
        /*wi1 = Image.width(); // размеры изображения
        hi1 = Image.height();
        ImMatrixFill(wi1, hi1, 127);

        for (int y = 0; y < hi1; y++)
        {
             QRgb *tempLine  = reinterpret_cast<QRgb*>(Image.scanLine(y));

             for (int x = 0; x < wi1; x++)
             {
               *tempLine++ = qRgba(255-qRed(*tempLine),
                                   255-qGreen(*tempLine),
                                   255-qBlue(*tempLine),
                                   qAlpha(*tempLine));
                } // x
        } // y*/
        Image.invertPixels(QImage::InvertRgba);
        pix2=QPixmap::fromImage(Image);
        ui->label_2->setPixmap(pix2.scaled(w2, h2, Qt::KeepAspectRatio));
        pix3=pix2;

        // whiteRight();
        pix3.save("x.png"); // QImage
        mag = imread("x.bmp", CV_8UC1); // Mat
        visibleIdeal=true;
        ui->verticalSlider_6->setValue(0);

        // normalize(mag, mag, 0, 1, CV_MINMAX, CV_32F);
        // clearLayout(ui->verticalLayout_6, true);
        // RightChart3DSurf(mag);

         if (ui->checkBox_3->isChecked()) on_verticalSlider_7_valueChanged(ValSld_7); // строка
}

void MainWindow::on_toolButton_3_clicked()
{  // обратная передача pix3 (отредактированное pix2) на первый экран pix1

    if (visibleRect) {// ui->checkBox->setCheckState(Qt::CheckState(0));
                     pix3=pix2/*&pixCut*/;
                     wi2=wrect; hi2=hrect;  // размеры вырезанного изображения
                     xrect=10; yrect=10; // новый прямоугольник-линза
                     wrect=qCeil(0.2*wi2);
                     hrect=qCeil(0.2*hi2);
                     // ui->checkBox->setCheckState(Qt::CheckState(0));
    } // if

    pix1 = pix3;
    pix2 = pix1;

    ui->label->setPixmap(pix1.scaled(w1, h1, Qt::KeepAspectRatio));

    ui->verticalSlider_5 ->setValue(0);
    ui->verticalSlider_5->setSliderPosition(0);

    wi1=wi2;
    hi1=hi2;
    ImMatrixFill(wi1, hi1, 127); // ??? сделать новые изображения

    SliderPosInit(0);
    ui->spinBox->setValue(0);
    ui->checkBox->setCheckState(Qt::CheckState(0)); // ui->checkBox_3->setChecked(false);  ???
    ui->verticalSlider_7->setMaximum(hi1-1);

    if (ui->checkBox_3->isChecked()) on_verticalSlider_7_valueChanged(ValSld_7); // строка
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{ // поворот
    QImage ImRot;
    int nx, ny;
    const qreal pi = 3.1415926535897932384626433832795;
    QColor color;

    if (ui->checkBox_3->isChecked())
        ui->checkBox_3->setChecked(false);  // ui->checkBox_3->setCheckState(Qt::CheckState(0));

    argRot=arg1;

    QImage Image = pix1.toImage();
    int wi1 = Image.width(); // размеры изображения // ???
    int hi1 = Image.height();

    qreal angle = qreal(arg1);
    qreal rad = pi * angle / 180.0;
    qreal rotateMat[2][2] = {{ qCos(rad),  qSin(rad)},
                             {-qSin(rad),  qCos(rad)}}; // или QMatrix2x2, но думаю и так ясно

    // вычисление размеров результирующего изображения  (координаты 3х углов)
    qreal x1 = qreal (hi1) * rotateMat[1][0];  // sin(rad)
    qreal y1 = qreal (hi1) * rotateMat[0][0];  // cos(rad)
    qreal x2 = qreal (wi1) * rotateMat[0][0] + qreal(hi1) * rotateMat[1][0];
    qreal y2 = qreal (hi1) * rotateMat[1][1] + qreal(wi1) * rotateMat[0][1];
    qreal x3 = qreal (wi1) * rotateMat[1][1];
    qreal y3 = qreal (wi1) * rotateMat[0][1];

    qreal minX = qMin(0.0, qMin(x1, qMin(x2, x3)));
    qreal minY = qMin(0.0, qMin(y1, qMin(y2, y3)));
    qreal maxX = qMax(0.0, qMax(x1, qMax(x2 ,x3)));
    qreal maxY = qMax(0.0, qMax(y1, qMax(y2, y3)));

    int newWi = qCeil(maxX - minX)+0; // +1, т.к. при поповроте используется nx = floor(nxd) и .т.д. ?
    int newHi = qCeil(maxY - minY)+0;

     ImRot = QImage(newWi,newHi, QImage::Format_ARGB32);

     for (int y = 0; y < newHi; y++)
     {
          QRgb *tempLine  = reinterpret_cast<QRgb*>(ImRot.scanLine(y));

          for (int x = 0; x < newWi; x++)
          { // заполнение серым
               *tempLine++ = qRgba(200,
                                   200,
                                   200,
                                   255);
          } // x
      } // y

     // if (sliderPosInit==false) {
         SliderPosInit(0);
         deltRGB_L=0;
         ImC = QImage(newWi, newHi, QImage::Format_ARGB32);
         ImG = QImage(newWi, newHi, QImage::Format_ARGB32);
        // ImS = QImage(newWi, newHi, QImage::Format_ARGB32);
         ImMatrixFill(newWi, newHi, 127);
     // } // if*/

       QApplication::processEvents();

    // нужно чтоб размеры outRGB стали newWidth x newHeight и чем-то залить
    // что-то типа resize(outRGB, newWidth, newHeight), fill(outRGB, Qt::gray);   

    // применяем матрицу поворота
    for(int y = 0; y < hi1; y++) {

        /*for(int x = 0; x < wi1; x++) { // или так
           QColor color = Image.pixelColor(x, y);*/


         QRgb *tempLine  = reinterpret_cast<QRgb*>(Image.scanLine(y)); // или так
        //  #pragma omp parallel for // num_threads(2) // schedule(dynamic)
         for (int x = 0; x < wi1; x++)
         {
           int r = qRed(*tempLine);
           int g = qGreen(*tempLine);
           int b = qBlue(*tempLine);
           int a = qAlpha(*tempLine);

           *tempLine++;

           color.setRgb(r,g,b,a);

           qreal nxd = qreal(x) * rotateMat[0][0] + qreal(y) * rotateMat[1][0] - minX;
           qreal nyd = qreal(x) * rotateMat[0][1] + qreal(y) * rotateMat[1][1] - minY;

           nx = qCeil(nxd);
           ny = qCeil(nyd);
           ImRot.setPixelColor(nx, ny, color);

           nx = qFloor(nxd);
           ny = qFloor(nyd);
           ImRot.setPixelColor(nx, ny, color);

           nx = qRound(nxd);
           ny = qRound(nyd);
           ImRot.setPixelColor(nx, ny, color);
       } // x
    } // y

    pix2=QPixmap::fromImage(ImRot);
    if (aspectRat) ui->label_2->setPixmap(pix2.scaled(w2, h2, Qt::KeepAspectRatio));
        else ui->label_2->setPixmap(pix2.scaled(w2, h2, Qt::KeepAspectRatioByExpanding));
    pix3=pix2;

       /* argRot=arg1;

        QPixmap rotatePixmap(pix2.size());
        // rotatePixmap.fill(Qt::transparent);

        QPainter p(&rotatePixmap);
        // p.setRenderHint(QPainter::Antialiasing); // сглаживание
        // p.setRenderHint(QPainter::SmoothPixmapTransform);
        // p.setRenderHint(QPainter::HighQualityAntialiasing);
        p.translate(rotatePixmap.size().width() / 2, rotatePixmap.size().height() / 2); // центрирует изображение
        p.rotate(argRot); // градус
        p.translate(-rotatePixmap.size().width() / 2, -rotatePixmap.size().height() / 2); // возвращает начало координат в 0
        p.drawPixmap(0, 0, pix2);
        p.end();

        pix2 = rotatePixmap;
        ui->label_2->setPixmap(pix2.scaled(w2, h2, Qt::KeepAspectRatio));
        pix3=pix2;*/
}

void MainWindow::on_checkBox_2_stateChanged(int arg1)
{ // пропорции при повороте
   if (arg1==2) aspectRat=false;
       else aspectRat=true;
   on_spinBox_valueChanged(argRot);      
}

void MainWindow::on_pushButton_clicked()
{ // преобразование цветного рисунка в монохромный серый

    QImage Image = pix2.toImage();

    SliderPosInit(0);
    wi2 = Image.width();
    hi2 = Image.height();
    ImMatrixFill(wi2, hi2, 127);

    for (int y = 0; y < hi2; y++)
    {
         QRgb *tempLine  = reinterpret_cast<QRgb*>(Image.scanLine(y));

         for (int x = 0; x < wi2; x++)
         {
           int r = qRed(*tempLine);
           int g = qGreen(*tempLine);
           int b = qBlue(*tempLine);
           int a = qAlpha(*tempLine);

           int ClMonochrom=qGray(r, g, b);

            *tempLine++ = qRgba(ClMonochrom,
                                ClMonochrom,
                                ClMonochrom,
                                a);
            } // x
    } // y
    pix2 = QPixmap::fromImage(Image);
    ui->label_2->setPixmap(pix2.scaled(w2, h2, Qt::KeepAspectRatio));
    pix3=pix2;
}

void MainWindow::on_verticalSlider_valueChanged(int value)
{ // яркость
     QString str;

    // sliderPosInit=false;

    QApplication::processEvents();

    QImage Image = pix2.toImage();
    wi2 = Image.width();
    hi2 = Image.height();

    StatLabel2->setText("brightness: "+str.number(value));

    for (int y = 0; y < hi2; y++)
    {
         QRgb *tempLine  = reinterpret_cast<QRgb*>(Image.scanLine(y));
         QRgb *deltLineC = reinterpret_cast<QRgb*>(ImC.scanLine(y));
         QRgb *deltLineG = reinterpret_cast<QRgb*>(ImG.scanLine(y));

         // #pragma omp parallel for num_threads(7) shared(value) schedule(dynamic) // private(color) private(valC)
         for (int x = 0; x < wi2; x++)
         {
           int r = qRed(*tempLine)  + value+(qRed(*deltLineC)  -127)+(qRed(*deltLineG) - 127);
           int g = qGreen(*tempLine)+ value+(qGreen(*deltLineC)-127)+(qGreen(*deltLineG)-127);
           int b = qBlue(*tempLine) + value+(qBlue(*deltLineC++)-127)+(qBlue(*deltLineG++)-127);
           int a = qAlpha(*tempLine);

                // *deltLineC++;

                // *deltLineG++;

                *tempLine++ = qRgba(r>255?255 : r<0?0 : r,
                                    g>255?255 : g<0?0 : g,
                                    b>255?255 : b<0?0 : b,
                                    a);
            } // x
    } // y

    deltRGB_L=value; // добавка яркости

    pix3=QPixmap::fromImage(Image);
    ui->label_2->setPixmap(pix3.scaled(w2, h2, Qt::KeepAspectRatio));
}

void MainWindow::on_verticalSlider_2_valueChanged(int value)
{ // контрастность
   qreal contrast;
   QString str;
   int r, g, b;

    // sliderPosInit=false;

    QApplication::processEvents();

    QImage Image = pix2.toImage();
    wi2 = Image.width();
    hi2 = Image.height();

    StatLabel2->setText("contrast: "+str.number(value));
    contrast = (130.0+qreal(value))/130.0;
    // contrast=contrast*contrast;

    for (int y = 0; y < hi2; y++)
    {
            QRgb *tempLine = reinterpret_cast<QRgb*>(Image.scanLine(y));
            QRgb *deltLineC = reinterpret_cast<QRgb*>(ImC.scanLine(y));
            QRgb *deltLineG = reinterpret_cast<QRgb*>(ImG.scanLine(y));

             // QApplication::processEvents();

            // #pragma omp parallel for num_threads(5) shared(y) schedule(dynamic) // private(color) private(valC)
           // #pragma omp parallel for schedule(static) // num_threads(6)
            for (int x = 0; x < wi2; x++)
            {
                int r0 = qRed(*tempLine);
                int g0 = qGreen(*tempLine);
                int b0 = qBlue(*tempLine);
                int a0 = qAlpha(*tempLine);

                r = qCeil(((qreal(r0)/255.0 - 0.5)*contrast + 0.5)*255.0);
                if (g0==r0) g=r;
                    else g = qCeil(((qreal(g0)/255.0 - 0.5)*contrast + 0.5)*255.0);
                if (b0==r0) b=r;
                    else if (b0==g0) b=g;
                             else b = qCeil(((qreal(b0)/255.0 - 0.5)*contrast + 0.5)*255.0);

                int dr = r-r0+127; // добавки контраста
                int dg = g-g0+127;
                int db = b-b0+127;
                *deltLineC++ = qRgba(dr>255?255 : dr<0?0 : dr,
                                     dg>255?255 : dg<0?0 : dg,
                                     db>255?255 : db<0?0 : db,
                                     a0);

                r = r + deltRGB_L+(qRed(*deltLineG) - 127);
                g = g + deltRGB_L+(qGreen(*deltLineG) - 127);
                b = b + deltRGB_L+(qBlue(*deltLineG++) - 127);;

                *tempLine++ = qRgba(r>255?255 : r<0?0 : r,
                                    g>255?255 : g<0?0 : g,
                                    b>255?255 : b<0?0 : b,
                                    a0);
                // *deltLineG++;
            } // x
    } // y
    pix3=QPixmap::fromImage(Image);
    ui->label_2->setPixmap(pix3.scaled(w2, h2, Qt::KeepAspectRatio));
}

void MainWindow::on_verticalSlider_3_valueChanged(int value)
{   // гамма коррекция
    qreal gamma;
    QString str;
    int r, g, b;

    /*qreal val, colorLP, colorLPOld, deltG, colorSP;
    QColor color, deltL, deltC, deltS;;

    QApplication::processEvents();

    Image = pix2.toImage();
    int wi = Image.width();
    int hi = Image.height();

    val = 0.01*(100-value);

    for (int x = 0; x < wi; x++)
    {
            for (int y = 0; y < hi; y++)
            {
                color = Image.pixelColor(x, y);
                colorLPOld = color.lightnessF();                

                colorLP = pow(colorLPOld,val);
                deltG = colorLP - colorLPOld;

                deltL = ImL.pixelColor(x, y);
                deltC = ImC.pixelColor(x, y);
                deltS = ImS.pixelColor(x, y);

                colorLP = colorLP + (deltL.lightnessF()-0.5)+(deltC.lightnessF()-0.5);
                if (colorLP>1.0) colorLP = 1.0;
                if (colorLP<0.0) colorLP = 0.0;

                colorSP = color.hslSaturationF()+(deltS.hsvSaturationF()-0.5);
                if (colorSP>1.0) colorSP = 1.0;
                if (colorSP<0.0) colorSP = 0.0;

                color.setHslF(color.hslHueF(),
                              colorSP,
                              colorLP);
                Image.setPixelColor(x, y, color); // новая гамма коррекция

                // запомнить матрицу изменений гамма коррекции deltG
                if (deltG>0.5) deltG = 0.5;
                if (deltG<-0.5) deltG = -0.5;
                color.setHslF(0.0,0.0,deltG+0.5);
                ImG.setPixelColor(x, y, color);
            }
    }*/

    // sliderPosInit=false;

    QApplication::processEvents();

    QImage Image = pix2.toImage();
    wi2 = Image.width();
    hi2 = Image.height();

    StatLabel2->setText("gamma: "+str.number(value));
    gamma = 0.01*(100.0-value);

    for (int y = 0; y < hi2; y++)
    {
            QRgb *tempLine = reinterpret_cast<QRgb*>(Image.scanLine(y));
            QRgb *deltLineC = reinterpret_cast<QRgb*>(ImC.scanLine(y));
            QRgb *deltLineG = reinterpret_cast<QRgb*>(ImG.scanLine(y));

            // #pragma omp parallel for
            for (int x = 0; x < wi2; x++)
            {
                int r0 = qRed(*tempLine);
                int g0 = qGreen(*tempLine);
                int b0 = qBlue(*tempLine);
                int a0 = qAlpha(*tempLine);

                r = qRound(qPow(qreal(r0)/255.0,gamma)*255.0);
                if (g0==r0) g=r;
                    else g = qRound(qPow(qreal(g0)/255.0,gamma)*255.0);
                if (b0==r0) b=r;
                    else if (b0==g0) b=g;
                             else b = qRound(qPow(qreal(b0)/255.0,gamma)*255.0);

                int dr = r-r0+127; // добавки гаммы-коррекции
                int dg = g-g0+127;
                int db = b-b0+127;
                *deltLineG++ = qRgba(dr>255?255 : dr<0?0 : dr,
                                     dg>255?255 : dg<0?0 : dg,
                                     db>255?255 : db<0?0 : db,
                                     a0);

                r =  r + deltRGB_L+qRed(*deltLineC)- 127;
                g =  g + deltRGB_L+qGreen(*deltLineC)- 127;
                b =  b + deltRGB_L+qBlue(*deltLineC++)- 127;
                *tempLine++ = qRgba(r>255?255 : r<0?0 : r,
                                    g>255?255 : g<0?0 : g,
                                    b>255?255 : b<0?0 : b,
                                    a0);
                // *deltLineC++;
            } // x
    } // y
    pix3=QPixmap::fromImage(Image);
    ui->label_2->setPixmap(pix3.scaled(w2, h2, Qt::KeepAspectRatio));
}

void MainWindow::on_verticalSlider_4_valueChanged(int value)
{ // изменение насыщенности
    /*QColor color, deltL, deltC, deltG;
    qreal deltS, colorSP, colorLP;

    sliderPosInit=false;

    QApplication::processEvents();

    Image = pix2.toImage();
    int wi = Image.width();
    int hi = Image.height();

    for (int x = 0; x < wi; x++)
    {
            for (int y = 0; y < hi; y++)
            {                
                deltS = 0.0075*value;

                color = Image.pixelColor(x, y);
                colorSP = color.hslSaturationF()+deltS;
                if (colorSP>1.0) colorSP = 1.0;
                if (colorSP<0.0) colorSP = 0.0;

                deltL = ImL.pixelColor(x, y);
                deltC = ImC.pixelColor(x, y);
                deltG = ImG.pixelColor(x, y);
                colorLP = color.lightnessF()+(deltL.lightnessF()-0.5)+(deltC.lightnessF()-0.5)+(deltG.lightnessF()-0.5);
                if (colorLP>1.0) colorLP = 1.0;
                if (colorLP<0.0) colorLP = 0.0;

                color.setHslF(color.hslHueF(),
                              colorSP,
                              colorLP);
                Image.setPixelColor(x, y, color); // новая насыщенность

                // запомнить матрицу изменений насыщенности deltS со сдвигом 0.5
                if (deltS>0.5) deltS = 0.5;
                if (deltS<-0.5) deltS = -0.5;
                color.setHslF(0.0,deltS+0.5,0.5);
                ImS.setPixelColor(x, y, color);
            }
    }*/
    pix3=QPixmap::fromImage(Image2);
    ui->label_2->setPixmap(pix3.scaled(w2, h2, Qt::KeepAspectRatio));
}

void MainWindow::intensityMask(int i, int j, int n, /*int nMid,*/ QImage Image, int wi, int hi)
{  //  QColor color;
    int ii, jj;
    int nMid=(n-1)/2;

    /* for (int m = 0; m < n; m++){ // вдоль y
         jj=j-nMid+m;
         if (jj<0) jj=-jj;
         if (jj>hi-1) jj=2*hi-jj-2;
         QRgb *maskLine = reinterpret_cast<QRgb*>(Image.scanLine(jj));
         // QRgb *maskLine = (QRgb*)(Image.scanLine(jj));

         for (int k = 0; k < n; k++){ // вдоль x
              ii=i+k-nMid;
              if (ii<0) ii=-ii;
              if (ii>wi-1) ii=2*wi-ii-2;

              // int r = 0; //qRed(*(maskLine+ii));
              // int g = 111; //qGreen(*(maskLine+ii));
              // int b = 0; // qBlue(*(maskLine+ii));
              // int a = 255; //qAlpha(*maskLine+ii);

              // int r = qRed(maskLine[ii]);
              // int g = qGreen(maskLine[ii]);
              // int b = qBlue(maskLine[ii]);

              //  int r = qRed(Image.scanLine(jj)[ii]);
              //  int g = qGreen(Image.scanLine(jj)[ii]);
              //  int b = qBlue(Image.scanLine(jj)[ii]);

               colMask[k][m] =qGray(r, g, b)/255.0;
          } // k           
    } // m*/

    for (int k = 0; k < n; k++){ // вдоль х (k)    
         ii=i+k-nMid;
         if (ii<0) ii=-ii;
         if (ii>wi-1) ii=2*wi-ii-2;
         // #pragma omp parallel for schedule(dynamic) num_threads(2) shared(ii) private(jj)

         for (int m = 0; m < n; m++){ // вдоль у (m) QColor
              jj=j+m-nMid;
              if (jj<0) jj=-jj;
              if (jj>hi-1) jj=2*hi-jj-2;
              // color = Image.pixelColor(ii, jj);
              // colMask[k][m] = color.lightnessF();
              colMask[k][m] =Image.pixelColor(ii, jj).lightnessF();
             // qreal c0=colMask[k][m];
          } // m
     } // k
}

qreal linearFiltr(int n, qreal C[9][9], qreal H[9][9])
{  // линейный фильтр
   qreal P, SH, Hm;
   // int i, j;

    P = 0.0; SH = 0.0;
    // #pragma omp /*private(P, SH)*/ reduction (+: P, +: SH) parallel num_threads(5) for schedule(dynamic) // shared(i, P, SH)
    // #pragma omp simd collapse(2)

    for (int i = 0; i < n; i++){
         for (int j = 0; j < n; j++){
            Hm = H[i][j];   
            P  = P + C[i][j] * Hm; // C[i][j] - старые элементы, H[i][j] - сглаживающая маска
            SH = SH + Hm;
         } // j
    }  // i
    P = P/SH; // усредненное значение C с весом Hm
   return P;
}

void MainWindow::on_toolButton_4_clicked()
{   // сглаживаение линейным фильтром
    // QColor color;
    QImage ImSm, Image;
    // qreal SmoothLight;
    // int nMid;

      Image = pix1.toImage(); // Image - исходное изображение
      ImSm = Image; // ImSm - будет получено сглаженное изображение

      int wi = Image.width(); // размеры изображения
      int hi = Image.height();

      ImMatrixFill(wi, hi, 127);
      SliderPosInit(0);
      ui->spinBox->setValue(0);      

      // nMid=(nMtr-1)/2;

      StatProgress->setMaximum(wi-1);
      for (int i = 0; i < wi; i++)
      {
         // #pragma omp parallel for schedule(dynamic) num_threads(2) shared(i, Image, ImSm) // !!!
         //  #pragma omp parallel num_threads(2) shared(i, Image, ImSm) // !!
          {
          //  #pragma omp for schedule(dynamic) // !!
            for (int j = 0; j < hi; j++)
            {
               QColor color = Image.pixelColor(i, j);
               intensityMask(i, j, nMtr, /*nMid,*/ Image, wi, hi); // матрица интенсивностей colMask размером nMtr x nMtr

               // ---------------------------------------------------------------------------------------------------
               qreal SmoothLight = linearFiltr(nMtr, colMask, Hm); // получение сглаженного значения

               if (SmoothLight>1.0) SmoothLight = 1.0;
               if (SmoothLight<0.0) SmoothLight = 0.0;

               color.setHslF(color.hslHueF(),
                             color.hslSaturationF(),
                             SmoothLight);

               ImSm.setPixelColor(i, j, color);               
             } // j
          } // parallel
            StatProgress->setValue(i);
       } // i

         /*StatProgress->setMaximum(hi-1);
         int r, g, b;
         for (int j = 0; j < hi; j++)
         {
              // QRgb *tempLine = reinterpret_cast<QRgb*>(Image.scanLine(j));
              QRgb *smoothLine = reinterpret_cast<QRgb*>(ImSm.scanLine(j));

              for (int i = 0; i < wi; i++)
              {
                  // int r = qRed(*tempLine);
                  // int g = qGreen(*tempLine);
                  // int b = qBlue(*tempLine);
                  // int a = qAlpha(*tempLine);

                  intensityMask(i, j, nMtr, nMid, Image, wi, hi); // матрица интенсивностей colMask размером nMtr x nMtr
                  // ------------------------------------------------------------------------------------------
                  SmoothLight = linearFiltr(nMtr, colMask, Hm); // получение сглаженного значения

                  *smoothLine++ = qRgba(r>255?255 : r<0?0 : r,
                                        g>255?255 : g<0?0 : g,
                                        b>255?255 : b<0?0 : b,
                                        255);
                  *smoothLine++;
              } // i
              StatProgress->setValue(j);
         } // j*/

       w2 = ui->label_2->width(); // размеры лейбла 2
       h2 = ui->label_2->height();

       pix2=QPixmap::fromImage(ImSm);
       ui->label_2->setPixmap(pix2.scaled(w2, h2, Qt::KeepAspectRatio));
       pix3=pix2;
       StatProgress->setValue(0);

       if (ui->checkBox_3->isChecked()) on_verticalSlider_7_valueChanged(ValSld_7); // строка
}

qreal medianFiltr(int nMtr, qreal C[9][9])
{   qreal minC, CC, Cs[81]/*, c0, c1, c2, c3, c4, c5, c6, c7, c8*/;
    int i, j, k, pos;

    k=0;
    for (i = 0; i < nMtr; i++){
         // #pragma omp simd reduction(+: k)
         for (j = 0; j < nMtr; j++){
         Cs[k]=C[i][j];
         k=k+1;
         } // j
    } // i

    k=nMtr*nMtr;
     // #pragma omp parallel for
    for (i = 0; i < (k+1)/2; i++){
         minC=Cs[i];
         pos=i;
         // #pragma omp simd reduction(+: k)
         for (j = i+1; j < k; j++){
             if (Cs[j]<minC){
                 minC=Cs[j];
                 pos=j;
             } // if
         } // j
         CC=Cs[i];
         Cs[i]=Cs[pos];
         Cs[pos]=CC;
     } // i
     // CC=minC;
     // c0=Cs[0];  c1=Cs[1]; c2=Cs[2]; c3=Cs[3]; c4=Cs[4]; c5=Cs[5]; c6=Cs[6]; c7=Cs[7]; c8=Cs[8];
     return Cs[(k-1)/2];
}

void MainWindow::SmoothValueMedian(QImage Image, int wi, int hi, int x, int y, int n, QColor color)
{
      QColor colorMedian;

      intensityMask(x, y, n, Image, wi, hi); // матрица интенсивностей colMask размером nMtr x nMtr (5 x 5)
      qreal SmoothLight = medianFiltr(n, colMask); // получение сглаженного значения

      colorMedian.setHslF(color.hslHueF(),
                    color.hslSaturationF(),
                    SmoothLight);

      ImSmMedian.setPixelColor(x, y, colorMedian);
}

void MainWindow::on_toolButton_5_clicked()
{ // сглаживание медианным фильтром
    // QColor color;
    QImage ImSm, Image;
    // qreal SmoothLight;
    // int nMid;

     Image = pix1.toImage(); // Image - исходное изображение из pix1
     ImSm = Image; // ImSm - будет получено сглаженное изображение

     int wi = Image.width(); // размеры изображения
     int hi = Image.height();

     ImMatrixFill(wi, hi, 127);
     SliderPosInit(0);
     ui->spinBox->setValue(0);
     StatProgress->setMaximum(wi-1);

     // int nMid=(nMtr-1)/2;
     for (int i = 0; i < wi; i++)
        {
            // #pragma omp parallel for num_threads(2) schedule(dynamic) shared(Image)
            for (int j = 0; j < hi; j++)
            {
                QColor color = Image.pixelColor(i, j);
                intensityMask(i, j, nMtr, Image, wi, hi); // матрица интенсивностей colMask размером nMtr x nMtr
                // --------------------------------------------------------------------------------------------------
                qreal SmoothLight = medianFiltr(nMtr, colMask); // получение сглаженного значения

                color.setHslF(color.hslHueF(),
                              color.hslSaturationF(),
                              SmoothLight);

                ImSm.setPixelColor(i, j, color);
            } // j
            StatProgress->setValue(i);
        } // i

     w2 = ui->label_2->width(); // размеры лейбла 2
     h2 = ui->label_2->height();

     pix2=QPixmap::fromImage(ImSm);
     ui->label_2->setPixmap(pix2.scaled(w2, h2, Qt::KeepAspectRatio));
     pix3=pix2;
     StatProgress->setValue(0);
     // if (visible) {set_on_Pix_FillRectDraw(2, 0, hi2-6, wi2, 10, 1.0, 0.0, 0.0, 0.3, pix3);}

     if (ui->checkBox_3->isChecked()) on_verticalSlider_7_valueChanged(ValSld_7); // строка
}

void MainWindow::MinMaxMatr(int n, qreal C[9][9])
{   int i, j;
    maxMatr=C[0][0]; minMatr=C[0][0];
    for (i = 0; i < n; i++){
         for (j = 0; j < n; j++){
              qreal Cij=C[i][j];
              if (Cij>maxMatr) maxMatr=Cij;
              if (Cij<minMatr) minMatr=Cij;
         } // j
    } // i
}

void MainWindow::on_toolButton_17_clicked()
{  // адаптивное медианным (Gonsales)
    QImage ImSm, Image;
    QColor color;
    qreal Zmin, Zmax, Zmed, Zxy;
    qreal SmoothLight;
    bool A1B, A2B, A12, B1B, B2B, B12;
   // qreal c0,c1,c2,c3,c4,c5,c6,c7,c8;

    Image = pix1.toImage(); // Image - исходное изображение из pix1
    ImSm = Image; // ImSm - будет получено сглаженное изображение

    int wi = Image.width();
    int hi = Image.height();

    ImMatrixFill(wi, hi, 127);
    SliderPosInit(0);
    ui->spinBox->setValue(0);
    StatProgress->setMaximum(wi-1);

    for (int i = 0; i < wi; i++)
       {
           // #pragma omp parallel for num_threads(2) schedule(dynamic) shared(Image)
           for (int j = 0; j < hi; j++)
           {
               color = Image.pixelColor(i, j);
               Zxy=color.lightnessF();

               int nMtr=1;
               do // cicle
               {
                  nMtr=nMtr+2;
                  intensityMask(i, j, nMtr, Image, wi, hi); // матрица интенсивностей colMask размером nMtr x nMtr

                  MinMaxMatr(nMtr, colMask);
                  Zmax=maxMatr;
                  Zmin=minMatr;
                  Zmed = medianFiltr(nMtr, colMask);

                /*  if ((i==23) && (j==31)){
                      c0=colMask[0][0];
                      c1=colMask[1][0];
                      c2=colMask[2][0];
                      c3=colMask[0][1];
                      c4=colMask[1][1];
                      c5=colMask[2][1];
                      c6=colMask[0][2];
                      c7=colMask[1][2];
                      c8=colMask[2][2];
                      SmoothLight=c0+c1+c2+c3+c4+c5+c6+c7+c8;
                  }*/

                  qreal A1=Zmed-Zmin;
                  qreal A2=Zmed-Zmax;

                  A1B=A1>0.0;
                  A2B=A2<0.0;
                  A12=(A1B && A2B); // !A12 - Zmed-pulse
               }
               while ((nMtr<9) && !A12);
               SmoothLight=Zxy; // =Zmed               
               if (A12) // Modification without if(A12) ???
               {
                 qreal B1=Zxy-Zmin;
                 qreal B2=Zxy-Zmax;
                 B1B=B1>0;
                 B2B=B2<0;
                 B12=(B1B && B2B);
                 if(!B12) SmoothLight=Zmed; // Zxy-pulse
               }              

               color.setHslF(color.hslHueF(),
                             color.hslSaturationF(),
                             SmoothLight);

               ImSm.setPixelColor(i, j, color);
           } // j
           StatProgress->setValue(i);
       } // i

    w2 = ui->label_2->width(); // размеры лейбла 2
    h2 = ui->label_2->height();

    pix2=QPixmap::fromImage(ImSm);
    ui->label_2->setPixmap(pix2.scaled(w2, h2, Qt::KeepAspectRatio));
    pix3=pix2;
    StatProgress->setValue(0);
    if (ui->checkBox_3->isChecked()) on_verticalSlider_7_valueChanged(ValSld_7); // строка
}

void MainWindow::on_toolButton_15_clicked()
{ // адаптивное медианным NEW
    QImage Image/*, ImSm*/;
    QColor color;
    int xk, ym;
    qreal sum1, color0, color1;
    qreal maxSum1;
    int L;    

    w2 = ui->label_2->width(); // размеры лейбла 2
    h2 = ui->label_2->height();

    Image = pix1.toImage(); // Image - исходное изображение из pix1
    ImSmMedian = Image; // ImSm - будет получено сглаженное изображение

    int wi = Image.width();
    int hi = Image.height();

    StatProgress->setMaximum(4);
    // StatProgress->setMaximum(wi-1);
    // StatProgress->setValue(int(wi/20.0));

   /* do // iterrations on L
    {
        Image=ImSmMedian;*/

        maxSum1=0.0; // max сумма приращений яркости 8 ближайших соседей
        for (int x = 0; x < wi; x++)
        {
            for (int y = 0; y < hi; y++)
            {
                color = Image.pixelColor(x, y);
                color0 = color.lightnessF();

                // 8 ближайших соседей
                sum1=0.0;
                for (int k=-1; k<2; k++)
                {
                    xk=x+k;
                    if (xk<0) xk=abs(xk);
                    if (xk>wi-1) xk=2*(wi-1)-xk;

                    for (int m=-1; m<2; m++)
                    {
                        ym=y+m;
                        if (ym<0) ym=abs(ym);
                        if (ym>hi-1) ym=2*(hi-1)-ym;

                         color = Image.pixelColor(xk, ym);
                         color1=color.lightnessF();
                         sum1=sum1+fabs(color0-color1);
                    } // m
                } // k
                if (sum1>maxSum1) maxSum1=sum1;
             } // y
         } // x
         StatProgress->setValue(1);

       // maxSum1 = maxSum1/7.0;
       maxSum1 = 1.0;
       // StatProgress->setMaximum(3);
       // if (maxSum1>4.1) maxSum1=0.8;
       //             else maxSum1=1.0;
       L=0;
       do // iterrations on L
       {
         Image=ImSmMedian;
        // сумма приращений интенсивнстей в каждой точке
        for (int x = 0; x < wi; x++)
        {
            for (int y = 0; y < hi; y++)
            {
                color = Image.pixelColor(x, y);
                color0 = color.lightnessF();

                // 8 ближайших соседей
                sum1=0.0;
                for (int k=-1; k<2; k++)
                {
                    xk=x+k;
                    if (xk<0) xk=abs(xk);
                    if (xk>wi-1) xk=2*(wi-1)-xk;

                    for (int m=-1; m<2; m++)
                    {
                        ym=y+m;
                        if (ym<0) ym=abs(ym);
                        if (ym>hi-1) ym=2*(hi-1)-ym;

                         color = Image.pixelColor(xk, ym);
                         color1=color.lightnessF();
                         sum1=sum1+fabs(color0-color1);
                    } // m
                } // k

                /*if (((L==0) || (L==4) || (L==6)) && (sum1>3.9)) SmoothValueMedian(Image, wi, hi, x, y, 3, color); //  1x1
                if ((L==1) && (sum1>3.4)) SmoothValueMedian(Image, wi, hi, x, y, 3, color); //  1x2
                if ((L==2)&& (sum1>2.9)) SmoothValueMedian(Image, wi, hi, x, y, 3, color); // +2x2
                if (((L==3) || (L==5)) && (sum1>2.4)) SmoothValueMedian(Image, wi, hi, x, y, 3, color); //  2x2*/
                // if ((L==0) && (sum1>2.4)) SmoothValueMedian(Image, wi, hi, x, y, 3, color); // 1x1
                // if ((L==0) && (sum1>3.4)) SmoothValueMedian(Image, wi, hi, x, y, 3, color); // 1x2
                // if ((L==0) && (sum1>2.9)) SmoothValueMedian(Image, wi, hi, x, y, 3, color); // +2x2
                /*if (((L==0) || (L==1)) && (sum1>2.4)) SmoothValueMedian(Image, wi, hi, x, y, 3, color); // 3x3 ideal
                if ((L==2) && (sum1>3.9)) SmoothValueMedian(Image, wi, hi, x, y, 3, color); // 1x1*/

                if (((L==0) || (L==1)) && (sum1>2.0*maxSum1)) SmoothValueMedian(Image, wi, hi, x, y, 3, color); // 3x3 real
                if ((L==2) && (sum1>3.5*maxSum1)) SmoothValueMedian(Image, wi, hi, x, y, 3, color); // 1x1

             } // y
             // StatProgress->setValue(x);
         } // x         
         pix2=QPixmap::fromImage(ImSmMedian);
         ui->label_2->setPixmap(pix2.scaled(w2, h2, Qt::KeepAspectRatio));
         L=L+1;
         StatProgress->setValue(L+1);
       } // L
       while (L<3);

       pix3=pix2;

       StatProgress->setValue(0);

        if (ui->checkBox_3->isChecked()) on_verticalSlider_7_valueChanged(ValSld_7); // строка
}

void MainWindow::on_toolButton_19_clicked()
{ // адаптивное линейным
    QImage ImSm, Image;
    QColor color;
    int xk, ym;
    qreal sum1, sum2, maxSum0, maxSum1, maxSum2, color0, color1;
    int filtrInd, L;

    Image = pix1.toImage(); // Image - исходное изображение из pix1
    ImSm = Image; // ImSm - будет получено сглаженное изображение

    int wi = Image.width();
    int hi = Image.height();


    // for (int L=0; L < 5; L++)
    maxSum0=1.0;
    L=0;
    StatProgress->setMaximum(20);
    do
    {
        Image=ImSm;

        // Максимум суммы приращений интенсивностей
        // StatProgress->setMaximum(wi-1);
        maxSum1=0.0; // max сумма приращений яркости 8 ближайших соседей
        maxSum2=0.0; // еще 12 соседей
        for (int x = 0; x < wi; x++)
        {
            for (int y = 0; y < hi; y++)
            {
                color = Image.pixelColor(x, y);
                color0 = color.lightnessF();

                // 8 ближайших соседей
                sum1=0.0;
                for (int k=-1; k<2; k++)
                {
                    xk=x+k;
                    if (xk<0) xk=abs(xk);
                    if (xk>wi-1) xk=2*(wi-1)-xk;

                    for (int m=-1; m<2; m++)
                    {
                        ym=y+m;
                        if (ym<0) ym=abs(ym);
                        if (ym>hi-1) ym=2*(hi-1)-ym;

                         color = Image.pixelColor(xk, ym);
                         color1=color.lightnessF();
                         sum1=sum1+fabs(color0-color1);
                    } // m
                } // k
                if (sum1>maxSum1) maxSum1=sum1;
                // + 12 соседей соседей
                sum2=0.0;
                // 6 соседей down-up
                for (int k=-1; k<2; k++)
                {
                    xk=x+k;
                    if (xk<0) xk=abs(xk);
                    if (xk>wi-1) xk=2*(wi-1)-xk;
                    // down
                    ym=y-1;
                    if (ym<0) ym=abs(ym);
                    color = Image.pixelColor(xk, ym);
                    color0=color.lightnessF();
                    ym=y-2;
                    if (ym<0) ym=abs(ym);
                    color = Image.pixelColor(xk, ym);
                    color1=color.lightnessF();
                    sum2=sum2+fabs(color0-color1);
                    // up
                    ym=y+1;
                    if (ym>hi-1) ym=2*(hi-1)-ym;
                    color = Image.pixelColor(xk, ym);
                    color0=color.lightnessF();
                    ym=y+2;
                    if (ym>hi-1) ym=2*(hi-1)-ym;
                    color = Image.pixelColor(xk, ym);
                    color1=color.lightnessF();
                    sum2=sum2+fabs(color0-color1);
                } // k
                // 6 соседей left-right
                for (int m=-1; m<2; m++)
                {
                    ym=y+m;
                    if (ym<0) ym=abs(ym);
                    if (ym>hi-1) ym=2*(hi-1)-ym;
                    // left
                    xk=x-1;
                    if (xk<0) xk=abs(xk);
                    color = Image.pixelColor(xk, ym);
                    color0=color.lightnessF();
                    xk=x-2;
                    if (xk<0) xk=abs(xk);
                    color = Image.pixelColor(xk, ym);
                    color1=color.lightnessF();
                    sum2=sum2+fabs(color0-color1);
                    // right
                    xk=x+1;
                    if (xk>wi-1) xk=2*(wi-1)-xk;
                    color = Image.pixelColor(xk, ym);
                    color0=color.lightnessF();
                    xk=x+2;
                    if (xk>wi-1) xk=2*(wi-1)-wi;
                    color = Image.pixelColor(xk, ym);
                    color1=color.lightnessF();
                    sum2=sum2+fabs(color0-color1);
                } // k
                if (sum2>maxSum2) maxSum2=sum2;
             } // y
             // StatProgress->setValue(x);
         } // x
        if (L==0) maxSum0=maxSum1;
         // StatProgress->setValue(0);

        // сумма приращений интенсивнстей в каждой точке
        for (int x = 0; x < wi; x++)
        {
            for (int y = 0; y < hi; y++)
            {
                color = Image.pixelColor(x, y);
                color0 = color.lightnessF();

                // 8 ближайших соседей
                sum1=0.0;
                for (int k=-1; k<2; k++)
                {
                    xk=x+k;
                    if (xk<0) xk=abs(xk);
                    if (xk>wi-1) xk=2*(wi-1)-xk;

                    for (int m=-1; m<2; m++)
                    {
                        ym=y+m;
                        if (ym<0) ym=abs(ym);
                        if (ym>hi-1) ym=2*(hi-1)-ym;

                         color = Image.pixelColor(xk, ym);
                         color1=color.lightnessF();
                         sum1=sum1+fabs(color0-color1);
                    } // m
                } // k
                // + 12 соседей соседей
                sum2=0.0;
                // 6 соседей down-up
                for (int k=-1; k<2; k++)
                {
                    xk=x+k;
                    if (xk<0) xk=abs(xk);
                    if (xk>wi-1) xk=2*(wi-1)-xk;
                    // down
                    ym=y-1;
                    if (ym<0) ym=abs(ym);
                    color = Image.pixelColor(xk, ym);
                    color0=color.lightnessF();
                    ym=y-2;
                    if (ym<0) ym=abs(ym);
                    color = Image.pixelColor(xk, ym);
                    color1=color.lightnessF();
                    sum2=sum2+fabs(color0-color1);
                    // up
                    ym=y+1;
                    if (ym>hi-1) ym=2*(hi-1)-ym;
                    color = Image.pixelColor(xk, ym);
                    color0=color.lightnessF();
                    ym=y+2;
                    if (ym>hi-1) ym=2*(hi-1)-ym;
                    color = Image.pixelColor(xk, ym);
                    color1=color.lightnessF();
                    sum2=sum2+fabs(color0-color1);
                } // k
                // 6 соседей left-right
                for (int m=-1; m<2; m++)
                {
                    ym=y+m;
                    if (ym<0) ym=abs(ym);
                    if (ym>hi-1) ym=2*(hi-1)-ym;
                    // left
                    xk=x-1;
                    if (xk<0) xk=abs(xk);
                    color = Image.pixelColor(xk, ym);
                    color0=color.lightnessF();
                    xk=x-2;
                    if (xk<0) xk=abs(xk);
                    color = Image.pixelColor(xk, ym);
                    color1=color.lightnessF();
                    sum2=sum2+fabs(color0-color1);
                    // right
                    xk=x+1;
                    if (xk>wi-1) xk=2*(wi-1)-xk;
                    color = Image.pixelColor(xk, ym);
                    color0=color.lightnessF();
                    xk=x+2;
                    if (xk>wi-1) xk=2*(wi-1)-wi;
                    color = Image.pixelColor(xk, ym);
                    color1=color.lightnessF();
                    sum2=sum2+fabs(color0-color1);
                } // k
               nMtr=1; filtrInd=0;
                // if (sum1>0.4*maxSum1) {nMtr=3; filtrInd=0;} // median
               if (sum1>2.0) {nMtr=3; filtrInd=0;} // median

              /*  nMtr=1; filtrInd=1;
                if (sum1<0.2*maxSum1){
                  if (sum2>0.8*maxSum2) {nMtr=3; filtrInd=1; ui->verticalSlider_5->setValue(1);} // linear
                      else if (sum2>0.5*maxSum2) {nMtr=5; filtrInd=1; ui->verticalSlider_5->setValue(2);} // linear
                               else if (sum2>0.2*maxSum2) {nMtr=7; filtrInd=1; ui->verticalSlider_5->setValue(3);} // linear
                                        else {nMtr=9; filtrInd=1; ui->verticalSlider_5->setValue(4);}
                }*/

                // int nMid=(nMtr-1)/2;
                intensityMask(x, y, nMtr, /*nMid,*/ Image, wi, hi); // матрица интенсивностей colMask размером nMtr x nMtr
                // --------------------------------------------------------------------------------------------------
                qreal SmoothLight;
                if (filtrInd==0) SmoothLight = medianFiltr(nMtr, colMask); // получение сглаженного значения
                            else SmoothLight = linearFiltr(nMtr, colMask, Hm);

                color.setHslF(color.hslHueF(),
                              color.hslSaturationF(),
                              SmoothLight);

                ImSm.setPixelColor(x, y, color);
             } // y
             // StatProgress->setValue(x);
         } // x
         // StatProgress->setValue(0);
         L=L+1;
         StatProgress->setValue(L);
      } // L
      while (maxSum1/maxSum0>0.5 && ((maxSum1>2.0) && (L<1))); // L<???

      w2 = ui->label_2->width(); // размеры лейбла 2
      h2 = ui->label_2->height();

      pix2=QPixmap::fromImage(ImSm);
      ui->label_2->setPixmap(pix2.scaled(w2, h2, Qt::KeepAspectRatio));
      pix3=pix2;

      StatProgress->setValue(0);
}

void MainWindow::on_toolButton_6_clicked()
{ // лапласиан
    QColor color;
    QImage ImSm, Image;
    qreal SmoothLight;
   //  int nMid;

    Image = pix1.toImage(); // Image - исходное изображение
    ImSm = Image; // ImSm - будет получено сглаженное изображение

    int wi = Image.width(); // размеры изображения
    int hi = Image.height();

    ImMatrixFill(wi, hi, 127);
    SliderPosInit(0);
    ui->spinBox->setValue(0);
    StatProgress->setMaximum(wi-1);

    // nMid=(nRtr-1)/2;
    for (int i = 0; i < wi; i++)
    {
          for (int j = 0; j < hi; j++)
          {
             color = Image.pixelColor(i, j);
             intensityMask(i, j, nRtr, /*nMid,*/ Image, wi, hi); // матрица интенсивностей colMask размером nRtr x nRtr
             // --------------------------------------------------------------------------------------------------
             SmoothLight = linearFiltr(nRtr, colMask, Hr); // получение сглаженного значения

             if (SmoothLight>1.0) SmoothLight = 1.0;
             if (SmoothLight<0.0) SmoothLight = 0.0;

             color.setHslF(color.hslHueF(),
                           color.hslSaturationF(),
                           SmoothLight);

             ImSm.setPixelColor(i, j, color);
          } // j
          StatProgress->setValue(i);
     } // i

     w2 = ui->label_2->width(); // размеры лейбла 2
     h2 = ui->label_2->height();

     pix2=QPixmap::fromImage(ImSm);
     ui->label_2->setPixmap(pix2.scaled(w2, h2, Qt::KeepAspectRatio));
     pix3=pix2;
     StatProgress->setValue(0);     
     if (ui->checkBox_3->isChecked()) on_verticalSlider_7_valueChanged(ValSld_7); // строка
}

void MainWindow::on_verticalSlider_5_valueChanged(int value)
{   // маски
    switch (value)
    {case 0:
               nMtr=1; Hm[0][0]=1.0;
               nRtr=1; Hr[0][0]=1.0;

               StatLabel2->setText(" ");
               break;

     case 1:   nMtr=3;
               Hm[0][0]=1.0;   Hm[0][1]=2.0;  Hm[0][2]=1.0;
               Hm[1][0]=2.0;   Hm[1][1]=4.0;  Hm[1][2]=2.0;
               Hm[2][0]=1.0;   Hm[2][1]=2.0;  Hm[2][2]=1.0;

               nRtr=5;
               Hr[0][0]=0.0;      Hr[0][1]=0.0;      Hr[0][2]=1.0/12.0; Hr[0][3]=0.0;      Hr[0][4]=0.0;
               Hr[1][0]=0.0;      Hr[1][1]=0.0;      Hr[1][2]=-4.0/3.0; Hr[1][3]=0.0;      Hr[1][4]=0.0;
               Hr[2][0]=1.0/12.0; Hr[2][1]=-4.0/3.0; Hr[2][2]=11.0;     Hr[2][3]=-4.0/3.0; Hr[2][4]=1.0/12.0;
               Hr[3][0]=0.0;      Hr[3][1]=0.0;      Hr[3][2]=-4.0/3.0; Hr[3][3]=0.0;      Hr[3][4]=0.0;
               Hr[4][0]=0.0;      Hr[4][1]=0.0;      Hr[4][2]=1.0/12.0; Hr[4][3]=0.0;      Hr[4][4]=0.0;

               StatLabel2->setText("3x3");
               break;


     case 2:   nMtr=5;
               Hm[0][0]=1.0;   Hm[0][1]=2.0;  Hm[0][2]=1.0;  Hm[0][3]=2.0;   Hm[0][4]=1.0;
               Hm[1][0]=1.0;   Hm[1][1]=3.0;  Hm[1][2]=4.0;  Hm[1][3]=3.0;   Hm[1][4]=1.0;
               Hm[2][0]=1.0;   Hm[2][1]=4.0;  Hm[2][2]=6.0;  Hm[2][3]=4.0;   Hm[2][4]=1.0;
               Hm[3][0]=1.0;   Hm[3][1]=3.0;  Hm[3][2]=4.0;  Hm[3][3]=3.0;   Hm[3][4]=1.0;
               Hm[4][0]=1.0;   Hm[4][1]=2.0;  Hm[4][2]=1.0;  Hm[4][3]=2.0;   Hm[4][4]=1.0;

               nRtr=5;
               Hr[0][0]=1.0/12.0; Hr[0][1]=0.0;      Hr[0][2]=1.0/12.0; Hr[0][3]=0.0;      Hr[0][4]=1.0/12.0;
               Hr[1][0]=0.0;      Hr[1][1]=-4.0/3.0; Hr[1][2]=-4.0/3.0; Hr[1][3]=-4.0/3.0; Hr[1][4]=0.0;
               Hr[2][0]=1.0/12.0; Hr[2][1]=-4.0/3.0; Hr[2][2]=21.0;     Hr[2][3]=-4.0/3.0; Hr[2][4]=1.0/12.0;
               Hr[3][0]=0.0;      Hr[3][1]=-4.0/3.0; Hr[3][2]=-4.0/3.0; Hr[3][3]=-4.0/3.0; Hr[3][4]=0.0;
               Hr[4][0]=1.0/12.0; Hr[4][1]=0.0;      Hr[4][2]=1.0/12.0; Hr[4][3]=0.0;      Hr[4][4]=1.0/12.0;

               StatLabel2->setText("5x5");
               break;

     case 3:   nMtr=7;
               Hm[0][0]=1.0;   Hm[0][1]=1.0;  Hm[0][2]=1.0;  Hm[0][3]=1.0;   Hm[0][4]=1.0;  Hm[0][5]=1.0;   Hm[0][6]=1.0;
               Hm[1][0]=1.0;   Hm[1][1]=1.0;  Hm[1][2]=2.0;  Hm[1][3]=4.0;   Hm[1][4]=2.0;  Hm[1][5]=1.0;   Hm[1][6]=1.0;
               Hm[2][0]=1.0;   Hm[2][1]=3.0;  Hm[2][2]=5.0;  Hm[2][3]=6.0;   Hm[2][4]=5.0;  Hm[2][5]=3.0;   Hm[2][6]=1.0;
               Hm[3][0]=1.0;   Hm[3][1]=4.0;  Hm[3][2]=6.0;  Hm[3][3]=8.0;   Hm[3][4]=6.0;  Hm[3][5]=4.0;   Hm[3][6]=1.0;
               Hm[4][0]=1.0;   Hm[4][1]=3.0;  Hm[4][2]=5.0;  Hm[4][3]=6.0;   Hm[4][4]=5.0;  Hm[4][5]=3.0;   Hm[4][6]=1.0;
               Hm[5][0]=1.0;   Hm[5][1]=1.0;  Hm[5][2]=2.0;  Hm[5][3]=4.0;   Hm[5][4]=2.0;  Hm[5][5]=1.0;   Hm[5][6]=1.0;
               Hm[6][0]=1.0;   Hm[6][1]=1.0;  Hm[6][2]=1.0;  Hm[6][3]=1.0;   Hm[6][4]=1.0;  Hm[6][5]=1.0;   Hm[6][6]=1.0;

               nRtr=3;
               Hr[0][0]=0.0;   Hr[0][1]=-1.0; Hr[0][2]=0.0;
               Hr[1][0]=-1.0;  Hr[1][1]=5.0;  Hr[1][2]=-1.0;
               Hr[2][0]=0.0;   Hr[2][1]=-1.0; Hr[2][2]=0.0;

               StatLabel2->setText("7x7");
               break;

     case 4:   nMtr=9;
               for (int i = 0; i < nMtr; i++){
               for (int j = 0; j < nMtr; j++)
               {Hm[i][j]=1.0;}}

               nRtr=3;
               Hr[0][0]=-1.0;   Hr[0][1]=-1.0; Hr[0][2]=-1.0;
               Hr[1][0]=-1.0;   Hr[1][1]=9.0;  Hr[1][2]=-1.0;
               Hr[2][0]=-1.0;   Hr[2][1]=-1.0; Hr[2][2]=-1.0;

               StatLabel2->setText("9x9");
               break;

    } // value
}

/*void MainWindow::setAAA(int &A1, int &A2)
{
    A1=A2;
}*/

/*void MainWindow::getPixs(QPixmap &pixOld, QPixmap &pixNew)
{
    pixOld=pix1;
    pixNew=pix1_5;
}*/

 /*void  MainWindow::getAA(int &A)
{
 A=AAA;
 }
*/

// int MainWindow::getA(int AAA) {return AAA;}

// QPixmap MainWindow::getPixOld(QPixmap &pixOld) {pixOld=pix1; return pixOld;}

// QPixmap MainWindow::getPixNew() {return pix1_5;}


void MainWindow::set_on_Pix_FillRectDraw(int lbl, int x1, int y1, int x2, int y2, qreal r, qreal g, qreal b, qreal t, QPixmap pixDown)
{
    QColor color;
    QPixmap pixUp;

    // lbl=1 рисование прямоугольника и узкого прямоугольника (строки) на label
    // lbl=2 рисование узкого прямоугольника (строки) на label_2

    if (lbl==1) {ui->label->setPixmap(pixDown.scaled(w1, h1, Qt::KeepAspectRatio));} // нижний слой
           else {ui->label_2->setPixmap(pixDown.scaled(w2, h2, Qt::KeepAspectRatio));} // нижний слой

    pixUp=pixDown;

    QPainter *painter = new QPainter(&pixUp); // так
    // QPainter painter(&pixUp); // или так
    QRect rectangle(x1, y1, x2, y2);
   // painter->setPen(QPen(Qt::yellow, 1, Qt::SolidLine, Qt::FlatCap));
   // painter->drawRect(rectangle);
    color.setRgbF(r, g, b, t);
    painter->fillRect(rectangle, color);
    update(rectangle);
    if (lbl==1) {ui->label->setPixmap(pixUp.scaled(w1, h1, Qt::KeepAspectRatio));} // верхний слой (с прямоугольником)
           else {ui->label_2->setPixmap(pixUp.scaled(w2, h2, Qt::KeepAspectRatio));} // верхний слой (с прямоугольником)
    painter->end();
}

void MainWindow::cutImage(int x1, int y1, int x2, int y2)
{// увеличенное изображение на label2
  // QPixmap pixCut;

  QRect rectangle(x1, y1, x2, y2);
  pixCut=(pix1).copy(rectangle); // pixCut
  ui->label_2->setPixmap(pixCut.scaled(w2, h2, Qt::KeepAspectRatio));
  pix2=pixCut; 
}

void MainWindow::on_checkBox_stateChanged(int arg1)
{// просмотр области

    ui->checkBox_3->setChecked(false);
    ui->toolButton_12->setEnabled(false);
    ui->toolButton_13->setEnabled(false);

    SliderPosInit(0); // ???
    ImMatrixFill(wi1, hi1, 127);
    ui->spinBox->setValue(0);

    // argRect=arg1;
    if (arg1==2) {visibleRect=true;
                  set_on_Pix_FillRectDraw(1, xrect, yrect, wrect, hrect, 1.0, 1.0, 0.0, 0.4, pix1);
                  cutImage(xrect, yrect, wrect, hrect);
    }
    else {visibleRect=false;
          pix2=pix1;
          ui->label->setPixmap(pix1.scaled(w1, h1, Qt::KeepAspectRatio));
          ui->label_2->setPixmap(pix2.scaled(w2, h2, Qt::KeepAspectRatio));
    }
    // QApplication::processEvents();
}

void MainWindow::mouseDoubleClickEvent(QMouseEvent *me)
{
    int x0=ui->label_2->x();
    int y0=ui->mainToolBar->y()+ui->mainToolBar->height() + ui->label_2->y();
    int x1=x0+ui->label_2->width();
    int y1=y0+ui->label_2->height();

    if(((me->x() > x0)&&(me->x() < x1))&&((me->y() > y0)&&(me->y() < y1)))
    {
        pix3.save("x.png"); // QImage
        Mat img = imread("x.png", CV_8UC1); // Mat

        namedWindow("Proccesed", 0);
        // resizeWindow("Proccesed", 1450, 950);
        imshow("Proccesed", img);
    }
}

void MainWindow::mousePressEvent(QMouseEvent* pe)
{
    if (visibleRect)
    {
      // начало координат на label
      int x0=ui->label->x();
      int y0=ui->mainToolBar->y() + ui->mainToolBar->height() + ui->label->y();

      // pe - координаты мыши
      int x = pe->x()- x0;
      int y = pe->y()- y0;

      qreal xq=qreal(x)*qMax(kw1,kh1);
      qreal yq=qreal(y)*qMax(kw1,kh1);

      // if(((x > 0) && (x < w1)) && ((y > 0) && (y < h1)))
      {  if (((xq > qreal(xrect)) && (xq < qreal(xrect+wrect))) && ((yq > qreal(yrect)) && (yq < qreal(yrect+hrect))))
        {   mouseInRect = true;
            dltX=/*qMax(kw1,kh1)*qreal(x)*/xq - qreal(xrect); dltY=/*qMax(kw1,kh1)*qreal(y)*/yq - qreal(yrect);
        }
        else mouseInRect = false;
      }
      /*else mouseInRect = false;*/
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *me)
{
    if (visibleRect)
    {      
       int x0=ui->label->x();
       int y0=ui->mainToolBar->y()+ui->mainToolBar->height() + ui->label->y();

       int x = me->x()- x0;
       int y = me->y()- y0;
       if (mouseInRect)
          {
           // if (x>xrect) {this->setCursor(Qt::SizeFDiagCursor);}
           qreal xq=qreal(x)*qMax(kw1,kh1); xrect = qCeil(xq - dltX);
           qreal yq=qreal(y)*qMax(kw1,kh1); yrect = qCeil(yq - dltY);
           set_on_Pix_FillRectDraw(1, xrect, yrect, wrect, hrect, 1.0, 1.0, 0.0, 0.4, pix1);
           cutImage(xrect, yrect, wrect, hrect);
          }
    }
} // mouseMove

void MainWindow::keyPressEvent(QKeyEvent *event)
{   
    if (event->key()==Qt::Key_Control) keyCtrl=true;  //event->key() - целочисленный код клавиши
    if (event->key()==Qt::Key_Shift) keyShift=true;
}

void MainWindow::keyReleaseEvent(QKeyEvent *event)
{   
    if (event->key()==Qt::Key_Control) keyCtrl=false;  //event->key() - целочисленный код клавиши
    if (event->key()==Qt::Key_Shift) keyShift=false;
}

void MainWindow::wheelEvent(QWheelEvent *we)
{
    // QKeyEvent *ev;

    if (visibleRect /*&& mouseInL1*/)
    {
        QPoint nAngle = we->angleDelta();
        if (!nAngle.isNull()){ // keyPressEvent(ev);
            if (keyCtrl) {dwrect = qCeil(qreal(wi1)/100.0); dhrect = qCeil (qreal(hi1)/100.0);}
                else if (keyShift) {dwrect = qCeil (qreal(wi1)/100.0); dhrect = 0;}
                         else {dwrect=1; dhrect=1;}
            if (nAngle.y()>0)
               {wrect=wrect+dwrect; hrect=hrect+dhrect;}
                         else {wrect=wrect-dwrect; hrect=hrect-dhrect;}
            set_on_Pix_FillRectDraw(1, xrect, yrect, wrect, hrect, 1.0, 1.0, 0.0, 0.4, pix1);
            cutImage(xrect, yrect, wrect, hrect);
        }
    }
   // event->accept();
}

void MainWindow::on_action_Exit_triggered()
{
    close();
}

void MainWindow::getHistogramm(QPixmap pix)
{
    QImage Image = pix.toImage();
    int wi = Image.width();
    int hi = Image.height();

    for (int k = 0; k <nHist; k++)
    {
       Yh[k]=0.0;
    }   

    StatProgress->setMaximum(wi-1);

    for (int x = 0; x < wi; x++)
        {
            for (int y = 0; y < hi; y++)
            {
                QColor color = Image.pixelColor(x, y);
                int lght = color.lightness();

                for (int k = 0; k <nHist; k++)
                {
                    if (lght==k)
                    {
                      Yh[k]=Yh[k]+1.0;
                      // if ((k=100) && (clr==1.0)) {Yh[k]=Yh[k]+1.0;}
                    }
                } // k
             } // y
             StatProgress->setValue(x);
         } // x

    qreal Ymax = 0.0;
    for (int k = 0; k < nHist; k++) {if (Yh[k]>Ymax) Ymax = Yh[k];} // Ymax
    for (int k = 0; k < nHist; k++) {YhNorm[k] = Yh[k]/Ymax;} // нормировка на 1
    StatProgress->setValue(0);
}

void MainWindow::clearLayout(QLayout* layout, bool deleteWidgets)
{
        while (QLayoutItem* item = layout->takeAt(0))
        {
            if (deleteWidgets)
            {
                if (QWidget* widget = item->widget())
                    delete widget;
            }
            if (QLayout* childLayout = item->layout())
                clearLayout(childLayout, deleteWidgets);
            delete item;
        }
}

void MainWindow::on_toolButton_8_clicked()
{ // гистограмма

    ui->checkBox->setChecked(false);
    ui->checkBox_3->setChecked(false);
    ui->toolButton_12->setChecked(false);
    ui->toolButton_13->setChecked(false);
    ui->toolButton_12->setEnabled(false);
    ui->toolButton_13->setEnabled(false);

    getHistogramm(pix1);

    QBarSet *set0 = new QBarSet("");
    set0->setPen(QPen(Qt::yellow, 1, Qt::SolidLine, Qt::FlatCap));
    for (int k = 0; k < nHist; k++)
    {
        set0->append(YhNorm[k]);
    }

    QBarSeries* series = new QBarSeries();   // Создать класс QLineSeries производный от QXYSeries
    series->append(set0);

    QChart *chart = new QChart();
    chart->legend()->hide();
    chart->setTitle("Image BarChart");
    chart->addSeries(series);
    // chart->createDefaultAxes();

    // 0X
    QStringList categories;
    categories << "Black" << "Dark Gray" << "Gray" << "Light Gray" << "White";

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    // series->attachAxis(axisX);

    // 0Y
    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0.0,1.0);
    chart->addAxis(axisY, Qt::AlignLeft);
    // series->attachAxis(axisY);

    QChartView *myChart = new QChartView(chart);
    myChart->setRenderHint(QPainter::Antialiasing);

    clearLayout(ui->verticalLayout_5, true);
    ui->verticalLayout_5->addWidget(myChart);

    on_toolButton_11_clicked();

     /*QPainter *painter = new QPainter(myChart);
    painter->setPen(QPen(Qt::red, 1, Qt::SolidLine, Qt::FlatCap));
    QRect rectangle(10, 10, 100, 100);
    painter->drawRect(rectangle);
    QColor color;
    color.setRgbF(1.0, 0.0, 0.0, 0.05);
    painter->fillRect(rectangle, color);
    update(rectangle);

    ui->verticalLayout_5->addWidget(myChart);*/

    // ui->verticalLayout_6->addWidget(myChart);

     // setCentralWidget(myChart);

    /*int x2 = ui->label_4->width();
    int y2 =  ui->label_4->height();
    pix00 = chartView->grab();
    ui->label_4->setPixmap(pix00.scaled(x2,y2, Qt::IgnoreAspectRatio));*/

    // QPicture *pic;
    // pic = myChart->grab();
    // ui->label_4->setPicture(*pic);
}

void MainWindow::on_toolButton_11_clicked()
{ // эквализация
    qreal lghtF;
    QColor color;
    int lrandom=nHist;

    QImage Image = pix1.toImage(); // ???

    qreal nsum = wi1*hi1;

    StatProgress->setMaximum(wi1-1);

    for (int x = 0; x < wi1; x++)
        {
          for (int y = 0; y < hi1; y++)
                {
                color = Image.pixelColor(x, y);
                int lght = color.lightness();

                if (lght == nHist-1) {lrandom = lrandom - 1;
                                      color.setHsl(color.hslHue(), color.hslSaturation(), lrandom); // если белый цвет
                                      if (lrandom == nHist-3) {lrandom=nHist;}
                }
                else {
                     int k=0; qreal sum=0.0;
                     do
                       {sum=sum+Yh[k];
                        k++;
                       }
                     while (k<=lght);

                     lghtF = sum/nsum; // новая яркость
                     if (lghtF>1.0)lghtF=1.0;
                     color.setHslF(color.hslHueF(), color.hslSaturationF(), lghtF);
                 }
                 Image.setPixelColor(x, y, color); // точка с новой яркостью
              } // y
              StatProgress->setValue(x);
         } // x
       pix2=QPixmap::fromImage(Image);
       ui->label_2->setPixmap(pix2.scaled(w2, h2, Qt::KeepAspectRatio));
       pix3=pix2;
       StatProgress->setValue(0);

       getHistogramm(pix2);

       QBarSet *set0 = new QBarSet("");
       set0->setPen(QPen(Qt::yellow, 1, Qt::SolidLine, Qt::FlatCap));
        for (int k = 0; k < nHist; k++)
        {
            set0->append(YhNorm[k]);
        }

        QBarSeries* series = new QBarSeries();   // Создать класс QLineSeries производный от QXYSeries
        series->append(set0);

        QChart *chart = new QChart();
        chart->legend()->hide();
        chart->setTitle("Equalized BarChart");
        chart->addSeries(series);
        // chart->createDefaultAxes();

        // 0X
        QStringList categories;
        categories << "Black" << "Dark Gray" << "Gray" << "Light Gray" << "White";

        QBarCategoryAxis *axisX = new QBarCategoryAxis();
        axisX->append(categories);
        chart->addAxis(axisX, Qt::AlignBottom);
        // series->attachAxis(axisX);

        // 0Y
        QValueAxis *axisY = new QValueAxis();
        axisY->setRange(0.0,1.0);
        chart->addAxis(axisY, Qt::AlignLeft);
        // series->attachAxis(axisY);

        QChartView *myChart = new QChartView(chart);
        myChart->setRenderHint(QPainter::Antialiasing);

        clearLayout(ui->verticalLayout_6, true);
        ui->verticalLayout_6->addWidget(myChart);
}

void MainWindow::on_checkBox_3_stateChanged(int arg1)
{   // вкл строку интенсивности
    int x, y, wi, hi;
    QString str;

    if (arg1==2) // вкл
        {      visibleLine=true;
               ui->checkBox->setChecked(false);
               if (ui->checkBox_2->isChecked()) ui->checkBox_2->setChecked(false);

               ui->toolButton_12->setChecked(false);
               ui->toolButton_13->setChecked(false);
               ui->toolButton_12->setEnabled(false);
               ui->toolButton_13->setEnabled(false);
               ui->verticalSlider_7->setTickInterval(qCeil(ui->verticalSlider_7->height()/10.0));

                // left chart
                QImage Image = pix1.toImage();
                wi = Image.width();
                hi = Image.height();

                // int value=0;
                set_on_Pix_FillRectDraw(1, 0, hi-6-ValSld_7, wi, 10, 0.0, 0.0, 1.0, 0.3, pix1);

                series1 = new QLineSeries();
                series1->setPen(QPen(Qt::blue, 1, Qt::SolidLine));
                y=hi-1-ValSld_7;
                StatLabel1->setText("Y: "+str.number(ValSld_7));
                for (x = 0; x < wi; x++)
                {
                  QColor color = Image.pixelColor(x, y);
                  qreal xs=qreal(x) / qreal(wi);
                  qreal ys=color.lightnessF();
                  series1->append(xs, ys);
                }
                chart1 = new QChart();
                chart1->legend()->hide();
                chart1->addSeries(series1);
                chart1->createDefaultAxes();
                chart1->setTitle("Brightness");
                chart1->axisY()->setMin(0.0);
                chart1->axisY()->setMax(1.0);

                QChartView *myChart1 = new QChartView(chart1);
                myChart1->setRenderHint(QPainter::Antialiasing);

                // right chart
                Image = pix3.toImage();
                wi2 = Image.width();
                hi2 = Image.height();
                if ((wi==wi2)&&(hi==hi2))
                {
                    set_on_Pix_FillRectDraw(2, 0, hi-6-ValSld_7, wi, 10, 1.0, 0.0, 0.0, 0.3, pix3);

                    series2 = new QLineSeries();
                    series2->setPen(QPen(Qt::red, 1, Qt::SolidLine));
                    y=hi-1-ValSld_7;
                    for (int x = 0; x < wi; x++)
                    {
                      QColor color = Image.pixelColor(x, y);
                      qreal xs=qreal(x) / qreal(wi);
                      qreal ys=color.lightnessF();
                      series2->append(xs, ys);
                    }
                    chart2 = new QChart();
                    chart2->legend()->hide();
                    chart2->addSeries(series2);
                    chart2->createDefaultAxes();
                    chart2->setTitle("After Proccessing");
                    chart2->axisY()->setMin(0.0);
                    chart2->axisY()->setMax(1.0);

                    QChartView *myChart2 = new QChartView(chart2);
                    myChart2->setRenderHint(QPainter::Antialiasing);

                    // charts on layouts
                    clearLayout(ui->verticalLayout_6, true);
                    ui->verticalLayout_6->addWidget(myChart2);
                } // wi==wi2

                clearLayout(ui->verticalLayout_5, true);
                ui->verticalLayout_5->addWidget(myChart1);
            } // visible
            else {visibleLine=false; // выкл
                  StatLabel1->setText(" ");
                  // clearLayout(ui->verticalLayout_5, true);
                  whiteLeft();
                  ui->label -> setPixmap(pix1.scaled(w1, h1, Qt::KeepAspectRatio));
                  // clearLayout(ui->verticalLayout_6, true);
                  whiteRight();
                  ui->label_2->setPixmap(pix3.scaled(w2, h2, Qt::KeepAspectRatio)); // ??? pix2
                  } // visible=false

     ui->verticalSlider_7->setVisible(visibleLine);
}

qreal Dispersion(qreal ysArr[4000], int wi)
{   int x;
    qreal sumY, sumY2;
    sumY = 0.0;
    for (x = 0; x < wi; x++)
    {
        sumY = sumY + ysArr[x];
    }
    sumY = sumY/qreal(wi);
    sumY2 = 0.0;
    for (x = 0; x < wi; x++)
    {
        sumY2 = sumY2 + pow(sumY - ysArr[x],2);
    }
    sumY2 = sumY2/qreal(wi);
    return sqrt(sumY2);
}

void MainWindow::on_verticalSlider_7_valueChanged(int value)
{ // перемещение строки интенсивностей
     int x, y, wi, hi, wi2, hi2;
     QString str;
     qreal disp, ysArr[4000];

     if (visibleLine)
     {   // left chart
         ValSld_7 = value;

         QImage Image = pix1.toImage();
         wi = Image.width();
         hi = Image.height();         

         set_on_Pix_FillRectDraw(1, 0, hi-6-value, wi, 10, 0.0, 0.0, 1.0, 0.3, pix1);

         series1->clear();
         chart1->removeSeries(series1);

         // series1 = new QLineSeries();
         // series1->setPen(QPen(Qt::blue, 1, Qt::SolidLine));
         y=hi-1-value;       
         // StatLabel1->setText("Y: "+str.number(value));

        /* for (x = 0; x < wi; x++)
         {
           QColor color = Image.pixelColor(x, y);
           qreal xs=qreal(x) / qreal (wi);
           qreal ys=color.lightnessF();
           series1->append(xs, ys);
         }*/

         QRgb *tempLine  = reinterpret_cast<QRgb*>(Image.scanLine(y));
         for (x = 0; x < wi; x++)
         {
           int r = qRed(*tempLine);
           int g = qGreen(*tempLine);
           int b = qBlue(*tempLine++);
           // int a = qAlpha(*tempLine);
           qreal xs=qreal(x) / qreal (wi);
           qreal ys=qreal(qGray(r, g, b))/255.0;
           series1->append(xs, ys);
           ysArr[x] = ys;
           // *tempLine++;
          } // x
         disp = Dispersion(ysArr,wi);
         StatLabel1->setText("Y: "+str.number(value)+" S: "+str.number(disp));

         chart1->addSeries(series1);
         chart1->createDefaultAxes();
         chart1->axisY()->setMin(0.0);
         chart1->axisY()->setMax(1.0);

         // right chart
         Image = pix3.toImage();
         wi2 = Image.width();
         hi2 = Image.height();
         if ((wi==wi2)&&(hi==hi2))
         {
             set_on_Pix_FillRectDraw(2, 0, hi-6-value, wi, 10, 1.0, 0.0, 0.0, 0.3, pix3);

             series2->clear();
             chart2->removeSeries(series2);

             y=hi-1-value;
            /* for (int x = 0; x < wi; x++)
             {
               QColor color = Image.pixelColor(x, y);
               qreal xs= qreal(x) / qreal(wi);
               qreal ys=color.lightnessF();
               series2->append(xs, ys);
              }*/

             QRgb *tempLine  = reinterpret_cast<QRgb*>(Image.scanLine(y));
             for (x = 0; x < wi; x++)
             {
               int r = qRed(*tempLine);
               int g = qGreen(*tempLine);
               int b = qBlue(*tempLine++);

               qreal xs=qreal(x) / qreal (wi);
               qreal ys=qreal(qGray(r, g, b))/255.0;
               series2->append(xs, ys);
               ysArr[x] = ys;
               // *tempLine++;
              } // x
              disp = Dispersion(ysArr,wi);
              StatLabel2->setText("S: "+str.number(disp));

              chart2->addSeries(series2);
              chart2->createDefaultAxes();
              chart2->axisY()->setMin(0.0);
              chart2->axisY()->setMax(1.0);
           } // if wi=wi2
     } // if visble
}

void MainWindow::DFT()
{    Mat img;

     // img = imread("D:/TRUBITSYN/Study_C++/ImagePro/Images/Micro2.png", CV_8UC1);
    // img = imread(mFileName.toStdString().c_str(), CV_8UC1);
    // cvtColor(img, img, CV_BGRA2GRAY);

       // Запись и чтение
       pix1.save("x.png"); // QImage
       img = imread("x.png", CV_8UC1); // Mat

     // QImage Im = pix1.toImage();
     // img.create(Im.height(),Im.width(),CV_8UC1);

    /*QImage Im = pix1.toImage();
    QPixelFormat pixFormat=Im.pixelFormat();
    Mat img(Im.height(),Im.width(),CV_8UC(pixFormat.channelCount()));
    for (int i=0; i<Im.width(); i++)
    for (int j=0; j<Im.height(); j++)
    {
     img.at<unsigned int>(j,i)=Im.pixel(i,j);
    }


    namedWindow("Proccesed", 0 );
    resizeWindow("Proccesed", 1450, 950);
    imshow("Proccesed", img);

    img.convertTo(img, CV_8UC1);*/

    // normalize(mag, mag, 0, 1, CV_MINMAX, CV_8UC(pixFormat.channelCount()));

    // waitKey(0);

    // Mat img = imread(mFileName, 0);
    // Mat img(Image.height(),Image.width(), 2 , (void*)Image.constBits(),Image.bytesPerLine()); // convert
    // Mat img(Image.height(),Image.width(), 1 , Image.bits(),Image.bytesPerLine());
    // Mat img(Image.height(),Image.width(), 1, const_cast<uchar*>(Image.bits()),Image.bytesPerLine());

      /* QImage Image = pix1.toImage(); // исходное изображение
      switch(Image.format()) {
      case QImage::Format_Invalid:
      {
        Mat empty;
        empty.copyTo(img);
        break;
      }
      case QImage::Format_RGB32:
      {
        Mat view(Image.height(),Image.width(),CV_8UC1,(void *)Image.constBits(),Image.bytesPerLine());
        view.copyTo(img);
        break;
      }
      case QImage::Format_RGB888:
      {
        Mat view(Image.height(),Image.width(),CV_8UC3,(void *)Image.constBits(),Image.bytesPerLine());
        cvtColor(view, img, COLOR_RGB2BGR);
        break;
      }
      default:
      {
        QImage conv = Image.convertToFormat(QImage::Format_ARGB32);
        Mat view(conv.height(),conv.width(),CV_8UC1,(void *)conv.constBits(),conv.bytesPerLine());
        view.copyTo(img);
        break;
      }
    } // switch*/

     // QImage Image = pix1.toImage(); // исходное изображение
    // QImage Conv = Image.convertToFormat(QImage::Format_ARGB32);
    // cvtColor(conv, conv, CV_BGRA2GRAY);
    // QImage Conv = Image.convertToFormat(QImage::Format_RGB888);
    // Mat img(Conv.height(),Conv.width(), 0 ,Conv.bytesPerLine());
    // Mat img(Conv.height(),Conv.width(), 0 , Conv.bits(),Conv.bytesPerLine());
    // Mat view(Conv.height(), Conv.width(), CV_8UC1 , (void *)Conv.constBits(), Conv.bytesPerLine());
    // Mat img(Conv.height(),Conv.width(), 0, const_cast<uchar*>(Conv.bits()),Conv.bytesPerLine());
    // Mat img( Image.height(), Image.width(), CV_8UC1, const_cast<uchar*>(Image.bits()), static_cast<size_t>(Image.bytesPerLine()));
    // Mat img(Image.height(), Image.width(), CV_8UC1 , (void *)Image.constBits(), Image.bytesPerLine());

    // Method 2
    int M = getOptimalDFTSize( img.rows );
    int N = getOptimalDFTSize( img.cols );

    Mat padded;
    copyMakeBorder(img, padded, 0, M - img.rows, 0, N - img.cols, BORDER_CONSTANT, Scalar::all(0));

    Mat planes[] = {Mat_<float>(padded), Mat::zeros(padded.size(), CV_32F)};
    // Mat complexImg;
    merge(planes, 2, complexImg); // Реальная и мнимая части входного сигнала (изображения) Add to the expanded another plane with zeros

    dft(complexImg, complexImg); // DFT - this way the result may fit in the source matrix complexImg


    // Проверка правильности фильтрации УДАЛИТЬ
    /*int wi, hi, wid2, hid2;
    wCut=100;
    qreal cx0, cy0;

  split(complexImg, planes); // Мнимая и реальная части Фурье-образа planes[0] = Re(DFT(Img), planes[1] = Im(DFT(Img))
  for (int k = 0; k < 2; k++)
  {
    wi = planes[k].cols;
    hi = planes[k].rows;
    wid2=qFloor(qreal(wi)/2.0);
    hid2=qFloor(qreal(hi)/2.0);

    //Фильтрация (относительно вершин прямоугольной области Фурье-образа)
    for (int y = 0; y < hi; y++) // y
    {
               if (y<hid2) cy0=0.0;
                      else cy0 = qreal(hi);
               qreal yrc=qreal(y)-cy0;

               for (int x = 0; x < wi; x++) // x
               {
                   if (x<wid2) cx0=0.0;
                          else cx0 = qreal(wi);
                   qreal xrc=qreal(x)-cx0;

                   qreal zr = qreal(planes[k].at<float>(y,x));
                   zr=IdealFilter(xrc, yrc, wCut)*zr;

                   planes[k].at<float>(y,x)=float(zr);
                } // x
     } // y
  }
  merge(planes, 2, complexImg);*/

    // for correct DISPLAY
    split(complexImg, planes); // Мнимая и реальная части Фурье-образа planes[0] = Re(DFT(Img), planes[1] = Im(DFT(Img))
    magnitude(planes[0], planes[1], planes[0]); // На выходе planes[0] = magnitude mag

    mag = planes[0]; // mag = sqrt(Re(DFT(img))**2 + Im(DFT(img))**2)

    // Логарифмический масштаб compute log(1 + sqrt(Re(DFT(img))**2 + Im(DFT(img))**2))
    mag += Scalar::all(1);
    log(mag, mag);

    // crop the spectrum, if it has an odd number of rows or columns
    mag = mag(Rect(0, 0, mag.cols & -2, mag.rows & -2));

    int cx = mag.cols/2;
    int cy = mag.rows/2;

    // rearrange the quadrants of Fourier image
    // so that the origin is at the image center
    //Центрирование  изображения
    Mat q0(mag, Rect(0, 0, cx, cy)); // Top-Left - Create a ROI per quadrant
    Mat q1(mag, Rect(cx, 0, cx, cy)); // Top-Right
    Mat q2(mag, Rect(0, cy, cx, cy)); // Bottom-Left
    Mat q3(mag, Rect(cx, cy, cx, cy)); // Bottom-Right

    Mat tmp;
    q0.copyTo(tmp); // swap quadrants (Top-Left with Bottom-Right)
    q3.copyTo(q0);
    tmp.copyTo(q3);

    q1.copyTo(tmp); // swap quadrant (Top-Right with Bottom-Left)
    q2.copyTo(q1);
    tmp.copyTo(q2);

    normalize(mag, mag, 0, 1, CV_MINMAX); // Transform the matrix with float values into a
                                          // viewable image form (float between values 0 and 1).

    // namedWindow("spectrum magnitude", WINDOW_AUTOSIZE );
    // imshow("spectrum magnitude", mag);

    // normalize(mag, mag, 0, 255, CV_MINMAX);
    // mag.copyTo(img);
}

void MainWindow::LeftChart3DSurf(Mat mag)
{   qreal xr, yr, zr, stepX, stepY;
    int i, j, x, y, countX, countY;

    // левый график Фурье-образа
    clearLayout(ui->verticalLayout_5, true);
    clearLayout(ui->verticalLayout_6, true); // без этого не работает. Не понятно

    int wi = mag.cols;
    int hi = mag.rows;
    // int wi = Image2.width();
    // int hi = Image2.height();

    qreal numbSx, numbSy; // густота сетки графика

    if (wi<hi) {if (wi % 2 == 0) numbSx=101.0;
                            else numbSx=100.0;
                    stepX= qreal(wi-1)/(numbSx-1.0); countX = int(numbSx);
                    numbSy=numbSx*qreal(hi-1)/qreal(wi-1); countY=qRound(numbSy);                    
                    if (countY % 2 == 0) countY=countY+1;
                    stepY=qreal(hi-1)/qreal(countY-1);
     }
          else { if (hi % 2 == 0) numbSy=101.0;
                             else numbSy=100.0;
                     stepY= qreal(hi-1)/(numbSy-1.0); countY = int(numbSy);
                     numbSx=numbSy*qreal(wi-1)/qreal(hi-1); countX=qRound(numbSx);                     
                     if (countX % 2 == 0) countX=countX+1;
                     stepX=qreal(wi-1)/qreal(countX-1);
          }

    // stepY=1.0; stepX=1.0; countY=hi; countX=wi;

    QSurfaceDataProxy *m_ProxyL = new QSurfaceDataProxy();
    QSurface3DSeries *SeriesL = new QSurface3DSeries(m_ProxyL);
    QSurfaceDataArray *dataArrayL = new QSurfaceDataArray;

    dataArrayL->reserve(countY);
    QSurfaceDataRow *newRowL;   

     for (i = 0; i < countY; i++)
    {
           yr=qreal(i)*stepY;
           y=qRound(yr);

           newRowL = new QSurfaceDataRow(countX);
           for (j = 0; j < countX; j++)
           {
               xr=qreal(j)*stepX;
               x=qRound(xr);
               zr = qreal (mag.at<float>(y,x));
               // zr = qreal (mag.at<float>(y,x));
               // zr=qreal(Image2.pixelColor(x, y).lightnessF());
               // zr=qMax(zr,0.0); zr=qMin(zr,1.0);              
               (*newRowL)[j].setPosition(QVector3D(float(xr), float(zr), float(yr)));
            } // x
           *dataArrayL << newRowL; // добавление строки
     } // y
// -------------------------------------------------------
     m_ProxyL->resetArray(dataArrayL);
     SeriesL->dataProxy();

     Q3DSurface *surfaceL = new Q3DSurface();
     surfaceL->addSeries(SeriesL);

     // градиентная закраска
     QLinearGradient gr;
     gr.setColorAt(0.0, Qt::black);
     gr.setColorAt(0.33, Qt::blue);
     gr.setColorAt(0.67, Qt::red);
     gr.setColorAt(1.0, Qt::yellow);
     surfaceL->seriesList().at(0)->setBaseGradient(gr);
     surfaceL->seriesList().at(0)->setColorStyle(Q3DTheme::ColorStyleRangeGradient);

     QWidget *mySurfaceL = QWidget::createWindowContainer(surfaceL);  // По аналогии QChartView *myChart2 = new QChartView(chart2);
     // clearLayout(ui->verticalLayout_5, true);
     // clearLayout(ui->verticalLayout_6, true); // Не работает. Не понятно
     ui->verticalLayout_5->addWidget(mySurfaceL); // вывод на layout5
}

void MainWindow::RightChart3DSurf(Mat mag)
{   // правый график Фурье-образа
    qreal xr, yr, zr, stepX, stepY;
    int i, j, x, y, countX, countY;

     clearLayout(ui->verticalLayout_6, true);
     // whiteRight();

    int wi = mag.cols;
    int hi = mag.rows;

    qreal numbSx, numbSy; // густота сетки графика

    if (wi<hi) {if (wi % 2 == 0) numbSx=101.0;
                            else numbSx=100.0;
                    stepX= qreal(wi-1)/(numbSx-1.0); countX = int(numbSx);
                    numbSy=numbSx*qreal(hi-1)/qreal(wi-1); countY=qRound(numbSy);
                    // if (((hi % 2 == 0) && (countY % 2 == 1)) || ((hi % 2 == 1) && (countY % 2 == 0))) countY=countY+1;
                    if (countY % 2 == 0) countY=countY+1;
                    stepY=qreal(hi-1)/qreal(countY-1);
     }
          else { if (hi % 2 == 0) numbSy=101.0;
                             else numbSy=100.0;
                     stepY= qreal(hi-1)/(numbSy-1.0); countY = int(numbSy);
                     numbSx=numbSy*qreal(wi-1)/qreal(hi-1); countX=qRound(numbSx);
                     // if (((wi % 2 == 0) && (countX % 2 == 1)) || ((wi % 2 == 1) && (countX % 2 == 0))) countX=countX+1;
                     if (countX % 2 == 0) countX=countX+1;
                     stepX=qreal(wi-1)/qreal(countX-1);
          }

    m_Proxy = new QSurfaceDataProxy();
    Series = new QSurface3DSeries(m_Proxy);
    dataArray = new QSurfaceDataArray;

    dataArray->reserve(countY);
    for (i = 0; i < countY; i++)
    {
           yr=qreal(i)*stepY;
           y=qRound(yr);

           newRow = new QSurfaceDataRow(countX);
           for (j = 0; j < countX; j++)
           {
               xr=qreal(j)*stepX;
               x=qRound(xr);
               zr = qreal (mag.at<float>(y,x));
               (*newRow)[j].setPosition(QVector3D(float(xr), float(zr), float(yr)));
            } // x
           *dataArray << newRow; // добавление строки
     } // y
// ---------------------------------
     m_Proxy->resetArray(dataArray);
     Series->dataProxy();

     surface = new Q3DSurface();
     surface->addSeries(Series);

     // градиентная закраска
     QLinearGradient gr;
     gr.setColorAt(0.0, Qt::black);
     gr.setColorAt(0.33, Qt::blue);
     gr.setColorAt(0.67, Qt::red);
     gr.setColorAt(1.0, Qt::yellow);
     surface->seriesList().at(0)->setBaseGradient(gr);
     surface->seriesList().at(0)->setColorStyle(Q3DTheme::ColorStyleRangeGradient);

     mySurface = QWidget::createWindowContainer(surface);  // По аналогии QChartView *myChart2 = new QChartView(chart2)
     // clearLayout(ui->verticalLayout_6, true);
     ui->verticalLayout_6->addWidget(mySurface); // вывод на layout6
}

void MainWindow::on_toolButton_9_clicked()
{   // ПРЯМОЕ ПРЕОБРАЗОВАНИЕ ФУРЬЕ

    ui->checkBox->setChecked(false);
    ui->checkBox_3->setChecked(false);
    ui->toolButton_12->setEnabled(true);
    ui->toolButton_13->setEnabled(true);
    // ui->verticalSlider_6 ->setValue(0);

    DFT();    

    // левый график Фурье-образа
    LeftChart3DSurf(mag);

    // правый график Фурье-образа
    RightChart3DSurf(mag);

    // правое окно
    on_toolButton_clicked();
}

void MainWindow::on_toolButton_12_toggled(bool checked)
{ // Batterwort filter
  if (checked==true) {      
      visibleBart=true; visibleIdeal=false;
      ui->toolButton_13->setChecked(false);
      // RightChart3DSurf(mag);
      ui->verticalSlider_6->setEnabled(true);
      complexImg.copyTo(complexImgFiltr); // глобальные
      on_verticalSlider_6_valueChanged(ValSld_6);
      // int value=ValSld_6+1;
      // ui->verticalSlider_6 ->setValue(0);
   }
  else {visibleBart=false;  // clearLayout(ui->verticalLayout_6, true);
        ui->verticalSlider_6->setEnabled(false);
  }
}

void MainWindow::on_toolButton_13_toggled(bool checked)
{   // Ideal filter
    if (checked==true){
        visibleIdeal=true; visibleBart=false;
        ui->toolButton_12->setChecked(false);
        // RightChart3DSurf(mag);
        ui->verticalSlider_6->setEnabled(true);
        complexImg.copyTo(complexImgFiltr); // глобальные
        on_verticalSlider_6_valueChanged(ValSld_6);
        // int value=ValSld_6+1;
        // ui->verticalSlider_6 ->setValue(0);
     }
     else {visibleIdeal=false;  // clearLayout(ui->verticalLayout_6, true);
           ui->verticalSlider_6->setEnabled(false);
    }
}

qreal BatterFilter(qreal xrc2, qreal yrc2, qreal wCut2)
{
     qreal H;
     // H=sqrt(xrc*xrc+yrc*yrc)/wCut;
     // H=1.0/(1.0+H*H*H*H);
     H=(xrc2+yrc2)/wCut2;
     H=1.0/(1.0+H*H);
     return H;
}

qreal IdealFilter(qreal xrc2, qreal yrc2, qreal wCut2)
{
    qreal H;
    // if(sqrt(xrc*xrc+yrc*yrc)>wCut)H=0.0;
       // else H=1.0;
    if((xrc2+yrc2)>wCut2)H=0.0;
                    else H=1.0;
    return H;
}

void MainWindow::Filtration()
{ // ОБРАТНОЕ ПРЕОБРАЗОВАНИЕ ФУРЬЕ после фильтрации и вывод изображения
       Mat /*complexImgFiltr,*/ invDFT, invDFTcvt, imgF;
       qreal cx, cy, yrc, yrc2, xrc, xrc2;
       int wi, hi, wid2, hid2;

       // Filtering
       // complexImg.copyTo(complexImgFiltr); // в глобальные ??????

       //Фильтрация (относительно вершин прямоугольной области Фурье-образа) График
       Mat planes[2];
       split(complexImg, planes); // Мнимая и реальная части Фурье-образа planes[0] = Re(DFT(Img), planes[1] = Im(DFT(Img))
       for (int k = 0; k < 2; k++)
       {
          wi = planes[k].cols;
          hi = planes[k].rows;
          wid2=qFloor(qreal(wi)/2.0);
          hid2=qFloor(qreal(hi)/2.0);
          for (int y = 0; y < hi; y++) // y
          {
                    if (y<hid2) cy=0.0;
                           else cy = qreal(hi);
                    yrc=qreal(y)-cy;
                    yrc2=yrc*yrc;

                    // #pragma omp parallel for schedule(dynamic) num_threads(6)
                    for (int x = 0; x < wi; x++) // x
                    {
                        if (x<wid2) cx=0.0;
                               else cx = qreal(wi);
                        xrc=qreal(x)-cx;
                        xrc2=xrc*xrc;

                        qreal zr = qreal(planes[k].at<float>(y,x));
                        if (visibleBart)  zr=BatterFilter(xrc2, yrc2, wCut2)*zr;
                            else if (visibleIdeal) zr=IdealFilter(xrc2, yrc2, wCut2)*zr;

                        planes[k].at<float>(y,x)=float(zr);
                    } // x
           } // y
       } // k
       merge(planes, 2, complexImgFiltr); // объединение planes[0] и planes[1]

      // быстрый доступ
       /* Mat planes[2];
       split(complexImg, planes); // Мнимая и реальная части Фурье-образа planes[0] = Re(DFT(Img), planes[1] = Im(DFT(Img))
       for (int k = 0; k < 2; k++)
       {
          wi = planes[k].cols;
          hi = planes[k].rows;
          wid2=qFloor(qreal(wi)/2.0);
          hid2=qFloor(qreal(hi)/2.0);

          for(int y = 0; y < hi; y++) {
              uchar* p = planes[k].ptr<uchar>(y); //pointer p points to the first place of each row
              if (y<hid2) cy=0.0;
                     else cy = qreal(hi);
              yrc=qreal(y)-cy;
              yrc2=yrc*yrc;

              for(int x = 0; x < wi; x++) {
                 // float zr = static_cast<uchar>(p[x]);
                 float zr = p[x];
                  // std::cout<<zr<<endl;
                  if (x<wid2) cx=0.0;
                         else cx = qreal(wi);
                  xrc=qreal(x)-cx;
                  xrc2=xrc*xrc;

                  if (visibleBart)  zr=BatterFilter(xrc2, yrc2, wCut2)*zr;
                      else if (visibleIdeal) zr=IdealFilter(xrc2, yrc2, wCut2)*zr;

                 *p++ = zr;  // operation here
              } // x
          } // y
       } // k
       merge(planes, 2, complexImgFiltr); // объединение planes[0] и planes[1]*/

       // быстрый доступ 2
       /*Mat planes[2];
       split(complexImg, planes); // Мнимая и реальная части Фурье-образа planes[0] = Re(DFT(Img), planes[1] = Im(DFT(Img))
       for (int k = 0; k < 2; k++)
              {
                 uint8_t *myData = planes[k].data;
                 // uchar *myData = planes[k].data;
                 wi = planes[k].cols;
                 hi = planes[k].rows;
                 wid2=qFloor(qreal(wi)/2.0);
                 hid2=qFloor(qreal(hi)/2.0);

                 for(int y = 0; y < hi; y++) {
                     if (y<hid2) cy=0.0;
                           else cy = qreal(hi);
                     yrc=qreal(y)-cy;
                     yrc2=yrc*yrc;

                         for(int x = 0; x < wi; x++) {
                             if (x<wid2) cx=0.0;
                                    else cx = qreal(wi);
                             xrc=qreal(x)-cx;
                             xrc2=xrc*xrc;

                             // uint8_t zr = myData[x + wi*y];
                             // uchar zr = myData[x + wi*y];
                             float zr = static_cast<uchar>(myData[x + wi*y]);
                             // uchar zr = *(planes[k].data+y*wi+x);
                             if (visibleBart)  zr=BatterFilter(xrc2, yrc2, wCut2)*zr;
                                 else if (visibleIdeal) zr=IdealFilter(xrc2, yrc2, wCut2)*zr;
                             // *(planes[k].data+y*wi+x)= zr;
                             myData[x + wi*y]=zr;
                     }
                 }
               } // k
               merge(planes, 2, complexImgFiltr); // объединение planes[0] и planes[1]*/


       // inverse DFT
       idft(complexImgFiltr, invDFT, DFT_SCALE | DFT_REAL_OUTPUT ); // Applying IDFT

       invDFT.convertTo(invDFTcvt, CV_8UC1); // Inverted to CV_8UC1

       // Первоначальные размеры изображения wi1, hi1 (глобальные)
       Mat part = invDFTcvt(Rect(0, 0, wi1, hi1));
       part = part.clone();

       // imshow("Output", part);

       // inverted to QImage
       cvtColor(part, imgF, COLOR_GRAY2BGRA);
       QImage ImageF(imgF.data, imgF.cols, imgF.rows, imgF.step[0], QImage::Format_ARGB32);
       pix2=QPixmap::fromImage(ImageF);
       ui->label_2->setPixmap(pix2.scaled(w2, h2, Qt::KeepAspectRatio));
       pix3=pix2;
}

void MainWindow::on_verticalSlider_6_valueChanged(int value)
{   // частота среза и фильтрация
      qreal xr, yr, zr, stepX, stepY, cx, cy, xrc, xrc2, yrc, yrc2, wCut;
      int i, j, x, y, countX, countY;
      QString str;
      QColor color;

    // правый график Фурье-образа
    if (visibleBart || visibleIdeal)
    {
        ValSld_6=value;

        int wi = mag.cols;
        int hi = mag.rows;

        qreal numbSx, numbSy; // густота сетки графика

        if (wi<hi) {if (wi % 2 == 0) numbSx=101.0;
                                else numbSx=100.0;
                        stepX= qreal(wi-1)/(numbSx-1.0); countX = int(numbSx);
                        numbSy=numbSx*qreal(hi-1)/qreal(wi-1); countY=qRound(numbSy);
                        if (countY % 2 == 0) countY=countY+1;
                        stepY=qreal(hi-1)/qreal(countY-1);
         }
              else { if (hi % 2 == 0) numbSy=101.0;
                                 else numbSy=100.0;
                         stepY= qreal(hi-1)/(numbSy-1.0); countY = int(numbSy);
                         numbSx=numbSy*qreal(wi-1)/qreal(hi-1); countX=qRound(numbSx);
                         if (countX % 2 == 0) countX=countX+1;
                         stepX=qreal(wi-1)/qreal(countX-1);
               }

         cx=qreal(wi)/2.0;
         cy=qreal(hi)/2.0;
         wCut=sqrt(cx*cx+cy*cy)*(1.0-qreal(value)/100.0); // частота среза
         StatLabel2->setText("cut off frequency: "+str.number(value)+" %");
         wCut2=wCut*wCut;

         surface->removeSeries(Series);

         dataArray = new QSurfaceDataArray;
         dataArray->reserve(countY);
         for (i = 0; i < countY; i++) // y
         {
                yr=qreal(i)*stepY;
                y=qRound(yr);
                yrc=yr-cy;
                yrc2=yrc*yrc;

                newRow = new QSurfaceDataRow(countX);
                for (j = 0; j < countX; j++) // x
                {
                    xr=qreal(j)*stepX;
                    x=qRound(xr);
                    xrc=xr-cx;
                    xrc2=xrc*xrc;

                    zr = qreal (mag.at<float>(y,x));
                    if (visibleBart)  zr=BatterFilter(xrc2, yrc2, wCut2)*zr;
                       else if (visibleIdeal) zr=IdealFilter(xrc2, yrc2, wCut2)*zr;

                    (*newRow)[j].setPosition(QVector3D(float(xrc), float(zr), float(yrc)));
                 } // x
                *dataArray << newRow; // добавление строки
          } // y
          Series->dataProxy()->resetArray(dataArray);
          surface->addSeries(Series);
          // ------------------------
          Filtration();
    } // if
}

void MainWindow::on_toolButton_14_clicked()
{
   // inverted Mat to QImage
    /*switch(image.type())
        {
            case CV_8UC4:
            {
                Mat view(image.getMat());
                QImage view2(view.data, view.cols, view.rows, view.step[0], QImage::Format_ARGB32);
                out = view2.copy();
                break;
            }
            case CV_8UC3:
            {
                Mat mat;
                cvtColor(image, mat, COLOR_BGR2BGRA); //COLOR_BGR2RGB doesn't behave so use RGBA
                QImage view(mat.data, mat.cols, mat.rows, mat.step[0], QImage::Format_ARGB32);
                out = view.copy();
                break;
            }
            case CV_8UC1:
            {
                Mat mat;
                cvtColor(image, mat, COLOR_GRAY2BGRA);
                QImage view(mat.data, mat.cols, mat.rows, mat.step[0], QImage::Format_ARGB32);
                out = view.copy();
                break;
            }
            default:
            {
                throw invalid_argument("Image format not supported");
                break;
            }
        }*/

}

void MainWindow::on_action_Save_RW_triggered()
{  // save RW
    QString mFileName=QFileDialog::getSaveFileName ( this, " save Right image...", QDir::currentPath(), " Image files ( *.png *.jpg *.bmp ); All files ( *.* ) " );
    if ( mFileName.isEmpty ( ) ) //Если пользователь не выбрал ни одного файла
        {
            return; //выйти из метода
        }
    pix2.save(mFileName);

}

void MainWindow::on_action_Save_triggered()
{
    // save
    QString mFileName=QFileDialog::getSaveFileName ( this, " save image...", QDir::currentPath(), " Image files ( *.png *.jpg *.bmp ); All files ( *.* ) " );
    if ( mFileName.isEmpty ( ) ) //Если пользователь не выбрал ни одного файла
    {
         return; //выйти из метода
    }
    pix1.save(mFileName);
}


void MainWindow::on_toolButton_21_clicked()
{
    ui->checkBox_3->setCheckState(Qt::CheckState(0));

    pix1.save("x.bmp"); // QImage
    mag = imread("x.bmp", CV_8UC1); // Mat
    normalize(mag, mag, 0, 1, CV_MINMAX, CV_32F);
    LeftChart3DSurf(mag);

    pix3.save("x.bmp"); // QImage
    mag = imread("x.bmp", CV_8UC1); // Mat
    normalize(mag, mag, 0, 1, CV_MINMAX, CV_32F);
    RightChart3DSurf(mag);
}

void MainWindow::on_actionCamera_triggered()
{
    // Mat frame;
    //--- INITIALIZE VIDEOCAPTURE
    // VideoCapture cap;
     // cap.open(0);

    // CvCapture* capture ;
    // capture = cvCreateCameraCapture(CV_CAP_ANY);
    // capture = cvCaptureFromCAM( -1 );


}


void MainWindow::on_spinBox_valueChanged(const QString &arg1)
{

}
