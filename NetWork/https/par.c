#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <openssl/ssl.h>
#include <openssl/bio.h>
 
#define HTTP_REQ_LENGTH          512
#define HTTP_RESP_LENGTH         20480
 
typedef struct
{
    int sock_fd;
    SSL_CTX *ssl_ct;
    SSL *ssl;
 
    //url 解析出来的信息
    char *host;
    char *path;
    int port;
} https_context_t;
 
static int https_init(https_context_t *context,const char* url);
static int https_uninit(https_context_t *context);
static int https_read(https_context_t *context,void* buff,int len);
static int https_write(https_context_t *context,const void* buff,int len);
static int https_get_status_code(https_context_t *context);
static int https_read_content(https_context_t *context,char *resp_contet,int max_len);
 
// http 请求头信息
static char https_header[] =
    "GET %s HTTP/1.1\r\n"
    "Host: %s:%d\r\n"
    "Connection: Close\r\n"
    "Accept: */*\r\n"
    "\r\n";
 
static char http_req_content[HTTP_REQ_LENGTH] = {0};
static char https_resp_content[HTTP_RESP_LENGTH+1] = {0};
 
static int create_request_socket(const char* host,const int port)
{
    int sockfd;
    struct hostent *server;
    struct sockaddr_in serv_addr;
 
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        printf("[http_demo] create_request_socket create socket fail.\n");
        return -1;
    }
 
    /* lookup the ip address */
    server = gethostbyname(host);
    if(server == NULL)
    {
        printf("[http_demo] create_request_socket gethostbyname fail.\n");
        close(sockfd);
        return -1;
    }
 
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    memcpy(&serv_addr.sin_addr.s_addr,server->h_addr,server->h_length);
 
    if (connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)) < 0)
    {
        printf("[http_demo] create_request_socket connect fail.\n");
        close(sockfd);
        return -1;
    }
    return sockfd;
}
 
/**
 * @brief https_parser_url  解析出https 中的域名、端口和路径
 * @param url   需要解析的url
 * @param host  解析出来的域名或者ip
 * @param port  端口，没有时默认返回443
 * @param path  路径，指的是域名后面的位置
 * @return
 */
static int https_parser_url(const char* url,char **host,int *port,char **path)
{
    if(url == NULL || strlen(url) < 9 || host == NULL || path == NULL)
    {
         printf("[https_demo] url or host or path is null.\n");
         return -1;
    }
 
    //判断是不是 https://
    int i = 0;
    char https_prefix[] = "https://";
    for(i=0;i<8;i++)
    {
        if(url[i] != https_prefix[i])
        {
            printf("[https_demo] illegal url = %s.\n",url);
            return -1;
        }
    }
 
    const char *temp = url+i;
    while(*temp != '/')  //next /
    {
        if(*temp == '\0')  //
        {
            printf("[https_demo] illegal url = %s.\n",url);
            return -1;
        }
        temp++;
    }
 
    const char *host_port = url+i;
    while(*host_port != ':' && *host_port != '/')  //找到 :或者 / 结束
    {
        host_port ++;
    }
 
    int host_len = host_port-url-i;  //减掉https://
    int path_len = strlen(temp);
    char *host_temp = (char *)malloc(host_len + 1);  //多一个字符串结束标识 \0
    if(host_temp == NULL)
    {
        printf("[https_demo] malloc host fail.\n");
        return -1;
    }
    if(*host_port++ == ':')  //url 中有端口
    {
        *port = 0;
        while(*host_port !='/' && *host_port !='\0')  //十进制字符串转成数字
        {
            *port *= 10;
            *port += (*host_port - '0');
            host_port ++;
        }
    }
    else
    {
        *port = 443;
    }
 
    char *path_temp = (char *)malloc(path_len + 1);  //多一个字符串结束标识 \0
    if(path_temp == NULL)
    {
        printf("[https_demo] malloc path fail.\n");
        free(host_temp);
        return -1;
    }
    memcpy(host_temp,url+i,host_len);
    memcpy(path_temp,temp,path_len);
    host_temp[host_len] = '\0';
    path_temp[path_len] = '\0';
    *host = host_temp;
    *path = path_temp;
    return 0;
}
 
