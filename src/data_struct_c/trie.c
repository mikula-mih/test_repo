#include <stdio.h>

typedef struct {
  Node *children[256];
} Node;

#define NODE_POOL_CAP 1024
Node *node_pool[NODE_POOL_CAP];
size_t node_pool_count = 0;

Node *alloc_node(void)
{
  assert(node_pool_count < NODE_POOL_CAP);
  return &node_pool[node_pool_count++];
}

void insert_text(Node *root, const char *text)
{

}

int main()
{
  printf("done trie\n");

  return 0;
}
