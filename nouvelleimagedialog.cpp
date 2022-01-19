#include "nouvelleimagedialog.h"
#include "ui_nouvelleimagedialog.h"

nouvelleImageDialog::nouvelleImageDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::nouvelleImageDialog)
{
    ui->setupUi(this);
}

nouvelleImageDialog::~nouvelleImageDialog()
{
    delete ui;
}
