#pragma once 
#include "cocos2d.h"

const int MAXRATE = 100000;

struct Fraction
{
public:
	int g_nFirst, g_nSecond;
public:
	void ShortCut()
	{
		int first, second;

		first = abs(this->g_nFirst);
		second = abs(this->g_nSecond);

		while (first != second)
		{
			if (first > second)
			{
				first -= second;
			}
			else
			{
				second -= first;
			}
		}
		this->g_nFirst /= first;
		this->g_nSecond /= second;
	}
	static Fraction FastShortCut(int first, int second)
	{
		Fraction scF;
		scF.g_nFirst = first;
		scF.g_nSecond = second;

		scF.ShortCut();

		return scF;
	}
};

class GameRandom
{
public:
	inline static GameRandom* GetInstance()
	{
		return sp_pInstance = (sp_pInstance != nullptr) ? sp_pInstance : new GameRandom();
	}
	bool GetRandom(float nRate);
private:
	GameRandom (){}
	static GameRandom* sp_pInstance;
};