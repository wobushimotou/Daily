#ifndef LOGIC_H
#define LOGIC_H
#include <QString>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <iostream>
#include <QVector>
#include "../DBOP/Client.h"
#include "../DBOP/DbOperation.h"
class Dboper {
public:
    Dboper();
    ~Dboper();
    int UserLogin(QString userName,QString userPasswd);
    bool UserRegister(QString userName,QString userPasswd,QString userMail);

    bool AddUser(QString Name,QString Passwd,QString Mail,int type);
    UserData SelectUser(QString Name);
    bool DeleteUser(QString Name);
    bool UpdateUser(QString Name,QString Passwd,QString Mail);

    bool AddRoom(QString Name,int row,int col);
    bool DeleteRoom(QString Name);
    RoomData SelectRoom(QString Name);
    RoomData SelectRoom(int RoomId);
    bool UpdateRoom(QString Name,int row,int col);

    bool AddMovie(MovieData &data);
    MovieData SelectMovie(QString Name);
    MovieData SelectMovie(int movieId);
    bool DeleteMovie(QString Name);
    bool UpdateMovie(MovieData &data);

    bool AddSche(ScheduleData &data);
    ScheduleData SelectSche(QString roomName,QDateTime Start);
    ScheduleData SelectSche(QString movieName);
    ScheduleData SelectSche(int ScheduleId);

    bool DeleteSche(QString roomName,QDateTime Start);
    bool UpdateSche(ScheduleData &data);
private:
    QSqlDatabase db;
};


#endif // LOGIC_H
