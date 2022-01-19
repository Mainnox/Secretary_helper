#ifndef FORMTOTALDIALOG_H
#define FORMTOTALDIALOG_H

#include <QDialog>

namespace Ui {
class FormTotalDialog;
}

class FormTotalDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FormTotalDialog(QWidget *parent = nullptr);
    ~FormTotalDialog();
    bool                getok();
    double              gettva();
    double              getaccompte();

private slots:
    void on_checkBox_clicked(bool checked);

    void on_doubleSpinBox_valueChanged(double arg1);

    void on_doubleSpinBox_2_valueChanged(double arg1);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::FormTotalDialog *ui;
    bool                m_ok;
    double              m_tva;
    double              m_accompte;
};

#endif // FORMTOTALDIALOG_H
