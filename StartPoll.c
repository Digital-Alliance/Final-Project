int main(void) 
{ 
 
volatile int *memory	= (int *) 0x01000000;
volatile int *start   	= (int *) 0xFF200000;  // output: start signal 
volatile int *clk	= (int* ) 0xFF200010; //  input: clock signal
volatile int *ready  = (int*) 0xFF200020;
volatile int *datain = (int*) 0xFF200030;
volatile int *clkin = (int*) 0xFF200040;
int x;
int c; int clkprev;
 *start = 0; *ready = 0; *clk =0;
 int y;
int mem2 = memory;
/*while ( c != '1') 
 
{ printf("\n");
  printf("Press 1 to Start Camera:\n");
  c =getchar();
} */
*start = 1;
for(c=0; c<1000000; c++);
*start = 3;
(*ready) = 1;
for(x =0; x<640*480; x++){
	//printf("%d ", x); 
	*clk = 1;
	while(*clkin == 0);
	memory[x] = *datain;
	*clk = 0;
	while(*clkin == 1);
	} // for
for(x =0; x<480; x++){
	for(y = 0; y<640; y++){
	printf("%d,", memory[x*640+y]);
	
	}
	printf("\n");
	}
return 1;
} 

