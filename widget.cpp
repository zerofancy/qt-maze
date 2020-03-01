#include "widget.h"
#include "ui_widget.h"

bool(*L_goUp)();
bool(*L_goDown)();
bool(*L_goLeft)();
bool(*L_goRight)();
QVector<myPoint> (*getTip) ();

//Dialog dia;

int po_ch_x=1;
int po_ch_y=1;

bool handleEvents=true;

Menu* sysMenu=NULL;

QString picPath[6];


void sleep(unsigned int msec)

{

QTime dieTime = QTime::currentTime().addMSecs(msec);

while( QTime::currentTime() < dieTime )

QCoreApplication::processEvents(QEventLoop::AllEvents, 1);

}

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    timerB=new QTimer;
    timerT=new QTimer;
    timerL=new QTimer;
    timerR=new QTimer;

    connect(timerB,SIGNAL(timeout()),this,SLOT(moveBottom()));
    connect(timerT,SIGNAL(timeout()),this,SLOT(moveTop()));
    connect(timerL,SIGNAL(timeout()),this,SLOT(moveLeft()));
    connect(timerR,SIGNAL(timeout()),this,SLOT(moveRight()));

    ui->setupUi(this);
    player=new QMediaPlayer;
    player->setMedia(QUrl::fromLocalFile("background.mp3"));
    player->setVolume(30);

    pla_vic=new QMediaPlayer;
    pla_vic->setMedia(QUrl::fromLocalFile("victory.mp3"));
    pla_vic->setVolume(30);

    ui->pushButton->setVisible(false);
    ui->pushButton_2->setVisible(false);
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(1000);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();
    setWindowFlags(Qt::FramelessWindowHint);//无边框
    m_areaMovable = geometry();
    m_bPressed = false;

    setFixedSize(1024, 768);

    b1=new QScrollBar();
    b2=new QScrollBar();
    ui->graphicsView->setHorizontalScrollBar(b1);
    ui->graphicsView->setVerticalScrollBar(b2);
    //设置不显示滚动条
    ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //设置视图固定大小
    setFixedSize(1024, 768);

    scene = new QGraphicsScene(this);
//    scene->setSceneRect(0,0,1024,768);
    //将scene和View绑定
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setBackgroundBrush(QColor(192,192,192,192));
    //过滤方向键
    if ( parent )
             parent->installEventFilter( this );
    scene->installEventFilter(this);
    setStyleSheet("border:2px groove gray;border-radius:10px;padding:2px 4px;");
//    setAttribute(Qt::WA_TranslucentBackground);//背景透明
    connect(player,SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)),this,SLOT(playAgain(QMediaPlayer::MediaStatus)));
    player->play();
}

QGraphicsItem* LoadMap(int n,int x,int y,int sizemode=50){
    QGraphicsPixmapItem*pItem=new QGraphicsPixmapItem();
    //QString tmppath=QString("map%1.bmp").arg(n);
    QString tmppath=QString("%1").arg(picPath[n]);
    QPixmap image(tmppath);
    pItem->setPixmap(image.scaled(sizemode, sizemode));
    pItem->setX(x*sizemode);
    pItem->setY(y*sizemode);
    return pItem;
}


void Widget::start(bool(*p1)(), bool(*p2)(), bool(*p3)(), bool(*p4)()){
    QSettings ini2(QString("style%1.ini").arg(mazestye), QSettings::IniFormat);
//    qDebug()<<QString("style%1.ini").arg(mazestye);
    for(int i=1;i<=5;i++){
//        qDebug()<<ini2.value("/set/now").toString();
//        qDebug()<<ini2.value(QString("/pics/%1").arg(i)).toString();
        picPath[i]=QString("%1/%2").arg(ini2.value("/settings/path").toString()).arg(ini2.value(QString("/pics/%1").arg(i)).toString());
        qDebug()<<picPath[i];
    }
    int x=1;
    int y=1;
    int n=3;
    int sizemode=50;
    QGraphicsPixmapItem*pItem=new QGraphicsPixmapItem();
//    QString tmppath=QString("map%1.bmp").arg(n);
    QString tmppath=QString("%1").arg(picPath[n]);
    QPixmap image(tmppath);
    pItem->setPixmap(image.scaled(sizemode, sizemode));
    pItem->setX(x*sizemode);
    pItem->setY(y*sizemode);
    pItem->setZValue(3);
    Lead=pItem;
    scene->addItem(pItem);
    L_goUp=p3;//因为坐标换算问题，两边不对应
    L_goDown=p4;
    L_goLeft=p1;
    L_goRight=p2;
    return;
}

