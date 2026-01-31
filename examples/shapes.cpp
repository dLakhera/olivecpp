#include "../olive.cpp"


#define WIDTH 800
#define HEIGTH 600

#define ROWS 6
#define COLS 8

#define CELL_W (WIDTH/COLS)
#define CELL_H (HEIGTH/ROWS)

#define BACKGROUND_COLOR  0xFF000000
#define FOREGROUND_COLOR 0xFFFFFFFF

static uint32_t pixels[WIDTH * HEIGTH];

int checkboard_sample(){

	const char* file_path = "samples/checker_sample.ppm";
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

int circle_sample(){
	const char* file_path = "samples/circle.ppm";

	olivec_fill(pixels, WIDTH, HEIGTH, BACKGROUND_COLOR);		
	olivec_fill_circle(pixels, WIDTH, HEIGTH, WIDTH/2, HEIGTH/2, 100,FOREGROUND_COLOR);
	if (olivec_save_to_ppm_file_path(pixels, WIDTH, HEIGTH, file_path) == -1){
		std::cerr << "Failed to input data to file path given!" << std::endl;
	} 
	olivec_fill(pixels, WIDTH, HEIGTH, BACKGROUND_COLOR);
	
	uint32_t color = 0xFFFFFFFF;

	file_path = "samples/checker_circle.ppm";
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

	const char* file_path = "samples/lines.ppm";

	olivec_fill(pixels, WIDTH, HEIGTH,BACKGROUND_COLOR);
	olivec_fill_line(pixels, WIDTH, HEIGTH, 0,			0,			WIDTH/4,	HEIGTH,		FOREGROUND_COLOR);
	olivec_fill_line(pixels, WIDTH, HEIGTH, WIDTH/4,	0,			0,			HEIGTH,		FOREGROUND_COLOR);
	olivec_fill_line(pixels, WIDTH, HEIGTH, 3*WIDTH/4,	0,			WIDTH,		HEIGTH,		FOREGROUND_COLOR);
	olivec_fill_line(pixels, WIDTH, HEIGTH, WIDTH/4,	HEIGTH,		0,			0,			FOREGROUND_COLOR);
	olivec_fill_line(pixels, WIDTH, HEIGTH, 3*WIDTH/4,	HEIGTH,		WIDTH,		0,			FOREGROUND_COLOR);
	olivec_fill_line(pixels, WIDTH, HEIGTH, WIDTH/2,	HEIGTH,		WIDTH/2,	0,			0xFF20CC20);
	olivec_fill_line(pixels, WIDTH, HEIGTH, WIDTH,		HEIGTH/2,	0,			HEIGTH/2,	0xFFCC0220);
	
	olivec_fill_line(pixels, WIDTH, HEIGTH, 0,			HEIGTH/2,	WIDTH,		0,			0xFF00CCFF);
	olivec_fill_line(pixels, WIDTH, HEIGTH, 0,			HEIGTH/2,	WIDTH,		HEIGTH,		0xFF00CCFF);
	
	if (olivec_save_to_ppm_file_path(pixels, WIDTH, HEIGTH, file_path) == -1){
		std::cerr << "Failed to input data to file path given!" << std::endl;
	}

	
	file_path = "samples/checker_lines.ppm";
	
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

int triangles_sample()
{
	const char* file_path = "samples/triangle.ppm";
	olivec_fill(pixels, WIDTH, HEIGTH, BACKGROUND_COLOR);

	int x1,x2,x3,y1,y2,y3;

	x1 = 10, x2 = 200, x3 = 500;
	y1 = 10, y2 = 10, y3 = 300;

	olivec_fill_triangle_vector(
		pixels, WIDTH, HEIGTH, 
		x1, y1,
		x2, y2,
		x3, y3,
		0xff2ee90e	
	);

	x1 = 400, x2 = 700, x3 = 50;
	y1 = 40, y2 = 250, y3 = 550;
	olivec_fill_triangle_vector(
		pixels, WIDTH, HEIGTH, 
		x1, y1,
		x2, y2,
		x3, y3,
		0xffe98a4a	
	);

	x1 = 110, x2 = 500, x3 = 780;
	y1 = 50, y2 = 50, y3 = 240;
	olivec_fill_triangle_vector(
		pixels, WIDTH, HEIGTH, 
		x1, y1,
		x2, y2,
		x3, y3,
		0xff1783b1	
	);


	if (olivec_save_to_ppm_file_path(pixels, WIDTH, HEIGTH, file_path) == -1){
		std::cerr << "Failed to input data to file path given!" << std::endl;
		return -1;
	}

	file_path = "samples/checker_triagles.ppm";

	olivec_fill(pixels, WIDTH, HEIGTH, BACKGROUND_COLOR);
	for(int y =0;y<ROWS;y++) {
		for(int x=0;x<COLS;x++) {
			olivec_fill_circle(
				pixels, WIDTH, HEIGTH,
				x*CELL_W, y*CELL_H,
				5,
				0xFFFF0000
			);
		}
	}

	for(int y =0;y<ROWS;y++) {
		for(int x=0;x<COLS;x++) {

			olivec_fill_triangle_vector(
				pixels, WIDTH, HEIGTH,
				x*CELL_W, y*CELL_H,
				(x+1)*CELL_W, y*CELL_H,
				x*CELL_W, (y+1)*CELL_H,
				0xFF20BB20
			);
		}
	}

	if (olivec_save_to_ppm_file_path(pixels, WIDTH, HEIGTH, file_path) == -1){
		std::cerr << "Failed to input data to file path given!" << std::endl;
		return -1;
	}

	return 1;
}


