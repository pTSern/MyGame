#include "Player/Player.h"
class PlayerFactory
{
public:
	static PlayerFactory* GetInstance()
	{
		return p_pInstance = (p_pInstance != nullptr) ? p_pInstance : new PlayerFactory();
	}
	bool RegisterType(std::string typeID, std::function<Player* ()> pCreator);
	Player* Create(std::string typeID);
private:
	PlayerFactory() {};
	std::map<std::string, std::function<Player* ()>> m_creators;
	static PlayerFactory* p_pInstance;
};


template<class Type>
class PlayerRegister
{
public:
	PlayerRegister(std::string className)
	{
		PlayerFactory::GetInstance()->RegisterType(className, []()->Player* {return new Type(); });
	};
};