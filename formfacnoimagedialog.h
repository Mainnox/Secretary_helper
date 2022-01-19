#ifndef FORMFACNOIMAGEDIALOG_H
#define FORMFACNOIMAGEDIALOG_H

#include <QDialog>
#include "nouvellelignedialog.h"
#include <QLabel>
#include <QListWidgetItem>

namespace Ui {
class FormFacnoimageDialog;
}

class FormFacnoimageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit FormFacnoimageDialog(QWidget *parent = nullptr);
    ~FormFacnoimageDialog();
    bool                getok();
    QWidget             *getwidget();
    QList<QWidget *>    getlist();
    double              gettotal();

private slots:
    void on_pushButton_2_clicked();

    void on_listWidget_clicked(const QModelIndex &index);

    void on_Remove_clicked();

    void on_Up_clicked();

    void on_Down_clicked();

    void on_pushButton_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::FormFacnoimageDialog    *ui;
    QList<QList<QWidget *>>     m_list;
    int                         m_nbr_ligne;
    QString                     m_name;
    QModelIndex                 m_tmp;
    bool                        m_ok;
    double                      m_total;
    QList<QWidget *>            m_list_recap;
    QWidget                     *m_widget;
};

#endif // FORMFACNOIMAGEDIALOG_H
