#include "informationdialog.h"
#include "ui_informationdialog.h"

informationDialog::informationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::informationDialog)
{
    ui->setupUi(this);
}

informationDialog::~informationDialog()
{
    delete ui;
}
