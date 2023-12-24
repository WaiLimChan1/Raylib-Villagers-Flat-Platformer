#include "Header.h"
#include "GlobalConstVariables.cpp"
#include "MyCamera.h"
#include "Background.h"
#include "AnimationPro.h"
#include "Character.h"

// Global Variables
//---------------------------------------------------------------------------------------------------------------------------------------------------------------
Background background;
MyCamera camera;

vector<Character> villagers;
int chosenOne;
bool selectAll;
//---------------------------------------------------------------------------------------------------------------------------------------------------------------

void SetUpVillagers()
{
	Character man, woman, oldMan, oldWoman, boy, girl;
	int health = 10;

	AnimationPro attack(LoadTexture("Villagers/Man/attack.png"), 4.0, 1.0 / 13.0, 1, 4, 4);
	AnimationPro death(LoadTexture("Villagers/Man/death.png"), 4.0, 1.0 / 12.0, 1, 4, 4);
	AnimationPro hurt(LoadTexture("Villagers/Man/hurt.png"), 4.0, 1.0 / 12.0, 1, 2, 2);
	AnimationPro idle(LoadTexture("Villagers/Man/idle.png"), 4.0, 1.0 / 6.0, 1, 4, 4);
	AnimationPro walk(LoadTexture("Villagers/Man/walk.png"), 4.0, 1.0 / 8.0, 1, 6, 6);
	man = Character("Man", attack, death, hurt, idle, walk, { 0,0 }, 300, false, health);
	villagers.push_back(man);

	attack = AnimationPro(LoadTexture("Villagers/Woman/attack.png"), 4.0, 1.0 / 13.0, 1, 4, 4);
	death = AnimationPro(LoadTexture("Villagers/Woman/death.png"), 4.0, 1.0 / 12.0, 1, 4, 4);
	hurt = AnimationPro(LoadTexture("Villagers/Woman/hurt.png"), 4.0, 1.0 / 12.0, 1, 2, 2);
	idle = AnimationPro(LoadTexture("Villagers/Woman/idle.png"), 4.0, 1.0 / 6.0, 1, 4, 4);
	walk = AnimationPro(LoadTexture("Villagers/Woman/walk.png"), 4.0, 1.0 / 8.0, 1, 6, 6);
	woman = Character("Woman", attack, death, hurt, idle, walk, { 100,0 }, 300, false, health);
	villagers.push_back(woman);

	attack = AnimationPro(LoadTexture("Villagers/Old Man/attack.png"), 4.0, 1.0 / 13.0, 1, 4, 4);
	death = AnimationPro(LoadTexture("Villagers/Old Man/death.png"), 4.0, 1.0 / 12.0, 1, 4, 4);
	hurt = AnimationPro(LoadTexture("Villagers/Old Man/hurt.png"), 4.0, 1.0 / 12.0, 1, 2, 2);
	idle = AnimationPro(LoadTexture("Villagers/Old Man/idle.png"), 4.0, 1.0 / 6.0, 1, 4, 4);
	walk = AnimationPro(LoadTexture("Villagers/Old Man/walk.png"), 4.0, 1.0 / 8.0, 1, 6, 6);
	oldMan = Character("Old Man", attack, death, hurt, idle, walk, { 200,0 }, 300, false, health);
	villagers.push_back(oldMan);

	attack = AnimationPro(LoadTexture("Villagers/Old Woman/attack.png"), 4.0, 1.0 / 13.0, 1, 4, 4);
	death = AnimationPro(LoadTexture("Villagers/Old Woman/death.png"), 4.0, 1.0 / 12.0, 1, 4, 4);
	hurt = AnimationPro(LoadTexture("Villagers/Old Woman/hurt.png"), 4.0, 1.0 / 12.0, 1, 2, 2);
	idle = AnimationPro(LoadTexture("Villagers/Old Woman/idle.png"), 4.0, 1.0 / 6.0, 1, 4, 4);
	walk = AnimationPro(LoadTexture("Villagers/Old Woman/walk.png"), 4.0, 1.0 / 8.0, 1, 6, 6);
	oldWoman = Character("Old Woman", attack, death, hurt, idle, walk, { 300,0 }, 300, false, health);
	villagers.push_back(oldWoman);

	attack = AnimationPro(LoadTexture("Villagers/Boy/attack.png"), 4.0, 1.0 / 13.0, 1, 4, 4);
	death = AnimationPro(LoadTexture("Villagers/Boy/death.png"), 4.0, 1.0 / 12.0, 1, 4, 4);
	hurt = AnimationPro(LoadTexture("Villagers/Boy/hurt.png"), 4.0, 1.0 / 12.0, 1, 2, 2);
	idle = AnimationPro(LoadTexture("Villagers/Boy/idle.png"), 4.0, 1.0 / 6.0, 1, 4, 4);
	walk = AnimationPro(LoadTexture("Villagers/Boy/walk.png"), 4.0, 1.0 / 8.0, 1, 6, 6);
	boy = Character("Boy", attack, death, hurt, idle, walk, { 400,0 }, 300, false, health);
	villagers.push_back(boy);

	attack = AnimationPro(LoadTexture("Villagers/Girl/attack.png"), 4.0, 1.0 / 13.0, 1, 4, 4);
	death = AnimationPro(LoadTexture("Villagers/Girl/death.png"), 4.0, 1.0 / 12.0, 1, 4, 4);
	hurt = AnimationPro(LoadTexture("Villagers/Girl/hurt.png"), 4.0, 1.0 / 12.0, 1, 2, 2);
	idle = AnimationPro(LoadTexture("Villagers/Girl/idle.png"), 4.0, 1.0 / 6.0, 1, 4, 4);
	walk = AnimationPro(LoadTexture("Villagers/Girl/walk.png"), 4.0, 1.0 / 8.0, 1, 6, 6);
	girl = Character("Girl", attack, death, hurt, idle, walk, { 500,0 }, 300, false, health);
	villagers.push_back(girl);
}

