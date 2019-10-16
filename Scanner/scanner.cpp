#include <iostream>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <map>
#include <vector>
#include <dirent.h>
#include <string.h>

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
    Scan(string s) : filename(s) { 
        jd = new Judge();
        typecode = ++(--jd->signs.end())->second;
    } 
    void Scanner();
    void Display();
private:
    bool IsDirectory(string ,string);
    bool IsIdentifier(string word);
    bool IsConstant(string word);
    typedef map<string,int> TypeCode;
    void Replace();
    void PreTreatMent();
    void Analysis();
    vector<pair<string,int>> values;
    TypeCode Identifier;
    TypeCode Constant;
    vector<string> Grand;
    string filepath = "/usr/java/jdk-10.0.2/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin";
    string filename;
    Judge *jd;
    int typecode;
};

//返回文件名为name的文件是否存在于Path目录下
bool Scan::IsDirectory(string name,string Path) {
    //递归的进行查询
    string file;
    DIR *dir;
    struct dirent *dp;
    dir = opendir(Path.c_str());
    while((dp = readdir(dir)) != NULL) {
        if(!strcmp(dp->d_name,name.c_str())) {
            return true;
        }
    } 
    return false;
}
bool Scan::IsIdentifier(string word) {
    auto p = Identifier.find(word);
    return !(p == Identifier.end());
}

bool Scan::IsConstant(string word) {
    auto p = Constant.find(word);
    return !(p == Constant.end());
}

void Scan::Replace() {

    fstream file(filename);
    fstream file_I(filename.substr(0,filename.find(".",0))+".I",ios::out);
    char ch;
    //处理所有的预处理命令
    while(file.read(&ch,1)) {
        if(ch == '#') {
            string word;
            while(file.read(&ch,1)) {
                if(jd->IsSign(ch) && !jd->IsSpace(ch))
                    break;
                if(jd->IsLetter(ch))
                    word.push_back(ch);
            }
            if(word == "include") {
                word = "";
                //获取文件名
                while(file.read(&ch,1)) {
                    if(ch == '>' || ch == '\"')
                        break;
                    if(jd->IsDigit(ch) || jd->IsLetter(ch) || ch == '.')
                        word.push_back(ch);
                }

                string Path;
                //获取文件的搜索目录
                if(word[word.size()] == 'h')
                    Path = filepath;

                if(ch == '>')
                    Path += ":.";
                else
                    Path += ".:";

                for(int i = 0;i != count(Path.begin(),Path.end(),':');++i) {
                    auto it = Path.find(":",0);
                    string catalog = Path.substr(0,it);
                    //在每个搜索目录下查询文件是否存在
                    if(IsDirectory(word,catalog)) {
                        //打开文件，将文件中的内容输入到.i文件中
                        string Include = catalog+"/"+word;
                        fstream grandfile(Include); 
                        string data;
                        char c;
                        while(grandfile.read(&c,1)) {
                            data.push_back(c);
                        }
                        grandfile.close();
                        file_I << data;
                        break;
                    }
                    Path = Path.substr(it+1,Path.size());
                }

            }
            else if(word == "define") {

            }
            continue;
        }
        file_I << ch;
    } 
    
    file.close();
    file_I.close();
}

void Scan::PreTreatMent() {
    //预处理
    Replace();

    fstream file_i(filename.substr(0,filename.find(".",0))+".i",ios::out);
    fstream file_I(filename.substr(0,filename.find(".",0))+".I");

    char ch;
    char last;
    

    //滤掉换行以及注释,减少空格
    while(file_I.read(&ch,1)) {
        //保持双引号内的内容不变
        if(ch == '"') {
            file_i << ch;
            while(file_I.read(&ch,1)) {
                file_i << ch;
                if(ch == '"')
                    break;
            }
            continue;
        }
        //过滤注释包括//与/*---*/
        if(ch == '/') {
            file_I >> ch;
            if(ch == '*') {
                while(file_I >> ch) {
                    if(ch == '*') {
                        file_I >> ch;
                        if(ch == '/')
                            break;
                    }
                }
                continue;
            }
            if(ch == '/' || last == '/') {
                while(file_I.read(&ch,1))
                    if(ch == '\n')
                        break;
            }
            continue;
        }
        else if(ch == '\n')
            continue;
        //过滤空格，多个空格根据情况减少为一个或零个
        else if(ch == ' ') {
            while(file_I.read(&ch,1)) {
                if(ch != ' ')
                    break;
            }
            if(!jd->IsSign(last) && !jd->IsSign(ch)) {
                file_i << " ";
            }
            if(ch == '/') {
                last = '/';
                continue;
            }
        }
        
        file_i << ch;
        last = ch;
    } 

    file_I.close();
    file_i.close();
}

