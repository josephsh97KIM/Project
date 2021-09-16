#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <sys/ioctl.h>
#include <signal.h>

#define MOTOR_ATTRIBUTE_ERROR_RANGE 4
#define FPGA_STEP_MOTOR_DEVICE "/dev/fpga_step_motor"
#define BUZZER_DEVICE "/dev/fpga_buzzer"

unsigned char quit = 0;

void user_signal1(int sit)
{
	quit = 1;
}

void usage(char* dev_info); 

int main(int argc, char **argv)
{
	int i;
	int dev;
	int str_size;

	int motor_action;
	int motor_direction;
	int motor_speed;


	unsigned char motor_state[3];
	
	memset(motor_state,0,sizeof(motor_state));

	if(argc!=4) {
		printf("Please input the parameter! \n");
		usage(argv[0]);
		return -1;
	}

	motor_action = atoi(argv[1]);  //모터 onoff
	if(motor_action<0||motor_action>1) {
		printf("Invalid motor action!\n");
		usage(argv[0]);
		return -1;
	}
	
	motor_direction = atoi(argv[2]);  //모터 방향
	if(motor_direction<0||motor_direction>1) {
		printf("Invalid motor direction!\n");
		usage(argv[0]);
		return -1;
	}
	
	motor_speed = atoi(argv[3]);      //모터 속도
	if(motor_speed<0||motor_speed>255) {
		printf("Invalid motor speed!\n");
		usage(argv[0]);
		return -1;
	}
	
	motor_state[0]=(unsigned char)motor_action;   //./fpga_step_motor  [0] [1] [2] 여기서 [0]은 0은 정지,1은 구동 
	motor_state[1]=(unsigned char)motor_direction;; //[1]은 모터 방향 0은 정지,1은 구동
	motor_state[2]=(unsigned char)motor_speed;      //[2]은 모터 속도로 인자값은 5로 최대 255까지 작동

	dev = open(FPGA_STEP_MOTOR_DEVICE, O_WRONLY);
	if (dev<0) {
		printf("Device open error : %s\n",FPGA_STEP_MOTOR_DEVICE);
		exit(1);
	}
	
	write(dev,motor_state,3);


	close(dev);
	
	return 0;
}


void usage(char* dev_info) 
{
	printf("<Usage> %s [Motor Action] [Motor Diretion] [Speed]\n",dev_info);
	printf("Motor Action : 0 - Stop / 1 - Start\n");
	printf("Motor Direction : 0 - Left / 1 - Right\n");
	printf("Motor Speed : 0(Fast) ~ 250(Slow)\n");
	printf("ex) %s 1 0 10\n",dev_info);
}





void set_motor_action( m1,  m2,  m3)
{
	int motor_action =0;
	int motor_direction =0;
	int motor_speed = 0;
	int dev_m;
	int dev_b;

	unsigned char motor_state[3];
	
	memset(motor_state,0,sizeof(motor_state));

	motor_action =m1;
	motor_direction =m2;
	motor_speed =m3;

	motor_state[0]=(unsigned char)motor_action;   //./fpga_step_motor  [0] [1] [2] 여기서 [0]은 0은 정지,1은 구동 
	motor_state[1]=(unsigned char)motor_direction;; //[1]은 모터 방향 0은 정지,1은 구동
	motor_state[2]=(unsigned char)motor_speed;      //[2]은 모터 속도로 인자값은 5로 최대 255까지 작동
	
	dev_m = open(FPGA_STEP_MOTOR_DEVICE, O_WRONLY);
	dev_b = open(BUZZER_DEVICE, O_RDWR);
	if (dev_m<0) {
		printf("Device open error : %s\n",FPGA_STEP_MOTOR_DEVICE);
		exit(1);
	}
	if(dev_b < 0){
		printf("Device open error : %s\n",BUZZER_DEVICE);
		exit(1);
	}
	(void)signal(SIGINT, user_signal1);

	write(dev_m,motor_state,3);
	
	
	
	//for()문작성 필요?

	memset(motor_state,0,sizeof(motor_state);
	motor_state[0]= (unsigned char)motor_action;
	usleep(100);
	
	write(dev_m,motor_state,3);

		while(!quit){
		if(state != 0){
			state = 0;
			data = 1;
			retval = write(dev_b, &data, 1); //부저가 울리는 write코드문
			if(retval < 0){
				printf("Write Error! \n"); //buzzer구동시에는 ./fpga_test_buzzer라고 치는데 write 오류가 생길시 나온다.
				return -1;
			}
		}
		else{
			state = 1;
			data = 0;
			retval = write(dev_b, &data, 1);
			if(retval < 0){
				printf("Write Error!\n");
				return -1;
			}
		}
		sleep(1);
	}

	printf("Current Buzzer Value : %d\n",data);
	close(dev_b);

	
	
	close(dev_m);
	
	return 0;
}
