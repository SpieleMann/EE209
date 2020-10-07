/*
 * Name:          JungHeeJun
 * StudentID:     20190614
 * Assignment #:  2
 * file name:     sgrep.c
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h> /* for skeleton code */
#include <unistd.h> /* for getopt */
#include "str.h"

#define FIND_STR        "-f"
#define REPLACE_STR     "-r"
#define DIFF_STR        "-d"

#define MAX_STR_LEN 1023

#define FALSE 0
#define TRUE  1

typedef enum {
  INVALID,
  FIND,
  REPLACE,
  DIFF
} CommandType;

/*
 * Fill out your functions here (If you need) 
 */

int ArgumentCheck(const char* arg)
{
  if(StrGetLength(arg) > MAX_STR_LEN)
  {
    fprintf(stderr, "Error: argument is too long\n");
      return FALSE;
  }
  
  return TRUE;
}


/*--------------------------------------------------------------------*/
/* PrintUsage()
   print out the usage of the Simple Grep Program                     */
/*--------------------------------------------------------------------*/
void 
PrintUsage(const char* argv0) 
{
  const static char *fmt = 
    "Simple Grep (sgrep) Usage:\n"
    "%s [COMMAND] [OPTIONS]...\n"
    "\nCOMMNAD\n"
    "\tFind: -f [search-string]\n"
    "\tReplace: -r [string1] [string2]\n"
    "\tDiff: -d [file1] [file2]\n";

  printf(fmt, argv0);
}
/*-------------------------------------------------------------------*/
/* DoFind()
   Your task:
   1. Do argument validation 
   - String or file argument length is no more than 1023
   - If you encounter a command-line argument that's too long, 
   print out "Error: argument is too long"
   
   2. Read the each line from standard input (stdin)
   - If you encounter a line larger than 1023 bytes, 
   print out "Error: input line is too long" 
   - Error message should be printed out to standard error (stderr)
   
   3. Check & print out the line contains a given string (search-string)
      
   Tips:
   - fgets() is an useful function to read characters from file. Note 
   that the fget() reads until newline or the end-of-file is reached. 
   - fprintf(sderr, ...) should be useful for printing out error
   message to standard error

   NOTE: If there is any problem, return FALSE; if not, return TRUE  */
/*-------------------------------------------------------------------*/
int
DoFind(const char *pcSearch)
{
  /*
   * Read inputs from stdin, and find the line containing target str.
   * Found line is printed via stdout
   * Returns TRUE if whole procedure is successfully done,
   * otherwise return FALSE
   */
  char buf[MAX_STR_LEN + 2]; 
  char *found;
  int len;

  /* If argument's length exceeds 1023 bytes, raise error */
  if(!ArgumentCheck(pcSearch))
    return FALSE;
   
  /* Read the line by line from stdin, Note that this is an example */
  while (fgets(buf, sizeof(buf), stdin)) {
    /* check input line length */
    if ((len = StrGetLength(buf)) > MAX_STR_LEN) {
      fprintf(stderr, "Error: input line is too long\n");
      return FALSE;
    }
    
    /* Find the string */
    found = StrSearch(buf, pcSearch);
    
    /* If the string is succesfully found */
    if(found) {
      /* then print the line via stdout*/
      printf("%s", buf);

      /* If the last line doesn't end with newline character, */
      if(buf[StrGetLength(buf) - 1] != '\n') {\
        /* then print newline character forcibly */
        printf("\n");
      }
    }
  }


   
  return TRUE;
}
/*-------------------------------------------------------------------*/
/* DoReplace()
   Your task:
   1. Do argument validation 
      - String length is no more than 1023
      - If you encounter a command-line argument that's too long, 
        print out "Error: argument is too long"
      - If word1 is an empty string,
        print out "Error: Can't replace an empty substring"
      
   2. Read the each line from standard input (stdin)
      - If you encounter a line larger than 1023 bytes, 
        print out "Error: input line is too long" 
      - Error message should be printed out to standard error (stderr)

   3. Replace the string and print out the replaced string

   NOTE: If there is any problem, return FALSE; if not, return TRUE  */
