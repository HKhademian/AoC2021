typedef struct QNode {
  size_t row,col;
  U32 cost;
  struct QNode *next;
} QNode;

void   printQ (QNode **head);
QNode* enqueue(QNode **head, size_t row, size_t col, U32 cost);
QNode* dequeue(QNode **head);

void printQ(QNode **head) {
  printf("Queue:\n"); 
  if(!head || !*head) printf("- Empty\n");
  else {
    QNode *node = *head;
    while(node!=NULL)
      printf("- [%lu:%lu]=%lu\n", node->row, node->col, node->cost), node=node->next;
  }
  printf("EndOfQueue\n"); 
}

QNode* enqueue(QNode **queue, size_t row, size_t col, U32 cost) {
  printf("\nenqueueing [%lu:%lu]=%lu\n", row,  col,  cost);

  //search for existing node
  QNode *prev=NULL, *node = *queue;
  while(node!=NULL && !(node->row==row && node->col==col))
    prev=node, node=node->next;
  //new if not exists
  if(node==NULL){
    prev = NULL;
    node = (QNode*) calloc(1, sizeof(QNode));
    node->next = NULL;
    node->row = row;
    node->col = col;
  }
  
  // update props
  node->cost = cost;
  
  // remove from queue
  if(prev!=NULL)
    prev->next = node->next;
  else if(node==*queue)
    *queue=node->next;
  
  if(*queue==NULL) {
    // make node as queue head
    *queue = node;
  } else {
    // find node position which bigger cost
    QNode *cur = *queue;
    prev = NULL;
    while(cur->next!=NULL && cur->next->cost < cost)
      prev=cur, cur=cur->next;

    if(cur->cost >= cost) {
      // add node before cur
      node->next = cur;
      if(prev != NULL) {
        prev->next = node;
      } else {
        *queue = node;
      }
    } else {
      // add node after cur
      node->next=cur->next;
      cur->next=node;
    }
  }

  return node;
}

QNode* dequeue(QNode **queue) {
  QNode *node = *queue;
  if(node!=NULL){
    *queue = node->next;
    printf("\ndequeue [%lu:%lu]=%lu\n", node->row, node->col, node->cost);
  }
  return node;
}
