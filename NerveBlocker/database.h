#ifndef DATABASE_H
#define DATABASE_H
#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrl>
#include <QDateTime>
#include <QFile>
#include <QDebug>
#include <QtSql>

class database : public QObject
{
    Q_OBJECT


public:
    explicit database(QObject *parent = 0);


signals:

public slots:
    void checkforupdate(int);
    void open();
    void close();
    void getUpdate(int);
    void getDB();
    void replyFinished (QNetworkReply *reply);
    void mapreplyFinished (QNetworkReply *reply);
    void dbdlFinished (QNetworkReply *reply);

private:
   QNetworkAccessManager *manager;
   QNetworkAccessManager *manager2;
   QSqlDatabase db;
};

#endif // DATABASE_H
