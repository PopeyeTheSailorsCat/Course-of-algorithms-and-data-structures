#include <stdlib.h>
#include <stdio.h>
#pragma warning(disable:4996)
#define W 70
#define N 20
char TABLE[N][W];
typedef struct tree_t{
  int value;
  int length;
  struct tree_t*leftChild;
  struct tree_t* rightChild;
};
typedef struct tree_t tree;
int ReadNumber(void) {//reading a number from a file
  int elem, sum;
  sum = 0;
  elem = getchar();
  while (elem < 58 && elem > 47) {
    sum *= 10;
    sum += (char)elem - '0';
    elem = getchar();
  }
  return sum;
}

tree* ReadTree(void) {//reading a tree from a file
  char left, right;
  int value;// length;
  tree *tmp = NULL;
  value = ReadNumber();
  left = (char)getchar();
  right = (char)getchar();
  if (getchar() != EOF) {
    tmp = malloc(sizeof(tree));
    tmp->value = value;
    tmp->length = 0;
    tmp->leftChild = NULL;
    tmp->rightChild = NULL;
    if (left != '-') {
      tmp->leftChild = ReadTree();
    }
    if (right != '-') {
      tmp->rightChild = ReadTree();
    }
  }
  return tmp;
}

int CountMyNumber(int value) {//consider the length of the number
  int valueLength=0;
  do {
    value /= 10;
    valueLength++;
  } while (value > 0);
  return valueLength;
}

int CountMyTree(tree* currentElem){//consider the length of the number and the length of the sub trees
  int globalLength=0;
  if (currentElem->rightChild) {
    globalLength+=CountMyTree(currentElem->rightChild);
  }
  if (currentElem->leftChild) {
    globalLength+=CountMyTree(currentElem->leftChild);
  }
  globalLength += CountMyNumber(currentElem->value);
  currentElem->length = globalLength;
  return globalLength;
}

int y = 0;
void PrintInTable(int x, int printThis, int length) {//printing in table
  do {
    TABLE[y][x + length - 1] = printThis % 10 +'0';
    printThis /= 10;
    length--;
  } while (printThis);
}

void PrintTree(tree* currentElement, int x) {//putting a tree in a table
  if (currentElement) {
    if (currentElement->leftChild) {
      y++;
      y++;
      PrintTree(currentElement->leftChild, x - 8);
      y--;
      y--;
      y--;
    }
    PrintInTable(x, currentElement->value, CountMyNumber(currentElement->value));
    y++;
    if (currentElement->leftChild) {
      TABLE[y][x - 1] = '/';
    }
    if (currentElement->rightChild) {
      TABLE[y][x + CountMyNumber(currentElement->length)] = '\\';
    }
    PrintInTable(x, currentElement->length, CountMyNumber(currentElement->length));
    if (currentElement->rightChild) {
      y++;
      PrintTree(currentElement->rightChild, x + 8);
      y--;
      y--;
    }
    free(currentElement);
  }
}

void PrintTABLE(void) {//the output table
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < W; j++) {
      printf("%c", TABLE[i][j]);
    }
    printf("\n");
  }
}
void InitTABLE(void) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < W; j++) {
      TABLE[i][j] = ' ';
    }
  }
}

int main(void) {
  FILE *fp;
  tree* myTree;
  fp = freopen("input.txt", "r", stdin);
  InitTABLE();
  myTree = ReadTree();
  CountMyTree(myTree);
  PrintTree(myTree, 35);
  PrintTABLE();
  getch();
  return 0;
}