#include "bilandialog.h"
#include "ui_bilandialog.h"
#include <QDir>
#include <QMessageBox>
#include <QTextStream>
#include <QScrollArea>

BilanDialog::BilanDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BilanDialog)
{
    ui->setupUi(this);
    setupall();
    for (int i = 0; i < m_year_list.size(); i++)
    {
        ui->comboBox->addItem(getyear(m_year_list[i]));
    }
    fillyear(0);
}

BilanDialog::~BilanDialog()
{
    delete ui;
}

void        BilanDialog::setupall()
{
    QStringList list;
    QStringList fac_list;
    QDir dir(QApplication::applicationDirPath() + "/Facture/");
    list = dir.entryList(QDir::AllDirs);
    for (int i = 2; i < list.size(); i++)
    {
        QDir fol(QApplication::applicationDirPath() + "/Facture/" + list[i] + "/");
        QStringList list2 = fol.entryList(QDir::Files);
        for (int j = 0; j < list2.size(); j++)
        {
            QFile file(QApplication::applicationDirPath() + "/Facture/" + list[i] + "/" + list2[j]);
            if (!file.open(QFile::ReadOnly))
                QMessageBox::warning(this, "Error", "File cannot open");
            QTextStream textfile(&file);
            while (1)
            {
                QString line = textfile.readLine();
                if (line.isNull())
                    break;
                else
                    fac_list.append(line + "," + list[i]);
            }
            file.close();
        }
    }
    fac_list.sort();
    setupyear(fac_list);
}

void        BilanDialog::setupyear(const QStringList fac_list)
{
    int i = 0;

    while (i < fac_list.size())
    {
        QString tmp = fac_list[i];
        if (fac_list[i][5] != '0' || fac_list[i][6] >= '5')
            tmp[3] = tmp[3].toLatin1() + 1;
        tmp[6] = '4';
        tmp[8] = '3';
        QStringList list;
        while (i < fac_list.size() && (fac_list[i].compare(tmp)) <= 0)
        {
            list << fac_list[i];
            i++;
        }
        m_year_list.append(list);
    }
}

void           BilanDialog::showfac_list()
{
    for (int i = 0; i < m_year_list.size(); i++)
    {
        QMessageBox::information(this, "title", m_year_list[i].join("\n"));
    }
}

QString        BilanDialog::getyear(QStringList fac)
{
    QStringList list = fac[0].split('-');

    if (list[1][0] != '0' || list[1][1] >= '5')
        return (list[0] + "-" + QString::number(list[0].toInt() + 1));
    return (QString::number(list[0].toInt() - 1) + "-" + list[0]);
}

void            BilanDialog::fillyear(int i)
{
    m_t_ht = 0;
    m_t_tva = 0;
    m_t_ttc = 0;
    int j = 0;
    set_ma(m_year_list[i], j);
    set_ju(m_year_list[i], j);
    set_jul(m_year_list[i], j);
    set_a(m_year_list[i], j);
    set_s(m_year_list[i], j);
    set_o(m_year_list[i], j);
    set_n(m_year_list[i], j);
    set_d(m_year_list[i], j);
    set_j(m_year_list[i], j);
    set_f(m_year_list[i], j);
    set_m(m_year_list[i], j);
    set_av(m_year_list[i], j);

    ui->Total_HT->setText(QString::number(m_t_ht, 'f', 2) + " HT");
    ui->Total_TVA->setText(QString::number(m_t_tva, 'f', 2) + " TVA");
    ui->Total_TTC->setText(QString::number(m_t_ttc, 'f', 2) + " TTC");
}

