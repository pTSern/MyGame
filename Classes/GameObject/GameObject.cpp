#pragma once
#include "GameObject.h"
GameObject::GameObject(const XProperties* pProperties) : AGameObject(pProperties)
{
	m_sTextureID = pProperties->GetTextureID();
	m_pPosition = pProperties->GetPosition();
	m_pSprite = cocos2d::Sprite::create(m_sTextureID);
	if (m_pPosition) m_pSprite->setPosition(*m_pPosition);
	if (pProperties->GetIsPhysic())
	{
		m_pPhysicBody = cocos2d::PhysicsBody::createBox(m_pSprite->getContentSize());
		m_pPhysicBody->setDynamic(false);
		m_pPhysicBody->setGravityEnable(false);
		//m_pPhysicBody->setContactTestBitmask(2);
		
		
		this->setPhysicsBody(m_pPhysicBody);
	}

	this->addChild(m_pSprite);
}
void GameObject::SetPosition(cocos2d::Point pos)
{
	m_pSprite->setPosition(pos);
}
void GameObject::SetNPosition(cocos2d::Point pos)
{
	cocos2d::Node::setPosition(pos);
}
void GameObject::Update(float dt)
{
	m_pPhysicBody->setPositionOffset(m_pSprite->getPosition());
}
void GameObject::Cleaner()
{
	m_pSprite->release();
	CC_SAFE_DELETE(m_pSprite);
	CC_SAFE_DELETE(m_pPosition);
	m_pPhysicBody->release();
	m_pPhysicBody->onRemove();
}