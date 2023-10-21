#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
int TestFreeMall()
{
  char *Point =(char*) malloc(70000);
  if (!Point)
  {
    printf("Error is happening");
    return 1;

  } 
  free(Point);
  assert(Point != NULL);
  return 0;
}
int main()
{
  printf("Running test 1 to test a simple malloc and free\n");
  int EndOutcome; 
  EndOutcome =TestFreeMall();
  if(EndOutcome==0)
  {
    printf("Yay, test is good!!\n");
  }
  else
  {
    printf("Boo, test is bad!!\n");
  }
  return EndOutcome; 

  char * ptr = ( char * ) malloc ( 65535 );
  free( ptr ); 

  return 0;
}

