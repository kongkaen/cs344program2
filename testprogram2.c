/*
Assignment 2: File & Directories
Natthaphong Kongkaew
CS 344 Fall 2020
Oregon State University
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <fcntl.h>


#define PREFIX "movies_"
#define SUFFIX "csv"
#define SIZE 25

/* Part of the following function are from my previous assignment */

/* struct for movie information */
typedef struct movie
{
    char *title;
    int year;
    struct movie *next;
} movie;

/* Part of the following function are from my previous assignment */

/* Parse each line which has "," delimited and create a  movie struct*/
movie *createMovie(char *line)
{
    // Allocate memory for pointer to struct
    movie *currMovie = malloc(sizeof(struct movie));

    // Pointer to use with strtok_r
    char *saveptr;

    // The first token is the movie title
    char *token = strtok_r(line, ",", &saveptr);
    currMovie->title = calloc(strlen(token) + 1, sizeof(char));
    strcpy(currMovie->title, token);

    // The next token is the year release
    token = strtok_r(NULL, ",", &saveptr);
    currMovie->year = atoi(token);

    // The next token is the language
    token = strtok_r(NULL, ",", &saveptr);
    //currMovie->language = calloc(strlen(token) + 1, sizeof(char));
    //strcpy(currMovie->language, token);

    // The last token is the rating score
    token = strtok_r(NULL, "\n", &saveptr);
    //currMovie->rating = strtof(token, NULL);

    // Set the next node to NULL in the newly created movie entry
    currMovie->next = NULL;

    return currMovie;

    //add to test free memory
    free(currMovie);
    free(saveptr);
}

/* Part of the following function are from my previous assignment */

/* Read an user file and parse data each line
to create a linked list of movie
*/
movie *processFile(char *fileName)
{
    // Open a file in read only mode
    FILE *fp = fopen(fileName, "r");

    if (fp == NULL){
      printf("Unable to open the file");
    }

    // Creat charactor array to store data in each line
    char currLine[1024];
    // a counter to count the number of line being read.
    int line_count=0;
    // The head of the linked list
    movie *head = NULL;
    // The tail of the linked list
    movie *tail = NULL;

    // Read a line from the file
    while (fgets(currLine, sizeof(currLine), fp))
    {
      // skip reading the first line which is the column header
      if (line_count >=1)
      {

        // Get a new movie node corresponding to the current line
        movie *newNode = createMovie(currLine);

        // Is this the first node in the linked list?
        if (head == NULL)
        {
            // This is the first node in the linked link
            // Set the head and the tail to this node
            head = newNode;
            tail = newNode;
        }
        else
        {
            // This is not the first node.
            // Add this node to the list and advance the tail
            tail->next = newNode;
            tail = newNode;
        }

      }
      line_count++;

    }
    //printf("Processed file %s and parsed data for %d movies\n", fileName, line_count-1);
    fclose(fp);
    //free(currLine);
    return head;
}

/* Part of the following function are from my previous assignment */

/* swap data for the linked list */
void swap(movie *ptr1, movie*ptr2)
{
  // Swap title
	char *temp1 = ptr1->title;
	ptr1->title = ptr2->title;
	ptr2->title = temp1;

  // Swap Year
	int temp2 = ptr1->year;
	ptr1->year = ptr2->year;
	ptr2->year = temp2;


}

/* Part of the following function are from my previous assignment */

/* Bubble sort year in linked list in Decending order */
void bubbleSortYear(movie *list)
{
    int flag;
    movie *currMovie;
    movie *nextMovie = NULL;

    /* Checking for empty list */
    if (list == NULL)
        return;

    do
    {
        // Set flag for a swapped movie
        flag = 0;

        // Set pointer to the movie list
        currMovie = list;

        // Iterate through the movie list
        while (currMovie->next != nextMovie)
        {
            // Compare movies
            if (currMovie->year < currMovie->next->year)
            {
                // Swap between movies
                swap(currMovie, currMovie->next);

                // Set flag to 1, mean already swapped
                flag = 1;
            }
            // current movie point to the next movie in the list
            currMovie = currMovie->next;
        }
        nextMovie = currMovie;
    }
    while (flag);
}


