#include "gps_thread.h"
#include "rtthread.h"
#include "gps.h"
#include "usart3.h"
#include "usart.h"
#include "led.h"

u8 gps_rx_buf[USART3_MAX_RECV_LEN];
u8 gps_tx_buf[GPS_TX_BUF_LEN];

nmea_msg gps_info;

static rt_thread_t gps_thread = RT_NULL;
rt_sem_t gps_sem = RT_NULL;

static void gps_thread_entry(void* parameter)
{
    u16 rxlen, i;
    while(1)
    {
        rt_sem_take(gps_sem, RT_WAITING_FOREVER);
        
        rxlen=USART3_RX_STA&0X7FFF;	//得到数据长度
		for(i=0;i<rxlen;i++)gps_rx_buf[i]=USART3_RX_BUF[i];	   
 		USART3_RX_STA=0;		   	//启动下一次接收
		GPS_Analysis(&gps_info,(u8*)gps_rx_buf);//分析字符串
        
        
        
        while(USART_GetFlagStatus(USART1,USART_FLAG_TC)==RESET);
		USART_SendData(USART1,gps_info.svnum);
        
        LED1=!LED1;
        rt_thread_delay(1);
    }
}

void gps_thread_init(void)
{
    gps_sem = rt_sem_create("gps_sem", 0, RT_IPC_FLAG_FIFO);
    
    gps_thread = 
    rt_thread_create("gps",
                    gps_thread_entry,
                    RT_NULL,
                    512,    //stack size
                    5,      //priority
                    20);    //slice
    rt_thread_startup(gps_thread);
}
