#include <stdlib.h>
#include <stdio.h>
#pragma warning(disable:4996)
#define false 0
#define true 1
typedef struct partOfChain chain;
struct partOfChain{
  int roadTo;
  chain* next;
};
typedef struct grph head;
struct grph {
  _Bool used;
  chain* next;
};
int howManyVertex;
void Push(head* graph, int begin, int end) {//adding another element
  chain* tmp = malloc(sizeof(chain));
  tmp->roadTo = end;
  tmp->next = NULL;
  if (!graph[begin].next) {//see if we started the chain
    graph[begin].next = tmp;
    return;
  }
  tmp->next = graph[begin].next;
  graph[begin].next = tmp;
  return;
}

_Bool MakeStep(head* graph, int position, int deep) {//visiting another site
  chain* here;
  deep++;
  if (deep == howManyVertex) {
    printf("%i ", position + 1);
    return true;
  }
  here = graph[position].next;
  while (here) {
    if (!graph[here->roadTo].used) {
      
      graph[here->roadTo].used = true;
      if (MakeStep(graph, here->roadTo, deep)) {
        printf("%i ", position + 1);
        return true;
      }
    }
    here = here->next;
  }
  graph[position].used = false;
  return false;
}

_Bool FirstStep(head* graph) {//Select the first node
  //chain* here;
  int i = 0;
  while (i< howManyVertex) {
    if (graph[i].used != true && graph[i].next !=NULL) {
      graph[i].used = true;
      if (MakeStep(graph, i, 0)) {
        //printf("%i\n", i+1);
        return true;

      }
    }
    if (!graph[i].next) {
      break;
    }
    graph[i].used = false;
    i++;
  }
  printf("No way\n");
  return false;
}
void InitializationAndReadGraph(head* graph) {
  int from, to;
  for (int i = 0; i < howManyVertex; i++) { //spree to avoid mistakes
    graph[i].next = NULL;
    graph[i].used = false;
  }

  //чтение
  while (scanf("%i %i", &from, &to)) { //read cycle of the adjacency list
    Push(graph, from - 1, to - 1);
    Push(graph, to - 1, from - 1);
    //printf("%i %i\n", from, to);
    if (getchar() == EOF) {
      break;
    }
    //getch();
  }
  return;
}

void CleanGraph(head* graph) {
  for (int i = 0; i < howManyVertex; i++) {//Cleaning
    chain* here = graph[i].next;
    chain* nextch;
    while (here) {
      nextch = here->next;
      free(here);
      here = nextch;
    }
  }
}

int main(void) {
 // int howManyVertex;
  FILE *fp;
  head* graph;

  fp = freopen("input.txt", "r", stdin);
  scanf("%i", &howManyVertex);
  graph = malloc(howManyVertex * sizeof(head)); //creating graphs
  InitializationAndReadGraph(graph);
  FirstStep(graph);
  CleanGraph(graph);
  free(graph);
  getch();
  return 0;
}