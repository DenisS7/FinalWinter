#pragma once
#include "../surface.h"
#include <vector>

class Sprites
{
private:
    Sprites()
    {
    }

    GameSpace::Surface* s_player_idle = new GameSpace::Surface("assets/Player/player_idle.png");
    GameSpace::Surface* s_player_run = new GameSpace::Surface("assets/Player/player_run.png");
    GameSpace::Surface* s_player_dead = new GameSpace::Surface("assets/Player/player_dead.png");
    GameSpace::Surface* s_player_run_body = new GameSpace::Surface("assets/Player/player_run_body.png");

    GameSpace::Surface* s_arrow_down = new GameSpace::Surface("assets/Weapons/arrow_down.png");
    GameSpace::Surface* s_arrow_left = new GameSpace::Surface("assets/Weapons/arrow_left.png");
    GameSpace::Surface* s_arrow_up = new GameSpace::Surface("assets/Weapons/arrow_up.png");
    GameSpace::Surface* s_arrow_right = new GameSpace::Surface("assets/Weapons/arrow_right.png");

    GameSpace::Surface* s_ice_explosion = new GameSpace::Surface("assets/Weapons/ice_explosion.png");

    GameSpace::Surface* s_snowball_down = new GameSpace::Surface("assets/Weapons/snowball_attack-blue_down.png");
    GameSpace::Surface* s_snowball_left = new GameSpace::Surface("assets/Weapons/snowball_attack-blue_left.png");
    GameSpace::Surface* s_snowball_up = new GameSpace::Surface("assets/Weapons/snowball_attack-blue_up.png");
    GameSpace::Surface* s_snowball_right = new GameSpace::Surface("assets/Weapons/snowball_attack-blue_right.png");

    GameSpace::Surface* s_metalgift_idle = new GameSpace::Surface("assets/Enemies/metalgift/metalgift_idle.png");
    GameSpace::Surface* s_metalgift_run = new GameSpace::Surface("assets/Enemies/metalgift/metalgift_run.png");
    GameSpace::Surface* s_metalgift_explosion = new GameSpace::Surface(
        "assets/Enemies/metalgift/metalgift_explosion.png");

    GameSpace::Surface* s_snowman_turn = new GameSpace::Surface("assets/Enemies/snowman/snowman_turn.png");
    GameSpace::Surface* s_snowman_spawn = new GameSpace::Surface("assets/Enemies/snowman/snowman_spawn.png");
    GameSpace::Surface* s_snowman_attack = new GameSpace::Surface("assets/Enemies/snowman/snowman_attack.png");
    GameSpace::Surface* s_snowman_dead = new GameSpace::Surface("assets/Enemies/snowman/snowman_death.png");

    GameSpace::Surface* s_rager_idle = new GameSpace::Surface("assets/Enemies/rager/rager_idle.png");
    GameSpace::Surface* s_rager_move = new GameSpace::Surface("assets/Enemies/rager/rager_move.png");
    GameSpace::Surface* s_rager_attack = new GameSpace::Surface("assets/Enemies/rager/rager_attack.png");
    GameSpace::Surface* s_rager_dead = new GameSpace::Surface("assets/Enemies/rager/rager_death.png");

    GameSpace::Surface* s_gifts = new GameSpace::Surface("assets/Map/gifts.png");

    GameSpace::Surface* s_potion_heal = new GameSpace::Surface("assets/Items/heal_potion.png");
    GameSpace::Surface* s_potion_speed = new GameSpace::Surface("assets/Items/speed_potion.png");
    GameSpace::Surface* s_potion_firerate = new GameSpace::Surface("assets/Items/firerate_potion.png");
    GameSpace::Surface* s_potion_shield = new GameSpace::Surface("assets/Items/shield_potion.png");
    GameSpace::Surface* s_potion_damage = new GameSpace::Surface("assets/Items/damage_potion.png");

    GameSpace::Surface* s_campfire_extinct = new GameSpace::Surface("assets/Map/campfire_extinct.png");
    GameSpace::Surface* s_campfire_on = new GameSpace::Surface("assets/Map/campfire.png");

    GameSpace::Surface* s_play_button = new GameSpace::Surface("assets/UI/play_full.png");
    GameSpace::Surface* s_quit_button = new GameSpace::Surface("assets/UI/exit_full.png");
    GameSpace::Surface* s_replay_button = new GameSpace::Surface("assets/UI/replay_full.png");
    GameSpace::Surface* s_scores_button = new GameSpace::Surface("assets/UI/scores_full.png");
    GameSpace::Surface* s_path_button = new GameSpace::Surface("assets/UI/path_full.png");
    GameSpace::Surface* s_back_button = new GameSpace::Surface("assets/UI/back_full.png");

    GameSpace::Surface* s_number1 = new GameSpace::Surface("assets/Font/font_1.png");
    GameSpace::Surface* s_numbers = new GameSpace::Surface("assets/Font/font_numbers.png");
    GameSpace::Surface* s_dot = new GameSpace::Surface("assets/Font/dot.png");


    GameSpace::Sprite* player_idle = new GameSpace::Sprite{s_player_idle, 24};
    GameSpace::Sprite* player_run = new GameSpace::Sprite{s_player_run, 32};
    GameSpace::Sprite* player_dead = new GameSpace::Sprite{s_player_dead, 28};
    GameSpace::Sprite* player_run_body = new GameSpace::Sprite{s_player_run_body, 32};

