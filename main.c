#include<stdio.h>

#define WIDTH 800
#define HEIGHT 600

typedef struct
{
	float x, y, z;
}vec3;

typedef struct
{
	vec3 start;
	vec3 dir;
}ray;

typedef struct
{
	vec3 pos;
	float radius;
}sphere;

vec3 vec3Sub(vec3 *v1, vec3 *v2)
{
	vec3 result = {v1->x - v2->x, v1->y - v2->y, v1->z - v2->z};
	return result;
}

float vec3Dot(vec3 *v1, vec3 *v2)
{
	return v1->x * v2->x + v1->y * v2->y + v1->z * v2->z;
}

int intersectRaySphere(ray *r, sphere *s)
{

	vec3 raytosphere = vec3Sub(&r->start, &s->pos);

	float a = vec3Dot(&r->dir, &r->dir);
	float b = 2 * vec3Dot(&r->dir, &raytosphere);
	float c = vec3Dot(&raytosphere, &raytosphere) - (s->radius)*(s->radius);

	float disc = b * b - 4 * a * c;
	if (disc >= 0)
		return 1;
	else
		return 0;
}

void saveppm(char *filename, unsigned char *img, int width, int height)
{
	FILE *f;

	f = fopen(filename, "wb");

	fprintf(f, "P6 %d %d %d\n", width, height, 255);
	fwrite(img, 3, width*height, f);

	fclose(f);
}

int main(int argc, char *argv[])
{
	unsigned char img[WIDTH * HEIGHT * 3];
	int i,j;

	for(i=0; i<HEIGHT; i++)
	{
		for(j=0; j<WIDTH; j++)
		{
			img[(j + i*WIDTH) * 3 + 0] = 255;
			img[(j + i*WIDTH) * 3 + 1] = 255;
			img[(j + i*WIDTH) * 3 + 2] = 0;
			
		}
	}

	saveppm("test_image.ppm", img, WIDTH, HEIGHT);

	return 0;
}
