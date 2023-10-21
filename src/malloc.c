//malloc 2 
//Name: Mary-Rose Tracy
//ID#:1001852753
//Original Includes, gonna make it alphabetical order
#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>
//my own includes just in case. 
#include <stddef.h>
//original Defines
#define ALIGN4(s)(((((s)-1)>>2)<<2)+4)
#define BLOCK_DATA(b)((b)+1)
#define BLOCK_HEADER(ptr)((struct _block*)(ptr)-1)
//original static ints, gonna make it alphabetical
static int atexit_registered=0; //o static int
static int max_heap=0; //o static int
static int num_blocks=0; //o static int
static int num_coalesces=0; //o static int
static int num_frees=0; //o static int
static int num_grows=0; //o static int
static int num_mallocs=0; //o static int
static int num_reuses=0; //o static int
static int num_requested=0; //o static int
static int num_splits=0; //o static int

/* brief printStatistics
 *  \param none
 *  Prints the heap statistics upon process exit.  Registered
 *  via atexit()
 *  \return none
 */
//original print statistics model, not gonna touch this one
void printStatistics(void) //we'' call print statistics at malloc
{
  printf("\nheap management statistics\n");
  printf("mallocs:\t%d\n",num_mallocs);
  printf("frees:\t\t%d\n",num_frees);
  printf("reuses:\t\t%d\n",num_reuses);
  printf("grows:\t\t%d\n",num_grows);
  printf("splits:\t\t%d\n",num_splits);
  printf("coalesces:\t%d\n",num_coalesces);
  printf("blocks:\t\t%d\n",num_blocks);
  printf("requested:\t%d\n",num_requested);
  printf("max heap:\t%d\n",max_heap);
}
//original struct _block
struct _block 
{
   size_t size;         /* Size of the allocated _block of memory in bytes */
   struct _block *next;  /* Pointer to the next _block of allcated memory   */
   bool free;          /* Is this _block free?                            */
   char padding[3];    /* Padding: IENTRTMzMjAgU3ByaW5nIDIwMjM            */

};
struct _block *heapList = NULL; //original  Free list to track the _blocks available
/*\brief findFreeBlock
 * \param last pointer to the linked list of free _blocks
 * \param size size of the _block needed in bytes 
 * \return a _block that fits the request or NULL if no free _block matches
 * \TODO Implement Next Fit
 * \TODO Implement Best Fit
 * \TODO Implement Worst Fit
 */
struct _block *findFreeBlock(struct _block **last, size_t size) 
{
   struct _block *CPoint=heapList; //CPoint- means Current Point Using original _block, & heaplist variable
#if defined FIT && FIT == 0 //Original, I know I'm gonna more curr alot so I changed the variable b/c I kept on mityping it
/* First fit While we haven't run off the end of the linked list and. while the CPointent node we point to isn't free or isn't big enough
then continue to iterate over the list. This loop ends either. with CPoint pointing to NULL, meaning we've run to the end of the list
without finding a node or it ends pointing to a free node that has enough. space for the request.*/
   while(CPoint&& !(CPoint->free&&CPoint->size>=size)) //original method
   {
      *last=CPoint;
      CPoint=CPoint->next;
   }
#endif

// \TODO Put your Best Fit code in this #ifdef block
#if defined BEST&&BEST==0
   /** \TODO Implement best fit here */
   struct _block *Best=NULL; //initialize best & make it null
   while(CPoint)
   {
      if(CPoint->free&&CPoint->size>=size)
      {
         if(!Best||CPoint->size<Best->size)
         {
            Best=CPoint;
         }
      }
      *last=CPoint;
      CPoint=CPoint->next;
   }
   CPoint=Best;
#endif
// \TODO Put your Worst Fit code in this #ifdef block
#if defined WORST&&WORST==0
   /** \TODO Implement worst fit here */
struct _block *Worst=NULL; //we are doing Worst fit not make it null
while(CPoint)
{
   if(CPoint->free&&CPoint->size>=size)
   {
      if(!Worst||CPoint->size>Worst->size)
      {
         Worst=CPoint;
      }
   }
   *last=CPoint;
   CPoint=CPoint->next;
}
CPoint=Worst;
#endif
// \TODO Put your Next Fit code in this #ifdef block
#if defined NEXT&&NEXT==0
   /** \TODO Implement next fit here */
   static struct _block *NFPoint=NULL;//we doing Next Fit point now make it null 
   if(!NFPoint)
   {
      NFPoint=heapList;
   }
   CPoint=NFPoint;
   while(CPoint&&!(CPoint->free&&CPoint->size>=size))
   {
      *last=CPoint; //we gonna use the last variable & dereference it
      CPoint=CPoint->next;
      if(!CPoint)
      {
         CPoint=heapList;
      }
      if(CPoint==NFPoint)
      {
         break;
      }
   }
   NFPoint = CPoint;
#endif
   return CPoint;
}
/* \brief growheap. Given a requested size of memory, use sbrk() to dynamically 
 increase the data segment of the calling process.Updates. the free list with the newly allocated memory.
 * \param last tail of the free _block list. \param size size in bytes to request from the OS. \return returns the newly allocated _block of NULL if failed */
