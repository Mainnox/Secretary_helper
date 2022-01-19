#include "footagedialog.h"
#include "ui_footagedialog.h"

FootageDialog::FootageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FootageDialog)
{
    ui->setupUi(this);
}

FootageDialog::~FootageDialog()
{
    delete ui;
}
