#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
int TestingMalloc();
int TestingMalloc()
{
  char * Point1 = ( char * ) malloc( 2048 );
  printf("address of Ptr1: %p\n ", Point1);
  free( Point1 );
  char * Point2 = ( char * ) malloc( 1024 );
  printf("address of Ptr2: %p\n ", Point2);
  free( Point2 );
  return 0;
}
int main()
{
  printf("Running test 4 to test a block split and reuse\n");
  int EndOutcome=TestingMalloc();
  if(EndOutcome==0)
  {
    printf("Yay,test is good!!\n");
  }
  else
  {
    printf("Boo,test is bad!!\n");
  }
  return EndOutcome;
}
