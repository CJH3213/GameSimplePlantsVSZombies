#include "TurfScript.h"
#include "GameObject.h"
#include "SceneBase.h"
#include "GrowPlantScript.h"
#include "TextureRender.h"
#include "Game.h"
#include "Input.h"
#include "Peashooter.h"
#include "LifeScript.h"

ComponentBase* TurfScript::Clone() const
{
	TurfScript* newComp = new TurfScript();

	// ֲ��������������ʼ��ʱ���ȡ��
	// ��ť�����ͨ���ⲿע�룬һ��ͨ��Ԥ�Ƽ�ʵ����ʱע��
	// �п��ܻ��ǻ���bug��ע��һ��

	return newComp;
}

void TurfScript::Awake()
{
	// ��ȡ��Ƭ���нű�
	mCardBank = GetScene()->FindGameObject("CardBank")->GetComponent<CardBankScript>();

	// ��ȡֲ�������
	auto actorsManager = GetScene()->FindGameObject("ActorsManager");
	mPlantManager = actorsManager->GetComponent<PlantsManager>();

	// ע��������
	//std::string tag = mGameObject->GetName();
	mBtn->mMouseEnterEvents.AddListener("Enter", std::bind(&TurfScript::OnMouseEnter, this));
	mBtn->mMouseOverEvents.AddListener("Over", std::bind(&TurfScript::OnMouseOver, this));
	mBtn->mMouseExitEvents.AddListener("Exit", std::bind(&TurfScript::OnMouseExit, this));
	mBtn->OnClick.AddListener("OnClick", std::bind(&TurfScript::OnClick, this));
}

void TurfScript::DestroyPlant()
{
	//����Ŀǰ��Ƥ�ϵ�ֲ������Ӷ���
	DestroyAllChildren(mPlant);
	Destroy(mPlant);
	mPlant = nullptr;
}

void TurfScript::OnMouseEnter()
{
	GameObject* obj = mPlantManager->mMouseHold;
	// ���������ֲ�������������Ƥ����ʾ��ֲЧ��
	if(obj != nullptr && obj->mName == "PreviewPlant" && mPlant == nullptr)
	{
		// ��������Ƥ����ʾ��͸������ֲЧ��ʾ��ͼ
		mPreviewPlant = new GameObject(*obj);// ("TurfPlant");
		GetScene()->AddGameObject(mPreviewPlant);
		mPreviewPlant->SetParent(mGameObject);
		mPreviewPlant->mTransform->localPosition = { 0, 0 };
		// ����Ԥ��ֲ���������ͼƬ
		TextureRender* textureRender = mPreviewPlant->GetComponent<TextureRender>(); 
		textureRender->SetAlpha(0.6f);
		textureRender->SetDrawOrder(5);
		// ���ýű��������������ֲ�Ĳ�Ҫ��������ƶ�
		mPreviewPlant->GetComponent<GrowPlantScript>()->mIsPlanted = true;
	}
}

void TurfScript::OnMouseOver()
{
	// ������ôд�е���������һ�û�뵽��������
	// �����ڲ�Ƥ�ϣ����Ҽ����£�ȡ��ʾ��ͼ
	if (Input::GetMouseButton(1) && mPreviewPlant)
	{
		Destroy(mPreviewPlant);
		mPreviewPlant = nullptr;
	}
}

void TurfScript::OnMouseExit()
{
	// ����Ƴ���Ƥ��ɾ��ʾ��Ч��ͼ
	Destroy(mPreviewPlant);
	mPreviewPlant = nullptr;
}

void TurfScript::OnClick()
{
	// ��Ԥ��ֲ��������Ԥ��ֲ����ֲ����Ƥ��
	if (mPreviewPlant != nullptr && mPlant == nullptr)
	{
		// ʵ����Ԥ��ֲ���ʵ��ֲ��
		GrowPlantScript* script = mPreviewPlant->GetComponent<GrowPlantScript>();
		Prefab* plant = script->mPlantInfo.mPlantPrefab;

		// ����-ʵ����ֲ��Ԥ�Ƽ�
		Prefab* currPlant = new Prefab(*plant);
		mPlant = currPlant;
		GetScene()->AddGameObject(currPlant);
		currPlant->SetParent(mGameObject);	// ע��ݿ���ֲ��ĸ�����
		//currPlant->mTransform->localPosition = { 0, 0 };

		// ֪ͨ��Ƭ���У����ۣ���ֲ�¼� 
		mCardBank->Planted(script->mPlantInfo.mName);

		// ����Ԥ����ֲЧ���Ķ���
		Destroy(mPreviewPlant);
		mPreviewPlant = nullptr;
	}
	else
	{
		// ��������������
		GameObject* obj = mPlantManager->mMouseHold;
		if (obj != nullptr && obj->mName == "Shovel")
		{
			//����Ŀǰ��Ƥ�ϵ�ֲ������Ӷ���
			DestroyPlant();
		}
	}
}
