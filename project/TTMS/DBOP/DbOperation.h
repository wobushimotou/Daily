#pragma once
#include <string>
#include "GetParameter.h"
#include <typeinfo>
#include <iostream>
#include <vector>
//#include <mysql++/mysql++.h>
#include <sstream>

using namespace std;
template <typename T>
class DbSent{
private:
    /*
    mysqlpp::Connection conn;
    //连接数据库
    int ConnectDb();
    */
public:
    /*
    vector<string> vec;

    
    //传入语句并执行，将结果存储在vec中
    //flag = 1表示查询操作,=0表示增删改操作
    void Execute(std::string SendEnce);

    DbOperation() {
        ConnectDb();

    }
    ~DbOperation() {}

    */
    //根据传入内容生成增删改查的语句
    std::string Insert(T &data);
    std::string Delete(T &data,long flag);
    //根据dataSet与flagSet设置要设置的内容,通过dataGet与flagGet查找要设置的内容
    std::string Update(T &dataSet,long flagSet,T &dataGet,long flagGet);
    //生成由dataFind与flagFind决定的结果,通过dataGet与flagGet查找
    std::string Select(T &dataFind,long flagFind,T &dataGet,long flagGet);

   
};
//根据传入参数的类型获取字符串表示的其类型
template <typename U>    
std::string GetType(U &data) {
    std::string type;
    type += typeid(data).name();
    for(auto it = type.begin();it != type.end();) {
        if(*it >= '0' && *it <= '9') {
        type.erase(it);
            continue;
        }
        ++it;
    }
    return type;
}

//根据传入数据的类型以及flag获取 'XX','XX' 的表达式
//sflag为1表明查询类型字段,0表明查询类型字段值
template <typename U>
std::string GetSentEnceComma(U &data,long flag,char sflag) {

    std::string sentEnce;
    if(flag & 00001)
        sentEnce += one(data,sflag);
    if(flag & 00002)
        sentEnce += ","+two(data,sflag);
    if(flag & 00004)
        sentEnce += ","+three(data,sflag);
    if(flag & 00010)
        sentEnce += ","+four(data,sflag);
    if(flag & 00020)
        sentEnce += ","+five(data,sflag);

    if((flag & 00040) && six(data,sflag) != "")
        sentEnce += ","+six(data,sflag);
    if((flag & 00100) && seven(data,sflag) != "")
        sentEnce += ","+seven(data,sflag);
    if((flag & 00200) && eight(data,sflag) != "")
        sentEnce += ","+eight(data,sflag);
    if((flag & 00400) && nine(data,sflag) != "")
        sentEnce += ","+nine(data,sflag);
    if((flag & 01000) && ten(data,sflag) != "")
        sentEnce += ","+ten(data,sflag);
    if((flag & 02000) && eleven(data,sflag) != "")
        sentEnce += ","+eleven(data,sflag);
    if((flag & 04000) && twelve(data,sflag) != "")
        sentEnce += ","+twelve(data,sflag);
    
    return sentEnce;
}

//根据传入数据的类型以及flag获取 XX='XX' 的表达式
template <typename U>
std::string GetSentEnceEqual(U &data,long flag) {
    std::string sentEnce;
    if(flag & 00001) {
        sentEnce += one(data,0)+"=";
        sentEnce += one(data,1);
    }
    if(flag & 00002) {
        sentEnce += two(data,0)+"=";
        sentEnce += two(data,1);
    }
    if(flag & 00004) {
        sentEnce += three(data,0)+"=";
        sentEnce += three(data,1);
    }

    if(flag & 00010) {
        sentEnce += four(data,0)+"=";
        sentEnce += four(data,1);
    }

    if(flag & 00020) {
        sentEnce += five(data,0)+"=";
        sentEnce += five(data,1);
    }

    if(flag & 00040) {
        sentEnce += six(data,0)+"=";
        sentEnce += six(data,1);
    }

    if(flag & 00100) {
        sentEnce += seven(data,0)+"=";
        sentEnce += seven(data,1);
    }
    if(flag & 00200) {
        sentEnce += eight(data,0)+"=";
        sentEnce += eight(data,1);
    }

    if(flag & 00400) {
        sentEnce += nine(data,0)+"=";
        sentEnce += nine(data,1);
    }

    if(flag & 01000) {
        sentEnce += ten(data,0)+"=";
        sentEnce += ten(data,1);
    }

    if(flag & 02000) {
        sentEnce += eleven(data,0)+"=";
        sentEnce += eleven(data,1);
    }

    if(flag & 04000) {
        sentEnce += twelve(data,0)+"=";
        sentEnce += twelve(data,1);
    }
    return sentEnce;

}

//根据数据生成插入数据语句
template <typename T>
std::string DbSent<T>::Insert(T &data) {
    //初始化语句
    std::string sentEnce;

    sentEnce += "INSERT INTO ";
    sentEnce += GetType(data);
    sentEnce += " VALUES(";
    sentEnce += GetSentEnceComma(data,07777,1)+");";
    return sentEnce;
}

//根据数据生成删除语句
template <typename T>
std::string DbSent<T>::Delete(T &data,long flag) {
    std::string sentEnce;
    sentEnce += "DELETE FROM ";
    sentEnce += GetType(data);   
    sentEnce += " WHERE ";
    sentEnce += GetSentEnceEqual(data,flag);
    sentEnce += ";";

    return sentEnce;
}

template <typename T>
std::string DbSent<T>::Update(T &dataSet,long flagSet,T &dataGet,long flagGet) {
    std::string sentEnce;
    sentEnce += "UPDATE ";
    sentEnce += GetType(dataSet);   
    sentEnce += " SET ";
    sentEnce +=GetSentEnceEqual(dataSet,flagSet);
    sentEnce += " WHERE ";
    sentEnce += GetSentEnceEqual(dataGet,flagGet);
    sentEnce += ";";

    return sentEnce;
}
template <typename T>
std::string DbSent<T>::Select(T &dataFind,long flagFind,T &dataGet,long flagGet) {
    std::string sentEnce;
    sentEnce += "SELECT ";
    sentEnce += GetSentEnceComma(dataFind,flagFind,0);
    sentEnce += " FROM ";
    sentEnce += GetType(dataFind);
    if(flagGet != 00000)
        sentEnce += " WHERE ";
    sentEnce += GetSentEnceEqual(dataGet,flagGet);
    sentEnce += ";";
    
    return sentEnce;
} 
/*
template <typename T>
int DbSent<T>::ConnectDb() {
    std::string db = "TTMS";
    std::string server = "localhost";
    std::string user = "root";
    std::string passwd = "123456";
    if(conn.connect(db.c_str(),server.c_str(),user.c_str(),passwd.c_str())) {
        std::cout << "连接数据库成功" << std::endl;
        return 1;
    }
    return 0;
}
*/
/*
template <typename T>
void DbOperation<T>::Execute(std::string SendEnce) {
    mysqlpp::Query query = conn.query(SendEnce.c_str());
    string Result;    
    stringstream s;
    string temp;

    mysqlpp::StoreQueryResult res;
    res = query.store();
    

    if (res) {
        auto it = res.begin();
        for(;it != res.end();++it) {
            mysqlpp::Row row = *it;
            
            for(size_t i = 0;i != row.size();++i) {
                s << row[i] << " ";
                s >> temp;
                Result += temp;
                Result += " ";
            }
            s << endl;
            Result += "\n";
            vec.push_back(Result);
        }
    }
}
*/





