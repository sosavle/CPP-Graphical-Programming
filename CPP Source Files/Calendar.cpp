// Luis Sosa Monday Lab 7

#include <iostream>
using namespace std;

int month_length(int year,int month){
	if(month>12 || month < 0){
		cout << "INVALID MONTH";
		exit(0);
	}
	if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12){
		return 31;
	}
	else if(month == 2){
		if(year%4){
			return 28;
		}
		else{
			return 29;
		}
	}
	else{
		return 30;
	}
}

int day_of_year(int year, int month, int day){
	int daySum = 0;
	for(int i = 1; i<month; i++){
		daySum += month_length(year,i);
	}
	return daySum + day;
}

int day_of_century(int year, int month, int day){
	int num_years = year - 2000;
	int leap = 0;
	for(int i = 0; i<num_years; i++){
		if(month_length(2000+i,2) == 29){
			leap++;
		}
	}
	return 365*(num_years-1) + leap + day_of_year(year, month, day);
}

int day_of_forever(int year, int month, int day){
	int leapCount = 0;

	for(int i = 0; i<year; i++){
		if(i%400 == 0){
			leapCount++;
		}
		else if((i%4 == 0) && (i%100!=0)){
			leapCount++;
		}
	}
	return 365*year + leapCount + day_of_year(year,month,day);
}

int determine_weekday(int year, int month, int day){
	return (day_of_forever(year, month, day)+ 5)%7 ;
}

void print_calendar(int year, int month){
	cout << " Su Mo Tu We Th Fr Sa" << endl;
	cout << " ";
	int todayWeekday = determine_weekday(year, month, 1);

	for(int i = 0; i<todayWeekday; i++){
		cout << " - ";
	}

	int numDays = month_length(year,month);
	for(int i = 1; i<=numDays; i++){
		if(i<10){
			cout << " ";
		}
		cout << i << " ";
		if(todayWeekday==6){
			cout << endl << " ";
		}
		todayWeekday = (todayWeekday + 1)%7;
	}
	if(todayWeekday > 0){
		for(int i = todayWeekday; i<7; i++){
			cout << " - ";
		}
	}
}

void main(){
	int a = month_length(2020,3);
	//cout << a;
	int b = day_of_year(2013,3,1);
	//cout << b;
	int c = day_of_century(2001,1,31);
	//cout << c;
	int d = day_of_forever(1776,7,4);
	//cout << d;
	int e = determine_weekday(2019, 3, 1);
	//cout << e;

	int year = 0;
	int month = 0;
	cout << "Please enter a year and month to view: ";
	cin >> year;
	cin >> month;
	cout << endl;

	print_calendar(year, month);
}
