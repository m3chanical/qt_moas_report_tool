#ifndef BARONIALMOASCONTACT_H
#define BARONIALMOASCONTACT_H

#include <QDialog>
#include <QMap>


namespace Ui {
class BaronialMoasContact;
}

class BaronialMoasContact : public QDialog
{
    Q_OBJECT

public:
    explicit BaronialMoasContact(QWidget *parent = nullptr);
    ~BaronialMoasContact();

private slots:
    void on_buttonBox_accepted();
    void on_q44_baronialMoass44_editingFinished();
    void on_q45_baronialMoass45_editingFinished();

    void on_q45_baronialMoass45_textEdited(const QString &arg1);

signals:
    void on_baronialUpdated(QMap<QString, QString> baronial_contact);

private:
    Ui::BaronialMoasContact *ui;
};

#endif // BARONIALMOASCONTACT_H
