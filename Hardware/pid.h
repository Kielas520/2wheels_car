#ifndef __PID_h_
#define __PID_h_

#define MAX_SPEED 130
#define MAX_ANGLE 50

enum
{
  POSITION_PID,  
  DELTA_PID,    
};

typedef struct
{
	float target;	
	float now;
	float error[3];		
	float p,i,d;
	float pout, dout, iout;
	float out;   
	
	uint32_t pid_mode;

}pid_t;


void pid_Init(pid_t *pid, uint32_t mode, float p, float i, float d);
void angle_pid_control(pid_t *pid, float pitch);
void speed_pid_controlA(void);
void speed_pid_controlB(void);
void pid_cal(pid_t *pid);
void pidout_limit(pid_t *pid);

#endif
