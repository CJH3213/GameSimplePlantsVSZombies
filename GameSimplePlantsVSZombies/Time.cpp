#include "Time.h"

//注：静态的类成员变量必须显式初始化（其实初始化就是定义，类里面的只是声明），否则会报错无法解析外部符号

//从游戏开始的时间，不受暂停影响
Uint32 Time::realtimeSinceStartup;
//从游戏开始的时间，受暂停、缩放影响
Uint32 Time::time;
//从游戏开始的总帧数
Uint32 Time::frameCount;
//从场景开始的时间，受暂停、缩放影响
Uint32 Time::timeSinceLevelLoad;

//时间缩放比例，（1为正常速率，小于1为变慢，大于1为变快）
float Time::timeScale;
//调用FixedUpdate方法的固定间隔时长
float Time::fixedDeltaTime;

//上一帧时的时间
Uint32 Time::lastFrameTicks;
//两帧时间间隔，单位1秒（1.0f = 1S），会受时间缩放比影响
float Time::deltaTime;
//两帧时间间隔，不受时间缩放比影响
float Time::unscaleDeltaTime;
