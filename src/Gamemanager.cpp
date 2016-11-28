#include "Gamemanager.hpp"

GameManager::GameManager(){
	
	Hero hero(100,10,10,10,100);
	HUD hud(hero);
	mapsize=60;
	map=makeMap(mapsize);
	findStart(map);
	
	animationTime=0.15;
	
	fpsTime=0;
	//Loading textures to sprites

	if (!wall_t.loadFromFile("resources/wall50.png"))
	{
	    perror("Couldn't load wall texture");
	}
	wall.setTexture(wall_t);


	if (!ground_t.loadFromFile("resources/ground50.png"))
	{
	    perror("Couldn't load ground texture");
	}
	ground.setTexture(ground_t);


	if (!MC_t.loadFromFile("resources/knight_animation.png"))
	{
	    perror("Couldn't load character texture");
	}
	SourceSprite=sf::IntRect(0,0,50,50);
	MC.setTexture(MC_t);
	MC.setTextureRect(SourceSprite);
	MC.setPosition(350,200);

	if (!stairs_t.loadFromFile("resources/stairs.png"))
	{
	    perror("Couldn't load stairs texture");
	}
	stairs.setTexture(stairs_t);
	
	
	loadEnemyTexture('resources/enemy_risumies.png');
}

void GameManager::loadEnemyTexture(Monster& enemy){
	sf::Texture new_texture;
	if (!new_texture.loadFromFile(enemy.getPicName())){
		perror("Couldn't load enemy texture: "+texture_name);
	}
	sf::Sprite new_sprite;
	//SourceSprite=sf::IntRect(0,0,50,50);
	new_sprite.setTexture(new_texture);
	enemy_sprites.push_back(new_sprite);
	enemy.setSprite(enemy_sprites.back());
}

void GameManager::updateAll(){
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
		movePlayer(1);
	}else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
		movePlayer(2);
	}else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
		movePlayer(3);
	}else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		movePlayer(4);
	}
	hud.updateStats(hero);
	
}

void GameManager::drawAll(sf::RenderWindow & window){
	updatePercentages();
	if (movePercentage>0 && movePercentage<0.5){
		SourceSprite.left=50;
	}else if (movePercentage>0.5 && movePercentage<1){
		SourceSprite.left=100;
	}else{
		SourceSprite.left=0;
	}
	MC.setTextureRect(SourceSprite);
	drawMap(window);
	//drawFps(window);
	window.draw(MC);
	hud.drawHUD(window);

}

void GameManager::drawFps(sf::RenderWindow& window){
	fpsTime=fpsClock.restart().asSeconds();
	int fps=(int) 1.f/(fpsTime);
	//Actually drawing to game screen not yet implemented
	std::cout<<"FPS: "<<fps<<std::endl;
}

void GameManager::drawMap(sf::RenderWindow& window){
	for(n=-1;n<16;n++){
		for(m=-1;m<10;m++){
			wall.setPosition(offsetx+xPercentage*50+50*(n),offsety+yPercentage*50+50*(m));
			window.draw(wall);
		}
	}
	for(n=(int) MCspot.x -8;n<(int) MCspot.x +9;n++){
		for(m=(int) MCspot.y -6;m<(int) MCspot.y +6;m++){
			if(n>-1 && m>-1 && n<mapsize && m<mapsize){
				if(map[n][m]==1){

					wall.setPosition(offsetx+xPercentage*50+50*(-MCspot.x+n+7),offsety+yPercentage*50+50*(-MCspot.y+m+4));
					window.draw(wall);
				}else if(map[n][m]==0){
			
					ground.setPosition(offsetx+xPercentage*50+50*(-MCspot.x+n+7),offsety+yPercentage*50+50*(-MCspot.y+m+4));
					window.draw(ground);


				}else if(map[n][m]==2){
					stairs.setPosition(offsetx+xPercentage*50+50*(-MCspot.x+n+7),offsety+yPercentage*50+50*(-MCspot.y+m+4));
					window.draw(stairs);					
				}
			}

		}
	}
}

void Gamemanager::drawEnemies(sf::RenderWindow& window){
	*/PAAVOO!!!*/
		// How I'm supposed to draw something?
}	

void GameManager::updatePercentages(){
	if(movingUp || movingDown || movingLeft || movingRight){
		if(movingUp || movingDown){
			yPercentage=(clock.getElapsedTime().asSeconds()-cmdTime)/animationTime;

			if(yPercentage>1){
				yPercentage=1;
			}
			if(movingUp){
				offsety=-50;
			}else if(movingDown){
				offsety=50;
				yPercentage=-yPercentage;
			}
		}
		if(movingLeft || movingRight){
			xPercentage=(clock.getElapsedTime().asSeconds()-cmdTime)/animationTime;
			if(xPercentage>1){
				xPercentage=1;
			}
			if(movingLeft){
				offsetx=-50;
			}else if(movingRight){
				offsetx=50;
				xPercentage=-xPercentage;
			}
		}
		if(fabs(yPercentage)>fabs(xPercentage)){
			movePercentage=fabs(yPercentage);
		}else if (fabs(xPercentage)>fabs(yPercentage)){
			movePercentage=fabs(xPercentage);
		}

		if(movePercentage>=1){

			movingLeft=false;
			movingUp=false;
			movingDown=false;
			movingRight=false;
			offsetx=0;
			offsety=0;
			xPercentage=0;
			yPercentage=0;
			movePercentage=0;
		}
	}
}
	

