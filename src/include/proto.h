#ifndef PROTO_H__
#define PROTO_H__

#include <site_type.h>

//多播地址
#define DEFAULT_MGROUP 		"224.2.2.2"
#define DEFAULT_RCVPORT 	"1989"

//总频道个数
#define CHNNR			100

//发送节目单的频道
#define LISTCHNID		0

//最小、最大频道号
#define MINCHNID		1
#define MAXCHNID		(MINCHNID+CHNNR-1)

//发送包的最大的channel包长度，UDP包推荐长度（512-64K），要减去IP和UDP包的报头
#define MSG_CHANNEL_MAX		(65536-20-8)
#define MAX_DATA		(MSG_CHANNEL_MAX-sizeof(uint8_t))

//节目单包的长度
#define MSG_LIST_MAX		(65536-20-8)
#define MAX_ENTRY		(MSG_CHANNEL_MAX-sizeof(uint8_t))

//发送数据结构体,UDP的结构体不能对齐
struct msg_channel_st{
	chnid_t chnid;
	uint8_t data[1];
}__attribute__((packed));

struct msg_listentry_st{
	chnid_t chnid;
	uint16_t len;
	uint8_t desc[1];
}__attribute__((packed));

struct msg_list_st{
	chnid_t chnid;
	struct msg_listentry_st entry[1];
}__attribute__((packed));

#endif
