#include "Character.h"
Character::Character() {}
Character::Character(const char* name, AnimationPro attack, AnimationPro death, AnimationPro hurt, AnimationPro idle, AnimationPro walk, Vector2 pos, float speed, bool facingLeft, int health)
	: name(name), current(idle), attack(attack), death(death), hurt(hurt), idle(idle), walk(walk), pos(pos), speed(speed), facingLeft(facingLeft), health(health)
{
	this->pos.x = SCREEN_WIDTH / 2 - current.getWidth() / 2;
	this->pos.y = SCREEN_HEIGHT - current.getHeight();

	lastStatus = IDLE;
	status = IDLE;
	dead = false;
}

const char* Character::getName() { return name; }
int Character::getFrame() { return current.getFrame(); }
Status Character::getStatus() { return status; }
Vector2 Character::getPos() { return pos; }
int Character::getHealth() { return health; }

Vector2 Character::getSyncCameraPos() { return { pos.x - (SCREEN_WIDTH - current.getWidth()) / 2, pos.y - (SCREEN_HEIGHT - current.getHeight()) + current.getHeight() / 3}; } //pos.x - 404, pos.y - 608

Rectangle Character::getHitbox(Vector2 cameraPos)
{
	float hitboxWidth = current.getWidth() / 3;
	float hitboxHeight = current.getHeight() / 2;
	return Rectangle{ pos.x - cameraPos.x + hitboxWidth, pos.y - cameraPos.y + 2 * hitboxHeight / 3, hitboxWidth, hitboxHeight};
}
void Character::drawHitbox(Vector2 cameraPos) { DrawRectangleRec(getHitbox(cameraPos), RED); }

Rectangle Character::getAttackBox(Vector2 cameraPos)
{
	float attackBoxWidth = current.getWidth() / 3;
	float attackBoxHeight = current.getHeight() / 2;
	float attackBoxX = pos.x - cameraPos.x + attackBoxWidth;
	float attackBoxY = pos.y - cameraPos.y + 2 * attackBoxHeight / 3;
	
	if (facingLeft) attackBoxX -= attackBoxWidth;
	else attackBoxX += attackBoxWidth;
	return Rectangle{ attackBoxX, attackBoxY, attackBoxWidth, attackBoxHeight };
}
void Character::drawAttackBox(Vector2 cameraPos) { DrawRectangleRec(getAttackBox(cameraPos), ORANGE); }

void Character::draw(Vector2 cameraPos)
{
	current.draw({ pos.x - cameraPos.x, pos.y - cameraPos.y }, facingLeft);

	if (!(dead && current.atLastFrame())) //Stop updating frame once death animation is over
		current.updateFrame();
}

void Character::endMovement() //End character movement when unselected
{
	if (!dead) 
		if ((status != ATTACK && status != HURT && status != DEATH) || current.atLastFrame()) 
			status = IDLE;
}

void Character::takeInput()
{
	if (!dead)
	{
		if ((status != ATTACK && status != HURT && status != DEATH) || current.atLastFrame())
		{
			if (!IsKeyDown(KEY_A) && !IsKeyDown(KEY_D))
				status = IDLE;
			else
			{
				if (IsKeyDown(KEY_A)) facingLeft = true;
				if (IsKeyDown(KEY_D)) facingLeft = false;
				status = WALK;
			}
		}

		if (IsMouseButtonPressed(0)) status = ATTACK;
		if (IsKeyDown(KEY_SPACE)) status = IDLE;
	}
	else if (IsKeyDown(KEY_R)) //Revive
	{
		current = idle;

		lastStatus = IDLE;
		status = IDLE;

		health = 10;
		dead = false;
	}
}

bool Character::atMidFrame() { return current.atMidFrame(); }
bool Character::isHitByRec(Rectangle attackBox, Vector2 cameraPos, bool atMidFrame)
{
	if (CheckCollisionRecs(getHitbox(cameraPos), attackBox) && atMidFrame) // atMidFrame So it doesn't attack multiple times in one trigger
	{
		status = HURT;
		return true;
	}
	return false;
}
bool Character::checkDeath() //Necessary because you can still be hit after death, this function will change status back to DEATH
{ 
	if (health <= 0)
	{
		status = DEATH;
		return true;
	}
	return false;
}

void Character::changeAnimation()
{
	if (lastStatus != status && lastStatus != DEATH) //Animation changes only when a new status is met. If player is dead there shouldn't be a new status
	{
		if (status == ATTACK) current = attack;
		if (status == HURT)
		{
			health--;
			if (health <= 0) dead = true;
			else current = hurt;
		}
		if (status == DEATH || dead) current = death;
		if (status == IDLE) current = idle;
		if (status == WALK) current = walk;
	}
	lastStatus = status;
}

void Character::updatePosition()
{
	if (status == WALK)
	{
		float dt = GetFrameTime();
		if (facingLeft) pos.x -= speed * dt;
		else pos.x += speed * dt;
	}
}

void Character::unloadTexture()
{
	attack.unloadTexture();
	death.unloadTexture();
	hurt.unloadTexture();
	idle.unloadTexture();
	walk.unloadTexture();
}

