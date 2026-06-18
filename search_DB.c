#include "inv.h"

int search_database(MainNode **arr,char *word)
{
    // check if database empty.
    if(arr == NULL)
    {
        printf("Database is empty.\n");
        return FAILURE;
    }
    int index;
    // calculate index for alphabet.
    if(isalpha(word[0]))
    {
        index = tolower(word[0]) - 'a';
    }
    else
    {
        index = 26; // special character index.
    }
    // check if index empty.
    if(arr[index] == NULL)
    {
        printf("Word not found.\n");
        return FAILURE;
    }
    MainNode *main_temp = arr[index];
    // search word in mainnode.
    while(main_temp != NULL)
    {
        // if word found.
        if(strcmp(main_temp->word,word) == 0)
        {
            printf("\nWord : %s\n",main_temp->word);
            printf("File count : %d\n",main_temp->file_count);
            SubNode *sub_temp = main_temp->link; // traverse through subnode.

            // display the file details.
            while(sub_temp != NULL)
            {
                printf("File : %s  |  Word Count : %d\n",sub_temp->file_name,sub_temp->word_count);
                sub_temp = sub_temp->sub_link;
            }
            return SUCCESS;
        }
        main_temp = main_temp->main_link; // move mainnode.
    }
    // if word not found.
    printf("Word not found.\n");
    return FAILURE;
}