#ifndef FOOTAGEDIALOG_H
#define FOOTAGEDIALOG_H

#include <QDialog>

namespace Ui {
class FootageDialog;
}

class FootageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FootageDialog(QWidget *parent = nullptr);
    ~FootageDialog();

private:
    Ui::FootageDialog *ui;
};

#endif // FOOTAGEDIALOG_H
