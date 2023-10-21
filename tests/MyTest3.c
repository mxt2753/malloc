#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
int TestingCoal();
int main()
{
  printf("Running test 3  to test coalesce\n");
  int EndOutcome = TestingCoal();
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

int TestingCoal()
{
  char * ptr1 = ( char * ) malloc ( 1200 );
  char * ptr2 = ( char * ) malloc ( 1200 );

  if(!ptr1 || !ptr2)
  {
    printf("Error happening with the Memory, section 1...exiting");
    return 1;
  }

  free( ptr1 );
  free( ptr2 );

  char * ptr3 = ( char * ) malloc ( 2048 );
  if(!ptr3)
  {
    printf("Error happening with the Memory, section 2...exiting");
    return 1;
  }
  free( ptr3 );
  return 0;
}
