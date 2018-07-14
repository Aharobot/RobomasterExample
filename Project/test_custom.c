#include "execute_task.h"
#include "can_device.h"
#include "uart_device.h"
#include "pid.h"
#include "sys.h"

//leftΪ���ҡ��
//rightΪ�ұ�ҡ��


int16_t test_moto_speed_right = 0;
int16_t test_moto_speed_left = 0;
int16_t test_moto_current[2];
uint8_t test_servo;
uint8_t key1;

void moto_control(void)
{
	//LED���ƺ���
	write_led_io(LED_IO1, LED_ON);	
	
	//������ٶȸ���
	test_moto_speed_right = rc.ch2 / RC_MAX_VALUE * MAX_WHEEL_RPM;
	test_moto_speed_left = rc.ch4 / RC_MAX_VALUE * MAX_WHEEL_RPM;
	
	
	//�ջ�����������
	test_moto_current[0] = pid_calc(&pid_wheel_spd[0], moto_chassis[0].speed_rpm, test_moto_speed_right);
	test_moto_current[1] = pid_calc(&pid_wheel_spd[1], moto_chassis[1].speed_rpm, test_moto_speed_left);
	
	//���͵���ĵ���
	set_test_motor_current_left(test_moto_current);
	
	
	
	//������ƺ��������趨
	set_pwm_group_param(PWM_GROUP1, 20000);
	
	//�������ƶ˿�
	start_pwm_output(PWM_IO1);
    
	//�����������
		if(test_servo == 0)
	{
		set_pwm_param(PWM_IO1, 2200);
	}
	else
	{
		set_pwm_param(PWM_IO1, 1500);
	}
   

	//  ��չ��İ������Ƶ��
	//      read_key_io(KEY_IO1,&key1);  
	//			if(key1 ==1)
	//		{
	//			 set_test_motor_current(test_moto_current);
	//			}
			
			
}
//�����ʼ�������趨
void test_moto_init(void)
{
	//PID������ʼ��		 
	pid_init(&pid_test_moto, 7000, 0, 1, 0, 0);

}
void left_moto_init(void)
{
	//PID������ʼ��		 
	pid_init(&pid_wheel_spd[0], 7000, 0, 1, 0, 0);
}
void right_moto_init(void)
{
	//PID������ʼ��		 
	pid_init(&pid_wheel_spd[1], 7000, 0, 1, 0, 0);
}
