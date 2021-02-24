#include "deputymoascontact.h"
#include "ui_deputymoascontact.h"
#include "mainwindow.h"
#include <QPushButton>

DeputyMoasContact::DeputyMoasContact(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DeputyMoasContact)
{
    ui->setupUi(this);

    setWindowTitle(QString::fromUtf8("Deputy MoAS Contact Information"));
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    connect(this, &DeputyMoasContact::on_deputyUpdated, qobject_cast<MainWindow*>(parent), &MainWindow::on_deputyUpdated);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
}

DeputyMoasContact::~DeputyMoasContact()
{
    delete ui;
}

void DeputyMoasContact::on_buttonBox_accepted()
{

    QMap<QString, QString> deputy_info;

    deputy_info[ui->q23_deputysSca->objectName()] = ui->q23_deputysSca->text();
    deputy_info[ui->q24_deputysModern->objectName()] = ui->q24_deputysModern->text();
    deputy_info[ui->q25_deputysEmail->objectName()] = ui->q25_deputysEmail->text();

    emit on_deputyUpdated(deputy_info);
}

void DeputyMoasContact::on_q23_deputysSca_editingFinished()
{
    // TODO: Add validation
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
}

void DeputyMoasContact::on_q24_deputysModern_editingFinished()
{
    // TODO: Add validation
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
}

void DeputyMoasContact::on_q25_deputysEmail_editingFinished()
{
    // TODO: Add validation
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
}
