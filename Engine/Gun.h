#pragma once

#include "Graphics.h"
#include "Keyboard.h"

class Gun 
{
public:
	void drawHandGun();
	void drawShotGun();
	void drawRifle();
private:
	int handGunAmmo = 5;
	int shotGunAmmo = 5;
	int rifleAmmo = 5;
};