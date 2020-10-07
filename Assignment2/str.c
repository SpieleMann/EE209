/*
 * Name:          JungHeeJun
 * StudentID:     20190614
 * Assignment #:  2
 * file name:     str.c
 */

#include <assert.h> /* to use assert() */
#include <stdio.h>
#include "str.h"

/* Your task is: 
   1. Rewrite the body of "Part 1" functions - remove the current
      body that simply calls the corresponding C standard library
      function.
   2. Write appropriate comment per each function
*/

/* Part 1 */
/*------------------------------------------------------------------------*/
size_t StrGetLength(const char* pcSrc)
{
  const char *pcEnd;
  assert(pcSrc); /* NULL address, 0, and FALSE are identical. */
  pcEnd = pcSrc;
	
  while (*pcEnd) /* null character and FALSE are identical. */
    pcEnd++;

  return (size_t)(pcEnd - pcSrc);
}

/*------------------------------------------------------------------------*/
char *StrCopy(char* pcDest, const char* pcSrc)
{
  char *pcDest_idx;
  const char *pcSrc_idx;
  assert(pcDest);
  assert(pcSrc);

  pcDest_idx = pcDest;
  pcSrc_idx = pcSrc;

  while(*pcSrc_idx)
  {
    *pcDest_idx = *pcSrc_idx;
    pcDest_idx++;
    pcSrc_idx++;
  }

  *pcDest_idx = '\0';

  return pcDest;
}

/*------------------------------------------------------------------------*/
int StrCompare(const char* pcS1, const char* pcS2)
{
  const char *pcS1_idx, *pcS2_idx;
  assert(pcS1);
  assert(pcS2);

  pcS1_idx = pcS1;
  pcS2_idx = pcS2;

  while((*pcS1_idx) && (*pcS2_idx))
  {
    if(*pcS1_idx != *pcS2_idx)
      return *pcS1_idx - *pcS2_idx;

    pcS1_idx++;
    pcS2_idx++;
  }

  return (int)(*pcS1_idx - *pcS2_idx);
}
/*------------------------------------------------------------------------*/
char *StrSearch(const char* pcHaystack, const char *pcNeedle)
{
  int chk;
  const char *pcHaystack_rep, *pcNeedle_rep;
  const char *pcHaystack_idx, *pcNeedle_idx;
  assert(pcHaystack);
  assert(pcNeedle);

  pcHaystack_rep = pcHaystack;
  pcNeedle_rep = pcNeedle;

  while(*pcHaystack_rep)
  {
    chk = 1;
    pcHaystack_idx = pcHaystack_rep;
    pcNeedle_idx = pcNeedle_rep;
    
    while(*pcNeedle_idx)
    {
      if(*pcHaystack_idx != *pcNeedle_idx)
      {
        chk = 0;
        break;
      }

      pcHaystack_idx++;
      pcNeedle_idx++;
    }

    if(chk)
      return (char*)pcHaystack_rep;

    pcHaystack_rep++;
  }

  return NULL;
}
/*------------------------------------------------------------------------*/
char *StrConcat(char *pcDest, const char* pcSrc)
{
  char *pcDest_rep;
  const char *pcSrc_rep;
  assert(pcDest);
  assert(pcSrc);

  pcDest_rep = pcDest;
  pcSrc_rep = pcSrc;

  while(*pcDest_rep)
    pcDest_rep++;

  while(*pcSrc_rep)
  {
    *pcDest_rep = *pcSrc_rep;
    pcDest_rep++;
    pcSrc_rep++;
  }

  *pcDest_rep = '\0';

  return pcDest;
}