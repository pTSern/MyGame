//#pragma once
//#include "ShopChild_Type.h"
//
//void ShopType_Display::Init()
//{
//	
//}
//
//void ShopType_Display::AddChilds(cocos2d::Node* pNode, ...)
//{
//	cocos2d::Vector<cocos2d::Node*> vN = this->p_vChildL;
//	va_list args;
//	va_start(args, pNode);
//
//	if (pNode)
//	{
//		vN.pushBack(pNode);
//		cocos2d::Node* i = va_arg(args, cocos2d::Node*);
//
//		while (i)
//		{
//			vN.pushBack(i);
//			i = va_arg(args, cocos2d::Node*);
//		}
//	}
//
//	va_end(args);
//
//	this->p_vChildL = vN;
//}
//
//void ShopType_Display::RunChild(cocos2d::Node *pNode)
//{
//	if (!p_bIsRunning)
//	{
//		int i = 0;
//		for (auto x : p_vChildL)
//		{
//			//pNode->addChild(x, p_vActiveChild[i]->g_nOrder, p_vActiveChild[i]->g_sName);
//			pNode->addChild(x);
//			i++;
//		}
//	}
//	p_bIsRunning = true;
//}
//	
//
//void ShopType_Display::StopChild(cocos2d::Node* pNode)
//{
//	if (p_bIsRunning)
//	{
//		for (const auto& x : p_vChildL)
//		{
//			pNode->removeChild(x);
//		}
//		p_bIsRunning = false;
//	}
//}
//
//void ShopType_Display::Previous(cocos2d::Ref* pSender)
//{
//	if (g_nCurrentIndex > 0) g_nCurrentIndex--;
//}
//
//void ShopType_Display::Next(cocos2d::Ref* pSender)
//{
//	if (g_nCurrentIndex < g_nMaxPage) g_nCurrentIndex++;
//}