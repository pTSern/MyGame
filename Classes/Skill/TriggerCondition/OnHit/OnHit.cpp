#include "OnHit.h"
//static SkillConditionRegister<OnHit> s_register("ONHIT");

void OnHit::AutoCheckCondition()
{
	if (m_pCaster->GetChampionAction() == ChampionAction::GET_HIT)
	{
		this->m_bIsMatchCondition = true;
	}
}
void  OnHit::CallCheckCondition()
{
}
void OnHit::Cleaner()
{
	TriggerCondition::Cleaner();
}