void Widget::passGetTip(QVector<myPoint> (*getTip_)())
{
    getTip=getTip_;
}

void Widget::showpic(int n, int x, int y, int sizemode, int paintLevel)
{
    QGraphicsItem*pItem=LoadMap(n,x,y,sizemode);
    pItem->setZValue(paintLevel);
    scene->addItem(pItem);
}

void Widget::setLeadPos(int x, int y, int sizemode)//主角设置
{
    handleEvents=false;
    tar_x=x*sizemode;
    tar_y=y*sizemode;
//    if(tar_x<Lead->pos().x()){
//        timerL->start(1);
//    }
//    if(tar_x>Lead->pos().x()){
//        timerR->start(1);
//    }
//    if(tar_y<Lead->pos().y()){
//        timerT->start(1);
//    }
//    if(tar_y>Lead->pos().y()){
//        timerB->start(1);
//    }
//    int tmpfh=1;
//    tmpfh=x*sizemode>Lead->pos().x()?1:-1;
//    int counter=0;
//    while (Lead->pos().x()!=x*sizemode) {
//        sleep(1);
//        if(counter>5){
//            b1->setValue(Lead->pos().x()-10*sizemode);
//            counter=0;
//        }
//        Lead->moveBy(tmpfh,0);
//        counter++;
//    }
//    tmpfh=y*sizemode>Lead->pos().y()?1:-1;
//    while (Lead->pos().y()!=y*sizemode) {
//        sleep(1);
//        if(counter>5){
//            b2->setValue(Lead->pos().y()-7*sizemode);
//            counter=0;
//        }
//        Lead->moveBy(0,tmpfh);
//        counter++;
//    }
//    qDebug()<<b1->value();
//    qDebug()<<b2->value();
    b1->setValue((x-10)*sizemode);
    b2->setValue((y-7)*sizemode);

//    qDebug()<<Lead->pos();
//    qDebug()<<Lead->scenePos();
//    ui->graphicsView->setSceneRect(-(ui->graphicsView->width()/2-Lead->pos().x()+ui->graphicsView->scene()->width()/2),-(ui->graphicsView->height()/2-Lead->pos().y()+ui->graphicsView->scene()->height()/2),ui->graphicsView->scene()->width(),ui->graphicsView->scene()->height());
//    qDebug()<<ui->graphicsView->sceneRect();
    //              qDebug()<<ui->graphicsView->scene()->sceneRect();
    Lead->setX(x*sizemode);
    Lead->setY(y*sizemode);
    handleEvents=true;
}

void Widget::win(){
//    QMessageBox::information(this,"Maze","You win!");
//    sleep(100);



    qDebug("Save success!");
    a->par=this;//将窗体放到主函数构筑，稍稍加快速度
    saveImg();
    player->stop();
    pla_vic->play();
    a->show();
    a->time->start(5000);
    //this->close();
//    QApplication::exit();
    //绕过这个bug思路：设置timer完成close操作……
//    Dialog*xinchuangkou=new Dialog;
}

void Widget::setScrollBar(int n)
{
    b1->setMaximum(n);
    b2->setMaximum(n);
}

Widget::~Widget()
{
    delete ui;
}

