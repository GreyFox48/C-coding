#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

struct dict_t {
        int nval;
        int max;
        char **word;
};

enum {INIT = 1, GROW = 2};

struct dict_t *create_dictionary(FILE *file);
void free_dict(struct dict_t *dict);
int find_word(struct dict_t *dict, char *input);
char *find_play(struct dict_t *dict, char *input);
int check_play(char *dict, char *input);
int word_value(char *word);

#define LEN 128

int main(void)
{
        FILE *fp = fopen("scrabble.txt", "r");
        struct dict_t *dict = create_dictionary(fp);
        char input[LEN];
        int temp = 0;
        char *word_temp = NULL;
        
        while (1) {
                printf("Scrabble Menu\n");
                printf("\t1. Determine if a word exits in the scrabble dictiontary.\n");
                printf("\t2. Determine the best play from given tiles.\n");
                printf("\t3. Quit the program.\n");
                printf("Enter an option [1, 2, 3]: ");
                fgets(input, LEN, stdin);
                temp = atoi(input);

                switch (temp) {
                case 1: /* find word option */
                        printf("Enter the word to search for (lower case characters only): ");
                        fgets(input, LEN, stdin);
                        /* remove the newline character */
                        input[strcspn(input, "\n")] = 0;
                        temp = find_word(dict, input);
                        if (temp == -1) {
                                printf("The word does not exist in the dictionary.\n");                                
                        } else {
                                printf("%s exist in the dictionary.\n", input);
                        }
                        break;
                case 2: /* determine the best play */
                        printf("Enter tiles that you have (lower case characters only): ");
                        fgets(input, LEN, stdin);
                        /* remove the newline character */
                        input[strcspn(input, "\n")] = 0;
                        word_temp = find_play(dict, input);
                        if (word_temp) {
                                printf("%s is the best play (for %d points)\n", word_temp, word_value(word_temp));                                
                        } else {
                                printf("No play can be made from these tiles\n");
                        }
                        break;
                case 3: /* quit option */
                        printf("Goodbye!\n");
                        free_dict(dict);
                        fclose(fp);
                        return 0;
                        break;
                default:
                        printf("%d is not a valid option.\n", temp);
                        break;
                }
        }

        return 0;
}

/** 
 * Populates a dict_t structure, using the listed words provided by the given file
 * @param file The file with the words to be stored
 * @return a populated dict_t structure with information from file
 */
struct dict_t *create_dictionary(FILE *file) 
{
        int i = 0;
        char buff[LEN];
        struct dict_t *dict = malloc(sizeof(struct dict_t));
        assert(dict);
        dict->nval = INIT;
        dict->max = INIT;
        dict->word = NULL;

        while (fgets(buff, LEN, file)) {
                if (!dict->word) {
                        dict->word = malloc(sizeof(char *) * INIT);
                        assert(dict->word);
                } else if (dict->nval > dict->max) {
                        dict->word = realloc(dict->word, GROW * dict->max * sizeof(char *));
                        assert(dict->word);
                        dict->max *= GROW;
                }
                dict->word[i] = malloc((strlen(buff) + 1) * sizeof(char));
                strncpy(dict->word[i], buff, strlen(buff) + 1);
                /* by finding # of characters that are not \n, finds index of \n */
                dict->word[i][strcspn(dict->word[i], "\n")] = 0;
                dict->nval++;
                i++;
        }
        /* while loop leaves nval off by +1 */
        dict->nval--;

        return dict;
}

/**
 * Free a dict_t structure, and all its elements
 * @param dict the structure to be freed
 */
void free_dict(struct dict_t *dict)
{
        int i;

        for(i = 0; i < dict->nval; i++) {
                free(dict->word[i]);
        }
        free(dict->word);
        free(dict);

        return;
}

/**
 * Determines if a word exists in a given dict_t.  Utilizes
 * a binary search
 * @param dict the dict_t structure to be searched
 * @param input the word to look for in the given dict_t
 * @return the dict->word index of input on success, 
 * -1 on failure
 */
int find_word(struct dict_t *dict, char *input)
{
        int max = dict->nval - 1;
        int min = 0;
        int size = strlen(input);
        int cmp, i;

        while (max >= min) {
                i = (max + min) / 2;
                cmp = strncmp(dict->word[i], input, size);
                if (cmp == 0 && (size == strlen(dict->word[i]))) {
                        return i;                
                } if (cmp > 0 || (cmp == 0 && strlen(dict->word[i]) > size)) {
                        max = i - 1;
                } else {
                        min = i + 1;
                }
        }

        return -1;
}

/**
 * Searches through a dict_t struct to determine the best play from the sereis
 * of characters input
 * @param dict the dict_t structures to be searched through
 * @param input the series of characters to be checked
 * @return pointer to the best play
 */
char *find_play(struct dict_t *dict, char *input) 
{
        int i, temp;
        int max_val = 0;
        char *play = NULL;

        for (i = 0; i < dict->nval; i++) {
                /* check to ensure the word can be played from input */
                if (check_play(dict->word[i], input)) {
                        temp = word_value(dict->word[i]);
                        if (max_val < temp) {
                                max_val = temp;
                                play = dict->word[i];
                        }                        
                }
        }

        return play;
}

/**
 * Checks a given word against the characters of input to ensure it can be played
 * @param dict the word to check for
 * @param input the series of characters to check against
 * @return 0 if play is not possible, 1 if it is
 */
int check_play(char *dict, char *input)
{
        char word[LEN];
        /* copy to prevent changing word in dictionary */
        strncpy(word, dict, strlen(dict));
        int word_size = strlen(dict);
        int i, j;

        /* if word is too large to even create, instantly fail */
        if (strlen(dict) > strlen(input)) {
                return 0;
        }

        for (i = 0; i < strlen(input); i++) {
                for (j = 0; j < word_size; j++) {
                        if (input[i] == word[j]) {
                                word[j] = 0;
                                break;
                        }
                }
        } 

        for (i = 0; i < word_size; i++) {
                if (word[i] > 0) {
                        return 0;
                }
        }

        return 1;
}

/**
 * Determines the value of a word against scrabble characters values
 * @param word the word to determine the value of
 * @return the value of the word 
 */
int word_value(char *word)
{
        int value = 0;
        int i;
        int charval[26] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

        for (i = 0; i < strlen(word); i++) {
                value += charval[word[i] - 'a'];
        }

        return value;

}
