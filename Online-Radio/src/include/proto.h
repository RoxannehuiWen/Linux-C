////////////////////////////////////////////////////////////////////////////////

#ifndef _TBF_H_
#define _TBF_H_
#define TBF_MAX 1024
#define CPS 16400
#define BURST 32800
#define BUFSIZE 16400

#include <pthread.h>

typedef void tbf_t;
struct tbf_st{
	int cps,burst;
	int token;
	int pos;
	pthread_mutex_t mut;
	pthread_cond_t cond;
};

tbf_t *tbf_init(int cps,int burst,struct tbf_st *me);
int tbf_destroy(tbf_t *);
int tbf_fetchtoken(tbf_t *,int);
int tbf_returntoken(tbf_t *,int);
void module_load(void);
void module_unload(void);

#endif

////////////////////////////////////////////////////////////////////////////////

#ifndef _MEDIALIB_H_
#define _MEDIALIB_H_

#include <sys/types.h>
#include <sys/socket.h>
#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/time.h>

void *send_music_udp(void *);

#endif
////////////////////////////////////////////////////////////////////////////////

#ifndef _PROTO_H__
#define _PROTO_H__

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define MGROUP  "224.2.2."
#define RCVPORT "1999"

#define DEFAULT_INSTALLPATH "/usr/local/netradio/*"
#define DEFAULT_DESCFILE "desc.txt"

#define LEN_DESC 32

#define NR_CHN 200

typedef int chnid_t;

//////////////////////////////////////////////////////////
/*         the return infomation for the channel        */

#define PATHSIZE 128
#define LEN_MGROUP 32
#define NAMESIZE 512

struct choice
{
chnid_t chnid;
char mgroup[LEN_MGROUP];
char filename[NAMESIZE];
int ser_sd;
tbf_t *tbf;
char sbuf[BUFSIZE];
int len,pos,sfd,ret,size;
struct ip_mreqn mreq;
struct sockaddr_in raddr;
} __attribute__((packed));

///////////////////////////////////////////////////////////
/*global variable for the channel and the broadcast group*/

struct choice chn_bg[NR_CHN];

//////////////////////////////////////////////////////////
/*		pass the opreration using TCP		*/

struct msg_channel_st
{
	chnid_t chnid;
	uint16_t data_len;		
	uint8_t data[1];
} __attribute__((packed));

//////////////////////////////////////////////////////////
/*    the list of channel and the list in its channel   */

struct music_st
{
	chnid_t chnid;
	struct music_st *next;		
	uint8_t name[1];	/*ASCIIZ*/
}__attribute__((packed));

struct channel_list_st
{
	chnid_t chnid;
	struct channel_list_st *next;
	uint8_t desc[LEN_DESC];	
}__attribute__((packed));

typedef struct channel_list_st sNode, *pNode;
typedef struct music_st sMusic,*pMusic;

#endif
////////////////////////////////////////////////////////////////////////////////


