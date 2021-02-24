#ifndef DEPUTYMOASCONTACT_H
#define DEPUTYMOASCONTACT_H

#include <QDialog>
#include <QMap>

namespace Ui {
class DeputyMoasContact;
}

class DeputyMoasContact : public QDialog
{
    Q_OBJECT

public:
    explicit DeputyMoasContact(QWidget *parent = nullptr);
    ~DeputyMoasContact();

private slots:
    void on_buttonBox_accepted();

    void on_q23_deputysSca_editingFinished();

    void on_q24_deputysModern_editingFinished();

    void on_q25_deputysEmail_editingFinished();

signals:
    void on_deputyUpdated(QMap<QString, QString> deputy_contact);

private:
    Ui::DeputyMoasContact *ui;
};

#endif // DEPUTYMOASCONTACT_H
