#include "library.h"

struct Weather{
	int year[1000], month[1000], day[1000];
	double minTemp[1000], avgTemp[1000], maxTemp[1000];
	double snow[1000];
	double precip[1000];
	double maxWind[1000];
};

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

void find_limits(double data[], double limits[], int size){
	double min = limits[0];
	double max = limits[1];
	for(int i=0; i<size; ++i){
		if(data[i] == -1) 
			continue;
		else if(data[i] < min)
			min = data[i];
		else if(data[i] > max)
			max = data[i];
	}
	limits[0] = min;
	limits[1] = max;
}

void round_limits(double &min, double &max, int n){
	if(min != 0) min = int(min/n - 1) * n;
	max = int(max/n + 1) * n;
}



int read_file(Weather &data){
	// Read File
	ifstream fin;
	string filename = open_file_pop_up("", "", "Please select weather data to read");
	fin.open(filename);
	//fin.open("BOSTON-MA.txt");
	//fin.open("HOPELESS-MO.txt");
	if(fin.fail()){
		cerr << "Error opening file"; 
		wait(1.5); 
		exit(1);
	}
	int size=0;
	while(fin >> data.year[size]){
		fin >> data.month[size] >> data.day[size] >> data.minTemp[size] >> data.avgTemp[size]
			>> data.maxTemp[size] >> data.snow[size] >> data.precip[size] >> data.maxWind[size];
		if(fin.fail()){
			cerr << "Error reading file (might be missing values?)"; 
			wait(2);
			exit(2);
		}
		++size;
	}
	fin.close();
	return size;
}

void draw_y_labels(int windowWidth, int windowHeight, int min, int max, double scalingFactor, int n){
	set_pen_color(color::light_grey);
	int j = 0;
	for(int i=min; i<=max; i+=n){
		double x = 50;
		double y = windowHeight-scalingFactor*n-scalingFactor*n*j;
		move_to(x-5,y);
		set_pen_color(color::dark_grey);
		write_string(i,direction::west);
		set_pen_color(color::light_grey);

		if(i==0 || i+n>max || i==min)
			fill_rectangle(x,y,windowWidth-x-50,2.0,color::dark_grey);
		else
			fill_rectangle(x+2,y,windowWidth-x-50-4,2.0,color::light_grey);
		++j;
	}

}

void draw_x_labels(Weather data, int windowHeight, int min, int max, int size, double scalingFactor, int n){
	
	char months[] = {'J','F','M','A','M','J','J','A','S','O','N','D',' '};
	int feb = month_length(data.year[0],2);
	int monthSize[] = {31, feb, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31, 31};
	int j = 0;
	for(int i=0; j<=12; i+= monthSize[j]){
		double x = 1.8*i+50;
		double y = windowHeight-n*scalingFactor-scalingFactor*abs(max-min);
		if(i==0 || j==12) set_pen_color(color::dark_grey);
		fill_rectangle(x,y,2.0,double(scalingFactor*abs(max-min)));
		move_to(x+15*1.8,windowHeight-n*scalingFactor+5.0);
		set_pen_color(color::dark_grey);
		write_string(months[j],direction::south);
		set_pen_color(color::light_grey);
		++j;
	}
}

void plot_weather_data(int year[], int month[], int day[], double series[], int windowHeight, int min, int size, double scalingFactor, int n, int userColor){
	set_pen_color(userColor);
	move_to(0*1.8+50,windowHeight-scalingFactor*series[0]-n*scalingFactor-scalingFactor*abs(min));
	int lastDay = 0;
	int j = 0;
	for(int i=day_of_year(year[0],month[0],day[0]); j<size; i=day_of_year(year[j],month[j],day[j])){
		cout << endl << series[j];
		if(series[j] != -1 && lastDay == i-1){draw_to(i*1.8+50,windowHeight-scalingFactor*series[j]-n*scalingFactor-scalingFactor*abs(min));}
		else if (j+1<size){
			move_to(i*1.8+50,windowHeight-scalingFactor*series[j+1]-n*scalingFactor-scalingFactor*abs(min));
		}
		++j;
		lastDay = i;
	}
} 

