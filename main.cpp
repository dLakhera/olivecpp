#include <iostream>
#include <fstream>
#include <cstdint>
#include <cstring>

#include "olive.cpp"

#define HEIGTH 600
#define WIDTH 800

#define ROWS 6
#define COLS 8
#define CELL_W (WIDTH/COLS)
#define CELL_H (HEIGTH/ROWS)

#define BACKGROUND_COLOR  0xFF0000FF


static uint32_t pixels[HEIGTH * WIDTH];


int checkboard_sample(){

	char* file_path = "samples/checker_sample.ppm";
	for(int y =0;y<ROWS;y++) {
		for(int x=0;x<COLS;x++) {
			uint32_t color = BACKGROUND_COLOR;
			if ((x+y) %2) {
				color = 0xFF00FF00;
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


void circle_sample(){
	char* file_path = "samples/circle.ppm";

	olivec_fill(pixels, WIDTH, HEIGTH, BACKGROUND_COLOR);		
	olivec_fill_circle(pixels, WIDTH, HEIGTH, WIDTH/2, HEIGTH/2, 100, 0xFF00FF00);
	if (olivec_save_to_ppm_file_path(pixels, WIDTH, HEIGTH, file_path) == -1){
		std::cerr << "Failed to input data to file path given!" << std::endl;
	} 
}

int main(){

	checkboard_sample();
	circle_sample();

	std::cout << "Deepak Lakhera|!" << std::endl;
	return 0;
}
