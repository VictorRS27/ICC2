typedef int elem;
typedef struct list list_t;

list_t *create();
void destroy(list_t *l);
int insert(list_t *l, elem x, void *y);
void *lremove_by_elem(list_t *l, elem cutter);