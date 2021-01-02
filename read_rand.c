#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <time.h>
#include <fcntl.h>

#define SUFFLE_NUM 10000 // 이 값은 마음대로 수정할 수 있음

void GenRecordSequence(int *list, int n);
void swap(int *a, int *b);

int main(int argc, char **argv)
{
	struct timeval before;
	struct timeval after;
	int *read_order_list = NULL;
	int num_of_records;
	int fd;
	off_t fsize;
	char *buf=NULL;
	long operating_time;

	if(argc!=2){
		fprintf(stderr, "usage: %s <filename>\n",argv[0]);
		exit(1);}

	if((fd=open(argv[1],O_RDONLY))<0){
		fprintf(stderr,"open error for %s\n", argv[1]);
		exit(1);
	}

	fsize = lseek(fd,0,SEEK_END);
	num_of_records = fsize/100; //전체 레코드의 개수
	buf = malloc(fsize+ 1);

	read_order_list = (int*)calloc(num_of_records,sizeof(int));

	GenRecordSequence(read_order_list, num_of_records);
	
	if((gettimeofday(&before, NULL))<0) //읽기 전 시간
		fprintf(stderr, "time error");
	for(int i=0;i<num_of_records;i++){ 
		lseek(fd,((read_order_list[i])*100),SEEK_SET);
		read(fd,buf,100);	} 
	if((gettimeofday(&after,NULL))<0) //읽은 후 시간
		fprintf(stderr,"time error");
	operating_time = (after.tv_sec-before.tv_sec)*1000000+(after.tv_usec-before.tv_usec);

	printf("#records: %d ",num_of_records);
	printf("timecost: %ld us\n",operating_time);	
	free(read_order_list);
	free(buf);
	return 0;
}

void GenRecordSequence(int *list, int n)
{
       	int i, j, k;
	srand((unsigned int)time(0));
	
	for(i=0; i<n; i++){
		list[i] = i;}
       	for(i=0; i<SUFFLE_NUM; i++){
		j = rand() % n;
		k = rand() % n;
		swap(&list[j], &list[k]);
	}
	return;
}

void swap(int *a, int *b)
{
	int tmp;
	tmp = *a;
	*a = *b;
	*b = tmp;
	return;
}
