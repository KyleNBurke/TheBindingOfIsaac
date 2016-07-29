#include "stdafx.h"
#include "AnimationSystem.hpp"
#include "AnimationCom.hpp"
#include "AnimationStateStatic.hpp"
#include "AnimationStateDynamic.hpp"
#include "ProjectileCom.hpp"
#include "LifetimeCom.hpp"
#include "Utilities.hpp"

AnimationSystem::AnimationSystem(const sf::Time& deltaTime) : deltaTime(deltaTime) {}

void AnimationSystem::update(Entity& entity)
{
	if(entity.hasComponent(Component::ComponentType::Animation))
	{
		std::shared_ptr<AnimationCom> animCom = std::dynamic_pointer_cast<AnimationCom>(entity.getComponent(Component::ComponentType::Animation));
		std::shared_ptr<AnimationState> currentState(animCom->states[animCom->currentState]);

		if(currentState->getType() == AnimationState::AnimationStateType::Dynamic)
		{
			std::shared_ptr<AnimationStateDynamic> state = std::dynamic_pointer_cast<AnimationStateDynamic>(currentState);

			state->elapsedTime += deltaTime.asSeconds();

			if(state->elapsedTime > state->frameTime)
			{
				state->elapsedTime = 0.0f;
				state->currentFrame = ++state->currentFrame % state->frameCount;
			}

			sf::IntRect frame = state->initialFrame;
			frame.left = frame.left + state->currentFrame * frame.width;

			entity.sprite.setTextureRect(frame);
		}
		else
		{
			std::shared_ptr<AnimationStateStatic> state = std::dynamic_pointer_cast<AnimationStateStatic>(currentState);

			if(!state->set)
				entity.sprite.setTextureRect(state->frame);
		}
	}
}