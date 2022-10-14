#include "BulletPhysic_Default.h"

static PhysicRegister<BulletPhysic_Default> s_register("DEFAULT");

BulletPhysic_Default::BulletPhysic_Default()
{

}

cocos2d::Point BulletPhysic_Default::NextXY(float fTime, float fForce, DIR eChampionDir, float fAngle, float fBulletMass)
{
	float wind_X = GameEnvironment::GetInstance()->GetWindForce() * cos(fAngle) * fTime / fBulletMass;
	if (fAngle == PI / 2) wind_X = GameEnvironment::GetInstance()->GetWindForce() * fTime;

	float nextX = m_fStartPoint_X + eChampionDir * fForce * cos(fAngle) * cos(fAngle) * fTime / fBulletMass + wind_X;
	float nextY = m_fStartPoint_Y + (((-1)*GameEnvironment::GetInstance()->GetGravityAcceleration() * sin(fAngle) * fTime + fForce * sin(fAngle) * sin(fAngle) * fTime)) / fBulletMass - 0.5* GameEnvironment::GetInstance()->GetGravityAcceleration() * (-1)*fTime*fTime;
	//cocos2d::log(("     > NEXT X Y: " + std::to_string(nextX) + " - " + std::to_string(nextY) + " WIND: " + std::to_string(GameEnvironment::GetInstance()->GetWindForce()) + " WITH FORCE: " + std::to_string(fForce) + " WITH ANGLE: " + std::to_string(fAngle*180/PI)).c_str() );
	return cocos2d::Point(nextX, nextY);
}
void BulletPhysic_Default::CalculateStartPoint(cocos2d::Sprite* pChampionSprite, cocos2d::Sprite* pBulletSprite, DIR eChampionDir, float fAngle)
{
	BulletPhysic::CalculateStartPoint(pChampionSprite, pBulletSprite, eChampionDir, fAngle);
	//cocos2d::log("%f - %f", m_fStartPoint_X, m_fStartPoint_Y);
	//cocos2d::log("%f", m_fSafeAngle);
}
void BulletPhysic_Default::CalculateStartPoint(cocos2d::Size championSize, cocos2d::Point championPos, cocos2d::Size bulletSize, DIR eChampionDir, float fAngle_R)
{
	BulletPhysic::CalculateStartPoint(championSize, championPos, bulletSize, eChampionDir, fAngle_R);
}
