#include "baronialmoascontact.h"
#include "ui_baronialmoascontact.h"
#include "mainwindow.h"
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QPushButton>

BaronialMoasContact::BaronialMoasContact(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BaronialMoasContact)
{
    ui->setupUi(this);

    setWindowTitle(QString::fromUtf8("Baronial MoAS's Contact Information"));
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);

    connect(this, &BaronialMoasContact::on_baronialUpdated, qobject_cast<MainWindow*>(parent), &MainWindow::on_baronialUpdated);
    QRegularExpression rx("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b",
                              QRegularExpression::CaseInsensitiveOption); // email regex
    ui->q45_baronialMoass45->setValidator(new QRegularExpressionValidator(rx, this));
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

}

BaronialMoasContact::~BaronialMoasContact()
{
    delete ui;
}

void BaronialMoasContact::on_buttonBox_accepted()
{
    QMap<QString, QString> baronial_contact;

    baronial_contact[ui->q44_baronialMoass44->objectName()] = ui->q44_baronialMoass44->text();
    baronial_contact[ui->q45_baronialMoass45->objectName()] = ui->q45_baronialMoass45->text();

    emit on_baronialUpdated(baronial_contact);
}

void BaronialMoasContact::on_q44_baronialMoass44_editingFinished()
{
    // TODO: check is valid
    //ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
}

void BaronialMoasContact::on_q45_baronialMoass45_editingFinished()
{
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
}

void BaronialMoasContact::on_q45_baronialMoass45_textEdited(const QString &)
{
    if(!ui->q45_baronialMoass45->hasAcceptableInput())
    {
        ui->label_2->setStyleSheet("QLabel { color : red; }");
    }
    else
    {
        ui->label_2->setStyleSheet("QLabel { color : white; }");
    }
}
