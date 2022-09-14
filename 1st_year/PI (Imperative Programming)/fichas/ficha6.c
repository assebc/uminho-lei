#include <stdio.h>
#include <stdlib.h>

typedef struct staticStack {

	int sp;
	int values [10];

} *SStack;


void SinitStack(SStack s){

	s->sp = -1;

}

int SisEmpty (SStack s){

	if(s->sp == -1) return 0;

	return 1;
}

int Spush (SStack s, int x){

	if(s->sp == 10) return 1;
	
	s->values[++s->sp] = x;	

	return 0;

}

int Spop (SStack s, int *x){

	if (!SisEmpty(s)) return 1;

	*x = s->values[s->sp--];
	return 0;
}

void ShowSStack (SStack s){
    int i;
    printf ("%d Items: ", s->sp);
    for (i=s->sp-1; i>=0; i--) 
        printf ("%d ", s->values[i]);
    putchar ('\n');
}

int Stop (SStack s, int *x){

	if(!SisEmpty(s)) return 1;

	*x = s->values[s->sp];
	return 0;
}

// ================================== //

typedef struct staticQueue {

	int front;
	int length;
	int values[10];

} *SQueue;

void SinitQueue(SQueue q){

	q->front = 0;
	q->length = 0;

}

int SisEmptyQ (SQueue q){

	if(q->front == 0 && q->length == 0) return 1;

	return 0;
}

int Senqueue (SQueue q, int x){

	if(q->front == 10 && q->length == 10) return 1;

	q->values[++q->front] = x;
	q->length++;

	return 0;
}

int Sdequeue (SQueue q, int *x){

	if(SisEmptyQ(q)) return 1;

	*x = q->values[q->front++];
	return 0;
}

int Sfront (SQueue q, int *x){

	if(SisEmptyQ(q)) return 1;

	*x = q->values[q->front];

	return 0;
}

void ShowSQueue (SQueue q){
    int i, p;
    printf ("%d Items: ", q->length);
    for (i=0, p=q->front; i<q->length; i++) {
        printf ("%d ", q->values[p]);
        p = (p+1)%10;
    }
    putchar ('\n');
}

int main(){

  int i ; 
  struct staticStack s1;
  SStack S1 = &s1;
  
  struct staticQueue q1;
  SQueue Q1 = &q1;
  
  
  printf ("Testing Stacks .... \n");
  SinitStack (S1);
  for (i=0; i<15; i++) 
  	if (Spush (S1,i) != 0) printf ("ERROR pushing %d\n", i);
  
  ShowSStack (S1);
  
  printf ("Testing Queues .... \n");
  SinitQueue (Q1);
  for (i=0; i<15; i++) {
    if (Senqueue (Q1,i) != 0) printf ("ERROR enqueueing %d\n", i);
  }
  ShowSQueue (Q1);


	return 0;
}