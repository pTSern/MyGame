#pragma once
#include "Physic/BulletPhysic.h"
class BulletPhysicFactory
{
public:
	static BulletPhysicFactory* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new BulletPhysicFactory(); }
	bool RegisterType(std::string typeID, std::function<BulletPhysic* ()> pCreator);
	BulletPhysic* Create(std::string typeID);
private:
	BulletPhysicFactory(){}
	std::map<std::string, std::function<BulletPhysic* ()>> m_creators;
	static BulletPhysicFactory* s_Instance;
};

template<class Type>
class PhysicRegister
{
public:
	PhysicRegister(std::string className)
	{
		BulletPhysicFactory::GetInstance()->RegisterType(className, []()->BulletPhysic* {return new Type(); });
	};
};