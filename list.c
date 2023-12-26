#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

#define NODE_TYPE void *

// Define a structure for generic node.
typedef struct Node {
  NODE_TYPE *data;
  struct Node *next;
} Node;

// Define a structure for a linked list
typedef struct {
  Node *head;
  uint16_t size;
} List;

#define LIST(name) List *name = create_list()

#define PUSH(list, data) push(list, data)

#define DESTROY(list) destroy_list(list)

#define SIZE(list) list->size

#define FOREACH(list, callback) \
  Node *current = list->head; \
  while(current != NULL) { \
    callback(current); \
    current = current->next; \
  } \

// Create a new node
static Node *create_node(void *data) {
  Node *new = (Node*)malloc(sizeof(Node));

  if(new == NULL) {
    fprintf(stderr, "Failed to allocate memory for a new node");
    return NULL;
  }

  new->data = data;
  new->next = NULL;
  return new;
}

static void destroy_node(Node *node) {
  free(node);
}

static void destroy_list(List *list) {
  while(list->head != NULL) {
    Node *tmp = list->head;
    list->head = list->head->next;
    destroy_node(tmp);
  }
  free(list);
}

static void list_debug(Node *node) {
  printf("%s\n", node->data);
}

// This function create a new linked list
static List *create_list() {
  List *new = (List*)malloc(sizeof(List));

  if(new == NULL) {
    fprintf(stderr, "Failed to allocate memory for a new linked list");
    return NULL;
  }

  new->head = NULL;
  new->size = 0;

  return new;
}

static void push(List *list, void *data) {
  Node *new = create_node(data);
  new->next = list->head;
  list->head = new;
  list->size++;
}

int main() {
  LIST(list);

  for(int i = 0; i < 100; i++) {
    PUSH(list, "Foo");
  }

  FOREACH(list, list_debug);

  printf("%zu\n", SIZE(list));

  DESTROY(list);
}
