#include "nouvellelignedialog.h"
#include "ui_nouvellelignedialog.h"

NouvelleLigneDialog::NouvelleLigneDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NouvelleLigneDialog)
{
    ui->setupUi(this);
    QPixmap bkgnd(QApplication::applicationDirPath() + "/Image/grey-gradient-background.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
    m_ok = false;
    m_nombre = 1;
    m_prix_t = 0;
    m_prix_u = 0;
    m_ref = "";
    m_dimension = "";
    m_name = "";
    m_types = "u";
    m_civ = "";
}

NouvelleLigneDialog::~NouvelleLigneDialog()
{
    delete ui;
}

void NouvelleLigneDialog::on_lineEdit_textChanged(const QString &arg1)
{
    m_name = arg1;
}

void NouvelleLigneDialog::on_lineEdit_2_textChanged(const QString &arg1)
{
    m_dimension = arg1;
}

void NouvelleLigneDialog::on_lineEdit_3_textChanged(const QString &arg1)
{
    m_ref = arg1;
}

void NouvelleLigneDialog::on_comboBox_activated(const QString &arg1)
{
    m_types = arg1;
}

void NouvelleLigneDialog::on_spinBox_valueChanged(int arg1)
{
    m_nombre = arg1;
    m_prix_t = m_prix_u * m_nombre;
    ui->PrixTotal->setText(QString::number(m_prix_t));
}

void NouvelleLigneDialog::on_doubleSpinBox_valueChanged(double arg1)
{
    m_prix_u = arg1;
    m_prix_t = m_prix_u * m_nombre;
    ui->PrixTotal->setText(QString::number(m_prix_t));
}

void NouvelleLigneDialog::on_pushButton_2_clicked()
{
    m_ok = false;
    close();
}

void NouvelleLigneDialog::on_pushButton_clicked()
{

    if (m_name.isEmpty())
        QMessageBox::warning(this, "Erreur", "Le champs nom est obligatoire !");
    else
    {
        m_ok = true;
        close();
    }
}

bool NouvelleLigneDialog::getok()
{
    return (m_ok);
}

QString NouvelleLigneDialog::getname()
{
    return (m_name);
}

QString NouvelleLigneDialog::getref()
{
    return (m_ref);
}

QString NouvelleLigneDialog::getdimension()
{
    return (m_dimension);
}

int     NouvelleLigneDialog::getnombre()
{
    return (m_nombre);
}

double NouvelleLigneDialog::getprix_t()
{
    return (m_prix_t);
}

double NouvelleLigneDialog::getprix_u()
{
    return (m_prix_u);
}

QString NouvelleLigneDialog::gettypes()
{
    return (m_types);
}

void NouvelleLigneDialog::on_comboBox_2_currentIndexChanged(const QString &arg1)
{
    m_civ = arg1;
}
