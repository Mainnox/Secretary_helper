#include "paydialog.h"
#include "ui_paydialog.h"

PayDialog::PayDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PayDialog)
{
    ui->setupUi(this);
    m_list_model = new QStandardItemModel;
    m_tab_model = new QStandardItemModel;
    setuplist();
    ui->listView->setModel(m_list_model);
    ui->tableView->setModel(m_tab_model);
}

PayDialog::~PayDialog()
{
    delete ui;
    delete m_list_model;
    delete m_tab_model;
}

void    PayDialog::setuplist()
{
    QDir dir(QApplication::applicationDirPath() + "/Payement/reglement");
    QStringList entry_list = dir.entryList();
    for (int i = 2; i < entry_list.size(); i++)
        m_list_model->appendRow(new QStandardItem(entry_list[i].chopped(4)));
}

void PayDialog::on_listView_doubleClicked(const QModelIndex &index)
{
    setuptab(index);
}

void PayDialog::setuptab(const QModelIndex index)
{
    QString name(m_list_model->item(index.row())->text());
    QFile file(QApplication::applicationDirPath() + "/Payement/reglement/" + name + ".pay");
    QList<QStandardItem *> list;
    m_tab_model->clear();
    m_tab_model->setHorizontalHeaderLabels({"Date", "Numero", "Montant"});
    ui->tableView->horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    ui->tableView->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    ui->tableView->horizontalHeader()->setSectionResizeMode(2, QHeaderView::Stretch);
    if (!file.open(QFile::ReadOnly))
    {
        QMessageBox::warning(this, "ERROR", "Cannot open the file: "
                             + QApplication::applicationDirPath() + "/Payement/reglement/" + name + ".pay");
        close();
    }
    QTextStream textstream(&file);
    QStringList s_list(textstream.readAll().split("\n"));
    for (int i = 0; i < s_list.size() - 1; i++)
    {
        QStringList reglement(s_list[i].split(","));
        for (int j = 0; j < reglement.size(); j++)
            list.append(new QStandardItem(reglement[j]));
        m_tab_model->appendRow(list);
        list.clear();
    }
}
