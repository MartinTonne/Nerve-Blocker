#include "database.h"

#include <QtSql>
#include <QApplication>

database::database(QObject *parent) :
    QObject(parent)
{

}


void database::checkforupdate(int localversion){

        QSqlQuery query;
        query.exec("SELECT version FROM version DECS");
        while (query.next()) {
        int version = query.value(0).toInt();

        if(version > localversion){
            QSettings s;
            s.setValue("version", version);
            while(version>localversion){
                localversion++;
                database::getUpdate(localversion);

            }

            }


              qDebug() << localversion << version;
        }

}

void database::open(){
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("192.168.1.90");
    db.setDatabaseName("nerveblocker");
    db.setUserName("nerve");
    db.setPassword("nerve");
    bool ok = db.open();
    if(!ok){
        qDebug() << db.lastError();

    }else{


        QSettings s;
        int version = s.value("version", 0).toInt();

        database::checkforupdate(version);

    }
}
void database::close(){



}
void database::getUpdate(int version){

    QSqlQuery query;
      query.exec("SELECT image_id, image_map FROM images WHERE version="+version);
      while (query.next()) {
              int image_id = query.value(0).toInt();
              int image_map = query.value(1).toInt();
              manager = new QNetworkAccessManager(this);

                  connect(manager, SIGNAL(finished(QNetworkReply*)),
                          this, SLOT(replyFinished(QNetworkReply*)));
                  QString img_url = QString("http://sandnes.lordmarty.com/tmp/%1.png").arg(image_id);
                  QNetworkReply* reply = manager->get(QNetworkRequest(QUrl(img_url)));
                          reply->setProperty("imageid", image_id);

                manager2 = new QNetworkAccessManager(this);
                 connect(manager2, SIGNAL(finished(QNetworkReply*)),
                          this, SLOT(mapreplyFinished(QNetworkReply*)));
                  QString map_url = QString("http://sandnes.lordmarty.com/tmp/%1_map.png").arg(image_map);

                  QNetworkReply* reply2 = manager2->get(QNetworkRequest(QUrl(map_url)));
                          reply2->setProperty("imagemap", image_map);




          }
}
void database::replyFinished (QNetworkReply *reply)
{
    if(reply->error())
    {
        qDebug() << "ERROR!";
        qDebug() << reply->errorString();
    }
    else
    {
        qDebug() << reply->header(QNetworkRequest::LocationHeader).toString();

        qDebug() << reply->header(QNetworkRequest::LastModifiedHeader).toDateTime().toString();
        qDebug() << reply->header(QNetworkRequest::ContentLengthHeader).toULongLong();
        qDebug() << reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        qDebug() << reply->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();
        QString basePath = QStandardPaths::standardLocations(QStandardPaths::HomeLocation)[0];

        int image_id = reply->property("imageid").toInt();
        qDebug() << image_id;
        qDebug() << QString(basePath+"\\nerveblocker\\%1.png").arg(image_id);

        QFile *file = new QFile(QString(basePath+"\\nerveblocker\\%1.png").arg(image_id));
        if(file->open(QFile::Append))
        {
            file->write(reply->readAll());
            file->flush();
            file->close();
        }
        delete file;

    }


}
void database::mapreplyFinished (QNetworkReply *reply2)
{
    if(reply2->error())
    {
        qDebug() << "ERROR!";
        qDebug() << reply2->errorString();
    }
    else
    {
        qDebug() << reply2->header(QNetworkRequest::LocationHeader).toString();

        qDebug() << reply2->header(QNetworkRequest::LastModifiedHeader).toDateTime().toString();
        qDebug() << reply2->header(QNetworkRequest::ContentLengthHeader).toULongLong();
        qDebug() << reply2->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        qDebug() << reply2->attribute(QNetworkRequest::HttpReasonPhraseAttribute).toString();
        QString basePath = QStandardPaths::standardLocations(QStandardPaths::HomeLocation)[0];

        int image_map = reply2->property("imagemap").toInt();
        qDebug() << image_map;
        qDebug() << QString(basePath+"\\nerveblocker\\%1_map.png").arg(image_map);

        QFile *file = new QFile(QString(basePath+"\\nerveblocker\\%1_map.png").arg(image_map));
        if(file->open(QFile::Append))
        {
            file->write(reply2->readAll());
            file->flush();
            file->close();
        }
        delete file;

    }


}
