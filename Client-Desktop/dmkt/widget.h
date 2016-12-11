#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QLabel>
#include <QtNetwork>
#include <QTextCodec>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QStringList>
#include <QMessageBox>
#include <QVariant>
#include "danmu.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

public:
    QLabel *mylabel[1000];
    QPropertyAnimation *qplab[1000];
    QNetworkAccessManager *manager;
    long long beginid;
    Danmu danmu[000];
    int curr;   //index of danmu curr
    int upindex;    //index of up
    int mytimerid;

private:
    Ui::Widget *ui;

public:
    void reloaddm();
    void displaydanmu();

protected:
    void timerEvent(QTimerEvent *event);

signals:
    void response(int len);
    void error(int errCode);

//private slots:
//    void replyFinished(QNetworkReply *);
//    void my_get(QString strUrl);
//    void my_post(QString strUrl);
};

#endif // WIDGET_H
