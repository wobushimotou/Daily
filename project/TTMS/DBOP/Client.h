#pragma once
#include <iostream>
#include <QString>
#include <QString>
using namespace std;

//用户数据
struct UserData{

    int userId = 0;
    QString userName;
    QString userPasswd;
    int userType;      //0 管理员 1 经理 2　用户
    QString userMail;
    QString to_string() {
        return QString::number(userId)+" "+userName+" "+userPasswd \
                +" "+QString::number(userType)+" "+userMail;
    }
};

//影片数据
struct MovieData{

    int movieId = 0;
    QString title; //电影名
    double rating;
    QString genres;//类型
    int runTime;
    QString poster;    //图片链接
    QString directors; //导演
    QString actors;    //主演
    QString plotSimple;    //简介
    QString country;   //国家

};

//放映厅数据
struct RoomData{

    int roomId = 0;
    QString roomName;
    int rows;
    int cols;
    QString distrbute;//座位分布
    QString to_string() {
        return QString::number(roomId)+" "+roomName+" "+QString::number(rows)+" "+QString::number(cols) \
                +" "+distrbute;
    }

};

//演出计划数据
struct ScheduleData{

    int scheduleId = 0;
    int movieId;
    int roomId;
    int price;
    QString beginTime;
    QString endTime;
};

//电影票数据
struct TicketData{

    int ticketId = 0;
    int roomId;
    int scheduleId;
    int row;
    int col;
    int price;
    int status;
    int userId;
};

