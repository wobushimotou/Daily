#include <QString>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <iostream>
#include <dboper.h>
#include <QDateTime>
Dboper::Dboper() {
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("TTMS");       //这里输入你的数据库名
    db.setUserName("root");
    db.setPassword("123456");   //这里输入你的密码

    if(db.open()) {
        qDebug() << "open";
    }

}
Dboper::~Dboper() {
    db.close();

    qDebug() << "close";
}
int Dboper::UserLogin(QString userName,QString userPasswd) {
    QSqlQuery query(db);
    QString sentence = "select * from UserData where UserName='"+userName+"' and UserPasswd='"+userPasswd+"'";
    query.exec(sentence);
    if(query.next()) {
        std::cout << "存在" << std::endl;
        return query.value(3).toInt();
    }

    return 0;
}
bool Dboper::UserRegister(QString userName,QString userPasswd,QString userMail) {

    QSqlQuery query(db);
    QString sentence = "select * from UserData where UserName='"+userName+"' and UserPasswd='"+userPasswd+"'";
    qDebug() << sentence;
    query.exec(sentence);
    if(query.next()) {
        std::cout << "存在" << std::endl;  
        return false;
    }

    if(AddUser(userName,userPasswd,userMail,3)) {
        return true;
    }

    return false;
}

bool Dboper::AddUser(QString Name,QString Passwd,QString Mail,int type) {
    //用户表中有此用户数据
    if(SelectUser(Name).userId != 0)
        return false;
    QSqlQuery query(db);


    QString sentence = "insert into UserData values(null,'"+Name+"','"+Passwd+"',"+QString::number(type)+",'"+Mail+"')";

    qDebug() << sentence;


    query.exec(sentence);
    if(query.isValid()) {
        return false;
    }
    return true;
}

UserData Dboper::SelectUser(QString Name) {
    QSqlQuery query(db);
    UserData result;
    QString sentence = "select * from UserData where userName='"+Name+"'";

    query.exec(sentence);
    qDebug() << sentence;
    if(query.next()) {
        result.userId = query.value(0).toInt();
        result.userName = query.value(1).toString();
        result.userPasswd = query.value(2).toString();
        result.userType = query.value(3).toInt();
        result.userMail = query.value(4).toString();
    }

    return result;
}

bool Dboper::DeleteUser(QString Name) {
    //用户表中无此用户数据
    if(SelectUser(Name).userId == 0)
        return false;
    QSqlQuery query(db);
    QString sentence = "delete from UserData where userName='"+Name+"'";
    qDebug() << sentence;

    query.exec(sentence);
    if(query.isValid()) {
        return false;
    }
    return true;
}

bool Dboper::UpdateUser(QString Name,QString Passwd,QString Mail) {
    //用户表中无此用户数据
    if(SelectUser(Name).userId == 0)
        return false;
    QSqlQuery query(db);
    QString sentence = "update UserData set userPasswd = '"+Passwd+"',userMail = '"+Mail+"' where userName='"+Name+"'";
    qDebug() << sentence;

    query.exec(sentence);
    if(query.isValid()) {
        return false;
    }
    return true;
}

bool Dboper::AddRoom(QString Name,int row,int col) {
    //用户表中有此用户数据
    QString result;
    if(SelectRoom(Name).roomId != 0)
        return false;

    QString sit(row*col,'0');
    QSqlQuery query(db);
    query.exec("select MAX(roomId)+1 from RoomData");
    if(query.next())
        result = query.value(0).toString();
    QString sentence = "insert into RoomData values('"+result+"','"+Name+"',"+QString::number(row)+","+QString::number(col)+",'"+sit+"')";
    qDebug() << sentence;

    query.exec(sentence);
    if(query.isValid()) {
        return false;
    }
    return true;
}
bool Dboper::DeleteRoom(QString Name) {
    //演出厅表表中无此数据
        if(SelectRoom(Name).roomId == 0)
            return false;
        QSqlQuery query(db);
        QString sentence = "delete from RoomData where roomName='"+Name+"'";
        qDebug() << sentence;

        query.exec(sentence);
        if(query.isValid()) {
            return false;
        }
        return true;
}
RoomData Dboper::SelectRoom(QString Name) {
    QSqlQuery query(db);
    RoomData result;
    QString sentence = "select * from RoomData where roomName='"+Name+"'";

    query.exec(sentence);
    if(query.next()) {
        result.roomId = query.value(0).toInt();
        result.roomName = query.value(1).toString();
        result.rows = query.value(2).toInt();
        result.cols = query.value(3).toInt();
        result.distrbute = query.value(4).toString();
    }
    return result;
}

