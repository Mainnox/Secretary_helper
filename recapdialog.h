#ifndef RECAPDIALOG_H
#define RECAPDIALOG_H

#include <QDialog>
#include <QDir>
#include <QStandardItemModel>

namespace Ui {
class RecapDialog;
}

class RecapDialog : public QDialog
{
    Q_OBJECT

public:
    explicit RecapDialog(QWidget *parent = nullptr, QString name = "");
    ~RecapDialog();
    void        showlist();
    QString     reverse_date(QString &date);
    void        setup_class(QString name);
    void        set_j(QStringList const year);
    void        modify(const QString &name, const int &where, const QStringList &modify, const int &code);
    bool        verif(const QModelIndex &index);

private slots:
    void onDataChanged(const QModelIndex&, const QModelIndex&);

    void on_checkBox_stateChanged(int arg1);

    void on_tableView_clicked(const QModelIndex &index);

    void on_Onverra_clicked();

    void on_pushButton_clicked();

private:
    Ui::RecapDialog     *ui;
    QStandardItemModel  *m_model;
    QString             m_name;
    QString             m_path;
    QDir                m_dir;
    QStringList         m_faclist;
    QStringList         m_entryList;
    QString             m_tmp;
    QModelIndex         m_index;
    double              m_t_ht;
    double              m_t_tva;
    double              m_t_ttc;
};

#endif // RECAPDIALOG_H
