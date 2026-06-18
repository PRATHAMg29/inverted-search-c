# Inverted Search using C

## Overview

Developed an Inverted Search application in C to efficiently search words across multiple text files. The application creates an indexed database using Hashing and Linked Lists, enabling faster retrieval of words, the files in which they occur, and their occurrence count. The project also supports saving the database to a backup file and rebuilding it later through an update operation.

## Features

* Validate input text files
* Create database from multiple files
* Search for a word across all indexed files
* Display complete database
* Save database to a backup file
* Update database from a saved backup file
* Hash table based indexing for efficient search
* Word occurrence tracking across multiple files

## Technologies & Concepts Used

* C Programming
* Hashing
* Linked Lists
* Dynamic Memory Allocation
* File Handling
* Structures
* Functions
* Command Line Arguments

## Project Structure

.
├── main.c
├── create_DB.c
├── search_DB.c
├── display_DB.c
├── save_DB.c
├── update_DB.c
├── validate.c
├── inv.h
└── sample .txt files

## Data Structure Used

Hash Table (27 Indexes)
│
▼
Main Node
(Stores Word)
│
▼
Sub Nodes
(File Name & Word Count)

Example:

hello
├── file1.txt -> 3
└── file2.txt -> 1

world
├── file1.txt -> 2
└── file3.txt -> 4

## How to Run

### Compile

gcc *.c -o inverted_search

### Execute

./inverted_search file1.txt file2.txt file3.txt

## Menu Options

1. Create Database
2. Search Database
3. Display Database
4. Save Database
5. Update Database
6. Exit
