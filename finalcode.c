#include<stdio.h>
#include<stdlib.h>

int number;
int top = -1;
int isPresent(int* , int );
int* push(int * , int);
void Display_stack(int *);







int adjacency_count(int matrix[number][number], int no)
{
  int i,j;
  int count =0;
  for(j=0;j<number;j++)
  {
    if(matrix[no][j]==1)
    {
      count++;
    }
  }
  return count;
}

int * adjacency_result (int matrix[number][number], int no, int * result)
{
  int i,j,k=0;
  int count;
  count = adjacency_count(matrix,no);
  for(j=0;j<number;j++)
  {
    if(matrix[no][j]==1)
    {
      result[k]=j;
      k++;
    }
  }
  return result;
}



void write_to_csv(int matrix[number][number]) {
    FILE *file = fopen("graph.csv", "w");
    if (file == NULL) {
        printf("Error: Unable to open the CSV file.\n");
        exit(1);
    }

    for (int i = 0; i < number; i++) {
        for (int j = 0; j < number; j++) {
            fprintf(file, "%d,", matrix[i][j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

void main()
{
    printf("\n\n\n\t\t\t\t\t\t   Project Based Learning\n\n\n");
    printf("\t\t\t\t\t\t Topic : Friend Suggestion\n\n\n");
    printf("\t\t\t\t\t\t\t ");
    printf("WELCOME\n\n\n");
  printf("Enter total number of nodes\n");
  scanf("%d",&number);
  int matrix[number][number];
  int count_adj[number];
  int i,j,k,no;
  int count;
  int *stack;
    char decision;
  stack = (int *)malloc(number * sizeof(int));
  printf("Enter 1 if friend and 0 if not a friend.\n");
  for(i=0;i<number;i++)
  {
    for(j=0;j<number;j++)
    {
        printf("Is %d friend of %d : ",i,j);
      scanf("%d",&matrix[i][j]);
    }
  }
  write_to_csv(matrix);
  while(1)
    {
        printf("\nEnter operation to perform : ");
        printf("\n1. My friends.\n2. Recommend me friends\n3. Exit\n");
        int choice;
        scanf("%d",&choice);
        switch(choice)
        {
        case 1:
            printf("Who are you : ");
            scanf("%d",&no);
            int * friends;
            count = adjacency_count(matrix,no);
            friends = (int *) malloc(count*sizeof(int));
            friends = adjacency_result(matrix,no,friends);
            printf("Your friends are : ");
            for(i=0;i<count;i++)
            {
                printf("%d, ",friends[i]);
            }
            break;

          case 2:
          printf("Who are you : ");
          scanf("%d", &no);

          int flag;
          count = adjacency_count(matrix, no);
          int *result = (int *)malloc(count * sizeof(int));
          int *final_result = (int *)malloc(number * sizeof(int));
          int *visited = (int *)calloc(number, sizeof(int)); // Initialize all elements to 0

          for (i = 0; i < number; i++) {
              count_adj[i] = adjacency_count(matrix, i);
          }

          for (i = 0; i < count; i++) {
              result = adjacency_result(matrix, no, result);
              for (j = 0; j < count_adj[result[i]]; j++) {
                  final_result[result[i]] = 1; // Mark direct friends as visited
              }
          }

          for (i = 0; i < count; i++) {
              result = adjacency_result(matrix, no, result);
              for (j = 0; j < count_adj[result[i]]; j++) {
                  int friend_of_friend = result[i];
                  if (!visited[friend_of_friend] && friend_of_friend != no) {
                      final_result[friend_of_friend] = 1; // Mark recommended friends as visited
                      visited[friend_of_friend] = 1; // Mark as visited
                      for (k = 0; k < number; k++) {
                          if (matrix[friend_of_friend][k] == 1 && !visited[k]) {
                              final_result[k] = 1; // Mark friends of recommended friends as visited
                              visited[k] = 1; // Mark as visited
                          }
                      }
                  }
              }
          }

          printf("\nRecommendations : ");
          for (i = 0; i < number; i++) {
              if (final_result[i] && i != no) {
                  printf("%d, ", i);
              }
          }

          printf("\n");

          free(result);
          free(final_result);
          free(visited);
          break;


        case 3:
            exit(0);

        default:
            printf("Enter valid option\n");
        }
    }
}


int * push(int * stack, int no)
{
    if(no>=number||no<0)
    {
    }
    else if(isPresent(stack,no))
    {
    }
    else
    {
        top++;
        stack[top] = no;
        //printf("\tNo : %d--",stack[top]);
        //printf("\tTop : %d-",top);
    }
    return stack;
}

int isPresent(int *stack, int no)
{
    int i,flag = 0;
    for(i=0;i<=top;i++)
    {
        if(stack[i]==no)
        {
            flag = 1;
            break;
        }
    }
    return flag;
}

void Display_stack(int *stack)
{
    int i;
    for(i=0;i<=top;i++)
    {
        printf("%d, ",stack[i]);
    }
}