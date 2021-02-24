#ifndef MOASCONTACT_H
#define MOASCONTACT_H

#include <QDialog>
#include <QMap>

namespace Ui {
class MoasContact;
}

class MoasContact : public QDialog
{
    Q_OBJECT

public:
    explicit MoasContact(QWidget *parent = nullptr);
    ~MoasContact();

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

    void on_moasAreaCode_editingFinished();

    void on_moasStreet_editingFinished();

    void on_moasStreetTwo_editingFinished();

    void on_moasCity_editingFinished();

    void on_moasState_editingFinished();

    void on_moasZipCode_editingFinished();

    void on_moasPhoneNumber_editingFinished();

signals:
    void on_moasUpdated(QMap<QString, QString> moas_contact);

private:
    Ui::MoasContact *ui;
};

#endif // MOASCONTACT_H
