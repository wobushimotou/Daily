#include "Parsing.h"

void Parsing::Replace(string &source,string target)
{
    int n = count(target.begin(),target.end(),'|');
    int m = count(source.begin(),source.end(),target[0]);
    char ch = target[0];
    //分解target
    vector<string> vv;
    target = target.substr(3,target.size());

    for(int i = 0;i != n+1;++i) {
        int pos = target.find_first_of("|",0);
        vv.push_back(target.substr(0,pos));
        target = target.substr(pos+1,target.size());
    }

    //寻找在source中出现的第一个可替换符号
    size_t t;
    for(int i = 0;i != m;++i) {
        t = source.find_first_of(ch,0);
        int t_next= source.find_first_of("|",t);
        string ss = source.substr(t,t_next-t);
        auto temp = ss;
        //ss为待替换产生式
        if(t != string::npos) {
            for(int i = 0;i != n+1;++i) {
                ss = vv[i]+ss.substr(1,ss.size());         
                source += "|" + ss;
                ss = temp;
            }
            //删除ss自身
            int pos = source.find(temp);
            source.erase(pos,temp.size()+1);
        }    
    }


}

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


void Parsing::ExtractSign()
{
    fstream file(filename);
    string ss;
    //提取所有非终结符号
    while(getline(file,ss)) {
        nonendSigns.push_back(ss[0]);
    }
    
    file.seekg(0,ios::beg);
    char ch;
    while(file >> ch) {
        if(find(nonendSigns.begin(),nonendSigns.end(),ch) == nonendSigns.end() )
            if(ch != '|' && ch != '-' && ch != '>')
                endSigns.push_back(ch);
    }
}

void Parsing::LeftRecursion()
{
    //读取文法的所有产生式
    vector<string> data;
    fstream file_new(filename+"_new");
    fstream file_fin(filename+"_fin",ios::out);
    string ss;

    ExtractSign();

    while(getline(file_new,ss))
        data.push_back(ss);

    for(size_t i = 0;i != data.size();++i) {
        //消除直接左递归
        size_t t = 0;
        t = InnonendSign(data[i],t+1);
        while(t != string::npos) {
            char cc = data[i][t];
            char flag = data[i][t-1];
            if(flag == '|' || flag == '>') {
                if(data[i][0] == cc) {
                    data.push_back(DirectLeftRecursion(data[i],t));
                }

                if(Index(data[i][0]) > Index(cc)) {
                    //可以进行替换
                    for(auto &f:data)
                        if(f[0] == cc) {
                            Replace(data[i],f);
                            f = "";
                        }
                }
            }
            t = InnonendSign(data[i],t+1);
        }
    }


    for(auto &e:data)
        file_fin << e << endl;
}



string Parsing::DirectLeftRecursion(string &ss,int pos)
{
    vector<string> vec;
    string tt;

    //含有直接左递归
    if(pos != 3) {
        string Last  = ss.substr(pos,ss.size());
        string Front = ss.substr(3,pos-1-3);
        ss = ss.substr(0,3);
        ss += Last + "|" + Front;
        cout << ss << endl;
    }

    int t = ss.find_first_of("|");
    string x = ss.substr(4,t-4);
    string y = ss.substr(t+1,ss.size());
    char A = GetNextSign();
    ss = ss.substr(0,3);
    ss += y+A;
    tt += A;
    tt += "->"+x+A+"|@";
    return tt;
}

void Parsing::ExtractLeftFactor()
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
            sort(vec.begin()+1,vec.end());
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
            cout << vv.size() << endl;


            for(size_t m = 0;m != vv.size();++m) {
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
            }

            if(vv.size() && ((vv.end()-1)->size() == 0))
                vv.erase(vv.end()-1);
            
            
            vec.resize(0);

        }   
    } 

}

