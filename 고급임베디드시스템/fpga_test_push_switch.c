#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <signal.h>


#define MAX_BUTTON 9

#include "./fpga_dot_font.h"
#define FPGA_DOT_DEVICE "/dev/fpga_dot"

unsigned char quit = 0;

void user_signal1(int sig)
{
	quit = 1;
}

int main(void)
{
	int i;
	int dev1;
	int dev2;
	int buff_size;
	int set_num;
	int test;
	unsigned char push_sw_buff[MAX_BUTTON];    //device 파일을 열고, 사용자의 입력에 따라 드라이버를 이용해서 출력 

	dev1 = open("/dev/fpga_push_switch", O_RDWR);   //key Device file open
	if(dev1 < 0){
		printf("Device Open Error\n");
		close(dev1);
		return -1;
	}

	dev2 = open(FPGA_DOT_DEVICE, O_WRONLY);                     //device 파일을 열고,사용자의 입력에 따라 드라이버를 이용해서 출력
	if(dev2<0){
		printf("Device open error : %s\n", FPGA_DOT_DEVICE);
		exit(1);
	}


	(void)signal(SIGINT, user_signal1);

	buff_size = sizeof(push_sw_buff);
	printf("Press <ctrl+c> to quit.\n");

	while(!quit){
		usleep(400000);
		read(dev1, &push_sw_buff, buff_size);
	
		for(i=0;i< MAX_BUTTON; i++)
		{
			test =push_sw_buff[i];
			if(test ==1)
			{

		//printf("[%d]", push_sw_buff[i]);
		//set_num = push_sw_buff[i];
				set_num = i+1;
				str_size = sizeof(fpga_number[set_num]);
				write(dev2,fpga_number[set_num],str_size);

		//printf("\n");
			}
		}
	}

	close(dev1);
	close(dev2);

	return 0;
}
