#ifndef ACOMPTEDIALOG_H
#define ACOMPTEDIALOG_H

#include <QDialog>
#include <QModelIndex>
#include <QDate>

namespace Ui {
class AcompteDialog;
}

class AcompteDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AcompteDialog(QString name, QString numero, double reste, QWidget *parent = nullptr);
    ~AcompteDialog();
    void    setnumero(QString numero);
    void    setdate(QString date);
    void    setname(QString name);
    void    setreste(double reste);
    void    setattente(bool attente);

    bool    getok();
    double  getmontant(void);
    double  getreste(void);
    QString getdate(void);

private slots:
    void on_montant_valueChanged(double arg1);

    void on_annuler_clicked();

    void on_accepter_clicked();

    void on_dateEdit_userDateChanged(const QDate &date);

private:
    Ui::AcompteDialog *ui;

    bool m_ok;
    bool m_attente;
    QString m_numero;
    QString m_date;
    QString m_nom;
    double m_reste;
    double m_montant;
};

#endif // ACOMPTEDIALOG_H
