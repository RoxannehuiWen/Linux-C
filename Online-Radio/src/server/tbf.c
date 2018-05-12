#include "../include/proto.h"

pthread_mutex_t mut_job=PTHREAD_MUTEX_INITIALIZER;
pthread_once_t init_once = PTHREAD_ONCE_INIT;
struct tbf_st *job[TBF_MAX];
pthread_t tid_alrm;

static void *thr_alrm(void *unused)
{
	int i;
	while(1)
	{
		
		pthread_mutex_lock(&mut_job);

		for(i=0;i<TBF_MAX;i++)
			if(job[i]!=NULL)
			{
				pthread_mutex_lock(&job[i]->mut);

				job[i]->token+=job[i]->cps;
				if(job[i]->token>job[i]->burst)
				{
					job[i]->token=job[i]->burst;
				}
				pthread_cond_broadcast(&job[i]->cond);
				pthread_mutex_unlock(&job[i]->mut);
			}
		pthread_mutex_unlock(&mut_job);
		sleep(1);
	}
}

static int get_free_pos_unlock(void)
{
	int i;
	for(i=0;i<TBF_MAX;++i)
	{
		if(job[i]==NULL)
		{
			puts("get_free_pos");
			return i;
		}
	}
	return -1;
}

void module_unload(void)
{
	int i;
	pthread_cancel(tid_alrm);
	pthread_join(tid_alrm,NULL);
	for(i=0;i<TBF_MAX;++i)
		free(job[i]);
}

void module_load(void)
{
	int err;
		
	if(err=pthread_create(&tid_alrm,NULL,thr_alrm,NULL))
	{
		fprintf(stderr,"pthread_create():%s\n",strerror(err));
		exit(1);
	}
	//atexit(module_unload);
}

tbf_t *tbf_init(int cps,int burst,struct tbf_st *me)
{
	int pos;
	//pthread_once(&init_once,module_load);
	me=malloc(sizeof(*me));
	if(me==NULL)
	{
		perror("malloc()");
		return NULL;
	}
	me->token=0;
	me->cps=cps;
	me->burst=burst;
	pthread_mutex_lock(&mut_job);
	pos=get_free_pos_unlock();
	if(pos<0)
	{
		pthread_mutex_unlock(&mut_job);
		free(me);
		return NULL;
	}
	me->pos=pos;
	job[pos]=me;
	pthread_mutex_unlock(&mut_job);

	return me;
}

int tbf_destroy(tbf_t *p)
{
	struct tbf_st *me=p;
	pthread_mutex_lock(&mut_job);
	job[me->pos]=NULL;
	pthread_mutex_unlock(&mut_job);
	free(p);
	return 0;
}

static int min(int a,int b)
{
	if(a<b)
		return a;
	return b;

}

int tbf_fetchtoken(tbf_t *p,int size)
{
	struct tbf_st *me=p;
	int n;
	if(size<0)
		return -EINVAL;

	pthread_mutex_lock(&me->mut);
	while(me->token<=0){
		pthread_cond_wait(&me->cond,&me->mut);
	}
	n=min(me->token,size);
	me->token-=n;
	pthread_mutex_unlock(&me->mut);
	return n;
}

int tbf_returntoken(tbf_t *p,int size)
{
	struct tbf_st *me=p;
	if(size<0)
		return -EINVAL;

	pthread_mutex_lock(&mut_job);
	me->token+=size;
	pthread_cond_broadcast(&me->cond);
	pthread_mutex_unlock(&mut_job);
	return size;
}
