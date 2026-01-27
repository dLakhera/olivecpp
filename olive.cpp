#ifndef OLIVE_C_
#define OLIVE_C_

#define return_defer(value) do {result = value; goto defer;} while(0)

#define SWAP(a, b) do { \
    auto _tmp = (a);   \
    (a) = (b);         \
    (b) = _tmp;        \
} while (0)

float lerpf(float a, float b, float c){
	return a+(b-a)*c;
}

void sort_triangle_points_by_y(
	int *x1, int *y1,
	int *x2, int *y2,
	int *x3, int *y3 
)
{

	if(*y1 > *y2) {
		SWAP(*y1,*y2);
		SWAP(*x1, *x2);
	}
	if(*y2 > *y3) {
		SWAP(*y3,*y2);
		SWAP(*x3, *x2);
	}
	if(*y1 > *y2) {
		SWAP(*y1,*y2);
		SWAP(*x1, *x2);
	}

}

struct Vector2D{
	int x,y;

	Vector2D(int x, int y) : x(x), y(y) {}
	
	float cross(const Vector2D *v) const {
		// return std::sqrt(this->dot(this)*v->dot(v) - this->dot(v)*this->dot(v));
		return x*v->y - y*v->x;
	}
};

void olivec_fill_triangle_vector(
	uint32_t *pixels, size_t pixels_w, size_t pixels_h, 
	int x1, int y1,
	int x2, int y2,
	int x3, int y3,
	uint32_t color)
{

	int minb_x = std::min(x1, std::min(x2,x3));
	int minb_y = std::min(y1, std::min(y2,y3));
	int maxb_x = std::max(x1, std::max(x2,x3));
	int maxb_y = std::max(y1, std::max(y2,y3));

	if (( x1 == x2 and x2 == x3) or (y1 == y2 and y2==y3))
	{
		return;
	}

	Vector2D ba = Vector2D(x2-x1, y2-y1);
	Vector2D bc = Vector2D(x2-x3, y2-y3);
	Vector2D ca = Vector2D(x3-x1, y3-y1);
	
	float area = ba.cross(&ca);

	for ( int x = minb_x; x < maxb_x; x++) {
		if(x>=0 and x < (int)pixels_w)
		{
			for( int y = minb_y; y < maxb_y; y++) {
				if(y >=0 and y < (int) pixels_h) {

					Vector2D pc = Vector2D(x-x3, y-y3);
					
					float a = pc.cross(&bc)/area;
					float b = pc.cross(&ca)/area;
					float c = 1 - a - b;

					if(a >=0.0f and b>=0.0f and c>=0.0f) {
						pixels[y*pixels_w + x] = color;
					}

				}
			}
		}
	}
}


bool olivec_line_segment_params(
	int x1, int y1,
	int x2, int y2,
	float *m, float *c
)
{
	int dx = x2-x1;
	int dy = y2-y1;

	if(dx == 0) return false;

	*m = dy/dx;
	*c = y1 - (*m)*x1;

	return true;
}

void olivec_fill(uint32_t *pixels, size_t width, size_t height, uint32_t color)
{

	for(size_t i=0;i<width*height;i++) {
		pixels[i] = color;
	}
}

void olivec_fill_circle(uint32_t* pixels, size_t pixels_w, size_t pixels_h, int x0, int y0, size_t radius, uint32_t color)
{

	// First implemenetation
	// for(int dy = (-1)*(int)radius; dy < (int)radius; dy++)
	// {
	// 	int y = y0+dy;
	// 	if(y<(int)pixels_h and y>=0) {
	// 		for(int dx = (-1)*(int)radius; dx < (int)radius; dx++) {
	// 			int x = x0+dx;
	// 			if(x>=0 and x<(+int)pixels_w) {
	// 				float distance = dx*dx + dy*dy;
	// 				if (distance <= radius*radius) {
	// 					pixels[y*pixels_h + x] = color;
	// 					// pixels[]
	// 				}
	// 			}
	// 		}
	// 	}
	// }


	// optimised!
	for(int dy = (-1)*(int)radius; dy <= 0; dy++)
	{
		for(int dx = (-1)*(int)radius; dx <= 0; dx++) {
			float distance = dx*dx + dy*dy;
			if (distance <= radius*radius) {
				int x = x0+dx, y = y0+dy;
				int x1 = x - 2*dx, y1 = y;
				int x2 = x - 2*dx, y2 = y - 2*dy;
				int x3 = x, y3 = y - 2*dy;
				if(x>=0 and x<(int)pixels_w and y >=0 and y < (int)pixels_h) {
					pixels[y*pixels_w + x] = color;
				}

				if(x1>=0 and x1<(int)pixels_w and y1 >=0 and y1 < (int)pixels_h) {
					pixels[y1*pixels_w + x1] = color;
				}

				if(x2>=0 and x2<(int)pixels_w and y2 >=0 and y2 < (int)pixels_h) {
					pixels[y2*pixels_w + x2] = color;
				}

				if(x3>=0 and x3<(int)pixels_w and y3 >=0 and y3 < (int)pixels_h) {
					pixels[y3*pixels_w + x3] = color;
				}

			}	
		
		}
	}
}


