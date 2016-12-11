use ost;

create table danmu(
  ToUserName varchar(255),
  FromUserName varchar(255),
  CreateTime bigint,
  MsgType char(50),
  Content text,
  MsgId bigint,
  status int,
  savetime datetime,
  timelabel timestamp
);


--insert into danmu values('hello','hello',15167,'text','hello world',164654435555,5,now(),now());

--select * from danmu;

--update danmu set status=2 where MsgId=65848646;

/*
  About time:
    mysql 内置函数：
      now()返回YYYY-MM-DD:HH:MM:SS即当前时间-->datetime
      curdate()返回YYYY-MM-DD格式的日期-->date
      curtime()返回HH:MM:SS格式的时间-->teim
      eg:insert into tablename(crytime) values(now())

    在php中向数据库写入时间:
      $timeoffset=8;
      $savetime=date("Y-m-d H:i:s",time()+$timeoffset*3600);
      $insert_time="insert into danmu(savetime) values($time)";


*/
