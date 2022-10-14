#pragma once
#include "cocos2d.h"
#include "Node_StringNTag.h"
#include "ui/CocosGUI.h"
#include "Extention/Statics_Attributes.h"
class InGameUI : public cocos2d::Node
{
public:
	cocos2d::Sprite* g_pHealthBar_Background, * g_pStaminahBar_Background;
	cocos2d::ui::LoadingBar * g_pHealthBar, * g_pStaminaBar;

	int g_displayForce, g_displayMemForce, g_displayMemAngle;
public:
	void Init(std::string sHPBar, std::string sSTMBar);
	void Set_HPSTM_BarPosition(cocos2d::Point pos);
	void Display_HP_Bar(float fMin, float fMax);
	void Display_HP_Bar(float fPercent);
	void Display_STM_Bar(float fPercent);
	void Display_STM_Bar(float fMin, float fMax);
	void Disable();
};

class PlayerClientUI : public cocos2d::Node
{
public:
	cocos2d::Sprite* g_pSkillUI;
	cocos2d::Sprite* g_pAngleVector;
	cocos2d::Sprite* g_pBackground;
	cocos2d::ui::LoadingBar* g_pForceBar, * g_pMemoryForceBar;
public:
	void Init(std::string sForceBar, std::string sBackground);
	void DisplayForce(float fPercent);
	void DisplayForceMemory(float fPercent);
	void DisplayForce(float fMin, float fMax);
	void DisplayForceMemory(float fMin, float fMax);
	void Set_AngleVector_Position(cocos2d::Point pos);
	void Set_Angle_Rotation(int nDegree, DIR eDir);
	void Disable();
};

