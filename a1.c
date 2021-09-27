/*
* Author: Sean Mackenzie
* Due Date: September 17th, 2021
* Description: Assignment 1
* Course: CS3413
*/
#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#define USER_NAME 50
#define BUFFER_SIZE 150
#define JOB_TOTAL
//--------------------------------------------------------------------
//Creating a node
//--------------------------------------------------------------------
struct Node{
  //Can be any data type
  char user[USER_NAME];
  char process;
  int arrival;
  int duration;
  int finish;
  int touched;
  //Creates the next in the list which makes it a linked list
  struct Node *next;
};
//--------------------------------------------------------------------
//Function adds a node to the linked list
//--------------------------------------------------------------------
void newNode(struct Node** head_ref, char *new_user, char new_process, int new_arrival, int new_duration){
  //Allocating memory for the nodes, each node will move in as the new head of the list
  //printf("in new node section\n");
  struct Node* new_node = (struct Node*)malloc(sizeof(struct Node));
  //Have the new_node->next be where head ref is pointing, which is the old head
  new_node->next = *head_ref;
  //Copy the data over to the new node.
  //printf("before strn copy for the string (user)\n");
  strncpy(&(new_node->user[0]), new_user, USER_NAME);
  //printf("moving values to new node values\n");
  new_node->process = new_process;
  new_node->arrival = new_arrival;
  new_node->duration = new_duration;
  new_node->finish = 0;
  new_node->touched = 0;
  //printf("finished moving the values, the process arrival is as follows: %d\n", new_arrival);
    //Have head_ref point to new head
  *head_ref = new_node;
  free(new_node);
    //printf("set head ref to point to new node.\n");
}

//--------------------------------------------------------------------
//Initialize the algorithm
//--------------------------------------------------------------------
int prio_algortihm(struct Node *head_node){
  int cycle = 1;
  //int process_number = 0;
  //This node will serve as the active node. The active node is the one currently having processes done
  struct Node *active = NULL;
  //This will be the node we are currently comparing the active node to. I dont not want to risk moving the head node.
  //Have it start by pointing at the head node.
  struct Node *current = NULL;
  //go through the nodes
  //If this breaks, try getting ridof & and put a * in front of current
  current = head_node;

  printf("Time      Job\n");
  //while(current !=NULL){
    /*while (cycle <= current->arrival && current->next != NULL){
      //if the process should not yet enter or has not entered during or prior to the cycle, skip to next one
      current = current->next;
      }
      active = current;
      current = current->next;
      */
      //If this is the right cycle, we do the check of if it is the shortest option

      //------------------------------------------------
      //I hope this code doesnt sadden you too much
      //-----------------------------------------------
    while(1){
      int job_total = 0;
      current = head_node;
      while(current!= NULL){
          job_total += current->duration;
        if (active == NULL && current->arrival <= cycle && current->duration > 0){
          active = current;
        }
        if(active != NULL && active->duration >= current->duration && current->duration > 0 && current->arrival <= cycle){
          active = current;
        }
        current = current->next;
      }
      if (job_total == 0) {
        break;
      }
        if(active != NULL){
          active-> duration = active->duration -1;
          printf(" %d         %c\n",cycle, active->process);
          //saving value for the summary
          //this is to save vaules for summary
          if(active->duration == 0){
            active->finish = cycle+1;
          }
        }
        //else{
          //printf("%d        IDLE\n", cycle);
        //}
        cycle++;
        active = NULL;
        //printf("Cycle: %d \n", cycle);
    }
  printf(" %d        IDLE\n\n", cycle);

  //TODO fix summaries
  printf(" Summary\n");
  active = head_node;
  current = head_node->next;
  while(active!=NULL){
    current = head_node->next;
    while (current!= NULL){
      if(strcmp(active->user, current->user) == 0 && active->touched == 0){
        current->touched = 1;
        if(active->finish > current->finish){
          printf("%s    %d\n",active->user, active->finish);
          //current = current->next;
        }
        else{
          printf("%s    %d\n",current->user, current->finish);
        }
      }
      current= current->next;
    }
    //printf("%s    %d\n",active->user, active->finish);
    active = active->next;
  }
  return 0;
}
//--------------------------------------------------------------------
//Creating the main function aka the driver
//--------------------------------------------------------------------
//argc used to see number of command line arguments are submitted
//argv is a pointer to the files on the command line
int main(int argc,char *argv[]){
  char *user_in = malloc(sizeof user_in * USER_NAME);
  char process_in;
  int arrival_in;
  int duration_in;
//-------------------------------------------------------------------
/*
IGNORE THESE COMMENTS THEYT WERE ME BEING A DUMMY
printf("running check\n");
reads the file submitted
  TODO Fix file input.
  FILE *inputFile =fopen(argv[1], "r");
  if (argc != 1){
    printf("Incorrect number of files submitted \n");
    return 1;
  }
  printf("proper file numbers check\n");
  Checks to ensure that the file was read
  if (inputFile == 0 || inputFile == NULL){
    printf("Could not open file.\n");
    return 1;
  }
  used for test.
  if (inputFile == NULL){
    printf("input file was null\n");
    return 1;
  }
  if (inputFile == 0){
    printf("Input was == 0\n");
    return 1;
  }
  printf("file check\n");
  instantiating the node
  */
//----------------------------------------------------------------------
  struct Node *start = NULL;

  //creating a buffer to skip over the first line of the input file
  char *fileBuffer = malloc(sizeof(char) * BUFFER_SIZE);
  //Storing the information from the file provided
  int i = 0;
  while(fgets(fileBuffer, BUFFER_SIZE, stdin) != NULL){
    i++;
    //printf("buffer check rotation: %d \n", i);
    //Have the file scan into variables (may have issue with string going to char) and then send to newNode function
    int scan = fscanf(stdin, "%s %s %d %d",&user_in[0],&process_in, &arrival_in, &duration_in);
    if (scan != 4){
      break;
    }
    //sending information to create a new node. Pass by value only allowed for char and int, no arrays or more complex types.
    //printf("After fscanf \n");
    newNode(&start, &user_in[0], process_in, arrival_in, duration_in);
    //printf("Entering the end of loop, loop will restart.\n\n");

  }
  prio_algortihm(start);
  free(user_in);
  free(fileBuffer);
  return 0;

}
