#include "../include/thr_chnnel.h"
#include "../include/proto.h"


void *send_music_udp(void *chnel)
{
	struct choice *chn=(struct choice *)chnel;
	chn->ser_sd=socket(AF_INET,SOCK_DGRAM,0);
	if(chn->ser_sd<0)
	{
		perror("socket()");
		exit(1);
	}
	
	(chn->mreq).imr_ifindex=if_nametoindex("eth0");
	inet_pton(AF_INET,"0.0.0.0",&(chn->mreq).imr_address);
	inet_pton(AF_INET,chn->mgroup,&(chn->mreq).imr_multiaddr);

	if(setsockopt(chn->ser_sd,IPPROTO_IP,IP_MULTICAST_IF,&(chn->mreq),sizeof(struct ip_mreqn)))
	{
		perror("setsockopt");
		exit(1);
	}

	chn->tbf=tbf_init(CPS,BURST,chn->tbf);

	if(chn->tbf==NULL)
	{
		perror("tbf_init()");
		exit(1);
	}



	(chn->raddr).sin_family=AF_INET;
	(chn->raddr).sin_port=htons(atoi(RCVPORT));
	if(inet_pton(AF_INET,chn->mgroup,&(chn->raddr).sin_addr)!=1)
	{
		fprintf(stderr,"Bad address.\n");
		exit(1);
	}
	//	printf("raddr=%d\n",(chn->raddr).sin_addr);
	memset((chn->sbuf),0,sizeof(chn->sbuf));
	//while(1){
		do{
			chn->sfd=open(chn->filename,O_RDONLY);
			//	chn->sfd=open("/etc/services",O_RDONLY);
			if(chn->sfd<0)
			{
				if(errno!=EINTR)
				{
					perror("open()");
					exit(1);
				}
			}
		}while(chn->sfd<0);
		while(1)
		{
			chn->size=tbf_fetchtoken(chn->tbf,BUFSIZE);

			while((chn->len=read(chn->sfd,chn->sbuf,chn->size))<0)
			{	
				if(errno==EINTR)continue;
				perror("read()");
				break;
			}
			if(chn->len==0)break;
			tbf_returntoken(chn->tbf,chn->size-chn->len);
			chn->pos=0;
			while(chn->len>0)
			{
				if((chn->ret=sendto(chn->ser_sd,&(chn->sbuf),sizeof(chn->sbuf),0,(void *)&(chn->raddr),sizeof(struct sockaddr_in)))<0)
				{
					perror("sendto()");
					exit(1);
				}
				chn->pos+=chn->ret;chn->len-=chn->ret;
			}
		}
		puts("OK");
	
//	}
	close(chn->ser_sd);
}
