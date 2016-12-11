#ifndef DANMU_H
#define DANMU_H
#include<QString>
#include <QDateTime>
#include <QDate>
#include <QTime>

class Danmu
{
public:
    QString ToUserName;
    QString FromUserName;
    QString CreateTime;
    QString MsgType;
    QString Content;
    long long MsgId;
    int status;
    QDateTime savetime;


    Danmu()
    {
        ToUserName="unknown";
        FromUserName="unknown";
        CreateTime="unknown";
        MsgType="fail";
        Content="unknowndata";
        MsgId=-1;
        status=2;
    }

    Danmu(QString rToUser,QString rFrom,QString rCreate,QString rMsg,QString rCon,long long rMsgId,int rstatus,QDateTime rsavetime)
    {
        ToUserName=rToUser;
        FromUserName=rFrom;
        CreateTime=rCreate;
        MsgType=rMsg;
        Content=rCon;
        MsgId=rMsgId;
        status=rstatus;
        savetime=rsavetime;
    }
};

#endif // DANMU_H
