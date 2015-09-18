#include "database.h"

#include <QApplication>
#include <QtSql>

database::database()
{

    QSqlDatabase db = QSqlDatabase::addDatabase("MYSQL");
        db.setHostName("sandnes.lordmarty.com:3306");
        db.setDatabaseName("nerveblocker");
        db.setUserName("nerve");
        db.setPassword("nerve");
        bool ok = db.open();
        if(ok){
            QSqlQuery query;
              query.exec("SELECT image_id, image_map FROM images");
              while (query.next()) {
                      int image_id = query.value(0).toInt();
                      int image_map = query.value(1).toInt();
                      qDebug() << image_id << image_map;
                  }
        }else{

        }
}

