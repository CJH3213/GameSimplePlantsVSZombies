#include "CardBankScript.h"
#include "SceneBase.h"
#include "CardScript.h"
#include "Animator.h"
#include "Game.h"
#include "ShovelScript.h"
#include "ZombiesManager.h"

void CardBankScript::Awake()
{
    // ��ʼ���������ı�
    mSunNumText->SetContent(std::to_wstring(mSunNum));

    // ��������
    for (int i = 0; i < mMaxCardNum; i++)
    {
        // ��Ƭ����С����
        GameObject* bgG = new GameObject("CardSilhouette");
        GetScene()->AddGameObject(bgG);
        bgG->SetParent(mGameObject);
        bgG->mTransform->SetPosition(GetCardCenterPos(i));
        // ֤����
        TextureRender* bgRenC = new TextureRender(
            GetGame()->mImageManagement->
            GetTextureByPath(
            "AdventureScreen/SeedPacketSilhouette.png"));
        bgG->AddComponent(bgRenC);
    }

    // �˳�����
    Vector2 exitPos = { 223, -44 };
    // �ǳ�����
    Vector2 entryPos = { 223, 43 };
    // ���εǳ�ƫ������
    Vector2 offsetPos = { 30, 0 };
    // �����˳�
    mAnimator->AddKeyframe("Exit", {
        {0.0f, entryPos},
        {0.5f, exitPos, 0.0f, {1.0f, 1.0f},
            [this] {AddShovel(); }},
        });
    // ���µǳ�1
    mAnimator->AddKeyframe("Entry1", {
        {0.0f, exitPos},
        {0.5f, entryPos}
        });
    // ���µǳ�2
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
    int d1 = -112;     // ��һ����Ƭ���x����
    int w = 50;     // ��Ƭ���
    int d2 = 9;     // ��Ƭ֮�����
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
    // map��֤key����ʱ�������
    CardScript* script = card->GetComponent<CardScript>();
    std::string name = script->mCardInfo.name;
    mCards.emplace(name, script);
}

void CardBankScript::RemoveCard(std::string name)
{
    mCards.erase(name);
    
    // ���¼��㿨Ƭ����
    int i = 0;
    for (auto& card : mCards)
    {
        Vector2 pos = GetCardCenterPos(i++);
        card.second->GetTransform()->SetPosition(pos);
    }
}

void CardBankScript::LetsRock()
{
    // �������п���״̬��������ӻ��Ƴ�
    for (auto card : mCards)
    {
        card.second->mState = CardScript::IsLock;
    }

    // ��Ƭ������������
    mGameObject->GetComponent<Animator>()->Play("Exit");

    // �������

    // ��Ƭ�����������µǳ�
}

void CardBankScript::Planted(std::string name)
{
    auto iter = mCards.find(name);
    if (iter != mCards.end())
    {
        CardScript* script = (*iter).second;
        // ��ȴ�Ѿ���ֲ�Ŀ�Ƭ
        script->BeginCoolDown();

        // ֧��������
        AddSunNum(-script->mCardInfo.amount);
    }
}

void CardBankScript::AddSunNum(int num)
{
    mSunNum += num;
    mSunNumText->SetContent(std::to_wstring(mSunNum));
    // ���䶯����鿨Ƭ�Ƿ������
    CheckCardsAffordable();
}

void CardBankScript::CoolDownAllCards()
{
    // ��������鿨Ƭ�Ƿ����
    CheckCardsAffordable();

    // ��ʼ��ս����ȴ���п�Ƭ����������ô��ģ�
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
    // ��ӱ���ͼ
    GameObject* shovelBackGroundG = new GameObject("ShovelBG");
    GetScene()->AddGameObject(shovelBackGroundG);
    shovelBackGroundG->SetParent(mGameObject);
    shovelBackGroundG->mTransform->localPosition = { 258, -7 };
    // ����ͼ
    TextureRender* shovelBGRenC = new TextureRender(
        GetGame()->mImageManagement->
        GetTextureByPath(
        "AdventureScreen/ShovelBank.png"));
    shovelBackGroundG->AddComponent(shovelBGRenC);

    // ��Ӳ���ͼ
    GameObject* shovelG = new GameObject("Shovel");
    GetScene()->AddGameObject(shovelG);
    shovelG->SetParent(shovelBackGroundG);
    // ͼ
    TextureRender* shovelRenC = new TextureRender(
        GetGame()->mImageManagement->
        GetTextureByPath(
        "AdventureScreen/Shovel.png"));
    shovelG->AddComponent(shovelRenC);
    // ��ť���
    Button* shovelBtnC = new Button();
    shovelG->AddComponent(shovelBtnC);
    shovelBtnC->mSize = shovelRenC->mTexture->GetSize();
    // �ű�
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