void        BilanDialog::set_j(QStringList const year, int &i)
{
    double t_achat_ht = 0;
    double t_vente_ht = 0;
    double t_diver_ht = 0;
    double t_achat_tva = 0;
    double t_vente_tva = 0;
    double t_diver_tva = 0;
    double t_achat_ttc = 0;
    double t_vente_ttc = 0;
    double t_diver_ttc = 0;

    t_achat_ht = 0;
    while (i < year.size())
    {
        if (year[i][6] != '1' || year[i][5] != '0')
            break;
        QStringList list = year[i].split(",");
        if (list[6] == "Achat")
        {
            t_achat_ht += list[3].toDouble();
            t_achat_tva += list[4].toDouble();
            t_achat_ttc += list[5].toDouble();
        }
        if (list[6] == "Vente")
        {
            t_vente_ht += list[3].toDouble();
            t_vente_tva += list[4].toDouble();
            t_vente_ttc += list[5].toDouble();
        }
        if (list[6] == "Divers")
        {
            t_diver_ht += list[3].toDouble();
            t_diver_tva += list[4].toDouble();
            t_diver_ttc += list[5].toDouble();
        }
        i++;
    }
    ui->Achat_HT_1->setText(QString::number(t_achat_ht, 'f', 2) + " HT");
    ui->Achat_TVA_1->setText(QString::number(t_achat_tva, 'f', 2) + " TVA");
    ui->Achat_TTC_1->setText(QString::number(t_achat_ttc, 'f', 2) + " TTC");
    ui->Vente_HT_1->setText(QString::number(t_vente_ht, 'f', 2) + " HT");
    ui->Vente_TVA_1->setText(QString::number(t_vente_tva, 'f', 2) + " TVA");
    ui->Vente_TTC_1->setText(QString::number(t_vente_ttc, 'f', 2) + " TTC");
    ui->Divers_HT_1->setText(QString::number(t_diver_ht, 'f', 2) + " HT");
    ui->Divers_TVA_1->setText(QString::number(t_diver_tva, 'f', 2) + " TVA");
    ui->Divers_TTC_1->setText(QString::number(t_diver_ttc, 'f', 2) + " TTC");
    ui->Total_HT_1->setText(QString::number(t_vente_ht - (t_achat_ht + t_diver_ht), 'f', 2) + " HT");
    ui->Total_TVA_1->setText(QString::number(t_vente_tva - (t_achat_tva + t_diver_tva), 'f', 2) + " TVA");
    ui->Total_TTC_1->setText(QString::number(t_vente_ttc - (t_achat_ttc + t_diver_ttc), 'f', 2) + " TTC");
    m_t_ht += t_vente_ht - (t_achat_ht + t_diver_ht);
    m_t_tva += t_vente_tva - (t_achat_tva + t_diver_tva);
    m_t_ttc += t_vente_ttc - (t_achat_ttc + t_diver_ttc);
}

void        BilanDialog::set_f(QStringList const year, int &i)
{
    double t_achat_ht = 0;
    double t_vente_ht = 0;
    double t_diver_ht = 0;
    double t_achat_tva = 0;
    double t_vente_tva = 0;
    double t_diver_tva = 0;
    double t_achat_ttc = 0;
    double t_vente_ttc = 0;
    double t_diver_ttc = 0;

    t_achat_ht = 0;
    while (i < year.size())
    {
        if (year[i][6] != '2' || year[i][5] != '0')
            break;
        QStringList list = year[i].split(",");
        if (list[6] == "Achat")
        {
            t_achat_ht += list[3].toDouble();
            t_achat_tva += list[4].toDouble();
            t_achat_ttc += list[5].toDouble();
        }
        if (list[6] == "Vente")
        {
            t_vente_ht += list[3].toDouble();
            t_vente_tva += list[4].toDouble();
            t_vente_ttc += list[5].toDouble();
        }
        if (list[6] == "Divers")
        {
            t_diver_ht += list[3].toDouble();
            t_diver_tva += list[4].toDouble();
            t_diver_ttc += list[5].toDouble();
        }
        i++;
    }
    ui->Achat_HT_2->setText(QString::number(t_achat_ht, 'f', 2) + " HT");
    ui->Achat_TVA_2->setText(QString::number(t_achat_tva, 'f', 2) + " TVA");
    ui->Achat_TTC_2->setText(QString::number(t_achat_ttc, 'f', 2) + " TTC");
    ui->Vente_HT_2->setText(QString::number(t_vente_ht, 'f', 2) + " HT");
    ui->Vente_TVA_2->setText(QString::number(t_vente_tva, 'f', 2) + " TVA");
    ui->Vente_TTC_2->setText(QString::number(t_vente_ttc, 'f', 2) + " TTC");
    ui->Divers_HT_2->setText(QString::number(t_diver_ht, 'f', 2) + " HT");
    ui->Divers_TVA_2->setText(QString::number(t_diver_tva, 'f', 2) + " TVA");
    ui->Divers_TTC_2->setText(QString::number(t_diver_ttc, 'f', 2) + " TTC");
    ui->Total_HT_2->setText(QString::number(t_vente_ht - (t_achat_ht + t_diver_ht), 'f', 2) + " HT");
    ui->Total_TVA_2->setText(QString::number(t_vente_tva - (t_achat_tva + t_diver_tva), 'f', 2) + " TVA");
    ui->Total_TTC_2->setText(QString::number(t_vente_ttc - (t_achat_ttc + t_diver_ttc), 'f', 2) + " TTC");
    m_t_ht += t_vente_ht - (t_achat_ht + t_diver_ht);
    m_t_tva += t_vente_tva - (t_achat_tva + t_diver_tva);
    m_t_ttc += t_vente_ttc - (t_achat_ttc + t_diver_ttc);
}

