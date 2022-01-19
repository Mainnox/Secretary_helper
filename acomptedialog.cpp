#include "acomptedialog.h"
#include "ui_acomptedialog.h"
#include <QMessageBox>

AcompteDialog::AcompteDialog(QString name, QString numero, double reste, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AcompteDialog)
{
    ui->setupUi(this);
    ui->numero->setText(numero);
    ui->nom->setText(name);
    ui->reste->setValue(reste);
    ui->dateEdit->setDate(QDate::currentDate());
    m_reste = reste;
    m_ok = false;
}

AcompteDialog::~AcompteDialog()
{
    delete ui;
}

bool    AcompteDialog::getok()
{
    return (m_ok);
}

void    AcompteDialog::setnumero(QString numero)
{
    m_numero = numero;
}

void    AcompteDialog::setreste(double reste)
{
    m_reste = reste;
}

void    AcompteDialog::setdate(QString date)
{
    m_date = date;
}

void    AcompteDialog::setname(QString name)
{
    m_nom = name;
}

void    AcompteDialog::setattente(bool attente)
{
    m_attente = attente;
}

void AcompteDialog::on_montant_valueChanged(double arg1)
{
    if (arg1 > m_reste)
    {
        ui->montant->setValue(m_reste);
        ui->reste->setValue(0);
    }
    else
        ui->reste->setValue(m_reste - arg1);
}

void AcompteDialog::on_annuler_clicked()
{
    m_ok = false;
    close();
}

void AcompteDialog::on_accepter_clicked()
{
    m_montant = ui->montant->value();
    if (m_montant)
        m_ok = true;
    else
        m_ok = false;
    close();
}

void AcompteDialog::on_dateEdit_userDateChanged(const QDate &date)
{
    m_date = date.toString("dd.MM.yyyy");
}

double AcompteDialog::getreste(void)
{
    return (m_reste);
}

double AcompteDialog::getmontant(void)
{
    return (m_montant);
}

QString AcompteDialog::getdate(void)
{
    return (m_date);
}
