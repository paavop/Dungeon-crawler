#ifndef MONSTER_H
#define MONSTER_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

#include <cstdlib>
#include <iostream>


class Monster {
	public:
		Monster(sf::Vector2i pos);
		Monster(int health, int strength, int agility, 
				int defense,  int lvl, int hearing_radius,
				sf::Vector2i pos, std::string name,std::string image);

		std::string		getPicName();
		std::string	 	getName();
		sf::Vector2i 	getPos();
		void 			setSprite(sf::Sprite& sprite);
		void 			setPos(unsigned int x, unsigned int y);
		void			setTargetPos(sf::Vector2i pos);
		bool 			isFreshTarget();
		void			detectPlr(sf::Vector2i pos);
		void 			undetectPlr();
		bool 			takeDamage(int dmg);
		bool 			isAlive();
		void 			heal(int h);
		void			die();
		int 			getHp();
		int	 			getStr();
		int				getLvl();
		int 			getAgi();
		int 			getDef();
		int				getHearingRadius();
		int 			getMaxHp();
		
		bool			movesUp();
		bool			movesDown();
		bool			movesLeft();
		bool			movesRight();
		void			stopMove();
		void			moveUp();
		void			moveDown();
		void			moveLeft();
		void			moveRight();


		bool 			canMove(std::vector<std::vector<int>>& map);
		void 			moveTowardsTarget(std::vector<std::vector<int>>& map);
		int 			faceWhere();
		void			faceThere(int dir);
		void 			lvlUp(int lvl);

		
	private:

		enum Direction {Up, Right, Down, Left, Stop};
		Direction moving_dir = Stop;
		Direction facing_dir = Up;

		bool alive;
		bool detects_player;
		unsigned int target_freshness =0;
		std::string pic_name;
		std::string name;	//Monster's name (daa-a)
		//sf::Texture &texture;
		//sf::Sprite	&sprite;
		int maxhp;			//Monster's max health points	
		int hp;				//Monster's current health points
		int lvl;			//Level of the Monster
		int strength;		//Monster's strength stat
		int agility;		//Monster's agility stat
		int defense;		//Monster's defense stat
		int hearing;		//hearing radius
		
		bool movingUp,movingDown,movingLeft,movingRight;
		bool faceUp, faceDown,faceLeft,faceRight;

		sf::Vector2i position;
		sf::Vector2i target_pos;	//place where the enemy tries to go
};


/*

class MonsterCatalog {
public:
	explicit MonsterCatalog();
	~MonsterCatalog();

	std::vector<Monster*> const& 	getMonsters() const			{return monster_catalog_;}
	void 							setMonster(Monster* monster){monster_catalog_.push_back(monster);}	


private:
	std::vector<Monster*> monster_catalog_;
}
*/
#endif
