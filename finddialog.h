#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>
#include <QList>
#include <QStandardItemModel>
#include <QFileSystemModel>
#include <QCompleter>

namespace Ui {
class FindDialog;
}

class FindDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FindDialog(QWidget *parent = nullptr);
    ~FindDialog();
    void        setupall();
    void        setuplist();
    void        setuptab(const int &i);
    QString     reverse_date(QString &date);
    void        setComplete();

private slots:
    void on_listView_clicked(const QModelIndex &index);

    void on_Recherche_returnPressed();

private:
    Ui::FindDialog      *ui;
    QStandardItemModel    *m_list_model;
    QStandardItemModel      *m_tab_model;
    QStringList                 m_list;
    QStringList             m_complete;
    double                  m_ht;
    double                  m_tva;
    double                  m_ttc;
};

#endif // FINDDIALOG_H
