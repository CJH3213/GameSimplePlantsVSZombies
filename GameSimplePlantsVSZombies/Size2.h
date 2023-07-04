#pragma once

/// <summary>
/// 表示2维尺寸：宽高
/// </summary>
template<class T>
class Size2
{
public:
	T mHeight;
	T mWidth;

	//构造函数
	Size2(T h, T w) { mHeight = h; mWidth = w; }
	Size2() { mHeight = 0; mWidth = 0; }

};