void        BilanDialog::set_m(QStringList const year, int &i)
{
    double t_achat_ht = 0;
    double t_vente_ht = 0;
    double t_diver_ht = 0;
    double t_achat_tva = 0;
    double t_vente_tva = 0;
    double t_diver_tva = 0;
    double t_achat_ttc = 0;
    double t_vente_ttc = 0;
    double t_diver_ttc = 0;

    t_achat_ht = 0;
    while (i < year.size())
    {
        if (year[i][6] != '3')
            break;
        QStringList list = year[i].split(",");
        if (list[6] == "Achat")
        {
            t_achat_ht += list[3].toDouble();
            t_achat_tva += list[4].toDouble();
            t_achat_ttc += list[5].toDouble();
        }
        if (list[6] == "Vente")
        {
            t_vente_ht += list[3].toDouble();
            t_vente_tva += list[4].toDouble();
            t_vente_ttc += list[5].toDouble();
        }
        if (list[6] == "Divers")
        {
            t_diver_ht += list[3].toDouble();
            t_diver_tva += list[4].toDouble();
            t_diver_ttc += list[5].toDouble();
        }
        i++;
    }
    ui->Achat_HT_3->setText(QString::number(t_achat_ht, 'f', 2) + " HT");
    ui->Achat_TVA_3->setText(QString::number(t_achat_tva, 'f', 2) + " TVA");
    ui->Achat_TTC_3->setText(QString::number(t_achat_ttc, 'f', 2) + " TTC");
    ui->Vente_HT_3->setText(QString::number(t_vente_ht, 'f', 2) + " HT");
    ui->Vente_TVA_3->setText(QString::number(t_vente_tva, 'f', 2) + " TVA");
    ui->Vente_TTC_3->setText(QString::number(t_vente_ttc, 'f', 2) + " TTC");
    ui->Divers_HT_3->setText(QString::number(t_diver_ht, 'f', 2) + " HT");
    ui->Divers_TVA_3->setText(QString::number(t_diver_tva, 'f', 2) + " TVA");
    ui->Divers_TTC_3->setText(QString::number(t_diver_ttc, 'f', 2) + " TTC");
    ui->Total_HT_3->setText(QString::number(t_vente_ht - (t_achat_ht + t_diver_ht), 'f', 2) + " HT");
    ui->Total_TVA_3->setText(QString::number(t_vente_tva - (t_achat_tva + t_diver_tva), 'f', 2) + " TVA");
    ui->Total_TTC_3->setText(QString::number(t_vente_ttc - (t_achat_ttc + t_diver_ttc), 'f', 2) + " TTC");
    m_t_ht += t_vente_ht - (t_achat_ht + t_diver_ht);
    m_t_tva += t_vente_tva - (t_achat_tva + t_diver_tva);
    m_t_ttc += t_vente_ttc - (t_achat_ttc + t_diver_ttc);
}

void        BilanDialog::set_av(QStringList const year, int &i)
{
    double t_achat_ht = 0;
    double t_vente_ht = 0;
    double t_diver_ht = 0;
    double t_achat_tva = 0;
    double t_vente_tva = 0;
    double t_diver_tva = 0;
    double t_achat_ttc = 0;
    double t_vente_ttc = 0;
    double t_diver_ttc = 0;

    t_achat_ht = 0;
    while (i < year.size())
    {
        if (year[i][6] != '4')
            break;
        QStringList list = year[i].split(",");
        if (list[6] == "Achat")
        {
            t_achat_ht += list[3].toDouble();
            t_achat_tva += list[4].toDouble();
            t_achat_ttc += list[5].toDouble();
        }
        if (list[6] == "Vente")
        {
            t_vente_ht += list[3].toDouble();
            t_vente_tva += list[4].toDouble();
            t_vente_ttc += list[5].toDouble();
        }
        if (list[6] == "Divers")
        {
            t_diver_ht += list[3].toDouble();
            t_diver_tva += list[4].toDouble();
            t_diver_ttc += list[5].toDouble();
        }
        i++;
    }
    ui->Achat_HT_4->setText(QString::number(t_achat_ht, 'f', 2) + " HT");
    ui->Achat_TVA_4->setText(QString::number(t_achat_tva, 'f', 2) + " TVA");
    ui->Achat_TTC_4->setText(QString::number(t_achat_ttc, 'f', 2) + " TTC");
    ui->Vente_HT_4->setText(QString::number(t_vente_ht, 'f', 2) + " HT");
    ui->Vente_TVA_4->setText(QString::number(t_vente_tva, 'f', 2) + " TVA");
    ui->Vente_TTC_4->setText(QString::number(t_vente_ttc, 'f', 2) + " TTC");
    ui->Divers_HT_4->setText(QString::number(t_diver_ht, 'f', 2) + " HT");
    ui->Divers_TVA_4->setText(QString::number(t_diver_tva, 'f', 2) + " TVA");
    ui->Divers_TTC_4->setText(QString::number(t_diver_ttc, 'f', 2) + " TTC");
    ui->Total_HT_4->setText(QString::number(t_vente_ht - (t_achat_ht + t_diver_ht), 'f', 2) + " HT");
    ui->Total_TVA_4->setText(QString::number(t_vente_tva - (t_achat_tva + t_diver_tva), 'f', 2) + " TVA");
    ui->Total_TTC_4->setText(QString::number(t_vente_ttc - (t_achat_ttc + t_diver_ttc), 'f', 2) + " TTC");
    m_t_ht += t_vente_ht - (t_achat_ht + t_diver_ht);
    m_t_tva += t_vente_tva - (t_achat_tva + t_diver_tva);
    m_t_ttc += t_vente_ttc - (t_achat_ttc + t_diver_ttc);
}

