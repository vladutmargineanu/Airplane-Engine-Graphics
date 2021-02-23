#include "ship.h"

MyPlaneObject::MyPlaneObject(float posx, float posy, float R, float G, float B)
{
	this->posx = posx;
	this->posz = posy;

	this->moving = false;
	this->visible = true;

	this->speedx = 0;
	this->speedz = 0;

	this->R = R;
	this->G = G;
	this->B = B;
}

MyPlaneObject::~MyPlaneObject()
{
}
