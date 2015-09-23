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
    Q_OBJECT


public:
    explicit database(QObject *parent = 0);


signals:

public slots:
    void checkforupdate(int);
    void open();
    void close();
    void getUpdate(int);
    void replyFinished (QNetworkReply *reply);
    void mapreplyFinished (QNetworkReply *reply);

private:
   QNetworkAccessManager *manager;
   QNetworkAccessManager *manager2;

};

#endif // DATABASE_H
