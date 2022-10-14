#include "Map.h"
MapManager* MapManager::p_pInstance = nullptr;
//cocos2d::TMXTiledMap* MapManager::p_pTileMap = nullptr;

cocos2d::TMXTiledMap* MapManager::GetTileMap()
{
	return p_pTileMap;
}
cocos2d::TMXLayer* MapManager::GetLayer()
{
	return p_pLayer;
}
void MapManager::LoadTileMap(std::string sMapName)
{
	this->p_pTileMap = cocos2d::TMXTiledMap::create(sMapName.c_str());

	this->p_pLayer = this->p_pTileMap->getLayer("collision");
	this->p_pLayer->setVisible(false);

	//p_pPhysicBody = cocos2d::PhysicsBody::createEdgeBox(p_pLayer->getContentSize());
	//p_pPhysicBody->setContactTestBitmask(5);
	//p_pPhysicBody->setDynamic(false);

	//auto edgeBody = cocos2d::PhysicsBody::createEdgeBox(this->p_pTileMap->getMapSize(), cocos2d::PHYSICSBODY_MATERIAL_DEFAULT, 1);
	//m_pNode->setPhysicsBody(edgeBody);
	//m_pNode->setPosition(this->p_pTileMap->getMapSize() / 2);

	//m_pSprite = p_pLayer->getTileAt(cocos2d::Point(39,26));
	//m_pSprite->setPhysicsBody(m_pPhysicBody);
	//this->p_pLayer->setPhysicsBody(p_pPhysicBody);
	//this->p_pObjectGroup = this->p_pTileMap->getObjectGroup("collision_1");
}
void MapManager::Cleaner()
{
	this->p_pTileMap->release();
	this->p_pLayer->release();
	this->p_pObjectGroup->release();
}
cocos2d::Size MapManager::GetMapSize()
{
	return cocos2d::Size(this->p_pTileMap->getMapSize().width * this->p_pTileMap->getTileSize().width, this->p_pTileMap->getMapSize().height * this->p_pTileMap->getTileSize().height);
}
cocos2d::Point MapManager::GetTileCoordForPosition(cocos2d::Point pos)
{
	int x = pos.x / this->p_pTileMap->getTileSize().width;
	int y = ((this->p_pTileMap->getMapSize().height * this->p_pTileMap->getTileSize().height) - pos.y) / this->p_pTileMap->getTileSize().height;
	//cocos2d::log((std::to_string(x) + " - " + std::to_string(y)).c_str());
	return cocos2d::Point(x, y);
}

bool MapManager::CheckMapCollision(cocos2d::Point pos)
{
	cocos2d::Point tileCoord = MapManager::GetInstance()->GetTileCoordForPosition(pos);
	int tileGID = MapManager::GetInstance()->GetLayer()->getTileGIDAt(tileCoord);
	if (tileGID)
	{
		auto x = MapManager::GetInstance()->GetTileMap()->getPropertiesForGID(tileGID).asValueMap();
		if (x.at("collision").asString() == "true")
		{
			return true;
		}
	}
	return false;
	
}
bool MapManager::CheckMapCollision(cocos2d::Point pos, cocos2d::Size size)
{
	if (IsOutOfMap(pos, size))
	{
		return false;
	}
	return this->CheckMapCollision(pos);
}
bool MapManager::IsReachTheVoid(cocos2d::Point pos, cocos2d::Size size)
{
	if (pos.y - size.height / 2 <= 0)
	{
		cocos2d::log("REACH THE VOID");
		return true;
	}
		
	return false;
}
bool MapManager::IsReachSideMap(cocos2d::Point pos, cocos2d::Size size)
{
	if (pos.x - size.width / 2 <= 0 || pos.x + size.width / 2 >= GetMapSize().width)
	{
		return true;
	}
	return false;
}
bool MapManager::IsOutOfMap(cocos2d::Point pos, cocos2d::Size size)
{
	if (pos.y - size.height / 2 <= 0 || pos.y - size.height / 2 >= GetMapSize().height)
	{
		cocos2d::log("OUT OF MAP");
		return true;
	}
	return false;
}