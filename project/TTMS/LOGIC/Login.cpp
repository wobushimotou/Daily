#include <string>
#include "../DBOP/DbOperation.h"
#include "../DBOP/Client.h"
#include "../DBOP/GetParameter.h"
bool login(std::string userName,std::string userPasswd) {
    DbOperation<UserData> db;
    db.Execute("Select * from UserData where userName='"+userName+"' and userPasswd = '"+userPasswd+"';"); 
    if(db.vec.size() == 0) 
        return false;
    return true;
}

