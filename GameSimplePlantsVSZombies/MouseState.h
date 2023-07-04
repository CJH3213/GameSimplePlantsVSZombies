#pragma once
#include "BasicInputDevice.h"
#include "ButtonStateEnum.h"
#include "Vector2.h"
#include <SDL.h>

class MouseState :
    public BasicInputDevice
{
private:
    //ָ������
    Vector2 mMousePos;
    //����״̬
    Uint32 mCurrButtons;
    Uint32 mPrevButtons;
public:
    //����ǰ׼��
    void PrepareForUpdate() override;
    //����
    void Update() override;

    //�û���ȡ���ָ��λ��
    const Vector2& GetPosition() const { return mMousePos; }
    //�û���ȡ��갴��״̬
    ButtonState GetButtonState(int button) const;

};

