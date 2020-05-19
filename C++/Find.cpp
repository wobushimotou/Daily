void Find(string s,map<char,int> &imap) {
    for(int i = 0;i != s.size();++i) {
        imap[s[i]]++;
    }
}
