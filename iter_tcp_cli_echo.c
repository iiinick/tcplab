#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#define BUFFER_LENGTH 140

//客户端服务程序
int main(int argc, char *argv[]) {
//获取服务器地址
struct sockaddr_in server_addr;
int connfd;
char buf[BUFFER_LENGTH];
int n;
int count=0;

if (argc != 3){
printf("输入错误\n");
return 1;
}

connfd = socket(AF_INET, SOCK_STREAM, 0);

bzero(&server_addr, sizeof(server_addr));
server_addr.sin_family = AF_INET;
server_addr.sin_port = htons(atoi(argv[2]));
if (inet_aton(argv[1], &server_addr.sin_addr) == 0){
return 1;
}


//建立连接
if(connect(connfd,(struct sockaddr *)&server_addr,sizeof(server_addr))<0){
printf("woccccc\n");
}

//打印服务器的ip和端口信息
char out[50]="[cli] server[";
strcat(out,argv[1]);
strcat(out,":");
strcat(out,argv[2]);
strcat(out,"] is connected!");
printf("%s\n",out);

while(1){
memset(buf, 0, BUFFER_LENGTH);

fgets(buf,BUFFER_LENGTH,stdin);
printf("[ECH_RQT]%s",buf);
//退出
if(strcmp(buf,"exit\n")==0||strcmp(buf,"EXIT\n")==0){

close(connfd);
printf("[cli] connfd is closed!");
return 0;
}

count=strlen(buf);
buf[count]='\0';
//传输字符
n=write(connfd,buf,strlen(buf));
if(n==-1){
printf("woccccczx\n");
}
//获得回声
n=read(connfd,buf,BUFFER_LENGTH);
buf[n]='\0';
//设置输出格式
char out2[130]="[ECH_REP]";
strcat(out2,buf);
printf("%s",out2);
}
close(connfd);
}