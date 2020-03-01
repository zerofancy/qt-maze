#include "menu.h"
#include "ui_menu.h"

Menu::Menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);
    size_N=ui->verticalSlider->value();
    setWindowFlags(Qt::FramelessWindowHint);//这句会去掉标题栏 } 注意:mask的图多余部分设为白色    ui->setupUi(this);

}

Menu::~Menu()
{
    delete ui;
}

void Menu::on_play_clicked()
{
    this->close();
    S_result=1;
}

void Menu::on_help_clicked()
{
//    this->close();
    frmHelp tmp_help;
    tmp_help.exec();
    S_result=2;
}

void Menu::on_exit_clicked()
{
    this->close();
    S_result=3;
    qDebug("quit");
    QApplication::closeAllWindows();
    exit(0);
}

void Menu::on_verticalSlider_actionTriggered(int action)
{
    size_N=ui->verticalSlider->value();
}

void Menu::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton){
        qDebug() << "press left button";
        this->isPress=true;
        this->point=event->globalPos()-this->pos();
    }
}
void Menu::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton){
        if(this->isPress==true){
            move(event->globalPos()-point);
            point=event->globalPos()-this->pos();
        }
    }
}
void Menu::mouseReleaseEvent(QMouseEvent *event)
{
    this->isPress=false;
}
