#include "GameRandom.h"

GameRandom* GameRandom::sp_pInstance = nullptr;

bool GameRandom::GetRandom(float fRate)
{
	if (fRate >= 100) return true;
	if (fRate <= 0) return false;

	int nRate = 1000 * fRate;

	Fraction frac = Fraction::FastShortCut(nRate, MAXRATE);
	int luckyNumber = cocos2d::random(1, frac.g_nSecond);

	if ( frac.g_nFirst * 2 <= frac.g_nSecond && luckyNumber % 2 == 0 && luckyNumber <= frac.g_nFirst * 2)
	{
		//cocos2d::log("%d", luckyNumber);
		return true;
	}

	if (frac.g_nFirst * 2 > frac.g_nSecond)
	{
		if (luckyNumber % 2 == 0)
		{
			//cocos2d::log("%d", luckyNumber);
			return true;
		}
		else if (luckyNumber % 2 != 0 && luckyNumber <= (frac.g_nFirst - (frac.g_nSecond / 2)) - 1)
		{
			//cocos2d::log("%d", luckyNumber);
			return true;
		}
	}
	//cocos2d::log("%d", luckyNumber);
	return false;
}