void        BilanDialog::set_ma(QStringList const year, int &i)
{
    double t_achat_ht = 0;
    double t_vente_ht = 0;
    double t_diver_ht = 0;
    double t_achat_tva = 0;
    double t_vente_tva = 0;
    double t_diver_tva = 0;
    double t_achat_ttc = 0;
    double t_vente_ttc = 0;
    double t_diver_ttc = 0;

    t_achat_ht = 0;
    while (i < year.size())
    {
        if (year[i][6] != '5')
            break;
        QStringList list = year[i].split(",");
        if (list[6] == "Achat")
        {
            t_achat_ht += list[3].toDouble();
            t_achat_tva += list[4].toDouble();
            t_achat_ttc += list[5].toDouble();
        }
        if (list[6] == "Vente")
        {
            t_vente_ht += list[3].toDouble();
            t_vente_tva += list[4].toDouble();
            t_vente_ttc += list[5].toDouble();
        }
        if (list[6] == "Divers")
        {
            t_diver_ht += list[3].toDouble();
            t_diver_tva += list[4].toDouble();
            t_diver_ttc += list[5].toDouble();
        }
        i++;
    }
    ui->Achat_HT_5->setText(QString::number(t_achat_ht, 'f', 2) + " HT");
    ui->Achat_TVA_5->setText(QString::number(t_achat_tva, 'f', 2) + " TVA");
    ui->Achat_TTC_5->setText(QString::number(t_achat_ttc, 'f', 2) + " TTC");
    ui->Vente_HT_5->setText(QString::number(t_vente_ht, 'f', 2) + " HT");
    ui->Vente_TVA_5->setText(QString::number(t_vente_tva, 'f', 2) + " TVA");
    ui->Vente_TTC_5->setText(QString::number(t_vente_ttc, 'f', 2) + " TTC");
    ui->Divers_HT_5->setText(QString::number(t_diver_ht, 'f', 2) + " HT");
    ui->Divers_TVA_5->setText(QString::number(t_diver_tva, 'f', 2) + " TVA");
    ui->Divers_TTC_5->setText(QString::number(t_diver_ttc, 'f', 2) + " TTC");
    ui->Total_HT_5->setText(QString::number(t_vente_ht - (t_achat_ht + t_diver_ht), 'f', 2) + " HT");
    ui->Total_TVA_5->setText(QString::number(t_vente_tva - (t_achat_tva + t_diver_tva), 'f', 2) + " TVA");
    ui->Total_TTC_5->setText(QString::number(t_vente_ttc - (t_achat_ttc + t_diver_ttc), 'f', 2) + " TTC");
    m_t_ht += t_vente_ht - (t_achat_ht + t_diver_ht);
    m_t_tva += t_vente_tva - (t_achat_tva + t_diver_tva);
    m_t_ttc += t_vente_ttc - (t_achat_ttc + t_diver_ttc);
}

