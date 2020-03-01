#include "end.h"
#include "ui_end.h"
#include <QTimer>
#include"QBitmap"
#include"QProcess"
end::end(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::end)
{
        QPalette p = palette();
        QPixmap img("1231.png");

        QBitmap mask("1231.bmp");

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

    this->setPalette(palette);
    connect(time,SIGNAL(timeout()),this,SLOT(close1()));
}

end::~end()
{
    delete ui;
}

void end::close1()
{
    try {
//		this->close();
//		par->close();
        qApp->quit();   // 或者   aApp->closeAllWindows();
        QProcess::startDetached(qApp->applicationFilePath(), QStringList());
        exit(0);
    }
	catch(...)
	{
		;
	}
}

void end::keyPressEvent(QKeyEvent *event)
{
    if (event->key()==Qt::Key_Escape)
    {
//        this->close();
//        par->close();
        qDebug("Called.");
        qApp->quit();   // 或者   aApp->closeAllWindows();
        QProcess::startDetached(qApp->applicationFilePath(), QStringList());
        exit(0);
//        qDebug("%s",qApp->applicationFilePath());
    }
}


