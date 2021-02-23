#pragma once

class MyPlaneObject
{
public:
	MyPlaneObject(float posx, float posz, float R, float G, float B);
	~MyPlaneObject();

	float posx;
	float posz;
	float radius;

	bool moving;
	bool visible;

	float speedx;
	float speedz;

	float R;
	float G;
	float B;

	void foo() {}
};