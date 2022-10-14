#include "InGameUI.h"
//InGameUI* InGameUI::sp_pInstance = nullptr;
void InGameUI::Init(std::string sHPBar, std::string sSTMBar)
{
	g_pHealthBar = cocos2d::ui::LoadingBar::create(sHPBar);
	g_pStaminaBar = cocos2d::ui::LoadingBar::create(sSTMBar);
	g_pHealthBar_Background = cocos2d::Sprite::create("ui/hp_bar_background.png");
	g_pStaminahBar_Background = cocos2d::Sprite::create("ui/stamina_bar_background.png");

	this->addChild(g_pHealthBar);
	g_pHealthBar->setGlobalZOrder(1);
	this->addChild(g_pStaminaBar);
	g_pStaminaBar->setGlobalZOrder(1);

	this->addChild(g_pHealthBar_Background);
	g_pHealthBar_Background->setGlobalZOrder(0);
	this->addChild(g_pStaminahBar_Background);
	g_pStaminahBar_Background->setGlobalZOrder(0);

	
}
void InGameUI::Set_HPSTM_BarPosition(cocos2d::Point pos)
{
	g_pHealthBar->setPosition(cocos2d::Point(pos.x, pos.y - g_pHealthBar->getContentSize().height));
	g_pStaminaBar->setPosition(cocos2d::Point(g_pHealthBar->getPosition().x, g_pHealthBar->getPosition().y - g_pHealthBar->getContentSize().height/2 - g_pStaminaBar->getContentSize().height / 2));
	g_pHealthBar_Background->setPosition(g_pHealthBar->getPosition());
	g_pStaminahBar_Background->setPosition(g_pStaminaBar->getPosition());
}
void InGameUI::Display_HP_Bar(float fMin, float fMax)
{
	g_pHealthBar->setPercent(fMin / fMax * 100);
}
void InGameUI::Display_HP_Bar(float fPercent)
{
	g_pHealthBar->setPercent(fPercent);
}
void InGameUI::Display_STM_Bar(float fPercent)
{
	g_pStaminaBar->setPercent(fPercent);
}
void InGameUI::Display_STM_Bar(float fMin, float fMax)
{
	g_pStaminaBar->setPercent(fMin / fMax * 100);
}
void InGameUI::Disable()
{
	g_pHealthBar->setVisible(false);
	g_pStaminaBar->setVisible(false);
	g_pHealthBar_Background->setVisible(false);
	g_pStaminahBar_Background->setVisible(false);
}

//////////////////////

void PlayerClientUI::Init(std::string sForceBar, std::string sBackground)
{
	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	cocos2d::Vec2 origin = cocos2d::Director::getInstance()->getVisibleOrigin();

	g_pForceBar = cocos2d::ui::LoadingBar::create(sForceBar);
	g_pBackground = cocos2d::Sprite::create(sBackground);
	g_pMemoryForceBar = cocos2d::ui::LoadingBar::create("ui/force_memory.png");
	g_pAngleVector = cocos2d::Sprite::create("ui/angel.png");

	this->addChild(g_pAngleVector);
	g_pAngleVector->setGlobalZOrder(0);
	g_pAngleVector->setAnchorPoint(cocos2d::Point(0, 0.5));
	this->addChild(g_pMemoryForceBar);
	g_pMemoryForceBar->setGlobalZOrder(-1);
	this->addChild(g_pForceBar);
	g_pForceBar->setGlobalZOrder(0);
	this->addChild(g_pBackground);
	g_pBackground->setGlobalZOrder(-3);

	g_pBackground->setPosition(visibleSize / 2);
	g_pForceBar->setPosition(cocos2d::Point(visibleSize.width / 2, g_pForceBar->getContentSize().height * 1.5));
	g_pMemoryForceBar->setPosition(g_pForceBar->getPosition());
}

void PlayerClientUI::DisplayForce(float fMin, float fMax)
{
	this->g_pForceBar->setPercent(fMin / fMax * 100);
}
void PlayerClientUI::DisplayForce(float fPercent)
{
	this->g_pForceBar->setPercent(fPercent);
}
void PlayerClientUI::DisplayForceMemory(float fPercent)
{
	this->g_pMemoryForceBar->setPercent(fPercent);
}
void PlayerClientUI::DisplayForceMemory(float fMin, float fMax)
{
	this->g_pMemoryForceBar->setPercent(fMin / fMax * 100);
}
void PlayerClientUI::Set_AngleVector_Position(cocos2d::Point pos)
{
	g_pAngleVector->setPosition(pos);
}
void PlayerClientUI::Set_Angle_Rotation(int nDegree, DIR eDir)
{
	if (eDir == RIGHT) g_pAngleVector->setRotation(360 - nDegree);
	else g_pAngleVector->setRotation(180 + nDegree);
}
void PlayerClientUI::Disable()
{
	//g_pSkillUI->setVisible(false);
	g_pAngleVector->setVisible(false);
	g_pBackground->setVisible(false);
	g_pForceBar->setVisible(false);
	g_pMemoryForceBar->setVisible(false);
}