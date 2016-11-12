#include <SFML/Graphics.hpp>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>

//Muita kokeiluja
int dvdsaver();
int blockbuster();
int blockbuster2();


int main()
{	
	//Luodaan 20*20 taulukko nollia ja ykkosia, reunat ladataan 1:silla eli seinilla
	int array [20][20];
	int m,n;
	for (n=0;n<20;n++){
		for (m=0;m<20;m++){
			if(m==0 || n==0 ||m==19||n==19 ){
				array[n][m]=1;
			}else{
				array[n][m]=0;
			}
		}
	}
	
	//heitetaan random seinia joukkoon
	array[5][6]=1;
	array[15][16]=1;
	array[15][6]=1;
	array[3][5]=1;
	array[5][7]=1;
	array[18][6]=1;
	array[10][10]=1;
	array[7][13]=1;

	//pelaajan aloituspiste taulukossa
	sf::Vector2f mc(1.f,1.f);
	

 	//Ladataan kolme texturea ja laitetaan Sprite-jutskiin (wall, ground, pelihahmo)
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
			/*kun liikutaan vasemmalle, pitää pelihahmon graffoja kaantaa 90 astetta
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
			
			std::cout<<"x%: "<<perx<<" y%: "<<pery<<std::endl;
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
					if(n>-1 && m>-1 && n<20 && m<20){
						if(array[n][m]==1){
							wall.setPosition(offsetx+perx*50+50*(-mc.x+n+4),offsety+pery*50+50*(-mc.y+m+4));
							window.draw(wall);
						}else if(array[n][m]==0){
					
							ground.setPosition(offsetx+perx*50+50*(-mc.x+n+4),offsety+pery*50+50*(-mc.y+m+4));
							window.draw(ground);


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
					if(n>-1 && m>-1 && n<20 && m<20){
						if(array[n][m]==1){
							wall.setPosition(50*(-mc.x+n+4),50*(-mc.y+m+4));
							window.draw(wall);
						}else if(array[n][m]==0){
						
							ground.setPosition(50*(-mc.x+n+4),50*(-mc.y+m+4));
							window.draw(ground);


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
			std::cout<<"Pos x: "<<mc.x<<" Pos y: "<<mc.y<<std::endl;
			print=false;
		}
	}

}


//Alla myos vanhoja saatoja, aika turhia tosin
int blockbuster2(){
	int array [20][20];
	int m,n;
	for (n=0;n<20;n++){
		for (m=0;m<20;m++){
			if(m==0 || n==0 ||m==19||n==19 ){
				array[n][m]=1;
			}else{
				array[n][m]=0;
			}
		}
	}
	array[5][6]=1;
	array[15][16]=1;
	array[15][6]=1;
	array[3][5]=1;
	array[5][7]=1;
	array[18][6]=1;
	array[10][10]=1;
	array[7][13]=1;

	sf::Vector2f mc(3.f,2.f);
	sf::CircleShape bob(50.f);
	bob.setFillColor(sf::Color::Green);
	bob.setPosition(400,400);

	sf::Texture wallt;
	if (!wallt.loadFromFile("resources/wall100.png"))
	{
	    // error...
	}
	sf::Sprite wall(wallt);

	sf::Texture groundt;
	if (!groundt.loadFromFile("resources/ground100.png"))
	{
	    // error...
	}
	sf::Sprite ground(groundt);

	sf::Texture abajt;
	if (!abajt.loadFromFile("resources/knight100.png"))
	{
	    // error...
	}
	sf::Sprite jaba(abajt);

	jaba.setPosition(400,400);
	
	sf::RectangleShape rec(sf::Vector2f(100, 100));
	rec.setFillColor(sf::Color::Red);

	int windowx=900;
	int windowy=900;
	sf::RenderWindow window(sf::VideoMode(windowx, windowy), "Testi!");
	bool l,r,u,d,print=false;
	while (window.isOpen())
	{

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			l=true;

		}else if(l){
			jaba.setRotation(90);
			jaba.setOrigin(0,100);
			print=true;
			if (not (array[(int)mc.x-1][(int)mc.y]==1)){
				mc.x-=1;
			}
			l=false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			r=true;

		}else if(r){
			jaba.setRotation(270);
			jaba.setOrigin(100,0);
			print=true;
			if (not (array[(int)mc.x+1][(int)mc.y]==1)){
				mc.x+=1;
			}
			r=false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			u=true;

		}else if(u){
			jaba.setRotation(180);
			jaba.setOrigin(100,100);
			print=true;
			if (not (array[(int)mc.x][(int)mc.y-1]==1)){
				mc.y-=1;
			}
			u=false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			d=true;

		}else if(d){
			jaba.setRotation(0);
			jaba.setOrigin(0,0);
			print=true;
			if (not (array[(int)mc.x][(int)mc.y+1]==1)){
				mc.y+=1;
			}
			d=false;
		}

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		for(n=0;n<10;n++){
			for(m=0;m<10;m++){
				wall.setPosition(100*(n),100*(m));
				window.draw(wall);
			}
		}
		for(n=(int) mc.x -4;n<(int) mc.x +5;n++){
			for(m=(int) mc.y -4;m<(int) mc.y +5;m++){
				if(n>-1 && m>-1 && n<20 && m<20){
					if(array[n][m]==1){
						wall.setPosition(100*(-mc.x+n+4),100*(-mc.y+m+4));
						window.draw(wall);
					}else if(array[n][m]==0){
						
						ground.setPosition(100*(-mc.x+n+4),100*(-mc.y+m+4));
						window.draw(ground);


					}
				}

			}
		}
		window.draw(jaba);
		window.display();
		if(print){
			std::cout<<"Pos x: "<<mc.x<<" Pos y: "<<mc.y<<std::endl;
			print=false;
		}
	}
}
int blockbuster(){
	int array [10][10];
	int m,n;

	for (n=0;n<10;n++){
		for (m=0;m<10;m++){
			if(m==0 || n==0 ||m==9||n==9 ){
				array[n][m]=1;
			}else{
				array[n][m]=0;
			}
		}
	}
	sf::RectangleShape rec(sf::Vector2f(100, 100));
	rec.setFillColor(sf::Color::Red);

	sf::Vector2f myspot(5.f,5.f);
	sf::CircleShape mc(50.f);
	mc.setFillColor(sf::Color::Green);
	mc.setPosition(myspot.x*100,myspot.y*100);

	int windowx=1000;
	int windowy=1000;
	sf::RenderWindow window(sf::VideoMode(windowx, windowy), "Testi!");
	bool l,r,u,d=false;
	while (window.isOpen())
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			l=true;

		}else if(l){
			if (not (array[(int)myspot.x-1][(int)myspot.y]==1)){
				myspot.x-=1;
				mc.setPosition(myspot.x*100,myspot.y*100);
			}
			l=false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			r=true;

		}else if(r){
			if (not (array[(int)myspot.x+1][(int)myspot.y]==1)){
				myspot.x+=1;
				mc.setPosition(myspot.x*100,myspot.y*100);
			}
			r=false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			u=true;

		}else if(u){
			if (not (array[(int)myspot.x][(int)myspot.y-1]==1)){
				myspot.y-=1;
				mc.setPosition(myspot.x*100,myspot.y*100);
			}
			u=false;
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			d=true;

		}else if(d){
			if (not (array[(int)myspot.x][(int)myspot.y+1]==1)){
				myspot.y+=1;
				mc.setPosition(myspot.x*100,myspot.y*100);
			}
			d=false;
		}
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		for (n=0;n<10;n++){
			for (m=0;m<10;m++){
				if(array[n][m]==1){
					rec.setPosition(n*100,m*100);
					window.draw(rec);


				}
			}
		}
		window.draw(mc);
		window.display();
	}
	return 0;
}
int dvdsaver(){
	int windowx=1000;
	int windowy=1000;
	auto circ=100.f;
	sf::RenderWindow window(sf::VideoMode(windowx, windowy), "SFML works!");
	sf::CircleShape shape(circ);
	shape.setFillColor(sf::Color::Red);
	shape.setPosition(0,100);
	float speedx=4.5;
	float speedy=5.5;
	sf::Vector2f pos=shape.getPosition();
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		window.clear();
		window.draw(shape);
		window.display();
		pos=shape.getPosition();
		std::cout<<"Pos x: "<<pos.x<<" Pos y: "<<pos.y<<std::endl;
		if(pos.x>windowx-2*circ){
			speedx=-speedx;
		}
		if(pos.x<0){
			speedx=-speedx;
		}
		if(pos.y>windowy-2*circ){
			speedy=-speedy;
		}
		if(pos.y<0){
			speedy=-speedy;
		}
		shape.move(speedx,speedy);
	}


	return 0;
}
