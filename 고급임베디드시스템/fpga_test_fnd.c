#include <stdio.h>

#include <stdlib.h>

#include <unistd.h>

#include <sys/types.h>

#include <sys/stat.h>

#include <fcntl.h>

 

#include <string.h>

 

#define MAX_DIGIT 4

#define FND_DEVICE "/dev/fpga_fnd"

   

int main(int argc, char **argv)

{                                 //fnd device file open

   int dev;

   unsigned char data[4];

   unsigned char retval;

   int i;

   int a;

   int str_size;                   //����ڰ� �Է��� ���ڸ� �м��Ͽ�, device driver���� ��� ��û

 

   memset(data, 0, sizeof(data)); //memory set=0

 

   if(argc != 1){

      printf("please input the parameter! \n");

      printf("ex)./test_led a1\n");

      return -1;

   }

		str_size = (strlen(argv[1]));
        if(str_size>MAX_DIGIT)
        {
                printf("Warning! 4 Digit number only! \n");
                str_size = MAX_DIGIT;
        }

        for(i=0; i<str_size; i++)
        {
                if((argv[1][i]<0x30)||(argv[1][i])>0x39){
                        printf("Error! Invalid Value!\n");
                        return -1;
                }
                data[i] = argv[1][i]-0x30;
        }

 

   dev = open(FND_DEVICE, O_RDWR); //����̽� �ȿ���������(dev<0) error , fnd deive file open

   if(dev<0){

      printf("Device open error : %s\n", FND_DEVICE);

      exit(1);

   }

 
   //data[0] = 0x00;
   //data[1] = 0x00;
   //data[2] = 0x00;
   //data[3] = 0x00;

   for (a=0 ; a<9999 ; a++){


   retval = write(dev, &data, 4);//����ڰ� �Է��� ���ڸ� �м��Ͽ�, device driver���� ��� ��û

   if(retval<0){

      printf("Write Error!\n");

      return -1;

   }

 

   memset(data, 0, sizeof(data)); //�޸� ���� �����Ѵ�. �� data�� 0���� �����Ѵ�.

 

   sleep(1);

 

   retval = read(dev, &data, 4); // dev�κ��� data�ּҰ��� 4����Ʈ ���� ������

   if(retval<0){

      printf("Read Error!\n");

      return -1;

   }

 
   
   printf("Current FND Value : ");

   for(i=0; i<str_size; i++)

      printf("%d", data[i]);

   printf("\n");

   data[3]=data[3]+0x01;

   //���׸�Ʈ (����)�� �����ϱ�

    if (data[3]==10){

      data[3]=0x00;

      data[2]+=0x01;

      if (data[2]==10){

         data[2]=0x00;

         data[1]+=0x01;

            if (data[1]==10){         

               data[1]=0x00;

               data[0]+=0x01;

               if (data[0]==10){

                  data[0]=0x00; //data[i]������ ��� 0����

                  //data[0],data[2],data[1],data[3]=0x00;

               }

            }

            

      }

     }

	if(a==9999){
		a = 0;
		memset(data, 0, sizeof(data));
	}

   }
   
   close(dev);

 

   return(0);

}