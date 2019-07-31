#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

//任务函数
typedef struct WorkFunction{
    void *(*process)(void *arg);    //函数指针
    void * arg;                     //函数参数
    struct WorkFunction *next;      //指向下一个任务
}Work;

//线程池
typedef struct ThreadPool{
    pthread_t* threads;     //线程列表
    Work *tasks;    //任务列表
    pthread_mutex_t mutex;  //互斥量
    pthread_cond_t cond;    //条件变量
    int stop;  //标识线程池是否停止
    int max_thread_num; //线程池允许的最大活动线程数
    int cur_tasks;  //任务队列当前等待任务数
    
}Pool;

static Pool *pool;
void *run(void *args);

//初始化线程池
void InitPool(size_t t_num) {
    pool = (Pool *)malloc(sizeof(Pool));
    //初始化互斥量和条件变量
    pthread_mutex_init(&(pool->mutex),NULL);
    pthread_cond_init(&(pool->cond),NULL);

    //初始化任务队列
    pool->tasks = NULL;

    pool->threads = (pthread_t *)malloc(sizeof(pthread_t)*t_num);
    pool->max_thread_num = t_num;
    pool->cur_tasks = 0;
    pool->stop = 0;
      
    for(size_t i = 0;i < t_num;++i) {
        pthread_create(&(pool->threads[i]),NULL,run,NULL);
    }
}

void *run(void *arg) {
    while(!pool->stop) {
        pthread_mutex_lock(&(pool->mutex));
        //若等待队列为0则处于阻塞状态
        while(pool->cur_tasks == 0 && !pool->stop) {
            printf("thread is wait\n");
            pthread_cond_wait(&(pool->cond),&(pool->mutex));
        }

        //销毁线程池
        if(pool->stop) {
            pthread_mutex_unlock(&(pool->mutex));
            pthread_exit(NULL);
        }
        
        //从任务列表取出任务函数
        pool->cur_tasks--;
        Work *temp = pool->tasks;
        pool->tasks = pool->tasks->next;
        
        pthread_mutex_unlock(&(pool->mutex));

        //开始执行任务
        temp->process(temp->arg);
        free(temp);
    }
}

//往任务队列中添加任务
int Append(void *(*process)(void *arg),void *arg) {

    Work *newWork = (Work *)malloc(sizeof(Work));
    newWork->process = process;
    newWork->arg = arg;
    newWork->next = NULL;

    pthread_mutex_lock(&(pool->mutex));
    //将新任务添加到tasks的末尾
    Work *p = pool->tasks;
    if(p) { 
        while(p->next)
            p = p->next;
        p->next = newWork;
    }
    else
        pool->tasks = newWork; 

    pool->cur_tasks++;
    //唤醒线程去执行此任务
    pthread_cond_signal(&(pool->cond));
    pthread_mutex_unlock(&(pool->mutex));
    return 0;
}

int Desory() {
    if(pool->stop)
        return -1;
    pool->stop = 1;

    //唤醒所有线程
    pthread_cond_broadcast(&(pool->cond));

    //等待所有线程结束
    for(int i = 0;i < pool->max_thread_num;++i) {
        pthread_join(pool->threads[i],NULL);
    }

    free(pool->threads);

    //销毁等待队列
    while(pool->tasks) {
        Work *temp = pool->tasks;
        pool->tasks = pool->tasks->next;
        free(temp);
    }

    //销毁互斥锁和条件变量
    pthread_mutex_destroy(&(pool->mutex));
    pthread_cond_destroy(&(pool->cond));

    free(pool);
}
void *f(void *arg) {
    int a = *(int *)arg;
    printf("**%d**\n",a);
}

int main()
{
    InitPool(10);
    int ar[100];
    for(int i = 0;i < 100;++i) {
        ar[i] = i;
        Append(f,(void *)(ar+i));
    }

    int a;
    scanf("%d",&a);
    printf("任务队列长度为%d\n",pool->cur_tasks);
    Desory();
    return 0;
}

