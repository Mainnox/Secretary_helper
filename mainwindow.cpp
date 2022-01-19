#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_model_cours = new QStandardItemModel(this);
    m_model_attente = new QStandardItemModel(this);
    ui->cours->setModel(m_model_cours);
    ui->attente->setModel(m_model_attente);
    ui->attente->verticalHeader()->hide();
    ui->cours->verticalHeader()->hide();
    refresh_tabs();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::refresh_tabs()
{
    m_model_cours->clear();
    m_model_attente->clear();
    m_model_attente->setHorizontalHeaderLabels({"Date", "Nom", "Numero", "Montant"});
    m_model_cours->setHorizontalHeaderLabels({"Date", "Nom", "Numero", "Montant", "Reste"});
    ui->attente->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Interactive);
    ui->attente->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->attente->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Interactive);
    ui->attente->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Interactive);
    ui->cours->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    setup_cours();
    setup_attente();
}

void MainWindow::setup_cours()
{
    const QString path = QCoreApplication::applicationDirPath() + "/Payement/cours";
    QDir dir(path);
    QStringList entry_list = dir.entryList();
    QStringList faclist;
    int i = 2;

    while (i < entry_list.size())
    {
        QFile file(path + "/" + entry_list[i]);
        if (!file.open(QFile::ReadOnly))
            QMessageBox::warning(this, "Error", "File cannot open");
        QTextStream textfile(&file);
        while (1)
        {
            QString line = textfile.readLine();
            if (line.isNull())
                break;
            else
                faclist.append(line);
        }
        file.close();
        i++;
    }
    faclist.sort();
    QList<QStandardItem *>items;
    for (int i = 0; i < faclist.size(); i++)
    {
        items.clear();
        QStringList tab = faclist[i].split(",");
        for (int i = 0; i < tab.size(); i++)
        {
            if (i ==0)
                tab[i] = reverse_date(tab[i]);
            items.append(new QStandardItem(tab[i]));
        }
        m_model_cours->appendRow(items);
    }
}

void MainWindow::setup_attente()
{
    const QString path = QCoreApplication::applicationDirPath() + "/Payement/attente";
    QDir dir(path);
    QStringList entry_list = dir.entryList();
    QStringList faclist;
    int i = 2;

    while (i < entry_list.size())
    {
        QFile file(path + "/" + entry_list[i]);
        if (!file.open(QFile::ReadOnly))
            QMessageBox::warning(this, "Error", "File cannot open");
        QTextStream textfile(&file);
        while (1)
        {
            QString line = textfile.readLine();
            if (line.isNull())
                break;
            else
                faclist.append(line);
        }
        file.close();
        i++;
    }
    faclist.sort();
    QList<QStandardItem *>items;
    for (int i = 0; i < faclist.size(); i++)
    {
        items.clear();
        QStringList tab = faclist[i].split(",");
        for (int i = 0; i < tab.size(); i++)
        {
            if (i ==0)
                tab[i] = reverse_date(tab[i]);
            items.append(new QStandardItem(tab[i]));
        }
        m_model_attente->appendRow(items);
    }
}

QString MainWindow::reverse_date(QString date)
{
    QStringList swap = date.split("-");
    swap[0].swap(swap[2]);
    return (swap.join('-'));
}

void MainWindow::on_actionSortir_triggered()
{
    qApp->quit();
}

void MainWindow::on_actionNouvelle_Facture_triggered()
{
    FormulareDialog formulare(this);
    formulare.setModal(true);
    formulare.exec();
    refresh_tabs();
}

void MainWindow::on_pushButton_clicked()
{
    RecapDialog recap(this, "Achat");
    recap.setModal(true);
    recap.exec();
}

void MainWindow::on_pushButton_3_clicked()
{
    RecapDialog recap(this, "Vente");
    recap.setModal(true);
    recap.exec();
}

void MainWindow::on_pushButton_4_clicked()
{
    RecapDialog recap(this, "Divers");
    recap.setModal(true);
    recap.exec();
}

void MainWindow::on_pushButton_2_clicked()
{
    BilanDialog bilan(this);
    bilan.setModal(true);
    bilan.exec();
}

void MainWindow::on_pushButton_5_clicked()
{
    FindDialog find(this);
    find.setModal(true);
    find.exec();
}


