#ifndef ColSensor_h
#define ColSensor_h
class ColSensor{
private:
	//引脚定义
	int S0, S1, S2, S3, OUT;
	//定义延时
	unsigned long time;

public:
	//定义计数器
	unsigned long g_count;
	//定义数组，存放读取到的RGB值
	int g_array[3];
	//数组，存放比例系数
	float g_SF[3];
	//构造函数
	ColSensor(int a, int b, int c, int d, int e, unsigned long f);
	//将引脚配置输出，同事设置输出比例因子
	void Mode(int a = 1, int b = 1);
	//控制数字引脚，切换滤波器，红绿蓝分别对应S2与S3的00.11.01电平，10时过滤所有颜色
	void Digital_out(int a, int b);
	//计算比例系数
	void Test();
	//计算RGB值
	void Get();
};
#endif
