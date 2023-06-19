#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <unistd.h> 
#include <arpa/inet.h> 
#include <signal.h>
#include <errno.h>
#define BUFFER_LENGTH 140
#define LISTENQ 10

int main(int argc,char *argv[]){

//创建SIGINT信号处理器
int sigint_flag=0;

void change_sig(int sig){
     printf("SIDINT arrives");
     sigint_flag=1;
}

//安装SIGINT信号处理器,看不懂的代码1 love from zx
struct sigaction sa;
sa.sa_flags = 0;
sa.sa_handler=change_sig;
sigemptyset(&sa.sa_mask);
sigaction(SIGINT,&sa,NULL);

//定义服务器和客户机的地址结构
struct sockaddr_in server_addr, client_addr;
//定义套接字地址信息结构体变量
int listenfd,connfd;

socklen_t client_addr_len = sizeof(struct sockaddr);
char buf[BUFFER_LENGTH];
//定义接收缓存buf,长度为BUFFER_LENGTH
int n;

listenfd=socket(AF_INET,SOCK_STREAM,0);

if(listenfd == -1){return 1;}
if (argc != 4){
printf("输入不符合规范\n");
return 1;
}


//创建tcp套接字
bzero(&server_addr, sizeof(server_addr));
//套接字地址信息结构体变量初始化清0
server_addr.sin_family = AF_INET;
//指定网络协议类型为IP协议
inet_aton(argv[1],&server_addr.sin_addr);
server_addr.sin_port=htons(atoi(argv[2]));

if (bind(listenfd, (struct sockaddr *)&server_addr, 
sizeof(server_addr)) == -1){ 
//将地址信息绑定到套接字
printf("blinding failed\n");
return 1;
}

listen(listenfd,LISTENQ);


//在这里拼接字符输出
char out[50]="[srv]server[";
strcat(out,argv[1]);
strcat(out,":");
strcat(out,argv[2]);
strcat(out,"][");
strcat(out,argv[3]);
strcat(out,"]");
strcat(out," is initializing!");
printf("%s\n",out);


while(!sigint_flag){

connfd=accept(listenfd,(struct sockaddr*)&client_addr,&client_addr_len);

if(connfd<0){

if(errno==EINTR){
continue;
}else{

return 0;
}

}
//无限循环，收发数据
memset(buf,0, BUFFER_LENGTH);
// 清空buf变量存储空间
//读取数据

char out4[50]="[srv] client[";
char clip[20];
inet_ntop(AF_INET, &(client_addr.sin_addr), clip, INET_ADDRSTRLEN);
int clp = ntohs(client_addr.sin_port);
char client_port_str[6]; 
sprintf(client_port_str, "%d", clp);
strcat(out4,clip);
strcat(out4,":");
strcat(out4,client_port_str);
strcat(out4,"] is closed!");


//断开连接时的输出

while(1){

n=read(connfd,buf,sizeof(buf));
if(n==0){
printf("%s\n",out4);
close(connfd);
break;
}
//按要求打印传来的结果
char out2[130]="[ECH_RQT]";
buf[n] = '\0';
strcat(out2,buf);
printf("%s",out2);
//以阻塞I/O的方式从网络接收数据
// client_addr套接字地址信息结构体变量
if (n == -1){printf("fail to receive!!!!!");exit(1);}
else{ 

//返回数据
char back[60]="(";
strcat(back,argv[3]);
strcat(back,")");
strcat(back,buf);

n=write(connfd, back, strlen(back));


//小循环括号
}


if (n == -1){printf("fail to reply");exit(1);}
}
//while括号
}

if (close(listenfd) == -1){
//关闭套接字
printf("fail to close");
return 1;
}
//main括号
}