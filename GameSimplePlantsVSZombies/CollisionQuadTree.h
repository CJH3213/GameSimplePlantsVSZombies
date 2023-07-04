#pragma once
#include <vector>
#include "ICollider.h"
#include "Size2.h"
#include "Rectangle.h"
#include "Window.h"
#include "IRenderer.h"

/// <summary>
/// 碰撞检查专用 四叉树
/// </summary>
class CollisionQuadTree :
	public IRenderer
{
protected:
	// 游戏上下文
	class Game* mGame = nullptr;

	// 细分阈值
	uint16_t mThreshold = 2;
	// 该节点及子树存储个数
	//uint16_t mCount = 0;

	// 维护四叉树（对移动后的碰撞器重新插入，该方法用于递归）
	void MaintainTree(CollisionQuadTree& root);

public:
	// 四个子节点
	CollisionQuadTree* mSubNodes[4];
	// 本节点储存集合
	std::vector<ICollider*> mObjects;
	// 当前节点包围盒
	Rectangle mBounds;

	// 构造函数
	CollisionQuadTree(class Game* game, Vector2 center, Vector2 size);	//中心坐标，该节点大小（非子）
	// 析构函数
	~CollisionQuadTree();
	//// 深拷贝构造
	//CollisionQuadTree(const CollisionQuadTree& other);

	// 直接获取子节点
	//CollisionQuadTree* operator[](size_t index);
	// 赋值节点 
	//CollisionQuadTree& operator=(const CollisionQuadTree& cqt);

	// 获取相对方位，象限（0123）（-1是与多个子节点相交，-2是在当前节点外部）
	int GetContainNode(ICollider* collider);
	// 获取子节点中心坐标
	Vector2 GetChildCenter(uint8_t quad);
	// 获取子节点碰撞器个数
	size_t GetSubCollidersCount() const;
	// 获取当前节点碰撞器个数（含子节点）
	size_t GetCollidersCount() const;

	// 添加碰撞组件（自动扩大）
	void AddCollider(ICollider* collider);
	// 添加碰撞组件（无扩大功能，只能从当前节点开始插入，或失败）
	bool AddColliderWithoutBigger(ICollider* collider);
	// 删除碰撞组件
	bool RemoveCollider(ICollider* collider);
	// 查找碰撞器所在节点
	CollisionQuadTree* Find(ICollider* collider);
	// 碰撞检测
	void DetectionWith(ICollider* collider);
	// 维护四叉树（当前节点作为根节点向下维护）
	void MaintainTree() { MaintainTree(*this); }


	/******************渲染接口实现******************/
	virtual bool IsRenderEnable() override { return true; }
	// 设置绘制层级
	virtual int GetDrawOrder() const override { return 1; }
	// 渲染回调
	virtual void OnRender(Window* w) override;
};





