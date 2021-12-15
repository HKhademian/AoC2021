int main(void) {
  QNode *queue = (QNode*) calloc(1, sizeof(QNode));
  printQ(queue);
  
  enqueue(queue, 0, 0, 8) , printQ(queue);
  enqueue(queue, 1, 0, 10), printQ(queue);
  enqueue(queue, 2, 5, 6) , printQ(queue);
  dequeue(queue)          , printQ(queue);
  enqueue(queue, 2, 3, 9) , printQ(queue);
  enqueue(queue, 1, 3, 4) , printQ(queue);
  enqueue(queue, 0, 0, 7) , printQ(queue);
  enqueue(queue, 9, 9, 15), printQ(queue);
   
  do dequeue(queue), printQ(queue);
  while (queue->next);
  
  return 0;
}
