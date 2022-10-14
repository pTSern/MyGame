#pragma once
#include "Extention/Statics_Attributes.h"
#include "Extention/Node_StringNTag.h"
#include "GameObject/GameObject.h"
#include "cocos2d.h"

struct BulletStatic
{
public:
	void Init(int nBulletNum = 0, std::string sPhysicType = "", std::string sBulletTexture = "", float fShootDelay = 0)
	{
		this->g_nBulletNum = nBulletNum;
		this->g_sPhysicType = sPhysicType;
		this->g_sBulletTexture = sBulletTexture;
		this->g_fShootDelay = fShootDelay;
	}
public:
	int g_nBulletNum;
	std::string g_sPhysicType, g_sBulletTexture;
	float g_fShootDelay;
};

struct BulletElement
{
public:
	BulletElement()
	{
		g_bIsNeedRemove = false;
		g_fRotation = 0, g_fRotationSpeed = 300;
		g_fTime = 0, g_fFlySpeed = 18;
		g_bIsThroughPlayer = false, g_bIsThroughMap = false, g_bIsBouncing = false;
		g_fMass = 1;
		g_bIsContactPlayer = false;
	}
public:
	inline void SetIsNeedRemove(bool enable) { this->g_bIsNeedRemove = enable; }
	inline float GetRotation() { return g_fRotation; }
	inline void SetRotation(float rotation) 
	{ 
		g_fRotation = rotation; 
		
	}
	inline float GetRotationSpeed() {return g_fRotationSpeed; }
	inline void SetRotationSpeed(float spd) { this->g_fRotationSpeed = spd; }
	inline float GetTime() {return this->g_fTime; }
	inline float SetTime(float time) { this->g_fTime = time; }
	inline float GetFlySpeed() {return this->g_fFlySpeed;}
	inline void SetFlySpeed(float spd) { this->g_fFlySpeed = spd; }
	
	inline bool GetIsThroughPlayer() { return this->g_bIsThroughPlayer; }
	inline bool GetIsThroughMap() {return this->g_bIsThroughMap; }
	inline bool GetIsBoucingSideMap() { return this->g_bIsBouncing; }

	inline void SetIsThroughPlayer(bool enable) {this->g_bIsThroughPlayer = enable;}
	inline void SetIsThroughMap(bool enable) {this->g_bIsThroughMap = enable;}
	inline void SetIsBoucingSideMap(bool enable) {this->g_bIsBouncing = enable;}

	inline void SetMass(float mass) { this->g_fMass = mass; }
	inline float GetMass() {return this->g_fMass;}

	inline bool GetIsContactPlayer() { return this->g_bIsContactPlayer; }
	inline void SetIsContactPlayer(bool isContact) { this->g_bIsContactPlayer = isContact; }
public:
	bool g_bIsNeedRemove;
	float g_fRotation, g_fRotationSpeed;
	float g_fTime, g_fFlySpeed;
	bool g_bIsThroughPlayer, g_bIsThroughMap, g_bIsBouncing;
	cocos2d::Point g_pPreviousXY;
	float g_fMass;
	bool g_bIsContactPlayer;
};

