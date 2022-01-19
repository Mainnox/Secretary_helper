#ifndef NOUVELLEIMAGEDIALOG_H
#define NOUVELLEIMAGEDIALOG_H

#include <QDialog>

namespace Ui {
class nouvelleImageDialog;
}

class nouvelleImageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit nouvelleImageDialog(QWidget *parent = nullptr);
    ~nouvelleImageDialog();

private:
    Ui::nouvelleImageDialog *ui;
};

#endif // NOUVELLEIMAGEDIALOG_H
