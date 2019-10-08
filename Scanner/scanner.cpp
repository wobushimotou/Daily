#include <iostream>
#include <algorithm>
#include <fstream>
#include <map>

using namespace std;
class Judge{
public:
    Judge();
    bool IsDigit(char ch);
    bool IsLetter(char ch);
    bool IsSign(char ch);
    bool IsKey(string s);
    bool IsSpace(char ch) {
        return ch == ' ';
    }

    int get_num(string s);
    int to_num(string s);
    std::map<char,int> signs;
    std::map<std::string,int> keys;
};

class Scan{
public:
    Scan(string s) : filename(s) { jd = new Judge(); } 
    void Scanner();
    void Display();
private:
    void PreTreatMent();
    map<string,int> values;
    string filename;
    Judge *jd;
};

void Scan::PreTreatMent() {
    //预处理
    fstream file(filename);
    fstream file_i(filename.substr(0,filename.find(".",0))+".i",ios::out);
    char ch;
    char last;
    //滤掉换行以及注释,减少空格
    while(file.read(&ch,1)) {
        if(ch == '"') {
            file_i << ch;
            while(file.read(&ch,1)) {
                file_i << ch;
                if(ch == '"')
                    break;
            }
        }
        else if(ch == '/') {
            file >> ch;
            if(ch == '*') {
                while(file >> ch) {
                    if(ch == '*') {
                        file >> ch;
                        if(ch == '/')
                            break;
                    }
                }
            }
            continue;
        }
        else if(ch == '\n')
            continue;
        else if(ch == ' ') {
            while(file.read(&ch,1)) {
                if(ch != ' ')
                    break;
            }
            if(!jd->IsSign(last)) {
                file_i << " ";
            }
        }
        
        file_i << ch;
        last = ch;
    } 
    file.close();
    file_i.close();
}

void Scan::Scanner() {
    //预处理
    PreTreatMent();
}

Judge::Judge() {
    //初始化，将所有符号和关键字读入对应的结构中
    fstream file_sign("signwords.md"); 
    char temp[100];
    string s;
    while(file_sign.getline(temp,100)) {
        s = temp;
        int n = get_num(s);
        if(n != -1)
            signs[s[0]] = n;
     } 

    //读关键字表
    fstream file_key("kwords.md");
    string letter;
    for(char i = 65;i <= 122;++i) {
        if(IsLetter(i))
            letter.push_back(i);
    }

    while(file_key.getline(temp,100)) {
        s = temp; 
        int n = get_num(s);
        if(n != -1) {
            int it = s.find_first_not_of(letter,0);
            keys[s.substr(0,it)] = n;
        }
    }
}

int Judge::get_num(string s) {
    int it = s.find_first_of("0123456789",0);
    int its = s.find_first_not_of("0123456789",it);
    
    if(it != -1 && its != -1 && its >= it)
        return to_num(s.substr(it,its-it));
    return -1;
}

int Judge::to_num(string s) {
    int sum = 0;
    for(auto p = s.begin();p != s.end();++p)
        sum = sum*10 + *p - '0';
    return sum;
}
bool Judge::IsDigit(char ch) {
    return (ch >= '0' && ch <= '9');
}

bool Judge::IsLetter(char ch) {
    return ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'));
}

bool Judge::IsSign(char ch) {
    auto p = signs.find(ch);
    return !(p == signs.end());
}

bool Judge::IsKey(string s) {
    auto p = keys.find(s);
    return !(p == keys.end());
}
