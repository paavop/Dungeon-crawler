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
	Weapon weapon("ase",10,"src",0.5);
	hero.addItem(weapon);
	hero.equip(0);
	EXPECT_EQ (20,hero.getStr());
}
TEST(test_game, test_hero_armor) {
	Hero hero;
	hero=Hero(100,10,10,10,100);
	Armor armor("kilpi",10,"src");
	hero.addItem(armor);
	hero.equip(0);
	EXPECT_EQ (20,hero.getDef());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
#endif
