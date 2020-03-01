#ifndef FRMHELP_H
#define FRMHELP_H

#include <QWidget>
#include"QDialog"
#include"QBitmap"
#include"QKeyEvent"

namespace Ui {
class frmHelp;
}

class frmHelp : public QDialog
{
    Q_OBJECT

public:
    explicit frmHelp(QDialog *parent = 0);
    ~frmHelp();

private:
    Ui::frmHelp *ui;
    void keyPressEvent(QKeyEvent *event);

};

#endif // FRMHELP_H
