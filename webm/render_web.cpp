
#include "../olive.cpp"

#define WIDTH 800
#define HEIGTH 600

#define ROWS 6
#define COLS 8

#define PI 3.14159265359

#define CELL_W (WIDTH/COLS)
#define CELL_H (HEIGTH/ROWS)

#define BACKGROUND_COLOR  0xFF000000
#define FOREGROUND_COLOR 0xFFFFFFFF

#define RENDER_EXPORT __attribute__((export_name("render")))
#define export __attribute__((visibility("default")))

static uint32_t pixels[WIDTH * HEIGTH];

float __builtin_atan2f(float y, float x);
float __builtin_sqrtf(float x);
float __builtin_sinf(float x);
float __builtin_cosf(float x);

float angle = 0.0f;

void rotate_point(uint32_t *x, uint32_t *y) {
	uint32_t cx = *x - WIDTH/2;
	uint32_t cy = *y - HEIGTH/2;
	
	float mag = __builtin_sqrtf(cx*cx + cy*cy);
	float dir = __builtin_atan2f(cx,cy) + angle;

	*x = __builtin_cosf(dir) * mag + WIDTH/2;
	*y = __builtin_sinf(dir) * mag + HEIGTH/2;
}

extern "C" RENDER_EXPORT uint32_t* render(float dt)
{

	angle += 0.5*PI*dt;

	olivec_fill(pixels, WIDTH, HEIGTH, BACKGROUND_COLOR);
	
	uint32_t x1,x2,x3,y1,y2,y3;

	// x1 = 10, x2 = 400, x3 = 700;
	// y1 = 250, y2 = 50, y3 = 500;

	x1 = WIDTH/2, y1 =  HEIGTH/8;
	x2 = WIDTH/8, y2 =  HEIGTH/2;
	x3 = WIDTH*7/8, y3 =  HEIGTH*7/8;

	rotate_point(&x1, &y1);
	rotate_point(&x2, &y2);
	rotate_point(&x3, &y3);

	olivec_fill_triangle_vector(
		pixels, WIDTH, HEIGTH, 
		x1, y1,
		x2, y2,
		x3, y3,
		0xFF0000FF
	);

	return pixels;

}
