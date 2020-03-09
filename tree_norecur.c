#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#pragma warning(disable:4996)
#define W 70
#define N 20
char TABLE[N][W];
typedef struct tree_t {
  int key;
  int number;
  bool visit;
  struct tree_t*leftChild;
  struct tree_t* rightChild;
  struct tree_t* myParent;
};
typedef struct tree_t tree;



//int y = 0;

void PrintTABLE(void) {
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

void PrintInTable(tree *t, int x, int y) {
  if (!t) {
    return;
  }
  if (t->leftChild) {
    PrintInTable(t->leftChild, x - (t->leftChild->number), y+1);
    }
  TABLE[y][x] = t->key+'0';
  if (t->rightChild) {
    PrintInTable(t->rightChild, x + (t->rightChild->number), y+1);
  }
}

void IncreaseNumber(tree *t) {
  while (t->number != -1) {
    t->number = t->number + 1; //shit
    t = t->myParent;
  }
  return;
}

tree* add(tree* t, int k)
{
  int flag=0;
  tree* root=t;
  tree* child;
  if (t == NULL){
    t = (tree*)malloc(sizeof(tree));
    t->key = k;
    t->leftChild = t->rightChild =t->myParent= NULL;
    t->number = -1;
    return t;
  }
  else
  {
    while (!flag) {
      if (t->leftChild == NULL) {
        child = (tree*)malloc(sizeof(tree));
        t->leftChild = child;
        child->myParent = t;
        child->key = k;
        child->visit = false;
        child->number = 1;
        child->leftChild = child->rightChild = NULL;
        IncreaseNumber(t);
        flag = 1;//Function for increasing subtrees
      }else if(t->rightChild == NULL){
        child = (tree*)malloc(sizeof(tree));
        t->rightChild = child;
        child->myParent = t;
        child->key = k;
        child->number = 1;
        child->visit = false;
        child->leftChild = child->rightChild = NULL;
        IncreaseNumber(t);
        flag = 1;//Function for increasing subtrees
      }else if (t->leftChild->number > t->rightChild->number) {
        t = t->rightChild;
      }
      else {
        t = t->leftChild;
      }
    }
  }
  return root;
}
void DownNumber(tree* current) { //I walk to the root of the current element , lowering them under the trees, as I take the element
  while (current->number != -1) {
    current->number = current->number - 1;
    current = current->myParent;
  }
}

tree* FindChildForChange(tree* current) {//Looking for the leftmost element for the current one
  while (current->leftChild != NULL) {
    current = current->leftChild;
  }
  current->myParent->leftChild = current->myParent->rightChild;//I write the right element instead of the left one to " Maintain order"
  current->myParent->rightChild = NULL;
  DownNumber(current->myParent);
  return current;
}

tree* delete(tree*t, int k) {
  int compas=0;
  if (t == NULL) {
    return t;
  }
  tree* root = t;
  tree* childForChange;
  int flag = 0;
  while (!flag) {
    if (t->key == k) {
      if (t->leftChild==NULL &&  t ->rightChild == NULL){ //A leaf or a very empty tree???
        if (t->number == -1) { //The tree is over
          free(t);
          return NULL; 
        }
        DownNumber(t->myParent);
        if (t->myParent->leftChild!=NULL && t->myParent->leftChild->key == k) {//Determining what kind of child I am at the moment
          t->myParent->leftChild = NULL;
        }
        else {
          t->myParent->rightChild = NULL;
        }
      }
      else {
        //Case where the node is the root
        childForChange = FindChildForChange(t);//Find a child node to be beautiful
        if (t->number != -1) {
          childForChange->myParent = t->myParent;//You can not throw pointers, but just change the number and delete that child, but let's say we need to change
          if (t->myParent->leftChild != NULL && t->myParent->leftChild->key == k) {//Determining what kind of child I am at the moment
            t->myParent->leftChild = childForChange;
          }
          else {
            t->myParent->rightChild = childForChange;
          }
        }
        else {
          root = childForChange;

        }
        childForChange->leftChild = t->leftChild;
        if (childForChange->leftChild) {
          childForChange->leftChild->myParent = childForChange;
        }
        childForChange->rightChild = t->rightChild;
        if (childForChange->rightChild) {
          childForChange->rightChild->myParent = childForChange;
        }
        childForChange->number = t->number;
        
      }
      free(t);
      return root;
    }
    else if (t->leftChild != NULL && t->leftChild->visit==0 &&(t->rightChild==NULL || t->rightChild->visit==0)) {//since we always add as much as possible to the left
      t = t->leftChild;                                                                  //Then this check is made , since when moving to the right
    }                                                                                    //We clean the left one so that we don 't leave any garbage
    else if (t->rightChild != NULL && t->rightChild->visit==0) {                        //You need a crutch on the root, because there will be a problem with the lack of an element
      if (t->leftChild){
        t->leftChild->visit = 0;
      }
      t = t->rightChild;
    }
    else {
      if (t->number==-1){ //&& ((t->rightChild!=NULL && t->rightChild->visit == 1 )||(t->rightChild!=NULL && t->leftChild->visit==1 )|| (t->rightChild==NULL && t->leftChild==NULL))) {//если нет элемента
        printf("No element found\n");
        t->rightChild->visit = 0;
        return t;
      }
      t->visit = 1;
      if (t->leftChild) {
        t->leftChild->visit = 0;
      }
      if (t->rightChild) {
        t->rightChild->visit = 0;
      }
      t = t->myParent;
    }
  }
 
}

int main(void) {
  tree* myTree=NULL;
  int command = 0;
  int elem;
  InitTABLE();
  while (command != -1) {
    scanf("%i", &command);
    switch (command){
    case 1:
      printf("add elem: ");
      scanf("%i", &elem);
      myTree = add(myTree, elem);
      PrintInTable(myTree, 35, 0);
      PrintTABLE();
      InitTABLE();
      break;
    case 2:
      printf("delete elem: ");
      scanf("%i", &elem);
      myTree = delete(myTree, elem);
      PrintInTable(myTree, 35, 0);
      PrintTABLE();
      InitTABLE();
      break;
    default:
      printf("unknow command\n");
      break;
    }
    //printf("%i\n", command);
  }
  getch();
  return 0;
}