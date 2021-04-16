#ifndef __GPS_THREAD_H__
#define __GPS_THREAD_H__

#include "gps.h"
#include "rtthread.h"
#include "usart3.h"

#define GPS_TX_BUF_LEN  100

extern u8 gps_rx_buf[USART3_MAX_RECV_LEN];
extern u8 gps_tx_buf[GPS_TX_BUF_LEN];

extern nmea_msg gps_info;
extern rt_sem_t gps_sem;
void gps_thread_init(void);

#endif
