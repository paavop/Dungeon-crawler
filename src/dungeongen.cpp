#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <iostream>
#include <string>
main(){

	int mapsize=30;
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
	int rooms=rand() %5 +9;

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
	array[lastx+sizex/2-1][lasty]=2;
	
	//print map to terminal
	for(n=0;n<mapsize;n++){
		for(m=0;m<mapsize;m++){
			std::cout<<array[n][m]<<" ";
		}
		std::cout<<std::endl;
	}
}


	
