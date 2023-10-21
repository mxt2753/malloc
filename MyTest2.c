#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
int TestFreeMall();

int TestFreeMall()
{
  char * Point = ( char * ) malloc (65535);
  if(!Point)
  {
    printf("Error happening with the Memory, section 1...exiting");
    return 1;
  }

  char * PointArr[1024];

  int i;
  for (i=0;i<1024;i++)
  {
    PointArr[i]=(char*)malloc(1024); 
    if(!PointArr[i])
    {
      printf("Error happening with the Memory, section 2...exiting");
      return 1;
    }
    //PointArr[i] = PointArr[i];
  }
  free(Point);
  for (i=0;i<1024;i++ )
  {
    if(i%2==0)
    {
      free(PointArr[i] );
      assert(PointArr[i]!= NULL);
    }
  }
  Point = (char *) malloc ( 65535 );
  if(!Point)
  {
    printf("Error happening with the Memory, section 3...exiting");
    return 1;
  }
  free(Point); 
  return 0;
}
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
