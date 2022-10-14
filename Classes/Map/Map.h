#pragma once
#include "cocos2d.h"
class MapManager
{
public:
	inline static MapManager* GetInstance()
	{
		return p_pInstance = (p_pInstance != nullptr) ? p_pInstance : new MapManager();
	}
	cocos2d::TMXTiledMap* GetTileMap();
	cocos2d::TMXLayer* GetLayer();
	void LoadTileMap(std::string sMapName);
	void Cleaner();

	/**
	* Check if input position is contact to a collision object
	* 
	* @Input: position need to be checked 
	* @Return: TRUE -> Contaced to a collision object
	* @Return: FALSE -> NO Contact happen
	*/
	bool CheckMapCollision(cocos2d::Point pos);
	bool CheckMapCollision(cocos2d::Point pos, cocos2d::Size size);
	cocos2d::Size GetMapSize();
	cocos2d::Sprite* GetSprite() { return this->p_pSprite; }

	cocos2d::Point GetTileCoordForPosition(cocos2d::Point pos);
	bool IsReachTheVoid(cocos2d::Point pos, cocos2d::Size size);
	bool IsOutOfMap(cocos2d::Point pos, cocos2d::Size size);
	bool IsReachSideMap(cocos2d::Point pos, cocos2d::Size size);
private:
	MapManager(){}
	static MapManager* p_pInstance;
	cocos2d::TMXTiledMap* p_pTileMap;
	cocos2d::TMXLayer* p_pLayer;
	cocos2d::PhysicsBody* p_pPhysicBody;
	cocos2d::Sprite* p_pSprite;
	cocos2d::TMXObjectGroup* p_pObjectGroup;
};