void        BilanDialog::set_ju(QStringList const year, int &i)
{
    double t_achat_ht = 0;
    double t_vente_ht = 0;
    double t_diver_ht = 0;
    double t_achat_tva = 0;
    double t_vente_tva = 0;
    double t_diver_tva = 0;
    double t_achat_ttc = 0;
    double t_vente_ttc = 0;
    double t_diver_ttc = 0;

    t_achat_ht = 0;
    while (i < year.size())
    {
        if (year[i][6] != '6')
            break;
        QStringList list = year[i].split(",");
        if (list[6] == "Achat")
        {
            t_achat_ht += list[3].toDouble();
            t_achat_tva += list[4].toDouble();
            t_achat_ttc += list[5].toDouble();
        }
        if (list[6] == "Vente")
        {
            t_vente_ht += list[3].toDouble();
            t_vente_tva += list[4].toDouble();
            t_vente_ttc += list[5].toDouble();
        }
        if (list[6] == "Divers")
        {
            t_diver_ht += list[3].toDouble();
            t_diver_tva += list[4].toDouble();
            t_diver_ttc += list[5].toDouble();
        }
        i++;
    }
    ui->Achat_HT_6->setText(QString::number(t_achat_ht, 'f', 2) + " HT");
    ui->Achat_TVA_6->setText(QString::number(t_achat_tva, 'f', 2) + " TVA");
    ui->Achat_TTC_6->setText(QString::number(t_achat_ttc, 'f', 2) + " TTC");
    ui->Vente_HT_6->setText(QString::number(t_vente_ht, 'f', 2) + " HT");
    ui->Vente_TVA_6->setText(QString::number(t_vente_tva, 'f', 2) + " TVA");
    ui->Vente_TTC_6->setText(QString::number(t_vente_ttc, 'f', 2) + " TTC");
    ui->Divers_HT_6->setText(QString::number(t_diver_ht, 'f', 2) + " HT");
    ui->Divers_TVA_6->setText(QString::number(t_diver_tva, 'f', 2) + " TVA");
    ui->Divers_TTC_6->setText(QString::number(t_diver_ttc, 'f', 2) + " TTC");
    ui->Total_HT_6->setText(QString::number(t_vente_ht - (t_achat_ht + t_diver_ht), 'f', 2) + " HT");
    ui->Total_TVA_6->setText(QString::number(t_vente_tva - (t_achat_tva + t_diver_tva), 'f', 2) + " TVA");
    ui->Total_TTC_6->setText(QString::number(t_vente_ttc - (t_achat_ttc + t_diver_ttc), 'f', 2) + " TTC");
    m_t_ht += t_vente_ht - (t_achat_ht + t_diver_ht);
    m_t_tva += t_vente_tva - (t_achat_tva + t_diver_tva);
    m_t_ttc += t_vente_ttc - (t_achat_ttc + t_diver_ttc);
}

void        BilanDialog::set_jul(QStringList const year, int &i)
{
    double t_achat_ht = 0;
    double t_vente_ht = 0;
    double t_diver_ht = 0;
    double t_achat_tva = 0;
    double t_vente_tva = 0;
    double t_diver_tva = 0;
    double t_achat_ttc = 0;
    double t_vente_ttc = 0;
    double t_diver_ttc = 0;

    t_achat_ht = 0;
    while (i < year.size())
    {
        if (year[i][6] != '7')
            break;
        QStringList list = year[i].split(",");
        if (list[6] == "Achat")
        {
            t_achat_ht += list[3].toDouble();
            t_achat_tva += list[4].toDouble();
            t_achat_ttc += list[5].toDouble();
        }
        if (list[6] == "Vente")
        {
            t_vente_ht += list[3].toDouble();
            t_vente_tva += list[4].toDouble();
            t_vente_ttc += list[5].toDouble();
        }
        if (list[6] == "Divers")
        {
            t_diver_ht += list[3].toDouble();
            t_diver_tva += list[4].toDouble();
            t_diver_ttc += list[5].toDouble();
        }
        i++;
    }
    ui->Achat_HT_7->setText(QString::number(t_achat_ht, 'f', 2) + " HT");
    ui->Achat_TVA_7->setText(QString::number(t_achat_tva, 'f', 2) + " TVA");
    ui->Achat_TTC_7->setText(QString::number(t_achat_ttc, 'f', 2) + " TTC");
    ui->Vente_HT_7->setText(QString::number(t_vente_ht, 'f', 2) + " HT");
    ui->Vente_TVA_7->setText(QString::number(t_vente_tva, 'f', 2) + " TVA");
    ui->Vente_TTC_7->setText(QString::number(t_vente_ttc, 'f', 2) + " TTC");
    ui->Divers_HT_7->setText(QString::number(t_diver_ht, 'f', 2) + " HT");
    ui->Divers_TVA_7->setText(QString::number(t_diver_tva, 'f', 2) + " TVA");
    ui->Divers_TTC_7->setText(QString::number(t_diver_ttc, 'f', 2) + " TTC");
    ui->Total_HT_7->setText(QString::number(t_vente_ht - (t_achat_ht + t_diver_ht), 'f', 2) + " HT");
    ui->Total_TVA_7->setText(QString::number(t_vente_tva - (t_achat_tva + t_diver_tva), 'f', 2) + " TVA");
    ui->Total_TTC_7->setText(QString::number(t_vente_ttc - (t_achat_ttc + t_diver_ttc), 'f', 2) + " TTC");
    m_t_ht += t_vente_ht - (t_achat_ht + t_diver_ht);
    m_t_tva += t_vente_tva - (t_achat_tva + t_diver_tva);
    m_t_ttc += t_vente_ttc - (t_achat_ttc + t_diver_ttc);
}

