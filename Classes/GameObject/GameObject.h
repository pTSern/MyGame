#pragma once
#include "cocos2d.h"
#include "AGameObject.h"
class GameObject : public AGameObject
{
public:
	GameObject(const XProperties* pProperties);
	virtual ~GameObject() = default;
	//virtual void Draw();
	virtual void Update(float dt);
	virtual void Cleaner();
public:
	void SetPosition(cocos2d::Point pos);
	void SetNPosition(cocos2d::Point pos);
public:
	void UpdateSprite(std::string textureID)
	{ 
		m_pSprite->setTexture(textureID); 
	}
	cocos2d::Sprite* GetSprite() 
	{
		return m_pSprite;
	}
	std::string GetSText()
	{
		return this->m_sTextureID;
	}
	void SetDynamicPhysic(bool yesORno)
	{
		m_pPhysicBody->setDynamic(yesORno);
	}
	void SetGravityEffect(bool yesORno)
	{
		m_pPhysicBody->setGravityEnable(yesORno);
	}
	void SetContestBitMark(int nNum)
	{
		m_pPhysicBody->setContactTestBitmask(nNum);
	}
	inline int GetContestBitMark()
	{
		return m_pPhysicBody->getContactTestBitmask();
	}
protected:
	std::string m_sTextureID;
	cocos2d::Point* m_pPosition;
	cocos2d::Sprite* m_pSprite;
	cocos2d::PhysicsBody* m_pPhysicBody;

	bool m_bIsPhysicsBody;
};