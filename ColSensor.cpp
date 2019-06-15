#include <Arduino.h>
#include "ColSensor.h"
ColSensor::ColSensor(int a, int b, int c, int d, int e, unsigned long f)
{
	S0 = a; S1 = b; S2 = c; S3 = d; OUT = e; time = f;
	g_count = 0;
}
void ColSensor::Mode(int a, int b)
{
	pinMode(S0, OUTPUT);
	pinMode(S1, OUTPUT);
	pinMode(S2, OUTPUT);
	pinMode(S3, OUTPUT);
	pinMode(OUT, INPUT);
	digitalWrite(S0, !(a == 0));
	digitalWrite(S1, !(b == 0));
}
void ColSensor::Digital_out(int a, int b)
{
	digitalWrite(S2, !(a == 0));
	digitalWrite(S3, !(b == 0));
}
void ColSensor::Test()
{
	g_array[0] = 0; g_array[1] = 0; g_array[2] = 0;
	for (int j = 0; j<3; j++){
		for (int i = 0; i < 3; i++){
			g_count = 0;
			switch (j){
			case 0: Digital_out(0, 0); break;
			case 1: Digital_out(0, 1); break;
			case 2: Digital_out(1, 1); break;
			default:break;
			}
			delay(this->time);
			g_array[j] += g_count;
		}
	g_array[j] /= 3;
	g_SF[j] = 255.0 / g_array[j];
	}
	Digital_out(1, 0);
	g_count = 0;
}
void ColSensor::Get()
{
	for (int i = 0; i<3; i++)
	{
		g_count = 0;
		switch (i){
		case 0: Digital_out(0, 0); break;
		case 1: Digital_out(0, 1); break;
		case 2: Digital_out(1, 1); break;
		default:break;
		}
		delay(this->time);
		g_array[i] = g_count;
		g_array[i] = g_SF[i] * g_array[i];
	}
	Digital_out(1, 0);
	g_count = 0;
}
