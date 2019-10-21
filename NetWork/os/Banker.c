/*
 *  银行家算法代码
 *
 *
 *
 * */
#include <stdio.h>
#include <pthread.h>
#include <sys/types.h>
#define RESOURCE 3
#define MAXPROCESS 100

int process = 0;
int Available[RESOURCE];
int MaxNeed[MAXPROCESS][RESOURCE];
int Allocation[MAXPROCESS][RESOURCE];
int Need[MAXPROCESS][RESOURCE];
int Finish[MAXPROCESS] = {0};

//比较进程p所需资源数是否全小于系统可用资源数
int Cmp(int p) {
    int flag = 0;
    for(int i = 0;i != RESOURCE;++i) {
        if(Need[p][i] > Available[i])
            return 0;
        if(Need[p][i] == -1) {
            flag = 1;
        }
    }
    
    if(flag)
        return 2;
    return 1;
}

int AllIsFinish() {
    for(int i = 0;i != process;++i)
        if(!Finish[i])
            return 0;
    return 1;
}
//判断系统是否处于安全状态
int Judge(int t) {
    for(int i = t;i != process;++i) {
        if(AllIsFinish())
            return 1;
        if(!Finish[i] && Cmp(i)) {
            printf("%d ",i);

            for(int j = 0;j != RESOURCE;++j) {
                Available[j] += Allocation[i][j]; 
            }
            
            Finish[i] = 1;
        }
        if(i == process-1)
            i = -1;
    }
}

//申请资源
int Apply(int p) {
    if(!Cmp(p)) {
        printf("请求资源数大于系统可分配资源数\n");
        return -1;
    }

    if(Judge(p))
        return 1;
}


int main()
{
    process = 5;
    for(int i = 0;i != RESOURCE;++i)
        scanf("%d",&Available[i]);

    for(int i = 0;i != process;++i) {
        for(int j = 0;j != RESOURCE;++j)
            scanf("%d",&MaxNeed[i][j]);
        for(int j = 0;j != RESOURCE;++j)
            scanf("%d",&Allocation[i][j]);
        for(int j = 0;j != RESOURCE;++j)
            Need[i][j] = MaxNeed[i][j] - Allocation[i][j];
    }

    for(int i = 0;i != process;++i) {
        if(Cmp(i)) {
            Apply(i);
            break;
        }

    }
    return 0;
}
