#include "Passive.h"
static SkillRegister<PassiveSkill> s_register("PASSIVE");
PassiveSkill::PassiveSkill() : Skill()
{
	this->m_sType = "Passive";
}
void PassiveSkill::Cleaner()
{
	Skill::Cleaner();
}