#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "str.h"

#define MAX_SIZE 100

#define STRCOPY_STR      "StrCopy"
#define STRCOMPARE_STR   "StrCompare"
#define STRGETLENGTH_STR "StrGetLength"
#define STRCONCAT_STR    "StrConcat"
#define STRSEARCH_STR    "StrSearch"

#define PRINT_RESULT(a) \
  (a) ? printf("Correct!\n") : printf("Wrong!\n")
/*------------------------------------------------------------------*/
void
TestStrCopy(const char* str1)
{
  char dest[MAX_SIZE];
  char answer[MAX_SIZE];
  char *res1, *res2;

  printf("===========================\n"
	 "Test StrCopy\n"
	 "===========================\n");

  res1 = StrCopy(dest, str1);
  res2 = strcpy(answer, str1);

  PRINT_RESULT((strcmp(res1, res2) == 0));
  printf("Your     Answer: [%s]\n", res1);
  printf("String.h Answer: [%s]\n", res2);

  return;
}
/*------------------------------------------------------------------*/
void 
TestStrGetLength(const char* str1)
{
  size_t res1, res2;

  printf("===========================\n"
	 "Test StrGetLength\n"
	 "===========================\n");

  res1 = StrGetLength(str1);
  res2 = strlen(str1);
  
  PRINT_RESULT(res1 == res2);
  printf("Your     Answer: [%d]\n", (int)res1);
  printf("String.h Answer: [%d]\n", (int)res2);
}
/*-----------------------------------------------------------------*/
void
TestStrSearch(const char* str1)
{
  printf("Entry\n");

  char *res1, *res2;

  printf("===========================\n"
	 "Test StrSearch\n"
	 "===========================\n");

  printf("TestStrSearch Starts\n");
  res1 = StrSearch(str1, "Str");
  printf("res1 done\n");
  res2 = strstr(str1, "Str");
  printf("res2 done\n");

  printf("res1 : %s\n", res1);
  printf("res2 : %s\n", res2);

  if((res1 == NULL) && (res2 == NULL))
  {
    printf("correct\n");
    return;
  }


  PRINT_RESULT((strcmp(res1, res2) == 0));
  printf("Your     Answer: [%s]\n", res1);
  printf("String.h Answer: [%s]\n", res2);

  return;
}
/*------------------------------------------------------------------*/
void
TestStrCompare(const char* str)
{
  int res1, res2;
  
  printf("===========================\n"
	 "Test StrCompare\n"
	 "===========================\n");
  
  res1 = StrCompare(str, "TestCompare");
  res2 = strcmp(str, "TestCompare");

  PRINT_RESULT((res1 * res2 > 0) || (res1 == 0 && res2 == 0));
  printf("Your     Answer: [%d]\n", res1);
  printf("String.h Answer: [%d]\n", res2);
  
  return;
}
/*------------------------------------------------------------------*/
void 
TestStrConcat(const char* str1)
{
  char dest1[MAX_SIZE] = "Previous dest: ";
  char answer1[MAX_SIZE] = "Previous dest: ";
  char *res1, *res2;

  printf("===========================\n"
	 "Test StrConcat\n"
	 "===========================\n");

  res1 = StrConcat(dest1, str1);
  res2 = strcat(answer1, str1);

  PRINT_RESULT((strcmp(res1, res2) == 0));
  printf("Your     Answer:\n[%s]\n", res1);
  printf("String.h Answer:\n[%s]\n", res2);
  printf("strcmp : %d\n", strcmp(res1, res2));
  printf("length : %d\n", (int)strlen(res2));

  return;
}

/*------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
  char *s = (char*)malloc(sizeof(char) * 10001);
  char *copy = (char*)malloc(sizeof(char) * 10001);

  scanf("%s", s);

  strcpy(copy, s);
  TestStrCopy(copy);

  strcpy(copy, s);
  TestStrGetLength(copy);

  strcpy(copy, s);
  TestStrSearch(copy);

  strcpy(copy, s);
  TestStrCompare(copy);

  strcpy(copy, s);
  TestStrConcat(copy);

  return 0;
}