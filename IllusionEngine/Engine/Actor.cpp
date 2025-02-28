#include "Actor.h"

Actor::Actor(GameMain* game) :mState(EActive)
, mPosition(Vector2::Zero)
, mScale(1.0f)
, mRotation(0.0f)
, mGame(game)
, mComponentMask(0)
{
	mGame->AddActor(this);
}

Actor::~Actor()
{
	// GameからActorを削除
	mGame->RemoveActor(this);
	// Componentsを削除
	while (!mComponents.empty())
	{
		Component* com = mComponents.back();
		mComponents.pop_back();
		delete com;
	}
}



void Actor::Update(float deltaTime)
{
	if (mState == EActive)
	{
		UpdateComponents(deltaTime);
		UpdateActor(deltaTime);
	}
}
void Actor::UpdateComponents(float deltaTime)
{
	for (auto com : mComponents)
	{
		com->Update(deltaTime);
	}
}
void Actor::UpdateActor(float deltaTime)
{

}


void Actor::AddComponent(class Component* component)
{
	// 更新順に追加
	int myOrder = component->GetUpdateOrder();
	auto iter = mComponents.begin();
	for (;
		iter != mComponents.end();
		++iter)
	{
		if (myOrder < (*iter)->GetUpdateOrder())
		{
			break;
		}
	}
	mComponents.insert(iter, component);
	// コンポーネントのタイプをマスクに追加
	uint64_t type = component->GetComponentType();
	mComponentMask |= type;
}

void Actor::RemoveComponent(class Component* component)
{
    // Components に探して削除
	auto target = std::find(mComponents.begin(), mComponents.end(), component);
	if (target != mComponents.end()) {
		uint32_t type = component->GetComponentType();

		// 削除
		delete* target;
		mComponents.erase(target);

		// 同じタイプのコンポーネントが残っているかどうかを確認
		bool hasSameType = false;
		for (Component* comp : mComponents) {
			if (comp->GetComponentType() == type) {
				hasSameType = true;
				break;
			}
		}

		// ない場合は、マスクを更新
		if (!hasSameType) {
			mComponentMask &= ~type; // ビット演算でtypeの桁を0に設定
		}
	}
}