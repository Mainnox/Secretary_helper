#include "recapdialog.h"
#include "ui_recapdialog.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QStandardItemModel>
#include <QAbstractItemView>
#include <QObject>
#include <QTableView>
#include <QDate>
#include <QPrintDialog>
#include <QPrinter>
#include <QPixmap>
#include <QPainter>
#include <QPageSize>
#include <QMargins>

RecapDialog::RecapDialog(QWidget *parent, QString name) :
    QDialog(parent),
    ui(new Ui::RecapDialog),
    m_name(name)
{
    ui->setupUi(this);
    setup_class(name);
    m_model = new QStandardItemModel(this);
    m_model->setHorizontalHeaderLabels({"Date", "Nom", "Numero", "HT", "TVA", "TTC"});
    QList<QStandardItem *> items;
    for (int i = 0; i < m_faclist.size(); i++)
    {
        items.clear();
        QStringList tab = m_faclist[i].split(",");
        for (int i = 0; i < tab.size(); i++)
        {
            if (i == 0)
                tab[i] = reverse_date(tab[i]);
            if (i == 3)
                m_t_ht += tab[i].toDouble();
            if (i == 4)
                m_t_tva += tab[i].toDouble();
            if (i == 5)
                m_t_ttc += tab[i].toDouble();
            if (i != 6)
                items.append(new QStandardItem(tab[i]));
        }
        m_model->appendRow(items);
    }
    ui->tableView->setModel(m_model);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->HT->setText(QString::number(m_t_ht, 'f', 2) + " HT");
    ui->TVA->setText(QString::number(m_t_tva, 'f', 2) + " TVA");
    ui->TTC->setText(QString::number(m_t_ttc, 'f', 2) + " TTC");
    if (name != "Divers")
        ui->Type->setText(name + "s");
    else
        ui->Type->setText(name);
    QObject::connect(ui->tableView->model(), SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)), this, SLOT(onDataChanged(const QModelIndex&, const QModelIndex&)));
}

RecapDialog::~RecapDialog()
{
    delete ui;
    delete m_model;
}

void           RecapDialog::showlist()
{
    QString test = m_faclist.join('\n');
    QMessageBox::information(this, "test", test);
}

void           RecapDialog::setup_class(QString name)
{
    m_name = name;
    m_path = QCoreApplication::applicationDirPath() + "/Facture/" + m_name;
    QDir dir(m_path);
    m_dir = dir;
    m_entryList = dir.entryList();
    m_t_ht = 0;
    m_t_tva = 0;
    m_t_ttc = 0;
    m_tmp = "";
    int i = 2;

    while (i < m_entryList.size())
    {
        QFile file(m_path + "/" + m_entryList[i]);
        if (!file.open(QFile::ReadOnly))
            QMessageBox::warning(this, "Error", "File cannot open");
        QTextStream textfile(&file);
        while (1)
        {
            QString line = textfile.readLine();
            if (line.isNull())
                break;
            else
                m_faclist.append(line);
        }
        file.close();
        i++;
    }
    m_faclist.sort();
}

QString                RecapDialog::reverse_date(QString &date)
{
    QStringList swap = date.split("-");
    swap[0].swap(swap[2]);
    return (swap.join('-'));
}

