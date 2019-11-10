#include "library.h"
using namespace std;

void print_time(){
	int date = get_calendar_date();
	int year = date/10000;
	int month = (date%10000)/100;
	int day = date%100;

	int time  = get_clock_time();
	int hour = (time/10000) % 12;
	int minute = (time%10000)/100;
	//int second = time%100;

	print("  year: ");  print(year);   new_line();
	print(" month: ");  print(month);  new_line();
	print("   day: ");  print(day);    new_line();
	print("  hour: ");  print(hour);   new_line();
	print("minute: ");  print(minute); new_line();
}

void print_monroe_time(){
	int date = get_calendar_date();
	int year = date/10000;
	int month = (date%10000)/100;
	int day = date%100;

	int time  = get_clock_time();
	int hour = (time/10000);
	int minute = (time%10000)/100;
	//int second = time%100;

	// DATE
	cout << " date: " << year << "-";
	if(month<10){
		cout << "0";
	}
	cout << month << "-";
	if(day<10){
		cout << "0";
	}
	cout << day << endl;

	/// HOURS (Replacing 0 with 12)
	cout << " time: ";
	if(hour%12 == 0){
		cout << "12";
	}
	else{
		cout << hour%12;
	}
	cout << ":";

	/// MINUTES
	if(minute<10){
		cout << "0";
	}
	cout << minute;

	if(hour<12){
		cout << " a.m.";
	}
	else{
		cout << " p.m.";
	}

}

void draw_circle(int x, int y, int r, int n){
	if(n<=0){
		move_to(x,y-r);
	}
	if(n<360){
		draw_distance(2*3.1416*r/360);
		turn_right_by_degrees(1);
		draw_circle(x,y,r,n+1);
	}
}

void draw_ticks(int x, int y, int r, int n){
	if(n<=0){
		set_pen_width(2);
	}
	if(n<360){
		move_to(x,y);
		move_distance(3*r/4.0);
		draw_distance(r/4.0-10);
		turn_right_by_degrees(30);
		draw_ticks(x,y,r,n+30);
	}
}

int get_year(){
	int year = get_calendar_date()/10000;
	return year;
}

int get_day(){
	int day = get_calendar_date()%100;
	return day;
}

int get_month(){
	int month = (get_calendar_date()%10000)/100;
	return month;
}

int get_hour(){
	int hour = (get_clock_time()/10000);
	return hour%12;
}

string get_monroe(){
	int hour = (get_clock_time()/10000);
	if(hour<12)
		return "a.m.";
	else
		return"p.m.";
}

int get_minute(){
	int minute = (get_clock_time()%10000)/100;
	return minute;
}

int get_second(){
	int second = get_clock_time()%100;
	return second;
}

void draw_hour_hand(int x, int y, int r){
	double angle = get_hour()*30 + 30*get_minute()/60.0;
	set_pen_width(6);

	move_to(x,y);
	set_pen_color(color::white);
	set_heading_degrees(angle-0.5);
	draw_distance(r-85);

	move_to(x,y);
	set_pen_color(color::black);
	set_heading_degrees(angle);
	draw_distance(r-85);
}

void draw_minute_hand(int x, int y, int r, int n){
	int angle = 6*get_minute();
	set_pen_width(3);

	if(!n && 6*get_second() != angle-6){
	move_to(x,y);
	set_pen_color(color::white);
	set_heading_degrees(angle-6);
	draw_distance(r-60);
	}

	move_to(x,y);
	set_pen_color(color::black);
	set_pen_width(3);
	set_heading_degrees(angle);
	draw_distance(r-60);
}

void draw_second_hand(int x, int y, int r, int n){
	int angle = 6*get_second();
	set_pen_width(2);
	
	if(!n){
		move_to(x,y);
		set_pen_color(color::white);
		set_heading_degrees(angle-6);
		draw_distance(r-50);
	}

		move_to(x,y);
		set_pen_color(color::black);
		set_heading_degrees(angle);
		draw_distance(r-50);

}

string stringify_month(int month){
	if(month == 1)
		return "January";
	else if(month == 2)
		return "February";
	else if(month == 3)
		return "March";
	else if(month == 4)
		return "April";
	else if(month == 5)
		return "May";
	else if(month == 6)
		return "June";
	else if(month == 7)
		return "July";
	else if(month == 8)
		return "August";
	else if(month == 9)
		return "September";
	else if(month == 10)
		return "October";
	else if(month == 11)
		return "November";
	else if(month == 12)
		return "December";
	else
		return "Freaky error OwO";
}

string append_suffix(int day){
	if(day==1 || day==21 || day == 31)
		return "st";
	else if(day==2 || day==22)
		return "nd";
	else if(day==3 || day==23)
		return "rd";
	else
		return "th";

}

void draw_time(int j){
	
	set_pen_color(color::black);

	move_to(60,60);
	set_font_size(50);
	int month = get_month();
	string month_name = stringify_month(month);
	write_string(month_name);
	write_string(" ");
	int day = get_day();
	write_int(day);
	string suffix = append_suffix(day);
	write_string(suffix);
	write_string(" ");
	write_int(get_year());

	move_to(120,460);
	write_int(get_hour());
	write_string(":");
	int minute = get_minute();
	if(minute<10)
		write_string("0");
	write_int(minute);
	write_string(" ");
	write_string(get_monroe());


	if(!j){
		set_pen_color(color::white);
		fill_rectangle(60,10,300,60);
		fill_rectangle(120,430,300,100);
	}

	set_pen_color(color::black);
	move_to(60,60);
	set_font_size(50);
	month_name = stringify_month(month);
	write_string(month_name);
	write_string(" ");
	write_int(day);
	suffix = append_suffix(day);
	write_string(suffix);
	write_string(" ");
	write_int(get_year());

	move_to(120,460);
	write_int(get_hour());
	write_string(":");
	if(minute<10)
		write_string("0");
	write_int(minute);
	write_string(" ");
	write_string(get_monroe());
}

void draw_clock(int n, int j){ 
// n controls animation update speed for clock hands, j for the strings
	set_pen_color(color::black);
	set_heading_degrees(90);
	draw_circle(200, 250, 150, 0);
	draw_ticks(200, 250, 150, 0);
	draw_second_hand(200,250,150,n);

	// Note, animation is controled by only updating at some frames. 
	// if(!n) is shorthand for if(n==0). 
	// n is a variable between 0 and 1, j is a variable between 0 and 9.
		if(!n){
			draw_minute_hand(200,250,150,n);
			draw_hour_hand(200,250,150);
		}
	draw_time(j);
	draw_clock((n+1)%2,(j+1)%10);
}

void main(){
	//print_time();
	print_monroe_time();
	make_window(400,500);
	set_pen_width(3);
	draw_clock(0,0);
}
