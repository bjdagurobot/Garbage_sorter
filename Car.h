#ifndef Car_h
#define Car_h
class Car{
private:
	//定义引脚，L_IN1和R_IN3分别为小车前进时IN1和IN3的电平
	int IN1, IN2, IN3, IN4, MotorA, MotorB, L_IN1, R_IN3;

public:
	//构造函数，默认L_IN1和R_IN3为1
	Car(int a, int b, int c, int d, int e, int f);
	//将引脚配置为输出
	void Mode();
	//控制数字引脚电平，进而控制左右轮旋转方向
	void Digital_out(int a, int b, int c, int d);
	//控制PWM引脚，进而控制左右轮速度
	void Analog_out(int a, int b);
	//可设置小车前进时IN1和IN3的电平，以此对Move函数进行修正
	void Infer(int a, int b);
	/*第一，二个形参分别表示MotorA和MotorB的PWM，第三个形参为小
	车运动的方式，取值为1至9，分别表示单边左后转，后退，单边右后
	转，双边左转，停止，双边右转，单边左前转，前进，单边右前转，
	第四个形参表示延迟时间，默认为1ms，可以用此函数配合Infer
	函数对小车前进时IN1和IN3的电平进行确认，从而修正此函数*/
	void Move(int a, int b, int c, unsigned long d = 1);
};
#endif

