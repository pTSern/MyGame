#include "GameEnvironment.h"

GameEnvironment* GameEnvironment::sp_pInstance = nullptr;

void GameEnvironment::GenerateWindForce()
{
	p_nWindFroce = cocos2d::random(-15, 15);
	if (p_nWindFroce >= 0) p_eWindDir = RIGHT;
	else p_eWindDir = LEFT;

	p_pWindForceText->setString(std::to_string(p_nWindFroce * p_eWindDir).c_str());
	p_pWindTexture->setRotation(90 + (int)p_eWindDir * 90);
	cocos2d::log(("     WIND FORCE: " + std::to_string(p_nWindFroce) + " WIND DIR: " + std::to_string(p_eWindDir)).c_str());

}