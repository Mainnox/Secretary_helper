#ifndef FORMULAREDIALOG_H
#define FORMULAREDIALOG_H

#include <QDialog>
#include <QDate>
#include <QFile>
#include <QInputDialog>

namespace Ui {
class FormulareDialog;
}

class FormulareDialog : public QDialog
{
    Q_OBJECT

public:
    explicit    FormulareDialog(QWidget *parent = nullptr);
                ~FormulareDialog();
    void        sort(QString path);
    void        setComplete();

private slots:
    void on_Name_textChanged(const QString &arg1);

    void on_Numero_textChanged(const QString &arg1);

    void on_HT_valueChanged(double arg1);

    void on_TVA_valueChanged(double arg1);

    void on_TTC_valueChanged(double arg1);

    void on_pushButton_clicked();

    void on_radioButton_2_toggled(bool checked);

    void on_radioButton_3_toggled(bool checked);

    void on_radioButton_toggled(bool checked);

    void on_dateEdit_userDateChanged(const QDate &date);

private:
    Ui::FormulareDialog *ui;
    QStringList     m_complete;
    QString         m_numero;
    QString         m_name;
    QString         m_type;
    double          m_ht;
    double          m_tva;
    double          m_ttc;
    QDate           m_date;
};

#endif // FORMULAREDIALOG_H
