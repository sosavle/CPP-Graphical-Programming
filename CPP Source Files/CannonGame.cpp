#include "library.h"


// FUNCTIONS USED BY THE WHOLE PROGRAM
double calculate_height(const double velocity, const double time){
	return (velocity*time - 16.087*time*time + 0.5);
}

double calculate_time(const double velocity){
	return 2*velocity/32.174;
}

double calculate_distance(const double velocity, const double time){
	return velocity*time;
}

/////// INITIAL PARTS OF THE LAB
void trajectory_interface(const double velocity, const double time, const double totalTime){
	if(time>0){
	trajectory_interface(velocity, time-1, totalTime);
	int adjustedTime = time*10; // Used to get rid of excessive decimals
	cout << "after " << adjustedTime/10.0 << " seconds (" << int(time/totalTime*100+0.5) << "%), height is " << calculate_height(velocity,time) << " feet" << endl;
	}
}

// Console printing of values
void print_trajectory(const double velocity){
	const double time = calculate_time(velocity);
	trajectory_interface(velocity, time, time);
}

// Gradual color change during trajectory
double gradient(double n, double maxTime){
	return n/maxTime;
}

// Draw vertical diagram
void plot_vertical_interface(double maxTime, double velocity, int n, double windowHeight){
	if(n <= maxTime){
		set_pen_color(1-gradient(n,maxTime), 0, gradient(n,maxTime));
		draw_point(50.0,windowHeight-calculate_height(velocity,n));
		plot_vertical_interface(maxTime, velocity, n+1, windowHeight);
	}
}

// Setup for vertical diagram (Used so that the user does not have to specify n=0, as this is always the case)
void plot_vertical(double velocity){
	double maxTime = calculate_time(velocity);
	double windowHeight = calculate_height(velocity,maxTime/2)+30;
	make_window(100, windowHeight);
	set_pen_width(5);
	plot_vertical_interface(maxTime, velocity, 0, windowHeight);
}


// Draw arc
void plot_trajectory_interface(double maxTime, double velocity, double n, double windowHeight, double windowWidth){
	if(n <= maxTime){
		set_pen_color(1-gradient(n,maxTime), 0, gradient(n,maxTime));
		draw_point(windowWidth*n/maxTime,windowHeight-calculate_height(velocity,n));
		plot_trajectory_interface(maxTime, velocity, n+0.001, windowHeight, windowWidth);
	}
}
 
// Setup for drawing arc (Used so that the user does not have to specify n=0, as this is always the case)
void plot_trajectory(double velocity){
	double maxTime = calculate_time(velocity);
	double windowHeight = calculate_height(velocity,maxTime/2)+30;
	double windowWidth = 100*maxTime;
	make_window(windowWidth, windowHeight);
	set_pen_width(5);
	plot_trajectory_interface(maxTime, velocity, 0, windowHeight, windowWidth);
}

//// HERE STARTS CANNON GAME ////

// DRAWS ENEMY BASE WINDOWS
void draw_windows(int x, int y, int w, int h, int stop){
	move_to(-1*w+x+10, y-h/2);
	set_heading_degrees(90);
	set_pen_width(10);
	if(get_x_position()<stop-15){
		draw_distance(10);
		draw_windows(x+40,y,w,h,stop);
	}
}

// DRAWS ENEMY BASE
void draw_base(double windowHeight,double x, double h,double w){
	move_to(x,windowHeight-h);
	set_heading_degrees(180);
	draw_distance(h);
	turn_right_by_degrees(90);
	draw_distance(w);
	turn_right_by_degrees(90);
	draw_distance(h);
	turn_right_by_degrees(90);
	draw_distance(w);
	set_pen_color(color::black);
	draw_windows(x,windowHeight,w,h,x);
}

// CHECKS FOR COLLISION WITH ENEMY BASE
bool checkCollision(double x, double y, double baseX, double baseH, double baseW){
	if(y>=baseH && x>=(baseX-baseW) && x<=baseX){
		return true;
	}
	else{
		return false;
	}
}

