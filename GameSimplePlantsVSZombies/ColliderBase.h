#pragma once
#include "ComponentBase.h"
#include "ICollider.h"
#include <map>
#include <array>
#include "EventHandlers.h"
#include "IRenderer.h"

class ColliderBase :
    public ComponentBase, public ICollider, public IRenderer
{
private:
	// 记录与之碰撞过的组件状态
	std::map<ICollider*, std::array<bool, 2>> mCollisionState;

	// 消除指定碰撞器记录
	void RemoveColliderRecord(ICollider* other);

public:
	// 矩形碰撞器与基坐标偏移量
	Vector2 mOffset;

	// 碰撞进入事件回调
	EventHandlers<void(ICollider*)> mEnterEvents;
	// 碰撞保持事件回调
	EventHandlers<void(ICollider*)> mStayEvents;
	// 碰撞分离事件回调
	EventHandlers<void(ICollider*)> mExitEvents;

	/******************脚本基础方法******************/
	// 析构函数
	~ColliderBase();

	// 组件初始化
	virtual void Awake() override;
	// 启用、禁用
	//virtual void OnEnable() {};
	virtual void OnDisable();

	/******************碰撞接口实现******************/
	// 是否启用碰撞
	virtual bool IsColliderEnable() override { return IsEnable(); }
	// 碰撞回调函数
	virtual void OnCollisionCallback(ICollider*) override;
	// 碰撞检测结束后调用
	virtual void LateCollideUpdate() override;
	// 获取碰撞器所挂载的游戏对象
	virtual class GameObject* GetGameObj() override;

	/******************渲染接口实现******************/
	// 是否启用渲染
	virtual bool IsRenderEnable() override { return IsEnable(); }
	// 设置绘制层级
	virtual int GetDrawOrder() const override { return 1; }
	// 渲染回调
	virtual void OnRender(Window* w) override;

	/******************自定义方法******************/
	// 获取碰撞记录表
	const std::map<ICollider*, std::array<bool, 2>>& GetCollisionState() { return mCollisionState; }
};

