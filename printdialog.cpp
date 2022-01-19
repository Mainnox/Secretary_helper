#include "printdialog.h"
#include "ui_printdialog.h"

PrintDialog::PrintDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PrintDialog)
{
    ui->setupUi(this);
    QPixmap bkgnd(QApplication::applicationDirPath() + "/Image/grey-gradient-background.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Background, bkgnd);
    this->setPalette(palette);
    m_act_pages = 0;
    albert_setup();
    m_list_string.append(QStringList());
    m_footage = false;
    m_header = false;
    m_total_p = false;
    m_test = 0;
    m_titre = 0;
    m_nbr_fac = 0;
    m_total = 0;
}

PrintDialog::~PrintDialog()
{
    delete ui;
}

void PrintDialog::albert_setup()
{
    QList<QList<QWidget *>> list;
    QWidget *pages = new QWidget(this);
    pages->setGeometry(338, 1, 595, 824);
    pages->setMinimumSize(595, 824);
    pages->setMaximumSize(595, 824);
    QVBoxLayout *layout = new QVBoxLayout();
    layout->setContentsMargins(9, 0, 9, 9);

    pages->setStyleSheet("QWidget\n{\n	background-color: white;\n}");
    pages->setLayout(layout);
    m_layout_list.insert(m_act_pages, layout);
    m_list.insert(m_act_pages, list);
    m_pages.insert(m_act_pages, pages);
    if (m_act_pages)
        m_pages[m_act_pages - 1]->hide();
    ui->gridLayout_2->addWidget(pages, 1, 4);
    ui->nbr_page->setText(QString::number(m_act_pages + 1) + "/" + QString::number(m_list.size()));
}

void PrintDialog::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    if (item->text() == "Footage")
    {
        if (m_footage)
        {
            QMessageBox::warning(this, "Erreur", "Il y a deja un footage !");
            return;
        }
        m_footage = true;
        QGridLayout *layout = new QGridLayout;
        QList<QWidget *> list;
        QLabel *reserve = new QLabel("Réserve de propriété: Nous nous réservons la propriété des marchandises jusqu'au paiement du prix par l'acheteur.", this);
        list.append(reserve);
        QLabel *siren = new QLabel("Siren 410 084 396 / siret 410 084 396 00036 / APE 4322 B", this);
        list.append(siren);
        QLabel *Tva = new QLabel("Tva intercommunautaire fr 6641008439600036", this);
        list.append(Tva);
        layout->addWidget(reserve, 0, 0, 1, 2, Qt::AlignCenter);
        layout->addWidget(siren, 1, 0, Qt::AlignLeft);
        layout->addWidget(Tva, 1, 1, Qt::AlignRight);

        layout->setMargin(10);
        ui->listWidget_2->addItem("Footage");
        m_list_string[m_act_pages].append("Footage");
        m_list[m_act_pages].append(list);
        m_layout_list[m_act_pages]->addLayout(layout, 0);
    }
    else if (item->text() == "Test")
    {
        QGridLayout *layout = new QGridLayout;
        QList<QWidget *> list;
        QLabel *test = new QLabel("Test" + QString::number(m_test), this);
        layout->addWidget(test);
        list.append(test);
        if (m_footage)
        {
            layout->setMargin(10);
            ui->listWidget_2->insertItem(m_layout_list[m_act_pages]->count() - 1, "test " + QString::number(m_test));
            m_list_string[m_act_pages].append("test " + QString::number(m_test));
            m_list[m_act_pages].insert(m_layout_list[m_act_pages]->count() - 1, list);
            m_layout_list[m_act_pages]->insertLayout(m_layout_list[m_act_pages]->count() - 1, layout, 1);
        }
        else
        {
            layout->setMargin(10);
            ui->listWidget_2->insertItem(m_layout_list[m_act_pages]->count(), "test " + QString::number(m_test));
            m_list_string[m_act_pages].append("test " + QString::number(m_test));
            m_list[m_act_pages].insert(m_layout_list[m_act_pages]->count(), list);
            m_layout_list[m_act_pages]->insertLayout(m_layout_list[m_act_pages]->count(), layout, 1);
        }
        m_test++;
    }
    else if (item->text() == "Header")
    {
        if (m_header)
        {
            QMessageBox::warning(this, "Erreur", "Il y a deja un header");
            return;
        }
        addHeader();
        m_header = true;
    }
    else if (item->text() == "Titre")
    {
        titreDialog titre;
        QList<QWidget *> list;
        titre.exec();
        if (titre.getok())
        {
            QLabel *tm_itre = new QLabel(titre.gettitre());
            QVBoxLayout *layout = new QVBoxLayout;
            layout->addWidget(tm_itre);
            list.append(tm_itre);
            if (m_footage)
            {
                layout->setMargin(10);
                ui->listWidget_2->insertItem(m_layout_list[m_act_pages]->count() - 1, "Titre " + QString::number(m_titre));
                m_list_string[m_act_pages].append("Titre " + QString::number(m_titre));
                m_list[m_act_pages].insert(m_layout_list[m_act_pages]->count() - 1, list);
                m_layout_list[m_act_pages]->insertLayout(m_layout_list[m_act_pages]->count() - 1, layout, 1);
            }
            else
            {
                layout->setMargin(10);
                ui->listWidget_2->insertItem(m_layout_list[m_act_pages]->count(), "Titre " + QString::number(m_titre));
                m_list_string[m_act_pages].append("Titre " + QString::number(m_titre));
                m_list[m_act_pages].insert(m_layout_list[m_act_pages]->count(), list);
                m_layout_list[m_act_pages]->insertLayout(m_layout_list[m_act_pages]->count(), layout, 1);
            }
        }
    }
    else if (item->text() == "Facture avec image")
    {
        FormFacnoimageDialog form;
        form.exec();
        if (form.getok())
        {
            QVBoxLayout *layout = new QVBoxLayout;
            QList<QWidget *> list = form.getlist();
            list.append(form.getwidget());
            form.getwidget()->setParent(this);
            layout->addWidget(form.getwidget());
            m_total += form.gettotal();
            if (m_footage)
            {
                layout->setMargin(10);
                ui->listWidget_2->insertItem(m_layout_list[m_act_pages]->count() - 1, "Facture " + QString::number(++m_nbr_fac));
                m_list_string[m_act_pages].append("Facture " + QString::number(++m_nbr_fac));
                m_list[m_act_pages].insert(m_layout_list[m_act_pages]->count() - 1, list);
                m_layout_list[m_act_pages]->insertLayout(m_layout_list[m_act_pages]->count() - 1, layout, 1);
            }
            else
            {
                layout->setMargin(10);
                ui->listWidget_2->insertItem(m_layout_list[m_act_pages]->count(), "Facture " + QString::number(++m_nbr_fac));
                m_list_string[m_act_pages].append("Facture " + QString::number(++m_nbr_fac));
                m_list[m_act_pages].insert(m_layout_list[m_act_pages]->count(), list);
                m_layout_list[m_act_pages]->insertLayout(m_layout_list[m_act_pages]->count(), layout, 1);
            }
        }
    }
    else if (item->text() == "Footage avec assurance")
    {
        if (m_footage)
        {
            QMessageBox::warning(this, "Erreur", "Il y a deja un footage !");
            return;
        }
        m_footage = true;
        QList<QWidget *> list;
        QVBoxLayout *layout = new QVBoxLayout;
        QLabel *blue = new QLabel("En votre aimable reglement");
        blue->setStyleSheet("QLabel { color : blue; }");
        blue->setAlignment(Qt::AlignCenter);
        list.append(blue);

        QLabel *red = new QLabel("L'Amour du travail bien fait, tout simplement...");
        red->setStyleSheet("QLabel { color : red; }");
        red->setAlignment(Qt::AlignCenter);
        list.append(red);

        QLabel *assurance = new QLabel;
        assurance->setPixmap(QPixmap::fromImage(QImage(QCoreApplication::applicationDirPath() + "/image/Ligne_assurance.png")));
        assurance->setAlignment(Qt::AlignCenter);
        list.append(assurance);

        QGridLayout *layout_2 = new QGridLayout;
        QLabel *reserve = new QLabel("Réserve de propriété: Nous nous réservons la propriété des marchandises jusqu'au paiement du prix par l'acheteur.", this);
        list.append(reserve);
        QLabel *siren = new QLabel("Siren 410 084 396 / siret 410 084 396 00036 / APE 4322 B", this);
        list.append(siren);
        QLabel *Tva = new QLabel("Tva intercommunautaire fr 6641008439600036", this);
        list.append(Tva);
        layout_2->addWidget(reserve, 0, 0, 1, 2, Qt::AlignCenter);
        layout_2->addWidget(siren, 1, 0, Qt::AlignLeft);
        layout_2->addWidget(Tva, 1, 1, Qt::AlignRight);

        layout->addWidget(blue);
        layout->addWidget(red);
        layout->addWidget(assurance);
        layout->addLayout(layout_2);

        layout->setMargin(10);
        ui->listWidget_2->addItem("Footage avec assurance");
        m_list_string[m_act_pages].append("Footage avec assurance");
        m_list[m_act_pages].append(list);
        m_layout_list[m_act_pages]->addLayout(layout, 0);
    }
    else if (item->text() == "Certificat de ramonage")
    {
        QVBoxLayout *layout = new QVBoxLayout;
        QList<QWidget *> list;
        QLabel *certif = new QLabel("CERTIFICAT DE RAMONAGE");
        certif->setStyleSheet("font-weight: bold;");
        list.append(certif);
        layout->addWidget(certif);
        QLabel *tenant = new QLabel("Facture tenant lieu de cerficat de ramonage");
        tenant->setStyleSheet("font-weight: bold;");
        list.append(tenant);
        layout->addWidget(tenant);
        QLabel *blank = new QLabel("");
        list.append(blank);
        layout->addWidget(blank);

        QGridLayout *layout_2 = new QGridLayout;

        QLabel *ramon = new QLabel("Ramonage de cheminee");
        QLabel *ramon_2 = new QLabel("u");
        QLabel *ramon_3 = new QLabel("1");
        list.append(ramon);
        list.append(ramon_2);
        list.append(ramon_3);
        layout_2->addWidget(ramon, 0, 0);
        layout_2->addWidget(ramon_2, 0, 1);
        layout_2->addWidget(ramon_3, 0, 2);

        QLabel *con = new QLabel("Controle du tirage");
        QLabel *con_2 = new QLabel("u");
        QLabel *con_3 = new QLabel("1");
        list.append(con);
        list.append(con_2);
        list.append(con_3);
        layout_2->addWidget(con, 1, 0);
        layout_2->addWidget(con_2, 1, 1);
        layout_2->addWidget(con_3, 1, 2);

        QLabel *net = new QLabel("Nettoyage");
        QLabel *net_2 = new QLabel("u");
        QLabel *net_3 = new QLabel("1");
        list.append(net);
        list.append(net_2);
        list.append(net_3);
        layout_2->addWidget(net, 2, 0);
        layout_2->addWidget(net_2, 2, 1);
        layout_2->addWidget(net_3, 2, 2);

        QLabel *forfait = new QLabel("Forfait dans le cadre de l'entretien de la chaudiere");
        QLabel *forfait_2 = new QLabel("u");
        QLabel *forfait_3 = new QLabel("1");
        QLabel *forfait_4 = new QLabel("   43,18 €");
        QLabel *forfait_5 = new QLabel("   43,18 €");
        forfait_4->setAlignment(Qt::AlignCenter);
        forfait_5->setAlignment(Qt::AlignCenter);
        list.append(forfait);
        list.append(forfait_2);
        list.append(forfait_3);
        list.append(forfait_4);
        list.append(forfait_5);
        layout_2->addWidget(forfait, 3, 0);
        layout_2->addWidget(forfait_2, 3, 1);
        layout_2->addWidget(forfait_3, 3, 2);
        layout_2->addWidget(forfait_4, 3, 3);
        layout_2->addWidget(forfait_5, 3, 4);

        QLabel *image = new QLabel("");
        image->setPixmap(QPixmap::fromImage(QImage(QCoreApplication::applicationDirPath() + "/image/ramon.jpg")));
        image->setStyleSheet("background-color = white;");
        list.append(image);
        layout_2->addWidget(image, 0, 3, 3, 2);
        layout_2->setColumnStretch(0, 1);
        layout->addLayout(layout_2);
        m_total += 43.18;
        if (m_footage)
        {
            layout->setMargin(10);
            ui->listWidget_2->insertItem(m_layout_list[m_act_pages]->count() - 1, "Certificat de ramonage");
            m_list_string[m_act_pages].append("Certificat de ramonage");
            m_list[m_act_pages].insert(m_layout_list[m_act_pages]->count() - 1, list);
            m_layout_list[m_act_pages]->insertLayout(m_layout_list[m_act_pages]->count() - 1, layout, 1);
        }
        else
        {
            layout->setMargin(10);
            ui->listWidget_2->insertItem(m_layout_list[m_act_pages]->count(), "Certificat de ramonage");
            m_list_string[m_act_pages].append("Certificat de ramonage");
            m_list[m_act_pages].insert(m_layout_list[m_act_pages]->count(), list);
            m_layout_list[m_act_pages]->insertLayout(m_layout_list[m_act_pages]->count(), layout, 1);
        }
    }
    else if (item->text() == "Contrat_Gaz")
    {
        QGridLayout *layout = new QGridLayout;
        QList<QWidget *> list;
        QLabel *contrat = new QLabel("CONTRAT D'ENTRETIEN: GAZ", this);
        contrat->setStyleSheet("font-weight: bold;");
        contrat->setAlignment(Qt::AlignCenter);
        layout->addWidget(contrat, 0, 0, 1, 4);
        list.append(contrat);
        QLabel *depa = new QLabel("Dépannage illimité pendant un an, pièces en sus", this);
        depa->setStyleSheet("font-weight: bold;");
        contrat->setAlignment(Qt::AlignCenter);
        layout->addWidget(depa, 1, 0, 1, 4);
        list.append(depa);
        QLabel *dep = new QLabel("Dépose de la jaquette", this);
        layout->addWidget(dep, 2, 0);
        list.append(dep);
        QLabel *depo = new QLabel("Dépose des turbulateurs", this);
        layout->addWidget(depo, 3, 0);
        list.append(depo);
        QLabel *rampe = new QLabel("Dépose rampe bruleur", this);
        layout->addWidget(rampe, 4, 0);
        list.append(rampe);
        QLabel *bros = new QLabel("Brossage des carneaux", this);
        layout->addWidget(bros, 5, 0);
        list.append(bros);
        QLabel *net = new QLabel("Nettoyage bruleur air comprimeé 8 bars", this);
        layout->addWidget(net, 6, 0);
        list.append(net);
        QLabel *neto = new QLabel("Nettoyage chambre de combustion air comprime 8 bars", this);
        layout->addWidget(neto, 7, 0);
        list.append(neto);
        QLabel *remontage = new QLabel("Remontage");
        layout->addWidget(remontage, 8, 0);
        list.append(remontage);
        QLabel *ver = new QLabel("Verification des organes de securite", this);
        layout->addWidget(ver, 9, 0);
        list.append(ver);
        QLabel *ess = new QLabel("Essais", this);
        layout->addWidget(ess, 10 ,0);
        list.append(ess);
        QLabel *entre = new QLabel("Entretien annuel chaudiere", this);
        layout->addWidget(entre, 11, 0);
        list.append(entre);
        QLabel *uu = new QLabel("u");
        layout->addWidget(uu, 11, 1);
        list.append(uu);
        QLabel *un = new QLabel("1");
        layout->addWidget(un, 11, 2);
        list.append(un);
        QLabel *tot = new QLabel("    124,09 €");
        layout->addWidget(tot, 11, 3);
        list.append(tot);
        QLabel *tota = new QLabel("    124,09 €");
        layout->addWidget(tota, 11, 4);
        list.append(tota);
        layout->setColumnStretch(0, 4);
        layout->setColumnStretch(4, 1);
        layout->setColumnStretch(5, 1);


        if (m_footage)
        {
            layout->setMargin(10);
            ui->listWidget_2->insertItem(m_layout_list[m_act_pages]->count() - 1, "Certificat_Gaz");
            m_list_string[m_act_pages].append("Certificat_Gaz");
            m_list[m_act_pages].insert(m_layout_list[m_act_pages]->count() - 1, list);
            m_layout_list[m_act_pages]->insertLayout(m_layout_list[m_act_pages]->count() - 1, layout);
        }
        else
        {
            layout->setMargin(10);
            ui->listWidget_2->insertItem(m_layout_list[m_act_pages]->count(), "Certificat_Gaz");
            m_list_string[m_act_pages].append("Certificat_Gaz");
            m_list[m_act_pages].insert(m_layout_list[m_act_pages]->count(), list);
            m_layout_list[m_act_pages]->insertLayout(m_layout_list[m_act_pages]->count(), layout);
        }
    }
    else if (item->text() == "Total")
    {
        FormTotalDialog form;
        form.exec();
        if (form.getok())
        {
            if (!m_total_p)
            {
                m_total_p = true;
                QLabel *cheque_2;
                QGridLayout *layout = new QGridLayout;
                QList<QWidget *> list;
                QLabel *Deduire = new QLabel("A deduire");
                list.append(Deduire);
                layout->addWidget(Deduire, 3, 0, Qt::AlignCenter);
                QLabel *ht = new QLabel("Montant ht");
                list.append(ht);
                layout->addWidget(ht, 0, 1);
                QLabel *ht_2 = new QLabel(QString::number(m_total) + " €");
                list.append(ht_2);
                layout->addWidget(ht_2, 0, 2, Qt::AlignRight);
                QLabel *tva = new QLabel("TVA " + QString::number(form.gettva()) + " %");
                list.append(tva);
                layout->addWidget(tva, 1, 1);
                QLabel *tva_2 = new QLabel(QString::number(std::round(((m_total / 100) * form.gettva()) * 100) / 100) + " €");
                list.append(tva_2);
                layout->addWidget(tva_2, 1, 2, Qt::AlignRight);
                QLabel *ttc = new QLabel("Montant ttc");
                list.append(ttc);
                layout->addWidget(ttc, 2, 1);
                QLabel *ttc_2 = new QLabel(QString::number(m_total + (std::round(((m_total / 100) * form.gettva()) * 100) / 100)) + " €");
                list.append(ttc_2);
                layout->addWidget(ttc_2, 2, 2, Qt::AlignRight);
                QLabel *cheque = new QLabel("Cheque");
                list.append(cheque);
                layout->addWidget(cheque, 3, 1);
                if (form.getaccompte())
                    cheque_2 = new QLabel(QString::number(form.getaccompte()) + " €");
                else
                    cheque_2 = new QLabel("- €");
                list.append(cheque_2);
                layout->addWidget(cheque_2, 3, 2);
                layout->addWidget(cheque_2, 3, 2, Qt::AlignRight);
                QLabel *solde = new QLabel("Solde");
                list.append(solde);
                layout->addWidget(solde, 4, 1);
                QLabel *solde_2 = new QLabel(QString::number(m_total + (std::round(((m_total / 100) * form.gettva()) * 100) / 100)) + " €");
                list.append(solde_2);
                layout->addWidget(solde_2, 4, 2, Qt::AlignRight);
                layout->setColumnStretch(0, 3);
                layout->setColumnStretch(1, 1);
                layout->setColumnStretch(2, 1);
                if (m_footage)
                {
                    layout->setMargin(10);
                    ui->listWidget_2->insertItem(m_layout_list[m_act_pages]->count() - 1, "Total");
                    m_list_string[m_act_pages].append("Total");
                    m_list[m_act_pages].insert(m_layout_list[m_act_pages]->count() - 1, list);
                    m_layout_list[m_act_pages]->insertLayout(m_layout_list[m_act_pages]->count() - 1, layout);
                }
                else
                {
                    layout->setMargin(10);
                    ui->listWidget_2->insertItem(m_layout_list[m_act_pages]->count(), "Total");
                    m_list_string[m_act_pages].append("Total");
                    m_list[m_act_pages].insert(m_layout_list[m_act_pages]->count(), list);
                    m_layout_list[m_act_pages]->insertLayout(m_layout_list[m_act_pages]->count(), layout);
                }
            }
        }
    }
}

