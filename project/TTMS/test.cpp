#include <iostream>
#include <string>
#include <mysql++/mysql++.h>

using namespace std;

int main(int argc, char *argv[])
{
    // Get database access parameters from command line
    string db="TTMS";
    string server="localhost";
    string user="root";
    string passwd="123456";

    // Connect to the sample database.
    mysqlpp::Connection conn(false);

    if (conn.connect(db.c_str(), server.c_str(), user.c_str(), passwd.c_str())) {
        // Retrieve a subset of the sample stock table set up by resetdb
        // and display it.
        cout << "连接成功" << endl;
        conn.query("SET NAMES UTF8");

        mysqlpp::Query query = conn.query("select * from UserData");
        
        if (mysqlpp::StoreQueryResult res = query.store()) {
            cout << "We have:" << endl;
            mysqlpp::StoreQueryResult::const_iterator it;

            for (it = res.begin(); it != res.end(); ++it) {
                mysqlpp::Row row = *it;

                for(size_t i = 0;i != row.size();++i) {
                    cout << '\t' << row[i];
                }
                cout << endl;
            }
        }
        else {
            cerr << "Failed to get item list: " << query.error() << endl;
            return 1;
        }
       return 0;
    }
    else {
        cerr << "DB connection failed: " << conn.error() << endl;
        return 1;
    }
}