RoomData Dboper::SelectRoom(int RoomId) {
    QSqlQuery query(db);
    RoomData result;
    QString sentence = "select * from RoomData where roomId='"+QString::number(RoomId)+"'";

    query.exec(sentence);
    if(query.next()) {
        result.roomId = query.value(0).toInt();
        result.roomName = query.value(1).toString();
        result.rows = query.value(2).toInt();
        result.cols = query.value(3).toInt();
        result.distrbute = query.value(4).toString();
    }
    return result;
}
bool Dboper::UpdateRoom(QString Name,int row,int col) {
    //演出厅表中无此数据

    if(SelectRoom(Name).roomId == 0)
        return false;

    QSqlQuery query(db);
    QString sentence = "update RoomData set rows = "+QString::number(row)+",cols = "+QString::number(col)+" where roomName ='"+Name+"'";
    qDebug() << sentence;

    query.exec(sentence);
    if(query.isValid()) {
        return false;
    }
    return true;
}

bool Dboper::AddMovie(MovieData &data) {
    //电影表中有此数据
    //用户表中有此用户数据
    QString result;
    if(SelectMovie(data.title).movieId != 0)
        return false;

    QSqlQuery query(db);
    query.exec("select MAX(movieId)+1 from MovieData");
    if(query.next())
        result = query.value(0).toString();
    QString sentence = "insert into MovieData values('"+result+"','"+QString::number(data.rating)+"','"+data.genres+"','"+ \
            QString::number(data.runTime)+"','"+data.title+"','"+data.poster+"','"+data.directors+"','"+data.actors+"','"+ \
            data.plotSimple+"','"+data.country+"')";

    qDebug() << sentence;

    query.exec(sentence);
    if(query.isValid()) {
        return false;
    }
    return true;
}

MovieData Dboper::SelectMovie(QString Name) {
    QSqlQuery query(db);
    MovieData result;
    QString sentence = "select * from MovieData where title='"+Name+"'";

    query.exec(sentence);
    if(query.next()) {
        result.movieId = query.value(0).toInt();
        result.title = query.value(4).toString();
        result.rating = query.value(1).toDouble();
        result.genres = query.value(2).toString();
        result.runTime = query.value(3).toInt();
        result.poster = query.value(5).toString();
        result.directors = query.value(6).toString();
        result.actors = query.value(7).toString();
        result.plotSimple = query.value(8).toString();
        result.country = query.value(9).toString();
    }

    return result;
}

MovieData Dboper::SelectMovie(int movieId) {
    QSqlQuery query(db);
    MovieData result;
    QString sentence = "select * from MovieData where movieId='"+QString::number(movieId)+"'";

    query.exec(sentence);
    if(query.next()) {
        result.movieId = query.value(0).toInt();
        result.title = query.value(4).toString();
        result.rating = query.value(1).toDouble();
        result.genres = query.value(2).toString();
        result.runTime = query.value(3).toInt();
        result.poster = query.value(5).toString();
        result.directors = query.value(6).toString();
        result.actors = query.value(7).toString();
        result.plotSimple = query.value(8).toString();
        result.country = query.value(9).toString();
    }

    return result;
}

bool Dboper::DeleteMovie(QString Name) {
    //电影表中无此数据
        if(SelectMovie(Name).movieId == 0)
            return false;
        QSqlQuery query(db);
        QString sentence = "delete from MovieData where title='"+Name+"'";
        qDebug() << sentence;

        query.exec(sentence);
        if(query.isValid()) {
            return false;
        }
        return true;
}

bool Dboper::UpdateMovie(MovieData &data) {
    //电影表中无此数据
    if(SelectMovie(data.title).movieId == 0)
        return false;

    QSqlQuery query(db);

    QString sentence = "update MovieData set rating="+QString::number(data.rating) \
            +",genres='"+data.genres+"',runTime="+QString::number(data.runTime)+",poster='"+data.poster+"',directors='"+data.directors \
            +"',actors='"+data.actors+"',plotSimple='"+data.plotSimple+"',country='"+data.country+"' where title='"+data.title+"'";
    qDebug() << sentence;

    query.exec(sentence);
    if(query.isValid()) {
        return false;
    }
    return true;
}