/*-------------------------------------------------------------------*/
int
DoReplace(const char *pcString1, const char *pcString2)
{
  /*
   * Read inputs from stdin,
   * and find the line containing target string (here, pcString1).
   * the target string in found line is replaced into pcString2.
   * Returns TRUE if whole procedure is successfully done,
   * otherwise return FALSE
   */
  char buf[MAX_STR_LEN + 2]; 
  char *found;
  char *buf_idx;
  int isValidArg1, isValidArg2, len, pcString1_len;

  /* Get the length of pcString1 */
  pcString1_len = StrGetLength(pcString1);

  /* Check the validity of arguments */
  isValidArg1 = ArgumentCheck(pcString1);
  isValidArg2 = ArgumentCheck(pcString2);

  /* If argument's length exceeds 1023 bytes, raise error */
  if(!isValidArg1 || !isValidArg2)
    return FALSE;

  /* If pcString1 is an empty string, raise error */ 
  if(StrGetLength(pcString1) == 0) {
    fprintf(stderr, "Error: Can't replace an empty substring\n");
    return FALSE;
  }

  /* Read the line by line from stdin */
  while (fgets(buf, sizeof(buf), stdin)) {
    /* check input line length */
    if ((len = StrGetLength(buf)) > MAX_STR_LEN) {
      fprintf(stderr, "Error: input line is too long\n");
      return FALSE;
    }
    
    /* Initially, buf_idx indicates buf */
    buf_idx = buf;

    /* Repeat the procedure until no more is found */
    while((found = StrSearch(buf_idx, pcString1)) != NULL) {
      /* If the string is succesfully found, then do the trick */
      /* Cut the string by set *found = null */
      *found = '\0';

      /* Print the cut string */
      printf("%s", buf_idx);

      /* Print the replacing string */
      printf("%s", pcString2);

      /* Update buf_idx to repeat for the remaining part */
      buf_idx = found + pcString1_len;
    }

    /* Print the remaining string */
    printf("%s", buf_idx);
  }

  // /* If the last line doesn't end with newline character, */
  // if(buf_idx[StrGetLength(buf_idx) - 1] != '\n')
  //   /* then print newline character forcibly */
  //   printf("\n");

  return TRUE;
}
/*-------------------------------------------------------------------*/
/* DoDiff()
   Your task:
   1. Do argument validation 
     - file name length is no more than 1023
     - If a command-line argument is too long, 
       print out "Error: argument is too long" to stderr

   2. Open the two files
      - The name of files are given by two parameters
      - If you fail to open either file, print out error messsage
      - Error message: "Error: failed to open file [filename]\n"
      - Error message should be printed out to stderr

   3. Read the each line from each file
      - If you encounter a line larger than 1023 bytes, 
        print out "Error: input line [filename] is too long" 
      - Error message should be printed out to stderr

   4. Compare the two files (file1, file2) line by line 

   5. Print out any different line with the following format
      file1@linenumber:file1's line
      file2@linenumber:file2's line

   6. If one of the files ends earlier than the other, print out an
      error message "Error: [filename] ends early at line XX", where
      XX is the final line number of [filename].

   NOTE: If there is any problem, return FALSE; if not, return TRUE  */
