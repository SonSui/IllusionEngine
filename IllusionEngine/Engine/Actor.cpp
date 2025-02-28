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
	// Game����Actor���폜
	mGame->RemoveActor(this);
	// Components���폜
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
	// �X�V���ɒǉ�
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
	// �R���|�[�l���g�̃^�C�v���}�X�N�ɒǉ�
	uint64_t type = component->GetComponentType();
	mComponentMask |= type;
}

void Actor::RemoveComponent(class Component* component)
{
    // Components �ɒT���č폜
	auto target = std::find(mComponents.begin(), mComponents.end(), component);
	if (target != mComponents.end()) {
		uint32_t type = component->GetComponentType();

		// �폜
		delete* target;
		mComponents.erase(target);

		// �����^�C�v�̃R���|�[�l���g���c���Ă��邩�ǂ������m�F
		bool hasSameType = false;
		for (Component* comp : mComponents) {
			if (comp->GetComponentType() == type) {
				hasSameType = true;
				break;
			}
		}

		// �Ȃ��ꍇ�́A�}�X�N���X�V
		if (!hasSameType) {
			mComponentMask &= ~type; // �r�b�g���Z��type�̌���0�ɐݒ�
		}
	}
}