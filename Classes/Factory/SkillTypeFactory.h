#pragma once
#include "Skill/SkillType/SkillType.h"
#include "cocos2d.h"

class SkillTypeFactory
{
public:
	static SkillTypeFactory* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new SkillTypeFactory(); }
	bool RegisterType(std::string typeID, std::function<SkillType* ()> pCreator);
	SkillType* Create(std::string typeID);
private:
	SkillTypeFactory() {};
	std::map<std::string, std::function<SkillType*()>> m_creators;
	static SkillTypeFactory* s_Instance;
};

template<class Type>
class SkillTypeRegister
{
public:
	SkillTypeRegister(std::string className)
	{
		SkillTypeFactory::GetInstance()->RegisterType(className, []()->SkillType* {return new Type(); });
	};
};