// DRAWS CANNONBALL TRAJECTORY
bool draw_trajectory(double xVelocity, double yVelocity, double startX, double startY, double windowHeight, double baseX, double baseH, double baseW, double n){
	double height = startY - calculate_height(yVelocity,n);
	double distance = startX + calculate_distance(xVelocity,n);
	if(checkCollision(distance,height,baseX,baseH,baseW)){
		cout << " YOU WIN!! THE WORLD HAS BEEN SAVED! " << endl;
		set_pen_color(color::green);
		move_to(400,50);
		write_string(" YOU WIN!! THE WORLD HAS BEEN SAVED!");
		return true;
	}
	if(height<700){
		draw_point(distance,height);
		if(int(n*100)%2 == 0) wait(0.01); // Real Time drawing (correction necessary because using wait(0.01) alone, the program takes approximately twice the expected time
		draw_trajectory(xVelocity, yVelocity, startX, startY, windowHeight, baseX, baseH, baseW, n+0.01);
	}
	else{
		cout << "Sarg, looks like our cannonball flew a sweet " << n << " seconds and covered a good " << calculate_distance(xVelocity, n) << " feet." << endl;
		cout << "...but we still missed the target though..." << endl;
		new_line();
		return false;
	}
}

// SETUP FOR PLOTTING
bool begin_simulation(double velocity, double angle, bool firstWindow, double baseX, double baseH, double baseW){

	double xVelocity = velocity * sin(angle);	
	double yVelocity = velocity * cos(angle);
	double maxTime = calculate_time(yVelocity);
	double maxDist = maxTime*xVelocity;
	double maxHeight = calculate_height(yVelocity, 0.5*maxTime);
	double windowHeight = 700;
	double windowWidth = maxDist;

		//Erase previous cannon
		set_pen_color(color::white);
		set_pen_width(260);
		move_to(2.0,windowHeight-12);
		draw_point();
		set_pen_width(6);

		// Start drawing cannon
		set_pen_color(color::black);
		move_to(2.0,windowHeight-20);
		set_heading_radians(angle);
		draw_distance(100);
		turn_right_by_degrees(90);
		draw_distance(15);

		// Get trajectory starting position
		double startX = get_x_position();
		double startY = get_y_position();

		// Finish drawing cannon
		draw_distance(15);
		turn_right_by_degrees(90);
		draw_distance(100);
		turn_right_by_degrees(90);
		draw_distance(30);
	

	set_pen_color(1,0,0);
	bool cont = draw_trajectory(xVelocity, yVelocity, startX, startY, windowHeight, baseX, baseH, baseW, 0);

	

	return cont;
}


// MULTIPLE ATTEMPTS
void again(int attempt, int baseX, int baseH, int baseW){
	if(attempt>0){
		cout << "Attempts remaining: " << attempt << endl;
		print("How much gunpowder d'ya want sarg? ");
		const double velocity = read_double();
		print("Roger 'at. Whattabout the cannon angle? ");
		const double angle = read_double()*3.1416/180.0;
		new_line();
		//print_trajectory(velocity);
		//plot_vertical(velocity);
		//plot_trajectory(velocity);

		if(!begin_simulation(velocity,angle,true,baseX,700 - baseH,baseW)){
			again(attempt-1, baseX, baseH, baseW);
		}
	}
	else{
		print(" GAME OVER ");
		set_pen_color(color::red);
		move_to(500,50);
		write_string("GAME OVER");
	}
}

// MAIN
void main(){
	// TO TEST PREVIOUS PARTS OF THE LAB

		//print_trajectory(100);
		//plot_vertical(100);
		//plot_trajectory(100);
	
	make_window(1200, 700);
	set_pen_width(6);
	int baseX = random_in_range(500,1000);
	int baseH = random_in_range(50,150);
	int baseW = random_in_range(75,200);
	draw_base(700,baseX,baseH,baseW);


	again(3, baseX, baseH, baseW);
}