bool Widget::eventFilter( QObject *o, QEvent *e )
{
    frmHelp tmp_help;
    QVector<myPoint> tipPoints;
    if(!handleEvents){
        if ( e->type() != QEvent::KeyPress )
        return QWidget::eventFilter( o, e );
        return true;
    }
    if ( e->type() == QEvent::KeyPress ) {
        QKeyEvent *k = (QKeyEvent *)e;
        qDebug()<<k->key();
        switch(k->key())
        {
        case Qt::Key_Up:
            if(L_goUp()){
                ;
            }
        break;
        case Qt::Key_Down:
            if(L_goDown()){
                ;
            }
        break;
        case Qt::Key_Right:
            if(L_goRight()){
                ;
            }
        break;
        case Qt::Key_Left:
            if(L_goLeft()){
                ;
            }
        break;
        case Qt::Key_Escape:
            qApp->quit();   // 或者   aApp->closeAllWindows();
            QProcess::startDetached(qApp->applicationFilePath(), QStringList());
            break;
        case Qt::Key_P:
            if(player->state()==QMediaPlayer::StoppedState){
                player->play();
            }else {
                player->stop();
            }
            break;
        case Qt::Key_F1:
            tmp_help.exec();
            break;
        case Qt::Key_O:
            saveImg();
            break;
        case 126:
            if(!ui->pushButton_2->isEnabled()){
                return QWidget::eventFilter( o, e );
            }
            tipPoints= getTip();
            for(int i=0; i<tipPoints.size(); i++){
                Widget::showpic(4,tipPoints[i].y,tipPoints[i].x,50,2);
            }
            ui->pushButton_2->setDisabled(true);
            break;
        default:
            return QWidget::eventFilter( o, e );
        }
        return true;
    } else {
        return QWidget::eventFilter( o, e );
    }
}

void Widget::on_pushButton_clicked()
{
    this->close();
}

void Widget::on_pushButton_2_clicked()
{
    QVector<myPoint> tipPoints;
    tipPoints= getTip();
    for(int i=0; i<tipPoints.size(); i++){
        Widget::showpic(4,tipPoints[i].y,tipPoints[i].x,50,2);
    }
    ui->pushButton_2->setDisabled(true);
}

void Widget::mousePressEvent(QMouseEvent *e)
{
  //鼠标左键
  if(e->button() == Qt::LeftButton)
  {
  m_ptPress = e->pos();
  qDebug() << pos() << e->pos() << m_ptPress;
  m_bPressed = m_areaMovable.contains(m_ptPress);
  }
}

void Widget::mouseMoveEvent(QMouseEvent *e)
{
  if(m_bPressed)
  {
  qDebug() << pos() << e->pos() << m_ptPress;
  move(pos() + e->pos() - m_ptPress);
  }
}

void Widget::mouseReleaseEvent(QMouseEvent *)
{
  m_bPressed = false;
}

//设置鼠标按下的区域
void Widget::setAreaMovable(const QRect rt)
{
  if(m_areaMovable != rt)
  {
    m_areaMovable = rt;
  }
}

bool Widget::close1()
{
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
       animation->setDuration(1000);
       animation->setStartValue(1);
       animation->setEndValue(0);
       animation->start();
       connect(animation, SIGNAL(finished()), this, SLOT(close()));
       return true;
}

void Widget::saveImg()
{
    QString fileName =QFileDialog::getSaveFileName(NULL,"保存场景截图","","*.png");

    if (!fileName.isNull())
    {
        //fileName是文件名
        QImage image(150* mapsize_n, 150*mapsize_n ,QImage::Format_ARGB32);
                QString pngName = fileName;
                QPainter painter(&image);
                painter.setRenderHint(QPainter::Antialiasing);
                scene->render(&painter);
                bool saveSuccess =  image.save(pngName);
                Q_ASSERT(saveSuccess == true);
    }
    else
    {
        //点的是取消
    }
}

void Widget::playAgain(QMediaPlayer::MediaStatus m_state)
{
//    qDebug()<<m_state;
    if(m_state==QMediaPlayer::EndOfMedia){
        player->play();
    }
}

void Widget::moveLeft()
{
    if(Lead->pos().x()>tar_x){
        Lead->moveBy(-3,0);
    }else{
        timerL->stop();
        Lead->pos().setX(tar_x);
    }
}

void Widget::moveRight()
{
    if(Lead->pos().x()<tar_x){
        Lead->moveBy(3,0);
    }else{
        timerR->stop();
        Lead->pos().setX(tar_x);
    }

}

void Widget::moveTop()
{
    if(Lead->pos().y()>tar_y){
        Lead->moveBy(0,-3);
    }else{
        timerT->stop();
        Lead->pos().setY(tar_y);
    }

}

void Widget::moveBottom()
{
    if(Lead->pos().y()<tar_y){
        Lead->moveBy(0,3);
    }else{
        timerB->stop();
        Lead->pos().setY(tar_y);
    }

}
//void Widget::setSysMnu(Menu *w)
//{
//    sysMenu=w;
//}
