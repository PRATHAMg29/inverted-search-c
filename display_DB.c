#include "inv.h"

int display_database(MainNode **arr,file_name *file)
{
    // check if database empty.
    if(arr == NULL)
    {
        printf("Database is empty\n");
        return FAILURE;
    }
    int count = 1;

    // display the heading.
    printf("\n----------------------------------------------------------\n");
    printf("No\tWord\tFile Count\tFile Name\tWord Count\n");
    printf("\n----------------------------------------------------------\n");

    // traverse through all array indexes.
    for(int i = 0; i < 27; i++)
    {
        // check if index not empty.
        if(arr[i] != NULL)
        {
            MainNode *main_temp = arr[i];

            // traverse through mainnode list.
            while(main_temp != NULL)
            {
                SubNode *sub_temp = main_temp->link;

                // print first subnode with word details.
                if(sub_temp != NULL)
                {
                    printf("%d\t%-10s %-14d %-17s %-5d\n", count++,main_temp->word,main_temp->file_count,sub_temp->file_name,sub_temp->word_count);
                    sub_temp = sub_temp->sub_link;
                }

                // print the remaining subnodes.
                while(sub_temp != NULL)
                {
                    printf("\t\t\t          %-17s %-5d\n",sub_temp->file_name,sub_temp->word_count);
                    sub_temp = sub_temp->sub_link;
                }
                printf("\n");
                main_temp = main_temp->main_link; // move mainnode.
            }
        }
    }
    printf("\n----------------------------------------------------------\n");
    return SUCCESS;
}