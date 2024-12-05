#include <stdio.h>

#define WIDTH	40*3
#define HEIGHT	60*3

double semi_width  = (double)WIDTH / 2.0;
double semi_height = (double)HEIGHT/ 2.0;

// escala de grises
#define NUM_COLORS	5
int gray_scale[NUM_COLORS][3] = {
	{0, 0, 0},
	{64, 64, 64},
	{128, 128, 128},
	{192, 192, 192},
	{255, 255, 255}
};
// double color_factor = (double)(NUM_COLORS-1) / (double)MAX_ITER;

// colores
int black[3]	= { 0, 0, 0 };
int red[3]	= { 255, 0, 0 };
int green[3]	= { 0, 255, 0 };
int blue[3]	= { 0, 0, 255 };
int cyan[3]	= { 0, 255, 255 };
int magenta[3]	= { 255, 0, 255 };
int yellow[3]	= { 255, 255, 0 };
int white[3]	= { 255, 255, 255 };

// imagen
int pixel[WIDTH][HEIGHT][3];


void print_pixels(){
	for (int j=0; j<HEIGHT; j++){
		for (int i=0; i<WIDTH; i++){
			printf("( ");
			for (int k=0; k<3; k++)
				printf("%d ", pixel[i][j][k]);
			printf(")");
		}
		printf("\n");
	}
}

FILE* init_archi(){
	FILE* archi = fopen("out.ppm", "w");
	if (!archi){
		printf("ERROR abriendo el archivo\n");
		return archi;
	}

	fprintf(archi, "P3\n");		// P3 significa que los colores están en ASCII
	fprintf(archi, "%d %d\n", WIDTH, HEIGHT);	// pixeles ancho y alto
	fprintf(archi, "%d\n", 255);	// color máximo
	return archi;
}

int save_image(){
	FILE *archi = init_archi();
	if (!archi) return 0;

	for (int j=0; j<HEIGHT; j++){
		for (int i=0; i<WIDTH; i++)
			for (int k=0; k<3; k++)
				fprintf(archi, "%d ", pixel[i][j][k]);
		//fprintf(archi, "\n");
	}
	fclose(archi);
	return 1;
}

void swap(int *a, int *b){
	int aux = *a;
	*a = *b;
	*b = aux;
}

void draw_fill_rect(int x1, int y1, int x2, int y2, int c[3]){
	if (x1>x2) swap(&x1, &x2);
	if (y1>y2) swap(&y1, &y2);

	if (x1<0) x1=0;
	if (y1<0) y1=0;

	for (int i=x1; i<=x2 && i<WIDTH; i++)
		for (int j=y1; j<=y2 && j<HEIGHT; j++){
			pixel[i][j][0] = c[0];
			pixel[i][j][1] = c[1];
			pixel[i][j][2] = c[2];
		}
}

int main(){

	draw_fill_rect(0, 0, 24*3, 19*3, red);
	draw_fill_rect(25*3, 0, 40*3, 19*3, white);
	draw_fill_rect(0, 20*3, 24*3, 53*3, white);
	draw_fill_rect(25*3, 20*3, 39*3, 53*3, blue);
	draw_fill_rect(0, 54*3, 5*3, 60*3, gray_scale[3]);
	draw_fill_rect(5*3, 54*3, 24*3, 60*3, yellow);
	draw_fill_rect(25*3, 54*3, 40*3, 60*3, white);

	//print_pixels();
	if (!save_image()) return 1;

	return 0;
}
