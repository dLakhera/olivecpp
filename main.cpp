#include <iostream>
#include <fstream>
#include <cstdint>
#include <cstring>

#include "olive.cpp"

#define WIDTH 800
#define HEIGTH 600

#define ROWS 6
#define COLS 8

#define CELL_W (WIDTH/COLS)
#define CELL_H (HEIGTH/ROWS)

#define BACKGROUND_COLOR  0xFF0000FF
#define FOREGROUND_COLOR 0xFFFF0000

static uint32_t pixels[WIDTH * HEIGTH];


int checkboard_sample(){

	char* file_path = "samples/checker_sample.ppm";
	for(int y =0;y<ROWS;y++) {
		for(int x=0;x<COLS;x++) {
			uint32_t color = BACKGROUND_COLOR;
			if ((x+y) %2) {
				color = FOREGROUND_COLOR;
			}
			olivec_fill_rect(pixels, WIDTH, HEIGTH,  x*CELL_W, y*CELL_H, CELL_W, CELL_H, color);
		}
	}

	if (olivec_save_to_ppm_file_path(pixels, WIDTH, HEIGTH, file_path) == -1){
		std::cerr << "Failed to input data to file path given!" << std::endl;
		return -1;
	} 

	return 1;
}

float lerpf(float a, float b, float c){
	return a+(b-a)*c;
}

int circle_sample(){
	char* file_path = "samples/circle.ppm";

	olivec_fill(pixels, WIDTH, HEIGTH, BACKGROUND_COLOR);		
	olivec_fill_circle(pixels, WIDTH, HEIGTH, WIDTH/2, HEIGTH/2, 100, 0xFF00FF00);
	if (olivec_save_to_ppm_file_path(pixels, WIDTH, HEIGTH, file_path) == -1){
		std::cerr << "Failed to input data to file path given!" << std::endl;
	} 
	olivec_fill(pixels, WIDTH, HEIGTH, BACKGROUND_COLOR);
	
	uint32_t color = 0xFFFFFFFF;

	char* file_path = "samples/checker_circle.ppm";
	for(int y =0;y<ROWS;y++) {
		for(int x=0;x<COLS;x++) {
			float u = (float)x/COLS;
			float v = (float)y/ROWS;
			float t = (u+v)/2;
			float radius = CELL_W;
			olivec_fill_circle(pixels, WIDTH, HEIGTH,
					x*CELL_W + CELL_W/2, y*CELL_H + CELL_H/2, 
					(size_t) lerpf(radius/4, radius/2, t), 
					color);
		}
	}

	if (olivec_save_to_ppm_file_path(pixels, WIDTH, HEIGTH, file_path) == -1){
		std::cerr << "Failed to input data to file path given!" << std::endl;
		return -1;
	} 

	return 1;

}

int line_sample(){

	char* file_path = "samples/lines.ppm";

	olivec_fill(pixels, WIDTH, HEIGTH,0xFF000000);
	olivec_fill_line(pixels, WIDTH, HEIGTH, 100, 100, 700, 850, 0xFFFFFFFF);
	if (olivec_save_to_ppm_file_path(pixels, WIDTH, HEIGTH, file_path) == -1){
		std::cerr << "Failed to input data to file path given!" << std::endl;
	}

	
	char* file_path = "samples/checker_lines.ppm";
	
	olivec_fill(pixels, WIDTH, HEIGTH, 0xFFFFFFFF);

	for(int y =0;y<ROWS;y++) {
		for(int x=0;x<COLS;x++) {
			olivec_fill_line(pixels, WIDTH, HEIGTH, x*CELL_W, y*CELL_H, (x+1)*CELL_W, y*CELL_H, 0xFF000000);
			olivec_fill_line(pixels, WIDTH, HEIGTH, x*CELL_W, y*CELL_H, x*CELL_W, (y+1)*CELL_H, 0xFF000000);
		}
	}

	if (olivec_save_to_ppm_file_path(pixels, WIDTH, HEIGTH, file_path) == -1){
		std::cerr << "Failed to input data to file path given!" << std::endl;
		return -1;
	}

	return 1;
}


int main(){

	std::cout << CELL_W << " " << CELL_H << std::endl;

	checkboard_sample();
	circle_sample();
	line_sample();

	std::cout << "Deepak Lakhera|!" << std::endl;
	return 0;
}
