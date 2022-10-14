#include "SoundManager.h"
SoundManager* SoundManager::sp_pInstance = nullptr;

void SoundManager::PlayGameFightSound()
{
	p_nBattleIndex = cocos2d::AudioEngine::play2d(User::GetInstance()->GetUserSound()->g_sGameFight, true, User::GetInstance()->GetUserSound()->g_fVolume);
	cocos2d::AudioEngine::stop(p_nMenuIndex);
}
void SoundManager::PlayMainMenuSound()
{
	p_nMenuIndex = cocos2d::AudioEngine::play2d(User::GetInstance()->GetUserSound()->g_sMenu, true, User::GetInstance()->GetUserSound()->g_fVolume);
	cocos2d::AudioEngine::stop(p_nBattleIndex);
}
void SoundManager::SetVolume()
{

}
void SoundManager::PlaySoundEffect(std::string sPath)
{
	cocos2d::AudioEngine::play2d(sPath, false, User::GetInstance()->GetUserSound()->g_fVolume);
}