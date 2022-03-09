#pragma once
#include "../surface.h"
#include <vector>

class Sprites
{
private:
	Sprites() {}

	GameSpace::Sprite* player_idle = new GameSpace::Sprite{ new GameSpace::Surface("assets/Player/player_idle.png"), 24 };
	GameSpace::Sprite* player_run = new GameSpace::Sprite{ new GameSpace::Surface("assets/Player/player_run.png"), 32 };
	GameSpace::Sprite* player_dead = new GameSpace::Sprite{ new GameSpace::Surface("assets/Player/player_dead.png"), 28 };
	GameSpace::Sprite* player_run_body = new GameSpace::Sprite{ new GameSpace::Surface("assets/Player/player_run_body.png"), 32 };

	GameSpace::Sprite* arrow_down = new GameSpace::Sprite{ new GameSpace::Surface("assets/Weapons/arrow_down.png"), 1};
	GameSpace::Sprite* arrow_left = new GameSpace::Sprite{ new GameSpace::Surface("assets/Weapons/arrow_left.png"), 1 };
	GameSpace::Sprite* arrow_up = new GameSpace::Sprite{ new GameSpace::Surface("assets/Weapons/arrow_up.png"), 1 };
	GameSpace::Sprite* arrow_right = new GameSpace::Sprite{ new GameSpace::Surface("assets/Weapons/arrow_right.png"), 1 };

	GameSpace::Sprite* snowball_down = new GameSpace::Sprite{ new GameSpace::Surface("assets/Weapons/snowball_attack-blue_down.png"), 4 };
	GameSpace::Sprite* snowball_left = new GameSpace::Sprite{ new GameSpace::Surface("assets/Weapons/snowball_attack-blue_left.png"), 4 };
	GameSpace::Sprite* snowball_up = new GameSpace::Sprite{ new GameSpace::Surface("assets/Weapons/snowball_attack-blue_up.png"), 4 };
	GameSpace::Sprite* snowball_right = new GameSpace::Sprite{ new GameSpace::Surface("assets/Weapons/snowball_attack-blue_right.png"), 4 };

	GameSpace::Sprite* metalgift_idle = new GameSpace::Sprite{ new GameSpace::Surface("assets/Enemies/metalgift/metalgift_idle.png"), 1 };
	GameSpace::Sprite* metalgift_run = new GameSpace::Sprite{ new GameSpace::Surface("assets/Enemies/metalgift/metalgift_run.png"), 24 };
	GameSpace::Sprite* metalgift_explosion = new GameSpace::Sprite{ new GameSpace::Surface("assets/Enemies/metalgift/metalgift_explosion.png"), 6 };

	GameSpace::Sprite* snowman_turn = new GameSpace::Sprite{ new GameSpace::Surface("assets/Enemies/snowman/snowman_turn.png"), 8};
	GameSpace::Sprite* snowman_spawn = new GameSpace::Sprite{ new GameSpace::Surface("assets/Enemies/snowman/snowman_spawn.png"), 10 };
	GameSpace::Sprite* snowman_attack = new GameSpace::Sprite{ new GameSpace::Surface("assets/Enemies/snowman/snowman_attack.png"), 56 };
	GameSpace::Sprite* snowman_dead = new GameSpace::Sprite{ new GameSpace::Surface("assets/Enemies/snowman/snowman_death.png"), 48 };

	GameSpace::Sprite* rager_idle = new GameSpace::Sprite{ new GameSpace::Surface("assets/Enemies/rager/rager_idle.png"), 24 };
	GameSpace::Sprite* rager_move = new GameSpace::Sprite{ new GameSpace::Surface("assets/Enemies/rager/rager_move.png"), 20 };
	GameSpace::Sprite* rager_attack = new GameSpace::Sprite{ new GameSpace::Surface("assets/Enemies/rager/rager_attack.png"), 24 };
	GameSpace::Sprite* rager_dead = new GameSpace::Sprite{ new GameSpace::Surface("assets/Enemies/rager/rager_death.png"), 16 };

	GameSpace::Sprite* gifts = new GameSpace::Sprite{ new GameSpace::Surface("assets/Map/gifts.png"), 4 };
	
	GameSpace::Sprite* potion_heal = new GameSpace::Sprite{ new GameSpace::Surface("assets/Items/heal_potion.png"), 12 };
	GameSpace::Sprite* potion_speed = new GameSpace::Sprite{ new GameSpace::Surface("assets/Items/speed_potion.png"), 12 };
	GameSpace::Sprite* potion_firerate = new GameSpace::Sprite{ new GameSpace::Surface("assets/Items/firerate_potion.png"), 12 };
	GameSpace::Sprite* potion_shield = new GameSpace::Sprite{ new GameSpace::Surface("assets/Items/shield_potion.png"), 12 };
	GameSpace::Sprite* potion_damage = new GameSpace::Sprite{ new GameSpace::Surface("assets/Items/damage_potion.png"), 12 };


public:
	Sprites(const Sprites&) = delete;
	~Sprites()
	{
		delete player_idle;
		delete player_run;
		delete player_dead;
		delete player_run_body;

		delete arrow_down;
		delete arrow_left;
		delete arrow_up;
		delete arrow_right;
		
		delete snowball_down;
		delete snowball_left;
		delete snowball_up;
		delete snowball_right;

		delete metalgift_idle;
		delete metalgift_run;
		delete metalgift_explosion;

		delete snowman_turn;
		delete snowman_spawn;
		delete snowman_attack;
		delete snowman_dead;

		delete rager_idle;
		delete rager_move;
		delete rager_attack;
		delete rager_dead;

		delete gifts;
		
		delete potion_heal;
		delete potion_speed;
		delete potion_firerate;
		delete potion_shield;
		delete potion_damage;
	}
	static	Sprites& get() { static Sprites instance; return instance; }

	std::vector <GameSpace::Sprite*> player = { player_idle, player_run, player_dead, player_run_body };
	std::vector <GameSpace::Sprite*> arrow = { arrow_down, arrow_left, arrow_up, arrow_right };
	std::vector <GameSpace::Sprite*> snowball = { snowball_down, snowball_left, snowball_up, snowball_right };

	std::vector <GameSpace::Sprite*> metalgift = { metalgift_idle, metalgift_run, metalgift_explosion };
	std::vector <GameSpace::Sprite*> snowman = { snowman_turn, snowman_spawn, snowman_attack, snowman_dead };
	std::vector <GameSpace::Sprite*> rager = { rager_idle, rager_move, rager_attack, rager_dead };

	std::vector <GameSpace::Sprite*> gift = { gifts };
	std::vector <GameSpace::Sprite*> potion = { potion_heal, potion_speed, potion_firerate, potion_shield, potion_damage };

	GameSpace::Surface tilemap{ "assets/Map/all_map.png" };

};

