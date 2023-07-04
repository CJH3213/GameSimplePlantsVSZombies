#include <iostream>
#include <exception>
#include "Game.h"

/// <summary>
/// 面函数，哈哈哈
/// 使用SDL库，必须一字不差定义main函数
/// </summary>
/// <param name="argc"></param>
/// <param name="argv"></param>
/// <returns></returns>
int main(int argc, char* argv[])
{
	//printf_s("main()");

	//try
	//{
		Game game("PVZ");
		game.Start();
		game.Main();
		game.Finish();	
	//}
	//catch (const char* errMsg)
	//{
	//	std::cout  << "GameError: " << errMsg << std::endl;
	//}
	//catch (...)
	//{
	//	std::cout << "GameError: " << "...Error" << std::endl;
	//}

	//getchar();

	return 0;
}

/*
C++的异常捕获机制没有其他高级语言那么有用，
一般来说只能捕获到手动throw出的异常，
对于内存非法访问之类的系统级别错误，软件直接被干掉！
所以不要指望使用C++的异常捕获防止软件闪退。
*/