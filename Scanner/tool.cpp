#include <iostream>
#include <fstream>

using namespace std;
int main()
{
    fstream file("keywords.md");
    fstream file2("kwords.md",ios::out);
    char ch = '1';
    string s;
    int l = -1;
    while(file.read(&ch,1)) {
        if(ch == '1') {
            ch = l+'0';
        }
        s.push_back(ch);
        if(ch == '\n') {
            int p = s.find("：",0);
            if(p != -1) {
                string s1 = s.substr(0,p); 
                string s2 = s.substr(p+1,s.size());
                s = s1+" | " + to_string(l) +" | "+ s2;
            }

            file2 << s;
            l++;
            s = "";
        }
    }
    file.close();
    file2.close();
    return 0;
}

