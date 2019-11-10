#include "library.h"

void draw_mountains(int x, int windowWidth,int windowHeight){
	note_position();
	if(x<windowWidth){
		set_heading_degrees(random_in_range(60,120));
		draw_distance(random_in_range(10,5));
	int new_x = get_x_position();
	draw_mountains(new_x,windowWidth, windowHeight);
	}
}

void draw_background(int windowWidth,int windowHeight){
	int mode = random_in_range(0,2);
	int sky;

	if(mode == 0){
		sky = color::indigo;
	}
	else if (mode == 1)
		sky = color::light_blue;
	else
		sky = color::orange;

	set_pen_color(sky);
	fill_rectangle(0,0,windowWidth, windowHeight);
	set_pen_width(75);

	if(mode==0){
		set_pen_color(0.96,0.97,0.46);
		draw_point(100+22*20,100);
		set_pen_color(sky);
		draw_point(100+22*20-20,100-20);
	}
	if(mode==1){
		set_pen_color(color::yellow);
		draw_point(100+22*20,100);
	}

	
	set_pen_width(2);
	set_pen_color(0,0.5,0.5);
	move_to(0,200);
	start_shape();
	note_position(0,windowHeight);
	draw_mountains(0,windowWidth,windowHeight);
	note_position(windowWidth,windowHeight);
	fill_shape();


	set_pen_color(0,0.69,0.2);
	move_to(0,250);
	start_shape();
	note_position(0,windowHeight);
	draw_mountains(0,windowWidth,windowHeight);
	note_position(windowWidth,windowHeight);
	fill_shape();


	set_pen_color(0,0.55,0);
	move_to(0,300);
	start_shape();
	note_position(0,windowHeight);
	draw_mountains(0,windowWidth,windowHeight);
	note_position(windowWidth,windowHeight);
	fill_shape();

	set_pen_color(color::light_red);
	fill_rectangle(0,windowHeight-40,windowWidth+2,windowHeight);
	set_pen_color(color::dark_grey);
	fill_rectangle(0,windowHeight-20,windowWidth+2,windowHeight);

}

void draw_window(int x, int y, int width, int height, int color){
	// Draw Window
	fill_rectangle(x,y,width,height,color);
	// Draw Curtains
	int has_curtains = random_in_range(1,10);
	if(has_curtains == 1){
		set_pen_width(1);
		set_pen_color(color::red);
		
		// Left Curtain
		start_shape();
		move_to(x,y);
		note_position();
		move_to(x+width/6,y);
		note_position();
		set_heading_degrees(-160);
		draw_distance(height/3);
		note_position();
		set_heading_degrees(160);
		draw_distance(height-height/3);
		note_position();
		move_to(x,y+height);
		note_position();
		
		fill_shape();

		// Right Curtain
		start_shape();
		move_to(x+width,y);
		note_position();
		move_to(x+width-width/6,y);
		note_position();
		set_heading_degrees(160);
		draw_distance(height/3);
		note_position();
		set_heading_degrees(-160);
		draw_distance(height-height/3);
		note_position();
		move_to(x+width,y+height);
		note_position();
		
		fill_shape();
	}

	// Draw creepo
	int has_creepo = random_in_range(1,5);
	if(has_creepo == 1){
		set_pen_color(color::white);
		move_to(x+width/2,y+height/2);
		set_pen_width(8);
		draw_point();
		fill_rectangle(x+width/2-1,y+height/2,3,height/2);
		set_pen_color(color::black);
		move_to(x+2*width/5,y+height/2);
		set_pen_width(3);
		draw_point();
		move_to(x+3*width/5,y+height/2);
		draw_point();
	}
}

void draw_door(int x, int width, int height, int y, int doorColor, int doorH){
		fill_rectangle(x,y,width,doorH,doorColor);
	}

void draw_window_row(int n, int x, int width, int height, int y, int color){
	if(n>0){
		draw_window(x,y,width,height,color);
		draw_window_row(n-1,x+30,width,height,y,color);
	}
}

void draw_bottom_floor(int n, int x, int width, int height, int y, int color, int door, int doorH, int doorColor){
	if(n>0 && n != door){
		draw_window(x,y,width,height,color);
		draw_bottom_floor(n-1,x+30,width,height,y,color, door, doorH, doorColor);
	}
	else if(n==door){
		draw_door(x, width, height, y+height/3, doorColor, doorH-height/3);
		draw_bottom_floor(n-1,x+30,width,height,y,color, door, doorH, doorColor);
	}
}

void draw_window_block(int i, int j, int x, int h, int w, int y, int color){
	if(i>0){
		draw_window_row(j,x,w,h,y,color);
		draw_window_block(i-1, j, x, h, w, y-h-8, color);
	}
}

int set_window_color(){
	int rand = random_in_range(0,2);
	if(rand == 0) return color::purple;
	if(rand == 1) return color::indigo;
	else return color::dark_green;
}

int set_building_color(){
	int rand = random_in_range(0,2);
	if(rand == 0) return color::pink;
	if(rand == 1) return color::light_blue;
	if(rand == 2) return color::light_green;
}

void draw_buildings(int x, int windowHeight, int height, int width){
	int winH = random_in_range(10,20);
	int winW = random_in_range(10,20);
	set_pen_color(set_building_color());
	fill_rectangle(25+x,windowHeight-height-45,width+5,height+5);

	int windowColor = set_window_color();
	draw_window_block(height/(winH+8)-1,width/30,x+40,winH,winW,windowHeight-65,windowColor);
}

