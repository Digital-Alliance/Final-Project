static inline unsigned int getCycles ()
{
  unsigned int cycleCount;
  // Read CCNT register
  asm volatile ("MRC p15, 0, %0, c9, c13, 0\t\n": "=r"(cycleCount));  
  return cycleCount;
}
static inline void initCounters ()
{
  // Enable user access to performance counter
  asm volatile ("MCR p15, 0, %0, C9, C14, 0\t\n" :: "r"(1));
  // Reset all counters to zero
  int MCRP15ResetAll = 23; 
  asm volatile ("MCR p15, 0, %0, c9, c12, 0\t\n" :: "r"(MCRP15ResetAll));  
  // Enable all counters:  
  asm volatile ("MCR p15, 0, %0, c9, c12, 1\t\n" :: "r"(0x8000000f));  
  // Disable counter interrupts
  asm volatile ("MCR p15, 0, %0, C9, C14, 2\t\n" :: "r"(0x8000000f));
  // Clear overflows:
  asm volatile ("MCR p15, 0, %0, c9, c12, 3\t\n" :: "r"(0x8000000f));
}
int main(void)
{
int i = 0;
int fakeCounter = 0;
initCounters (); 
    
unsigned int time = getCycles();
for (i = 0; i < 20000; i++)
fakeCounter = fakeCounter + 1;
time = getCycles() - time;
printf ("Elapsed Time: %d cycles\n", time);

time = getCycles();
for (i = 0; i < 200000; i++)
fakeCounter = fakeCounter + 1;
time = getCycles() - time;
printf ("Elapsed Time: %d cycles\n", time);
}
