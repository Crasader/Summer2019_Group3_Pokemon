#include "Trainer.h"

Trainer::Trainer(cocos2d::Layer* layer)
{
	m_currentState = state_start;
	m_sprite = Sprite::create("res/Map/0.png");
	m_sprite->setAnchorPoint(Vec2(0.5f, 0));
	m_sprite->retain();
	layer->addChild(m_sprite);
	Vector<SpriteFrame*> animFrames;
	//idle left right up down
	//walk up down left right
	//run left right up down
}

Trainer::~Trainer()
{
}

int Trainer::getCurrentState()
{
	return m_currentState;
}

void Trainer::walkLeft()
{
	//setState(Trainer::state_walkLeft);
	m_sprite->setPosition(Vec2(m_sprite->getPosition().x -1, m_sprite->getPosition().y ));
}

void Trainer::walkRight()
{
	//setState(Trainer::state_walkRight);
	m_sprite->setPosition(Vec2(m_sprite->getPosition().x +1, m_sprite->getPosition().y));
}

void Trainer::walkUp()
{
	//setState(Trainer::state_walkUp);
	m_sprite->setPosition(Vec2(m_sprite->getPosition().x , m_sprite->getPosition().y +1));
}

void Trainer::walkDown()
{
	//setState(Trainer::state_walkDown);
	m_sprite->setPosition(Vec2(m_sprite->getPosition().x , m_sprite->getPosition().y -1));
}

void Trainer::runLeft()
{
	setState(Trainer::state_runLeft);
}

void Trainer::runRight()
{
	setState(Trainer::state_runRight);
}

void Trainer::runUp()
{
	setState(Trainer::state_runUp);
}

void Trainer::runDown()
{
	setState(Trainer::state_runDown);
}

void Trainer::setState(int nextState)
{
	if (!((m_currentState == state_idleDown || m_currentState == state_idleLeft || m_currentState == state_idleRight || m_currentState == state_walkUp || m_currentState == state_walkDown || m_currentState == state_walkLeft || m_currentState == state_walkRight || m_currentState == state_runUp || m_currentState == state_runDown || m_currentState == state_runLeft || m_currentState == state_runRight) && m_sprite->getNumberOfRunningActions() > 0))
	{
		switch (nextState)
		{
		case state_start:
			setState(state_idleUp);
			break;
		case state_idleUp:
			if (nextState != m_currentState)
			{
				m_sprite->stopAllActions();
				m_sprite->runAction(m_animation[anime_idleUp]);
			}
			else if (m_sprite->getNumberOfRunningActions() == 0)//alway set if action finished
			{
				m_sprite->runAction(m_animation[anime_idleUp]);
			}
		break;
		case state_idleDown:
			if (nextState != m_currentState)
			{
				m_sprite->stopAllActions();
				m_sprite->runAction(m_animation[anime_idleDown]);
			}
			else if (m_sprite->getNumberOfRunningActions() == 0)//alway set if action finished
			{
				m_sprite->runAction(m_animation[anime_idleDown]);
			}
			break;
		case state_idleLeft:
			if (nextState != m_currentState)
			{
				m_sprite->stopAllActions();
				m_sprite->runAction(m_animation[anime_idleLeft]);
			}
			else if (m_sprite->getNumberOfRunningActions() == 0)//alway set if action finished
			{
				m_sprite->runAction(m_animation[anime_idleLeft]);
			}
			break;
		case state_idleRight:
			if (nextState != m_currentState)
			{
				m_sprite->stopAllActions();
				m_sprite->runAction(m_animation[anime_idleRight]);
			}
			else if (m_sprite->getNumberOfRunningActions() == 0)//alway set if action finished
			{
				m_sprite->runAction(m_animation[anime_idleRight]);
			}
			break;

		case state_walkUp:
			if (nextState != m_currentState)
			{
				m_sprite->stopAllActions();
				m_sprite->runAction(m_animation[anime_walkUp]);
			}
			else if (m_sprite->getNumberOfRunningActions() == 0)//alway set if action finished
			{
				m_sprite->runAction(m_animation[anime_walkUp]);
			}
			break;
		case state_walkDown:
			if (nextState != m_currentState)
			{
				m_sprite->stopAllActions();
				m_sprite->runAction(m_animation[anime_walkDown]);
			}
			else if (m_sprite->getNumberOfRunningActions() == 0)//alway set if action finished
			{
				m_sprite->runAction(m_animation[anime_walkDown]);
			}
			break;

		case state_walkLeft:
			if (nextState != m_currentState)
			{
				m_sprite->stopAllActions();
				m_sprite->runAction(m_animation[anime_walkLeft]);
			}
			else if (m_sprite->getNumberOfRunningActions() == 0)//alway set if action finished
			{
				m_sprite->runAction(m_animation[anime_walkLeft]);
			}
			break;
		case state_walkRight:
			if (nextState != m_currentState)
			{
				m_sprite->stopAllActions();
				m_sprite->runAction(m_animation[anime_walkRight]);
			}
			else if (m_sprite->getNumberOfRunningActions() == 0)//alway set if action finished
			{
				m_sprite->runAction(m_animation[anime_walkRight]);
			}
			break;
		case state_runUp:
			if (nextState != m_currentState)
			{
				m_sprite->stopAllActions();
				m_sprite->runAction(m_animation[anime_runUp]);
			}
			else if (m_sprite->getNumberOfRunningActions() == 0)//alway set if action finished
			{
				m_sprite->runAction(m_animation[anime_runUp]);
			}
			break;

		case state_runDown:
			if (nextState != m_currentState)
			{
				m_sprite->stopAllActions();
				m_sprite->runAction(m_animation[anime_runDown]);
			}
			else if (m_sprite->getNumberOfRunningActions() == 0)//alway set if action finished
			{
				m_sprite->runAction(m_animation[anime_runDown]);
			}
			break;
		case state_runLeft:
			if (nextState != m_currentState)
			{
				m_sprite->stopAllActions();
				m_sprite->runAction(m_animation[anime_runLeft]);
			}
			else if (m_sprite->getNumberOfRunningActions() == 0)//alway set if action finished
			{
				m_sprite->runAction(m_animation[anime_runLeft]);
			}
			break;
		case state_runRight:
			if (nextState != m_currentState)
			{
				m_sprite->stopAllActions();
				m_sprite->runAction(m_animation[anime_runRight]);
			}
			else if (m_sprite->getNumberOfRunningActions() == 0)//alway set if action finished
			{
				m_sprite->runAction(m_animation[anime_runRight]);
			}
			break;
		}
		m_currentState = nextState;
	}
}
void Trainer::update(float dt)
{
	setState(Trainer::state_idleUp);
}

Sprite * Trainer::GetSprite()
{
	return m_sprite;
}
