#include "ChooseBoxScript.h"
#include "SceneBase.h"
#include "CardScript.h"
#include "Animator.h"
// 预制件
#include "Sunflower.h"
#include "Peashooter.h"

void ChooseBoxScript::Awake()
{
	// 获取卡片银行控制脚本
	mCardBank = GetScene()->FindGameObject("CardBank")->GetComponent<CardBankScript>();
	// 获取背景图对象
	mBackGround = GetScene()->FindGameObject("BackGround");

	// 点击事件监听
	mStartBtn->mMouseUpAsButtonEvents.AddListener("ChooerScript", std::bind(&ChooseBoxScript::OnClick, this));

	// 第一个卡片坐标
	Vector2 firstCard = {-190, -180};
	// 右侧卡片y坐标，超过换行
	int xMax = 190;
	// 两个卡片之间的步进距离
	Vector2 step = { 50 + 10, 70 + 10 };
	// 提供计算用的临时坐标
	Vector2 pos = firstCard;

	// 加载卡片信息
	mCardInfo.emplace_back(CardInfo{ "Sunflower", 50, 2.5f, "AdventureScreen/Sunflower", new Sunflower() });
	mCardInfo.emplace_back(CardInfo{ "Peashooter", 100, 2.5f, "AdventureScreen/Peashooter", new Peashooter() });

	// 测试：把预制件的子物体和组件实例化
	mCardInfo[0].plantPrefab->SetScene(GetScene());
	mCardInfo[0].plantPrefab->Instantiate();
	mCardInfo[1].plantPrefab->SetScene(GetScene());
	mCardInfo[1].plantPrefab->Instantiate();

	for (int i = 0; i < mCardInfo.size(); i++)
	{
		Card* card = new Card();
		GetScene()->AddGameObject(card);
		card->SetParent(mGameObject);
		card->mTransform->localPosition = pos;
		auto script = card->GetComponent<CardScript>();
		script->mCardInfo = mCardInfo[i];
		script->SetUsable(true);
		mCards.emplace(mCardInfo[i].name, card);
		// 计算下一个卡片坐标
		pos.x += step.x;
		if (pos.x > xMax)
		{
			pos.x = firstCard.x;
			pos.y += step.y;	//换行
		}

	}

	// 播放选卡音乐
	mAudio->Play("Resource/Sounds/Choose your seeds.wav", true);
}

void ChooseBoxScript::GiveBack(std::string name)
{
	auto iter = mCards.find(name);
	if (iter != mCards.end())
	{
		Card* card = (*iter).second;
		CardScript* script = card->GetComponent<CardScript>();
		script->SetUsable(true);
	}
}

ChooseBoxScript::~ChooseBoxScript()
{
	for (auto& info : mCardInfo)
	{
		// 析构预制件模板
		delete info.plantPrefab;
	}
}

void ChooseBoxScript::OnClick()
{
	// 卡片银行 - 开始战斗
	mCardBank->LetsRock();

	// 选卡栏向左退场
	mGameObject->GetComponent<Animator>()->Play("Exit");
	// 背景图左移
	mBackGround->GetComponent<Animator>()->Play("GoToLeft");

	// 音乐改变为关卡背景音乐
	mAudio->Stop("Resource/Sounds/Choose your seeds.wav");
	mAudio->Play("Resource/Sounds/Grasswalk.wav", true);
}
