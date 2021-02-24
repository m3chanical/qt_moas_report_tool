#include "moasrequest.h"
#include <QDebug>
#include <QNetworkReply>
#include <QMessageBox>
#include <QIcon>

MoasRequest::MoasRequest(QObject *parent) : QObject(parent)
{
    // TODO: create a signal here and connect it to a slot on the main form for announcing completion.
}

void MoasRequest::Post(QMap<QString, QString> post_data)
{
    qDebug() << moas_report_url.toString();
    post_data["formID"] = "50690741078155";

    QMap<QString, QString>::const_iterator i = post_data.constBegin();
    while(i != post_data.constEnd())
    {
        qDebug() << i.key() << ": " << i.value();
        params.addQueryItem(i.key(), i.value());
        ++i;
    }
    QNetworkRequest qreq(moas_report_url);

    qreq.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");
    reply = qnam->post(qreq, params.query(QUrl::FullyEncoded).toUtf8());
    connect(reply, &QNetworkReply::finished, this, &MoasRequest::httpFinished);
}

void MoasRequest::httpFinished()
{
    QMessageBox msgBox;
    msgBox.setWindowIcon(QIcon(":/pics/moas"));
    QByteArray res = reply->readAll();

    qDebug() << "reply: " << res;
    if(res.contains("Thank You!"))
    {
        msgBox.setWindowTitle("Success");
        msgBox.setText("Report successfully submitted. Look for a copy in your email!");        
    }
    else if(res.contains("Incomplete Values"))
    {
        msgBox.setWindowTitle("Error");
        msgBox.setText("There are incomplete values or errors in your form. Please correct them. Ensure that all fields with asterisks (*) are filled out");
    }
    msgBox.exec();
}
