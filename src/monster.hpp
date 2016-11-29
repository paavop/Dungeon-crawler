#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <vector>


class Monster {
	public:
		Monster(sf::Vector2f pos);
		Monster(int health, int strength, int agility, 
				int defense,  int lvl, int hearing_radius,
				sf::Vector2f pos, std::string name);

		std::string		getPicName();
		std::string	 	getName();
		sf::Vector2f 	getPos();
		void 			setSprite(sf::Sprite& sprite);
		void 			setPos(unsigned int x, unsigned int y);
		void			setTargetPos(sf::Vector2f pos);
		void			detectsPlr();
		void 			undetectsPlr();
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
		
		
	private:
		bool alive;
		bool detects_player;
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
		

		sf::Vector2f position;
		sf::Vector2f target_pos;	//place where the enemy tries to go
};