std::vector<std::vector<int>> GameManager::makeMap(int size){
	int mapsize=size;

	std::vector<std::vector<int>> array;
	int n,m;
	array.resize(mapsize);
	for(int i=0;i<mapsize;i++){
		array[i].resize(mapsize);
	}
	

	//Fill the map with walls
	for(n=0;n<mapsize;n++){
		for(m=0;m<mapsize;m++){
			array[n][m]=1;

		}
	}
	srand (time(NULL));
	
	//How many rooms are made
	int rooms=rand() %5 +10;

	//std::cout<<"Rooms: "<<rooms<<std::endl;
	int i;
	
	//lastx and lasty are used to build tunnels from one room to another
	int lastx=rand() %(mapsize-2)+1;
	int lasty=rand() %(mapsize-2)+1;
	int sizex,sizey,startx,starty;
	
	 
	for(i=0;i<rooms;i++){
		//A different size and location is randomized for every room
		sizex=rand() %6 +4;
		sizey=rand() %6 +4;
		startx=rand() %(mapsize-sizex-1) +1;
		starty=rand() %(mapsize-sizey-1) +1;
		
		//std::cout<<"sizex: "<<sizex<<" sizey: "<<sizey<<" startx: "<<startx<<" starty: "<<starty<<std::endl;
		
		//Make the room by insertin 0's in the array
		for(n=startx;n<startx+sizex;n++){
			for(m=starty;m<starty+sizey;m++){
				if(n>-1 && m>-1 && m<mapsize && m<mapsize){
					array[n][m]=0;
				}
			}
		}
		
		//Build a tunnel from the last room
		if(lastx<startx){
			for(n=lastx;n<startx+1;n++){
				array[n][lasty]=0;
				//array[n][lasty-1]=0;
			}
		}else{
			for(n=startx;n<lastx+1;n++){
				array[n][lasty]=0;
				//array[n][lasty-1]=0;
			}
		}
		if(lasty<starty){
		
			for(n=lasty;n<starty+1;n++){
				array[startx][n]=0;
				//array[startx-1][n]=0;
			}
		}else{
			for(n=starty;n<lasty+1;n++){
				array[startx][n]=0;
				//array[startx-1][n]=0;
			}
		}
		
		//save coordinates of this room
		if(i%2!=0){
			lastx=startx+sizex/2;
			lasty=starty+sizey/2;
		}
	}
	
	//Add a num. 2 to the last room, could be used as the exit of a level?
	array[lastx+sizex/2-1][lasty-1]=2;
	
	//print map to terminal
	for(n=0;n<mapsize;n++){
		for(m=0;m<mapsize;m++){
			if(array[m][n]==0){
				std::cout<<". ";
			}
			else if(array[m][n]==1){
				std::cout<<"# ";
			}
			else{
				std::cout<<array[m][n]<<" ";
			}
			
		}
		std::cout<<std::endl;
	}
	
	
	
	


	return array;
}
void GameManager::findStart(std::vector<std::vector<int>> map){
	float mcx=0;
	float mcy=0;
	int n,m;
	int mapsize=map.size();
	for(n=0;n<mapsize;n++){
		for(m=0;m<mapsize;m++){
			if (map[n][m]==0){

				mcx=n;
				mcy=m;
				break;
			}
		}
		if(mcx!=0){
			break;
		}
	}
	MCspot.x=mcx;
	MCspot.y=mcy;

	return ;
}

void GameManager::movePlayer(int direction){
	if(movingDown || movingLeft || movingRight || movingUp){
		return;
	}
	switch(direction){
	//up
	case 1:
		MC.setRotation(180);
		MC.setOrigin(50,50);
		if (not (map[(int)MCspot.x][(int)MCspot.y-1]==1)){
			hud.sendMsg("Moving up");
			MCspot.y-=1;
			movingUp=true;
			cmdTime=clock.getElapsedTime().asSeconds();
		}
		break;
		
	//down
	case 2:
		MC.setRotation(0);
		MC.setOrigin(0,0);
		if (not (map[(int)MCspot.x][(int)MCspot.y+1]==1)){
			hud.sendMsg("Moving down");
			MCspot.y+=1;
			movingDown=true;
			cmdTime=clock.getElapsedTime().asSeconds();
		}
		break;
		
	//left
	case 3:
		MC.setRotation(90);
		MC.setOrigin(0,50);
		if (not (map[(int)MCspot.x-1][(int)MCspot.y]==1)){
			hud.sendMsg("Moving left");
			MCspot.x-=1;
			movingLeft=true;
			cmdTime=clock.getElapsedTime().asSeconds();
		}
		break;
		
	//right
	case 4:
		MC.setRotation(270);
		MC.setOrigin(50,0);
		if (not (map[(int)MCspot.x+1][(int)MCspot.y]==1)){
			hud.sendMsg("Moving right");			
			MCspot.x+=1;
			movingRight=true;
			cmdTime=clock.getElapsedTime().asSeconds();
		}
		break;
	}

}
	
bool GameManager::isFree(const sf::Vector2u pos){
	return(map[pos.y][pos.x] == 0);
}
	
void GameManager::setEnemies(){
	*/	TESTING	/*
	this->monsters.push_back(sf::Vector2f(MCspot.x+1, MCspot.y));
}
	
	
	
