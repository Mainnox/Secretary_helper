#include "formheaderdialog.h"
#include "ui_formheaderdialog.h"

formheaderDialog::formheaderDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::formheaderDialog)
{
    ui->setupUi(this);
    m_name = "";
    m_numero = "";
    m_adresse = "";
    m_complement = "";
    m_ville = "";
    m_civ = "";
    m_ok = false;
    ui->dateEdit->setDate(QDate::currentDate());
    m_date = QDate::currentDate();
    setcomplete();
}

formheaderDialog::~formheaderDialog()
{
    delete ui;
}

void formheaderDialog::on_lineEdit_textChanged(const QString &arg1)
{
    if (arg1.contains(',') || arg1.contains('\\') || arg1.contains('/'))
    {
        QMessageBox::warning(this, "Erreur", "Les noms et les numero ne peuvent pas contenir ces charateres : /\\,");
        ui->lineEdit->clear();
    }
    else
        m_name = arg1;
}

void formheaderDialog::on_lineEdit_2_textChanged(const QString &arg1)
{
    if (arg1.contains(',') || arg1.contains('\\') || arg1.contains('/'))
    {
        QMessageBox::warning(this, "Erreur", "Les noms et les numero ne peuvent pas contenir ces charateres : /\\,");
        ui->lineEdit_2->clear();
    }
    else
        m_numero = arg1;
}

void formheaderDialog::on_dateEdit_dateChanged(const QDate &date)
{
    m_date = date;
}

void formheaderDialog::on_lineEdit_3_textChanged(const QString &arg1)
{
    m_adresse = arg1;
}


void formheaderDialog::on_lineEdit_4_textChanged(const QString &arg1)
{
    m_complement = arg1;
}

QString formheaderDialog::getname()
{
    return (m_name);
}

QString formheaderDialog::getnumero()
{
    return (m_numero);
}

QString formheaderDialog::getadresse()
{
    return (m_adresse);
}

QString formheaderDialog::getcomplement()
{
    return (m_complement);
}

QDate   formheaderDialog::getdate()
{
    return (m_date);
}

QString formheaderDialog::getciv()
{
    return (m_civ);
}

void    formheaderDialog::setcomplete()
{
    QDir dir(QApplication::applicationDirPath() + "/Facture/");
    QStringList entry_list = dir.entryList(QDir::Dirs);
    for (int i = 2; i < entry_list.size(); i++)
    {
        QDir dir(QApplication::applicationDirPath() + "/Facture/" + entry_list[i] + "/");
        QStringList fac_list = dir.entryList(QDir::Files);
        for (int j = 0; j < fac_list.size(); j++)
        {
            fac_list[j].chop(4);
            if (m_complete.lastIndexOf(fac_list[j]) == -1)
                m_complete.append(fac_list[j]);
        }
    }
    m_complete.sort();
    QCompleter *completer = new QCompleter(m_complete, this);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setFilterMode(Qt::MatchContains);
    ui->lineEdit->setCompleter(completer);
}

void formheaderDialog::on_pushButton_2_clicked()
{
    m_ok = false;
    close();
}

void formheaderDialog::on_pushButton_clicked()
{
    if (m_name.isEmpty() || m_numero.isEmpty() || m_adresse.isEmpty() || m_ville.isEmpty())
    {
        QMessageBox::warning(this, "Erreur", "Les champs nom, numero, ville et adresse sont obligatoires !");
        return;
    }
    m_ok = true;
    close();
}

bool formheaderDialog::getok()
{
    return (m_ok);
}

void formheaderDialog::on_lineEdit_5_textChanged(const QString &arg1)
{
    m_ville = arg1;
}

QString formheaderDialog::getville()
{
    return (m_ville);
}

void formheaderDialog::on_comboBox_currentIndexChanged(const QString &arg1)
{
    m_civ = arg1;
}
