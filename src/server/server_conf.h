#ifndef SERVERCONF_H
#define SERVERCONF_H

#define		DEFAULT_MEDIADIR	"/home/liwh/apeu/proj/netradio/media/"
#define		DEFAULT_IF		"eth0"	


enum{
	RUN_DEAMON = 1;
	RUN_FOREGROUD
};



struct server_conf_st{
	char *rcvport;
	char *mgroup;
	char *media_dir;
	char *runmode;
	char *ifname;};

extern struct server_conf_st server_conf;

#endif
