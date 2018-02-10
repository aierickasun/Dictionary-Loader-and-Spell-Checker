/**
 * Implements a dictionary's functionality.
 */

#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "dictionary.h"


// Holds the number of words
int count = 0;
//Holds the root of the trie.
trie* head;

//DEBUG:


/**
 * Returns true if word is in dictionary else false.
 */
bool check(const char *word)
{
    int i = 0;
    int index = 0;
    trie* traverse = head;

    while(word[i]!=' ' && word[i]!='\0' && word[i]!='\n'){
        index = (word[i]!='\'') ? tolower(word[i])-97 : 26 ;

        if(traverse->letters[index]==NULL){
            return false;
        }
        
        traverse = traverse->letters[index];
        i++;
    }
    return traverse->isEnd;
}
/* 
    Adds a String into the Trie.
*/
void add(char *current){
    trie* traverse = head;
    int i, index;
    i = index = 0;
    if(isalpha(current[i])){
        while(current[i]!=' ' && current[i]!='\0' && current[i]!='\n'){
            index = (current[i]!='\'') ? tolower(current[i])-97 : 26 ;
            if(traverse->letters[index]==NULL){
                traverse->letters[index] = malloc(sizeof(trie));
                if(traverse->letters[index] == NULL){
                    fprintf(stderr, "Failed to allocate memory\n");
                  //  return 2;
                }
            }
            traverse = traverse->letters[index];
            i++;
        }
        traverse->isEnd = true;
        count++;
    }
}
/**
 * Loads dictionary into memory. Returns true if successful else false.
 */
bool load(const char *dictionary)
{
    FILE *fin = fopen(dictionary, "r");
    head = malloc(sizeof(trie));
    if(head==NULL){
        fprintf(stderr, "Couldn't open %s\n", dictionary);
        return 2;
    }
    char current[LENGTH];
    if(fin==NULL){
        fprintf(stderr, "Couldn't open %s\n", dictionary);
        return 2;
    }
    while(fgets(current, LENGTH, fin)!=NULL){
        add(current);
    }
    fclose(fin);
    return true;
}

/**
 * Returns number of words in dictionary if loaded else 0 if not yet loaded.
 */
unsigned int size(void)
{
    return (count!=-1)? count : 0;
}

bool isAllNull(trie* cur){
    for(int i = 0; i < 27; i++){
        if(cur->letters[i]!=NULL){
            return false;
        }
    }
    return true;
}


/**
 * Recursively removes a leaf.
 */
void travRemove(trie* cur){
    if(isAllNull(cur) == true){
        free(cur);
    } else {
        for(int i = 0; i < 27; i++){
            if(cur->letters[i]!=NULL){
                travRemove(cur->letters[i]);
            }
        }
        free(cur);
    }
}

/**
 * Unloads dictionary from memory. Returns true if successful else false.
 */
bool unload(void)
{
    travRemove(head);
    return true;
}
