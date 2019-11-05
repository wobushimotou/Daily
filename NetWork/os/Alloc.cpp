#include <iostream>
#include <iomanip>
#include <algorithm>
#include <deque>

using namespace std;
struct area{
    int ID;
    int size;
    int address;
    bool flag;
};


class Alloc{
public:
    Alloc(int _max):Max_length(_max){ id = 0; }
    void Init();
    bool First_fit(int);
    bool Best_fit(int);
    bool Worst_fit(int);
    void Show();
    bool Recycle(int);
private:
    deque<area> head;
    int Max_length;
    int id;
};

void Alloc::Init() {
    area temp;
    temp.ID = 0;
    temp.size = Max_length;  
    temp.address = 0;
    temp.flag = 0;
    head.push_back(temp);
}

bool Alloc::First_fit(int size) {
    if(!size)
        return false;
    //从头结点开始寻找不小于size大小的分区
    for(auto p = head.begin();p != head.end();++p) {
        if(p->size >= size && !p->flag) {
            //不用申请新的结点
            if(p->size == size) {
                p->flag = 1;
                return true;
            }
            else {
                //申请新的结点
                area temp;
                temp.ID = ++id;
                temp.size = size;
                temp.address = p->address;
                temp.flag = 1;

                //改变当前分区大小
                p->size -= size;
                p->address += size;

                //将此节点插入当前分区前面
                head.emplace(p,temp);  
                return true;
            }
        }
    }
    return false;
}

bool Alloc::Best_fit(int size) {
    //对空闲分区链表按照大小进行排序
    sort(head.begin(),head.end(),[](const area &a,const area &b){ return a.size < b.size; });
    return First_fit(size);    
}

bool Alloc::Worst_fit(int size) {
    sort(head.begin(),head.end(),[](const area &a,const area &b){ return a.size > b.size; });
    return First_fit(size);
}

bool Alloc::Recycle(int ID) {
    //根据分区ＩＤ回收内存
    auto p = head.begin();
    for(;p != head.end();++p) {
        if(p->ID == ID)
            break;
    }
    if(p == head.end())
        return false;

    //回收p所在分区
    
    p->flag = 0;

    //是否合并Ｐ所在分区
    if((p != head.begin() && !(p-1)->flag) && (p != head.end()-1 && (p+1)->flag))  {
        //改变上一个结点大小
        (p-1)->size += p->size;

        //删除当前分区
        head.erase(p);
        return true;
    }
    if((p != head.begin() && (p-1)->flag) && (p != head.end()-1 && !(p+1)->flag))  {
        //改变下一个结点大小
        (p+1)->size += p->size;
        (p+1)->address -= p->size;

        //删除当前分区
        head.erase(p);
        return true;
    }
    if((p != head.begin() && !(p-1)->flag) && (p != head.end()-1 && !(p+1)->flag))  {
        //将三个分区合并到前一个分区中
        (p-1)->size += p->size;
        (p-1)->size += (p+1)->size;

        //删除当前分区和下一个分区
        head.erase(p); 
        head.erase(p+1);
        return true;
    }

    //无和合并分区
    return true;
}

void Alloc::Show() {
    cout << setw(10) << "ID" << setw(10) << "Address" << setw(10) << "size" << setw(10) << "used" << endl;
    for(auto p = head.begin();p != head.end();++p) {
        cout << setw(10) << p->ID << setw(10) << p->address << setw(10) << p->size << setw(10) << p->flag << endl;        
    }
}

int main()
{
    Alloc ac(1024);    
    ac.Init();
    cout << "1.分配内存" << endl << "2.释放内存" << endl << "输入:" << endl;
    char ch;
    char t;
    int id;
    int size;
    while(cin >> ch) {
        if(ch == '1') {
            system("clear");
            cout << "1.FF算法" << endl << "2.BF算法" << endl << "3.WF算法" << endl << "输入:" << endl;
            cin >> t;
            if(t == '1') {
                cout << "输入要分配的大小:" << endl;
                cin >> size;
                ac.First_fit(size);
                ac.Show();
            }
            else if(t == '2') {
                cout << "输入要分配的大小:" << endl;
                cin >> size;
                ac.Best_fit(size);
                ac.Show();
            }
            else if(t == '3') {
                cout << "输入要分配的大小:" << endl;
                cin >> size;
                ac.Worst_fit(size);
                ac.Show();
            }
        }
        else if(ch == '2') {
            cout << "输入要释放的分区ID" << endl;
            cin >> id;
            if(ac.Recycle(id) ) {
                cout << "释放成功" << endl;
                ac.Show();
            }
            else 
                cout << "释放失败" << endl;
        }
        cout << "1.分配内存" << endl << "2.释放内存" << endl << "输入:" << endl;
    }
    return 0;
}

