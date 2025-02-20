#include "stm32f10x.h"                  // Device header
#include "math.h"
#include "MPU6050.h"



float get_pitch(float current_pitch)
{
	int16_t AX, AY, AZ, GX, GY, GZ;
	// 获取MPU6050的数据
    MPU6050_GetData(&AX, &AY, &AZ, &GX, &GY, &GZ);
	
	// 调整漂移
	AZ += 1400;
	AY += 100;
	
	/* 解算 */
	float FAZ = AZ / 16384.0;
	float FAY = AY / 16384.0;
	
	// 仅使用加速度计计算俯仰角（Pitch）
	float pitch = atan2(FAY, FAZ) * 180 / 3.14; // 转换为度数
	current_pitch = pitch;
	pitch = pitch*0.5 + current_pitch*0.5;
	
	return pitch;
}
