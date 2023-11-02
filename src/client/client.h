#ifndef		CLIENT_H
#define		CLIENT_H

#define		DEFAULT_PLAYERCMD	"/usr/local/bin/mpg123 - > /dev/null"

//使用结构体设置命令行默认值
struct client_conf_st{
	char *rcvport;
	char *mgroup;
	char *player_cmd;
};

extern struct client_conf_st client_conf;







#endif