void SetUp()
{
	background = Background(LoadTexture("Villagers/DarkForest.png"), { 0,0 }, 1.1f);
	camera = MyCamera({ 0,200 }, 600.0f, false);

	SetUpVillagers();
	chosenOne = 0;
	selectAll = false;
}

void printWorldPosition(Vector2 cameraPos, bool cameraLocked)
{
	char message[100];
	int offsetX = 10;
	int offsetY = 0;
	int fontSize = 30;
	Color color = WHITE;

	DrawText("World Positions: (x, y) ", offsetX, offsetY, fontSize, color);
	offsetY += fontSize;

	if (cameraLocked) strcpy_s(message, "(Locked) Camera Positions: (");
	else strcpy_s(message, "Camera Positions: (");
	strcat_s(message, to_string((int)cameraPos.x).c_str());
	strcat_s(message, ", ");
	strcat_s(message, to_string((int)cameraPos.y).c_str());
	strcat_s(message, ")");
	DrawText(message, offsetX, offsetY, fontSize, color);
	offsetY += fontSize;

	if (selectAll) color = RED;

	int counter = 0;
	for (auto& villager : villagers)
	{
		//Print Out World Position
		strcpy_s(message, villager.getName());
		strcat_s(message, ": (");
		strcat_s(message, to_string((int)villager.getPos().x).c_str());
		strcat_s(message, ", ");
		strcat_s(message, to_string((int)villager.getPos().y).c_str());
		strcat_s(message, ") ");
		strcat_s(message, "Health: "); // Health
		strcat_s(message, to_string((int)villager.getHealth()).c_str()); // Health Value
		strcat_s(message, " Frame: "); // Frame
		strcat_s(message, to_string((int)villager.getFrame()).c_str()); // Frame Value
		if (counter == chosenOne) DrawText(message, offsetX, offsetY, fontSize, RED);
		else DrawText(message, offsetX, offsetY, fontSize, color);
		offsetY += fontSize;
		counter++;
	}
}

void Draw()
{
	BeginDrawing();
	ClearBackground(BLACK);

	background.draw(camera.getPos());

	for (auto &villager : villagers)
	{
		villager.draw(camera.getPos());

		//Hitboxes
		/*
		villager.drawHitbox(camera.getPos());
		if (villager.getStatus() == ATTACK)
		villager.drawAttackBox(camera.getPos());
		*/
	}

	printWorldPosition(camera.getPos(), camera.getLocked());
	EndDrawing();
}

void Input()
{
	//Selecting Individual Villager Or Selecting All Villagers
	if (IsMouseButtonPressed(1))
	{
		chosenOne++;
		selectAll = false;
	}
	if (chosenOne > villagers.size() - 1) chosenOne = 0;
	if (IsKeyPressed(KEY_F)) selectAll = !selectAll;

	//Allow Selected Villager/Villagers Receive User Input And Let The Unselected Villagers End Animation(ATTACK, HURT, DEATH) Once Animation Is Done
	if (selectAll) for (auto &villager : villagers) villager.takeInput();
	else
	{
		for (int i = 0; i < villagers.size(); i++)
		{
			if (i == chosenOne) villagers.at(chosenOne).takeInput();
			else villagers.at(i).endMovement();
		}
	}

	//Move Camera 
	camera.takeInput();
}

void Logic()
{
	//Attacking And Receiving Damage (Determine If Character Is Dead)
	for (int attackerIndex = 0; attackerIndex < villagers.size(); attackerIndex++)
	{
		for (int defenderIndex = 0; defenderIndex < villagers.size(); defenderIndex++)
		{
			if (attackerIndex != defenderIndex)
			{
				Character& attacker = villagers.at(attackerIndex);
				Character& defender = villagers.at(defenderIndex);
				if (attacker.getStatus() == ATTACK)
				{
					defender.isHitByRec(attacker.getAttackBox(camera.getPos()), camera.getPos(), attacker.atMidFrame());
					defender.checkDeath();
				}
			}
		}
	}

	//Determine Villagers' Animation And Move Villagers
	for (auto& villager : villagers)
	{
		villager.changeAnimation();
		villager.updatePosition();
	}

	if (camera.getLocked()) camera.setPos(villagers.at(chosenOne).getSyncCameraPos()); //Sync Camera With Selected Villager
	camera.checkTopDownBound(background.getScaledSize()); // Last Camera Position Adjustment To Make Sure Camera Is Not Out Of Bound
}


int main()
{
	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Villagers Flat-Platformer");
	SetWindowState(FLAG_VSYNC_HINT);
	srand(time(0));

	SetUp();
	while (!WindowShouldClose())
	{
		Draw();
		Input();
		Logic();
	}

	//Unload All Textures
	background.unloadTexture();
	for (auto villager : villagers) villager.unloadTexture();

	CloseWindow();

	return 0;
}