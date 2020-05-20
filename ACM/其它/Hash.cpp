#include <iostream>
#include <vector>
#include <map>
#include <mutex>
#include <thread>
#include <sstream>
using namespace std;

class Hash{
private:
    map<string,string> imap;
    mutex w;

public:
    Hash() {  }
    void Set(const string &key,const string &value) {
        w.lock();
            imap[key] = value;

        w.unlock();
    }

    string get(const string &key) {
        string s;
        w.lock();
            auto p = imap.find(key);
            if(p != imap.end())
                s = p->second;
            else
                s = "none";
        w.unlock();
        return s;
    }

};
void work(vector<string> vec,Hash &_hash,int s,int e) {

    /* for(auto p = vec.begin()+s;p != vec.begin()+e;++p) { */
    /*     string s = *p; */
    /*     if(s[0] == 's') { */
    /*         stringstream ss(s); */ 
    /*         string key; */
    /*         string value; */
    /*         ss >> key; */
    /*         ss >> key; */
    /*         ss >> value; */
    /*         _hash.Set(key,value); */
    /*     } */
    /*     else { */
    /*         stringstream ss(s); */ 
    /*         string key; */
    /*         ss >> key; */
    /*         ss >> key; */
    /*         cout << _hash.get(key) << endl; */
    /*     } */
    /* } */

}

int main()
{
    int t_num;
    cin >> t_num;
    

    vector<string> vec;
    Hash _hash;


    string s;

    while(cin >> s) {
        vec.push_back(s);
    }

    int task = vec.size()/t_num;

    for(int i = 0;i != t_num;) {
        if(i != t_num-1) {

            thread t(work,std::ref(vec),std::ref(_hash),i,i+task);
            t.detach();
        }
        else {

            thread t(work,std::ref(vec),std::ref(_hash),i,vec.size());
            t.detach();
        }

        
        i = i+task;
    }
    return 0;










}

