#pragma once
#include <string>
#include "Client.h"
#include "DbOperation.h"
class GetParameter
{
public:
    GetParameter() {}
    ~GetParameter() {}

private:

};

typedef union data{
    UserData Ud;
    MovieData Md;
    ScheduleData Sd;
    RoomData Rd;
    TicketData Td;
}Data;

template <typename T> std::string one(T &data,char flag);
template <typename T> std::string two(T &data,char flag);
template <typename T> std::string three(T &data,char flag);
template <typename T> std::string four(T &data,char flag);
template <typename T> std::string five(T &data,char flag);
template <typename T> std::string six(T &data,char flag);
template <typename T> std::string seven(T &data,char flag);
template <typename T> std::string eight(T &data,char flag);
template <typename T> std::string nine(T &data,char flag);
template <typename T> std::string ten(T &data,char flag);
template <typename T> std::string eleven(T &data,char flag);
template <typename T> std::string twelve(T &data,char flag);

template <typename T>
std::string one(T &data,char flag) {

    Data temp;
    memcpy(&temp,&data,sizeof(data));
    switch(sizeof(data)) {
    case sizeof(UserData):
        if(flag)
            return "'"+std::string(temp.Ud.userId)+"'";
        else
            return "userId";
    case sizeof(MovieData):
        if(flag)
            return "'"+std::string(temp.Md.movieId)+"'";
        else
            return "movieId";
    case sizeof(RoomData):
        if(flag)
            return "'"+std::string(temp.Rd.roomId)+"'";
        else
            return "roomId";
    case sizeof(ScheduleData):
        if(flag)
            return "'"+std::string(temp.Sd.scheduleId)+"'";
        else
            return "scheduleId";
    case sizeof(TicketData):
        if(flag)
            return "'"+std::string(temp.Td.ticketId)+"'";
        else
            return "ticketId";
    }
}

template <typename T>
std::string two(T &data,char flag) {
    Data temp;
    memcpy(&temp,&data,sizeof(data));
    switch(sizeof(data)) {
    case sizeof(UserData):
        if(flag)
            return "'"+std::string(temp.Ud.userName)+"'";
        else
            return "userName";
    case sizeof(MovieData):
        if(flag)
            return "'"+std::string(temp.Md.title)+"'";
        else
            return "title";
    case sizeof(RoomData):
        if(flag)
            return "'"+std::string(temp.Rd.roomName)+"'";
        else
            return "roomName";
    case sizeof(ScheduleData):
        if(flag)
            return "'"+std::string(temp.Sd.movieId)+"'";
        else
            return "movieId";
    case sizeof(TicketData):
        if(flag)
            return "'"+std::string(temp.Td.roomId)+"'";
        else
            return "roomId";
    }
}

template <typename T>
std::string three(T &data,char flag) {
    Data temp;
    memcpy(&temp,&data,sizeof(data));
    switch(sizeof(data)) {
    case sizeof(UserData):
        if(flag)
            return "'"+std::string(temp.Ud.userPasswd)+"'";
        else
            return "userPasswd";
    case sizeof(MovieData):
        if(flag)
            return "'"+std::to_string(temp.Md.rating)+"'";
        else
            return "rating";
    case sizeof(RoomData):
        if(flag)
            return "'"+std::to_string(temp.Rd.rows)+"'";
        else
            return "rows";
    case sizeof(ScheduleData):
        if(flag)
            return "'"+std::string(temp.Sd.roomId)+"'";
        else
            return "roomId";
    case sizeof(TicketData):
        if(flag)
            return "'"+std::string(temp.Td.scheduleId)+"'";
        else
            return "scheduleId";
    }
}

template <typename T>
std::string four(T &data,char flag) {
    Data temp;
    memcpy(&temp,&data,sizeof(data));
    switch(sizeof(data)) {
    case sizeof(UserData):
        if(flag)
            return "'"+std::to_string(temp.Ud.userType)+"'";
        else
            return "userType";
    case sizeof(MovieData):
        if(flag)
            return "'"+std::string(temp.Md.genres)+"'";
        else
            return "genres";
    case sizeof(RoomData):
        if(flag)
            return "'"+std::to_string(temp.Rd.cols)+"'";
        else
            return "cols";
    case sizeof(ScheduleData):
        if(flag)
            return "'"+std::string(temp.Sd.beginTime)+"'";
        else
            return "beginTime";
    case sizeof(TicketData):
        if(flag)
            return "'"+std::to_string(temp.Td.row)+"'";
        else
            return "row";
    }
}

template <typename T>
std::string five(T &data,char flag) {
    Data temp;
    memcpy(&temp,&data,sizeof(data));
    switch(sizeof(data)) {
    case sizeof(UserData):
        if(flag)
            return "'"+std::string(temp.Ud.userMail)+"'";
        else
            return "userMail";
    case sizeof(MovieData):
        if(flag)
            return "'"+std::to_string(temp.Md.runTime)+"'";
        else
            return "runTime";
    case sizeof(RoomData):
        if(flag)
            return "'"+std::string(temp.Rd.distrbute)+"'";
        else
            return "distrbute";
    case sizeof(ScheduleData):
        if(flag)
            return "'"+std::string(temp.Sd.endTime)+"'";
        else
            return "endTime";
    case sizeof(TicketData):
        if(flag)
            return "'"+std::to_string(temp.Td.col)+"'";
        else
            return "col";
    }
}

template <typename T>
std::string six(T &data,char flag) {
    Data temp;
    memcpy(&temp,&data,sizeof(data));
    if(sizeof(data) == sizeof(MovieData)) {
        if(flag)
            return "'"+std::string(temp.Md.poster)+"'";
        else
            return "poster";
    }
    return "";
}

template <typename T>
std::string seven(T &data,char flag) {
    /*
    Data temp;
    memcpy(&temp,&data,sizeof(data));
    if(sizeof(data) == sizeof(MovieData)) {
        if(flag)
            return "'"+std::string(temp.Md.writers)+"'";
        else
            return "writers";
    }
    */
    return "";
}

template <typename T>
std::string eight(T &data,char flag) {
    Data temp;
    memcpy(&temp,&data,sizeof(data));
    if(sizeof(data) == sizeof(MovieData)) {
        if(flag)
            return "'"+std::string(temp.Md.directors)+"'";
        else
            return "directors";
    }
    return "";
}

template <typename T>
std::string nine(T &data,char flag) {
    Data temp;
    memcpy(&temp,&data,sizeof(data));
    if(sizeof(data) == sizeof(MovieData)) {
        if(flag)
            return "'"+std::string(temp.Md.actors)+"'";
        else
            return "actors";
    }
    return "";
}

template <typename T>
std::string ten(T &data,char flag) {
    Data temp;
    memcpy(&temp,&data,sizeof(data));
    if(sizeof(data) == sizeof(MovieData)) {
        if(flag)
            return "'"+std::string(temp.Md.plotSimple)+"'";
        else
            return "plotSimple";
    }
    return "";
}

template <typename T>
std::string eleven(T &data,char flag) {
    Data temp;
    memcpy(&temp,&data,sizeof(data));
    if(sizeof(data) == sizeof(MovieData)) {
        if(flag)
            return "'"+std::string(temp.Md.country)+"'";
        else
            return "country";
    }
    return "";
}

template <typename T>
std::string twelve(T &data,char flag) {
    /*
    Data temp;
    memcpy(&temp,&data,sizeof(data));
    if(sizeof(data) == sizeof(MovieData)) {
        if(flag)
            return "'"+std::string(temp.Md.alsoKnownAs)+"'";
        else
            return "alsoKnownAs";
    }
    */
    return "";
}