void        BilanDialog::set_a(QStringList const year, int &i)
{
    double t_achat_ht = 0;
    double t_vente_ht = 0;
    double t_diver_ht = 0;
    double t_achat_tva = 0;
    double t_vente_tva = 0;
    double t_diver_tva = 0;
    double t_achat_ttc = 0;
    double t_vente_ttc = 0;
    double t_diver_ttc = 0;

    t_achat_ht = 0;
    while (i < year.size())
    {
        if (year[i][6] != '8')
            break;
        QStringList list = year[i].split(",");
        if (list[6] == "Achat")
        {
            t_achat_ht += list[3].toDouble();
            t_achat_tva += list[4].toDouble();
            t_achat_ttc += list[5].toDouble();
        }
        if (list[6] == "Vente")
        {
            t_vente_ht += list[3].toDouble();
            t_vente_tva += list[4].toDouble();
            t_vente_ttc += list[5].toDouble();
        }
        if (list[6] == "Divers")
        {
            t_diver_ht += list[3].toDouble();
            t_diver_tva += list[4].toDouble();
            t_diver_ttc += list[5].toDouble();
        }
        i++;
    }
    ui->Achat_HT_8->setText(QString::number(t_achat_ht, 'f', 2) + " HT");
    ui->Achat_TVA_8->setText(QString::number(t_achat_tva, 'f', 2) + " TVA");
    ui->Achat_TTC_8->setText(QString::number(t_achat_ttc, 'f', 2) + " TTC");
    ui->Vente_HT_8->setText(QString::number(t_vente_ht, 'f', 2) + " HT");
    ui->Vente_TVA_8->setText(QString::number(t_vente_tva, 'f', 2) + " TVA");
    ui->Vente_TTC_8->setText(QString::number(t_vente_ttc, 'f', 2) + " TTC");
    ui->Divers_HT_8->setText(QString::number(t_diver_ht, 'f', 2) + " HT");
    ui->Divers_TVA_8->setText(QString::number(t_diver_tva, 'f', 2) + " TVA");
    ui->Divers_TTC_8->setText(QString::number(t_diver_ttc, 'f', 2) + " TTC");
    ui->Total_HT_8->setText(QString::number(t_vente_ht - (t_achat_ht + t_diver_ht), 'f', 2) + " HT");
    ui->Total_TVA_8->setText(QString::number(t_vente_tva - (t_achat_tva + t_diver_tva), 'f', 2) + " TVA");
    ui->Total_TTC_8->setText(QString::number(t_vente_ttc - (t_achat_ttc + t_diver_ttc), 'f', 2) + " TTC");
    m_t_ht += t_vente_ht - (t_achat_ht + t_diver_ht);
    m_t_tva += t_vente_tva - (t_achat_tva + t_diver_tva);
    m_t_ttc += t_vente_ttc - (t_achat_ttc + t_diver_ttc);
}

void        BilanDialog::set_s(QStringList const year, int &i)
{
    double t_achat_ht = 0;
    double t_vente_ht = 0;
    double t_diver_ht = 0;
    double t_achat_tva = 0;
    double t_vente_tva = 0;
    double t_diver_tva = 0;
    double t_achat_ttc = 0;
    double t_vente_ttc = 0;
    double t_diver_ttc = 0;

    t_achat_ht = 0;
    while (i < year.size())
    {
        if (year[i][6] != '9')
            break;
        QStringList list = year[i].split(",");
        if (list[6] == "Achat")
        {
            t_achat_ht += list[3].toDouble();
            t_achat_tva += list[4].toDouble();
            t_achat_ttc += list[5].toDouble();
        }
        if (list[6] == "Vente")
        {
            t_vente_ht += list[3].toDouble();
            t_vente_tva += list[4].toDouble();
            t_vente_ttc += list[5].toDouble();
        }
        if (list[6] == "Divers")
        {
            t_diver_ht += list[3].toDouble();
            t_diver_tva += list[4].toDouble();
            t_diver_ttc += list[5].toDouble();
        }
        i++;
    }
    ui->Achat_HT_9->setText(QString::number(t_achat_ht, 'f', 2) + " HT");
    ui->Achat_TVA_9->setText(QString::number(t_achat_tva, 'f', 2) + " TVA");
    ui->Achat_TTC_9->setText(QString::number(t_achat_ttc, 'f', 2) + " TTC");
    ui->Vente_HT_9->setText(QString::number(t_vente_ht, 'f', 2) + " HT");
    ui->Vente_TVA_9->setText(QString::number(t_vente_tva, 'f', 2) + " TVA");
    ui->Vente_TTC_9->setText(QString::number(t_vente_ttc, 'f', 2) + " TTC");
    ui->Divers_HT_9->setText(QString::number(t_diver_ht, 'f', 2) + " HT");
    ui->Divers_TVA_9->setText(QString::number(t_diver_tva, 'f', 2) + " TVA");
    ui->Divers_TTC_9->setText(QString::number(t_diver_ttc, 'f', 2) + " TTC");
    ui->Total_HT_9->setText(QString::number(t_vente_ht - (t_achat_ht + t_diver_ht), 'f', 2) + " HT");
    ui->Total_TVA_9->setText(QString::number(t_vente_tva - (t_achat_tva + t_diver_tva), 'f', 2) + " TVA");
    ui->Total_TTC_9->setText(QString::number(t_vente_ttc - (t_achat_ttc + t_diver_ttc), 'f', 2) + " TTC");
    m_t_ht += t_vente_ht - (t_achat_ht + t_diver_ht);
    m_t_tva += t_vente_tva - (t_achat_tva + t_diver_tva);
    m_t_ttc += t_vente_ttc - (t_achat_ttc + t_diver_ttc);
}