struct _block *growHeap(struct _block *last, size_t size) 
{
   /* Request more space from OS*/
   struct _block *CPoint=(struct _block*)sbrk(0); //orignal , just changed curr to CPoint
   struct _block *prev=(struct _block*)sbrk(sizeof(struct _block)+size); //original
   //sbrk???? "sbrk() function is used to change the space allocated for the calling process -IBM" oh okay 
   assert(CPoint==prev);
   /* OS allocation failed */
   if(CPoint==(struct _block*)-1) 
   {
      return NULL;
   }
   /* Update heapList if not set */
   if(heapList==NULL) 
   {
      heapList=CPoint;
   }
   /* Attach new _block to previous _block */
   if(last) 
   {
      last->next=CPoint;
   }
   /* Update _block metadata:
      Set the size of the new block and initialize the new block to "free".
      Set its next pointer to NULL since it's now the tail of the linked list.
   */
   CPoint->size=size; //from orginal
   CPoint->next=NULL; //from orginal
   CPoint->free=false;//from orginal
   num_grows++;
   max_heap+=(sizeof(struct _block)+size);
   return CPoint;
}

/*
 * \brief malloc
 *
 * finds a free _block of heap memory for the calling process.
 * if there is no free _block that satisfies the request then grows the 
 * heap and returns a new _block
 *
 * \param size size of the requested memory in bytes
 *
 * \return returns the requested memory allocation to the calling process 
 * or NULL if failed
 */
void *malloc(size_t size) 
{
   //original method
   if(atexit_registered==0)
   {
      atexit_registered=1;
      atexit(printStatistics);
   }
   /* Align to multiple of 4 */
   size=ALIGN4(size); //original
   /* Original- Handle 0 size */
   if(size==0) 
   {
      return NULL;
   }
   /* Look for free _block.  If a free block isn't found then we need to grow our heap. */
   struct _block *last=heapList; //original 
   struct _block *next=findFreeBlock(&last,size); //original
   /* TODO: If the block found by findFreeBlock is larger than we need then:
   If the leftover space in the new block is greater than the sizeof(_block)+4 then. split the block.
   If the leftover space in the new block is less than the sizeof(_block)+4 then. don't split the block. */
   if(next)
   {
      num_reuses++; //from static int 
      num_requested+=size; //from static int
   }
   else
   {
      next=growHeap(last,size);
      num_blocks++;
      num_requested+=size;
      if(!next)
      {
         return NULL;
      }
   }
   if(next->size >size +sizeof(struct _block)+4)
   {
      struct _block *TNBlock =(struct _block *)((char *)next + sizeof(struct _block)+size);
      TNBlock->size = next->size -size -sizeof(struct _block);
      TNBlock->next=next->next;
      TNBlock-> free=true;
      next->size = size;
      next->next=TNBlock;
      num_splits++;
      num_blocks++;
   }
   next-> free = false;
   num_mallocs++;
   return BLOCK_DATA(next);
}
/*
   Could not find free _block, so grow heap 
   if (next == NULL) 
   {
      next = growHeap(last, size);
   }

    Could not find free _block or grow heap, so just return NULL 
   if (next == NULL) 
   {
      return NULL;
   }
   
   Mark _block as in use 
   next->free = false;

   Return data address associated with _block to the user 
   return BLOCK_DATA(next);
}
*/
/*
 * \brief free
 *
 * frees the memory _block pointed to by pointer. if the _block is adjacent
 * to another _block then coalesces (combines) them
 *
 * \param ptr the heap memory to free
 *
 * \return none
*/
void free(void *ptr) 
{
   struct _block *CPoint = BLOCK_HEADER(ptr); //orginial
   if (ptr == NULL) 
   {
      return;
   }
   /* Make _block as free */
   // assert(CPoint->free == 0); //orginial
   CPoint->free = true; //orginial
   num_frees++; //from static int

   /* TODO: Coalesce free _blocks.  If the next block or previous block 
            are free then combine them with this block being freed.
   */
  struct _block *next = CPoint-> next;
  if(next && next->free)
  {
   CPoint->size+=next->size+sizeof(struct _block);
   CPoint->next=next->next;
   num_coalesces++; //from static int
   num_blocks--; //from static int
  }
  struct _block *prev=heapList;
  while(prev&&prev->next!=CPoint)
  {
   prev=prev->next;
  }
  if(prev&&prev->free)
  {
   prev->size += CPoint-> size +sizeof(struct _block);
   prev-> next= CPoint->next;
   num_coalesces++; //static int
   num_blocks--; //from static int
  }
}
void *calloc(size_t nmemb,size_t size)
{
   // \TODO Implement calloc
   size_t TotSize =nmemb*size;
   void *ptr=malloc(TotSize);
   if(ptr)
   {
      memset(ptr,0,TotSize);

   }
   return ptr;

   //return NULL;
}

void *realloc( void *ptr, size_t size )
{
   // \TODO Implement realloc
   if(!ptr)
   {
      return malloc(size);
   }
   if(size==0)
   {
      free(ptr);
      return NULL;
   }
   struct _block *CPoint = BLOCK_HEADER(ptr);
   size_t OrigSize = CPoint->size;

   if(size<= OrigSize)
   {
      return ptr;
   }
   void *NPoint = malloc(size);
   if(NPoint)
   {
      memcpy(NPoint, ptr, OrigSize);
      free(ptr);
   }
   return NPoint;
   //return NULL;
} 



/* vim: IENTRTMzMjAgU3ByaW5nIDIwMjM= -----------------------------------------*/
/* vim: set expandtab sts=3 sw=3 ts=6 ft=cpp: --------------------------------*/
