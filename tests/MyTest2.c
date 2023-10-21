#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
int TestFreeMall();
int main()
{
  printf("Running test 2 to exercise malloc and free\n");
  int EndOutcome = TestFreeMall();
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
int TestFreeMall()
{
  char * ptr = ( char * ) malloc (65535);
  if(!ptr)
  {
    printf("Error happening with the Memory, section 1...exiting");
    return 1;
  }

  char * ptr_array[1024];

  int i;
  for ( i = 0; i < 1024; i++ )
  {
    ptr_array[i] = ( char * ) malloc ( 1024); 
    if(!ptr_array[i])
    {
      printf("Error happening with the Memory, section 2...exiting");
      return 1;
    }
    //ptr_array[i] = ptr_array[i];
  }
  free( ptr );
  for (i = 0; i < 1024; i++ )
  {
    if( i % 2 == 0 )
    {
      free( ptr_array[i] );
      assert(ptr_array[i]!= NULL);
    }
  }
  ptr = ( char * ) malloc ( 65535 );
  if(!ptr)
  {
    printf("Error happening with the Memory, section 3...exiting");
    return 1;
  }
  free( ptr ); 

  return 0;
}
