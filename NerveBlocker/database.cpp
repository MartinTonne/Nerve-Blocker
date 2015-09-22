#include "database.h"

#include <QtSql>
#include <QApplication>

database::database()
{
    database::open();

    QSettings s;
    int version = s.value("version", 0).toInt();

    database::checkforupdate(version);


    database::close();

}

void database::checkforupdate(int localversion){

        QSqlQuery query;
        query.exec("SELECT version FROM version DECS");
        while (query.next()) {
        int version = query.value(0).toInt();

        if(version > localversion){
            QSettings s;
            s.setValue("version", version);
            database::getUpdate();

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

    }
}
void database::close(){



}
void database::getUpdate(){
    QString basePath = QStandardPaths::standardLocations(QStandardPaths::HomeLocation)[0];

    QSqlQuery query;
      query.exec("SELECT image_id, image_map FROM images");
      while (query.next()) {
              int image_id = query.value(0).toInt();
              int image_map = query.value(1).toInt();

          }
}
