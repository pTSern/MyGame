#include "AI/AI.h"
class BotFactory
{
public:
	static BotFactory* GetInstance()
	{
		return sp_pInstance = (sp_pInstance != nullptr) ? sp_pInstance : new BotFactory();
	}
	bool RegisterType(std::string typeID, std::function<AI* ()> pCreator);
	AI* Create(std::string typeID);

private:
	static BotFactory* sp_pInstance;
	std::map<std::string, std::function<AI* ()>> m_creators;
};

template<class Type>
class BotRegister
{
public:
	BotRegister(std::string className)
	{
		BotFactory::GetInstance()->RegisterType(className, []()->AI* {return new Type(); });
	};
};