#pragma once
#include "cocos2d.h"
#include "User/User.h"
class SoundManager
{
public:
	inline static SoundManager* GetInstance()
	{
	   return sp_pInstance = (sp_pInstance != nullptr) ? sp_pInstance : new SoundManager();	
	}
public:
	void PlayGameFightSound();
	void PlayMainMenuSound();
	void SetVolume();
	void PlaySoundEffect(std::string sPath);
	inline void Cleaner()
	{
		cocos2d::AudioEngine::end();
	}
private:
	SoundManager(){}
	static SoundManager *sp_pInstance;
	int p_nBattleIndex, p_nMenuIndex;
};
