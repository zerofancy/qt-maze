#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include"QDialog"
#include "widget.h"
#include"frmhelp.h"

namespace Ui {
class Menu;
}

class Menu : public QDialog
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = 0);
    ~Menu();

    int S_result=0;

    int size_N;

private slots:


    void on_play_clicked();

    void on_help_clicked();

    void on_exit_clicked();

    void on_verticalSlider_actionTriggered(int action);

private:
    Ui::Menu *ui;
    bool isPress=false;
    QPoint point;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
};

#endif // MENU_H
