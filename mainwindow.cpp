#include <QtWidgets>
#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "moaspost.h"
#include <QRegularExpression>
#include <QRegularExpressionValidator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowIcon(QIcon(":/pics/moas"));
    setWindowTitle(QString::fromUtf8("MoAS Report Tool"));
    setWindowFlags(Qt::Window | Qt::MSWindowsFixedSizeDialogHint);

    ui->q4_whichGroup->addItems(groupList);
    ui->q5_whichQuarter->addItems(quarterList);
    ui->q41_whatIs->addItems(positionList);
    ui->memberExpireDateEdit->setDateTime(QDateTime::currentDateTime());

    ui->q6_whatYear->installEventFilter(this);
    ui->q19_membershipNumber->installEventFilter(this);

    QRegularExpression rx("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b",
                              QRegularExpression::CaseInsensitiveOption); // email regex
    ui->q18_emailAddress->setValidator(new QRegularExpressionValidator(rx, this));
    ui->q43_seneschalsEmail->setValidator(new QRegularExpressionValidator(rx, this));

    // setting these up in case they aren't changed, because they default to some text
    post_request[ui->q4_whichGroup->objectName()] = ui->q4_whichGroup->currentText();
    post_request[ui->q5_whichQuarter->objectName()] = ui->q5_whichQuarter->currentText();
    post_request[ui->q41_whatIs->objectName()] = ui->q41_whatIs->currentText();

    load_default(); // load default settings, if any, into the form
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionAbout_triggered()
{
    DialogAbout dialogAbout(this);
    dialogAbout.exec();
}

void MainWindow::on_actionExport_Settings_triggered()
{
    QString export_settings = QFileDialog::getOpenFileName(this,
                                 tr("Save report settings") + QString("..."),
                                 "",
                                 tr("Json files") + QString(" (*.json)"));

    if(!export_settings.isEmpty())
    {
        save_settings(export_settings);
    }
}

void MainWindow::on_actionImport_Settings_triggered()
{
    QString import_settings = QFileDialog::getOpenFileName(this,
                                 tr("Open json settings") + QString("..."),
                                 "",
                                 tr("Json files") + QString(" (*.json)"));

    if(!import_settings.isEmpty())
    {
        load_settings(import_settings);
    }
}

void MainWindow::on_submitButton_clicked()
{
    QMessageBox::StandardButton reply;

    post_request[ui->q38_isThere38->objectName()] = ui->q38_isThere38->toPlainText();
    post_request[ui->q37_isThere37->objectName()] = ui->q37_isThere37->toPlainText();
    post_request[ui->q36_whatAre->objectName()] = ui->q36_whatAre->toPlainText();
    post_request[ui->q29_workshopsamp->objectName()] = ui->q29_workshopsamp->toPlainText();
    post_request[ui->q32_eventAamps->objectName()] = ui->q32_eventAamps->toPlainText();
    post_request[ui->q46_collegiaOr46->objectName()] = ui->q46_collegiaOr46->toPlainText();
    post_request[ui->q34_miscAamps->objectName()] = ui->q34_miscAamps->toPlainText();

    reply = QMessageBox::question(this, "Submit MoAS Report", "Are you sure you want to submit your report?",
                                    QMessageBox::Yes|QMessageBox::No);
    // pass by ref?
    if(reply == QMessageBox::Yes)
        moas_post.Post(post_request);

    // TODO: on success, clear the post_request map?

}

void MainWindow::load_default()
{

}

void MainWindow::load_settings(QString import_file)
{
    // get json settings, apply to widgets
    qDebug() << import_file;
}

void MainWindow::save_settings(QString import_file)
{
    // create json file, save it.
    qDebug() << import_file;
}

bool MainWindow::eventFilter(QObject *watched, QEvent *event)
{    
    if((watched == ui->q6_whatYear || watched == ui->q19_membershipNumber)
        && event->type() == QEvent::MouseButtonPress)
    {
        ui->q6_whatYear->setCursorPosition(0);
        return true;
    }
    else
    {
        return QMainWindow::eventFilter(watched, event);
    }
}

void MainWindow::on_q41_whatIs_activated(int index)
{
    if(index == 1)
    {
        BaronialMoasContact baronialMoasContact(this);
        baronialMoasContact.exec();
    }
    else
    {
        post_request.remove("");
        post_request.remove("");
    }
}

void MainWindow::on_contactInfoRadioYes_clicked()
{
    post_request["q14_hasAny"] = "Yes";
    MoasContact moasContact(this);
    moasContact.exec();
}

void MainWindow::on_deputyRadioYes_clicked()
{
    post_request["q26_doYou"] = "Yes";
    DeputyMoasContact deputyContact(this);
    deputyContact.exec();
}

void MainWindow::on_moasUpdated(QMap<QString, QString> moas_contact)
{
    post_request.insert(moas_contact);
}

void MainWindow::on_deputyUpdated(QMap<QString, QString> deputy_contact)
{
    post_request.insert(deputy_contact);
}

void MainWindow::on_baronialUpdated(QMap<QString, QString> baronial_contact)
{    
    post_request.insert(baronial_contact);
}

void MainWindow::on_q4_whichGroup_currentIndexChanged(const QString &arg1)
{
    post_request[ui->q4_whichGroup->objectName()] = arg1;
    check_form_valid();
}

void MainWindow::on_q5_whichQuarter_currentIndexChanged(const QString &arg1)
{
    post_request[ui->q5_whichQuarter->objectName()] = arg1;
    check_form_valid();
}

