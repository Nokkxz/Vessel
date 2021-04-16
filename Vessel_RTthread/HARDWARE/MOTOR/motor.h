#ifndef __MOTOR_H
#define __MOTOR_H
#include "sys.h"

#define MOTOR_MOVE_FORWARD              1<<0
#define MOTOR_MOVE_LEFT                 1<<1
#define MOTOR_ROTATE_CLOCKWISE          1<<2

void motor_init(void);
void motor_act(u8 mode, u8 gear);

#endif
