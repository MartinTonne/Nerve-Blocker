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
class database : public QObject
{
public:
    database();

public slots:
    void checkforupdate(int);
    void open();
    void close();
    void getUpdate();
    void replyFinished (QNetworkReply *reply);


private:
   QNetworkAccessManager *manager;
};

#endif // DATABASE_H
