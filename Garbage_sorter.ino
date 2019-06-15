#include "Function.h"  //包含变量的定义和函数的实现
#include "ColSensor.h"  //颜色传感器类
#include "Track.h"  //巡线传感器类
#include "Car.h"  //小车类
#include "ColQueue.h"  //队列类
#include "Servo.h"



int color[4] = { 0, 0, 0, 0 };//颜色缓存区



void Catch(int n)    //夹取方块并放到小车相应垃圾桶上
{
  int a;
  int s11, s12,  s21, s22, s23,  s31 ;

  s11 = 35; s12 = 0; //张开、闭合
  s21 = 67; s22 = 95;  s23 = 125;//地面辣鸡高度、辣鸡桶高度、辣鸡桶上面高度（保证移动过程中不会碰到其他辣鸡堆的辣鸡）
  s31 = 10;  //捡辣鸡位置
  
  switch (n) //1-3分别表示红蓝绿3个垃圾桶的位置
  {
    case 1:a = 110; break;
    case 2:a = 126; break;
    case 3:a = 141; break;
    default:return; break;
  }


  ServoMove(s22, s21, 2);
  ServoMove(s11, s12, 1);
  ServoMove(s21, s23, 2);
  ServoMove(s31, a, 3);
  ServoMove(s23, s22, 2);
  ServoMove(s12, s11, 1);
  ServoMove(s22, s23, 2);
  ServoMove(a, s31, 3);
  ServoMove(s23, s22, 2);
  


  Plus();//修正速度
  
}


void Down(int n)    //夹取小车上的垃圾并放到相应的垃圾场 
{
  
  int a;
  int s11, s12,  s21, s22, s23,  s31,  s32 ;

  s11 = 38; s12 = 0; //张开、闭合
  s21 = 67; s22 = 93;  s23 = 125;//地面辣鸡高度，辣鸡桶上面高度（保证移动过程中不会碰到其他辣鸡堆的辣鸡）、辣鸡桶高度
  s31 = 60; s32 = 10; //捡辣鸡位置
  
  switch (n) //1-3分别表示红蓝绿3个垃圾桶的位置
  {
    case 1:a = 112; break;
    case 2:a = 127; break;
    case 3:a = 142; break;
    default:return; break;
  }  

  ServoMove(s22, s23, 2);
  ServoMove(s31, a, 3);
  ServoMove(s23, s22, 2);
  ServoMove(s11, s12, 1);
  ServoMove(s22, s23, 2);  
  ServoMove(a, s31,3);
  ServoMove(s23, s21, 2);
  ServoMove(s12, s11, 1);
  ServoMove(s21, s22, 2);
  ServoMove(s31, s32, 3);

  
}



void setup()
{
  SPEED1 = 180; SPEED2 = 150;
  
  TURN = 150;//转弯
  BACK = 80; //后退延迟
  DELAY = 600;//转弯延迟




  myservo1.attach(7); myservo2.attach(12); myservo3.attach(A0);
  myservo1.write(35); myservo2.write(115); myservo3.write(10);

  mysensor.Mode();  //颜色传感器引脚配置
  
  Ready();//自动调节白平衡，用方块测试，若蜂鸣器鸣叫，说明已检测到方块，校准方法：启动前让颜色传感器对准远处，启动后等蜂鸣器停止鸣叫就好
  delay(3000);



  
  mycar.Mode();
  //定义小车前进时IN1和IN3的电平
  mycar.Infer(1, 1);
  mytrack.Mode();
  //设定红外的阀值
  Modify();
  delay(3000);

num=0;

  
}
void loop()
{

//Memory[num]：记录着12个路口的颜色缓冲
///////////////////////////  从第一个路口前面开始出发去捡辣鸡  /////////////////

while (num != N)//num=记录小车所在的路口，分别取值为1至12   N=岔路口数   在Function中定义了
{
    Tracking(SPEED1, SPEED2); 
    num++; 

if(Memory[num] != 50)
{
    if(color[1]==0  ||  color[2]==0  ||  color[3]==0)//如果身上的辣鸡桶全满了，直接跑辣鸡堆倒辣鸡
    {
        if( (Memory[num] !=  color[Memory[num]] ) || Memory[num] ==0 ) //判断这个路口是否曾经进过，如果进过，判断身上的辣鸡桶还有没有空位装里面的辣鸡
        {
            In(); 
            
            Check(num);//检测色块值
            
            if (Memory[num] != 0 && color[Memory[num]] == 0)    //定义在Function_h，储存每个路口辣鸡块的颜色  int Memory[N + 1];
            {//判断这个颜色的辣鸡桶有没有满，没满的话就捡
              
                Catch(Memory[num]); //夹取辣鸡块到辣鸡桶里
                color[Memory[num]] = Memory[num];//标记车上的辣鸡桶已有辣鸡
                Memory[num] = 50;//把这个位置的垃圾箱标记清空，这样下次巡逻的时候就不会再进这个路口（为啥是50？瞎写的，除了0到3，想写啥就写啥）
              
            }
            
            else//满了就掉头就走
            
            {
              
                mycar.Move(SPEED1, SPEED2, 2, BACK);
                mycar.Move(0, 0, 5, 1);
              
            }
        
            
            Out();
        }
    }
}
    
  }

/////////////////////  转弯小区一圈，右转进辣鸡堆  /////////////////////////////////////////  

  num = 0;
  Tracking(SPEED1, SPEED2);
  TurnR();

/////////////////////  扔辣鸡  ////////////////////////////////////////
  
  while (num != 3)//扔辣鸡
  {
    Tracking(SPEED1, SPEED2);
    num++;
    if (color[num] != 0)//判断辣鸡车的辣鸡箱上有没有辣鸡
    Down(num);//有的话赶紧扔掉

  }
/////////////////  清空辣鸡桶标记  ////////////////  
  color[1]=0;
  color[2]=0;
  color[3]=0;
/////////////////  扔完辣鸡又去捡  /////////////////////
  
  num = 0;
  Tracking(SPEED1, SPEED2);
  TurnR();




}
