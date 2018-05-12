#include "../include/proto.h"
#include "../include/thr_chnnel.h"
#include <glob.h>
#include <dirent.h>

static int ip=1;
char buf[4];

void get_ip()
 {
	 ip++;
	 char s1[2],s2[2],s3[2];
	 s1[0]=ip/100;
	 s2[0]=ip%100/10;
	 s3[0]=ip%10;
	 s1[1]='\0';
	 s2[1]='\0';
	 s3[1]='\0';
	 memset(buf,0,3);
	 buf[0]='\0';
	 if(s1[0]!=0)
	 {
		 s1[0]=s1[0]+'0';
		 strcat(buf,s1);
	 } 
	 if(s2[0]!=0)
	 {
		 s2[0]=s2[0]+'0';
		 strcat(buf,s2);
	 }        
	 if(s3[0]!=0)
	 {
		 s3[0]=s3[0]+'0';
		 strcat(buf,s3);
	 }
	 buf[3]='\0';
	 puts(buf);

 }

unsigned int cn;
void init_channel_filename()
{
	char p[2]={'/','\0'};
	glob_t glob_res;
	DIR *dp;
	struct dirent *res;
	int ret,i,fd;
		
	ret=glob(DEFAULT_INSTALLPATH,0,NULL,&glob_res);
	if(ret!=0)
	{
		perror("glob()");
		exit(1);
	}
	cn=glob_res.gl_pathc;
	for(i=0;i<cn;++i)
	{	
		dp=opendir(glob_res.gl_pathv[i]);
		if(dp==NULL)
		{
			perror("opendir()");
			continue;
		}
		puts(glob_res.gl_pathv[i]);
		while((res=readdir(dp))!=NULL)
		{
			if(res->d_name[0]=='.')continue;
			puts(res->d_name);

			if(strcmp(res->d_name,DEFAULT_DESCFILE)!=0)
			{
				chn_bg[i].tbf=malloc(sizeof(struct tbf_st));
				chn_bg[i].chnid=i+1;
				chn_bg[i].tbf=malloc(sizeof(struct tbf_st));
				(chn_bg+i)->mgroup[0]='\0';
				memcpy(chn_bg[i].mgroup,MGROUP,sizeof(MGROUP));
				get_ip();	
				strcat(chn_bg[i].mgroup,buf);
				puts((chn_bg+i)->mgroup);	
				//strcat(path,res->d_name);
				memset((chn_bg+i)->filename,0,BUFSIZE);
				(chn_bg+i)->filename[0]='\0';
				strcat((chn_bg+i)->filename,glob_res.gl_pathv[i]);
				strcat((chn_bg+i)->filename,p);
				strcat((chn_bg+i)->filename,res->d_name);
				puts((chn_bg+i)->filename);	
				break;
			}
		}
	}
	globfree(&glob_res);
}

void create_channel_list(int sd)
{
	char *p;
	glob_t glob_res;
	DIR *dp;
	struct dirent *res;
	char buf[LEN_DESC],path[BUFSIZE];
	int ret,i,fd,len,size;
	char sbuf[BUFSIZE];
	
	pNode pnew;
	
	ret=glob(DEFAULT_INSTALLPATH,0,NULL,&glob_res);
	if(ret!=0)
	{
		perror("glob()");
		exit(1);
	}

memset(sbuf,0,BUFSIZE);
	for(i=0;i<glob_res.gl_pathc;++i)
	{	
		
		dp=opendir(glob_res.gl_pathv[i]);
		if(dp==NULL)
		{
			perror("opendir()");
			continue;
		}

		while((res=readdir(dp))!=NULL)
		{
			if(res->d_name[0]=='.')continue;

			path[0]='\0';
			strcat(path,glob_res.gl_pathv[i]);
			strcat(path,"/");

			if(strcmp(res->d_name,DEFAULT_DESCFILE)==0)
			{
				strcat(path,res->d_name);
				fd=open(path,O_RDONLY);
				//		p=strrchr(path,'/')+1;
				//		*p='\0';

				if(fd==-1){
					perror("open()");
					continue;
				}
				memset(buf,0,LEN_DESC);
				
				len=read(fd,buf,LEN_DESC);

				if(len<0)
				{
					perror("read()");
					close(fd);
					continue;
				}
				
				p=strchr(buf,'\n');
				p='\0';
			//	size=sizeof(sNode)+strlen(buf);				
				pnew=malloc(sizeof(sNode));
				memset(pnew->desc,'\0',LEN_DESC);
				strcpy(pnew->desc,buf);puts(buf);
				pnew->chnid=i+1;
				memcpy(sbuf+i*sizeof(chnid_t)+i*LEN_DESC+i*LEN_MGROUP,&(pnew->chnid),sizeof(chnid_t));
				memcpy(sbuf+(i+1)*sizeof(chnid_t)+i*LEN_DESC+i*LEN_MGROUP,pnew->desc,LEN_DESC);
memcpy(sbuf+(i+1)*sizeof(chnid_t)+(i+1)*LEN_DESC+i*LEN_MGROUP,(chn_bg+i)->mgroup,LEN_MGROUP);
				free(pnew);
			}
		}
	}
	if(send(sd,sbuf,BUFSIZE,0)<0)	
	{
		perror("send()");
		exit(1);
	}
	globfree(&glob_res);
}

void send_channel_list()
{
	int sd, newsd;
	struct sockaddr_in laddr, raddr;
	socklen_t raddr_len;
	char ipstr[IPSTRSIZE];

	sd = socket(AF_INET, SOCK_STREAM, 0/* IPPROTO_TCP, IPPROTO_SCTP */);
	if (sd<0) {
		perror("socket()");
		exit(1);
	}

	static int val=1;
	if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val))<0) {
		perror("setsockopt(SO_REUSEADDR,)");
	}

	laddr.sin_family = AF_INET;
	laddr.sin_port = htons(atoi(RCVPORT));
	inet_pton(AF_INET, "0.0.0.0", &laddr.sin_addr);
	if (bind(sd, (void*)&laddr, sizeof(laddr))<0) {
		perror("bind()");
		exit(1);
	}

	if (listen(sd, 200)<0) {
		perror("listen()");
		exit(1);
	}

	raddr_len = sizeof(raddr);
	while (1) {
		newsd = accept(sd, (void*)&raddr, &raddr_len);
		if (newsd<0) 
		{
			perror("accept()");
			exit(1);
		}
		inet_ntop(AF_INET, &raddr.sin_addr, ipstr, IPSTRSIZE);
		printf("Client: %s:%d\n", ipstr, ntohs(raddr.sin_port));
		create_channel_list(newsd);
		close(newsd);
	}
	close(sd);
	exit(0);
}