void Scan::Analysis() {
    fstream file_i(filename.substr(0,filename.find(".",0))+".i");
    char ch;
    string word;
    while(file_i.read(&ch,1)) {
        word.push_back(ch);
        if(jd->IsLetter(ch)) {
            while(file_i.read(&ch,1)) {
                if(jd->IsSign(ch) || jd->IsSpace(ch)) {
                   //判断是否为关键字
                    if(jd->IsKey(word)) {
                        auto p = make_pair(word,jd->keys[word]);
                        values.push_back(p);
                    }
                    else {
                        //判断标识符表中是否存在
                        if(!IsIdentifier(word))
                            //保存到标识符表中
                            Identifier[word] = typecode++;
                        auto p = make_pair(word,Identifier[word]); 
                        values.push_back(p);
                    }
                    //将分隔符保存起来
                    if(jd->IsSign(ch)) {
                        string temp(1,ch);
                        int num = jd->signs[ch];
                        auto p = make_pair(temp,num);
                        values.push_back(p);
                    }

                    break;
                }
                else {
                    word.push_back(ch);
                }
            }
            word = "";
        }
        else if(jd->IsDigit(ch)) {
            while(file_i.read(&ch,1)) {
                if(jd->IsSign(ch) || jd->IsSpace(ch)) {
                    //将常量保存到表中
                    if(!IsConstant(word))
                        Constant[word] = typecode++;
                    auto p = make_pair(word,Constant[word]);
                    values.push_back(p);

                    //将分隔符保存起来
                    if(jd->IsSign(ch)) {
                        string temp(1,ch);
                        int num = jd->signs[ch];
                        auto p = make_pair(temp,num);
                        values.push_back(p);
                    }
                    break;
                }    
                else {
                    word.push_back(ch);
                }
            }
        }
        else if(jd->IsSign(ch)) {
            //保存分隔符
            auto p = make_pair(string(1,ch),jd->signs[ch]);
            values.push_back(p);
            word = "";
            if(ch == '"') {
                while(file_i.read(&ch,1)) {
                    if(ch == '"')
                        break;
                    word.push_back(ch);
                }       
                //将""内的内容加入常量表
                if(!IsConstant(word))
                    Constant[word] = typecode++;
                auto p = make_pair(word,Constant[word]);
                values.push_back(p);
                auto q = make_pair("\"",jd->signs['"']);
                values.push_back(q);
            }

        }
        else if(jd->IsSpace(ch))
            continue;
        
    }
}

void Scan::Display() {
    cout << setw(20) << setfill(' ') << "sign" << " " << setw(20) << setfill(' ') << "typecode" << endl;
    for(auto p = values.begin();p != values.end();++p) {
        cout << setw(20) << setfill(' ') << p->first << " " << setw(20) << setfill(' ') << p->second << endl;
    } 
    
    cout << "标识符表" << endl;
    for(auto p = Identifier.begin();p != Identifier.end();++p) {
        cout << setw(20) << setfill(' ') << p->first << " " << setw(20) << setfill(' ') << p->second << endl;
    } 


    cout << "常量表" << endl;
    for(auto p = Constant.begin();p != Constant.end();++p) {
        cout << setw(20) << setfill(' ') << p->first << " " << setw(20) << setfill(' ') << p->second << endl;
    } 
  


}
void Scan::Scanner() {
    //预处理
    PreTreatMent();
    //开始词法分析
    Analysis();
    
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
