#include "inv.h"

int update_database(MainNode **arr, int *updated, file_name **uhead)
{
    *uhead = NULL; // initialize updated file list.
    char filename[50]; // store backup filename
failure:
    printf("Enter the database name\n");
    scanf("%s", filename); // get the filename from user.
    FILE *fp = fopen(filename, "r"); // open the file in read mode.

    // validate file exists or not.
    if(fp == NULL)
    {
        printf("%s does not exist\n", filename);
        goto failure;
    }

    // check if file is empty.
    fseek(fp, 0, SEEK_END);

    if(ftell(fp) == 0)
    {
        printf("File is empty\n");
        fclose(fp);
        goto failure;
    }

    rewind(fp); // move pointer to beginning of file.
    int index; // stores hash index.

    // read backup file data.
    while(fscanf(fp, "#%d;", &index) == 1)
    {
        // create main node.
        MainNode *new = malloc(sizeof(MainNode));

        new->link = NULL;       // initialize subnode link.
        new->main_link = NULL; // initialize mainnode link.

        // read word and file count.
        fscanf(fp,"%[^;];%d;",new->word,&new->file_count);

        // insert mainnode into the array.
        if(arr[index] == NULL)
        {
            arr[index] = new;
        }
        else
        {
            MainNode *temp = arr[index];

            // move to last mainnode.
            while(temp->main_link != NULL)
            {
                temp = temp->main_link;
            }
            temp->main_link = new; // attach new node.
        }

        // create subnodes.
        for(int i = 0; i < new->file_count; i++)
        {
            SubNode *newsub = malloc(sizeof(SubNode));
            newsub->sub_link = NULL; // initialize link.

            // read filename and word count.
            fscanf(fp,"%[^;];%d;",newsub->file_name,&newsub->word_count);

            // store filename in the updated list.
            insert_flist(uhead, newsub->file_name);

            // insert subnode.
            if(new->link == NULL)
            {
                new->link = newsub;
            }
            else
            {
                SubNode *temp = new->link;

                // move to last subnode.
                while(temp->sub_link != NULL)
                {
                    temp = temp->sub_link;
                }
                temp->sub_link = newsub; // attach subnode.
            }
        }

        // skip the ending '#'
        fscanf(fp, "#\n");
    }
    fclose(fp); // close the file
    *updated = 1; // updation successful.
    return SUCCESS;
}


void insert_flist(file_name **head, char *name)
{
    file_name *temp = *head; // temp for traversing.

    // check for duplicate filename.
    while(temp != NULL)
    {
        if(strcmp(temp->fname, name) == 0)
        {
            return;
        }
        temp = temp->link;
    }

    // create new node.
    file_name *new = malloc(sizeof(file_name));

    // allocate memory for the filename.
    new->fname = malloc(strlen(name) + 1);
    strcpy(new->fname, name); // copy filename.
    new->link = NULL; // initialize link.

    // insert at last operation.
    if(*head == NULL)
    {
        *head = new;
    }
    else
    {
        temp = *head;

        // move to the last node.
        while(temp->link != NULL)
        {
            temp = temp->link;
        }
        temp->link = new; // attach new node.
    }
}