## Overview

The main program, `speller.c`, is a program written in C that takes a custom dictionary[if not default] to spellcheck a text.	


## dictionary.c

The program `dictionary.c` loads a dictionary of words into a trie, which is an search tree that dynamically stores keys. When reTRIEving a word from the trie, the running time is the length of the key, which is very small in comparison to other sorting algorithms such as bubble, insertion, selection, etc., which are a function of the total number of keys in the data set. The idea is to start with an array of 26 nodes to represent each alphabet. During the loading of a word, everytime the corresponding numerical convertion of a letter of the word's index into an array of node is uninitialized, initialize that index by setting it's value to point to another array of 26 nodes. 

## speller.c

The program `speller.c` takes in 1 optional[a custom dictionary to load] and 1 necessary[the text to check] as the argv arguments. It loads the dictionary into a trie and compares each word of the text by seeing if it's in the trie.