void    PrintDialog::addHeader(void)
{
    formheaderDialog form;
    form.exec();
    if (form.getok())
    {
        QGridLayout *layout = new QGridLayout;
        QList<QWidget *> list;
        QVBoxLayout *grid5 = new QVBoxLayout;
        QLabel *numero = new QLabel("FACTURE" + form.getnumero(), this);
        numero->setStyleSheet("font-size: 17px; font-weight: bold;");
        QLabel *date = new QLabel("Metz le, " + form.getdate().toString(Qt::DefaultLocaleLongDate), this);

        list.append(numero);
        list.append(date);
        grid5->addWidget(numero, 0, Qt::AlignRight);
        grid5->addWidget(date, 0, Qt::AlignRight);
        layout->addLayout(grid5, 0, 1);


        QVBoxLayout *grid6 = new QVBoxLayout;
        QLabel *nom = new QLabel(form.getciv() + form.getname(), this);
        nom->setStyleSheet("font-size: 14px; font-weight: bold;");
        grid6->addWidget(nom, 0, Qt::AlignRight);
        list.append(nom);

        QVBoxLayout *grid7 = new QVBoxLayout;
        if (!form.getcomplement().isEmpty())
        {
            QLabel *complement = new QLabel(form.getcomplement(), this);
            grid7->addWidget(complement, 0, Qt::AlignRight);
            list.append(complement);
        }
        QLabel *adresse = new QLabel(form.getadresse(), this);
        QLabel *ville = new QLabel(form.getville(), this);
        grid7->addWidget(adresse, 0, Qt::AlignRight);
        grid7->addWidget(ville, 0, Qt::AlignRight);
        list.append(adresse);
        list.append(ville);
        grid6->addLayout(grid7);
        layout->addLayout(grid6, 1, 1);


        QGridLayout *grid2 = new QGridLayout;
        grid2->setGeometry(grid2->geometry());
        QLabel *entreprise = new QLabel("", this);
        entreprise->setPixmap(QPixmap::fromImage(QImage(QCoreApplication::applicationDirPath() + "/image/kremer_chauffage.png")));
        entreprise->setAlignment(Qt::AlignCenter);
        grid2->addWidget(entreprise, 0, 0, 1, 3);
        list.append(entreprise);
        QLabel *artisan = new QLabel("", this);
        list.append(artisan);
        QPixmap arti = QPixmap::fromImage(QImage(QCoreApplication::applicationDirPath() + "/image/Artisan.png"));
        artisan->setPixmap(arti.scaled(70, 120, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        grid2->addWidget(artisan, 1, 1);
        QLabel *carte = new QLabel("", this);
        QPixmap cart = QPixmap::fromImage(QImage(QCoreApplication::applicationDirPath() + "/image/Carte_visite.png"));
        carte->setPixmap(cart.scaled(65, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        grid2->addWidget(carte, 1, 2);
        list.append(carte);
        grid2->setColumnStretch(0, 1);

        QGridLayout *grid3 = new QGridLayout;
        QLabel *adresse_k = new QLabel("16, rue du Docteur Lallemand", this);
        QLabel *ville_k = new QLabel("57070 METZ Queuleu", this);
        QLabel *fixe = new QLabel("03 87 61 98 15", this);
        QLabel *portable = new QLabel("06 78 15 10 23", this);
        QLabel *mail = new QLabel("kremerchauffage@icloud.com", this);
        grid3->addWidget(adresse_k, 0, 0, 1, 2);
        grid3->addWidget(ville_k, 1, 0, 1, 2);
        grid3->addWidget(fixe, 2, 0);
        grid3->addWidget(portable, 2, 1);
        grid3->addWidget(mail, 3, 0, 1, 2);
        list.append(adresse_k);
        list.append(ville_k);
        list.append(fixe);
        list.append(portable);
        list.append(mail);
        grid2->addLayout(grid3, 1, 0);

        QGridLayout *grid4 = new QGridLayout;
        QLabel *label_bpl = new QLabel("BPL:", this);
        QLabel *label_ca = new QLabel("CA:", this);
        QLabel *bpl = new QLabel("FR76 1470 7000 3203 2210 9671 608", this);
        QLabel *ca = new QLabel("FR76 1610 6000 2986 1062 2853 675", this);
        grid4->addWidget(label_bpl, 0, 0);
        grid4->addWidget(label_ca, 1, 0);
        grid4->addWidget(bpl, 0, 1);
        grid4->addWidget(ca, 1, 1);
        list.append(label_ca);
        list.append(label_bpl);
        list.append(ca);
        list.append(bpl);
        grid4->setColumnStretch(1, 1);
        grid2->addLayout(grid4, 2, 0);
        layout->addLayout(grid2, 0, 0, 2, 1);
        layout->setColumnStretch(0, 1);

        layout->setMargin(10);
        ui->listWidget_2->insertItem(0, "Header");
        m_list_string[m_act_pages].append("Header");
        m_list[m_act_pages].insert(0, list);
        m_layout_list[m_act_pages]->insertLayout(0, layout, 0);
    }
}

void PrintDialog::on_listWidget_2_clicked(const QModelIndex &index)
{
    m_tmp = index;
    m_name = ui->listWidget_2->item(index.row())->text().split(' ')[0];
    if (index.row() != 0)
        ui->Up->setEnabled(true);
    else
        ui->Up->setEnabled(false);
    if (index.row() != ui->listWidget_2->count() - 1)
        ui->Down->setEnabled(true);
    else
        ui->Down->setEnabled(false);
    ui->Remove->setEnabled(true);
}

void PrintDialog::on_Remove_clicked()
{
    for (int i = 0; i < m_list[m_act_pages][m_tmp.row()].size(); i++)
        delete m_list[m_act_pages][m_tmp.row()][i];
    m_list[m_act_pages].removeAt(m_tmp.row());
    m_layout_list[m_act_pages]->removeItem(m_layout_list[m_act_pages]->takeAt(m_tmp.row()));
    delete ui->listWidget_2->takeItem(m_tmp.row());
    m_list_string[m_act_pages].removeAt(m_tmp.row());
    if (m_footage && m_tmp.row() == ui->listWidget_2->count())
        m_footage = false;
    if (m_name == "Header")
        m_header = false;
    if (m_name == "Total")
        m_total_p = false;
    if (m_name == "Certificat")
        m_total -= 43.18;
    ui->listWidget_2->clearSelection();
    ui->Up->setEnabled(false);
    ui->Down->setEnabled(false);
    ui->Remove->setEnabled(false);
}

void PrintDialog::on_Up_clicked()
{
    int row = m_tmp.row();
    m_layout_list[m_act_pages]->insertItem(row - 1, m_layout_list[m_act_pages]->takeAt(row));
    m_list[m_act_pages].move(row, row - 1);
    ui->listWidget_2->insertItem(row - 1, ui->listWidget_2->takeItem(row));
    m_list_string[m_act_pages].insert(row - 1, m_list_string[m_act_pages].takeAt(row));
    if (m_name != "Footage" && m_name != "Header" && m_name != "Total" && m_name != "Footage avec assurance")
        m_layout_list[m_act_pages]->setStretch(row - 1, 1);
    ui->listWidget_2->setItemSelected(ui->listWidget_2->item(row - 1), true);
    on_listWidget_2_clicked(m_tmp.sibling(row - 1, m_tmp.column()));
}

void PrintDialog::on_Down_clicked()
{
    int row = m_tmp.row();
    m_layout_list[m_act_pages]->insertItem(row + 1, m_layout_list[m_act_pages]->takeAt(row));
    m_list[m_act_pages].move(row, row + 1);
    ui->listWidget_2->insertItem(row + 1, ui->listWidget_2->takeItem(row));
    m_list_string[m_act_pages].insert(row + 1, m_list_string[m_act_pages].takeAt(row));
    if (m_name != "Footage" && m_name != "Header")
        m_layout_list[m_act_pages]->setStretch(row + 1, 1);
    ui->listWidget_2->setItemSelected(ui->listWidget_2->item(row + 1), true);
    on_listWidget_2_clicked(m_tmp.sibling(row + 1, m_tmp.column()));
}

void PrintDialog::on_add_clicked()
{
    m_act_pages++;
    albert_setup();
    if (m_act_pages < m_list.size() - 1)
        ui->right->setEnabled(true);
    else
        ui->right->setEnabled(false);
    if (m_act_pages > 0)
        ui->left->setEnabled(true);
    else
        ui->left->setEnabled(false);
    ui->delete_page->setEnabled(true);
    m_list_string.insert(m_act_pages, QStringList());
}

void PrintDialog::on_left_clicked()
{
    m_pages[m_act_pages]->hide();
    m_act_pages--;
    m_pages[m_act_pages]->setVisible(true);
    ui->nbr_page->setText(QString::number(m_act_pages + 1) + "/" + QString::number(m_list.size()));
    if (m_act_pages < m_list.size() - 1)
        ui->right->setEnabled(true);
    else
        ui->right->setEnabled(false);
    if (m_act_pages > 0)
        ui->left->setEnabled(true);
    else
        ui->left->setEnabled(false);
    ui->listWidget_2->clear();
    for (int i = 0; i < m_list_string[m_act_pages].size(); i++)
        ui->listWidget_2->addItem(m_list_string[m_act_pages][i]);
}
void PrintDialog::on_right_clicked()
{
    m_pages[m_act_pages]->hide();
    m_act_pages++;
    m_pages[m_act_pages]->setVisible(true);
    ui->nbr_page->setText(QString::number(m_act_pages + 1) + "/" + QString::number(m_list.size()));
    if (m_act_pages < m_list.size() - 1)
        ui->right->setEnabled(true);
    else
        ui->right->setEnabled(false);
    if (m_act_pages > 0)
        ui->left->setEnabled(true);
    else
        ui->left->setEnabled(false);
    ui->listWidget_2->clear();
    for (int i = 0; i < m_list_string[m_act_pages].size(); i++)
        ui->listWidget_2->addItem(m_list_string[m_act_pages][i]);
}

void PrintDialog::on_delete_page_clicked()
{
    QWidget *w = m_pages[m_act_pages];
    m_list.removeAt(m_act_pages);
    m_pages.removeAt(m_act_pages);
    m_layout_list.removeAt(m_act_pages);
    if (m_act_pages == m_list.size())
        m_act_pages--;
    delete w;
    m_pages[m_act_pages]->setVisible(true);
    if (m_act_pages < m_list.size() - 1)
        ui->right->setEnabled(true);
    else
        ui->right->setEnabled(false);
    if (m_act_pages > 0)
        ui->left->setEnabled(true);
    else
        ui->left->setEnabled(false);
    if (m_list.size() == 1)
        ui->delete_page->setEnabled(false);
    ui->nbr_page->setText(QString::number(m_act_pages + 1) + "/" + QString::number(m_list.size()));
    ui->listWidget_2->clear();
    for (int i = 0; i < m_list_string[m_act_pages].size(); i++)
        ui->listWidget_2->addItem(m_list_string[m_act_pages][i]);
}

void PrintDialog::on_reset_clicked()
{
    for (int i = 0; i < m_list[m_act_pages].size(); i++)
        for (int j = 0; j < m_list[m_act_pages][i].size(); j++)
            delete m_list[m_act_pages][i][j];
    m_list[m_act_pages].clear();
    ui->listWidget_2->clear();
    m_list_string[m_act_pages].clear();
}

void PrintDialog::on_pushButton_clicked()
{
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName("output.pdf");
            printer.setFullPage(false);

            QPainter painter(&printer);
            QWidget *w = m_pages[m_act_pages];
            double xscale = printer.pageRect().width() / double(w->width());
            double yscale = printer.pageRect().height() / double(w->height());
            double scale = qMin(xscale, yscale);
            painter.translate(printer.paperRect().center());
            painter.scale(scale, scale);
            painter.translate(-w->width()/ 2, -w->height()/ 2);
            w->render(&painter);
}
