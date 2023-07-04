#pragma once
#include "CollisionQuadTree.h"
#include "ICollider.h"
#include "IPointer.h"

/// <summary>
/// ��ײ������
/// </summary>
class CollisionManager
{
private:
	// ��Ϸ������
	class Game* mGame = nullptr;

	// ָ����ײ�������������Ĳ����������ڵ�
	CollisionQuadTree* mRootNode = nullptr;
	// ��������������ײ��
	std::vector<ICollider* > mColliders = std::vector<ICollider*>();
	// �����ײ�������
	std::vector<IPointer*> mPointers = std::vector<IPointer*>();

	// ���Ĳ��������ײ��
	void InsertIntoNode(ICollider* collider);

public:
	//���캯��
	CollisionManager(class Game* game , const Vector2& center, const Vector2& size);
	~CollisionManager();

	//�����ײ��
	void AddCollider(ICollider* collider);
	//ɾ����ײ��
	void RemoveCollider(ICollider* collider);
	//��������ײ��
	void AddPointer(IPointer* collider);
	//ɾ�������ײ��
	void RemovePointer(IPointer* collider);
	// ���������ײ���������
	void DetectionAll();
	// ���������ײ����������꣩
	void DetectionWithMouse();

	// ����Ϸѭ��ִ��
	void OnGameLoop();
	// ������ײ�����Ĳ���
	//void Draw(Window* w);
};

