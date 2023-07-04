#include "CardBankScript.h"
#include "SceneBase.h"
#include "CardScript.h"
#include "Animator.h"
#include "Game.h"
#include "ShovelScript.h"
#include "ZombiesManager.h"

void CardBankScript::Awake()
{
    // 初始阳光数量文本
    mSunNumText->SetContent(std::to_wstring(mSunNum));

    // 卡槽轮廓
    for (int i = 0; i < mMaxCardNum; i++)
    {
        // 卡片轮廓小背景
        GameObject* bgG = new GameObject("CardSilhouette");
        GetScene()->AddGameObject(bgG);
        bgG->SetParent(mGameObject);
        bgG->mTransform->SetPosition(GetCardCenterPos(i));
        // 证件照
        TextureRender* bgRenC = new TextureRender(
            GetGame()->mImageManagement->
            GetTextureByPath(
            "AdventureScreen/SeedPacketSilhouette.png"));
        bgG->AddComponent(bgRenC);
    }

    // 退场坐标
    Vector2 exitPos = { 223, -44 };
    // 登场坐标
    Vector2 entryPos = { 223, 43 };
    // 二次登场偏移坐标
    Vector2 offsetPos = { 30, 0 };
    // 向上退场
    mAnimator->AddKeyframe("Exit", {
        {0.0f, entryPos},
        {0.5f, exitPos, 0.0f, {1.0f, 1.0f},
            [this] {AddShovel(); }},
        });
    // 向下登场1
    mAnimator->AddKeyframe("Entry1", {
        {0.0f, exitPos},
        {0.5f, entryPos}
        });
    // 向下登场2
    mAnimator->AddKeyframe("Entry2", {
        {0.0f, exitPos + offsetPos, 0.0f, {1.0f, 1.0f},
            [this] {CoolDownAllCards(); }},
        {0.5f, entryPos + offsetPos, 0.0f, {1.0f, 1.0f},
            [this] {BattleBegins(); }}
        });
}

size_t CardBankScript::GetCardCount() const
{
    return mCards.size();
}

Vector2 CardBankScript::GetCardCenterPos(int index)
{
    int d1 = -112;     // 第一个卡片左侧x距离
    int w = 50;     // 卡片宽度
    int d2 = 9;     // 卡片之间距离
    Vector2 originPos = mGameObject->mTransform->GetPosition();

    return  originPos + Vector2(d1+(w+d2)*index, 0);
}

bool CardBankScript::IsFull()
{
    return mCards.size() >= mMaxCardNum;
}

bool CardBankScript::HasCardWithName(std::string name)
{
    return mCards.count(name) > 0;
}

void CardBankScript::AddCard(Card* card)
{
    // map保证key存在时不会插入
    CardScript* script = card->GetComponent<CardScript>();
    std::string name = script->mCardInfo.name;
    mCards.emplace(name, script);
}

void CardBankScript::RemoveCard(std::string name)
{
    mCards.erase(name);
    
    // 重新计算卡片坐标
    int i = 0;
    for (auto& card : mCards)
    {
        Vector2 pos = GetCardCenterPos(i++);
        card.second->GetTransform()->SetPosition(pos);
    }
}

void CardBankScript::LetsRock()
{
    // 锁定所有卡牌状态，不能添加或移除
    for (auto card : mCards)
    {
        card.second->mState = CardScript::IsLock;
    }

    // 卡片银行向上隐退
    mGameObject->GetComponent<Animator>()->Play("Exit");

    // 添加铁铲

    // 卡片银行向下重新登场
}

void CardBankScript::Planted(std::string name)
{
    auto iter = mCards.find(name);
    if (iter != mCards.end())
    {
        CardScript* script = (*iter).second;
        // 冷却已经种植的卡片
        script->BeginCoolDown();

        // 支出阳光数
        AddSunNum(-script->mCardInfo.amount);
    }
}

void CardBankScript::AddSunNum(int num)
{
    mSunNum += num;
    mSunNumText->SetContent(std::to_wstring(mSunNum));
    // 存款变动，检查卡片是否买得起
    CheckCardsAffordable();
}

void CardBankScript::CoolDownAllCards()
{
    // 根据余额检查卡片是否可买
    CheckCardsAffordable();

    // 开始对战后，冷却所有卡片（好像是这么玩的）
    for (auto card : mCards)
        card.second->BeginCoolDown();
}

void CardBankScript::CheckCardsAffordable()
{
    for (auto card : mCards)
    {
        if (card.second->mCardInfo.amount > mSunNum)
            card.second->SetUsable(false);
        else
            card.second->SetUsable(true);
    }
}

void CardBankScript::AddShovel()
{
    // 添加背景图
    GameObject* shovelBackGroundG = new GameObject("ShovelBG");
    GetScene()->AddGameObject(shovelBackGroundG);
    shovelBackGroundG->SetParent(mGameObject);
    shovelBackGroundG->mTransform->localPosition = { 258, -7 };
    // 背景图
    TextureRender* shovelBGRenC = new TextureRender(
        GetGame()->mImageManagement->
        GetTextureByPath(
        "AdventureScreen/ShovelBank.png"));
    shovelBackGroundG->AddComponent(shovelBGRenC);

    // 添加铲子图
    GameObject* shovelG = new GameObject("Shovel");
    GetScene()->AddGameObject(shovelG);
    shovelG->SetParent(shovelBackGroundG);
    // 图
    TextureRender* shovelRenC = new TextureRender(
        GetGame()->mImageManagement->
        GetTextureByPath(
        "AdventureScreen/Shovel.png"));
    shovelG->AddComponent(shovelRenC);
    // 按钮组件
    Button* shovelBtnC = new Button();
    shovelG->AddComponent(shovelBtnC);
    shovelBtnC->mSize = shovelRenC->mTexture->GetSize();
    // 脚本
    ShovelScript* script = new ShovelScript();
    shovelG->AddComponent(script);
    script->mBtn = shovelBtnC;
}

void CardBankScript::BattleBegins()
{
    GameObject* actorsManager = GetScene()->FindGameObject("ActorsManager");
    auto zombiesManager =  actorsManager->GetComponent<ZombiesManager>();
    zombiesManager->SetEnable(true);
}
