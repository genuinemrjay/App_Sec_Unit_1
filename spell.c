/****************************************************************************
 * spell.c
 *
 * Application Security, Assignment 1
 *
 * Adapted from code written by Ben Halperin
 ***************************************************************************/
#include "dictionary.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <sys/stat.h>
/**
 * Loads dictionary into memory.  Returns true if successful else false.
 */
bool load_dictionary(const char* dictionary_file, hashmap_t hashtable[]) {

  // check filename length
  if (strlen(dictionary_file) > 35){fputs ("File error",stderr); exit (1);}

  // variables
  FILE* fp;
  long lSize;
  char * buffer;
  node * new_node;
  size_t result;
  char word[LENGTH];
  int index = 0;

  // open file
  fp = fopen(dictionary_file, "r");

  // return false if file opening failed
  if (fp == NULL) {fputs ("File error",stderr); exit (1);}

  // obtain file size:
  fseek (fp , 0 , SEEK_END);
  lSize = ftell (fp);
  rewind (fp);

  // allocate memory to contain the whole file:
  buffer = malloc (sizeof(char)*lSize);
  if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}

  // copy the file into the buffer:
  result = fread (buffer,1,lSize,fp);
  if (result != lSize) {fputs ("Reading error",stderr); exit (3);}

  // close the file
  fclose(fp);

  // initialize null values in hash table
  for(int i = 0; i < HASH_SIZE; i++) {
      hashtable[i] = NULL;
  }

  // load words from file into the hashtable
  for (int i = 0; i < lSize; i++){

    // character
    char c = (char)buffer[i];

    if (index <= LENGTH) {
      // if valid character value
      if (isalpha(c) || c == '\''){
        // append character to word
          word[index] = tolower(c);
          index++;
      }

      // if a new line or carriage return
      else if (c == '\n' || c == '\r') {
        // add null terminate on word
        word[index] = '\0';
        // allocate memory
        new_node = malloc (sizeof(char*)*LENGTH+1);
        //new_node->next = malloc (sizeof(char)*LENGTH+1);
        // null ptr to next
        new_node->next = NULL;
        // copy word value to new node
        strncpy(new_node->word, word, (LENGTH+1));
        // get bucket value of word
        int bucket = hash_function(new_node->word);
        // if the first node added
        if (hashtable[bucket] == NULL) {
            hashtable[bucket] = new_node;
        }
        // or add to next node
        else {
            new_node->next = hashtable[bucket];
            hashtable[bucket] = new_node;
        }
        // reset index
        index = 0;
      }
    }
    else {
      index = 0;
    }
  }
  // free memory
  free (buffer);
  // return true
  return true;
}
/**
 * Returns true if word is in dictionary else false.
 */
bool check_word(const char* word, hashmap_t hashtable[]){

    // word and word length variables
    int word_len = strlen(word);
    char word_lwr[LENGTH];

    // return false if word longer than max allowed
    if (word_len > LENGTH){
      return false;
    }

    for (int i = 0; i <= word_len; i++) {

      if (isalpha(word[i])){
        word_lwr[i] = tolower(word[i]);
      }
      else if (isdigit(word[i])){
        return false;
      }
      else if (word[i] == ' '){
        return false;
      }
    }
    // append null
    word_lwr[word_len] = '\0';
    // get bucket value of word
    int bucket = hash_function(word_lwr);
    // cursor set to first node in bucket
    node* cursor = hashtable[bucket];
    // compare each word stored in each node to word_lwr
    while (cursor != NULL){
        // word is the same, return true
        if (strcmp(word_lwr, cursor->word) == 0){
            return true;
        }
        // move cursor to next node
        cursor = cursor->next;
      }
      return false;
  }
/**
 * Array misspelled is populated with words that are misspelled. Returns the length of misspelled.
 */
int check_words(FILE* fp, hashmap_t hashtable[], char * misspelled[]) {

    // return false if file opening failed
    if (fp == NULL) {fputs ("File error",stderr); exit (1);}

    // variables
    long lSize;
    char * buffer;
    size_t result;
    int index = 0;

    // obtain file size:
    fseek (fp , 0 , SEEK_END);
    lSize = ftell (fp);
    rewind (fp);

    // allocate memory to contain the whole file:
    buffer = malloc (sizeof(char)*lSize);
    if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}

    // copy the file into the buffer:
    result = fread (buffer,1,lSize,fp);
    if (result != lSize) {fputs ("Reading error",stderr); exit (3);}

    // close the file
    fclose(fp);

    int num_misspelled = 0;
    char word[LENGTH+1];

    // for each character in the file
    for (int i = 0; i < lSize; i++){

      // character
      char c = (char)buffer[i];

      if (isalpha(c) || ispunct(c) || isdigit(c)){
        if (index <= LENGTH){
          word[index] = c;
          index++;
        }
        else{
          index = 0;
        }
      }

      else {
        // remove ending punctuation
        if (ispunct(word[index -1])){
          word[index -1] = '\0';
        }
        else {
          word[index] = '\0';
        }
        // check spelling
        bool misspelled = check_word(word, hashtable);
        // print misspelled word
        if (misspelled == false){
            printf("%s\n", word);
            // increment number misspelled
            num_misspelled++;
        }
        index = 0;
      }
    }
    // free memory
    free (buffer);
    // return number misspelled
    return num_misspelled;
  }

