#ifndef FORMHEADERDIALOG_H
#define FORMHEADERDIALOG_H

#include <QDialog>
#include <QDate>
#include <QCompleter>
#include <QDir>
#include <QMessageBox>

namespace Ui {
class formheaderDialog;
}

class formheaderDialog : public QDialog
{
    Q_OBJECT

public:
    explicit formheaderDialog(QWidget *parent = nullptr);
    ~formheaderDialog();
    QString     getname();
    QString     getnumero();
    QDate       getdate();
    QString     getadresse();
    QString     getcomplement();
    bool        getok();
    QString     getville();
    void        setcomplete();
    QString     getciv();

private slots:
    void on_lineEdit_textChanged(const QString &arg1);

    void on_lineEdit_2_textChanged(const QString &arg1);

    void on_dateEdit_dateChanged(const QDate &date);

    void on_lineEdit_3_textChanged(const QString &arg1);

    void on_lineEdit_4_textChanged(const QString &arg1);

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_lineEdit_5_textChanged(const QString &arg1);

    void on_comboBox_currentIndexChanged(const QString &arg1);

private:
    Ui::formheaderDialog *ui;
    QString m_name;
    QString m_numero;
    QString m_adresse;
    QString m_complement;
    QString m_ville;
    QString m_civ;
    QDate m_date;
    QStringList m_complete;
    bool        m_ok;
};

#endif // FORMHEADERDIALOG_H