/* Function to return the largest file with the extension "csv"
in the current directory whose name starts with the prefix "movies_" */
char* findLargestFile(char *aDir)
{
        DIR *dp;
        struct dirent *entry;

        // Create struct stat store meta-data about a file
        struct stat statbuf;
        struct stat statbuffer;

        int i = 0;
        char *entryName;

        // Handle error if unable to open the directory
        if((dp = opendir(aDir)) == NULL) {
           fprintf(stderr, "Unable to open directory: %s\n", aDir);
           return 0;

        }

        // Changing to current directory
        chdir(aDir);

        // Read through all the entries
        while((entry = readdir(dp)) != NULL) {

          // locate index of the file extension
          const char *fileEXT = strrchr (entry->d_name, '.');

          if ((fileEXT != NULL) && (!strcmp (fileEXT+1, SUFFIX))){

            // Check file start with "movies_"
            if (strncmp(PREFIX, entry->d_name, strlen(PREFIX)) == 0){
              stat(entry->d_name, &statbuf);

              // Check for the regular file
              if(S_ISREG(statbuf.st_mode)) {

                stat(entry->d_name, &statbuffer);

                // Compare size of files
                if(statbuffer.st_size > i) {
                   i = (statbuffer.st_size);
                   entryName = (entry->d_name);
                }
           }
         }
       }

         }

        closedir(dp);

        return entryName;
}

/* Function to return the smallest file with the extension "csv"
in the current directory whose name starts with the prefix "movies_" */
char* findSmallestFile(char *aDir)
{
        DIR *dp;
        struct dirent *entry;

        // Create struct stat store meta-data about a file
        struct stat statbuf;
        struct stat statbuffer;

        int i = 5000;
        char *entryName;

        // Handle error if unable to open the directory
        if((dp = opendir(aDir)) == NULL) {
           fprintf(stderr, "cannot open directory: %s\n", aDir);
           return 0;

        }

        // Changing to current directory
        chdir(aDir);

        // Read through all the entries
        while((entry = readdir(dp)) != NULL) {

          // locate index of the file extension
          const char *fileEXT = strrchr (entry->d_name, '.');

          if ((fileEXT != NULL) && (!strcmp (fileEXT+1, SUFFIX))){

            // Check file start with "movies_"
            if (strncmp(PREFIX, entry->d_name, strlen(PREFIX)) == 0){
              stat(entry->d_name, &statbuf);

              // Check for the regular file
              if(S_ISREG(statbuf.st_mode)) {

                stat(entry->d_name, &statbuffer);

                // Compare size of files
                if(statbuffer.st_size < i) {
                   i = (statbuffer.st_size);
                   entryName = (entry->d_name);
                }
           }
         }
       }

         }

        closedir(dp);

        return entryName;
}

/*  Function to return true if target file found in the directory
    and return false if the target file is not found
*/
int searchFile(char* dir, char* targetFile){

  DIR * dirp;
  dirp = opendir(dir);
  struct dirent * entry;

  // Going throught all the file in directory and compare the name
  while ((entry = readdir(dirp)) != NULL){

    // Target file found, return 1
    if (strcmp(targetFile, entry->d_name) == 0) {
      return 1;
    }

  }
  closedir(dirp);

  // return 0 if target file is not found
  return 0;
}

/*  Function to create a new directory
    and return the path of the new directory
*/
char* makeNewDr(char *aDir){

  // Reset computer time to prevent generating the repeat random number
  srand(time(0));

  // Generate random number between 0-99999
  int num = (rand() % 100000);

  char* onid = "kongkaen.movies";

  char name[30];
  char *dirname;
  char* newPath;
  int check;

  // Create a name for the new directory
  sprintf(name,"%s.%d",onid,num);
  dirname=malloc(SIZE*sizeof(char));
  strcpy(dirname, name);

  // Create the directory path
  char createPath[30];
  sprintf(createPath,"./%s",dirname);
  newPath=malloc(SIZE*sizeof(char));
  strcpy(newPath, createPath);



  // Create directory with permission set to rwxr-x--- (0750)
  check = mkdir(dirname,0750);

    if (!check)
        printf("Created directory with name %s\n", dirname);

    else
    {
        printf("Unable to create directory\n");
        exit(1);
    }

    // add to test memory leak
    free(dirname);
    free(newPath);

    // Return the directory path
    return newPath;
}

