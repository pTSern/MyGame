#pragma once
#include "cocos2d.h"
#include <string>
class XProperties
{
public:
	XProperties(std::string textureID = "", cocos2d::Point* position = nullptr, int nLocalZOrder = 0, bool bIsPhysic = false) :
		p_sTextureID(textureID), 
		p_pPosition(position), 
		p_nLocalZOrder(nLocalZOrder),
		p_bIsPhysic(bIsPhysic)
	{};
	void Update(std::string textureID, cocos2d::Point* position, int nLocalZOrder)
	{
		p_sTextureID = textureID;
		p_pPosition = position;
		p_nLocalZOrder = nLocalZOrder;
	}
	inline std::string GetTextureID() const { return p_sTextureID; }
	inline cocos2d::Point* GetPosition() const { return p_pPosition; }
	inline int GetLocalZOrder() const { return p_nLocalZOrder; }
	inline bool GetIsPhysic() const { return p_bIsPhysic; }
	inline static void Cleaner(XProperties *p) { CC_SAFE_DELETE(p); }
private:
	std::string p_sTextureID;
	cocos2d::Point* p_pPosition;
	int p_nLocalZOrder;
	bool p_bIsPhysic;
};