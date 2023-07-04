#pragma once
#include "BasicInputDevice.h"
#include "ButtonStateEnum.h"
#include <SDL.h>

class KeyboardState :
    public BasicInputDevice
{
private:
    //��ǰ״̬
    const Uint8* mCurrState;
    //״̬�ݴ���
    Uint8 mPrevState[SDL_NUM_SCANCODES];

public:

    //��ʼ��
    void Initialize() override;
    //����ǰ׼��
    void PrepareForUpdate() override;
    //���£����ڻ�ȡ��SDL����״̬��ָ�룬���ֻ��Ҫ������Ϣ�ü��ɸ��°�����״̬

    //��ȡ��ǰ������ƽ
    bool GetKeyValue(SDL_Scancode keyCode) const;
    //��ȡ��������״̬
    enum ButtonState GetKeyState(SDL_Scancode keyCode) const;
};

