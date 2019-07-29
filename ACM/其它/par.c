#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct key_value{
    char pattern;
    char *str;
};

char *findstr(struct key_value *kv,char pattern) {

}

char findpattern(struct key_value *kv,char *str) {

}


int wordPattern(char pattern[],char str[]) {
    int lp = strlen(pattern);
    int ls = strlen(str);

    //存储所有单词的指针数组
    char *vec[50];
    
    char temp[20];  
    bzero(temp,20);

    //存储单词的个数
    int n;
    //取出str中所有的单词
    for(int i = 0,j = 0,n = 0;i <= ls;++i) {
        if(str[i] == ' ' || (i == ls && strlen(temp) )) {
            char *s = (char *)malloc(strlen(temp));
            strcpy(s,temp);
            vec[n++] = s;
            bzero(temp,20);
            j = 0;
        }
        else {
            temp[j++] = str[i];
        }
    }

    struct key_value kv[n];
    for(int i = 0,j = 0;i <= n;++i) {
        if(findstr(kv,pattern[i]) && findpattern(kv,vec[i])) {
            kv[j++] = {pattern[i],vec[i]};

        }
        else if(findstr(kv,pattern[i]) != vec[i]) {
            return false;
        }
    
    }
}
int main()
{
    char str[] = "wang heng hah jiji xixi";
    char patt[] = "aabb";
    wordPattern(patt,str); 
    return 0;
}

