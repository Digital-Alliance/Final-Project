#include <stdint.h>
int main(void) 
{ 
 
 // red LED address 
int i, j;
int c; 
volatile int16_t **picture = (int16_t **) 0x01000000;
volatile int *start  = (int *)     0xFF200070; 
volatile int *go = (int*)          0xFF200060;
volatile int *data1In = (int*)     0xFF200050;
volatile int *data2In = (int*)     0xFF200040;
volatile int *data1Out = (int*)    0xFF200030;
volatile int *data2Out = (int*)    0xFF200020;
volatile int *vgaclk = (int*)      0xFF200010;
volatile int *sdramclk = (int*)    0xFF200000;
  *start = 0;
//int y = 0;
int x = 0;
//int prev1 = -1;
*start = 1;

for(c=0; c<1000000; c++);
*start = 3;

for(i = 0; i<480; i++) {
	for(j = 0; j<640; j++)
		printf("%d,", picture[i*640+j]);
	printf("\n");}
return 1;
} 
