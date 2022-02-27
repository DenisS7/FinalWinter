#pragma once
#include "../surface.h"
#include <vector>

class Sprites
{
private:
	Sprites() {}

	GameSpace::Surface player_idle{ "assets/Player/player_idle.png" };
	GameSpace::Surface player_body{ "assets/Player/player_run_body.png" };
	GameSpace::Surface player_run{ "assets/Player/player_run.png" };
	GameSpace::Surface player_death{ "assets/Player/player_dead.png" };

	GameSpace::Surface crossbow_down{ "assets/Weapons/crossbow_down.png" };
	GameSpace::Surface crossbow_left{ "assets/Weapons/crossbow_left.png" };
	GameSpace::Surface crossbow_up{ "assets/Weapons/crossbow_up.png" };
	GameSpace::Surface crossbow_right{ "assets/Weapons/crossbow_right.png" };

	GameSpace::Surface metalbox_idle{ "assets/Enemies/metalgift/metalgift_idle.png" };
	GameSpace::Surface metalbox_run{ "assets/Enemies/metalgift/metalgift_idle.png " };
	GameSpace::Surface metalbox_explosion{ "assets/Enemies/metalgift/metalgift_explosion.png" };

	GameSpace::Surface snowman_turn{ "assets/Enemies/snowman/snowman_turn.png" };
	GameSpace::Surface snowman_spawn{ "assets/Enemies/snowman/snowman_spawn.png" };
	GameSpace::Surface snowman_attack{ "assets/Enemies/snowman/snowman_attack.png" };
	GameSpace::Surface snowman_death{ "assets/Enemies/snowman/snowman_attack.png" };

	GameSpace::Surface arrow_down{ "assets/Weapons/arrow_down.png" };
	GameSpace::Surface arrow_left{ "assets/Weapons/arrow_left.png" };
	GameSpace::Surface arrow_up{ "assets/Weapons/arrow_up.png" };
	GameSpace::Surface arrow_right{ "assets/Weapons/arrow_right.png" };

	GameSpace::Surface snowball_down{ "assets/Weapons/snowball_attack-blue_down.png" };
	GameSpace::Surface snowball_left{ "assets/Weapons/snowball_attack-blue_left.png" };
	GameSpace::Surface snowball_up{ "assets/Weapons/snowball_attack-blue_up.png" };
	GameSpace::Surface snowball_right{ "assets/Weapons/snowball_attack-blue_right.png" };

public:
	Sprites(const Sprites&) = delete;
	static	Sprites& get() { static Sprites instance; return instance; }

	GameSpace::Surface tilemap{ "assets/Map/all_map.png" };

	std::vector <GameSpace::Surface*> player = { &player_idle, &player_run, &player_death, &player_body };
	std::vector <GameSpace::Surface*> crossbow = { &crossbow_down, &crossbow_left, &crossbow_up, &crossbow_right };
	std::vector <GameSpace::Surface*> metalbox = { &metalbox_idle, &metalbox_run, &metalbox_explosion };
	std::vector <GameSpace::Surface*> snowman = { &snowman_turn, &snowman_spawn, &snowman_attack, &snowman_death };
	std::vector <GameSpace::Surface*> arrow = { &arrow_down, &arrow_left, &arrow_up, &arrow_right };
	std::vector <GameSpace::Surface*> snowball = { &snowball_down, &snowball_left, &snowball_up, &snowball_right };
};