    GameSpace::Sprite* arrow_down = new GameSpace::Sprite{s_arrow_down, 1};
    GameSpace::Sprite* arrow_left = new GameSpace::Sprite{s_arrow_left, 1};
    GameSpace::Sprite* arrow_up = new GameSpace::Sprite{s_arrow_up, 1};
    GameSpace::Sprite* arrow_right = new GameSpace::Sprite{s_arrow_right, 1};

    GameSpace::Sprite* ice_explosion = new GameSpace::Sprite{s_ice_explosion, 12};

    GameSpace::Sprite* snowball_down = new GameSpace::Sprite{s_snowball_down, 4};
    GameSpace::Sprite* snowball_left = new GameSpace::Sprite{s_snowball_left, 4};
    GameSpace::Sprite* snowball_up = new GameSpace::Sprite{s_snowball_up, 4};
    GameSpace::Sprite* snowball_right = new GameSpace::Sprite{s_snowball_right, 4};

    GameSpace::Sprite* metalgift_idle = new GameSpace::Sprite{s_metalgift_idle, 1};
    GameSpace::Sprite* metalgift_run = new GameSpace::Sprite{s_metalgift_run, 24};
    GameSpace::Sprite* metalgift_explosion = new GameSpace::Sprite{s_metalgift_explosion, 13};

    GameSpace::Sprite* snowman_turn = new GameSpace::Sprite{s_snowman_turn, 8};
    GameSpace::Sprite* snowman_spawn = new GameSpace::Sprite{s_snowman_spawn, 10};
    GameSpace::Sprite* snowman_attack = new GameSpace::Sprite{s_snowman_attack, 56};
    GameSpace::Sprite* snowman_dead = new GameSpace::Sprite{s_snowman_dead, 48};

    GameSpace::Sprite* rager_idle = new GameSpace::Sprite{s_rager_idle, 24};
    GameSpace::Sprite* rager_move = new GameSpace::Sprite{s_rager_move, 20};
    GameSpace::Sprite* rager_attack = new GameSpace::Sprite{s_rager_attack, 24};
    GameSpace::Sprite* rager_dead = new GameSpace::Sprite{s_rager_dead, 16};

    GameSpace::Sprite* gifts = new GameSpace::Sprite{s_gifts, 4};

    GameSpace::Sprite* potion_heal = new GameSpace::Sprite{s_potion_heal, 12};
    GameSpace::Sprite* potion_speed = new GameSpace::Sprite{s_potion_speed, 12};
    GameSpace::Sprite* potion_firerate = new GameSpace::Sprite{s_potion_firerate, 12};
    GameSpace::Sprite* potion_shield = new GameSpace::Sprite{s_potion_shield, 12};
    GameSpace::Sprite* potion_damage = new GameSpace::Sprite{s_potion_damage, 12};

    GameSpace::Sprite* campfire_extinct = new GameSpace::Sprite{s_campfire_extinct, 1};
    GameSpace::Sprite* campfire_on = new GameSpace::Sprite{s_campfire_on, 10};

    GameSpace::Sprite* play_button = new GameSpace::Sprite{s_play_button, 2};
    GameSpace::Sprite* quit_button = new GameSpace::Sprite{s_quit_button, 2};
    GameSpace::Sprite* replay_button = new GameSpace::Sprite{s_replay_button, 2};
    GameSpace::Sprite* scores_button = new GameSpace::Sprite{s_scores_button, 2};
    GameSpace::Sprite* path_button = new GameSpace::Sprite{s_path_button, 2};
    GameSpace::Sprite* back_button = new GameSpace::Sprite{s_back_button, 2};

    GameSpace::Sprite* number1 = new GameSpace::Sprite{s_number1, 1};
    GameSpace::Sprite* numbers = new GameSpace::Sprite{s_numbers, 9};
    GameSpace::Sprite* dot = new GameSpace::Sprite{s_dot, 1};

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

        delete campfire_on;
        delete campfire_extinct;

        delete play_button;
        delete quit_button;
        delete replay_button;
        delete scores_button;
        delete path_button;
        delete back_button;

        delete number1;
        delete numbers;
        delete dot;
    }

    static Sprites& get()
    {
        static Sprites instance;
        return instance;
    }

    std::vector<GameSpace::Sprite*> player = {player_idle, player_run, player_dead, player_run_body};
    std::vector<GameSpace::Sprite*> arrow = {arrow_down, arrow_left, arrow_up, arrow_right};
    std::vector<GameSpace::Sprite*> attack = {ice_explosion};

    std::vector<GameSpace::Sprite*> snowball = {snowball_down, snowball_left, snowball_up, snowball_right};

    std::vector<GameSpace::Sprite*> metalgift = {metalgift_idle, metalgift_run, metalgift_explosion};
    std::vector<GameSpace::Sprite*> snowman = {snowman_turn, snowman_spawn, snowman_attack, snowman_dead};
    std::vector<GameSpace::Sprite*> rager = {rager_idle, rager_move, rager_attack, rager_dead};

    std::vector<GameSpace::Sprite*> gift = {gifts};
    std::vector<GameSpace::Sprite*> potion = {potion_heal, potion_speed, potion_firerate, potion_shield, potion_damage};
    std::vector<GameSpace::Sprite*> campfire = {campfire_extinct, campfire_on};

    std::vector<GameSpace::Sprite*> button = {
        play_button, quit_button, replay_button, scores_button, path_button, back_button
    };

    std::vector<GameSpace::Sprite*> number = {number1, numbers, dot};

    GameSpace::Surface tilemap{"assets/Map/all_map.png"};
};