void MainWindow::on_q6_whatYear_editingFinished()
{
    post_request[ui->q6_whatYear->objectName()] = ui->q6_whatYear->text();
    check_form_valid();
}

void MainWindow::on_q41_whatIs_currentIndexChanged(const QString &arg1)
{
    post_request[ui->q41_whatIs->objectName()] = arg1;
    check_form_valid();
}

void MainWindow::on_q9_scaName_editingFinished()
{
    post_request[ui->q9_scaName->objectName()] = ui->q9_scaName->text();
    check_form_valid();
}

void MainWindow::on_q10_modernName_editingFinished()
{
    post_request[ui->q10_modernName->objectName()] = ui->q10_modernName->text();
    check_form_valid();
}

void MainWindow::on_q18_emailAddress_editingFinished()
{
    post_request[ui->q18_emailAddress->objectName()] = ui->q18_emailAddress->text();
    check_form_valid();
}

void MainWindow::on_q18_emailAddress_textEdited(const QString &)
{
    if(!ui->q18_emailAddress->hasAcceptableInput())
    {
        ui->label_7->setStyleSheet("QLabel { color : red; }");
    }
    else
    {
        ui->label_7->setStyleSheet("QLabel { color : white; }");
    }
    check_form_valid();
}

void MainWindow::on_q19_membershipNumber_editingFinished()
{
    post_request[ui->q19_membershipNumber->objectName()] = ui->q19_membershipNumber->text();
    check_form_valid();
}

void MainWindow::on_memberExpireDateEdit_dateChanged(const QDate &date)
{
    post_request["q17_expirationDate[month]"] = QString::number(date.month());
    post_request["q17_expirationDate[day]"] = QString::number(date.day());
    post_request["q17_expirationDate[year]"] = QString::number(date.year());
    check_form_valid();
}

void MainWindow::on_warrantYes_clicked()
{
    post_request["q39_doYou39"] = "Yes";
    check_form_valid();
}

void MainWindow::on_warrantNo_clicked()
{
    post_request["q39_doYou39"] = "No";
    check_form_valid();
}

void MainWindow::on_modernShare_stateChanged(int arg1)
{
    qDebug() << "checkbox state: " << arg1;
    // TODO: figure out wtf to do about the stupid post request.
    // maybe just add it all when generating it
}

void MainWindow::on_q42_seneschalsSca_editingFinished()
{
    post_request[ui->q42_seneschalsSca->objectName()] = ui->q42_seneschalsSca->text();
    check_form_valid();
}

void MainWindow::on_q43_seneschalsEmail_editingFinished()
{
    post_request[ui->q43_seneschalsEmail->objectName()] = ui->q43_seneschalsEmail->text();
    check_form_valid();
}

void MainWindow::on_q43_seneschalsEmail_textEdited(const QString &)
{
    if(!ui->q43_seneschalsEmail->hasAcceptableInput())
    {
        ui->label_12->setStyleSheet("QLabel { color : red; }");
    }
    else
    {
        ui->label_12->setStyleSheet("QLabel { color : white; }");
    }
    check_form_valid();
}

void MainWindow::on_contactInfoRadioNo_clicked()
{
    post_request["q14_hasAny"] = "No";

    post_request.remove("q20_moasMailing[addr_line1]");
    post_request.remove("q20_moasMailing[addr_line2]");
    post_request.remove("q20_moasMailing[city]");
    post_request.remove("q20_moasMailing[state]");
    post_request.remove("q20_moasMailing[postal]");
    post_request.remove("q20_moasMailing[country]");
    post_request.remove("q21_moasPhone21[area]");
    post_request.remove("q21_moasPhone21[phone]");

    check_form_valid();    
}

void MainWindow::on_deputyRadioNo_clicked()
{
    post_request["q26_doYou"] = "No";

    // if we change our mind we don't want to transmit this data anyway.
    post_request.remove("q23_deputysSCA");
    post_request.remove("q24_deputyModern");
    post_request.remove("q25_deputysEmail");

    check_form_valid();   
}

void MainWindow::check_form_valid()
{
    if(!ui->q4_whichGroup->currentText().isEmpty()
            && !ui->q5_whichQuarter->currentText().isEmpty()
            && ui->q6_whatYear->hasAcceptableInput()
            && !ui->q41_whatIs->currentText().isEmpty()
            && !ui->q9_scaName->text().isEmpty()
            && !ui->q10_modernName->text().isEmpty()
            && ui->q18_emailAddress->hasAcceptableInput()
            && ui->q19_membershipNumber->hasAcceptableInput()
            && ui->memberExpireDateEdit->dateTime() > QDateTime::currentDateTime()
            && (ui->warrantYes->isChecked() || ui->warrantNo->isChecked())
            && !ui->q42_seneschalsSca->text().isEmpty()
            && ui->q43_seneschalsEmail->hasAcceptableInput()
            && (ui->contactInfoRadioYes->isChecked() || ui->contactInfoRadioNo->isChecked())
            && (ui->deputyRadioYes->isChecked() || ui->deputyRadioNo->isChecked())
      )
    {
        ui->submitButton->setEnabled(true);
    }
    else
    {
        ui->submitButton->setEnabled(false);
    }
}

void MainWindow::on_q19_membershipNumber_textEdited(const QString &)
{
    check_form_valid();
}

void MainWindow::on_q6_whatYear_textEdited(const QString &)
{
    check_form_valid();
}
