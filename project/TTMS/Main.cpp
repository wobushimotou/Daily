#include <iostream>
#include <mysql++/mysql++.h>
#include <mysql++/cmdline.h>
#include <mysql++/mystring.h>

#include <typeinfo>

using namespace std;
int main()
{
    mysqlpp::Connection conn(false);
    string db="TTMS";
    string server="localhost";
    string user="root";
    string passwd="123456";
    string result;
    if (conn.connect(db.c_str(), server.c_str(), user.c_str(), passwd.c_str())) {

        cout << "connect db succeed. " << endl;
        mysqlpp::Query query = conn.query("SELECT * FROM MovieData");
        if (mysqlpp::StoreQueryResult res = query.store()) {

            mysqlpp::StoreQueryResult::const_iterator it;
            for(it = res.begin();it != res.end();++it) {
                mysqlpp::Row row = *it;
                for(auto p = row.begin();p != row.end();++p) 
                    cout << '\t' << *p << endl;
            }
        }
    } else {
        cout << "connect db fail. " << endl;
    }


    return 0;
}

