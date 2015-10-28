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
        }
        database::getUpdate(localversion);

}

void database::open(){
    QString basePath = QCoreApplication::applicationDirPath();
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(basePath+"/nerveblocker/nerve.sqlite");
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
void database::getDB(){

              manager = new QNetworkAccessManager(this);

                  connect(manager, SIGNAL(finished(QNetworkReply*)),
                          this, SLOT(dbdlFinished(QNetworkReply*)));
                  QString img_url = QString("http://sandnes.lordmarty.com/tmp/nerve.sqlite");
                  manager->get(QNetworkRequest(QUrl(img_url)));







}

void database::dbdlFinished (QNetworkReply *reply)
{
    if(reply->error())
    {
        qDebug() << "ERROR!";
        qDebug() << reply->errorString();
    }
    else
    {

        QString basePath = QCoreApplication::applicationDirPath();



        qDebug() << QString(basePath+"/nerveblocker/nerve.sqlite");



        if(!QDir(basePath+"/nerveblocker/").exists())
            QDir().mkdir(basePath+"/nerveblocker/");
        QFile *file = new QFile(QString(basePath+"/nerveblocker/nerve.sqlite"));
        if(file->open(QFile::Append))
        {
            file->write(reply->readAll());
            file->flush();
            file->close();
            qDebug() << "fileopen and appending";
        }
        delete file;
         qDebug() << "DBdownloaded";
         open();
    }


}


void database::getUpdate(int version){


    QSqlQuery query;
      query.exec(QString("SELECT image_id, image_map FROM images WHERE version=%1").arg(version));

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

        QString basePath = QCoreApplication::applicationDirPath();

        int image_id = reply->property("imageid").toInt();

        qDebug() << QString(basePath+"/nerveblocker/%1.png").arg(image_id);

        QFile *file = new QFile(QString(basePath+"/nerveblocker/%1.png").arg(image_id));
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

        QString basePath = QCoreApplication::applicationDirPath();

        int image_map = reply2->property("imagemap").toInt();
        qDebug() << image_map;
        qDebug() << QString(basePath+"/nerveblocker/%1_map.png").arg(image_map);

        QFile *file = new QFile(QString(basePath+"/nerveblocker/%1_map.png").arg(image_map));
        if(file->open(QFile::Append))
        {
            file->write(reply2->readAll());
            file->flush();
            file->close();
        }
        delete file;

    }


}
