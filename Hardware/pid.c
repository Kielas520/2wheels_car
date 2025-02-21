#include "stm32f10x.h" 
#include "pid.h"
#include "Encoder.h"
#include "Motor.h"

pid_t motorA;
pid_t motorB;
pid_t angle;

void pid_Init(pid_t *pid, uint32_t mode, float p, float i, float d)
{
                 // Device header
	pid->pid_mode = mode;
	pid->p = p;
	pid->i = i;
	pid->d = d;
}

void angle_pid_control(pid_t *pid, float pitch)
{
	// 计算输出
	angle.now = pitch;

	// 输入PID控制器进行计算
	pid_cal(&angle);

	// angle输出限幅
	pidout_limit(&angle);	

	// PID输出值 输入给电机PID控制器
	motorA.target = angle.out;
	motorB.target = angle.out;
}

void speed_pid_controlA()
{
	// 计算输出
	motorA.now = EncoderA_Get();

	// 输入PID控制器进行计算
	pid_cal(&motorA);

	// 电机输出限幅
	pidout_limit(&motorA);

	// PID输出值 输入给电机
	Motor_SetSpeedA(motorA.out);
}

void speed_pid_controlB()
{
	// 计算输出
	motorB.now = EncoderB_Get();
	
	// 输入PID控制器进行计算
	pid_cal(&motorB);
	
	// 电机输出限幅
	pidout_limit(&motorB);	

	// PID输出值 输入给电机
	Motor_SetSpeedB(motorB.out);
}

void pid_cal(pid_t *pid)
{
	// 计算当前偏差
	pid->error[0] = pid->target - pid->now;

	// 计算输出
	if(pid->pid_mode == DELTA_PID)  // 增量式
	{
		pid->pout = pid->p * (pid->error[0] - pid->error[1]);
		pid->iout = pid->i * pid->error[0];
		pid->dout = pid->d * (pid->error[0] - 2 * pid->error[1] + pid->error[2]);
		pid->out += pid->pout + pid->iout + pid->dout;
	}
	else if(pid->pid_mode == POSITION_PID)  // 位置式
	{
		pid->pout = pid->p * pid->error[0];
		pid->iout += pid->i * pid->error[0];
		pid->dout = pid->d * (pid->error[0] - pid->error[1]);
		pid->out = pid->pout + pid->iout + pid->dout;
	}

	// 记录前两次偏差
	pid->error[2] = pid->error[1];
	pid->error[1] = pid->error[0];

}

void pidout_limit(pid_t *pid)
{
	if(pid !=&angle)
	{
		// 限制电机速度范围
		if (pid->out > MAX_SPEED) 
			pid->out = MAX_SPEED; // 设置最大正速度
		else if (pid->out < -MAX_SPEED) 
			pid->out = -MAX_SPEED; // 设置最大负速度
	}
	else
	{
		// 限制angle范围
		if (pid->out > MAX_ANGLE) 
			pid->out = MAX_ANGLE; // 设置最大正速度
		else if (pid->out < -MAX_ANGLE) 
			pid->out = -MAX_ANGLE; // 设置最大负速度
	}
}