void RecapDialog::on_checkBox_stateChanged(int arg1)
{
    if (arg1)
        ui->tableView->setEditTriggers(QAbstractItemView::DoubleClicked);
    if (!arg1)
        ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

void RecapDialog::onDataChanged(const QModelIndex &a, const QModelIndex &b)
{
    QStringList m_modify;
    int         where = 0;

    if (verif(a))
    {
    for (int i = 0; i < m_model->columnCount(); i++)
        m_modify.append(m_model->item(b.row(), i)->text());
    for (int i = 0; i < b.row(); i++)
    {
        if (a.column() == 1)
        {
            if (m_tmp == m_model->item(i, 1)->text())
                where++;
        }
        else
            if (m_modify[1] == m_model->item(i, 1)->text())
                    where++;
    }
    m_modify[0] = reverse_date(m_modify[0]);
    if (a.column() == 1)
        modify(m_tmp, where, m_modify, 2);
    else
        modify(m_modify[1], where, m_modify, 1);
    }
}

void RecapDialog::on_tableView_clicked(const QModelIndex &index)
{
    m_tmp = m_model->item(index.row(), index.column())->text();
    m_index = index;
}

void RecapDialog::modify(const QString &name, const int &where, const QStringList &modify, const int &code)
{
    QFile file(m_path + "/" + name + ".fac");
    QStringList delete_list;
    if (!file.open(QFile::ReadOnly))
        QMessageBox::warning(this, "Error", "File cannot open");
    QTextStream textfile(&file);
    while (1)
    {
        QString line = textfile.readLine();
        if (line.isNull())
            break;
        else
            delete_list.append(line);
    }
    delete_list.removeAt(where);
    file.remove();
    if (code == 1)
    {
        delete_list.append(modify.join(",") + ',' + m_name);
        delete_list.sort();
    }
    if (delete_list.isEmpty())
        file.remove();
    else
    {
        if (!file.open(QFile::WriteOnly))
            QMessageBox::warning(this, "Error", "File cannot open");
        QTextStream textfile2(&file);
        for (int i = 0; i < delete_list.size(); i++)
            textfile2 << delete_list.at(i) << Qt::endl;
        file.flush();
        file.close();
    }
    if (code == 2)
    {
        QFile file2(m_path + "/" + modify[1] + ".fac");
        QStringList new_list;
        if (file2.exists())
        {
            if (!file2.open(QFile::ReadOnly))
                QMessageBox::warning(this, "Error", "File cannot open");
            QTextStream textfile3(&file2);
            while (1)
            {
                QString line = textfile3.readLine();
                if (line.isNull())
                    break;
                else
                    new_list.append(line);
            }
        }
        new_list.append(modify.join(",") + ',' + m_name);
        new_list.sort();
        file2.remove();
        if (!file2.open(QFile::WriteOnly))
            QMessageBox::warning(this, "Error", "File cannot open");
        QTextStream textfile4(&file2);
        for (int i = 0; i < new_list.size(); i++)
            textfile4 << new_list.at(i) << Qt::endl;
        file2.flush();
        file2.close();
    }
    m_faclist.clear();
    setup_class(m_name);
    m_model = new QStandardItemModel;
    m_model->setHorizontalHeaderLabels({"Date", "Nom", "Numero", "HT", "TVA", "TTC"});
    QList<QStandardItem *> items;
    for (int i = 0; i < m_faclist.size(); i++)
    {
        items.clear();
        QStringList tab = m_faclist[i].split(",");
        for (int i = 0; i < tab.size(); i++)
        {
            if (i == 0)
                tab[i] = reverse_date(tab[i]);
            if (i == 3)
                m_t_ht += tab[i].toDouble();
            if (i == 4)
                m_t_tva += tab[i].toDouble();
            if (i == 5)
                m_t_ttc += tab[i].toDouble();
            if (i != 6)
                items.append(new QStandardItem(tab[i]));
        }
        m_model->appendRow(items);
    }
    ui->tableView->setModel(m_model);
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    ui->HT->setText(QString::number(m_t_ht, 'f', 2) + " HT");
    ui->TVA->setText(QString::number(m_t_tva, 'f', 2) + " TVA");
    ui->TTC->setText(QString::number(m_t_ttc, 'f', 2) + " TTC");
    if (name != "Divers")
        ui->Type->setText(m_name + "s");
    else
        ui->Type->setText(m_name);
    QObject::connect(ui->tableView->model(), SIGNAL(dataChanged(const QModelIndex&, const QModelIndex&)), this, SLOT(onDataChanged(const QModelIndex&, const QModelIndex&)));
}

void RecapDialog::on_Onverra_clicked()
{
    int answer;
    int where = 0;

    if (m_tmp.isEmpty())
    {
        QMessageBox::information(this, "Erreur", "Selectionnez une ligne pour pouvoir la supprimer");
        return;
    }
    answer = QMessageBox::question(this, "Confirmation", "Etes vous sure de vouloir supprimer cette facture ?", QMessageBox::Yes | QMessageBox::No);
    if (answer == QMessageBox::Yes)
    {
        for (int i = 0; i < m_index.row(); i++)
        {
            if (m_model->item(m_index.row(), 1)->text() == m_model->item(i, 1)->text())
                where++;
        }
        modify(m_model->item(m_index.row(), 1)->text(), where, QStringList(), 0);
    }
}

bool   RecapDialog::verif(const QModelIndex &index)
{
    if (index.column() == 0)
    {
        QStringList date = m_model->item(index.row(), index.column())->text().split("-");
        if (date.size() != 3 && QMessageBox::warning(this, "Erreur", "Les dates doivent etre au format jj-mm-aaaa"))
            return (false);
        QDate date2(date[2].right(2).toInt(), date[1].toInt(), date[0].toInt());
        if (!date2.isValid() && QMessageBox::warning(this, "Erreur", "Les dates doivent etre au format jj-mm-aaaa"))
            return (false);
    }
    if (index.column() == 1 or index.column() == 2)
    {
        QString arg1 = m_model->item(index.row(), index.column())->text();
        if (arg1.contains(',') || arg1.contains('\\') || arg1.contains('/'))
        {
            QMessageBox::warning(this, "Erreur", "Les noms et les numero ne peuvent pas contenir ces charateres : /\\,");
            return (false);
        }
    }
    if (index.column() == 3 or index.column() == 4 or index.column() == 5)
    {
        bool ok;
        m_model->item(index.row(), index.column())->text().toDouble(&ok);
        if (!ok)
            QMessageBox::warning(this, "Erreur", "Les champs HT, TVA, TTC doivent contenir des nombres et la virgules doit etre un '.'");
        return (ok);
    }
    return (true);
}

void RecapDialog::on_pushButton_clicked()
{
    QPrinter printer(QPrinter::HighResolution);
    QPainter painter;
    painter.begin(&printer);
    QStringList list;
    for (int i = 0; i < 6; i++)
        list.append(m_model->item(m_index.row(), i)->text());
    printer.setPageSize(QPageSize(QPageSize::A4));
    printer.setPageMargins(QMargins(15, 15, 15, 15));
    painter.drawText(0, 100, "FACTURE " + list[2]);
    painter.end();
    QPrintDialog dialog(&printer);
    dialog.exec();
}
