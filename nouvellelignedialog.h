#ifndef NOUVELLELIGNEDIALOG_H
#define NOUVELLELIGNEDIALOG_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class NouvelleLigneDialog;
}

class NouvelleLigneDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NouvelleLigneDialog(QWidget *parent = nullptr);
    ~NouvelleLigneDialog();
    QString getname();
    QString getref();
    QString getdimension();
    QString gettypes();
    int     getnombre();
    double  getprix_u();
    double  getprix_t();
    bool    getok();

private slots:
    void on_lineEdit_textChanged(const QString &arg1);

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_lineEdit_3_textChanged(const QString &arg1);

    void on_comboBox_activated(const QString &arg1);

    void on_spinBox_valueChanged(int arg1);

    void on_doubleSpinBox_valueChanged(double arg1);

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_comboBox_2_currentIndexChanged(const QString &arg1);

private:
    Ui::NouvelleLigneDialog *ui;
    QString m_name;
    QString m_ref;
    QString m_dimension;
    QString m_types;
    QString m_civ;
    int     m_nombre;
    double  m_prix_u;
    double  m_prix_t;
    bool    m_ok;
};

#endif // NOUVELLELIGNEDIALOG_H
