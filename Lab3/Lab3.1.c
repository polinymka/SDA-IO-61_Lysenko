#include <stdio.h>
#include <string.h>

#define QUEUE_SIZE 50
#define PAGE_TIME 2

typedef struct {
int id;
int pages;
} Job;

typedef struct {
Job data[QUEUE_SIZE];
int head;
int tail;
int size;
} Queue;

void queue_init(Queue *q) {
q->head = 0;
q->tail = 0;
q->size = 0;
}

int is_empty(Queue *q) {
return q->size == 0;
}

int is_full(Queue *q) {
return q->size == QUEUE_SIZE;
}

int enqueue(Queue *q, Job job) {
if (is_full(q)) {
return 0;
}
q->data[q->tail] = job;
q->tail = (q->tail + 1) % QUEUE_SIZE;
q->size++;
return 1;
}

int dequeue(Queue *q, Job *out) {
if (is_empty(q)) {
return 0;
}
*out = q->data[q->head];
q->head = (q->head + 1) % QUEUE_SIZE;
q->size--;
return 1;
}

int peek_front(Queue *q, Job *out) {
if (is_empty(q)) {
return 0;
}
*out = q->data[q->head];
return 1;
}

void queue_destroy(Queue *q) {
queue_init(q);
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