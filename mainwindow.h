#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>
#include <QLayout>
#include <QPixmap>
#include <QColor>
#include <QImage>
#include <QSize>
#include <QtMath>
#include <QObject>
#include <QMouseEvent>
#include <QProgressBar>
#include <QLabel>

#include <QtCharts/QChartView>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QHorizontalStackedBarSeries>
#include <QtCharts/QLineSeries>
#include <QtCharts/QXYSeries>
#include <QtCharts/QCategoryAxis>
#include <QtCharts/QChart>

#include <QtDataVisualization/Q3DSurface>
#include <QtDataVisualization/QSurfaceDataProxy>
#include <QtDataVisualization/QHeightMapSurfaceDataProxy>
#include <QtDataVisualization/QSurface3DSeries>

// #include <opencv2/core/core.hpp>
// #include <opencv2/imgproc/imgproc.hpp>
// #include "opencv2/imgcodecs.hpp"
// #include <opencv2/objdetect/objdetect.hpp>
// #include <opencv2/imgproc/imgproc.hpp>
// #include <opencv2/highgui/highgui.hpp>

// #include <opencv2/videoio/videoio.hpp>

// #include "cv.h"

#include "opencv/cv.h"
#include "opencv2/core.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/opencv.hpp"
#include "opencv2/video.hpp"
#include "opencv2/videoio.hpp"

//#include <iostream>
//#include <stdio.h>




namespace Ui {
class MainWindow;
}

using namespace cv;
using namespace std;
using namespace QtDataVisualization;
QT_CHARTS_USE_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT    

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:

private slots:
    void showEvent(QShowEvent *event);
    void on_actionOpen_triggered();
    void closeEvent(QCloseEvent *event);

    void on_checkBox_stateChanged(int arg1);
    void on_checkBox_2_stateChanged(int arg1);
    void on_checkBox_3_stateChanged(int arg1);

    void on_pushButton_clicked();

    void on_toolButton_clicked();
    void on_toolButton_2_clicked();
    void on_toolButton_3_clicked();
    void on_toolButton_4_clicked();
    void on_toolButton_5_clicked();
    void on_toolButton_7_clicked();
    void on_toolButton_6_clicked();
    void on_toolButton_8_clicked();
    void on_toolButton_9_clicked();
    void on_toolButton_17_clicked(); 

    void on_toolButton_12_toggled(bool checked);
    void on_toolButton_13_toggled(bool checked);

    void whiteLeft();
    void whiteRight();
    // void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *event);

    void on_verticalSlider_valueChanged(int value);
    void on_verticalSlider_2_valueChanged(int value);
    void on_verticalSlider_3_valueChanged(int value);   
    void on_verticalSlider_4_valueChanged(int value);
    void on_verticalSlider_5_valueChanged(int value);
    void on_verticalSlider_6_valueChanged(int value);
    void on_verticalSlider_7_valueChanged(int value);

    void SliderPosInit(int pos);
    void ImMatrixFill(int width, int height, int v);
    void on_spinBox_valueChanged(int arg1);

    void set_on_Pix_FillRectDraw(int lbl, int x1, int y1, int x2, int y2, qreal r, qreal g, qreal b, qreal t, QPixmap pixDown);
    void cutImage(int x1, int y1, int x2, int y2);
    void getHistogramm(QPixmap pix);
    void SmoothValueMedian(QImage Image, int wi, int hi, int x, int y, int n, QColor color);
    void intensityMask(int i, int j, int n, /*int nMid,*/ QImage Image, int wi, int hi);

    void mouseDoubleClickEvent(QMouseEvent *me);
    void mousePressEvent(QMouseEvent* pe);
    void mouseMoveEvent(QMouseEvent *me);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void wheelEvent(QWheelEvent *we);

    void on_action_Exit_triggered();

    void clearLayout(QLayout* layout, bool deleteWidgets);
    void on_toolButton_11_clicked();
    void on_toolButton_14_clicked();   

    void LeftChart3DSurf(Mat mag);
    void RightChart3DSurf(Mat mag);

    void DFT();
    void Filtration();

    void on_action_Save_RW_triggered();
    void on_action_Save_triggered();

    void on_toolButton_15_clicked();

    void MinMaxMatr(int nMtr, qreal C[9][9]);

    void on_toolButton_19_clicked();

    void on_toolButton_21_clicked();

    void on_actionCamera_triggered();

    void on_spinBox_valueChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;

    QProgressBar *StatProgress;

    QLabel *StatLabel1, *StatLabel2 /*, *StatLabel3*/;
    QPixmap pix0, pix1, pix2, pix3, pixCut;
    QImage /*Image,*/ Image2, ImC, ImG, ImS, ImSmMedian;
    // QColor colorMedian;
    // QString mFileName;
    int w1, h1, w2, h2, wi1, hi1, wi2, hi2;
    int xrect=10, yrect=10, wrect, hrect, dwrect, dhrect;
    qreal dltX=0, dltY;
    int deltRGB_L=0;
    qreal kw1, kh1;
    qreal Hm[9][9], Hr[9][9], colMask [9][9];
    int nMtr=1, nRtr=1;
    const int nHist=256;
    qreal YhNorm[256], Yh[256];
    bool visibleLine=false, visibleRect=false, visibleBart=false, visibleIdeal=false, aspectRat, keyCtrl=false, keyShift=false, /*mouseInLab1=false,*/ mouseInRect;
    // bool sliderPosInit=true;
    int argRot=0;
    int ValSld_7=0, ValSld_6=0;
    qreal wCut2=1000000.0;
    qreal maxMatr, minMatr;

    QLineSeries *series1, *series2;
    QChart *chart1, *chart2;

    QSurfaceDataProxy *m_Proxy;
    QSurface3DSeries *Series;
    QSurfaceDataArray *dataArray;
    QSurfaceDataRow *newRow;
    Q3DSurface *surface;
    QWidget *mySurface;

    Mat complexImg, complexImgFiltr, mag;
};

#endif // MAINWINDOW_H
