#include <iostream>
#include <string.h>
#include "Client.h"
#include "GetParameter.h"
#include "DbOperation.h"

int main()
{
    UserData data1;
    bzero(&data1,sizeof(data1));
    memcpy(data1.userId,"1",8);
    memcpy(data1.userName,"wh",10);
    memcpy(data1.userPasswd,"wh",10);
    memcpy(data1.userMail,"1687734258@qq.com",20);
    data1.userType = '1';

    MovieData data2;
    bzero(&data2,sizeof(data2));
    memcpy(data2.movieId,"1",8);
    
    DbOperation<MovieData> db2;
    db2.Execute("insert into UserData values('3','mm','mm','1','123456@qq.com')");
    

    for(auto it = db2.vec.begin();it != db2.vec.end();++it)
        std::cout << *it << std::endl;
    return 0;
}

