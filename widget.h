#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QGraphicsView>
#include"QGraphicsItem"
#include"QGraphicsPixmapItem"
#include"QString"
#include"QKeyEvent"
#include"QMessageBox"
#include"QVector"
#include"QDebug"
#include"QTime"
#include"QScrollBar"
#include"QPropertyAnimation"
#include"end.h"
#include"QTimer"
#include"QRect"
#include"menu.h"
#include"QProcess"
#include"QMediaPlayer"
#include"QFileDialog"
#include"QSettings"
namespace Ui {
class Widget;
}

typedef struct
{
    int x;
    int y;
} myPoint;

class Widget :
        public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    QGraphicsScene * scene;

    QScrollBar*b1;
    QScrollBar*b2;

    QString mazestye;
    int mapsize_n;

    void start(bool(*p1)(),bool(*p2)(),bool(*p3)(),bool(*p4)());

    void passGetTip(QVector<myPoint> (*getTip_)());

    void showpic(int n,int x,int y,int sizemode=50,int paintLevel=1);

    void setLeadPos(int x,int y,int sizemode=50);

    void win();

    void setScrollBar(int n);

    void setAreaMovable(const QRect rt);

    bool close1();
    //void setSysMnu(Menu*w);

    void saveImg();

public slots:
protected:
      bool eventFilter( QObject *, QEvent * );
      void mousePressEvent(QMouseEvent *);
      void mouseMoveEvent(QMouseEvent *);
      void mouseReleaseEvent(QMouseEvent *);

private slots:
      void on_pushButton_clicked();
      void on_pushButton_2_clicked();
      void playAgain(QMediaPlayer::MediaStatus m_state);
      void moveLeft();
      void moveRight();
      void moveTop();
      void moveBottom();

private:
    Ui::Widget *ui;
    QRect m_areaMovable;//可移动窗口的区域，鼠标只有在该区域按下才能移动窗口
    bool m_bPressed;//鼠标按下标志（不分左右键）
    QPoint m_ptPress;//鼠标按下的初始位置
    QGraphicsPixmapItem* Lead;
    end* a=new end;
    QMediaPlayer*player;
    QMediaPlayer*pla_vic;
    QTimer*timerL;
    QTimer*timerR;
    QTimer*timerT;
    QTimer*timerB;

    int tar_x;
    int tar_y;
};

#endif // WIDGET_H