void MainWindow::on_attente_doubleClicked(const QModelIndex &index)
{
    AcompteDialog acompte(m_model_attente->item(index.row(), 1)->text(), m_model_attente->item(index.row(), 2)->text(),
                          m_model_attente->item(index.row(), 3)->text().toDouble(),
                          this);
    acompte.setModal(true);
    acompte.exec();
    if (acompte.getok())
    {
        QDir dir(QCoreApplication::applicationDirPath() + "/Payement/reglement/");
        QStringList entry_list = dir.entryList();
        QFile file(QApplication::applicationDirPath() + "/Payement/reglement/" + m_model_attente->item(index.row(), 1)->text()
                   + ".pay");
        if (!file.open(QFile::ReadWrite | QFile::Append))
            QMessageBox::warning(this, "Error", "File cannot open");
        QTextStream out(&file);
        out << acompte.getdate() + "," + m_model_attente->item(index.row(), 2)->text()
               + "," + QString::number(acompte.getmontant(), 'f', 2) + "\n";
        file.close();
        QFile rmv(QCoreApplication::applicationDirPath() + "/Payement/attente/"
                  + m_model_attente->item(index.row(), 1)->text() + ".pay");
        rmv.remove();
        if (acompte.getmontant() != acompte.getreste())
        {
            QString cop(reverse_date(m_model_attente->item(index.row(), 0)->text()) + ","
                        + m_model_attente->item(index.row(), 1)->text() + ","
                        + m_model_attente->item(index.row(), 2)->text() + ","
                        + m_model_attente->item(index.row(), 3)->text());
            QMessageBox::information(this, "title", cop);
            cop.append("," + QString::number(acompte.getreste() - acompte.getmontant(), 'f', 2) + "\n");
            QFile newone(QCoreApplication::applicationDirPath() + "/Payement/cours/"
                         + m_model_attente->item(index.row(), 1)->text() + ".pay");
            if (!newone.open(QFile::ReadWrite | QFile::Append))
                QMessageBox::warning(this, "ERROR", "File cannot open!");
            QTextStream out2(&newone);
            out2 << cop;
            newone.close();
        }
    }
    refresh_tabs();
}

void MainWindow::on_cours_doubleClicked(const QModelIndex &index)
{
    AcompteDialog acompte(m_model_cours->item(index.row(), 1)->text(), m_model_cours->item(index.row(), 2)->text(),
                          m_model_cours->item(index.row(), 4)->text().toDouble(),
                          this);
    acompte.setModal(true);
    acompte.exec();
    if (acompte.getok())
    {
        const QString path = QCoreApplication::applicationDirPath() + "/Payement/reglement/";
        QDir dir(path);
        QStringList entry_list = dir.entryList();
        QFile file(QApplication::applicationDirPath() + "/Payement/reglement/" + m_model_cours->item(index.row(), 1)->text()
                   + ".pay");
        if (!file.open(QFile::ReadWrite | QFile::Append))
            QMessageBox::warning(this, "Error", "File cannot open");
        QTextStream out(&file);
        out << acompte.getdate() + "," + m_model_cours->item(index.row(), 2)->text()
               + "," + QString::number(acompte.getmontant(), 'f', 2) + "\n";
        QFile rmv(QCoreApplication::applicationDirPath() + "/Payement/cours/"
                  + m_model_cours->item(index.row(), 1)->text() + ".pay");
        rmv.remove();
        if (acompte.getmontant() != acompte.getreste())
        {
            QString cop(reverse_date(m_model_cours->item(index.row(), 0)->text()) + ","
                        + m_model_cours->item(index.row(), 1)->text() + ","
                        + m_model_cours->item(index.row(), 2)->text() + ","
                        + m_model_cours->item(index.row(), 3)->text());
            QMessageBox::information(this, "title", cop);
            cop.append("," + QString::number(acompte.getreste() - acompte.getmontant(), 'f', 2) + "\n");
            QFile newone(QCoreApplication::applicationDirPath() + "/Payement/cours/"
                         + m_model_cours->item(index.row(), 1)->text() + ".pay");
            if (!newone.open(QFile::ReadWrite | QFile::Append))
                QMessageBox::warning(this, "ERROR", "File cannot open!");
            QTextStream out2(&newone);
            out2 << cop;
            newone.close();
        }
    }
    refresh_tabs();
}

void MainWindow::on_pushButton_6_clicked()
{
    PayDialog pay(this);
    pay.exec();
}

void MainWindow::on_pushButton_6_pressed()
{

}
