#include "frmhelp.h"
#include "ui_frmhelp.h"

frmHelp::frmHelp(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::frmHelp)
{
    ui->setupUi(this);
    QPalette p = palette();
    QPixmap img("help.jpg");

    QBitmap mask("help_mask.bmp");

    p.setBrush(QPalette::Window, QBrush(img));

    setPalette(p);

    setMask(mask);

    resize(img.size());

    setWindowFlags(Qt::FramelessWindowHint);//这句会去掉标题栏 } 注意:mask的图多余部分设为白色    ui->setupUi(this);
this->setAutoFillBackground(true);
QPalette palette;
setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
setWindowModality(Qt::WindowModal);

palette.setColor(QPalette::Background, QColor(192,253,123));
palette.setBrush(QPalette::Background, QBrush(img));

}

frmHelp::~frmHelp()
{
    delete ui;
}


void frmHelp::keyPressEvent(QKeyEvent *event)
{
    if (event->key()==Qt::Key_Escape||event->key()==Qt::Key_F1)
    {
        this->close();
    }
}
