#include "formtotaldialog.h"
#include "ui_formtotaldialog.h"

FormTotalDialog::FormTotalDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FormTotalDialog)
{
    ui->setupUi(this);
    QPixmap bkgnd(QApplication::applicationDirPath() + "/Image/grey-gradient-background.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
    m_accompte = 0;
    m_tva = 0;
    m_ok = false;
}

FormTotalDialog::~FormTotalDialog()
{
    delete ui;
}

void FormTotalDialog::on_checkBox_clicked(bool checked)
{
    ui->doubleSpinBox_2->setEnabled(checked);
    if (!checked)
    {
        m_accompte = 0;
        ui->doubleSpinBox_2->setValue(0);
    }
}

bool FormTotalDialog::getok()
{
    return (m_ok);
}

double FormTotalDialog::getaccompte()
{
    return (m_accompte);
}

double FormTotalDialog::gettva()
{
    return (m_tva);
}
void FormTotalDialog::on_doubleSpinBox_valueChanged(double arg1)
{
    m_tva = arg1;
}

void FormTotalDialog::on_doubleSpinBox_2_valueChanged(double arg1)
{
    m_accompte = arg1;
}

void FormTotalDialog::on_pushButton_clicked()
{
    m_ok = true;
    close();
}

void FormTotalDialog::on_pushButton_2_clicked()
{
    m_ok = false;
    close();
}
