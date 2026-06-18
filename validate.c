#include "inv.h"

int validate(char *argv[],file_name **file)
{
    int i = 1;
    // traverse through command line arguments.
    while(argv[i])
    {
next:
        // check NULL argument.
        if(argv[i] == NULL)
        {
            break;
        }
        // check .txt extension.
        char *p = strstr(argv[i],".");
        if(p == NULL || (strcmp(p,".txt") != 0))
        {
            printf(RED "Enter a proper file name for %s.\n" RESET, argv[i]);
            i++;
            goto next;
        }
        else
        {
            // open the file.
            FILE *fptr = fopen(argv[i],"r");
            // file not present.
            if(fptr == NULL)
            {
                printf(RED "%s file not present in directory.\n" RESET, argv[i]);
                i++;
                goto next;
            }
            // duplicate file validation.
            if(check_duplicate_file(argv[i], *file) == SUCCESS)
            {
                // insert first node.
                if(*file == NULL)
                {
                    file_name *newnode = (file_name *)malloc(sizeof(file_name));
                    newnode->link = NULL;
                    newnode->fname = argv[i];
                    *file = newnode;
                }
                else
                {
                    // create new node.
                    file_name *newnode = (file_name *)malloc(sizeof(file_name));
                    newnode->link = NULL;
                    newnode->fname = argv[i];
                    file_name *temp = *file;
                    // move to last node.
                    while(temp->link != NULL)
                    {
                        temp = temp->link;
                    }
                    temp->link = newnode; // attach node.
                }
            }
        }
        i++; // move to next argument
    }
    return SUCCESS;
}

int check_duplicate_file(char arr[],file_name *file)
{
    // empty file list.
    if(file == NULL)
        return SUCCESS;
    file_name *temp = file; // traversal pointer.
    // search duplicate filename.
    while(temp != NULL)
    {
        if(strcmp(temp->fname, arr) == 0)
        {
            printf(BCYAN "%s file name already exists in list.\n" RESET, arr);
            return FAILURE;
        }
        temp = temp->link; // move next node.
    }
    return SUCCESS;
}