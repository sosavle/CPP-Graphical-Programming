#include "library.h"

void toggle_power(bool &power){
	int windowWidth = get_window_width();
	int windowHeight = get_window_height();
	const int xDrawSpace = windowWidth/6;
	const int yDrawSpace = windowHeight/6;

	if(power){ // ON
		fill_rectangle(xDrawSpace-25-40-20-2,20-2,5*xDrawSpace+40+20+4, yDrawSpace+4, color::black);
		fill_rectangle(xDrawSpace-25-40-20,20,5*xDrawSpace+40+20, yDrawSpace, color::dark_blue);
	}
	else{ // OFF
		fill_rectangle(xDrawSpace-25-40-20-2,20-2,5*xDrawSpace+40+20+4, yDrawSpace+4, color::black);
		fill_rectangle(xDrawSpace-25-40-20,20,5*xDrawSpace+40+20, yDrawSpace, color::cyan);
	}
	power = !power; //Toggle
}

void refresh_screen(bool &power, double &current, int &digitPosition){
	power = !power; 
	toggle_power(power); //Refresh screen by turning display on and off without clearing calculator data
	if(digitPosition<6){
		move_to(540, 65);
		move_relative(-30*digitPosition,0);
	}
	else if(digitPosition == 6){ //If the number has an e in it
		move_to(540, 65);
		move_relative(-30*9,0);
	}
	write_string(current,direction::center, false);
	
	cout << current << endl;
}

void draw_button(int x,int y, int symbol, int buttonColor, int textColor){
	set_pen_color(color::black);
	set_pen_width(88);
	draw_point(x,y);
	set_pen_color(buttonColor);
	set_pen_width(85);
	draw_point(x,y);
	set_pen_color(textColor);
	set_font_size(65);
	write_char(symbol, direction::center);
	set_pen_color(color::black);
}

bool clicked_in_button(int c){
	if(c>14737632) //Color of pixel clicked has to be grey or black.
		return false;
	else
		return true;
}

void input_digit(int digit, double &current, bool power, int &digitPosition){
	if(digit!=0 || digitPosition !=0){
		if(current>=0) current = current*10 + digit;
		else current = current*10 - digit;
		refresh_screen(power, current, digitPosition);
		++digitPosition;
	}
}

void clear(double &current, double &ans, char &pending, bool &power, int &digitPosition){
	current = 0;
	ans = 0;
	pending = '0';
	digitPosition = 0;
	cout << "CLEAR\n";
	move_to(540, 60);
	refresh_screen(power, current, digitPosition);
}

int determine_digit_position(double ans){
	int digitPosition = 0;
	if(fmod(ans,1) == 0){
		while(abs(ans)/10>=1 && digitPosition<6){
			++digitPosition;
			ans = ans/10;
		}
	}
	else digitPosition = 5;
	return digitPosition;
}

void operate(double &current, double &ans, char &pending, char operation, int &digitPosition, bool &power){
	if(pending == '0') ans = current;
	
	if(operation == 'n'){ //Unary operator has special conditions, as it works with current and not ans
		cout << "ANS :" << ans << endl;
		current *= -1;
		refresh_screen(power, current, digitPosition);
		cout << "current: " << current << endl;
		return;
	}

	else if(pending == '+') ans += current;
	else if(pending == '-') ans -= current;
	else if(pending == '*') ans *= current;
	else if(pending == '/') ans /= current;
	else if(pending == '%') ans = fmod(ans,current);
	else if(pending == '^') ans = pow(ans,current);

	digitPosition = determine_digit_position(ans);
	refresh_screen(power, ans, digitPosition);
	digitPosition = 0;
	current = 0;
	cout << "ans: " << ans << endl;
	pending = operation;	
}

void equals(double &current, double &ans, char &pending, int &digitPosition, bool &power){
	if(pending == '+') operate(current, ans, pending, '+',digitPosition, power);
	else if(pending == '-') operate(current, ans, pending, '-',digitPosition, power);
	else if(pending == '*') operate(current, ans, pending, '*',digitPosition, power);
	else if(pending == '/') operate(current, ans, pending, '/',digitPosition, power);
	else if(pending == '%') operate(current, ans, pending, '%',digitPosition, power);
	else if(pending == '^') operate(current, ans, pending, '^',digitPosition, power);
	else if(pending == '0') ans = current; 
	digitPosition = determine_digit_position(ans);
	refresh_screen(power,ans,digitPosition);
	pending = '0';
	current = ans;
}

