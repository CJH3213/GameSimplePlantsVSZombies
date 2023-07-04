#include "ChooseBoxScript.h"
#include "SceneBase.h"
#include "CardScript.h"
#include "Animator.h"
// Ԥ�Ƽ�
#include "Sunflower.h"
#include "Peashooter.h"

void ChooseBoxScript::Awake()
{
	// ��ȡ��Ƭ���п��ƽű�
	mCardBank = GetScene()->FindGameObject("CardBank")->GetComponent<CardBankScript>();
	// ��ȡ����ͼ����
	mBackGround = GetScene()->FindGameObject("BackGround");

	// ����¼�����
	mStartBtn->mMouseUpAsButtonEvents.AddListener("ChooerScript", std::bind(&ChooseBoxScript::OnClick, this));

	// ��һ����Ƭ����
	Vector2 firstCard = {-190, -180};
	// �Ҳ࿨Ƭy���꣬��������
	int xMax = 190;
	// ������Ƭ֮��Ĳ�������
	Vector2 step = { 50 + 10, 70 + 10 };
	// �ṩ�����õ���ʱ����
	Vector2 pos = firstCard;

	// ���ؿ�Ƭ��Ϣ
	mCardInfo.emplace_back(CardInfo{ "Sunflower", 50, 2.5f, "AdventureScreen/Sunflower", new Sunflower() });
	mCardInfo.emplace_back(CardInfo{ "Peashooter", 100, 2.5f, "AdventureScreen/Peashooter", new Peashooter() });

	// ���ԣ���Ԥ�Ƽ�������������ʵ����
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
		// ������һ����Ƭ����
		pos.x += step.x;
		if (pos.x > xMax)
		{
			pos.x = firstCard.x;
			pos.y += step.y;	//����
		}

	}

	// ����ѡ������
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
		// ����Ԥ�Ƽ�ģ��
		delete info.plantPrefab;
	}
}

void ChooseBoxScript::OnClick()
{
	// ��Ƭ���� - ��ʼս��
	mCardBank->LetsRock();

	// ѡ���������˳�
	mGameObject->GetComponent<Animator>()->Play("Exit");
	// ����ͼ����
	mBackGround->GetComponent<Animator>()->Play("GoToLeft");

	// ���ָı�Ϊ�ؿ���������
	mAudio->Stop("Resource/Sounds/Choose your seeds.wav");
	mAudio->Play("Resource/Sounds/Grasswalk.wav", true);
}
