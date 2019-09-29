/****************************************************************************
 * test_main.c
 *
 * Application Security, Assignment 1
 *
 * Adapted from code written by Ben Halperin
 ***************************************************************************/
#include <check.h>
#include "dictionary.h"
#include <stdlib.h>
#include <stdio.h>

#define DICTIONARY "wordlist.txt"
#define TESTDICT "test_worlist.txt"

START_TEST(test_dictionary_normal)
{
    // initialize the hashtable
    hashmap_t hashtable[HASH_SIZE];

    // check to load dictionary function
    ck_assert(load_dictionary(DICTIONARY, hashtable));

    // test words and buckets for table testing
    const char* test_word_1 = "characterizations";
    const char* test_word_2 = "whiz";
    const char* test_word_3 = "demilitarized";
    int bucket_1 = hash_function(test_word_1);
    int bucket_2 = hash_function(test_word_2);
    int bucket_3 = hash_function(test_word_3);

    // Here we can test if certain words ended up in certain buckets
    // to ensure that our load_dictionary works as intended. I leave
    // this as an exercise.
    for (int i = 0; i < HASH_SIZE;i++) {
         node* cursor = hashtable[i];
         while (cursor != NULL){
             if (cursor->word == test_word_1){
               ck_assert_int_eq(bucket_1 , i);
             }
             else if (cursor->word == test_word_2){
               ck_assert_int_eq(bucket_2 , i);
             }
             else if (cursor->word == test_word_3){
               ck_assert_int_eq(bucket_3 , i);
             }
             cursor = cursor->next;
         }
     }
}
END_TEST

START_TEST(test_check_word_normal)
{
  // initialize the hashtable
    hashmap_t hashtable[HASH_SIZE];

    // load dictionary function
    load_dictionary(DICTIONARY, hashtable);

    // test for a correct word
    const char* correct_word = "Justice";
    ck_assert(check_word(correct_word, hashtable));

    // test for punctuation in the middle of a word
    const char* punctuation_word_2 = "pl.ace";
    ck_assert(!check_word(punctuation_word_2, hashtable));

    // test for punctuation at the beginning of word
    const char* question_mark = "??????ue";
    ck_assert(!check_word(question_mark, hashtable));

    // test word word longer than allowed
    const char* too_long = "pneumonoultramicroscopicsilicovolcanoconiosisandstuff";
    ck_assert(!check_word(too_long, hashtable));

    // test for buffer overflow on word
    const char* overflow = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa";
    ck_assert(!check_word(overflow, hashtable));
}
END_TEST

START_TEST(test_check_words_normal)
{
    hashmap_t hashtable[HASH_SIZE];
    load_dictionary(DICTIONARY, hashtable);
    char* expected[3];
    expected[0] = "sogn";
    expected[1] = "skyn";
    expected[2] = "betta";
    char *misspelled[MAX_MISSPELLED];
    FILE *fp = fopen("test1.txt", "r");
    int num_misspelled = check_words(fp, hashtable, misspelled);
    ck_assert_int_eq(num_misspelled , 3);
}
END_TEST

START_TEST(test_check_words)
{
    hashmap_t hashtable[HASH_SIZE];
    load_dictionary(DICTIONARY, hashtable);
    char* expected[6];
    expected[0] = "t3st";
    expected[1] = "t.est";
    expected[2] = "#tests";
    expected[3] = "@test";
    expected[4] = "0f";
    expected[5] = "Thi$";
    char *misspelled[MAX_MISSPELLED];
    FILE *fp = fopen("test_worlist.txt", "r");
    int num_misspelled = check_words(fp, hashtable, misspelled);
    ck_assert_int_eq(num_misspelled , 6);
}
END_TEST

Suite *
check_word_suite(void)
{
    Suite * suite;
    TCase * check_word_case;
    suite = suite_create("check_word");
    check_word_case = tcase_create("Core");
    tcase_add_test(check_word_case, test_dictionary_normal);
    tcase_add_test(check_word_case, test_check_word_normal);
    tcase_add_test(check_word_case, test_check_words);
    tcase_add_test(check_word_case, test_check_words_normal);
    suite_add_tcase(suite, check_word_case);

    return suite;
}

int
main(void)
{
    int failed;
    Suite *suite;
    SRunner *runner;

    suite = check_word_suite();
    runner = srunner_create(suite);
    srunner_run_all(runner, CK_NORMAL);
    failed = srunner_ntests_failed(runner);
    srunner_free(runner);
    return (failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE);
}

