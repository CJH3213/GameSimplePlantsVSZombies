#include "GrowPlantScript.h"
#include "Input.h"
#include "TransformComponent.h"
#include "SceneBase.h"
#include "TextureRender.h"
#include "Game.h"

ComponentBase* GrowPlantScript::Clone() const
{
	// ֱ���ÿ�������������Ӱ˸��ƽ�ȥ
	GrowPlantScript* newComp = new GrowPlantScript(*this);

	return newComp;
}

void GrowPlantScript::Awake()
{
	// ��ȡֲ�������
	auto actorsManager = GetScene()->FindGameObject("ActorsManager");
	mPlantManager = actorsManager->GetComponent<PlantsManager>();

	// ����Ԥ����ɫͼ
	TextureRender* texRen = mGameObject->GetComponent<TextureRender>();
	if(texRen->mTexture == nullptr)
	{
		texRen->ChangeTexture(GetGame()->mImageManagement->
			GetTexturesByDir(mPlantInfo.mResourceFolder)[0] );
	}
}

void GrowPlantScript::Update()
{
	// ��ֲ����Ƥ���߼������ڲ�Ƥ�ű�����������
	// ���飺TurfScript

	// δ����ʱ���������
	if (mIsPlanted == false)
	{
		// �ö����������������
		GetTransform()->SetPosition(Input::GetMousePosition());

		// �����Ҽ���ȡ����ֲ
		if (Input::GetMouseButton(0) || Input::GetMouseButton(1))
		{
			// ֲ�������ȡ����¼
			mPlantManager->mMouseHold = nullptr;

			// ��������
			Destroy(mGameObject);
		}
	}
}

