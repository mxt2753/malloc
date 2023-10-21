#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
int TestingCoal();

int TestingCoal()
{
  char * Point1 = ( char * ) malloc ( 1200 );
  char * Point2 = ( char * ) malloc ( 1200 );
  if(!Point1 || !Point2)
  {
    printf("Error happening with the Memory, section 1...exiting");
    return 1;
  }
  free( Point1 );
  free( Point2 );
  char * Point3 = ( char * ) malloc ( 2048 );
  if(!Point3)
  {
    printf("Error happening with the Memory, section 2...exiting");
    return 1;
  }
  free( Point3 );
  return 0;
}
int main()
{
  printf("Running test 3  to test coalesce\n");
  int EndOutcome=TestingCoal();
   if(EndOutcome==0)
  {
    printf("Yay, test is good!!\n");
  }
  else
  {
    printf("Boo, test is bad!!\n");
  }
  return EndOutcome;
}