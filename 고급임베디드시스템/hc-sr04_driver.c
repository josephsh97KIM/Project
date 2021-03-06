/* Achro-i.MX6Q External Sensor GPIO Control
FILE : hc-sr04_driver.c
AUTH : gmlee@huins.com */

#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/fs.h>
#include <linux/gpio.h>
#include <linux/delay.h>
#include <linux/kdev_t.h>
#include <linux/interrupt.h>

MODULE_LICENSE("GPL");

#define HCSR04_ECHO IMX_GPIO_NR(2, 3)      //28번핀
#define HCSR04_TRIGGER IMX_GPIO_NR(2, 2)   //26번핀

static int us_major=0, us_minor=0;
static int result, res;
static dev_t us_dev;
static struct cdev us_cdev;

struct timeval after, before;
u32 irq = -1;

static int us_register_cdev(void);
static int us_open(struct inode *inode, struct file *filp);
static int us_release(struct inode *inode, struct file *filp);
static int us_read(struct file *filp, char *buf, size_t count, loff_t *f_pos);

void output_sonicburst(void);
int gpio_init(void);
//static irqreturn_t ultrasonics_echo_interrupt(int irq, void *dev_id, struct pt_regs *regs);

static irqreturn_t ultrasonics_echo_interrupt(int irq, void *dev_id, struct pt_regs *regs)  //인터럽트가 걸리면 아래 핸들러가 실행
{
	if(gpio_get_value(HCSR04_ECHO))
	{
		do_gettimeofday( &before);   //절대시간 얻어온다.
		}
		else
		{
			do_gettimeofday( &after );

			printk(KERN_ALERT" Distance : %.0ld [cm] \n ", (after.tv_usec -
before.tv_usec) / 58);
			memset(&before, 0 , sizeof(struct timeval ) );
			memset(&after , 0 , sizeof(struct timeval ) );
		}

		return IRQ_HANDLED;      
}

static int us_open(struct inode *inode, struct file *filp)
{
	printk(KERN_ALERT "< Device has been opened >\n");
	
	return 0;
}
static int us_release(struct inode *inode, struct file *filp)
{
	printk(KERN_ALERT "< Device has been closed > \n");
		
	return 0;
}
static int us_read(struct file *filp, char *buf, size_t count, loff_t *f_pos)
{
	output_sonicburst();
	mdelay(1);
	return 0;
}
struct file_operations us_fops = {
	.open = us_open,
	.release = us_release,
	.read = us_read,
};

static int us_init(void)
{
	printk(KERN_ALERT "< Ultrasonic Module is up > \n");
	if((result = us_register_cdev())<0)
	{
		printk(KERN_ALERT "< Ultrasonic Register Fail > \n");
		return result;
	}

	res = gpio_init();
	if(res < 0 )
		return -1;
	return 0;
}

static void us_exit(void)
{
	printk(KERN_ALERT "< Ultrasonic Module is down > \n");
	free_irq(irq, NULL);
	gpio_free(HCSR04_TRIGGER);
	gpio_free(HCSR04_ECHO);
	cdev_del(&us_cdev);
	unregister_chrdev_region(us_dev,1);
}
void output_sonicburst(void)
{
	gpio_set_value(HCSR04_TRIGGER, 1);   //Echo 쪽 신호가 HIGH로 상승하게 되는데 이 때 인터럽트가 걸리게 된다.
	udelay(10);                          //Trigger PIN에 10us동안 HIGH 신호를 준다.
	gpio_set_value(HCSR04_TRIGGER, 0);
}

int gpio_init(void)
{
	int rtc;
	
	rtc=gpio_request(HCSR04_TRIGGER,"TRIGGER");
	if (rtc!=0) {
		printk(KERN_ALERT "<Trigger Pin Request Fail>\n");
		goto fail;
	}

	rtc=gpio_request(HCSR04_ECHO,"ECHO");
	if (rtc!=0) {
		printk(KERN_ALERT "<Echo Pin Request Fail>\n");
		goto fail;
	}
	
	rtc=gpio_direction_output(HCSR04_TRIGGER,0);
	if (rtc!=0) {
		printk(KERN_ALERT "<Trigget pin Setting Fail>\n");
		goto fail;
	}

	rtc=gpio_direction_input(HCSR04_ECHO);
	if (rtc!=0) {
		printk(KERN_ALERT "<Echo Pin Setting Fail>\n");
		goto fail;
	}

	rtc=gpio_to_irq(HCSR04_ECHO);        
	if (rtc<0) {
		printk(KERN_ALERT "<irq Pin GPIO Request Fail>\n");
		goto fail;
	} else {
		irq=rtc;
	}
	
	rtc = request_irq(irq, (void*)ultrasonics_echo_interrupt, IRQF_TRIGGER_RISING |   //irq:인터럽트 번호
IRQF_TRIGGER_FALLING | IRQF_DISABLED , "us", NULL);
	
	if(rtc) {
		printk(KERN_ALERT "<irq Register Fail>\n");
		goto fail;
	}

	printk(KERN_INFO "HC-SR04 Enable\n");
	gpio_set_value(HCSR04_TRIGGER,0);
	return 0;
fail:
	return -1;
}

static int us_register_cdev(void)
{
	int error;
	
	if(us_major) {
		us_dev = MKDEV(us_major, us_minor);
		error = register_chrdev_region(us_dev,1,"us");
	}else{
		error = alloc_chrdev_region(&us_dev,us_minor,1,"us");
		us_major = MAJOR(us_dev);
	}
	
	if(error<0) {
		printk(KERN_WARNING "us: can't get major %d\n", us_major);
		return result;
	}

	printk(KERN_ALERT "major number = %d\n", us_major);
	
	cdev_init(&us_cdev, &us_fops);
	us_cdev.owner = THIS_MODULE;
	us_cdev.ops = &us_fops;
	error = cdev_add(&us_cdev, us_dev, 1);
	
	if(error)
	{
		printk(KERN_NOTICE "us Register Error %d\n", error);
	}
	return 0;
}

MODULE_AUTHOR("gunmin, lee <gmlee@huins.com>");
MODULE_DESCRIPTION("HUINS ext sensor Device Driver");
MODULE_LICENSE("GPL");

module_init(us_init);
module_exit(us_exit);