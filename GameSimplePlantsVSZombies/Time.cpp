#include "Time.h"

//ע����̬�����Ա����������ʽ��ʼ������ʵ��ʼ�����Ƕ��壬�������ֻ��������������ᱨ���޷������ⲿ����

//����Ϸ��ʼ��ʱ�䣬������ͣӰ��
Uint32 Time::realtimeSinceStartup;
//����Ϸ��ʼ��ʱ�䣬����ͣ������Ӱ��
Uint32 Time::time;
//����Ϸ��ʼ����֡��
Uint32 Time::frameCount;
//�ӳ�����ʼ��ʱ�䣬����ͣ������Ӱ��
Uint32 Time::timeSinceLevelLoad;

//ʱ�����ű�������1Ϊ�������ʣ�С��1Ϊ����������1Ϊ��죩
float Time::timeScale;
//����FixedUpdate�����Ĺ̶����ʱ��
float Time::fixedDeltaTime;

//��һ֡ʱ��ʱ��
Uint32 Time::lastFrameTicks;
//��֡ʱ��������λ1�루1.0f = 1S��������ʱ�����ű�Ӱ��
float Time::deltaTime;
//��֡ʱ����������ʱ�����ű�Ӱ��
float Time::unscaleDeltaTime;
