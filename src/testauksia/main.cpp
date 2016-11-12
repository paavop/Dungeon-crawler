#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>


//Muita kokeiluja


main(){
	int mapsize=50;
	int array[mapsize][mapsize];
	int n,m;
	
	//Fill the map with walls
	for(n=0;n<mapsize;n++){
		for(m=0;m<mapsize;m++){
			array[n][m]=1;
		}
	}
	srand (time(NULL));
	
	//How many rooms are made
	int rooms=rand() %5 +12;

	//std::cout<<"Rooms: "<<rooms<<std::endl;
	int i;
	
	//lastx and lasty are used to build tunnels from one room to another
	int lastx=rand() %(mapsize-1)+1;
	int lasty=rand() %(mapsize-1)+1;
	int sizex,sizey,startx,starty;
	
	 
	for(i=0;i<rooms;i++){
		//A different size and location is randomized for every room
		sizex=rand() %6 +3;
		sizey=rand() %6 +3;
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
			}
		}else{
			for(n=startx;n<lastx+1;n++){
				array[n][lasty]=0;
			}
		}
		if(lasty<starty){
		
			for(n=lasty;n<starty+1;n++){
				array[startx][n]=0;
			}
		}else{
			for(n=starty;n<lasty+1;n++){
				array[startx][n]=0;
			}
		}
		
		//save coordinates of this room
		lastx=startx+sizex/2;
		lasty=starty+sizey/2;
	}
	
	//Add a num. 2 to the last room, could be used as the exit of a level?
	array[lastx+sizex/2-1][lasty-1]=2;
	
	//print map to terminal
	for(n=0;n<mapsize;n++){
		for(m=0;m<mapsize;m++){
			std::cout<<array[m][n]<<" ";
		}
		std::cout<<std::endl;
	}

	
	
	
	
	
	//Finds a safe spot for the player to start (not a wall)
	float mcx=0;
	float mcy=0;
	for(n=0;n<mapsize;n++){
		for(m=0;m<mapsize;m++){
			if (array[n][m]==0){
				mcx=n;
				mcy=m;
				break;
			}
		}
		if(mcx!=0){
			break;
		}
	}
	
	
	//pelaajan aloituspiste taulukossa
	sf::Vector2f mc(mcx,mcy);
	

 	//Loading textures to sprites
	sf::Texture wallt;
	if (!wallt.loadFromFile("resources/wall50.png"))
	{
	    // error...
	}
	sf::Sprite wall(wallt);

	sf::Texture groundt;
	if (!groundt.loadFromFile("resources/ground50.png"))
	{
	    // error...
	}
	sf::Sprite ground(groundt);

	sf::Texture abajt;
	if (!abajt.loadFromFile("resources/knight50.png"))
	{
	    // error...
	}
	sf::Sprite jaba(abajt);
	sf::Texture stair;
	if (!stair.loadFromFile("resources/stairs.png"))
	{
	    // error...
	}
	sf::Sprite stairs(stair);
	
	//Siirretaan pelihahmon kuva keskelle peliruutua
	jaba.setPosition(200,200);
	
	
	//luodaan peliruutu (450x450 px)
	int windowx=450;
	int windowy=450;
	sf::RenderWindow window(sf::VideoMode(windowx, windowy), "Testi!");
	
	//nailla pidetaan tiedossa mihin viimeksi liikuttu ja mihin liikkumassa
	bool l,r,u,d,print,ml=false;
	bool mu=false;
	bool mr=false;
	bool md=false;
	//animaatiot aikaan sidottuja, naita kaytetaan ajan mittaamiseen
	sf::Clock clock2;

	//haluttu animaatioon kuluva aika
	float animationtime=0.11;
	float cmdtime;
	
	
	while (window.isOpen())
	{
	

		//alla olevat if ja else if -jutut tsekkaavat milloin mitakin nuolinappainta on painettu
		//ja paastetty irti
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) and !(mu || md || ml || mr))
		{
			l=true;

		}else if(l){
			/*kun liikutaan vasemmalle, pitaa pelihahmon graffoja kaantaa 90 astetta
			Kuva kiertyy kuitenkin vasemman ylakulman suhteen, joten pitaa siirtaa
			50 px oikealle jotta on taas oikeassa kohdassa
			*/
			jaba.setRotation(90);
			jaba.setOrigin(0,50);
			print=true;
			if (not (array[(int)mc.x-1][(int)mc.y]==1)){
				//Pelihahmon todellinen sijainti jo seuraavassa ruudussa, animaatio tulee perassa
				mc.x-=1;
				ml=true;
				//Otetaan talteen aika jolloin kasky on annettu, kaytetaan liikkumisanimaation 
				//piirtoon
				cmdtime=clock2.getElapsedTime().asSeconds();
			}
			l=false;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) and !(mu || md || ml || mr))
		{
			r=true;

		}else if(r){
			jaba.setRotation(270);
			jaba.setOrigin(50,0);
			print=true;
			if (not (array[(int)mc.x+1][(int)mc.y]==1)){
				mc.x+=1;
				mr=true;
				cmdtime=clock2.getElapsedTime().asSeconds();
			}
			r=false;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) and !(mu || md || ml || mr))
		{
			u=true;

		}else if(u){
			jaba.setRotation(180);
			jaba.setOrigin(50,50);
			print=true;
			if (not (array[(int)mc.x][(int)mc.y-1]==1)){
				mc.y-=1;
				mu=true;
				cmdtime=clock2.getElapsedTime().asSeconds();
			}
			u=false;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) and !(mu || md || ml || mr))
		{
			d=true;

		}else if(d){
			jaba.setRotation(0);
			jaba.setOrigin(0,0);
			print=true;
			if (not (array[(int)mc.x][(int)mc.y+1]==1)){

				mc.y+=1;
				md=true;
				cmdtime=clock2.getElapsedTime().asSeconds();
			}
			d=false;
		}
		
		
		
		//tsekataan onko ruksia painettu eli suljetaanko ohjelma
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		//tyhjentaa peliruudun
		window.clear();
		
		/*Alla oleva piirtaa pelihahmon smoothin liikkeen vertaamalla kulunutta aikaa kaskyn annosta 
		aikaan jonka animaation halutaan kestavan. Piirtaa hahmon taman suhteen verran siihen suuntaan
		mihin ollaan liikkumassa.
		*/
		if(ml || mu || md || mr){
			float pery=0;
			float perx=0;
			if(mu || md){
				pery=(clock2.getElapsedTime().asSeconds()-cmdtime)/animationtime;
				if(pery>1){
					pery=1;
				}
			}
			if(ml || mr){
				perx=(clock2.getElapsedTime().asSeconds()-cmdtime)/animationtime;
				if(perx>1){
					perx=1;
				}
			}
			
			//std::cout<<"x%: "<<perx<<" y%: "<<pery<<std::endl;
			float per=(clock2.getElapsedTime().asSeconds()-cmdtime)/animationtime;
			for(n=0;n<9;n++){
				for(m=0;m<9;m++){
					wall.setPosition(perx*50+50*(n),pery*50*(m));
					window.draw(wall);
				}
			}
			float offsetx=0;
			float offsety=0;
			if(ml){
				offsetx=-50;
				
			}
			if(mr){
				offsetx=50;
				perx=-perx;
			}
			if(mu){
				offsety=-50;

			}
			if(md){
				offsety=50;
				pery=-pery;
				
			}
			for(n=-1;n<10;n++){
				for(m=-1;m<10;m++){
					wall.setPosition(offsetx+perx*50+50*(n),offsety+pery*50+50*(m));
					window.draw(wall);
				}
			}
			for(n=(int) mc.x -5;n<(int) mc.x +6;n++){
				for(m=(int) mc.y -5;m<(int) mc.y +6;m++){
					if(n>-1 && m>-1 && n<mapsize && m<mapsize){
						if(array[n][m]==1){
							wall.setPosition(offsetx+perx*50+50*(-mc.x+n+4),offsety+pery*50+50*(-mc.y+m+4));
							window.draw(wall);
						}else if(array[n][m]==0){
					
							ground.setPosition(offsetx+perx*50+50*(-mc.x+n+4),offsety+pery*50+50*(-mc.y+m+4));
							window.draw(ground);


						}else if(array[n][m]==2){
							stairs.setPosition(offsetx+perx*50+50*(-mc.x+n+4),offsety+pery*50+50*(-mc.y+m+4));
							window.draw(stairs);					
						}
					}

				}
			}
			if(clock2.getElapsedTime().asSeconds()-cmdtime>animationtime){
				
		
				ml=false;
			
		
				mu=false;
			
		
				md=false;
			
		
				mr=false;
			
			}
		//Jos ei olla liikkumassa piirtaa vain basic tilanteen, ei hankalia animaatiosaatoja
		}else{
		
			for(n=0;n<9;n++){
				for(m=0;m<9;m++){
					wall.setPosition(50*(n),50*(m));
					window.draw(wall);
				}
			}
			for(n=(int) mc.x -5;n<(int) mc.x +6;n++){
				for(m=(int) mc.y -5;m<(int) mc.y +6;m++){
					if(n>-1 && m>-1 && n<mapsize && m<mapsize){
						if(array[n][m]==1){
							wall.setPosition(50*(-mc.x+n+4),50*(-mc.y+m+4));
							window.draw(wall);
						}else if(array[n][m]==0){
					
						
							ground.setPosition(50*(-mc.x+n+4),50*(-mc.y+m+4));
							window.draw(ground);


						}else if(array[n][m]==2){
					
						
							stairs.setPosition(50*(-mc.x+n+4),50*(-mc.y+m+4));
							window.draw(stairs);


						}
					}

				}
			}
		}
		//piirtaa viela pelihahmon keskelle ruutua
		window.draw(jaba);
		window.display();
		//printtaillaan kaikkea jannaa
		if(print){
			//std::cout<<"Pos x: "<<mc.x<<" Pos y: "<<mc.y<<std::endl;
			print=false;
		}
	}

}



