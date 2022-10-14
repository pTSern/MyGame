#include "Active.h"
static SkillRegister<ActiveSkill> s_register("ACTIVE");

ActiveSkill::ActiveSkill() : Skill()
{
	this->m_sType = "Active";
}
void ActiveSkill::Cleaner()
{
	Skill::Cleaner();
}