bool Dboper::AddSche(ScheduleData &data) {
    //演出计划中无此数据
    if(SelectSche(data.scheduleId).scheduleId != 0)
        return false;
    QString result;
    QSqlQuery query(db);
    query.exec("select MAX(scheduleId)+1 from ScheduleData");
    if(query.next())
        result = query.value(0).toString();
    if(result == "0")
        result = "1";
    QString sentence = "insert into ScheduleData values('"+result+"','"+QString::number(data.movieId)+"','"+QString::number(data.roomId)\
            +"','"+data.beginTime+"','"+data.endTime+"',"+QString::number(data.price)+")";


    qDebug() << sentence;

    query.exec(sentence);
    if(query.isValid()) {
        return false;
    }
    return true;
}

ScheduleData Dboper::SelectSche(QString roomName,QDateTime Start) {
    QSqlQuery query(db);
    ScheduleData result;
    int roomId = SelectRoom(roomName).roomId;
    QString sentence = "select * from ScheduleData where roomId='"+QString::number(roomId)+"' and beginTime='"+Start.toString("yyyy-MM-dd hh:mm:ss")+"'";
    qDebug() << sentence;
    query.exec(sentence);
    if(query.next()) {
        result.scheduleId = query.value(0).toInt();
        result.movieId  = query.value(1).toInt();
        result.roomId = query.value(2).toInt();
        result.beginTime = query.value(2).toString();
        result.endTime = query.value(3).toString();
    }
    return result;
}

ScheduleData Dboper::SelectSche(int ScheduleId) {
    QSqlQuery query(db);
    ScheduleData result;

    QString sentence = "select * from ScheduleData where scheduleId='"+QString::number(ScheduleId)+"'";
    qDebug() << sentence;
    query.exec(sentence);
    if(query.next()) {
        result.scheduleId = query.value(0).toInt();
        result.movieId  = query.value(1).toInt();
        result.roomId = query.value(2).toInt();
        result.beginTime = query.value(2).toString();
        result.endTime = query.value(3).toString();
    }
    return result;
}

ScheduleData Dboper::SelectSche(QString movieName) {
    QSqlQuery query(db);
    ScheduleData result;
    int movieId = SelectMovie(movieName).movieId;
    QString sentence = "select * from ScheduleData where movieId='"+QString::number(movieId)+"'";
    qDebug() << sentence;
    query.exec(sentence);
    if(query.next()) {
        result.scheduleId = query.value(0).toInt();
        result.movieId  = query.value(1).toInt();
        result.roomId = query.value(2).toInt();

        result.beginTime = query.value(3).toString();
        result.beginTime[10] = ' ';
        result.endTime = query.value(4).toString();
        result.endTime[10] = ' ';
         result.price = query.value(5).toInt();
    }

    return result;
}


bool Dboper::DeleteSche(QString roomName,QDateTime Start) {
    //电影表中无此数据
        int ScheduleId;
        if((ScheduleId = SelectSche(roomName,Start).scheduleId) == 0)
            return false;
        QSqlQuery query(db);
        QString sentence = "delete from ScheduleData where scheduleId='"+QString::number(ScheduleId)+"'";
        qDebug() << sentence;

        query.exec(sentence);
        if(query.isValid()) {
            return false;
        }
        return true;
}

bool Dboper::UpdateSche(ScheduleData &data) {
    //演出计划表中无此数据
    if((data.scheduleId = SelectSche(SelectMovie(data.movieId).title).scheduleId) == 0)
        return false;

    QSqlQuery query(db);
    QString sentence = "update ScheduleData set movieId='"+QString::number(data.movieId)+"',roomId="+QString::number(data.roomId)+" price="+QString::number(data.price)+",beginTime='"+data.beginTime\
            +"',endTime='"+data.endTime+"' where scheduleId = '"+QString::number(data.scheduleId)+"'";

    qDebug() << sentence;
    query.exec(sentence);
    if(query.isValid()) {
        return false;
    }
    return true;
}
