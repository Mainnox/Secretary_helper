#ifndef PRINTDIALOG_H
#define PRINTDIALOG_H

#include <QDialog>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include "formheaderdialog.h"
#include "titredialog.h"
#include <QImage>
#include <QPixmap>
#include <QLayout>
#include <QMenu>
#include <QContextMenuEvent>
#include <QPrinter>
#include <QPrintDialog>
#include <QPainter>
#include "formfacnoimagedialog.h"
#include "formtotaldialog.h"
#include <cmath>

namespace Ui {
class PrintDialog;
}

class PrintDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PrintDialog(QWidget *parent = nullptr);
    ~PrintDialog();
    void addHeader(void);
    void actLayout(void);
    void albert_setup(void);

private slots:
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

    void on_listWidget_2_clicked(const QModelIndex &index);

    void on_Remove_clicked();

    void on_Up_clicked();

    void on_Down_clicked();

    void on_add_clicked();

    void on_left_clicked();

    void on_right_clicked();

    void on_delete_page_clicked();

    void on_reset_clicked();

    void on_pushButton_clicked();

private:
    Ui::PrintDialog *ui;
    bool    m_footage;
    bool    m_header;
    bool    m_total_p;
    int     m_test;
    QList<QWidget *> m_pages;
    QList<QStringList> m_list_string;
    QList<QVBoxLayout *> m_layout_list;
    QList<QList<QList<QWidget *>>> m_list;
    QModelIndex m_tmp;
    QString     m_name;
    double      m_total;
    double      m_ttc;
    double      m_ht;
    double      m_tva;
    int         m_act_pages;
    int         m_titre;
    int         m_nbr_pages;
    int         m_nbr_fac;
};

#endif // PRINTDIALOG_H
