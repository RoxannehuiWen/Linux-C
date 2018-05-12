#include "../include/thr_chnnel.h"
#include "../include/proto.h"

extern unsigned int cn;

int main()
{
	pthread_t tid[NR_CHN];
	int i=0,err;
	init_channel_filename();
	printf("cn=%d\n",cn);
	module_load();

	for (i=0;i<cn;++i)
	{
		puts("ii");
		err = pthread_create(tid+i, NULL, send_music_udp,chn_bg+i);
		printf("%d\n",err);
		if (err) 
		{
			fprintf(stderr, "pthread_create(): %s\n", strerror(err));
			exit(1);
		}
	}

	send_channel_list();
	for (i=0;i<cn;++i) {
		pthread_join(tid[i], NULL);
	}	
	module_unload();
	exit(0);
}
