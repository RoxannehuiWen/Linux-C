#include "../include/proto.h"



#define	IPSTRSIZE	40

int rd;

void *rcver(void *mgroup)
{

	//	struct msg_st rbuf;
	struct sockaddr_in laddr, raddr;
	socklen_t raddr_len;
	char ipstr[IPSTRSIZE];
	struct ip_mreqn mreq;
	char sbuf[BUFSIZE];
	char *mg=(char *)mgroup;
	pid_t pid;
	//int len=0,pos=0,ret;

	int pd[2];
	if(pipe(pd)<0){
		perror("pipe()");
		exit(1);
	}

	inet_pton(AF_INET, mg, &mreq.imr_multiaddr);
	inet_pton(AF_INET, "0.0.0.0", &mreq.imr_address);
	mreq.imr_ifindex = if_nametoindex("eth0");
	if (setsockopt(rd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &mreq, sizeof(mreq))) {
		perror("setsockopt()");
		exit(1);
	}

	laddr.sin_family = AF_INET;
	laddr.sin_port = htons(atoi(RCVPORT));
	inet_pton(AF_INET, "0.0.0.0", &laddr.sin_addr);
	if (bind(rd, (void*)&laddr, sizeof(laddr))<0) {
		perror("bind()");
		exit(1);
	}

	pid=fork();
	if(pid<0){
		perror("fork()");
		exit(1);
	}
	if(pid==0){
		close(pd[1]);
		sleep(2);
		dup2(pd[0],0);
		close(pd[0]);
		execl("/usr/local/bin/mpg123","mpg123","-",NULL);
		perror("execl");
		exit(1);
	}else
	{
		sleep(1);
	
		raddr_len = sizeof(raddr);	/* 必要 */
		while (1) {
			if (recvfrom(rd, sbuf, sizeof(sbuf), 0, (void*)&raddr, &raddr_len)<0) 
			{
				perror("recvfrom()");
				exit(1);
			}
			inet_ntop(AF_INET, &raddr.sin_addr, ipstr, IPSTRSIZE);
			printf("-- Message from: %s:%d --\n", ipstr, ntohs(raddr.sin_port));
			//printf("--: %s,--:%d\n", sbuf);
			write(pd[1],sbuf,BUFSIZE);			
		/*pos=0;ret=BUFSIZE;
		while((len=write(pd[1],sbuf+pos,ret))!=ret)
			{	ret-=len;
				pos+=len;
			}*/
		}
		close(pd[1]);
	}
	close(rd);
}

int main(int argc, char **argv)
{
	while(1){
		//getopt();
		int sd;
		struct sockaddr_in raddr;
		//FILE *fp;
		//pNode pnode;
		char rbuf[BUFSIZE];
		chnid_t id,channel=1;
		char desc[LEN_DESC];
		char mgroup[NR_CHN][LEN_MGROUP];
		int size,i=0,ret;
		pthread_t tid;

		if (argc<2) {
			fprintf(stderr, "Usage...\n");
			exit(1);
		}

		sd = socket(AF_INET, SOCK_STREAM, 0);
		if (sd<0) {
			perror("socket()");
			exit(1);
		}

		raddr.sin_family = AF_INET;
		raddr.sin_port = ntohs(atoi(RCVPORT));
		inet_pton(AF_INET, argv[1], &raddr.sin_addr);
		if (connect(sd, (void*)&raddr, sizeof(raddr))<0) {
			perror("connect()");
			exit(1);
		}

		if (read(sd, rbuf,BUFSIZE)<0) {
			fprintf(stderr, "Bad format.\n");
		} else {

			size=sizeof(chnid_t)+LEN_DESC+LEN_MGROUP;
			while(*(rbuf+i*size)!=0)
			{
				memcpy(&id,rbuf+i*size,sizeof(chnid_t));
				memcpy(desc,rbuf+i*size+sizeof(chnid_t),LEN_DESC);
				memcpy(mgroup[id],rbuf+i*size+sizeof(chnid_t)+LEN_DESC,LEN_MGROUP);
				printf("id: %d\n", id);
				printf("Channel: %s",desc);
				printf("muli-broadcast: %s\n",mgroup[id]);
				i++;
			}


		}

		rd = socket(AF_INET, SOCK_DGRAM, 0 /* IPPROTO_UDP */);
		if (sd<0) {
			perror("socket()");
			exit(1);
		}

		puts("/***************************************************************/");
		puts("Choose your channel, close the current channel(0):");
		scanf("%d",&channel);
		ret= pthread_create(&tid, NULL, rcver,(void *)mgroup[channel]);
		scanf("%d",&channel);
		if(channel==0){close(rd);
			pthread_cancel(tid);}
			continue;
	}
	return 0;
}
