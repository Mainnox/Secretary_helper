#include "titredialog.h"
#include "ui_titredialog.h"

titreDialog::titreDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::titreDialog)
{
    ui->setupUi(this);
    m_titre = "";
}

titreDialog::~titreDialog()
{
    delete ui;
}

void titreDialog::on_lineEdit_textChanged(const QString &arg1)
{
    m_titre = arg1;
}

void titreDialog::on_pushButton_clicked()
{
    if (m_titre.isEmpty())
        QMessageBox::warning(this, "ERREUR", "Veuillez remplir le champ avant validation");
    else
    {
        m_ok = true;
        close();
    }
}

void titreDialog::on_pushButton_2_clicked()
{
    close();
}

bool titreDialog::getok()
{
    return (m_ok);
}

QString titreDialog::gettitre()
{
    return (m_titre);
}
