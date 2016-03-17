/* An implementation of tree traversal for depth-first (pre-order, in-order, and post-order) and breadth-first traversal */
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

// Define node_t
typedef struct node{
  int value;
  struct node * l;
  struct node * r;
}node_t;

// Function signatures
node_t * make_node(int num);
node_t* find (node_t* root, int num);
void insert (node_t* root, int num);
void delete (node_t* root, int num);
void pre_order(node_t* root, FILE* output);
void in_order(node_t* root, FILE* output);
void post_order(node_t* root, FILE* output);

int main(int argc, char** argv) {
  
  // File initialization
  FILE* input_fp;
  FILE* output_fp;
  input_fp = fopen(argv[1], "r");
  //input_fp = fopen("pretest.txt", "r");
  output_fp = fopen("results.txt", "w");

  if(input_fp == NULL)
    {
      perror("Input file failed to open.");
    }
  
  int num;
  int file_read;

  // Declare tree root
  node_t* root = (node_t*)malloc(sizeof(node_t));
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
  //pre_order(root, output_fp);
  in_order(root, output_fp);
  //post_order(root, output_fp)
  return 0;
} //main

node_t * make_node(int num)
{
  node_t * new_node = (node_t*)malloc(sizeof(node_t));
  new_node->value = num;
  new_node->l = NULL;
  new_node->r = NULL;
  return new_node;
}

node_t* find (node_t* root, int num)
{
  node_t* cur = root;
  while(cur != NULL && cur->value != num)
    {
      if(num < cur->value)
        cur = cur->l;
      else
        cur = cur->r;
    }
  return cur;
}

void insert (node_t* root, int num)
{
  node_t* cur = root;
  while(cur->value != num)
    {
      if(num < cur->value)
        {
          if(cur->l == NULL)
            {
              cur->l = make_node(num);
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
              cur->r = make_node(num);
              cur->r->l = NULL;
              cur->r->r = NULL;
            }
          else
            cur = cur->r;
        }
    }
}

void delete (node_t* root, int num)
{
  node_t* cur = (node_t*)malloc(sizeof(node_t));
  node_t* l = (node_t*)malloc(sizeof(node_t));
  node_t* r = (node_t*)malloc(sizeof(node_t));
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

void pre_order(node_t* root, FILE* output)
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

void in_order(node_t* root, FILE* output)
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

void post_order(node_t* root,FILE* output )
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



