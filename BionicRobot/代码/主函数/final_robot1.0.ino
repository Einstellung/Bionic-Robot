#include <LobotServoController.h>

LobotServoController myse;

const int numRows = 4;//定义4行
const int numCols = 4;//定义4列
const int debounceTime = 20;//去抖动时间长度

const char keymap[numRows][numCols]= {//键值，可以按需要更改

  { '1','2','3','+' },

  {'4','5','6','-'  },

  {'7','8','9','X'  },

  {'*','0','#','/'  }
};

const int rowPins[numRows] = {12, 11, 10, 9};//设置硬件对应的引脚
const int colPins[numCols] = {8, 7, 6, 5};
/*************************音乐节拍******************************/

#define NTD0 -1
#define NTD1 294
#define NTD2 330
#define NTD3 350
#define NTD4 393
#define NTD5 441
#define NTD6 495
#define NTD7 556

#define NTDL1 147
#define NTDL2 165
#define NTDL3 175
#define NTDL4 196
#define NTDL5 221
#define NTDL6 248
#define NTDL7 278

#define NTDH1 589
#define NTDH2 661
#define NTDH3 700
#define NTDH4 786
#define NTDH5 882
#define NTDH6 990
#define NTDH7 112
//列出全部D调的频率
#define WHOLE 1
#define HALF 0.5
#define QUARTER 0.25
#define EIGHTH 0.25
#define SIXTEENTH 0.625
//列出所有节拍
int tune[]=                 //根据简谱列出各频率
{
  NTD3,NTD3,NTD4,NTD5,
  NTD5,NTD4,NTD3,NTD2,
  NTD1,NTD1,NTD2,NTD3,
  NTD3,NTD2,NTD2,
  NTD3,NTD3,NTD4,NTD5,
  NTD5,NTD4,NTD3,NTD2,
  NTD1,NTD1,NTD2,NTD3,
  NTD2,NTD1,NTD1,
  NTD2,NTD2,NTD3,NTD1,
  NTD2,NTD3,NTD4,NTD3,NTD1,
  NTD2,NTD3,NTD4,NTD3,NTD2,
  NTD1,NTD2,NTDL5,NTD0,
  NTD3,NTD3,NTD4,NTD5,
  NTD5,NTD4,NTD3,NTD4,NTD2,
  NTD1,NTD1,NTD2,NTD3,
  NTD2,NTD1,NTD1
};
float durt[]=                   //根据简谱列出各节拍
{
  1,1,1,1,
  1,1,1,1,
  1,1,1,1,
  1+0.5,0.5,1+1,
  1,1,1,1,
  1,1,1,1,
  1,1,1,1,
  1+0.5,0.5,1+1,
  1,1,1,1,
  1,0.5,0.5,1,1,
  1,0.5,0.5,1,1,
  1,1,1,1,
  1,1,1,1,
  1,1,1,0.5,0.5,
  1,1,1,1,
  1+0.5,0.5,1+1,
};
int length;
int tonepin=13;   //用13号接口来控制蜂鸣器发声
/*************************************************************/


//初始化功能
void setup(){
    Serial.begin(9600);
    pinMode(tonepin,OUTPUT);
    length=sizeof(tune)/sizeof(tune[0]);   //计算长度，用于蜂鸣器发声
    for(int row = 0; row < numRows; row++)
    {
       pinMode(rowPins[row],INPUT);
       digitalWrite(rowPins[row],HIGH);

    }
    
    for(int column = 0;column < numCols; column++)
    {
        pinMode(colPins[column],OUTPUT);
        digitalWrite(colPins[column],HIGH);
     }

//    myse.runActionGroup(1,0);  //不断运行1号动作组
//    delay(1000);
//    myse.stopActionGroup(); //停止动作组运行
//    myse.runActionGroup(2,1);  //运行100号动作组 1次
//    myse.stopActionGroup(); //停止动作组运行
}
//主循环
void loop() {

    long IntervalTime = 0;  //定义间隔时间

    // 添加其他的程序，循环运行
    char key = getkey();
//    if(key !=0){
//      Serial.print("Got key ");//串口打印键值
//      Serial.println(key);
//    }

    if(key == '1')
    {
 //       tone(tonepin, frequency );
        myse.stopActionGroup(); //停止动作组运行
        delay(1000);
        myse.runActionGroup(1,0);  //不断运行1号动作组
        if(key == '9')
        {
            myse.stopActionGroup(); //停止动作组运行
            delay(1000);
             myse.runActionGroup(100, 1); //运行100号动作组1次，舵机回中，回到初始位置        
          }
      }

    if(key == '2')
    {
         myse.runActionGroup(2,1);  //运行2号动作组1次，左移一次
         myse.stopActionGroup(); //停止动作组运行
//         myse.runActionGroup(100, 1); //运行100号动作组1次，舵机回中，回到初始位置 
      }

    if(key == '3')
    {
         myse.runActionGroup(3,1);  //运行3号动作组1次，右移1次
         myse.runActionGroup(100, 1); //运行100号动作组1次，舵机回中，回到初始位置 
      }

    if(key == '4')
    {
         myse.runActionGroup(4,5);  //执行4号动作组5次，实现挥手功能
      /*********************用于音乐发声************/

        for(int x=0;x<length;x++)
          {
            tone(tonepin,tune[x]);
            delay(500*durt[x]);   //这里用来根据节拍调节延时，500这个指数可以自己调整，在该音乐中，我发现用500比较合适。
            noTone(tonepin);
          }

      /*******************************************/
        myse.stopActionGroup(); //停止动作组运行
      }

     if(key == '5')
    {
         myse.runActionGroup(5,0);  //不断运行2号动作组
      }
  }
//读取键值程序
char getkey(){
    char key = 0;
    for(int column = 0;column < numCols; column++){
      digitalWrite(colPins[column],LOW);
      for(int row = 0 ;row < numRows; row++){
        if(digitalRead(rowPins[row]) == LOW){ //是否有按键按下
          delay(debounceTime);
          while(digitalRead(rowPins[row]) == LOW)  //等待按键释放
            ;
          key = keymap[row][column];   
        }
      }
      digitalWrite(colPins[column],HIGH); //De-active the current column
    }
    return key;
  }

