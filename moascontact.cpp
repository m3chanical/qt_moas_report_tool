#include "moascontact.h"
#include "mainwindow.h"
#include "ui_moascontact.h"
#include <QPushButton>

MoasContact::MoasContact(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MoasContact)
{
    ui->setupUi(this);

    setWindowTitle(QString::fromUtf8("Update MoAS Contact Information"));
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    connect(this, &MoasContact::on_moasUpdated, qobject_cast<MainWindow*>(parent), &MainWindow::on_moasUpdated);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

}

MoasContact::~MoasContact()
{
    delete ui;
}

void MoasContact::on_buttonBox_accepted()
{
    QMap<QString, QString> moas_contact;

    moas_contact["q20_moasMailing[addr_line1]"] = ui->moasStreet->text();
    moas_contact["q20_moasMailing[addr_line2]"] = ui->moasStreetTwo->text();
    moas_contact["q20_moasMailing[city]"] = ui->moasCity->text();
    moas_contact["q20_moasMailing[state]"] = ui->moasState->text();
    moas_contact["q20_moasMailing[postal]"] = ui->moasZipCode->text();
    moas_contact["q20_moasMailing[country]"] = "United States"; // hardcoded because i'm lazy af.
    moas_contact["q21_moasPhone21[area]"] = ui->moasAreaCode->text();
    moas_contact["q21_moasPhone21[phone]"] = ui->moasPhoneNumber->text();

    emit on_moasUpdated(moas_contact);
}


void MoasContact::on_buttonBox_rejected()
{    
    this->close();
}

void MoasContact::on_moasAreaCode_editingFinished()
{
    // TODO: Add validation
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
}

void MoasContact::on_moasStreet_editingFinished()
{
    // TODO: Add validation
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
}

void MoasContact::on_moasStreetTwo_editingFinished()
{
    // TODO: Add validation
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
}

void MoasContact::on_moasCity_editingFinished()
{
    // TODO: Add validation
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
}

void MoasContact::on_moasState_editingFinished()
{
    // TODO: Add validation
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
}

void MoasContact::on_moasZipCode_editingFinished()
{
    // TODO: Add validation
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
}

void MoasContact::on_moasPhoneNumber_editingFinished()
{
    // TODO: Add validation
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
}
