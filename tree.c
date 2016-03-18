/* An implementation of tree traversal for depth-first (pre-order, in-order, and post-order) and breadth-first traversal */
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

// Define tnode_t
typedef struct tnode{
  int value;
  struct tnode * l;
  struct tnode * r;
}tnode_t;

// Define qnode_t
typedef struct qnode{
  tnode_t* node;
  struct qnode* next;
}qnode_t;

// Function signatures
tnode_t * make_tnode(int num);
tnode_t* find (tnode_t* root, int num);
void insert (tnode_t* root, int num);
void delete (tnode_t* root, int num);
void pre_order(tnode_t* root, FILE* output);
void in_order(tnode_t* root, FILE* output);
void post_order(tnode_t* root, FILE* output);
qnode_t * make_qnode(tnode_t* node);
void enqueue (qnode_t* head, tnode_t* node);
tnode_t* dequeue (qnode_t* head);
void breadth_first(tnode_t* root, FILE* output);

int main(int argc, char** argv) {
  
  // File initialization
  FILE* input_fp;
  FILE* output_fp;
  //input_fp = fopen(argv[1], "r");
  input_fp = fopen("brtest.txt", "r");
  output_fp = fopen("results.txt", "w");

  if(input_fp == NULL)
    {
      perror("Input file failed to open.");
    }
  
  int num;
  int file_read;

  // Declare tree root
  tnode_t* root = (tnode_t*)malloc(sizeof(tnode_t));
  root->l = NULL;
  root->r = NULL;

  if(file_read = fscanf(input_fp, "%i", &num) != EOF)
    {
      root->value = num;

      // Read ints until the end of the file
      while((file_read = fscanf(input_fp, "%i", &num)) != EOF)
        {
          insert(root, num);
        }
    }
  else
    root = NULL;

  breadth_first(root, output_fp);

  /* if(strncmp(argv[2], "br", 2) == 0) */
  /*     breadth_first(root, output_fp); */
  /* else if(strncmp(argv[2], "pr", 2) == 0) */
  /*   pre_order(root, output_fp); */
  /* else if(strncmp(argv[2], "in", 2) == 0) */
  /*   in_order(root, output_fp); */
  /* else if(strncmp(argv[2], "po", 2) == 0) */
  /*   post_order(root, output_fp); */
  /* else */
  /*   printf("Invalid traversal command. Please re-run with in order, pre order, post order, or breadth first.\n"); */
  return 0;
} //main

tnode_t * make_tnode(int num)
{
  tnode_t * new_tnode = (tnode_t*)malloc(sizeof(tnode_t));
  new_tnode->value = num;
  new_tnode->l = NULL;
  new_tnode->r = NULL;
  return new_tnode;
}

tnode_t* find (tnode_t* root, int num)
{
  tnode_t* cur = root;
  while(cur != NULL && cur->value != num)
    {
      if(num < cur->value)
        cur = cur->l;
      else
        cur = cur->r;
    }
  return cur;
}

void insert (tnode_t* root, int num)
{
  tnode_t* cur = root;
  while(cur->value != num)
    {
      if(num < cur->value)
        {
          if(cur->l == NULL)
            {
              cur->l = make_tnode(num);
              cur->l->l = NULL;
              cur->l->r = NULL;
            }
          else
            cur = cur->l;
        }
      else
        {
          if(cur->r == NULL)
            {
              cur->r = make_tnode(num);
              cur->r->l = NULL;
              cur->r->r = NULL;
            }
          else
            cur = cur->r;
        }
    }
}

void delete (tnode_t* root, int num)
{
  tnode_t* cur = (tnode_t*)malloc(sizeof(tnode_t));
  tnode_t* l = (tnode_t*)malloc(sizeof(tnode_t));
  tnode_t* r = (tnode_t*)malloc(sizeof(tnode_t));
  cur = root;
  l = cur->l;
  r = cur->r;
  while(l != NULL && r != NULL && l-> value != num && r->value != num)
    {
      if(l->value == num)
        {
          cur->l = NULL;
          free(l);
        }
      else if(r->value == num)
        {
          cur->r = NULL;
          free(r);
        }
      if(num < cur->value)
        {
          cur = l;
          l = cur->l;
          r = cur->r;
        }
      else if(num > cur->value)
        {
          cur = r;
          l = cur->l;
          r = cur->r;
        }
    }
}

void pre_order(tnode_t* root, FILE* output)
{
  if(root != NULL)
    {
      fprintf(output, "%i ", root->value);
      if(root->l != NULL)
        pre_order(root->l, output);
      if(root->r != NULL)
        pre_order(root->r, output);
    }
  else
    fprintf(output, "Empty tree");
}

void in_order(tnode_t* root, FILE* output)
{
  if(root != NULL)
    {
      if(root->l != NULL)
        in_order(root->l, output);
      fprintf(output, "%i ", root->value);
      if(root->r != NULL)
        in_order(root->r, output);
    }
  else
    fprintf(output, "Empty tree");
}

void post_order(tnode_t* root,FILE* output )
{
  if(root != NULL)
    {
      if(root->l != NULL)
        post_order(root->l, output);
      fprintf(output, "%i ", root->value);
      if(root->r != NULL)
        post_order(root->r, output);
    }
  else
    fprintf(output, "Empty tree");
}

qnode_t* make_qnode(tnode_t* n)
{
  qnode_t* new_node = (qnode_t*)malloc(sizeof(qnode_t));
  new_node->node = n;
  new_node->next = NULL;
  return new_node;
}


void enqueue (qnode_t* head, tnode_t* node)
{
  qnode_t* new_node = make_qnode(node);
  if(head == NULL)
    head = new_node;
  else
    {
      while(head->next != NULL)
        {
          head = head->next;
        }
      head->next = new_node;
    }
}


tnode_t* dequeue (qnode_t* head)
{
  if(head == NULL)
    return NULL;
  qnode_t* tmp = (qnode_t*)malloc(sizeof(qnode_t));
  tmp = head;
  head = head->next;
  return tmp->node;
}

 
void breadth_first(tnode_t* root, FILE* output)
{
  qnode_t* head = (qnode_t*)malloc(sizeof(qnode_t));
  tnode_t* tmp = (tnode_t*)malloc(sizeof(tnode_t));
  head = NULL;
  enqueue(head, root);
  while((tmp = dequeue(head)) != NULL)
    {
      fprintf(output, "%i ", tmp->value);
      if(tmp->l != NULL)
        enqueue(head, tmp->l);
      if(tmp->r != NULL)
        enqueue(head, tmp->r);
      //tmp = dequeue(head);
    }
}


/*
  Refernces:
  http://www.geeksforgeeks.org/level-order-tree-traversal/
*/