void        BilanDialog::set_o(QStringList const year, int &i)
{
    double t_achat_ht = 0;
    double t_vente_ht = 0;
    double t_diver_ht = 0;
    double t_achat_tva = 0;
    double t_vente_tva = 0;
    double t_diver_tva = 0;
    double t_achat_ttc = 0;
    double t_vente_ttc = 0;
    double t_diver_ttc = 0;

    t_achat_ht = 0;
    while (i < year.size())
    {
        if (year[i][6] != '0')
            break;
        QStringList list = year[i].split(",");
        if (list[6] == "Achat")
        {
            t_achat_ht += list[3].toDouble();
            t_achat_tva += list[4].toDouble();
            t_achat_ttc += list[5].toDouble();
        }
        if (list[6] == "Vente")
        {
            t_vente_ht += list[3].toDouble();
            t_vente_tva += list[4].toDouble();
            t_vente_ttc += list[5].toDouble();
        }
        if (list[6] == "Divers")
        {
            t_diver_ht += list[3].toDouble();
            t_diver_tva += list[4].toDouble();
            t_diver_ttc += list[5].toDouble();
        }
        i++;
    }
    ui->Achat_HT_10->setText(QString::number(t_achat_ht, 'f', 2) + " HT");
    ui->Achat_TVA_10->setText(QString::number(t_achat_tva, 'f', 2) + " TVA");
    ui->Achat_TTC_10->setText(QString::number(t_achat_ttc, 'f', 2) + " TTC");
    ui->Vente_HT_10->setText(QString::number(t_vente_ht, 'f', 2) + " HT");
    ui->Vente_TVA_10->setText(QString::number(t_vente_tva, 'f', 2) + " TVA");
    ui->Vente_TTC_10->setText(QString::number(t_vente_ttc, 'f', 2) + " TTC");
    ui->Divers_HT_10->setText(QString::number(t_diver_ht, 'f', 2) + " HT");
    ui->Divers_TVA_10->setText(QString::number(t_diver_tva, 'f', 2) + " TVA");
    ui->Divers_TTC_10->setText(QString::number(t_diver_ttc, 'f', 2) + " TTC");
    ui->Total_HT_10->setText(QString::number(t_vente_ht - (t_achat_ht + t_diver_ht), 'f', 2) + " HT");
    ui->Total_TVA_10->setText(QString::number(t_vente_tva - (t_achat_tva + t_diver_tva), 'f', 2) + " TVA");
    ui->Total_TTC_10->setText(QString::number(t_vente_ttc - (t_achat_ttc + t_diver_ttc), 'f', 2) + " TTC");
    m_t_ht += t_vente_ht - (t_achat_ht + t_diver_ht);
    m_t_tva += t_vente_tva - (t_achat_tva + t_diver_tva);
    m_t_ttc += t_vente_ttc - (t_achat_ttc + t_diver_ttc);
}

