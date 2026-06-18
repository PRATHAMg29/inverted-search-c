#include "inv.h"

int save_database(MainNode **arr, file_name *file)
{
    char filename[50]; // store the filename.
failure:
    printf("Enter file name : ");
    scanf("%s", filename); // get filename from user.
    FILE *fp = fopen(filename, "r"); // open file in read mode.

    // check file exists and not empty
    if(fp != NULL)
    {
        fseek(fp, 0, SEEK_END); // move to end.
        long size = ftell(fp); // get file size.
        fclose(fp); // close the file.
        if(size != 0)
        {
            int option;
            printf("File is not empty\n");
            printf("1.Create new file\n");
            printf("2.Overwrite file\n");
            printf("Enter option : ");
            scanf("%d", &option);
            // enter a new filename.
            if(option == 1)
                goto failure;
        }
    }
    // open file in write mode.
    fp = fopen(filename, "w");

    // file open failure.
    if(fp == NULL)
    {
        printf("File open failed\n");
        return FAILURE;
    }

    // traverse through all array indexes.
    for(int i = 0; i < 27; i++)
    {
        MainNode *mtemp = arr[i]; // mainnode traversing.

        // traverse mainnode list.
        while(mtemp != NULL)
        {
            // write mainnode details.
            fprintf(fp, "#%d;%s;%d;",i,mtemp->word,mtemp->file_count);
            SubNode *stemp = mtemp->link; // subnode traversing.

            // write subnode details.
            while(stemp != NULL)
            {
                fprintf(fp, "%s;%d;",stemp->file_name,stemp->word_count);
                stemp = stemp->sub_link;
            }
            fprintf(fp, "#\n"); // end of one record.

            mtemp = mtemp->main_link; // move mainnode.
        }
    }
    fclose(fp); // close file.
    return SUCCESS;
}