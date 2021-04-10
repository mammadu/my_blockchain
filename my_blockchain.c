#include "my_blockchain.h"


//readline
//read a character
//combine into the return_string
//continue reading characters until read "\n"
//return return_str



char* readline()
{
    char* str = malloc(sizeof(char)); //str is malloc'd so we can free it later
    str[0] = '\0';
    char* character = malloc(sizeof(char));
    int characters_read = read(0, character, 1);
    // printf("the character is %s\n", character);
    // printf("the value of character is %d\n", character[0]);

    while (character[0] != '\n')
    {
        char* temp = str; //we make a temporay string to free everything stored at that location.
        str = combine_strings(temp, character);
        free(temp);
        // free(character);
        // char* character = malloc(sizeof(char));
        int characters_read = read(0, character, 1);
        // printf("the character is %s\n", character);
        // printf("the value of character is %d\n", character[0]);
        // printf("str is %s\n", str);
    }
    free(character);
    return str; //if no characters are passed, str == \0
}

int main()
{
    char* input = readline();    

    while(input[0] == '\0' || my_strcmp(input, "quit") != 0) 
    {
        int string_count = delimiter_count(input, ' ') + 1;
        char** string_array = split_string(input, ' ');
        // printf("string_array [%d] = %s\n", 0, string_array[0]);
        int i = 0;
        while (i < string_count)
        {
            printf("string_array [%d] = %s\n", i, string_array[i]);
            i++;
        }
        free_string_array(string_array, string_count);
        char* temp = input; //we make a temporay string to free everything stored at that location.
        free(temp);
        input = readline();
    }
    free(input);

    return 0;
}