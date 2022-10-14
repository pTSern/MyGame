#pragma once

struct ShopEconomy
{
public:
	ShopEconomy(float fPriceXu = 0, float fPriceSp = 0, bool bIsSale = 0, float fSaleXu = 0, float fSaleSp = 0)
	{
		g_fPriceXu = fPriceXu;
		g_fPriceSp = fPriceSp;
		g_bIsSale = bIsSale;
		g_fSaleXu = fSaleXu;
		g_fSaleSp = fSaleSp;
	}
	float g_fPriceXu, g_fPriceSp;
	bool g_bIsSale;
	float g_fSaleXu, g_fSaleSp;
};

