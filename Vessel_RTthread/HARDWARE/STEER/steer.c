#include "steer.h"
#include "usart.h"
 	  

// TIM2 PWM部分初始化 
// PWM输出初始化
// arr：自动重装值
// psc：时钟预分频数
// Tim2 PA 0 1 2 3
// Tim4 PB 6 7 8 9
// Tim3 PA 6 7 PB 0 1

void steer_init(void)
{
    u16 psc=71, arr=19999;
    
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	TIM_OCInitTypeDef  TIM_OCInitStructure;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);  

	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0; //TIM_CH1
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1; //TIM_CH2
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //TIM_CH2
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; //TIM_CH2
	GPIO_Init(GPIOA, &GPIO_InitStructure);

	TIM_TimeBaseStructure.TIM_Period = arr;
	TIM_TimeBaseStructure.TIM_Prescaler = psc;
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
 	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OC1Init(TIM2, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM2, TIM_OCPreload_Enable);
	TIM_OC2Init(TIM2, &TIM_OCInitStructure);
	TIM_OC2PreloadConfig(TIM2, TIM_OCPreload_Enable);
	TIM_OC3Init(TIM2, &TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM2, TIM_OCPreload_Enable);
	TIM_OC4Init(TIM2, &TIM_OCInitStructure);
	TIM_OC4PreloadConfig(TIM2, TIM_OCPreload_Enable);
    
	TIM_Cmd(TIM2, ENABLE);
    
    //float cmp_val = 0.075 * 19999; duty_ratio 1500us*50Hz=0.075
    
    TIM_SetCompare1(TIM2, 1500);
	TIM_SetCompare2(TIM2, 1500);
	TIM_SetCompare3(TIM2, 1500);
	TIM_SetCompare4(TIM2, 1500);
}

float degree2cmp_val(float degree)
{
	//! (0 -- 180) -> (25 -- 125)
	float temp = degree / 180 * 100 + 25;
	return temp / 1000 * 19999;
}

void servo_control(int servo_tag, float degree)
{
	float cmp_val = degree2cmp_val(degree);
	printf("%.2f\r\n", cmp_val);
	switch (servo_tag)
	{
	case 0:
		TIM_SetCompare1(TIM2, cmp_val);
		break;
	case 1:
		TIM_SetCompare2(TIM2, cmp_val);
		break;
	case 2:
		TIM_SetCompare3(TIM2, cmp_val);
		break;
	case 3:
		TIM_SetCompare4(TIM2, cmp_val);
		break;
	}
}
void servo_grab(float degree)
{
	servo_control(0, degree);
	servo_control(1, degree);
}

void servo_release(float degree)
{
	servo_grab(-degree);
}
