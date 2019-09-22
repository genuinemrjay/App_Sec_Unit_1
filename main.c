/****************************************************************************
 * main.c
 *
 * Application Security, Assignment 1
 *
 * Adapted from code written by Ben Halperin
 ***************************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include "dictionary.h"
#include <check.h>

//#define DICTIONARY "wordlist.txt"
#define TESTDICT "test_worlist.txt"

int main(int argc, char* argv[])
{
  // check for correct number of args
   if (argc != 2 && argc != 3){
       printf("Usage: spell_check <dictionary_file> <text_file>\n");
       return 1;
   }
  hashmap_t hashtable[HASH_SIZE];
  load_dictionary(argv[1], hashtable);
  char *misspelled[MAX_MISSPELLED];
  FILE *fp = fopen("test1.txt", "r");
  int num_misspelled = check_words(fp, hashtable, misspelled);
}
