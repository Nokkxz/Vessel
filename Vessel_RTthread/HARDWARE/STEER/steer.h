#ifndef __STEER_H
#define __STEER_H
#include "sys.h"

void steer_init(void);
void servo_release(float degree);
void servo_grab(float degree);
void servo_control(int servo_tag, float degree);

#endif
