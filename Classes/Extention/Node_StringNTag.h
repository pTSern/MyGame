#pragma once
#include <iostream>
enum class ChildName
{
	BULLET = 0,
	PLAYER = 1
};
class Node_StringNTag
{
public:
	static std::string BulletChildName();
	static std::string PlayerChildName();

	static int BulletOrderNum();
	static int BackgroundOrderNum();
	static int PlayerOrderNum();
	static int UIOrderNum();

	static int PlayerContactBitmask();
	static int BulletContactBitmask();
};