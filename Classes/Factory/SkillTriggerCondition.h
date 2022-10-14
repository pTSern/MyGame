#pragma once
#include "Skill/TriggerCondition/TriggerCondition.h"
#include "cocos2d.h"

class SkillConditionFactory
{
public:
	static SkillConditionFactory* GetInstance() { return s_Instance = (s_Instance != nullptr) ? s_Instance : new SkillConditionFactory(); }
	bool RegisterType(std::string typeID, std::function<TriggerCondition* ()> pCreator);
	TriggerCondition* Create(std::string typeID);
private:
	SkillConditionFactory() {};
	std::map<std::string, std::function<TriggerCondition*()>> m_creators;
	static SkillConditionFactory* s_Instance;
};

template<class Type>
class SkillConditionRegister
{
public:
	SkillConditionRegister(std::string className)
	{
		SkillConditionFactory::GetInstance()->RegisterType(className, []()->TriggerCondition* {return new Type(); });
	};
};
