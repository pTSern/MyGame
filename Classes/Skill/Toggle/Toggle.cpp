#include "Toggle.h"
static SkillRegister<ToggleSkill> s_register("TOGGLE");
ToggleSkill::ToggleSkill() : Skill()
{
	this->m_sType = "Toggle";
}