#include <iostream>
#include <exception>
#include "Game.h"

/// <summary>
/// �溯����������
/// ʹ��SDL�⣬����һ�ֲ����main����
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
C++���쳣�������û�������߼�������ô���ã�
һ����˵ֻ�ܲ����ֶ�throw�����쳣��
�����ڴ�Ƿ�����֮���ϵͳ����������ֱ�ӱ��ɵ���
���Բ�Ҫָ��ʹ��C++���쳣�����ֹ������ˡ�
*/