void        BilanDialog::set_n(QStringList const year, int &i)
{
    double t_achat_ht = 0;
    double t_vente_ht = 0;
    double t_diver_ht = 0;
    double t_achat_tva = 0;
    double t_vente_tva = 0;
    double t_diver_tva = 0;
    double t_achat_ttc = 0;
    double t_vente_ttc = 0;
    double t_diver_ttc = 0;

    t_achat_ht = 0;
    while (i < year.size())
    {
        if (year[i][6] != '1' || year[i][5] != '1')
            break;
        QStringList list = year[i].split(",");
        if (list[6] == "Achat")
        {
            t_achat_ht += list[3].toDouble();
            t_achat_tva += list[4].toDouble();
            t_achat_ttc += list[5].toDouble();
        }
        if (list[6] == "Vente")
        {
            t_vente_ht += list[3].toDouble();
            t_vente_tva += list[4].toDouble();
            t_vente_ttc += list[5].toDouble();
        }
        if (list[6] == "Divers")
        {
            t_diver_ht += list[3].toDouble();
            t_diver_tva += list[4].toDouble();
            t_diver_ttc += list[5].toDouble();
        }
        i++;
    }
    ui->Achat_HT_11->setText(QString::number(t_achat_ht, 'f', 2) + " HT");
    ui->Achat_TVA_11->setText(QString::number(t_achat_tva, 'f', 2) + " TVA");
    ui->Achat_TTC_11->setText(QString::number(t_achat_ttc, 'f', 2) + " TTC");
    ui->Vente_HT_11->setText(QString::number(t_vente_ht, 'f', 2) + " HT");
    ui->Vente_TVA_11->setText(QString::number(t_vente_tva, 'f', 2) + " TVA");
    ui->Vente_TTC_11->setText(QString::number(t_vente_ttc, 'f', 2) + " TTC");
    ui->Divers_HT_11->setText(QString::number(t_diver_ht, 'f', 2) + " HT");
    ui->Divers_TVA_11->setText(QString::number(t_diver_tva, 'f', 2) + " TVA");
    ui->Divers_TTC_11->setText(QString::number(t_diver_ttc, 'f', 2) + " TTC");
    ui->Total_HT_11->setText(QString::number(t_vente_ht - (t_achat_ht + t_diver_ht), 'f', 2) + " HT");
    ui->Total_TVA_11->setText(QString::number(t_vente_tva - (t_achat_tva + t_diver_tva), 'f', 2) + " TVA");
    ui->Total_TTC_11->setText(QString::number(t_vente_ttc - (t_achat_ttc + t_diver_ttc), 'f', 2) + " TTC");
    m_t_ht += t_vente_ht - (t_achat_ht + t_diver_ht);
    m_t_tva += t_vente_tva - (t_achat_tva + t_diver_tva);
    m_t_ttc += t_vente_ttc - (t_achat_ttc + t_diver_ttc);
}

void        BilanDialog::set_d(QStringList const year, int &i)
{
    double t_achat_ht = 0;
    double t_vente_ht = 0;
    double t_diver_ht = 0;
    double t_achat_tva = 0;
    double t_vente_tva = 0;
    double t_diver_tva = 0;
    double t_achat_ttc = 0;
    double t_vente_ttc = 0;
    double t_diver_ttc = 0;

    t_achat_ht = 0;
    while (i < year.size())
    {
        if (year[i][6] != '2' || year[i][5] != '1')
            break;
        QStringList list = year[i].split(",");
        if (list[6] == "Achat")
        {
            t_achat_ht += list[3].toDouble();
            t_achat_tva += list[4].toDouble();
            t_achat_ttc += list[5].toDouble();
        }
        if (list[6] == "Vente")
        {
            t_vente_ht += list[3].toDouble();
            t_vente_tva += list[4].toDouble();
            t_vente_ttc += list[5].toDouble();
        }
        if (list[6] == "Divers")
        {
            t_diver_ht += list[3].toDouble();
            t_diver_tva += list[4].toDouble();
            t_diver_ttc += list[5].toDouble();
        }
        i++;
    }
    ui->Achat_HT_12->setText(QString::number(t_achat_ht, 'f', 2) + " HT");
    ui->Achat_TVA_12->setText(QString::number(t_achat_tva, 'f', 2) + " TVA");
    ui->Achat_TTC_12->setText(QString::number(t_achat_ttc, 'f', 2) + " TTC");
    ui->Vente_HT_12->setText(QString::number(t_vente_ht, 'f', 2) + " HT");
    ui->Vente_TVA_12->setText(QString::number(t_vente_tva, 'f', 2) + " TVA");
    ui->Vente_TTC_12->setText(QString::number(t_vente_ttc, 'f', 2) + " TTC");
    ui->Divers_HT_12->setText(QString::number(t_diver_ht, 'f', 2) + " HT");
    ui->Divers_TVA_12->setText(QString::number(t_diver_tva, 'f', 2) + " TVA");
    ui->Divers_TTC_12->setText(QString::number(t_diver_ttc, 'f', 2) + " TTC");
    ui->Total_HT_12->setText(QString::number(t_vente_ht - (t_achat_ht + t_diver_ht), 'f', 2) + " HT");
    ui->Total_TVA_12->setText(QString::number(t_vente_tva - (t_achat_tva + t_diver_tva), 'f', 2) + " TVA");
    ui->Total_TTC_12->setText(QString::number(t_vente_ttc - (t_achat_ttc + t_diver_ttc), 'f', 2) + " TTC");
    m_t_ht += t_vente_ht - (t_achat_ht + t_diver_ht);
    m_t_tva += t_vente_tva - (t_achat_tva + t_diver_tva);
    m_t_ttc += t_vente_ttc - (t_achat_ttc + t_diver_ttc);
}

void BilanDialog::on_comboBox_activated(int index)
{
    fillyear(index);
}
