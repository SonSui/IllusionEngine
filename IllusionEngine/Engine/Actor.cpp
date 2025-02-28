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
	// Game‚©‚çActor‚ğíœ
	mGame->RemoveActor(this);
	// Components‚ğíœ
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
}

void Actor::RemoveComponent(class Component* component)
{
    // Components ‚É’T‚µ‚Äíœ
    auto target = std::find(mComponents.begin(), mComponents.end(), component);
    if (target != mComponents.end()) {
        delete* target;
        mComponents.erase(target);  
    }
}