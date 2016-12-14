#ifndef INCLUDED_H_
#define INCLUDED_H_

#include <SFML/Graphics.hpp>

#include <gtest/gtest.h>
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <algorithm>

#include "../../src/hero.hpp"
#include "../../src/monster.hpp"
#include "../../src/HUD.hpp"





TEST(test_game, test_hero_hp) {
	Hero hero;
	hero=Hero(100,10,10,10,100);
	hero.takeDamage(50);
	int hpnow=hero.getHp();
	EXPECT_EQ (50,hpnow);
}
TEST(test_game, test_hero_weapon) {
	Hero hero;
	hero=Hero(100,10,10,10,100);
	Weapon weapon("ase",10,"src",0.5,"sharp");
	hero.addItem(weapon);
	hero.equip(0);
	EXPECT_EQ (20,hero.getStr());
}
TEST(test_game, test_hero_armor) {
	Hero hero;
	hero=Hero(100,10,10,10,100);
	Armor armor("kilpi",10,"src","cool");
	hero.addItem(armor);
	hero.equip(0);
	EXPECT_EQ (20,hero.getDef());
}
TEST(test_game, test_hero_damage) {
	Hero hero;
	hero=Hero(100,10,10,10,100);

	hero.takeDamage(50);

	EXPECT_EQ (50,hero.getHp());
}
TEST(test_game, test_hero_lvlup) {
	Hero hero;
	hero=Hero(100,10,10,10,100);
	hero.lvlUp();


	EXPECT_LT (100,hero.getHp());
	EXPECT_LT (10,hero.getStr());
	EXPECT_LT (10,hero.getDef());
	EXPECT_LT (10,hero.getAgi());
}
TEST(test_game, test_monster_creation) {
	Monster monster(100,10,10,10,1,3,sf::Vector2i(0,0),"badguy");
	
	EXPECT_EQ (100,monster.getHp());
	
}
TEST(test_game, test_monster_move) {
	Monster monster(100,10,10,10,1,3,sf::Vector2i(1,1),"badguy");
	monster.moveUp();
	EXPECT_EQ (0,monster.getPos().y);
	monster.moveDown();
	EXPECT_EQ (1,monster.getPos().y);
	monster.moveLeft();
	EXPECT_EQ (0,monster.getPos().x);
	monster.moveRight();
	EXPECT_EQ (1,monster.getPos().x);
	
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
#endif
