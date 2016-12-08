#include "Gamemanager.hpp"



GameManager::GameManager(){
	
	hero=Hero(100,10,10,10,100);
	hud=HUD(hero);
	
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


	if (!MC_t.loadFromFile("resources/knight_animation2.png"))
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


	/*	TESTING	*/
	Monster monsu(sf::Vector2i(MCspot.x+2,MCspot.y+2));
	monsters.push_back(monsu);
	loadEnemyTexture(monsters[0]);

}

void GameManager::loadEnemyTexture(Monster& enemy){
	sf::Texture new_texture;
	if (!new_texture.loadFromFile(enemy.getPicName())){
		perror("Couldn't load enemy texture: ");
	}
	enemy_textures[enemy.getName()]=new_texture;
	enemy_sprites[enemy.getName()]=sf::Sprite();
	
	//SourceSprite=sf::IntRect(0,0,50,50);
	enemy_sprites[enemy.getName()].setTexture(enemy_textures[enemy.getName()]);


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

	/*	TESTING */
	tryDetectPlayer(monsters[0]);
	monsters[0].moveTowardsTarget(map);
	
	
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
	drawEnemies(window);

}

void GameManager::drawFps(sf::RenderWindow& window){
	fpsTime=fpsClock.restart().asSeconds();
	int fps=(int) 1.f/(fpsTime);
	
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

void GameManager::drawEnemies(sf::RenderWindow& window){
	
		// How I'm supposed to draw something?
		
	//This is how:
	for(n=0;n<monsters.size();n++){
		float xmonmove=0;
		float ymonmove=0;
		int monoffy=0;
		int monoffx=0;
		std::string name=monsters[n].getName();
		if(monsters[n].movesUp())
		{
			enemy_sprites[name].setRotation(180);
			enemy_sprites[name].setOrigin(50,50);
			ymonmove=-std::max(fabs(yPercentage),fabs(xPercentage));
			monoffy=50;
			//std::cout<<ymonmove<<std::endl;
		}
		else if(monsters[n].movesDown()){
			enemy_sprites[name].setRotation(0);
			enemy_sprites[name].setOrigin(0,0);
			ymonmove=std::max(fabs(yPercentage),fabs(xPercentage));
			monoffy=-50;
		}
		else if(monsters[n].movesLeft()){
			enemy_sprites[name].setRotation(90);
			enemy_sprites[name].setOrigin(0,50);
			xmonmove=-std::max(fabs(yPercentage),fabs(xPercentage));
			monoffx=50;
		}
		else if(monsters[n].movesRight()){
			enemy_sprites[name].setRotation(270);
			enemy_sprites[name].setOrigin(50,0);
			xmonmove=std::max(fabs(yPercentage),fabs(xPercentage));
			monoffx=-50;
		}

		int a=(int)50*(monsters[n].getPos().x-MCspot.x+7)+offsetx+xPercentage*50+xmonmove*50+monoffx;
		int b=(int)50*(monsters[n].getPos().y-MCspot.y+4)+offsety+yPercentage*50+ymonmove*50+monoffy;
		//std::cout<<"Drew enemy in: "<<a<<","<<b<<std::endl;
		enemy_sprites[name].setPosition(a,b);
		window.draw(enemy_sprites[name]);
	}
		
	
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
			monsters[0].stopMove();
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
			
			//monsters[0].moveLeft();
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
			
			//monsters[0].moveRight();
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
			
			
			//monsters[0].moveDown();
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
			
			
			//monsters[0].moveUp();
		}
		break;
	}

}
	
bool GameManager::isFreeTile(unsigned int x, unsigned int y){
	return(map[y][x] == 0);
}

void GameManager::tryDetectPlayer(Monster& monster){
	if(!seePlayer(monster)){
		hearPlayer(monster);
	}
}

bool GameManager::hearPlayer(Monster& monster){
	float distance = std::sqrt(std::pow(MCspot.x - monster.getPos().x, 2)
							  +std::pow(MCspot.y - monster.getPos().y, 2));
	if(monster.getHearingRadius() > distance){
		monster.detectPlr(MCspot);
		hud.sendMsg("I hear ya!");
		return true;
	}
	else{
		monster.undetectPlr();
		return false;	
	}
}

bool GameManager::seePlayer(Monster& monster){



	if (freeLineOfSight(MCspot, monster.getPos())){
		monster.detectPlr(MCspot);
		hud.sendMsg("I see ya!");
		return true;
	}
	else{
		monster.undetectPlr();
		return false;
	}

}
	

bool GameManager::freeLineOfSight(sf::Vector2i a, sf::Vector2i b){

	return false;   //TESTING

	int dx,dy, ax,ay,bx,by;
	ax = (int) a.x; ay = (int) ay;
	bx = (int) b.x; by = (int) by; 


	dx = bx - ax;
	dy = by - ay;
	bool paraller = (dx+1)%(dy+1);
	int steps_row = (dx+1)/(dy+1);
	if(paraller) steps_row +=1;

	int x = ax , y = ay, steps = 1;

	
	std::string coord=  "paraller: "+std::to_string(paraller)+"  steps: "+std::to_string(steps_row);
	std::cout << coord;
	while(!(x == bx && y == by)){

		if(!isFreeTile(x,y)){
			return false;
		}
		if(steps != steps_row){
			x++; steps++;
			continue;
		}
		
		//std::string coord=  "X: "+std::to_string(x)+"  Y: "+std::to_string(y);
		//hud.sendMsg(coord);
	
		else{
			if(paraller){
				y++;
			}
			else{
				y++; x++;
			}


			steps =1;


		}
	
	}
	return true;

		


		
	
}
	
void GameManager::setEnemies(){
	/*	TESTING	
	this->monsters.push_back(sf::Vector2f(MCspot.x+1, MCspot.y));
	*/
}
	
	
	
