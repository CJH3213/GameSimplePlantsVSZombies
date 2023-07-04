#pragma once
#include "CollisionQuadTree.h"
#include "ICollider.h"
#include "IPointer.h"

/// <summary>
/// 碰撞管理器
/// </summary>
class CollisionManager
{
private:
	// 游戏上下文
	class Game* mGame = nullptr;

	// 指向碰撞管理器最外层的四叉树，即根节点
	CollisionQuadTree* mRootNode = nullptr;
	// 线性容器储存碰撞器
	std::vector<ICollider* > mColliders = std::vector<ICollider*>();
	// 鼠标碰撞检测容器
	std::vector<IPointer*> mPointers = std::vector<IPointer*>();

	// 向四叉树添加碰撞器
	void InsertIntoNode(ICollider* collider);

public:
	//构造函数
	CollisionManager(class Game* game , const Vector2& center, const Vector2& size);
	~CollisionManager();

	//添加碰撞器
	void AddCollider(ICollider* collider);
	//删除碰撞器
	void RemoveCollider(ICollider* collider);
	//添加鼠标碰撞器
	void AddPointer(IPointer* collider);
	//删除鼠标碰撞器
	void RemovePointer(IPointer* collider);
	// 检查所有碰撞器（物与物）
	void DetectionAll();
	// 检测所有碰撞器（物与鼠标）
	void DetectionWithMouse();

	// 在游戏循环执行
	void OnGameLoop();
	// 绘制碰撞器和四叉树
	//void Draw(Window* w);
};