void main(){
	// Initialize data
	Weather data;
	double limits[2] = {0,0};
	int size = read_file(data);
	bool plotMinTemp = false;
	bool plotMaxTemp = false;
	bool plotAvgTemp = false;
	bool plotSnow = false;
	bool plotPrecip = false;
	bool plotWind = false;
	string series = "0";
	string userOrder[100];
	string currentColor = "0";
	int userColor[100];
	int s = 0;

	cout << "Enter what do you wish to plot, followed by a color\n" <<
			"MIN: minimum temperature,\nMAX: maximum temperature\n" <<
			"AVG: average temperature,\nSNOW: snowfall,\nWIND: windspeed\n" <<
			"RAIN: precipitation\nPLOT: generate plot\n" <<
			"Example: \"MIN BLUE AVG PURPLE MAX RED PLOT\"\n>> ";

	while(true){
		cin >> series;
		userOrder[s] = series;
		if(series == "EXIT") exit(0);
		else if(series == "MIN") {find_limits(data.minTemp,limits,size); plotMinTemp = true;}
		else if(series == "MAX") {find_limits(data.maxTemp,limits,size); plotMaxTemp = true;}
		else if(series == "AVG") {find_limits(data.avgTemp,limits,size); plotAvgTemp = true;}
		else if(series == "SNOW") {find_limits(data.snow,limits,size); plotSnow = true;}
		else if(series == "WIND") {find_limits(data.maxWind,limits,size); plotWind = true;}
		else if(series == "RAIN") {find_limits(data.precip,limits,size); plotPrecip = true;}
		else if(series == "PLOT") break;
		else cout << "\nInvalid Input\n\n";
		series = "0";

		cin >> currentColor;
		++s;
		if(currentColor == "RED") userColor[s] = color::dark_red;
		else if (currentColor == "ORANGE") userColor[s] = color::orange;
		else if (currentColor == "YELLOW") userColor[s] = color::yellow;
		else if (currentColor == "GREEN") userColor[s] = color::dark_green;
		else if (currentColor == "BLUE") userColor[s] = color::blue;
		else if (currentColor == "PURPLE") userColor[s] = color::violet;
		else if (currentColor == "BLACK") userColor[s] = color::black;
		else{
		   cout << "Invalid Color. Only primary and secondary colors, as well as black, are available\n";
		   --s;
		}
	}

	// Autoscaling
	double min = limits[0]; 
	double max = limits[1];
	int range = max-min;
	int n = 1;
	
	if(range>=300) n = 100;
	else if (range >=150) n = 20;
	else if (range >= 50) n = 10;
	else if (range >= 20) n = 5;
	else if (range >= 10) n = 2;
	

	round_limits(min,max,n);

	double scalingFactor = 5;
	if (range>200) scalingFactor = 0.5;
	else if(range>150) scalingFactor = 5;
	else if(range>70) scalingFactor = 8;
				
	// Create graphing window
	const int windowWidth = 365*1.8 + 2*50;
	const int windowHeight = scalingFactor*(max-min)+ 2*n*scalingFactor;
	make_window(windowWidth, windowHeight);
	set_pen_width(3);
	
	//Labels
	draw_x_labels(data, windowHeight, min, max, size, scalingFactor, n);
	draw_y_labels(windowWidth, windowHeight, min, max, scalingFactor, n);


	// Graph
	//fill_rectangle(0,0,100,100,userColor[s+1]);
	while(s>0){
		if(plotMinTemp && userOrder[s-1] == "MIN") plot_weather_data(data.year, data.month, data.day, data.minTemp, windowHeight, min, size, scalingFactor,n, userColor[s]);
		if(plotMaxTemp && userOrder[s-1] == "MAX") plot_weather_data(data.year, data.month, data.day, data.maxTemp, windowHeight, min, size, scalingFactor,n, userColor[s]);
		if(plotAvgTemp && userOrder[s-1] == "AVG") plot_weather_data(data.year, data.month, data.day, data.avgTemp, windowHeight, min, size, scalingFactor,n, userColor[s]);
		if(plotSnow && userOrder[s-1] == "SNOW") plot_weather_data(data.year, data.month, data.day, data.snow, windowHeight, min, size, scalingFactor,n, userColor[s]);
		if(plotWind && userOrder[s-1] == "WIND") plot_weather_data(data.year, data.month, data.day, data.maxWind, windowHeight, min, size, scalingFactor,n, userColor[s]);
		if(plotPrecip && userOrder[s-1] == "RAIN") plot_weather_data(data.year, data.month, data.day, data.precip, windowHeight, min, size, scalingFactor,n, userColor[s]);
		--s;
	}
}
