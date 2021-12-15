typedef signed int long I32;

typedef struct QNode {
  I32 row, col, cost;
  struct QNode *next;
} QNode;

#ifdef HEAP_DEBUG
  #define DEBUG_printf(...) printf(__VA_ARGS__)
#else
  #define DEBUG_printf(...) ;
#endif

void printQ(const QNode *head) {
  QNode* node = head->next;
  printf("Queue:\n"); 
  if(!node)
    printf("- Empty\n");
  else while(node)
    printf("- [%lu:%lu]=%lu\n", node->row, node->col, node->cost),
    node=node->next;
  printf("EndOfQueue\n"); 
}

QNode* enqueue(QNode *head, I32 row, I32 col, I32 cost) {
  DEBUG_printf("enqueueing [%ld:%ld]=%ld\n", row,  col,  cost);

  //search for existing node
  QNode *node = (QNode*) calloc(1, sizeof(QNode));
  node->next = NULL;
  node->row = row;
  node->col = col;
  node->cost = cost;
  
  // find node position which bigger cost
  QNode *cur = head;
  while(cur->next && cur->next->cost < cost)
    cur=cur->next;

  // add node after cur
  node->next=cur->next;
  cur->next=node;

  return node;
}

QNode* dequeue(QNode *head) {
  QNode *node = head->next;
  head->next = node==NULL? NULL : node->next;
  if(node)
    DEBUG_printf("dequeue [%ld:%ld]=%ld\n", node->row, node->col, node->cost);
  return node;
}
