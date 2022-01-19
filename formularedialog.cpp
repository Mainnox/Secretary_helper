#include "formularedialog.h"
#include "ui_formularedialog.h"

#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QString>
#include <QDir>
#include <QDate>
#include <QCompleter>

FormulareDialog::FormulareDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FormulareDialog)
{
    m_ht = 0;
    m_ttc = 0;
    m_type = "";
    m_tva = 0;
    m_numero = "";
    m_name = "";
    ui->setupUi(this);
    setComplete();
    ui->dateEdit->setDate(QDate::currentDate());
    m_date = QDate::currentDate();
}

FormulareDialog::~FormulareDialog()
{
    delete ui;
}

void FormulareDialog::sort(QString path)
{
    QStringList stringlist;
    QFile file(path);

    if (!file.open(QFile::ReadOnly))
        QMessageBox::warning(this, "Error", "File cannot open");
    QTextStream textfile(&file);

    while (1)
    {
        QString line = textfile.readLine();
        if (line.isNull())
            break;
        else
            stringlist.append(line);
    }
    file.remove();
    if (!file.open(QFile::WriteOnly))
        QMessageBox::warning(this, "Error", "File cannot open");
    QTextStream textfile2(&file);
    stringlist.sort();
    for (int i = 0; i < stringlist.size(); i++)
        textfile2 << stringlist.at(i) << Qt::endl;
    file.flush();
    file.close();
}


void FormulareDialog::on_Name_textChanged(const QString &arg1)
{
    if (arg1.contains(',') || arg1.contains('\\') || arg1.contains('/'))
    {
        QMessageBox::warning(this, "Erreur", "Les noms et les numero ne peuvent pas contenir ces charateres : /\\,");
        ui->Name->clear();
    }
    else
        m_name = arg1;
}

void FormulareDialog::on_Numero_textChanged(const QString &arg1)
{
    if (arg1.contains(',') || arg1.contains('\\') || arg1.contains('/'))
    {
        QMessageBox::warning(this, "Erreur", "Les noms et les numero ne peuvent pas contenir ces charateres : /\\,");
        ui->Numero->clear();
    }
    m_numero = arg1;
}

void FormulareDialog::on_HT_valueChanged(double arg1)
{
    m_ht = arg1;
    ui->TTC->setValue(m_ht + m_tva);
}

void FormulareDialog::on_TVA_valueChanged(double arg1)
{
    m_tva = arg1;
    ui->TTC->setValue(m_ht + m_tva);
}

void FormulareDialog::on_TTC_valueChanged(double arg1)
{
    m_ttc = arg1;
}

void FormulareDialog::on_pushButton_clicked()
{
    const QString filename = QCoreApplication::applicationDirPath()
            + "/Facture/" + m_type + "/" + this->m_name + ".fac";
    bool ok;
    if (m_name == "" || m_numero == "" || m_type == "")
    {
        QMessageBox::warning(this, "Error", "Les champs nom, type et numero sont obligatoires");
        return;
    }
    double acompte = QInputDialog::getDouble(this, "Acompte", "Acompte", 0, 0, m_ttc, 2, &ok);
    if (!ok)
        return;
    QFile file(filename);

    if (!file.open(QFile::ReadWrite | QFile::Append))
        QMessageBox::warning(this, "Error", "File cannot open");
    QTextStream out(&file);
    QString save = m_date.toString(Qt::ISODate) + ','
            + m_name + ',' + m_numero + ','
            + QString::number(m_ht, 'f', 2) + ','
            + QString::number(m_tva, 'f', 2) + ','
            + QString::number(m_ttc, 'f', 2) + ','
            + m_type + '\n';
    out << save;
    file.flush();
    file.close();
    sort(filename);
    QString filename2;
    if (acompte)
    {
        QFile regle(QCoreApplication::applicationDirPath() + "/Payement/reglement/" + m_name + ".pay");
        if (!regle.open(QFile::ReadWrite | QFile::Append))
            QMessageBox::warning(this, "Error", "File cannot open");
        QTextStream hugo_sama(&regle);
        hugo_sama << m_date.toString(Qt::ISODate) + "," + m_numero + "," + QString::number(acompte, 'f', 2) + '\n';
        regle.close();
        if (acompte == m_ttc)
        {
            close();
            return;
        }
        filename2 = QCoreApplication::applicationDirPath() + "/Payement/cours/" + m_name + ".pay";
    }
    else
        filename2 = QCoreApplication::applicationDirPath() + "/Payement/attente/" + m_name + ".pay";
    QFile file2(filename2);
    if (!file2.open(QFile::ReadWrite | QFile::Append))
        QMessageBox::warning(this, "Error", "File cannot open");
    QTextStream out2(&file2);
    QString save2;
    if (acompte)
        save2 = m_date.toString(Qt::ISODate) + ','
                + m_name + ',' + m_numero + ','
                + QString::number(m_ttc, 'f', 2) + ','
                + QString::number(m_ttc - acompte, 'f', 2)
                + '\n';
    else
        save2 = m_date.toString(Qt::ISODate) + ','
                + m_name + ',' + m_numero + ','
                + QString::number(m_ttc, 'f', 2)
                + '\n';
    out2 << save2;
    file2.flush();
    file2.close();
    close();
}

void FormulareDialog::on_radioButton_2_toggled(bool checked)
{
    if (checked)
        m_type = "Vente";
}

void FormulareDialog::on_radioButton_3_toggled(bool checked)
{
    if (checked)
        m_type = "Divers";
}

void FormulareDialog::on_radioButton_toggled(bool checked)
{
    if (checked)
        m_type = "Achat";
}

void FormulareDialog::on_dateEdit_userDateChanged(const QDate &date)
{
    m_date = date;
}

void FormulareDialog::setComplete()
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
    ui->Name->setCompleter(completer);
}
