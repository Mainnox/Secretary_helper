#include "formfacnoimagedialog.h"
#include "ui_formfacnoimagedialog.h"

FormFacnoimageDialog::FormFacnoimageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FormFacnoimageDialog)
{
    ui->setupUi(this);
    QPixmap bkgnd(QApplication::applicationDirPath() + "/Image/grey-gradient-background.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
    m_nbr_ligne = 1;
    m_total = 0;
    m_ok = false;
}

FormFacnoimageDialog::~FormFacnoimageDialog()
{
    delete ui;
}

void FormFacnoimageDialog::on_pushButton_2_clicked()
{
    NouvelleLigneDialog form;

    form.exec();
    if (form.getok())
    {
        QHBoxLayout *layout = new QHBoxLayout;
        QList<QWidget *> list;
        QLabel *prix_u;
        QLabel *prix_t;
        int i = 0;

        QLabel *name = new QLabel(form.getname(), this);
        layout->addWidget(name);
        list.append(name);
        if (!form.getref().isEmpty())
        {
            QLabel *ref = new QLabel(form.getref(), this);
            layout->addWidget(ref);
            list.append(ref);
            i++;
        }
        if (!form.getdimension().isEmpty())
        {
            QLabel *dimension = new QLabel(form.getdimension(), this);
            layout->addWidget(dimension);
            list.append(dimension);
            i++;
        }
        QLabel *type = new QLabel(form.gettypes(), this);
        layout->addWidget(type);
        list.append(type);
        QLabel *nombre = new QLabel(QString::number(form.getnombre()), this);
        layout->addWidget(nombre);
        list.append(nombre);
        if (form.getprix_u())
        {
            prix_u = new QLabel(QString::number(form.getprix_u()), this);
            prix_t = new QLabel(QString::number(form.getprix_t()), this);
            m_total += form.getprix_t();
        }
        else
        {
            prix_u = new QLabel("", this);
            prix_t = new QLabel("", this);
        }
        list.append(prix_t);
        list.append(prix_u);
        prix_u->setAlignment(Qt::AlignCenter);
        prix_t->setAlignment(Qt::AlignCenter);
        layout->addWidget(prix_u);
        layout->addWidget(prix_t);
        layout->setStretch(i + 3, 1);
        layout->setStretch(i + 4, 1);
        layout->setStretch(0, 4);
        m_list.append(list);
        ui->listWidget->addItem("Ligne " + QString::number(m_nbr_ligne));
        m_nbr_ligne++;
        ui->verticalLayout_2->addLayout(layout);
    }
}

void FormFacnoimageDialog::on_listWidget_clicked(const QModelIndex &index)
{
    m_tmp = index;
    m_name = ui->listWidget->item(index.row())->text().split(' ')[0];
    if (index.row() != 0)
        ui->Up->setEnabled(true);
    else
        ui->Up->setEnabled(false);
    if (index.row() != ui->listWidget->count() - 1)
        ui->Down->setEnabled(true);
    else
        ui->Down->setEnabled(false);
    ui->Remove->setEnabled(true);
}

void FormFacnoimageDialog::on_Remove_clicked()
{
    for (int i = 0; i < m_list[m_tmp.row()].size(); i++)
        delete m_list[m_tmp.row()][i];
    m_list.removeAt(m_tmp.row());
    ui->verticalLayout_2->removeItem(ui->verticalLayout_2->takeAt(m_tmp.row()));
    delete ui->listWidget->takeItem(m_tmp.row());
    ui->listWidget->clearSelection();
    ui->Up->setEnabled(false);
    ui->Down->setEnabled(false);
    ui->Remove->setEnabled(false);
}

void FormFacnoimageDialog::on_Up_clicked()
{
    int row = m_tmp.row();
    ui->verticalLayout_2->insertItem(row - 1, ui->verticalLayout_2->takeAt(row));
    m_list.move(row, row - 1);
    ui->listWidget->insertItem(row - 1, ui->listWidget->takeItem(row));
    on_listWidget_clicked(m_tmp.sibling(row - 1, m_tmp.column()));
}

void FormFacnoimageDialog::on_Down_clicked()
{
    int row = m_tmp.row();
    ui->verticalLayout_2->insertItem(row + 1, ui->verticalLayout_2->takeAt(row));
    m_list.move(row, row + 1);
    ui->listWidget->insertItem(row + 1, ui->listWidget->takeItem(row));
    ui->listWidget->setItemSelected(ui->listWidget->item(row + 1), true);
    on_listWidget_clicked(m_tmp.sibling(row + 1, m_tmp.column()));
}

void FormFacnoimageDialog::on_pushButton_clicked()
{
    m_ok = false;
    close();
}

void FormFacnoimageDialog::on_pushButton_5_clicked()
{
    m_ok = true;
    m_widget = ui->widget;
    for (int i = 0; i < m_list.size(); i++)
    {
        for (int j = 0; j < m_list[i].size(); j++)
        {
            m_list_recap.append(m_list[i][j]);
        }
    }
    close();
}


QList<QWidget *>    FormFacnoimageDialog::getlist()
{
    return (m_list_recap);
}

bool FormFacnoimageDialog::getok()
{
    return (m_ok);
}

QWidget *FormFacnoimageDialog::getwidget()
{
    return (m_widget);
}

double FormFacnoimageDialog::gettotal()
{
    return (m_total);
}

