#pragma once
#include "Champion/Champion.h"
class TriggerCondition
{
public:
	TriggerCondition() 
	{
		m_bIsMatchCondition = false;
	}
	void Init(Champion* pCaster)
	{
		this->m_pCaster = pCaster;
	}
	virtual void Cleaner()
	{
		//CC_SAFE_DELETE(m_pCaster);
	}
	virtual bool ConditionMatch()
	{
		return this->m_bIsMatchCondition;
	}
	virtual void AutoCheckCondition() = 0;
	virtual void CallCheckCondition() = 0;
protected:
	bool m_bIsMatchCondition;
	Champion* m_pCaster;
};
