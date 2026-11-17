#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PAGE_TIME 2

typedef struct {
int id;
int pages;
} Job;

typedef struct Node {
Job job;
struct Node *next;
} Node;

typedef struct {
Node *head;
Node *tail;
int size;
} Queue;

void queue_init(Queue *q) {
q->head = NULL;
q->tail = NULL;
q->size = 0;
}

int is_empty(Queue *q) {
return q->head == NULL;
}

int is_full(Queue *q) {
if (q == NULL) {
return 1;
}
return 0;
}

int enqueue(Queue *q, Job job) {
Node *node = (Node *)malloc(sizeof(Node));
if (node == NULL) {
return 0;
}
node->job = job;
node->next = NULL;

if (q->tail == NULL) {
    q->head = node;
} else {
    q->tail->next = node;
}
q->tail = node;
q->size++;
return 1;
}

int dequeue(Queue *q, Job *out) {
if (is_empty(q)) {
return 0;
}
Node *old = q->head;
*out = old->job;
q->head = old->next;

if (q->head == NULL) {
    q->tail = NULL;
}
free(old);
q->size--;
return 1;
}

int peek_front(Queue *q, Job *out) {
if (is_empty(q)) {
return 0;
}
*out = q->head->job;
return 1;
}

void queue_destroy(Queue *q) {
Job tmp;
while (!is_empty(q)) {
dequeue(q, &tmp);
}
}

void add_job(Queue *q, int pages, int *next_id) {
if (pages <= 0) {
printf("Помилка: кількість сторінок має бути додатною.\n");
return;
}

if (is_full(q)) {
    printf("Черга заповнена: завдання (%d стор.) відхилено.\n", pages);
    return;
}

Job job;
job.id = *next_id;
job.pages = pages;

if (enqueue(q, job)) {
    (*next_id)++;
    printf("Завдання №%d (%d стор.) додано в чергу.\n", job.id, job.pages);
} else {
    printf("Не вдалося додати завдання (%d стор.) у чергу.\n", pages);
}
}

void print_next_job(Queue *q, int *clock, int *busy) {
if (is_empty(q)) {
printf("Черга порожня: друкувати нічого.\n");
return;
}

Job job;
if (!dequeue(q, &job)) {
    printf("Помилка вилучення з черги.\n");
    return;
}

int duration = job.pages * PAGE_TIME;
int start = *clock;
*clock += duration;
*busy += duration;

printf("Завдання №%d (%d стор.): друк з t=%d с до t=%d с, завершено в момент t=%d с.\n",
       job.id, job.pages, start, *clock, *clock);
}

int main() {
Queue q;
queue_init(&q);

char cmd[32];
int next_id = 1;
int clock = 0;
int busy = 0;

while (scanf("%s", cmd) == 1) {
    if (strcmp(cmd, "add") == 0) {
        int pages;
        if (scanf("%d", &pages) != 1) {
            printf("Помилка: після add потрібне ціле число сторінок.\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
        } else {
            add_job(&q, pages, &next_id);
        }
    } else if (strcmp(cmd, "print") == 0) {
        print_next_job(&q, &clock, &busy);
    } else if (strcmp(cmd, "run") == 0) {
        if (is_empty(&q)) {
            printf("Черга порожня: друкувати нічого.\n");
        }
        while (!is_empty(&q)) {
            print_next_job(&q, &clock, &busy);
        }
    } else if (strcmp(cmd, "quit") == 0) {
        break;
    } else {
        printf("Невідома команда: %s\n", cmd);
    }
}

printf("Сумарний час роботи принтера: %d с.\n", busy);
queue_destroy(&q);
return 0;
}