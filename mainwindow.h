#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "dialogabout.h"
#include "moascontact.h"
#include "deputymoascontact.h"
#include "baronialmoascontact.h"
#include "moasrequest.h"

#include <QFile>
#include <QFileDialog>
#include <QStringList>
#include <QMap>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    bool eventFilter(QObject *watched, QEvent *event);
    ~MainWindow();

public slots:
    void on_moasUpdated(QMap<QString, QString> moas_contact);
    void on_deputyUpdated(QMap<QString, QString> deputy_contact);
    void on_baronialUpdated(QMap<QString, QString> baronial_contact);

private slots:
    void on_actionAbout_triggered();
    void on_submitButton_clicked();
    void on_actionExport_Settings_triggered();
    void on_actionImport_Settings_triggered();

    void load_settings(QString import_file);
    void save_settings(QString import_file);
    void load_default();

    void on_q41_whatIs_activated(int index);
    void on_contactInfoRadioYes_clicked();
    void on_deputyRadioYes_clicked();

    void on_q4_whichGroup_currentIndexChanged(const QString &arg1);
    void on_q5_whichQuarter_currentIndexChanged(const QString &arg1);
    void on_q6_whatYear_editingFinished();
    void on_q41_whatIs_currentIndexChanged(const QString &arg1);
    void on_q9_scaName_editingFinished();
    void on_q10_modernName_editingFinished();
    void on_q18_emailAddress_editingFinished();
    void on_q18_emailAddress_textEdited(const QString &arg1);
    void on_q19_membershipNumber_textEdited(const QString &arg1);
    void on_q6_whatYear_textEdited(const QString &arg1);
    void on_q43_seneschalsEmail_textEdited(const QString &arg1);

    void on_q19_membershipNumber_editingFinished();
    void on_memberExpireDateEdit_dateChanged(const QDate &date);
    void on_warrantYes_clicked();
    void on_warrantNo_clicked();
    void on_modernShare_stateChanged(int arg1);
    void on_q42_seneschalsSca_editingFinished();
    void on_q43_seneschalsEmail_editingFinished();
    void on_contactInfoRadioNo_clicked();
    void on_deputyRadioNo_clicked();

    void check_form_valid();

private:
    int i = 0;
    Ui::MainWindow *ui;
    MoasRequest moas_post;
    QMap<QString, QString> post_request;
    QStringList groupList = {
        "Abhainn Iarthair",
        "Berley Cort",
        "Black Diamond",
        "Bright Hills",
        "Caer Gelynniog",
        "Caer Mear",
        "Dun Carraig",
        "Greenlion Bay",
        "Highland Foorde",
        "Isenfir",
        "Lochmere",
        "Marinus",
        "Ponte Alto",
        "Rencester",
        "Rivers Point",
        "Roxbury Mill",
        "Seven Hills",
        "Spiaggia Levantina",
        "Stierbach",
        "Storvik",
        "Sudentorre",
        "Tir-y-Don",
        "Yarnvid"
    };
    QStringList quarterList = {
        "1st Quarter (Jan - Mar)",
        "2nd Quarter (Apr - Jun)",
        "3rd Quarter (Jul - Sep)",
        "4th Quarter (Oct - Dec)"
    };
    QStringList positionList = {
        "Baronial MoAS",
        "Canton MoAS",
        "Shire MoAS",
        "College MoAS",
        "Branch Seneschal",
        "Deputy MoAS",
        "Other"
    };
};
#endif // MAINWINDOW_H
