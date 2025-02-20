#ifndef __PID_h_
#define __PID_h_

#define MAX_DUTY 100
#define MAX_ANGLE 57

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
void speed_pid_control(pid_t *pid);

void pid_cal(pid_t *pid);
void pidout_limit(pid_t *pid);

#endif