void button_interface(int row, int col, double &current, double &ans, char &pending, bool &power, int &digitPosition){
	if (row == 0 && col == 4){
		clear(current, ans, pending, power, digitPosition);
		toggle_power(power);
		if(power) refresh_screen(power,current, digitPosition);
	}

	if(power){
		if (row == 0 && col == 1) input_digit(8, current, power, digitPosition);
		else if (row == 0 && col == 2) input_digit(9, current, power, digitPosition);
		else if (row == 0 && col == 3) operate(current, ans, pending, '+',digitPosition, power);
		else if(row == 0 && col == 0) input_digit(7, current, power, digitPosition);
	
		else if (row == 1 && col == 0) input_digit(4, current, power, digitPosition);
		else if (row == 1 && col == 1) input_digit(5, current,power, digitPosition);
		else if (row == 1 && col == 2) input_digit(6, current,power, digitPosition);
		else if (row == 1 && col == 3) operate(current, ans, pending, '-',digitPosition, power);
		else if (row == 1 && col == 4) operate(current, ans, pending, '^',digitPosition, power);

		else if (row == 2 && col == 0) input_digit(1, current, power, digitPosition);
		else if (row == 2 && col == 1) input_digit(2, current, power, digitPosition);
		else if (row == 2 && col == 2) input_digit(3, current, power, digitPosition);
		else if (row == 2 && col == 3) operate(current, ans, pending, '*',digitPosition, power);
		else if (row == 2 && col == 4) operate(current, ans, pending, 'n',digitPosition, power);

		else if (row == 3 && col == 0) clear(current, ans, pending, power, digitPosition);
		else if (row == 3 && col == 1) input_digit(0, current,power, digitPosition);
		else if (row == 3 && col == 2) equals(current, ans, pending,digitPosition, power);
		else if (row == 3 && col == 3) operate(current, ans, pending, '/',digitPosition, power);
		else if (row == 3 && col == 4) operate(current, ans, pending, '%',digitPosition, power);
	}
}

void push_button(int row, int col, int xDrawSpace, int yDrawSpace){
	const int x = get_x_position();
	const int y = get_y_position();
	const int symbols[20] = {'7','4','1','C','8','5','2','0','9','6','3','=','+','-',L'×',L'÷',L'\u263C',L'\u2191',177,37};
	set_font_style(style::bold);
	draw_button(xDrawSpace+row*(xDrawSpace+10)-25,yDrawSpace+85+col*(yDrawSpace+10),symbols[4*row+col], color::dark_grey,color::white);
	wait(0.08);
	set_font_style();
	draw_button(xDrawSpace+row*(xDrawSpace+10)-25,yDrawSpace+85+col*(yDrawSpace+10),symbols[4*row+col], color::light_grey,color::black);
	set_font_style(style::italic + style::bold);
	move_to(x,y);
}

void interactive_loop(double xDrawSpace,double yDrawSpace, bool &power){
	double ans = 0;
	double current = 0;
	char pending = '0';
	int digitPosition = 0;
	refresh_screen(power,current,digitPosition);
	while(true){
		int row = -1;
		int col = -1;
		wait_for_mouse_click();
		int x = get_click_x(); 
		int y = get_click_y();
		int c = get_pixel_color(x,y);
		
		if(clicked_in_button(c)){
			
			if (y < yDrawSpace+40) ;
			else if(y < yDrawSpace+85+44) row = 0;
			else if(y < yDrawSpace+85+44+yDrawSpace+10) row = 1;
			else if(y < yDrawSpace+85+44+2*(yDrawSpace+10))row = 2;
			else row = 3;			

			if(x < xDrawSpace-25+44) col = 0;
			else if(x < xDrawSpace-25+44+xDrawSpace+10) col = 1;
			else if(x < xDrawSpace-25+44+2*(xDrawSpace+10)) col = 2;
			else if(x < xDrawSpace-25+44+3*(xDrawSpace+10)) col = 3;
			else col = 4;

			if(row != -1){
				push_button(col,row, xDrawSpace, yDrawSpace);
				button_interface(row, col, current, ans, pending, power, digitPosition);
			}
		}	 
	}
}


void draw_button_set(int windowWidth, int windowHeight){
	const int symbols[20] = {'7','4','1','C','8','5','2','0','9','6','3','=','+','-',L'×',L'÷',L'\u263C',L'\u2191',177,37};
	int symbolPointer = 0;
	const int xDrawSpace = windowWidth/6;
	const int yDrawSpace = windowHeight/6;
	for(int i = xDrawSpace-25; i<=5*(xDrawSpace+10); i += xDrawSpace+10){
		for(int j = yDrawSpace+85; j<=4*(yDrawSpace+40); j += yDrawSpace+10){
			draw_button(i, j, symbols[symbolPointer],color::light_grey,color::black);
			symbolPointer++;
		}
	}
	bool power = false;
	toggle_power(power);
	set_font_style(style::italic + style::bold);
	interactive_loop(xDrawSpace,yDrawSpace,power);
}

void main(){
	const int windowWidth = 650;
	const int windowHeight = 600;
	make_window(windowWidth, windowHeight);
	set_font("Times New Roman");
	fill_rectangle(0,0,windowWidth, windowHeight,color::light_blue);
	draw_button_set(windowWidth, windowHeight);
}
