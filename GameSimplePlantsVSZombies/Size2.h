#pragma once

/// <summary>
/// ��ʾ2ά�ߴ磺���
/// </summary>
template<class T>
class Size2
{
public:
	T mHeight;
	T mWidth;

	//���캯��
	Size2(T h, T w) { mHeight = h; mWidth = w; }
	Size2() { mHeight = 0; mWidth = 0; }

};

