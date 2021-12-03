// LIST
typedef struct{
	int data[idx];
	int size;
}List;
void makenullList(List *l){
	l->size=0;
}
void pushList(List *l, int element){
	l->data[l->size]=element;
	l->size++;
}
int getList(List *l, int index){
	return l->data[index-1];
}
bool emptyList(List *l){
	return l->size==0;
}
void copyList(List *l1, List *l2){
	makenullList(l1);
	for(int i=1;i<=l2->size;i++){
		int value = getList(l2,i);
		pushList(l1,value);
	}
}

// Queue
typedef struct{
	int front;
	int rear;
	int data[100];
}Queue;
void makenullQueue(Queue *q){
	q->front=0;
	q->rear=-1;
}
bool emptyQueue(Queue *q){
	return q->front > q->rear;
}
void pushQueue(Queue *q, int element){
	q->rear++;
	q->data[q->rear]=element;
}
int getQueue(Queue *q){
	return q->data[q->front];
}
void plusFront(Queue *q){
	q->front++;
}

// STACK
typedef struct{
	int data[100];
	int size;
}Stack;
void makenullStack(Stack *s){
	s->size=0;
}
bool emptyStack(Stack *s){
	return s->size==0;
}
void pushStack(Stack *s, int element){
	s->data[s->size]=element;
	s->size++;
}
int getStack(Stack *s){
	return s->data[s->size-1];
}
void delSize(Stack *s){
	s->size--;
}
