#include "Actor.h"

Actor::Actor(GameMain* game)
{
    mGame = game;
}

Actor::~Actor()
{
}



void Actor::Update(float deltaTime)
{
}
void Actor::UpdateComponents(float deltaTime)
{
}
void Actor::UpdateActor(float deltaTime)
{
}


void Actor::AddComponent(class Component* component)
{
	mComponents.emplace_back(component);
}

void Actor::RemoveComponent(class Component* component)
{

    auto target = std::find(mComponents.begin(), mComponents.end(), component);

    if (target != mComponents.end()) {
        delete* target;
        mComponents.erase(target);  
    }


}