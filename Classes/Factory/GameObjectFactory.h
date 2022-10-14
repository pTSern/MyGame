#pragma once
#include "GameObject/GameObject.h"
#include "cocos2d.h"

class GameObjectFactory
{
public:
	static GameObjectFactory* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new GameObjectFactory(); }
	bool RegisterType(std::string typeID, std::function<GameObject* (XProperties* pProperties)> pCreator);
	GameObject* Create(std::string typeID, XProperties* pProperties);
private:
	GameObjectFactory() {};
	std::map<std::string, std::function<GameObject*(XProperties* pProperties)>> m_creators;
	static GameObjectFactory* s_Instance;
};

template<class Type>
class Register
{
public:
	Register(std::string className)
	{
		GameObjectFactory::GetInstance()->RegisterType(className, [](XProperties* pProperties)->GameObject* {return new Type(pProperties); });
	};
};
