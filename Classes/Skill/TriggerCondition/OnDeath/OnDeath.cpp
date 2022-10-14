#include "OnDeath.h"
static SkillConditionRegister<OnDeath> s_register("ONDEATH");
OnDeath::OnDeath() : TriggerCondition()
{

}
void OnDeath::AutoCheckCondition()
{
	if (m_pCaster->GetChampionAction() == ChampionAction::DYING)
	{
		this->m_bIsMatchCondition = true;
	}
}
void OnDeath::CallCheckCondition()
{
}
void OnDeath::Cleaner()
{
	TriggerCondition::Cleaner();
}