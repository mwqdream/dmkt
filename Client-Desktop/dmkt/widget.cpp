#include "widget.h"
#include "ui_widget.h"
#include <QPropertyAnimation>


Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);


//    //http-get
//    manager=new QNetworkAccessManager(this);
//    connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(replyFinished(QNetworkReply *)));
//    this->my_get("http://101.200.49.207/replypc.php/s?danmu=3");
//    this->my_get("http://101.200.49.207/replypc.php/s?danmu=4");
//    this->my_get("http://101.200.49.207/replypc.php/s?danmu=5");

//    this->my_post("http://101.200.49.207/replypc.php");
//    this->my_post("http://101.200.49.207/replypc.php");

    curr=0;
    upindex=0;
    //Mysql
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL","conn1");
    db.setHostName("101.200.49.207");
    db.setPort(3306);
    db.setDatabaseName("danmu");
    db.setUserName("mwqdanmu");
    db.setPassword("danmu666");
    bool ok=db.open();
    qDebug()<<ok;

    if(!ok)
    {
        QMessageBox::critical(0,"Cannot open database","Unable to establish a database connection.",QMessageBox::Cancel);
    }
    else
    {
        QSqlQuery query(db);
        //get the max MsgId from danmu
        query.exec("select MsgId from danmu order by MsgId desc limit 1");

        while(query.next())
        {
            beginid=query.value(5).toLongLong();
            qDebug()<<query.value(5).toLongLong();
        }
        query.exec("update danmu set status=2 where status=1 and MsgId<="+QString::number(beginid));
    }

    ui->label->adjustSize();
    ui->label_2->adjustSize();
    ui->label_3->adjustSize();
    QPropertyAnimation *qplab1 = new QPropertyAnimation(ui->label,"pos");
    qplab1->setDuration(4000);
    int hyin=qrand()%50;
    qplab1->setStartValue(QPoint(1600,hyin*10+10));
    qplab1->setEndValue(QPoint(-700,hyin*10+10));
    qplab1->start();

    QPropertyAnimation *qplab2 = new QPropertyAnimation(ui->label_2,"pos");
    qplab2->setDuration(4000);
    hyin=qrand()%50;
    qplab2->setStartValue(QPoint(1700,hyin*10+10));
    qplab2->setEndValue(QPoint(-500,hyin*10+10));
    qplab2->start();

    QPropertyAnimation *qplab3 = new QPropertyAnimation(ui->label_3,"pos");
    qplab3->setDuration(4000);
    hyin=qrand()%80;
    qplab3->setStartValue(QPoint(1800,hyin*10+10));
    qplab3->setEndValue(QPoint(-400,hyin*10+10));
    qplab3->start();

    //4s refresh
    mytimerid=startTimer(4000);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::timerEvent(QTimerEvent *event)
{
    if(event->timerId()==mytimerid)
    {
        reloaddm();
        displaydanmu();
    }
    else
    {
        QWidget::timerEvent(event);
    }
}

void Widget::reloaddm()
{
    curr=0;
    upindex=0;
    query.exec("select * from danmu where status=1 and MsgId>"+QString::number(beginid));
    while(query.next())
    {
        qDebug()<<query.value(0).toString()<<" "<<query.value(1).toString()<<" "<<query.value(2).toLongLong();
        QString rToUser=query.value(0).toString();
        QString rFrom=query.value(1).toString();
        QString rCreate=query.value(2).toLongLong();
        QString rMsg=query.value(3).toString();
        QString rCon=query.value(4).toString();
        long long rMsgId=query.value(5).toLongLong();
        int rstatus=1;
        QDateTime rsavetime=query.value(7).toDateTime();
        if(upindex<1000)
        {
            danmu[upindex]=Danmu(rToUser,rFrom,rCreate,rMsg,rCon,rMsg,rCon,rMsgId,rstatus,rsavetime);
            upindex++;
            if(rMsgId>beginid)
            {
                //refresh
                beginid=rMsgId;
            }
        }
        else
        {
            return;
        }
    }
}

void Widget::displaydanmu()
{
    int base=curr;
    for(;curr<upindex;curr++)
    {
        //label move show

        int t=qrand()%100;
        mylabel[curr]=new QLabel("test danmu",this);
        mylabel[curr]->setText("<html><head/><body><p><span style=\" font-size:30pt; color:#2835aa;\">"+danmu[curr].Content+"</span></p></body></html>");
        mylabel[curr]->setGeometry(1800,300,200,20);
        mylabel[curr]->setVisible(1);
        mylabel[curr]->adjustSize();


        qplab[curr] = new QPropertyAnimation(mylabel[curr],"pos");
        qplab[curr]->setDuration(9000);
        int yin=qrand()%80;
        qplab[curr]->setStartValue(QPoint(1600+(curr-base)*30,yin*10));
        qplab[curr]->setEndValue(QPoint(-1000+(curr-base)*30,yin*10));
        qplab[curr]->start();
    }
}

//void Widget::replyFinished(QNetworkReply *reply)
//{

//    //status code of the request
//    QVariant status_code=reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);

//    QTextCodec *codec=QTextCodec::codecForName("UTF-8");
//    QString all=codec->toUnicode(reply->readAll());

//    reply->deleteLater();
//}

//void Widget::my_get(QString strUrl)
//{
//    QNetworkRequest request;
//    request.setUrl(QUrl(strUrl));

//    manager->get(request);
//}

//void Widget::my_post(QString strUrl)
//{
//    QNetworkRequest request;
//    request.setUrl(QUrl(strUrl));
//    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

//    QByteArray postdata=QByteArray("getdanmu=10");
//    postdata.append("&hello=world");
//    request.setHeader(QNetworkRequest::ContentLengthHeader,postdata.length());

//    manager->post(request,postdata);
//}