/*  Function to create a .text file each year movies released
    Function will first, sort the movie list by year decending
    to group movies by year
    Then, create a .txt file yesr by year and store movie titles
*/
void createTXT(movie *list, char* filePath)
{

    int year = 0;
    int fPtr;
    FILE* fp;
    char name[30];
    char path[50];
    char* newLine = "\n";

    // Sort movie list by year decending
    bubbleSortYear(list);

    // Create .txt file for each year
    while (list != NULL)
    {
          // Generate file path to .txt for each year
        sprintf(path,"%s/%d.txt", filePath, list->year);

          // Create file with permission rw-r----- (640)
        fPtr = open(path, O_RDWR | O_CREAT | O_APPEND, 0640);

        //  Errer handling if the file is not created
        if (fPtr < 0){
          printf("Unable to create  the file");
          exit(0);
        }

        else{

          // Generate condition to prevent new line trailing at the end of file
          if (list->year == year){
            write(fPtr, newLine, strlen(newLine) + 1);
            write(fPtr, list->title, strlen(list->title) + 1);
          }

          if (list->year != year){
            write(fPtr, list->title, strlen(list->title) + 1);
          }

          // Close file
          close(fPtr);
        }

        // Update year
        year = list->year;

        // Update the linked list
        list = list->next;

    }
}


int main(){

  int ch, opt;
  char userPick[30];
  char *largest;
  char *smallest;
  char *mainDir = "./";

  // Prompt user to pick the options
  while(1){
    printf("\n1. Select file to process\n");
    printf("2. Exit the program\n");
    printf("\nEnter a choice 1 or 2: ");
    scanf("%d", &ch);

    // Prompt user to select a file to process
    switch(ch){

        case 1:
          printf("\nWhich file you want to process?\n");
          printf("Enter 1 to pick the largest file\n");
          printf("Enter 2 to pick the smallest file\n");
          printf("Enter 3 to specify the name of a file\n");
          printf("\nEnter a choice from 1 to 3: ");
          scanf("%d", &opt);

          switch(opt) {

            /*  User choose option 1: Program will find the largest csv file
                and start with "movies_" in the directory.
                then, program will create a new directory, paresing the file,
                and create txt file for each year
                and store movies title associated with the release year.
            */
            case 1:

              // Look for the largest file
              largest = findLargestFile(mainDir);
              printf("Now processing the chosen file named %s\n",largest);

              // Create a new directory
              char* newDir = makeNewDr(mainDir);

              // Parse data to linked list of movie struct
              movie *listLarge = processFile(largest);

              // Create .txt file in the new Directory
              createTXT(listLarge, newDir);

              break;

            /*  User choose option 1: Program will find the largest csv file
                and start with "movies_" in the directory.
                then, program will create a new directory, paresing the file,
                and create txt file for each year
                and store movies title associated with the release year.
            */
            case 2:

              // Look for the smallest file
              smallest = findSmallestFile(mainDir);
              printf("Now processing the chosen file named %s\n",smallest);

              // Create a new directory
              char* newDir2 = makeNewDr(mainDir);

              // Parse data to linked list
              movie *listSmall = processFile(smallest);

              // Create .txt file in the new Directory
              createTXT(listSmall, newDir2);

              break;

            /*  User choose option 1: Program will find the largest csv file
                and start with "movies_" in the directory.
                then, program will create a new directory, paresing the file,
                and create txt file for each year
                and store movies title associated with the release year.
            */
            case 3:

              // Prompt user to enter file name to precess
              printf("process the  file by name : ");
              scanf("%s", userPick);

              // Look for file user entered in the directory
              int fileFound = searchFile(mainDir, userPick);

              // There exist file user entered in current directory
              if (fileFound == 1){
                printf("Now processing the chosen file named %s\n", userPick);

                // Create a new directory
                char* newDir3 = makeNewDr(mainDir);

                // Parse data to linked list
                movie *userFile = processFile(userPick);

                // Create .txt file in the new Directory
                createTXT(userFile, newDir3);
              }

              // If file not found, display message
              if (fileFound == 0){
                printf("The file %s was not found. Try again\n", userPick);
              }

              break;


          }
            break;

        case 2:
            exit(0);

        // display a message if user use invalid input
        default:
            printf("You entered an incorrect choice. Try again.");
    }
  }


  return EXIT_SUCCESS;
}
