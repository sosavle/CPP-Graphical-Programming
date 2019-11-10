#include "library.h"

void draw_closed_star(const double x, const double y, const double s, const int n){
// Setup to begin drawing the star
	if(!n){
		start_shape();
		move_to(x,y);
		set_heading_degrees(18); // Orient the star upwards
		draw_closed_star(x, y, s, 1);
	}
// Recursive behavior to imitate a for loop
	else if(n<=5){
	   note_position();
	   turn_right_by_degrees(360.0/5*2);
	   move_distance(s);
	   draw_closed_star(x, y, s, n+1);
	}
	else if(n>5){
		fill_shape();
	}
}
void draw_open_star(const double x, const double y, const double s, const int n){
// Setup to begin drawing the star
	if(!n){
		move_to(x,y);
		set_heading_degrees(18); // Orient the star upwards
		draw_distance(s/3.0);
		move_distance(s/4.8); //Skip a small space
		draw_distance(s/3.0);
		draw_open_star(x, y, s, 1);
	}
// Recursive behavior to imitate a for loop
	else if(n<=5){
	   turn_right_by_degrees(360.0/5*2);
	   draw_distance(s/3.0);
	   move_distance(s/4.8); //Skip a small space
	   draw_distance(s/3.0);
	   draw_open_star(x, y, s, n+1);
	}
}

void draw_five_stars(const double x1, const double x2, const double y,  const double s){
	const double adjusted_x1 = x1+0.33*s;
	const double adjusted_x2 = x2-0.33*s;
	const double x = adjusted_x2 - adjusted_x1;

	draw_closed_star(2*x/11.0,y,s,0);
	draw_closed_star(4*x/11.0,y,s,0);
	draw_closed_star(6*x/11.0,y,s,0);
	draw_closed_star(8*x/11.0,y,s,0);
	draw_closed_star(10*x/11.0,y,s,0);
}

void draw_six_stars(const double x1, const double x2, const double y,  const double s){
	const double adjusted_x1 = x1+0.66*s;
	const double adjusted_x2 = x2-0.66*s;
	const double x = adjusted_x2 - adjusted_x1;

	draw_closed_star(x/11.0,y,s,0);
	draw_closed_star(3*x/11.0,y,s,0);
	draw_closed_star(5*x/11.0,y,s,0);
	draw_closed_star(7*x/11.0,y,s,0);
	draw_closed_star(9*x/11.0,y,s,0);
	draw_closed_star(11*x/11.0,y,s,0);
}


void draw_eleven_stars(const double x1, const double x2, const double y,  const double s){
	draw_six_stars(x1,x2,y,s);
	draw_five_stars(x1+2*s/3.0,x2,y+0.75*s,s);
}

// PART 1: Many stars
void draw_many_stars(const double width, const double height){
	draw_open_star(width/2, height/4,70,0);
	draw_closed_star(width/4, height/1.3,30,0);
	draw_open_star(width/3, height/1.2,63,0);
	draw_closed_star(width/8, height/3,70,0);
	draw_open_star(width/5, height/4,50,0);
	draw_closed_star(width/4, height/5,30,0);
	draw_open_star(width/1.2, height/4,50,0);
	draw_closed_star(width/1.5, height/5,30,0);
	draw_open_star(width/1.1, height/1.3,50,0);
	draw_closed_star(width/1.3, height/1.3,30,0);
}

// PART 2: DC Flag
void draw_dc_flag(const double height, const double width){

	draw_closed_star(width/4.0,height/15.0,height/4.4,0);
	draw_closed_star(width/2.0,height/15.0,height/4.4,0);
	draw_closed_star(3*width/4.0,height/15.0,height/4.4,0);
	fill_rectangle(0.0,height/2.6,width/1.0,height/5.0);
	fill_rectangle(0.0,height/1.5,width/1.0,height/5.0);	
}

// PART 3: Resizable US Flag
void draw_us_flag(double height){
	const double width = 1.9*height;
	const double s = height/16.0; // Size of a star
	// Draw Stripes
	set_pen_color(color::red);
	fill_rectangle(0.0,0.0,width/1.0,height/13.0);
	fill_rectangle(0.0,2*height/13.0,width/1.0,height/13.0);
	fill_rectangle(0.0,4*height/13.0,width/1.0,height/13.0);
	fill_rectangle(0.0,6*height/13.0,width/1.0,height/13.0);
	fill_rectangle(0.0,8*height/13.0,width/1.0,height/13.0);
	fill_rectangle(0.0,10*height/13.0,width/1.0,height/13.0);
	fill_rectangle(0.0,12*height/13.0,width/1.0,height/13.0);
	// Draw Blue Rectangle
	set_pen_color(color::blue);
	fill_rectangle(0.0,0.0,2*width/5.0,7*height/13.0);
	// Draw Stars
	set_pen_color(color::white);
	draw_eleven_stars(0,2*width/5.0,0.2*height/13.0,s);
	draw_eleven_stars(0,2*width/5.0,1.5*height/13.0,s);
	draw_eleven_stars(0,2*width/5.0,3*height/13.0,s);
	draw_eleven_stars(0,2*width/5.0,4.5*height/13.0,s);
	draw_six_stars(0,2*width/5.0,5.8*height/13.0,s);

}

void main(){
	const double WINDOW_HEIGHT = 300.0;
	const double WINDOW_WIDTH = 1.9*WINDOW_HEIGHT;
	set_pen_width(2);

	//Draw Stars
	make_window(WINDOW_WIDTH, WINDOW_HEIGHT);
	set_caption("Many Stars!");
	set_pen_color(color::green);
	draw_many_stars(WINDOW_WIDTH, WINDOW_HEIGHT);

	//Draw DC Flag
	make_window(WINDOW_WIDTH, WINDOW_HEIGHT);
	set_caption("It's DC!");
	set_pen_color(color::red);
	draw_dc_flag(WINDOW_HEIGHT, WINDOW_WIDTH);
	
	//Draw US Flag
	make_window(WINDOW_WIDTH, WINDOW_HEIGHT);
	set_caption("In AMERICA");
	draw_us_flag(WINDOW_HEIGHT);

	//It's resizable
	make_window(WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
	set_caption("It's resizable!");
	draw_us_flag(WINDOW_HEIGHT/2);
}
