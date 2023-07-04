#pragma once
#include <vector>
#include "SceneBase.h"

class SceneManager
{
private:
	// ��������
	std::vector<SceneBase*> mScenes;
	// ���𳡾���������ʵ����û����������
	std::vector<SceneBase*> mPendingScenes;
	// ��ǰ��������Ծ����
	SceneBase* mActivityScene = nullptr;
	// Game������Ϸ�����ģ�
	class Game* mGame = nullptr;

public:
	// ���캯��
	SceneManager(class Game* game) : mGame(game){}

	// ��ӳ���
	void LoadScene(SceneBase* scene);
	// ��ӳ����첽
	//void LoadSceneAsync(SceneBase* scene){}
	// ���ٳ���
	void DestroyScene(SceneBase* scene){}
	// ��ȡ��ǰ��Ծ����
	SceneBase* GetActivityScene();
	//��ȡ�ڼ�������
	SceneBase* GetSceneAt(int index);
	//ͨ�����ƻ�ȡ����
	SceneBase* GetSceneByName(std::string name);

	//��Ϸ��ѭ��
	void OnGameLoop_Pre();
	void OnGameLoop_Update();
};

