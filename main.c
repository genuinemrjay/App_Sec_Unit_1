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
#define TESTLIST "test1.txt"

int main(int argc, char* argv[]){
  // check for correct number of args
   if (argc != 2 && argc != 3){
       printf("Usage: spell_check <dictionary_file> <text_file>\n");
       return 1;
   }
  // initialize hashmap and load dictionary values
  hashmap_t hashtable[HASH_SIZE];
  //
  if (load_dictionary(argv[1], hashtable)) {

    // initialize mispelled
    char *misspelled[MAX_MISSPELLED];

    //open test file and check spelling
    FILE *fp = fopen(argv[2], "r");
    int num_misspelled = check_words(fp, hashtable, misspelled);
    printf("%d total misspelled words \n", num_misspelled);

    // free memory of hashtable
    for (int i = 0; i < HASH_SIZE;i++) {
         node* cursor = hashtable[i];
         while (cursor != NULL){
             // use temp pointer, move cursor to the next node and free memory
             node* temp = cursor;
             cursor = cursor->next;
             free(temp);
         }
     }
    free(misspelled[MAX_MISSPELLED]);
  }
}