void olivec_fill_line(uint32_t* pixels, size_t pixels_w, size_t pixels_h, 
		int x1, int y1, int x2, int y2, 
		uint32_t color)
{

	float slope, intercept;

	if (x1-x2 != 0) {
		slope = (float)(y2-y1)/(float)(x2-x1);
		intercept = (-1.0f)*slope*x1 + y1;
		
		if (x1 >x2) 
			SWAP(x1, x2);

		for(int x = x1; x<=x2; x++) {
			if(x>=0 and x<pixels_w ){
				int sy1 = slope*x + intercept;
				int sy2 = slope*(x+1) + intercept;
				
				if(sy1 > sy2) SWAP(sy1, sy2);

				for(int y = sy1;y<=sy2;y++){
					if(y >=0 and y<pixels_h) {
						pixels[y*pixels_w + x] = color;
					}
				}
			}
		}

	}
	else {
		if (x1 >=0 and x1<pixels_w){

			if (y1 >y2) 
				SWAP(y1, y2);


			for(int y = y1;y<y2;y++) {
				if ( y>=0 and y< pixels_h){
					pixels[y*pixels_w + x1] = color;
				}
			}
		}
		return ;

	}

}

void olivec_fill_rect(
		uint32_t *pixels, size_t pixels_w, size_t pixels_h, 
		int x0, int y0, size_t w, size_t h,
		uint32_t color)
{

	for(int dy= 0; dy < h; dy++) {
		int y = dy+y0;
		if (y <= pixels_h and y >=0 ) {
			for(int dx = 0;dx < w;dx++) {
				int x = x0 + dx;
				if(x>=0 and x<=pixels_w) {
					pixels[y*pixels_w + x] = color;
				}
			}
		}
	}

}

int olivec_investigate_ppm_file(const char* file_name) {

	std::ifstream inFile;
	uint8_t result = 0;
	
	{
		inFile.open(file_name, std::ios::in | std::ios::binary);
		
		if(!inFile.is_open()){
			return_defer(-1);
		}

		std::string line;
		while(std::getline(inFile, line)) {
			std::cout << line << "\n" ;
		}
		result = 1;
		inFile.close();
		return result;

	}

defer:

	if (inFile) {
		inFile.close();
	}

	return result;

}

int olivec_save_to_ppm_file_path(uint32_t *pixels, size_t width, size_t height, const char* file_path ){
	
	int result = 0;
	std::ofstream outFile;

	{
		outFile.open(file_path, std::ios::out|std::ios::binary);

		if (!outFile.is_open())
			return_defer(-1);
		
		std::string str = "P6\n" + std::to_string(width) + " " + std::to_string(height) + " 255\n";	
		outFile.write(str.c_str(), str.size());

		if(outFile.bad()) return_defer(-1);

		for(size_t i=0;i < width * height; i++) {
			// if (i%width == 0) outFile << "\n";
			uint8_t bytes[3] = {
				(pixels[i]>>(8*0)) & 0xFF,
				(pixels[i]>>(8*1)) & 0xFF,
				(pixels[i]>>(8*2)) & 0xFF,
			};
			
			// std::cout << "Attempting to write bytes to file! \n" << std::endl;

			outFile.write(reinterpret_cast<const char*>(bytes), sizeof(bytes));
			if (outFile.bad()) 
				return_defer(-1);
			
		}
	}
	
	outFile.close();

	return 1;

defer:

	if (outFile) outFile.close();
	return result;

}

#endif

