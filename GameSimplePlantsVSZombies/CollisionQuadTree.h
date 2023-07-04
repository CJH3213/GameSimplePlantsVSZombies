#pragma once
#include <vector>
#include "ICollider.h"
#include "Size2.h"
#include "Rectangle.h"
#include "Window.h"
#include "IRenderer.h"

/// <summary>
/// ��ײ���ר�� �Ĳ���
/// </summary>
class CollisionQuadTree :
	public IRenderer
{
protected:
	// ��Ϸ������
	class Game* mGame = nullptr;

	// ϸ����ֵ
	uint16_t mThreshold = 2;
	// �ýڵ㼰�����洢����
	//uint16_t mCount = 0;

	// ά���Ĳ��������ƶ������ײ�����²��룬�÷������ڵݹ飩
	void MaintainTree(CollisionQuadTree& root);

public:
	// �ĸ��ӽڵ�
	CollisionQuadTree* mSubNodes[4];
	// ���ڵ㴢�漯��
	std::vector<ICollider*> mObjects;
	// ��ǰ�ڵ��Χ��
	Rectangle mBounds;

	// ���캯��
	CollisionQuadTree(class Game* game, Vector2 center, Vector2 size);	//�������꣬�ýڵ��С�����ӣ�
	// ��������
	~CollisionQuadTree();
	//// �������
	//CollisionQuadTree(const CollisionQuadTree& other);

	// ֱ�ӻ�ȡ�ӽڵ�
	//CollisionQuadTree* operator[](size_t index);
	// ��ֵ�ڵ� 
	//CollisionQuadTree& operator=(const CollisionQuadTree& cqt);

	// ��ȡ��Է�λ�����ޣ�0123����-1�������ӽڵ��ཻ��-2���ڵ�ǰ�ڵ��ⲿ��
	int GetContainNode(ICollider* collider);
	// ��ȡ�ӽڵ���������
	Vector2 GetChildCenter(uint8_t quad);
	// ��ȡ�ӽڵ���ײ������
	size_t GetSubCollidersCount() const;
	// ��ȡ��ǰ�ڵ���ײ�����������ӽڵ㣩
	size_t GetCollidersCount() const;

	// �����ײ������Զ�����
	void AddCollider(ICollider* collider);
	// �����ײ������������ܣ�ֻ�ܴӵ�ǰ�ڵ㿪ʼ���룬��ʧ�ܣ�
	bool AddColliderWithoutBigger(ICollider* collider);
	// ɾ����ײ���
	bool RemoveCollider(ICollider* collider);
	// ������ײ�����ڽڵ�
	CollisionQuadTree* Find(ICollider* collider);
	// ��ײ���
	void DetectionWith(ICollider* collider);
	// ά���Ĳ�������ǰ�ڵ���Ϊ���ڵ�����ά����
	void MaintainTree() { MaintainTree(*this); }


	/******************��Ⱦ�ӿ�ʵ��******************/
	virtual bool IsRenderEnable() override { return true; }
	// ���û��Ʋ㼶
	virtual int GetDrawOrder() const override { return 1; }
	// ��Ⱦ�ص�
	virtual void OnRender(Window* w) override;
};





