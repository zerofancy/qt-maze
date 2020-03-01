#ifndef END_H
#define END_H

#include <QWidget>
#include"QTimer"
#include"QKeyEvent"

namespace Ui {
class end;
}

class end : public QWidget
{
    Q_OBJECT

public:
    explicit end(QWidget *parent = 0);
    QTimer *time=new QTimer;
    void (*s_img)()=NULL;
    ~end();
QWidget *par;
private:
    Ui::end *ui;
    void keyPressEvent(QKeyEvent *event);
public slots:
    void close1();

};

#endif // END_H
