#include "Parsing.h"
char Parsing::GetNextSign()
{
    if(signs.size()) {
        char sign = signs[0];
        signs.erase(0,1);
        return sign;
    }
    fstream file(filename,ios::in);
    string ss;
    char ch;
    while(file.read(&ch,1))
        ss.push_back(ch);
    for(char a = 'A';a != 'Z';++a)
        if(ss.find(a,0) == string::npos)
            signs.push_back(a);
    
    char sign = signs[0];
    signs.erase(0,1);
    return sign;
}

void Parsing::LeftRecursion()
{
    fstream file_new(filename+"_new",ios::in);
    fstream file_fin(filename+"_fin",ios::out);
    string ss;
    vector<string> vec;

    while(getline(file_new,ss)) {
        //含有直接左递归
        if(ss[0] == ss[3]) {    
            string tt;
            int t = ss.find_first_of("|");
            string x = ss.substr(4,t-4);
            string y = ss.substr(t+1,ss.size());
            char A = GetNextSign();
            ss = ss.substr(0,3);
            ss += y+A;
            tt += A;
            tt += "->"+x+A+"|@";

            file_fin << ss << "\n";
            file_fin << tt << "\n";
        } 
        else 
            file_fin << ss << "\n";
    }
}

void Parsing::LeftFactor()
{
    fstream file_old(filename,ios::in);
    fstream file_new(filename+"_new",ios::out);
    
    string ss;
    vector<string> vec;
    while(getline(file_old,ss)) {
        //判断有多少个产生式
        
        vector<string> vv;
        vector<string> data;
        int n = count(ss.begin(),ss.end(),'|');
        if(n) {
            //保存左部信息
            vec.push_back(ss.substr(0,ss.find_first_of(">")+1));
            //去掉左部信息
            ss = ss.substr(ss.find_first_of(">")+1,ss.size()); 

            for(int i = 0;i != n+1;++i) {
                //将所有产生式提取出来
                int t = ss.find_first_of("|",0);
                vec.push_back(ss.substr(0,t));
                ss = ss.substr(t+1,ss.size());
            }

            map<char,int> im;   //存储每个产生式中最左符号出现的次数
            map<char,string> ii;    //存储每个新的产生式

            for(auto p = vec.begin()+1;p != vec.end();++p)
                im[p->at(0)]++;
            
            
            char c;
            for(auto p = vec.begin()+1;p != vec.end();++p) {
                if(im[p->at(0)] > 1) {
                    //产生新的产生式
                    if(ii[p->at(0)].size() == 0) {
                        c = GetNextSign();
                        ii[p->at(0)].push_back(c);
                        ii[p->at(0)] += "->";
                    }
                    ii[p->at(0)] += p->substr(1,p->size())+"|";

                    //消除左公共因子
                    *p = p->at(0); 
                    p->push_back(c);
                }
            }

            for(auto &e:ii)
                if(e.second.size() > 0)
                    e.second = e.second.substr(0,e.second.size()-1);
            //合并产生式
            sort(vec.begin(),vec.end());
            vec.erase(unique(vec.begin(),vec.end()),vec.end());

            //将新的内容写入文件
            string content;

                 for(auto p = vec.begin();p != vec.end();++p)
                if(p->at(p->size()-1) == '>' || (p == vec.end()-1))
                    content += *p;
                else
                    content += *p+"|";


            //消除新产生式重复
            for(auto p = ii.begin();p != ii.end();++p)
                vv.push_back(p->second);

            for(auto p = vv.begin();p != vv.end();++p)
                for(auto q = p+1;q != vv.end();++q)
                    if(p->substr(3,p->size()) == q->substr(3,q->size())) {
                        char ch = p->at(0);
                        char c = q->at(0);
                        size_t t = 0;
                        while((t = content.find(c,0))!= string::npos) {
                            content[t] = ch;
                        }
                        *q = "";
                    }


            file_new << content << "\n";

            for(size_t m = 0;m != vv.size();++m)
                if(vv[m].size() ) {
                    vv[m] = vv[m].substr(0,vv[m].size());

                    if(find(data.begin(),data.end(),vv[m]) != data.end())
                        continue;
 
                    file_new << vv[m]<< "\n";
                    data.push_back(vv[m]);
                }
                else {
                    if(m != vv.size()-1)
                        vv.erase(vv.begin()+m);
                }

            if((vv.end()-1)->size() == 0)
                vv.erase(vv.end()-1);
            
            
            vec.resize(0);

        }   
    } 

}

