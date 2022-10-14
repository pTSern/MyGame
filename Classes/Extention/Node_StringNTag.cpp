#pragma once
#include "Node_StringNTag.h"

std::string Node_StringNTag::BulletChildName()
{
	return "bullet";
}
std::string Node_StringNTag::PlayerChildName()
{
	return "player";
}

int Node_StringNTag::BulletOrderNum()
{
	return 1;
}
int Node_StringNTag::BackgroundOrderNum()
{
	return -2;
}
int Node_StringNTag::PlayerOrderNum()
{
	return -1;
}
int Node_StringNTag::UIOrderNum()
{
	return 0;
}

int Node_StringNTag::PlayerContactBitmask()
{
	return 2;
}

int Node_StringNTag::BulletContactBitmask()
{
	return 1;
}