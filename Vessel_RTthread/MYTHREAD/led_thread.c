#include "rtthread.h"
#include "led.h"
#include "led_thread.h"

//for test

static rt_thread_t led0_thread = RT_NULL;
static rt_thread_t led1_thread = RT_NULL;

static void led0_thread_entry(void* parameter)
{
    while(1)
    {
        LED0=!LED0;
        rt_thread_delay(500);
    }
}

static void led1_thread_entry(void* parameter)
{
    while(1)
    {
        LED1=!LED1;
        rt_thread_delay(200);
    }
}

void led_thread_init(void)
{
    led0_thread = 
    rt_thread_create("led0",
                    led0_thread_entry,
                    RT_NULL,
                    512,    //stack size
                    5,      //priority
                    20);    //slice
//    rt_thread_startup(led0_thread);
    
    led1_thread = 
    rt_thread_create("led1",
                    led1_thread_entry,
                    RT_NULL,
                    512,    //stack size
                    5,      //priority
                    20);    //slice
//    rt_thread_startup(led1_thread);
}
