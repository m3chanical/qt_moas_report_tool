#include "dialogabout.h"
#include "ui_dialogabout.h"
#include <QMovie>

DialogAbout::DialogAbout(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogAbout)
{
    QMovie *movie = new QMovie(QString::fromUtf8(":/pics/small_animated_logo"));
    ui->setupUi(this);

    ui->labelLogo->setMovie(movie);
    movie->start();

    setWindowTitle(QString::fromUtf8("~# whoami"));
    setWindowFlags(Qt::Dialog | Qt::MSWindowsFixedSizeDialogHint);
}

DialogAbout::~DialogAbout()
{
    delete ui;
}

void DialogAbout::on_pushButton_clicked()
{
    this->close();
}
