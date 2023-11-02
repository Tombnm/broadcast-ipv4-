#include <stdio.h>
#include <stdlib.h>
#include <optget.h>
#include <string.h>
#include <errno.h>

#include <proto.h>
#include "server_conf.h"

//-M  指定多播组
//-P  指定接收端口
//-F  前台运行
//-D  指定媒体库位置
//-H  显示帮助
//-I  指定网络设备

struct server_conf_st server_conf = {\
	.rcvport = DEFAULT_RCVPORT,\
	.mgroup = DEFAULT_MGROUP,\
	.media_dir = DEFAULT_MEDIADIR,\
	.runmode = RUN_DAEMON,\
	.ifname = DEFAULT_IF};

static void printfhelp(void){
	printf("-M  指定多播组\n");
	printf("-P  指定接收端口\n");
	printf("-F  前台运行\n");
	printf("-D  指定媒体库位置\n");
	printf("-I  指定网络设备\n");
	printf("-H  显示帮助\n");}

//守护进程退出时的动作
static void daemon_exit(int s){
	closelog();
	exit(0);
}

//设置守护进程
static void daemonize(void){
	pid_t pid;
	int fd;

	pid = fork();
	if(pid < 0){
		syslog(LOG_ERR,"fork():failed:%s",strerror(errno));
		//perror("fork()");
		return -1;}
	
	//父进程退出
	if(pid > 0){
		exit(0);}
	
	//子进程设置为守护进程
	fd = open("/dev/null",O_RDWR);
	if(fd < 0){
		syslog(LOG_WARNING,"open():failed:%s)",strerror(errno));
		//perror("open()");
		return -2;}
	else{
		dup2(fd,0);
		dup2(fd,1);
		dup2(fd,2);
		if(fd > 2){
			close(fd);}}
	setsid();
	chdir("/");
	umask(0);
	return 0;}

//socket初始化
static void  socket_init(void){
	int serversd;
	struct ip_mreqn mreq;

	serversdsocket(AF_INET,SOCK_DGRAM,0);
	if(serversd < 0){
		syslog(LOG_ERR,"socket():%s",strerr(errno));
		exit(1);}
	//设置属性
	inet_pton(AF_INET,server_conf.mgroup,&mreq.imr_multiaddr);
	inet_pton(AF_INET,"0.0.0.0",&mreq.imr_address);
	mreq.imr_ifindex = if_nametoindex(server_conf.ifname);
	if(setsockopt(serversd,IPPROTO_IP,IP_MULTICAST_IF,&mreq,sizeof(mreq)) < 0){
		syslog(LOGERR,"setsockopt():%s",strerr(errno));
		exit(1);}
	
	//bind()
}









int main(int argc,char *argv[]){

int c;

//信号处理,sigaction()
struct sigaction sa;
sa.sa_handler = daemon_exit;
sigemptyset(&sa.sa_mask);
sigaddset(&sa.sa_mask,SIGINT);
sigaddset(&sa.sa_mask,SIGQUIT);
sigaddset(&sa.sa_mask,SIGTERM);

sigaction(SIGTERM,&sa,NULL);
sigaction(SIGINT,&sa,NULL);
sigaction(SIGQUIT,&sa,NULL);



//打开系统日志，用于处理守护进程的出错消息
openlog("netradio",LOG_PID | LOG_PERROR,LOG_DAEMON);


//命令行分析
while(1){
	c = getopt(argc,argv,"M:P:F:D:H:I");
	if(c < 0){
		break;}
	switch(c){
		case 'M':
			server_conf.mgroup = optarg;
			break;
		case 'P':
			server_conf.rcvport = optarg;
			break;
		case 'F':
			server_conf.runmode = RUN_FOREGROUD;
			break;
		case 'D':
			server_conf.media_dir = optarg;
			break;
		case 'I':
			server_conf.ifname = optarg;
			break;
		case 'H':
			printfhelp();
			exit(0);
			break;
		default:
			abort();
			break;}
	}

//守护进程的实现
if(server_conf.runmode == RUN_DAEMON){
	if(daemonize() != 0){
		exit(1);}}
else if(server_conf.runmode == RUN_FOREGROUD){
	//do nothing}
else{
	syslog(LOG_ERR,"error:server_conf.runmode.");
	//fprintf(stderr,"EINVAL\n");
	exit(1);}


//创建socket套接字
socket_init();

//获取频道信息
struct mlib_listentry_st *list;
list = malloc();
int list_size;
int err;
err = mlib_getchnlist(&list,&list_size);
if(){

}




//创建节目单线程
thr_list_creat(list,list_size);
//if err


//创建频道线程
int 1 = 0;
for(i = 0;i < list_size;i++){
	thr_channel_creat(list+i);
	if(){}	
}

syslog(LOG_DEBUG,"%d channel threads created.",i);

while(1){
	pause();
}





exit(0);
}