void draw_office_street(int windowWidth, int windowHeight, int distanceFilled){
	if(distanceFilled<windowWidth){
		int height = random_in_range(250,400);
		int width = random_in_range(100,250);
		draw_buildings(distanceFilled, windowHeight, height, width);
		draw_office_street(windowWidth, windowHeight, distanceFilled+width+30);
	}
}

int set_door_color(){
	int rand = random_in_range(0,2);
	if(rand == 0) return color::brown;
	else if(rand == 1) return color::dark_red;
	else return color::lime_green;
}

void set_house_color(){
	int rand = random_in_range(0,2);
	if(rand == 0) set_pen_color(color::light_grey);
	else if(rand == 1) set_pen_color(0.93,0.81,0.81);
	else set_pen_color(0.98,0.98,0.92);
}

void set_roof_color(){
	int rand = random_in_range(0,2);
	if(rand == 0) set_pen_color(color::yellow);
	else if(rand == 1) set_pen_color(0.81,0.80,0.08);
	else set_pen_color(0.93,0.42,0.31);
}


void draw_house(int x, int windowWidth, int windowHeight, int height, int width){
	
	// Draw House
	set_house_color();
	fill_rectangle(x,windowHeight-height-20,width,height);
	
	// Draw Roof
	set_roof_color();
	start_shape();
	move_to(x-15,windowHeight-height-20);
	note_position();
	set_heading_degrees(60);
	move_distance(((width+30)/2.0)/cos(30.0*3.1416/180));
	note_position();
	set_heading_degrees(120);
	move_distance(((width+30)/2.0)/cos(30.0*3.1416/180));
	note_position();
	fill_shape();

	// Draw Windows
	int floors;
	int numWindows;
	int winWidth = random_in_range(10,20);
	int winHeight = random_in_range(15,20);

	if(height>=80) floors = 2;
	else floors = 1;

	int windowColor = set_window_color();
	int doorColor = set_door_color();

	if(floors == 2){
		draw_window_row(width/30,x+10,winWidth,winHeight,windowHeight-height-12-20+winHeight+5,windowColor);
		draw_bottom_floor(width/30,x+10,winWidth,winHeight,windowHeight-height-12-20+winHeight+35,windowColor,random_in_range(1,width/30),height-2*winHeight-8,doorColor);
	}
	else{
		draw_bottom_floor(width/30,x+10,winWidth,winHeight,windowHeight-height-12-10+winHeight,windowColor,random_in_range(1,width/30),height-winHeight,doorColor);
	}
}

void draw_house_street(int windowWidth, int windowHeight, int distanceFilled){
	if(distanceFilled<windowWidth){
		int height = random_in_range(60,90);
		int width = random_in_range(100,180);
		draw_house(distanceFilled, windowWidth, windowHeight, height, width);
		draw_house_street(windowWidth, windowHeight, distanceFilled+200+30);
	}
	
}

void draw_foliage(int n, int x_min, int x_max, double y_min, double y_max, int r, int xcentre, int ycentre){
	if(n>0){
		int x = random_in_range(x_min, x_max);
		int y = random_in_range(y_min, y_max);
		int c = random_in_range(0,2);
		if(c==0) set_pen_color(color::green);
		else if(c==1) set_pen_color(color::dark_green);
		else set_pen_color(color::light_green);
		set_pen_width(random_in_range(5,10));

		int normal_x = x-xcentre;
		int normal_y = y-ycentre;

		if(normal_x*normal_x + normal_y*normal_y <= r*r){
			draw_point(x,y);
		}
		draw_foliage(n-1, x_min, x_max, y_min, y_max, r, xcentre, ycentre);
	}
}


void draw_tree(int x, int windowWidth, int windowHeight, int height, int width){
	set_pen_color(color::sodium_d);
	int y = windowHeight-height-21;
	fill_rectangle(x,y,width,height);
	move_to(x+width/2,y);
	draw_foliage(1000, x-width, x+2*width, y-1.5*width, y+1.5*width, 1.5*width, x+width/2,y);
}

void draw_tree_row(int windowWidth, int windowHeight, int distanceFilled){
	if(distanceFilled<windowWidth){
		int width = random_in_range(20,45);
		int height = width*random_in_range(4,5);
		draw_tree(distanceFilled, windowWidth, windowHeight, height, width);
		draw_tree_row(windowWidth, windowHeight, distanceFilled + 80);
	}
}

void draw_grass(int n, int windowWidth, int windowHeight){
	if(n>0){
		int x = random_in_range(0, windowWidth);
		int deg = random_in_range(-60,60);
		int c = random_in_range(0,2);
		if(c==0) set_pen_color(color::green);
		else if(c==1) set_pen_color(color::dark_green);
		else set_pen_color(color::light_green);
		move_to(x,windowHeight);
		set_heading_degrees(deg);
		set_pen_width(random_in_range(1,3));
		draw_distance(random_in_range(5,40));
		draw_grass(n-1,windowWidth,windowHeight);
	}
}

void main(){
	const int windowWidth = 700;
	const int windowHeight = 600;
	make_window(windowWidth,windowHeight);
	draw_background(windowWidth,windowHeight);
	draw_office_street(windowWidth,windowHeight,0);
	draw_tree_row(windowWidth, windowHeight, 20);
	draw_house_street(windowWidth, windowHeight,35);
	draw_grass(1000, windowWidth, windowHeight);
	
}
