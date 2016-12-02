#include "Gamemanager.hpp"


// Functions for calculating and executing combat related actions
// Attacker is the first given argument, target is the second



bool combat(Hero hero, Monster monster, HUD &hud){
  hud.sendMsg("Player is attacking");
  
  int hit_chance = std::rand() %100 + 1; // random chance to hit the target
  
  if((monster.getAgi() * 2) > hit_chance){ // if targets agility is high enough, dodge
 //   hud.sendMsg("%s dodged the attack!",monster.getName());
    return true;
  }

  int penetration = hero.getStr() - monster.getDef(); // Comparing stats
  if (penetration <= 0) {
    penetration = 1;
  }
  int damage = (penetration * hit_chance / 10); // calculating the amount damage done

  monster.takeDamage(damage);
 // hud.sendMsg("The hit dealt %i damage!",damage);
  return true;
}





bool combat(Monster monster, Hero hero, HUD &hud){
 // hud.sendMsg("%s is attacking", monster.getName());
  
  int hit_chance = std::rand() %100 + 1; // random chance to hit the target
  
  if((hero.getAgi() * 2) > hit_chance){ // if targets agility is high enough, dodge
    hud.sendMsg("Player dodged the attack!");
    return true;
  }

  int penetration = monster.getStr() - hero.getDef(); // Comparing stats
  if (penetration <= 0) {
    penetration = 1;
  }
  int damage = (penetration * hit_chance / 10); // Calculating the damage done

  hero.takeDamage(damage);
 // hud.sendMsg("The hit dealt %i damage!",damage);
  return true;
}
  
