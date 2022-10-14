#include "Hero_Bot.h"

static BotRegister<Hero_Bot> s_reg("HERO");
Hero_Bot::Hero_Bot() : AI()
{
	m_BulletSize = cocos2d::Size(16,16);
	m_ChampionSize = cocos2d::Size(30, 30);
}
void Hero_Bot::Move()
{

}
void Hero_Bot::Skill()
{

}
float Hero_Bot::ForceCalculate(DIR g_eDir, float g_fAngle, float g_fMass, cocos2d::Point posP, cocos2d::Point posB, float g_fMaxForce)
{
	cocos2d::log("     [====================================================]");
	cocos2d::Point truePosB = BulletPhysic::SCalculateStartPoint(m_ChampionSize, posB, m_BulletSize, g_eDir, g_fAngle);

	float a = 0.5 * GameEnvironment::GetInstance()->GetGravityAcceleration()*g_fMass*g_eDir*pow(cos(g_fAngle),2);
	float b = -(GameEnvironment::GetInstance()->GetWindForce()*cos(g_fAngle)*pow(sin(g_fAngle),2) + GameEnvironment::GetInstance()->GetGravityAcceleration()*sin(g_fAngle)*g_eDir*pow(cos(g_fAngle),2));
	float c = (posP.x - truePosB.x)*g_fMass* pow(sin(g_fAngle), 2) - (posP.y - truePosB.y) * g_fMass * g_eDir * pow(cos(g_fAngle), 2);

	cocos2d::log(("          a: " + std::to_string(a) + " - b: " + std::to_string(b) + " - c: " + std::to_string(c)).c_str());
	cocos2d::log( ("          BOT WIND: " + std::to_string(GameEnvironment::GetInstance()->GetWindForce())).c_str() );
	float delta = pow(b, 2) - 4 * a * c;
	if (delta < 0) return (int)ErorDetect::INVALID_DELTA;
	float time;
	time = (-b + sqrt(delta))/(2*a);
	if (time < 0) time = (-b - sqrt(delta))/(2*a);
	if (time < 0) return (int)ErorDetect::INVALID_TIME;

	//float force = ((posP.x - truePosB.x) - (GameEnvironment::GetInstance()->GetWindForce() * cos(g_fAngle) * time) / g_fMass) / ((int)g_eDir * cos(g_fAngle) * cos(g_fAngle) * time);
	float force = (posP.y - truePosB.y + GameEnvironment::GetInstance()->GetGravityAcceleration()*sin(g_fAngle)*time - 0.5* GameEnvironment::GetInstance()->GetGravityAcceleration()*time*time) / (pow(sin(g_fAngle),2)*time);
	if (force > g_fMaxForce) return (int)ErorDetect::OUT_OF_FORCE;

	float L = pow(force, 2) * pow(sin(g_fAngle),2) / (-2) * GameEnvironment::GetInstance()->GetGravityAcceleration();
	if ((L + truePosB.y )> (MapManager::GetInstance()->GetMapSize().height * 2.5)) return (int)ErorDetect::OUT_OF_MAP;

	cocos2d::log(("          L: " + std::to_string(L) + " TRUE POS Y: " + std::to_string(truePosB.y) + " MH: " + std::to_string(MapManager::GetInstance()->GetMapSize().height * 3) + " TIME: " + std::to_string(time)).c_str());
	cocos2d::log("     [====================================================]");
	return force;
}