class Bullet : public GameObject
{
public:
	//friend class BulletManager;
	Bullet(const XProperties* pProperties) : GameObject(pProperties)
	{
		this->SetContestBitMark(Node_StringNTag::BulletContactBitmask());
		m_pSprite->setTag(1);
	}
	void Init(SkillStatics* pChampSkill, BulletElement* pBulletElement)
	{
		this->m_pChampSkill = pChampSkill;
		this->m_pBulletElement = pBulletElement;
	}
	void Init(SkillStatics* pChampSkill)
	{
		this->m_pChampSkill = pChampSkill;
		m_pBulletElement = new (std::nothrow) BulletElement();
	}
public:
	static Bullet* Clone(Bullet* pB)
	{

	}
	static Bullet* Create(const XProperties* pProperties)
	{
		Bullet* pB = new (std::nothrow) Bullet(pProperties);
		if (pB) return pB;
		else CC_SAFE_DELETE(pB);

		return nullptr;
	}
	static Bullet* Create(const XProperties* pProperties, SkillStatics* pChampSkill, BulletElement* pBulletElement)
	{
		Bullet* pB = new (std::nothrow) Bullet(pProperties);
		
		if (pB && pChampSkill && pBulletElement)
		{
			pB->Init(pChampSkill, pBulletElement);
			return pB;
		}
		else CC_SAFE_DELETE(pB);

		return nullptr;
	}
	static Bullet* Create(std::string textureID, cocos2d::Point* position = nullptr, int nLocalZOrder = 0, bool bIsPhysic = false)
	{
		XProperties* pProperties = new XProperties(textureID, 0, 0, true);
		Bullet* pB = new (std::nothrow) Bullet(pProperties);
		XProperties::Cleaner(pProperties);
		if (pB) return pB;
		else CC_SAFE_DELETE(pB);

		return nullptr;
	}
	static Bullet* Create(SkillStatics* pChampSkill, BulletElement* pBulletElement, std::string textureID, cocos2d::Point* position = nullptr, int nLocalZOrder = 0, bool bIsPhysic = false)
	{
		XProperties* pProperties = new XProperties(textureID, 0, 0, true);
		Bullet* pB = new (std::nothrow) Bullet(pProperties);
		XProperties::Cleaner(pProperties);
		if (pB && pChampSkill && pBulletElement)
		{
			pB->Init(pChampSkill, pBulletElement);
			return pB;
		}
		else CC_SAFE_DELETE(pB);

		return nullptr;
	}
	static Bullet* Create(SkillStatics* pChampSkill, std::string textureID, cocos2d::Point* position = nullptr, int nLocalZOrder = 0, bool bIsPhysic = false)
	{
		XProperties* pProperties = new XProperties(textureID, 0, 0, true);
		Bullet* pB = new (std::nothrow) Bullet(pProperties);
		XProperties::Cleaner(pProperties);
		if (pB && pChampSkill)
		{
			pB->Init(pChampSkill);
			return pB;
		}
		else CC_SAFE_DELETE(pB);

		return nullptr;
	}
public:
	virtual void Update(float dt)
	{
		m_pPhysicBody->setRotationOffset(this->m_pBulletElement->g_fRotation);
		GameObject::Update(dt);
	}
	virtual void Cleaner()
	{
		CC_SAFE_DELETE(m_pChampSkill);
		CC_SAFE_DELETE(m_pBulletElement);
		GameObject::Cleaner();
	}
public:
	inline cocos2d::Sprite* GetBulletSprite() { return this->m_pSprite; }
	inline cocos2d::Point GetPosition() { return this->m_pSprite->getPosition(); }
	inline void AutoRotation(float dt) { m_pBulletElement->g_fRotation += dt * m_pBulletElement->g_fRotationSpeed; }
	inline void AutoIncreaseTime(float dt) { m_pBulletElement->g_fTime += dt * m_pBulletElement->g_fFlySpeed; }
	inline float GetTime() {return m_pBulletElement->g_fTime; }
	inline bool GetIsNeedRemoveBullet() { return m_pBulletElement->g_bIsNeedRemove; }
	inline float GetMass() { return this->m_pBulletElement->g_fMass; };
	inline cocos2d::Size GetContentSzie() { return this->m_pSprite->getContentSize(); }
	inline bool IsThroughMap() { return this->m_pBulletElement->g_bIsThroughMap; }
	inline bool IsBouncing() {return this->m_pBulletElement->g_bIsBouncing; }
	inline void Rotate() { this->m_pSprite->setRotation(m_pBulletElement->g_fRotation); }
	inline BulletElement* GetBulletStatic() { return this->m_pBulletElement; }
	inline SkillStatics* GetSkillStatics() {return this->m_pChampSkill;}
	inline bool IsContactPlayer() 
	{ 
		return this->m_pBulletElement->g_bIsContactPlayer; 
	}
	inline void ContactToPlayer() { this->m_pBulletElement->SetIsContactPlayer(true); }
protected:
	SkillStatics* m_pChampSkill;
	BulletElement* m_pBulletElement;
};