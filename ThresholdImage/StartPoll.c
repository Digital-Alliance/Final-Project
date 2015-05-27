int main(void) 
{ 
 
volatile int *start   	= (int *) 0xFF200000;  // output: start signal 
volatile int *clk	= (int* ) 0xFF200010; //  input: clock signal
volatile int *threshold = (int*) 0xFF200040;
char waste;
int c; 
*threshold = 170;
 *start = 0;
 
/*while ( c != '1') 
 
{ printf("\n");
  printf("Press 1 to Start Camera:\n");
  c =getchar();
} */
*start = 1;
//for(c=0; c<1000000; c++);
//*start = 3;
/*while( c!= '1')
{
  printf("\n");
  printf("Press 1 for Snapshot Mode\n");
  c =getchar();
}
*start = 3;*/



while(1){

	printf("Enter ThreshValues(0-254): ");
	scanf("%d", threshold);
	scanf("%c", waste);
}
return 1;
} 

