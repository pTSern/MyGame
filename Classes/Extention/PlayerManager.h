#pragma once
enum class PlayerStatus
{
	IDLE = 0,
	IS_TURN = 1,
	END_TURN = 2,
	FALLING = 3
};
struct PlayerStatics
{
public:
	float g_fForce = 0, g_fAngle = 0, g_fMoveSpeed = 0;
	DIR g_eDir;
	float g_fForceMemory = 0;
	bool g_bIsReverse = false;
};
struct PlayerAction
{
public:
	bool g_bIsUpAngle = false, g_bIsDownAngle = false, g_bIsForce = false, g_bIsTurn = false, g_bIsEndTurn = false;
	bool g_bIsShooting = false;
	bool g_bIsMoving = false;

	PlayerStatus g_eStatus = PlayerStatus::IDLE;
};
