#include "AlwayActive.h"
static SkillConditionRegister<AlwayActive> s_register("ALWAYACTIVE");
AlwayActive::AlwayActive() : TriggerCondition()
{

}
void AlwayActive::AutoCheckCondition()
{
	if (m_pCaster->GetStatics()->g_fHP > 0)
	{
		this->m_bIsMatchCondition = true;
	}
}
void AlwayActive::CallCheckCondition()
{
}