#ifndef TITREDIALOG_H
#define TITREDIALOG_H

#include <QDialog>
#include <QMessageBox>

namespace Ui {
class titreDialog;
}

class titreDialog : public QDialog
{
    Q_OBJECT

public:
    explicit titreDialog(QWidget *parent = nullptr);
    ~titreDialog();
    bool        getok();
    QString     gettitre();

private slots:
    void on_lineEdit_textChanged(const QString &arg1);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::titreDialog *ui;
    QString m_titre;
    bool m_ok = false;
};

#endif // TITREDIALOG_H
