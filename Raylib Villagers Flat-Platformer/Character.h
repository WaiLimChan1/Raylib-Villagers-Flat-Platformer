#pragma once
#include "Header.h"
#include "GlobalConstVariables.cpp"
#include "AnimationPro.h"

class Character
{
private:
	const char* name;

	AnimationPro current;

	AnimationPro attack;
	AnimationPro death;
	AnimationPro hurt;
	AnimationPro idle;
	AnimationPro walk;

	Status lastStatus;
	Status status;

	Vector2 pos;

	float speed;
	bool facingLeft;

	int health;
	bool dead;

public:
	Character();
	Character(const char* name, AnimationPro attack, AnimationPro death, AnimationPro hurt, AnimationPro idle, AnimationPro walk, Vector2 pos, float speed, bool facingLeft, int health);

	const char* getName();
	int getFrame();
	Status getStatus();
	Vector2 getPos();
	int getHealth();

	Vector2 getSyncCameraPos();

	Rectangle getHitbox(Vector2 cameraPos);
	void drawHitbox(Vector2 cameraPos);

	Rectangle getAttackBox(Vector2 cameraPos);
	void drawAttackBox(Vector2 cameraPos);

	void draw(Vector2 cameraPos);
	void endMovement();
	void takeInput();

	bool atMidFrame();
	bool isHitByRec(Rectangle attackBox, Vector2 cameraPos, bool atMidFrame);
	bool checkDeath();

	void changeAnimation();
	void updatePosition();

	void unloadTexture();
};

