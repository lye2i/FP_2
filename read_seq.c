#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
	struct timeval before;
	struct timeval after;
	int fd;
	off_t fsize;
	int record_nums;
	char *buf=NULL;
	long operating_time;

	if(argc!=2) {
		fprintf(stderr, "usage: %s <filename>\n",argv[0]);
		exit(1);
	}

	if((fd=open(argv[1],O_RDONLY))<0){ 
		fprintf(stderr,"open error for %s\n", argv[1]);
		exit(1);
	}

	fsize = lseek(fd, 0, SEEK_END);
	record_nums = fsize/100; //전체 레코드의 개수
	lseek(fd,0,SEEK_SET);
	buf = malloc(fsize+ 1);

	if((gettimeofday(&before, NULL))<0)
		fprintf(stderr,"time error\n"); //읽기 전 시간
	
	for(int i=0; i<record_nums; i++){
		read(fd,buf,100);}//레코드의 크기가 100바이트 이므로 100바이트씩 순차적으로 읽는다. 
	if((gettimeofday(&after,NULL))<0) //읽은 후 시간
		fprintf(stderr,"time error\n");
       
	operating_time = (after.tv_sec-before.tv_sec)*1000000+(after.tv_usec-before.tv_usec);

        printf("#records: %d ",record_nums);
        printf("timecost: %ld us\n",operating_time);
	free(buf);
	return 0;
}

