#include "inv.h"

int main(int argc, char *argv[])
{
    file_name *file = NULL;      // stores valid files list into structure.
    file_name *uhead = NULL;     // stores updated file list.
    SubNode *subnode = NULL;     // subnode pointer.
    MainNode *mainnode = NULL;   // mainnode pointer.
    MainNode *arr[27] = {NULL};  // hash array for database.
    int create = 0, update = 0;  // flags for create and update.

    // check command line arguments.
    if(argc < 2)
    {
        printf(RED "Invalid number of arguments.\n" RESET);
        return FAILURE;
    }

    // validate and store valid files into the structure.
    if(validate(argv, &file) == SUCCESS)
    {
        file_name *temp = file;

        printf(GREEN "Files stored into list are : " RESET);

        // print valid files list.
        while(temp != NULL)
        {
            printf("%s -> ", temp->fname);
            temp = temp->link;
        }

        printf("NULL\n");
    }
    while(1)
    {
        // menu for user.
        printf("\n---------------INVERTED SEARCH MENU---------------\n");
        printf("1.Create Database\n");
        printf("2.Search Database\n");
        printf("3.Display Database\n");
        printf("4.Save Database\n");
        printf("5.Update Database\n");
        printf("6.Exit\n");
        printf("--------------------------------------------------\n");
        printf("Enter your choice : ");
        int choice;
        scanf("%d", &choice); // take the user choice.
        printf("--------------------------------------------------\n");
        switch(choice)
        {
            case 1:
                // check valid files
                if(file == NULL)
                {
                    printf("No valid files found.\n");
                    break;
                }
                // prevents create again once creation is done.
                if(create == 1)
                {
                    printf("Database is already created.\n");
                    break;
                }
                // remove duplicate files after updation.
                if(update == 1)
                {
                    delete_duplicates(&file, uhead);
                }
                // create database.
                if(create_database(arr, file) == SUCCESS)
                {
                    create = 1;

                    printf("\n--------------------------------------------------\n");
                    printf("Database created successfully.\n");
                    printf("--------------------------------------------------\n");
                }
                else
                {
                    printf("\n--------------------------------------------------\n");
                    printf("Database creation failed.\n");
                    printf("--------------------------------------------------\n");
                }
                break;

            case 2:
            {
                // check database exists or not.
                if(create == 0 && update == 0)
                {
                    printf("Database not created yet.\n");
                    printf("First create or update database.\n");
                    break;
                }
                char word[100];
                // get search word from user.
                printf("Enter the word to search : ");
                scanf("%s", word);
                // search word in database.
                if(search_database(arr, word) == SUCCESS)
                {
                    printf("\n--------------------------------------------------\n");
                    printf("Search operation successful.\n");
                    printf("--------------------------------------------------\n");
                }
                else
                {
                    printf("\n--------------------------------------------------\n");
                    printf("Word not found.\n");
                    printf("--------------------------------------------------\n");
                }
                break;
            }

            case 3:
                // check database exists or not.
                if(create == 0 && update == 0)
                {
                    printf("Database not created yet.\n");
                    printf("First create or update database.\n");
                    break;
                }
                // display database to user.
                if(display_database(arr, file) == SUCCESS)
                {
                    printf("\n--------------------------------------------------\n");
                    printf("Display operation successful.\n");
                    printf("--------------------------------------------------\n");
                }
                break;

            case 4:
                // check database exists or not.
                if(create == 0 && update == 0)
                {
                    printf("Database not created yet.\n");
                    printf("First create or update database.\n");
                    break;
                }
                // save database into file.
                if(save_database(arr, file) == SUCCESS)
                {
                    printf("\n--------------------------------------------------\n");
                    printf("Save operation successful.\n");
                    printf("--------------------------------------------------\n");
                }
                else
                {
                    printf("\n--------------------------------------------------\n");
                    printf("Database saving failed.\n");
                    printf("--------------------------------------------------\n");
                }
                break;

            case 5:
                // prevent update after create.
                if(create == 1)
                {
                    printf("Database is already created.\n");
                    break;
                }
                // update database from backup file.
                if(update_database(arr, &update, &uhead) == SUCCESS)
                {
                    update = 1;

                    printf("\n--------------------------------------------------\n");
                    printf("Update operation successful.\n");
                    printf("--------------------------------------------------\n");
                }
                else
                {
                    update = 0;

                    printf("\n--------------------------------------------------\n");
                    printf("Database updation failed.\n");
                    printf("--------------------------------------------------\n");
                }
                break;

            case 6:
                return SUCCESS; // exit from program.

            default:
                printf("\n--------------------------------------------------\n");
                printf("Enter proper choice.\n");
                printf("--------------------------------------------------\n");
        }
    }
}

int delete_duplicates(file_name **head, file_name *uhead)
{
    file_name *utemp = uhead; // traverse through updated file list.
    // traverse updated files.
    while(utemp != NULL)
    {
        file_name *temp = *head; // original file list.
        file_name *prev = NULL;  // previous node.
        // search duplicate file.
        while(temp != NULL)
        {
            // duplicate found.
            if(strcmp(temp->fname, utemp->fname) == 0)
            {
                // delete first node.
                if(prev == NULL)
                {
                    *head = temp->link;
                }
                else
                {
                    // delete middle/end node.
                    prev->link = temp->link;
                }
                free(temp); // free deleted node.
                break;
            }
            prev = temp;       // move prev.
            temp = temp->link; // move temp.
        }
        utemp = utemp->link; // move the updated list.
    }
    return SUCCESS;
}