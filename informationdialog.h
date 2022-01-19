#ifndef INFORMATIONDIALOG_H
#define INFORMATIONDIALOG_H

#include <QDialog>

namespace Ui {
class informationDialog;
}

class informationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit informationDialog(QWidget *parent = nullptr);
    ~informationDialog();

private:
    Ui::informationDialog *ui;
};

#endif // INFORMATIONDIALOG_H
