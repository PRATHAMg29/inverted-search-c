#ifndef INV_H
#define INV_H

//HEADER FILES
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdarg.h>

//DEFINE MACROS
#define SUCCESS 1
#define FAILURE 0

#define RED       "\033[31m"  //define a macro name for colors
#define RESET     "\033[0m"
#define GREEN     "\033[32m"
#define BBLUE     "\033[94m"
#define BCYAN     "\033[96m"
#define BMAGENTA  "\033[95m"
#define ORANGE    "\033[38;5;208m"

//STRUCTURE FOR STORING FILE NAME
typedef struct filename
{
    char *fname;
    struct filename *link;
}file_name;

//STRUCTURE FOR SUBNODE
typedef struct sub_node
{
    char file_name[50];
    int word_count;
    struct sub_node *sub_link;
}SubNode;

//STRUCTURE FOR MAINNODE
typedef struct main_node
{
    char word[100];
    int file_count;
    SubNode *link;
    struct main_node *main_link;
}MainNode;

//FUNCTION PROTOTYPES
int validate(char *argv[],file_name **file);
int delete_duplicates(file_name **head, file_name *uhead);
int check_duplicate_file(char arr[],file_name *file);
int create_database(MainNode **arr,file_name *file);
MainNode *insert_first_mainnode(MainNode **arr,char str[]);
int insert_first_subnode(MainNode *node,char fname[]);
int search_database(MainNode **arr,char *word);
int update_database(MainNode **arr,int *updated,file_name **uhead);
void insert_flist(file_name **head, char *name);
int display_database(MainNode **arr,file_name *file);
int save_database(MainNode **arr,file_name *file);

#endif
