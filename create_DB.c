#include "inv.h"

int create_database(MainNode **arr,file_name *file)
{
    file_name *temp = file; 

    // traverse through file list.
    while(temp != NULL)
    {
        FILE *fptr = fopen(temp->fname,"r"); // open the file.
        // read words till the end of file.
        while(feof(fptr) == 0)
        {
            char str[100];
            fscanf(fptr,"%s",str); // read word.
            int index;
            // calculate index for alphabets.
            if(isalpha(str[0]))
            {
                index = tolower(str[0]) - 'a';
            }
            else
            {
                index = 26; // for special characters index.
            }
            // insert if index empty.
            if(arr[index] == NULL)
            {
                MainNode *node = insert_first_mainnode(&arr[index],str);
                if(node != NULL)
                {
                    insert_first_subnode(node,temp->fname);
                }
            }
            else
            {
                MainNode *main_temp = arr[index];
                MainNode *prev = NULL;
                // search word in mainnode.
                while(main_temp != NULL)
                {
                    //if word already exists.
                    if(strcmp(main_temp->word,str) == 0)
                    {
                        insert_first_subnode(main_temp,temp->fname);
                        break;
                    }
                    prev = main_temp;
                    main_temp = main_temp->main_link;
                }
                // insert new word if not found.
                if(main_temp == NULL)
                {
                    MainNode *newnode = insert_first_mainnode(&arr[index],str);

                    if(newnode != NULL)
                    {
                        insert_first_subnode(newnode,temp->fname);
                    }
                }
            }
        }
        fclose(fptr); // close the file.
        temp = temp->link; // move to the next file.
    }
    return SUCCESS;
}

MainNode *insert_first_mainnode(MainNode **arr,char str[])
{
    // insert when no node exists.
    if(*arr == NULL)
    {
        *arr = (MainNode *)malloc(sizeof(MainNode));
        if(*arr == NULL)
        {
            return NULL;
        }
        strcpy((*arr)->word,str); // copy the word.
        (*arr)->file_count = 0;   // initialize file count.
        (*arr)->main_link = NULL; // initialize main link.
        (*arr)->link = NULL;      // initialize sub link.
        return *arr;
    }
    else
    {
        MainNode *temp = *arr;

        // search for duplicate word.
        while(temp != NULL)
        {
            if(strcmp(temp->word,str) == 0)
            {
                return temp;
            }

            temp = temp->main_link;
        }
        // create new mainnode.
        MainNode *new = (MainNode *)malloc(sizeof(MainNode));
        if(new == NULL)
            return NULL;
        strcpy(new->word,str); // copy the word.
        new->file_count = 0;   // initialize count.
        new->link = NULL;      // initialize subnode link.

        // insert at beginning.
        new->main_link = *arr;
        *arr = new;
        return new;
    }
}

int insert_first_subnode(MainNode *node,char fname[])
{
    // validate mainnode.
    if(node == NULL)
        return FAILURE;

    // first subnode insertion.
    if(node->link == NULL)
    {
        SubNode *newnode = (SubNode *)malloc(sizeof(SubNode));
        if(newnode == NULL)
            return FAILURE;
        strcpy(newnode->file_name,fname); // copy the filename.
        newnode->word_count = 1; // initialize word count.
        newnode->sub_link = NULL; // initialize link.
        node->link = newnode;
        node->file_count++; // increment file count.
        return SUCCESS;
    }
    else
    {
        SubNode *temp = node->link;

        // check if filename already exists.
        while(temp != NULL)
        {
            if(strcmp(temp->file_name,fname) == 0)
            {
                temp->word_count++; // increment word count.
                return SUCCESS;
            }
            temp = temp->sub_link;
        }

        // create new subnode.
        SubNode *newnode = (SubNode *)malloc(sizeof(SubNode));
        if(newnode == NULL)
            return FAILURE;
        strcpy(newnode->file_name,fname); // copy the filename.
        newnode->word_count = 1; // initialize count.

        // insert at beginning.
        newnode->sub_link = node->link;
        node->link = newnode;
        node->file_count++; // increment file count.
        return SUCCESS;
    }
}