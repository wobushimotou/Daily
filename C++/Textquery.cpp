#include <iostream>
#include <sstream>
#include <string>
#include <memory>
#include <set>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

string make_plural(size_t ctr,const string &word,const string ending)
{
    return (ctr == 1)?word : word+ending;
}

class QueryResult;

class TextQuery {
public:
	using LineNo = vector<string>::size_type;
	TextQuery(istream&);
	QueryResult query(const string&) const;
private:
	shared_ptr<vector<string>> input;
	std::map<string, shared_ptr<std::set<LineNo>>> result;
    string cleanup_str(const string &word);
};


TextQuery::TextQuery(istream &is) : input(new vector<string>)
{
	string Text;
	while (getline(is,Text)) 		//对文件中每一行
	{
		input->push_back(Text);	//保存此行文本
		int n = input->size() - 1;	//当前行号
		istringstream line(Text);	//将行文本分解为单词
		string word;
		while (line >> word) 		//将行中的每个单词输出到word//如果单词不在wm中，以之为下标在wm中添加一行
		{
		 word = cleanup_str(word);

		 auto &lines = result[word];	//如果单词不在wm中，以之为下标在wm中添加一项；lines是一个shared_ptr

		 if (!lines)			//word第一次出现时，返回的指针为空
			lines.reset(new set<LineNo>);	//指针此时没有所指对象，分配一个新的set
		 lines->insert(n);		//将此行号插入set中
		}
	}
}
string TextQuery::cleanup_str(const string &word)
{
	string ret;
	for (auto it = word.begin(); it != word.end(); ++it)
	{
		if (!ispunct(*it))
			ret += tolower(*it);
	}
	return ret;
}

class QueryResult{
        friend ostream& operator<<(ostream&, const QueryResult&);
public:
        QueryResult(const string& s, shared_ptr<set<TextQuery::LineNo>> set,shared_ptr<vector<string>> v)
            : word(s), nos(set), input(v) {  }
        set<TextQuery::LineNo>::iterator Begin() { return nos->begin(); }
        set<TextQuery::LineNo>::iterator End() { return nos->end(); }
        shared_ptr<vector<string>> get_file() { vector<string> vec; vec.push_back("1.txt"); return make_shared<vector<string>>(vec); }
private:
        string word;
        shared_ptr<set<TextQuery::LineNo>> nos;
        shared_ptr<vector<string>> input;
};

ostream& operator<<(ostream &os, const QueryResult &q)
{
    os << q.word << "occurs" << q.nos->size() << " "
		<<make_plural(q.nos->size(), "time", "s") << endl;
    for(auto num : *q.nos)
        os << "\t(line " << num+1 << ")" << *(q.input->begin() + num) << endl;
    return os;
}

QueryResult TextQuery::query(const string &sought) const
{
    static shared_ptr<set<LineNo>> nodata(new set<LineNo>);

    auto loc = result.find(sought);

    if(loc == result.end())
        return QueryResult(sought,nodata,input);
    else
        return QueryResult(sought,loc->second,input);
}


class Query;
class Query_base{
    friend Query;
protected:
    using line_no = TextQuery::LineNo;
private:
    virtual QueryResult eval(const TextQuery&)const=0;
    virtual string rep() const=0;
};

class WordQuery : public Query_base{
    friend class Query;
    WordQuery(const string &s) : query_word(s) { cout << s+"WordQuery" << endl; }
    QueryResult eval(const TextQuery &t)const { return t.query(query_word); }
    string rep() const { return query_word; }
    string query_word;
};

class Query{
    friend Query operator~(const Query &);
    friend Query operator&(const Query &,const Query &);
    friend Query operator|(const Query &,const Query &);
public:
    Query(const string &);
    QueryResult eval(const TextQuery &t)const { return q->eval(t); };
    string rep() const {return q->rep();}
private:
    Query(shared_ptr<Query_base> query) : q(query) {   cout <<q->rep()+"Query(shared_ptr)" << endl; }
    shared_ptr<Query_base> q;
};

ostream &operator <<(ostream &os,const Query &query)
{
    return os << query.rep();
}

Query::Query(const string &s) : q(new WordQuery(s)) { cout << s+"Query" << endl;  }

class NotQuery : public Query_base{
    friend Query operator~(const Query &);
    NotQuery(const Query &q) : query(q) {  cout << q.rep()+"NotQuery" << endl;  }
    string rep() const { return "~("+query.rep()+")"; }
    QueryResult eval(const TextQuery &)const;
    Query query;
};

Query operator~(const Query &q)
{
    return shared_ptr<Query_base>(new NotQuery(q));
}

class BinaryQuery : public Query_base{
protected:
    BinaryQuery(const Query &l,const Query &r,string s) : lhs(l),rhs(r),opSym(s) {  cout << s+"BinaryQuery" << endl;  }
    string rep() const { return "("+lhs.rep()+" "+opSym+" "+rhs.rep()+" "+")"; }
    Query lhs,rhs;
    string opSym;
};

class AndQuery : public BinaryQuery{
    friend Query operator&(const Query &,const Query &);
    AndQuery(const Query &left,const Query &right) : BinaryQuery(left,right,"&") {   cout << "AndQuery" << endl; }
    QueryResult eval(const TextQuery &)const;
};

Query operator&(const Query &l,const Query &r)
{
    return shared_ptr<Query_base>(new AndQuery(l,r));
}

class OrQuery : public BinaryQuery{
    friend Query operator|(const Query &,const Query &);
    OrQuery(const Query &left,const Query &right) : BinaryQuery(left,right,"|") {   cout << "OrQuery" << endl; }
    QueryResult eval(const TextQuery &)const;
};

Query operator|(const Query &l,const Query &r)
{
    return shared_ptr<Query_base>(new OrQuery(l,r));
}

QueryResult OrQuery::eval(const TextQuery &text) const
{
    auto right = rhs.eval(text),left = lhs.eval(text);

    auto ret_lines = make_shared<set<line_no>>(left.Begin(),right.End());

    ret_lines->insert(right.Begin(),right.End());

    return QueryResult(rep(),ret_lines,left.get_file());
}

QueryResult AndQuery::eval(const TextQuery &text)const
{
    auto left = lhs.eval(text),right = rhs.eval(text);

    auto ret_lines = make_shared<set<line_no>>();
    
    set_intersection(left.Begin(),left.End(),right.Begin(),right.End(),inserter(*ret_lines,ret_lines->begin()));

    return QueryResult(rep(),ret_lines,left.get_file());
}

QueryResult NotQuery::eval(const TextQuery &text)const
{
    auto result = query.eval(text);

    auto ret_lines = make_shared<set<line_no>>();

    auto beg = result.Begin(),end = result.End();

    auto sz = result.get_file()->size();

    for(size_t n = 0;n != sz;++n) {
        if(beg == end || *beg != n)
            ret_lines->insert(n);
        else if(beg != end)
            ++beg;

    }
    return QueryResult(rep(),ret_lines,result.get_file());
}

int main()
{
    Query q2("1.txt");
    cout << q2.eval(cin) << endl;
    return 0;
}

