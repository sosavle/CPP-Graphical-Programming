#include "library.h"

struct Point{
	int x;
	int y;
};

struct Characters{
	Point robot;
};

struct Labrynth{
	char layout[10000];
	int rows;
	int cols;
	Point start;
	Point treasure;
};

void read_maze(ifstream &fin, Labrynth &maze, Characters &chars){
	string line;
	int row = 0;
	while(fin >> line){
		if(line.length() == 0) 
			break;
		maze.cols = line.length();
		for(int col=0; col<line.length(); ++col){
			maze.layout[col + line.length()*row] = line[col];
			if(line[col] == '+'){
				chars.robot.x = col;
				chars.robot.y = row;
			}
			//cout << maze.layout[col + line.length()*row];
		}
		++row;
		//cout << endl;
	}
	maze.rows = row;
}

void print_maze(Labrynth maze){
	for(int j=0; j<maze.rows; ++j){
		for(int i = 0; i<maze.cols; ++i){
			cout << maze.layout[i + maze.cols*j];
		}
		cout << "\n";
	} 
}

void draw_characters(int windowWidth, int windowHeight, Labrynth maze, Characters chars){
	set_pen_width(5);
	set_pen_color(color::blue);
	draw_point(windowWidth*chars.robot.x/maze.cols + 15,windowHeight*chars.robot.y/maze.rows + 15);
}

void draw_maze(int windowWidth, int windowHeight, Labrynth maze, Characters chars){
	//image* robot_icon = image_from_file("robot21.bmp");
	for(int i=0; i<(maze.cols); ++i){
		for(int j=0; j<(maze.rows); ++j){
			double x = windowWidth*i/maze.cols;
			double y = windowHeight*j/maze.rows;

			if(maze.layout[i + maze.cols*j] == 'X') set_pen_color(color::dark_grey);
			else if (maze.layout[i + maze.cols*j] == '-') set_pen_color(color::white);
			else if (maze.layout[i + maze.cols*j] == '$') set_pen_color(color::yellow);
			else if (maze.layout[i + maze.cols*j] == '+') set_pen_color(color::green);
			fill_rectangle(x,y,30.0,30.0,color::black);
			fill_rectangle(x+1,y+1,28.0,28.0);
		}
	}
	draw_characters(windowWidth, windowHeight, maze, chars);
}

bool validity_check(int windowWidth, int windowHeight,Labrynth maze, Characters &chars, int direction){
	//cout << maze.layout[chars.robot.x + chars.robot.y*maze.rows];
	if(chars.robot.x<0 || chars.robot.x>=maze.cols || chars.robot.y<0 || chars.robot.y>=maze.rows){
		return false;
	}
	else if(maze.layout[chars.robot.x + chars.robot.y*maze.cols] == 'X'){
		return false;
	}
	return true;

}

void moveChars(int windowWidth, int windowHeight, Labrynth maze, Characters &chars, int direction){
	//if(direction == -92) direction = -88;
	//else if(direction == -93) direction = -89;

	if(direction == -88) chars.robot.y += 1;
	else if(direction == -89) chars.robot.x += 1;
	else if(direction == -90) chars.robot.y -= 1;
	else if(direction == -91) chars.robot.x -= 1;

	if(validity_check(windowWidth, windowHeight, maze, chars, direction)){
		draw_maze(windowWidth,windowHeight,maze,chars);
		if(maze.layout[chars.robot.x + chars.robot.y*maze.cols] == '$'){
			move_to(windowWidth/2, 20);
			write_string("YOU WIN!",direction::center);
			wait(2);
			exit(0);
		}
	}
	else {
		if(direction == -88) chars.robot.y -= 1;
		else if(direction == -89) chars.robot.x -= 1;
		else if(direction == -90) chars.robot.y += 1;
		else if(direction == -91) chars.robot.x += 1;
	}
	//cout << chars.robot.x << " " << chars.robot.y << endl;
}

void main(){

	//Initialization
	Labrynth maze;
	Characters chars;
	ifstream fin;
	fin.open("treasure.txt");
	if(fin.fail()){
		cerr << "Error opening file"; 
		exit(1);
	}
	read_maze(fin,maze, chars);
	fin.close();
	//print_maze(maze);

	//Create Graphics
	const int windowWidth = 30*(maze.cols);
	const int windowHeight = 30*(maze.rows);
	make_window(windowWidth,windowHeight);
	fill_rectangle(0,0,windowWidth,windowHeight,color::black);
	draw_maze(windowWidth, windowHeight, maze, chars);

	//cout << maze.rows << " " << maze.cols << endl;
	
	//Interactive loop
	while(true){
		char input = wait_for_key_typed();
		if(input == 'q') {
			exit(0);
		}
		else if(input<=-88 && input>=-91){
			moveChars(windowWidth,windowHeight,maze,chars,input);
		}
	}
}
