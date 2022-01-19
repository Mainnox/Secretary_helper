#ifndef PAYDIALOG_H
#define PAYDIALOG_H

#include <QDialog>
#include <QStandardItemModel>
#include <QDir>
#include <QFile>
#include <QStringList>
#include <QMessageBox>
#include <QTextStream>

namespace Ui {
class PayDialog;
}

class PayDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PayDialog(QWidget *parent = nullptr);
    ~PayDialog();
    void setuplist();
    void setuptab(const QModelIndex);
private slots:
    void on_listView_doubleClicked(const QModelIndex &index);

private:
    Ui::PayDialog           *ui;
    QStandardItemModel      *m_list_model;
    QStandardItemModel      *m_tab_model;
};

#endif // PAYDIALOG_H