static int https_init(https_context_t *context,const char* url)
{
    if(context == NULL)
    {
        printf("[https_demo] init https_context_t is null.\n");
        return -1;
    }
 
    if(https_parser_url(url,&(context->host),&(context->port),&(context->path)))
    {
        printf("[https_demo] https_parser_url fail.\n");
        return -1;
    }
 
    context->sock_fd = create_request_socket(context->host,context->port);
    if(context->sock_fd < 0)
    {
        printf("[https_demo] create_request_socket fail.\n");
        goto https_init_fail;
    }
 
    context->ssl_ct = SSL_CTX_new(SSLv23_method());
    if(context->ssl_ct == NULL)
    {
        printf("[https_demo] SSL_CTX_new fail.\n");
        goto https_init_fail;
    }
 
    context->ssl = SSL_new(context->ssl_ct);
    if(context->ssl == NULL)
    {
        printf("[https_demo] SSL_new fail.\n");
        goto https_init_fail;
    }
 
    if(SSL_set_fd(context->ssl,context->sock_fd)<0)
    {
        printf("[https_demo] SSL_set_fd fail \n");
    }
 
    if(SSL_connect(context->ssl) == -1)
    {
        printf("[https_demo] SSL_connect fail.\n");
        goto https_init_fail;
    }
    return 0;
https_init_fail:
    https_uninit(context);
    return -1;
}
 
static int https_read(https_context_t *context,void* buff,int len)
{
    if(context == NULL || context->ssl == NULL)
    {
        printf("[https_demo] read https_context_t or ssl is null.\n");
        return -1;
    }
    return SSL_read(context->ssl,buff,len);
}
 
static int https_write(https_context_t *context,const void* buff,int len)
{
    if(context == NULL || context->ssl == NULL)
    {
        printf("[https_demo] write https_context_t or ssl is null.\n");
        return -1;
    }
    return SSL_write(context->ssl,buff,len);
}
 
static int https_get_status_code(https_context_t *context)
{
    if(context == NULL || context->ssl == NULL)
    {
        printf("[https_demo] get status https_context_t or ssl is null.\n");
        return -1;
    }
    int ret;
    int flag =0;
    int recv_len = 0;
    char res_header[1024] = {0};
    while(recv_len<1023)
    {
        ret = SSL_read(context->ssl, res_header+recv_len, 1);
        if(ret<1)  // recv fail
        {
            break;
        }
        //找到响应头的头部信息, 两个"\r\n"为分割点
        if((res_header[recv_len]=='\r'&&(flag==0||flag==2))||(res_header[recv_len]=='\n'&&(flag==1||flag==3)))
        {
            flag++;
        }
        else
        {
            flag = 0;
        }
        recv_len+=ret;
        if(flag==4)
        {
            break;
        }
    }
    //printf("[http_demo] recv_len=%d res_header = %s.\n",recv_len,res_header);
    /*获取响应头的信息*/
    int status_code = -1;
    char *pos = strstr(res_header, "HTTP/");
    if(pos)
    {
        sscanf(pos, "%*s %d", &status_code);//返回状态码
    }
    return status_code;
}
 
static int https_read_content(https_context_t *context,char *resp_contet,int max_len)
{
    if(context == NULL || context->ssl == NULL)
    {
        printf("[https_demo] read content https_context_t or ssl is null.\n");
        return -1;
    }
    int ret ;
    int recv_size = 0;
    while(recv_size < max_len)
    {
       ret = SSL_read(context->ssl,resp_contet + recv_size,max_len-recv_size);
       if(ret < 1)
       {
           break;
       }
       recv_size += ret;
    }
    return recv_size;
}
 
static int https_uninit(https_context_t *context)
{
    if(context == NULL)
    {
        printf("[https_demo] uninit https_context_t is null.\n");
        return -1;
    }
 
    if(context->host != NULL)
    {
        free(context->host);
        context->host = NULL;
    }
    if(context->path != NULL)
    {
        free(context->path);
        context->path = NULL;
    }
 
    if(context->ssl != NULL)
    {
        SSL_shutdown(context->ssl);
        //SSl_free(context->ssl);
        context->ssl = NULL;
    }
    if(context->ssl_ct != NULL)
    {
        SSL_CTX_free(context->ssl_ct);
        context->ssl_ct = NULL;
    }
    if(context->sock_fd > 0)
    {
        close(context->sock_fd);
        context->sock_fd = -1;
    }
    return 0;
}
 
int main()
{
    https_context_t https_ct = {0};
    int ret = SSL_library_init();
    printf("[https_demo] SSL_library_init ret = %d.\n",ret);
 
    https_init(&https_ct,"https://www.baidu.com/");
 
    ret = snprintf(http_req_content,HTTP_REQ_LENGTH,https_header,https_ct.path,https_ct.host,https_ct.port);
 
    ret = https_write(&https_ct,http_req_content,ret);
    printf("%s\n",http_req_content);

    printf("[https_demo] https_write ret = %d.\n",ret);
 
    if(https_get_status_code(&https_ct) == 200)
    {
       ret = https_read_content(&https_ct,https_resp_content,HTTP_RESP_LENGTH);
       if(ret > 0)
       {
           https_resp_content[ret] = '\0';  //字符串结束标识
           printf("[https_demo] https_write https_resp_content = \n %s.\n",https_resp_content);
       }
    }
    https_uninit(&https_ct);
    return 0;
}
