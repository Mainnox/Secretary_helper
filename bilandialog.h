#ifndef BILANDIALOG_H
#define BILANDIALOG_H

#include <QDialog>

namespace Ui {
class BilanDialog;
}

class BilanDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BilanDialog(QWidget *parent = nullptr);
    ~BilanDialog();
    void        setupall();
    void        setupyear(const QStringList fac_list);
    void        showfac_list();
    QString     getyear(QStringList fac);
    void        fillyear(int i);
    void        set_j(QStringList const year, int &i);
    void        set_f(QStringList const year, int &i);
    void        set_m(QStringList const year, int &i);
    void        set_av(QStringList const year, int &i);
    void        set_ma(QStringList const year, int &i);
    void        set_ju(QStringList const year, int &i);
    void        set_jul(QStringList const year, int &i);
    void        set_a(QStringList const year, int &i);
    void        set_s(QStringList const year, int &i);
    void        set_o(QStringList const year, int &i);
    void        set_n(QStringList const year, int &i);
    void        set_d(QStringList const year, int &i);
private slots:
    void on_comboBox_activated(int index);

private:
    Ui::BilanDialog     *ui;
    QList<QStringList>  m_year_list;
    double                 m_t_ht;
    double                 m_t_tva;
    double                 m_t_ttc;
};

#endif // BILANDIALOG_H
