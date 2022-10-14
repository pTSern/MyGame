#include "OnClick.h"
static SkillConditionRegister<OnClick> s_register("ONCLICK");
OnClick::OnClick() : TriggerCondition()
{

}
bool OnClick::ConditionMatch()
{
	return this->m_bIsMatchCondition;
}
void OnClick::AutoCheckCondition()
{

}
void OnClick::CallCheckCondition()
{
	this->m_bIsMatchCondition = true;
}
void OnClick::Cleaner()
{
	TriggerCondition::Cleaner();
}