
void add_pixel(int red, int green, int blue); 

void make_png(int width, int height);

int main() {
	add_pixel(255, 0, 0);
	add_pixel(255, 0, 0);
	add_pixel(0, 255, 0);
	add_pixel(0, 255, 0);
	add_pixel(0, 0, 255);
	make_png(3, 2);
}