#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTextStream>
#include <QMessageBox>
#include <QStandardItemModel>
#include "ui_mainwindow.h"
#include "formularedialog.h"
#include "recapdialog.h"
#include "bilandialog.h"
#include "finddialog.h"
#include "printdialog.h"
#include "acomptedialog.h"
#include <stdio.h>
#include "paydialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void    refresh_tabs();
    void    setup_cours();
    void    setup_attente();
    QString reverse_date(QString date);

private slots:
    void on_actionSortir_triggered();

    void on_actionNouvelle_Facture_triggered();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_5_clicked();

    void on_attente_doubleClicked(const QModelIndex &index);

    void on_cours_doubleClicked(const QModelIndex &index);

    void on_pushButton_6_clicked();

    void on_pushButton_6_pressed();

private:
    Ui::MainWindow *ui;
    QStandardItemModel  *m_model_attente;
    QStandardItemModel  *m_model_cours;
    QModelIndex         m_tmp;
};
#endif // MAINWINDOW_H
