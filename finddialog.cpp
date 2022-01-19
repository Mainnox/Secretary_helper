#include "finddialog.h"
#include "ui_finddialog.h"
#include <QTreeView>
#include <QDir>
#include <QMessageBox>
#include <QString>
#include <QTextStream>

FindDialog::FindDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FindDialog)
{
    ui->setupUi(this);
    m_list_model = new QStandardItemModel;
    m_tab_model = new QStandardItemModel;
    ui->listView->setModel(m_list_model);
    ui->tableView->setModel(m_tab_model);
    setupall();
}

FindDialog::~FindDialog()
{
    delete ui;
    delete m_list_model;
    delete m_tab_model;
}

void        FindDialog::setupall()
{
    setuplist();
    setComplete();
}

void        FindDialog::setuplist()
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
            if (m_list.lastIndexOf(fac_list[j]) == -1)
                m_list.append(fac_list[j]);
        }
    }
    m_list.sort(Qt::CaseInsensitive);
    QList<QStandardItem *> fill_list;
    for (int i = 0; i < m_list.size(); i++)
    {
        fill_list.clear();
        fill_list.append(new QStandardItem(m_list[i]));
        m_list_model->appendRow(fill_list);
    }
}

QString                FindDialog::reverse_date(QString &date)
{
    QStringList swap = date.split("-");
    swap[0].swap(swap[2]);
    return (swap.join('-'));
}

void        FindDialog::setuptab(const int &index)
{
    m_tab_model->clear();
    QList<QStandardItem *> list;
    QStringList list_read;
    QDir dir(QApplication::applicationDirPath() + "/Facture/Achat/");
    QDir dir1(QApplication::applicationDirPath() + "/Facture/Vente/");
    QDir dir2(QApplication::applicationDirPath() + "/Facture/Divers/");
    m_ht = 0;
    m_ttc = 0;
    m_tva = 0;

    m_tab_model->setHorizontalHeaderLabels({"Date", "Nom", "Numero", "HT", "TVA", "TTC", "Types"});
    ui->tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    if (dir.exists(m_list[index] + ".fac"))
    {
            QFile file(dir.path() + "/" + m_list[index] + ".fac");
            if (!file.open(QFile::ReadOnly))
                QMessageBox::warning(this, "Error", "File cannot open");
            QTextStream textfile(&file);
            while (1)
            {
                QString line = textfile.readLine();
                if (line.isNull())
                    break;
                else
                    list_read.append(line);
            }
            file.close();
    }
    if (dir1.exists(m_list[index] + ".fac"))
    {
            QFile file(dir1.path() + "/" + m_list[index] + ".fac");
            if (!file.open(QFile::ReadOnly))
                QMessageBox::warning(this, "Error", "File cannot open");
            QTextStream textfile(&file);
            while (1)
            {
                QString line = textfile.readLine();
                if (line.isNull())
                    break;
                else
                    list_read.append(line);
            }
            file.close();
    }
    if (dir2.exists(m_list[index] + ".fac"))
    {
            QFile file(dir2.path() + "/" + m_list[index] + ".fac");
            if (!file.open(QFile::ReadOnly))
                QMessageBox::warning(this, "Error", "File cannot open");
            QTextStream textfile(&file);
            while (1)
            {
                QString line = textfile.readLine();
                if (line.isNull())
                    break;
                else
                    list_read.append(line);
            }
            file.close();
    }
    list_read.sort();
    for (int j = 0; j < list_read.size(); j++)
    {
        list.clear();
        QStringList tab = list_read[j].split(",");
        for (int i = 0; i < tab.size(); i++)
        {
            if (i == 0)
                tab[i] = reverse_date(tab[i]);
            if (i == 3)
            {
                if (tab[6] == "Vente")
                    m_ht += tab[i].toDouble();
                else
                    m_ht -= tab[i].toDouble();
            }
            if (i == 4)
            {
                if (tab[6] == "Vente")
                    m_tva += tab[i].toDouble();
                else
                    m_tva -= tab[i].toDouble();
            }
            if (i == 5)
            {
                if (tab[6] == "Vente")
                    m_ttc += tab[i].toDouble();
                else
                    m_ttc -= tab[i].toDouble();
            }
            list.append(new QStandardItem(tab[i]));
        }
        m_tab_model->appendRow(list);
    }
    ui->HT->setText(QString::number(m_ht) + " HT");
    ui->TVA->setText(QString::number(m_tva) + " TVA");
    ui->TTC->setText(QString::number(m_ttc) + " TTC");
}

void FindDialog::on_listView_clicked(const QModelIndex &index)
{
    setuptab(index.row());
}

void FindDialog::setComplete()
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
    ui->Recherche->setCompleter(completer);
}

void FindDialog::on_Recherche_returnPressed()
{
    QString name = ui->Recherche->text();
    ui->Recherche->clear();
    bool ok = false;
    for (int i = 0; i < m_list_model->rowCount(); i++)
    {
        if (name == m_list_model->item(i)->text())
        {
            setuptab(i);
            ok = true;
            break ;
        }
    }
    if (!ok)
        QMessageBox::warning(this, "Erreur", name + " n'existe pas dans la liste des clients !");
}