/*-------------------------------------------------------------------*/
int
DoDiff(const char *file1, const char *file2)
{
  /*
   * It receives name of files to open by parameters.
   * Check the validity of file names and contents.
   * If each line of two files are unidentical,
   * then print it with corresponding line number.
   * Returns TRUE if whole procedure is successfully done,
   * otherwise return FALSE
   */
  char buf1[MAX_STR_LEN + 2];
  char buf2[MAX_STR_LEN + 2];
  int isValidArg1, isValidArg2;
  char *isRead1, *isRead2;
  int len1, len2, lineNum, comparedResult;
  int tooEarly1, tooEarly2;
  int isTooLong1, isTooLong2;
  FILE *fp1, *fp2;

  /* Check the validity of arguments */
  isValidArg1 = ArgumentCheck(file1);
  isValidArg2 = ArgumentCheck(file2);

  /* If argument's length exceeds 1023 bytes, raise error */
  if(!isValidArg1 || !isValidArg2)
    return FALSE;

  /* Open files */ 
  fp1 = fopen(file1, "r");
  fp2 = fopen(file2, "r");

  /* If either file is failed to open, raise error */
  if(!fp1 || !fp2)
  {
    fprintf(stderr, "Error: failed to open file %s\n", file1);
    return FALSE;
  }
  

  /* lineNum initialized to 0 */
  lineNum = 0;

  /* Read the line by line from stdin */
  while (1) {
    /* Increase lineNum */
    lineNum++;

    isRead1 = fgets(buf1, sizeof(buf1), fp1);
    isRead2 = fgets(buf2, sizeof(buf2), fp2);

    /* If either are exhausted simultaneously, break the while loop */
    if((!isRead1) && (!isRead2))
      break;

    /* Get length of each buf */
    len1 = StrGetLength(buf1);
    len2 = StrGetLength(buf2);

    /* Check if one ends earlier than the other */
    tooEarly1 = (!isRead1) && isRead2;
    tooEarly2 = isRead1 && (!isRead2);

    /* If one ends earlier than the other, raise error */
    if(tooEarly1 || tooEarly2) {
      if(tooEarly1)
        fprintf(stderr, "Error: %s ends early at line %d\n", file1, lineNum - 1);

      if(tooEarly2)
        fprintf(stderr, "Error: %s ends early at line %d\n", file2, lineNum - 1);

      return FALSE;
    }

    /* check input line length */
    isTooLong1 = (len1 > MAX_STR_LEN);
    isTooLong2 = (len2 > MAX_STR_LEN);

    /* If either is too long, raise error */
    if (isTooLong1 || isTooLong2) {
      fprintf(stderr, "Error: input line %s is too long\n", file1);
      return FALSE;
    }
    
    /* Compare those strings */
    comparedResult = StrCompare(buf1, buf2);
    
    /* If two strings are unidentical, print difference */
    if(comparedResult) {
      printf("%s@%d:%s", file1, lineNum, buf1);

      /* If the last line doesn't end with newline character, */
      if(buf1[StrGetLength(buf1) - 1] != '\n') {\
        /* then print newline character forcibly */
        printf("\n");
      }

      printf("%s@%d:%s", file2, lineNum, buf2);

      /* If the last line doesn't end with newline character, */
      if(buf2[StrGetLength(buf2) - 1] != '\n') {\
        /* then print newline character forcibly */
        printf("\n");
      }
    }
  }

  return TRUE;
}
/*-------------------------------------------------------------------*/
/* CommandCheck() 
   - Parse the command and check number of argument. 
   - It returns the command type number
   - This function only checks number of argument. 
   - If the unknown function is given or the number of argument is 
   different from required number, this function returns FALSE.
   
   Note: You SHOULD check the argument rule later                    */
/*-------------------------------------------------------------------*/ 
int
CommandCheck(const int argc, const char *argv1)
{
  int cmdtype = INVALID;
   
  /* check minimum number of argument */
  if (argc < 3)
    return cmdtype;
   
  /* check command type */ 
  if (strcmp(argv1, FIND_STR) == 0) {
    if (argc != 3)
      return FALSE;    
    cmdtype = FIND;       
  }
  else if (strcmp(argv1, REPLACE_STR) == 0) {
    if (argc != 4)
      return FALSE;
    cmdtype = REPLACE;
  }
  else if (strcmp(argv1, DIFF_STR) == 0) {
    if (argc != 4)
      return FALSE;
    cmdtype = DIFF;
  }
   
  return cmdtype;
}
/*-------------------------------------------------------------------*/
int 
main(const int argc, const char *argv[]) 
{
  int type, ret;
   
  /* Do argument check and parsing */
  if (!(type = CommandCheck(argc, argv[1]))) {
    fprintf(stderr, "Error: argument parsing error\n");
    PrintUsage(argv[0]);
    return (EXIT_FAILURE);
  }
   
  /* Do appropriate job */
  switch (type) {
  case FIND:
    ret = DoFind(argv[2]);
    break;
  case REPLACE:
    ret = DoReplace(argv[2], argv[3]);
    break;
  case DIFF:
    ret = DoDiff(argv[2], argv[3]);
    break;
  } 

  return (ret)? EXIT_SUCCESS : EXIT_FAILURE;
}