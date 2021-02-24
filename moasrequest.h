#ifndef MOASREQUEST_H
#define MOASREQUEST_H

#include <QObject>
#include <QMap>
#include <QNetworkAccessManager>
#include <QUrlQuery>

class MoasRequest : public QObject
{
    Q_OBJECT
public:
    explicit MoasRequest(QObject *parent = nullptr);
    void Post(QMap<QString, QString> post_data);

private slots:
    void httpFinished();

signals:


private:
    QUrl moas_report_url = QUrl("https://submit.jotform.us/submit/50690741078155/");
    QNetworkAccessManager *qnam = new QNetworkAccessManager(this);

    QNetworkReply *reply;
    QUrlQuery params;
};

#endif // MOASREQUEST_H
