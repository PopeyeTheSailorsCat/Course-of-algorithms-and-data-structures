#include <stdio.h>
#include <stdlib.h>
#pragma warning(disable:4996)
typedef struct untypelist list;
struct untypelist {
  int val_t;
  int index_t;
  list *next;
};

list* PushLast(list* Node,int elem, int index) {//put in the list
  list *tmp = (list*)malloc(sizeof(list));
  tmp->index_t = index;
  tmp->val_t = elem;
  tmp->next = NULL;
  //tmp->next = *Node;
  //Node->next = tmp;
  if (Node) {
    Node->next = tmp;
  }
  else {
    Node = tmp;
  }

  return tmp;
}

int Pop(list** Node) {//pull it out of the list
  list* tmp= NULL;
  tmp = *Node;
  *Node = (*Node)->next;
  free(tmp);
  return 0;
}

void ReadMatrix(list** Matrix, int height, int width) {//reading a matrix from a file
  list *lastElem = NULL;
  int elem;
  for (int i = 0; i < height; i++) {
    for (int j = 0; j < width; j++) {
      scanf("%i", &elem);
      if (elem) {
        lastElem = PushLast(lastElem, elem, j);
        //printf("%i", firstMatrix[i]->val_t);
      }
      if (!Matrix[i] && lastElem) {
        Matrix[i] = lastElem;
      }
    }
    //printf("\n");
    lastElem = NULL;
  }
}
void SumMatrix(list** firstMatrix, list** secondMatrix, int height, int width) {//the summation of the discharged matrix
  int *string;

  for (int i = 0; i < height; i++) {
    string = calloc(width + 1, sizeof(int));
    for (int j = 0; j <width; j++) {
      if (firstMatrix[i] && secondMatrix[i]) {
        if (firstMatrix[i]->index_t == j) {
          string[j] += firstMatrix[i]->val_t;
          Pop(&firstMatrix[i]);
        }
        if (secondMatrix[i]->index_t == j) {
          string[j] += secondMatrix[i]->val_t;
          Pop(&secondMatrix[i]);
        }
      }
      else if (firstMatrix[i]) {
        if (firstMatrix[i]->index_t == j) {
          string[j] += firstMatrix[i]->val_t;
          Pop(&firstMatrix[i]);
        }
      }
      else if (secondMatrix[i]) {
        if (secondMatrix[i]->index_t == j) {
          string[j] += secondMatrix[i]->val_t;
          Pop(&secondMatrix[i]);
        }
      }
      printf("%i ", string[j]);
    }
    printf("\n");
    //PrintString(string, width);
    free(string);
  }
  printf("\n");
}

int main(void) {
  FILE *fp = freopen("input.txt", "r", stdin);
  list **firstMatrix =  NULL;
  list **secondMatrix= NULL;
  int width, height;
  scanf("%i",&width);
  scanf("%i", &height);
  firstMatrix = malloc(height * sizeof(list*));
  secondMatrix = malloc(height * sizeof(list*));
  for (int i = 0; i < height; i++) {
    firstMatrix[i] = NULL;
    secondMatrix[i] = NULL;
  }
  ReadMatrix(firstMatrix, height, width);
  ReadMatrix(secondMatrix, height, width);
  fp = freopen("$CONIN", "r", stdin);
  SumMatrix(firstMatrix, secondMatrix, height, width);
  free(firstMatrix);
  free(secondMatrix);
  getch();
  return 0;
}