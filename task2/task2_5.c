#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node *link;
char str[200];

typedef struct Node {
	char * elem;
	link next;
} node;

typedef link list;

list lst;

char equal_to_str(char *a){
	char res = 1;
	int n = 0;
	if (*str != *a)
		return 0;
	while (*(str + n) && *(a + n) && *(str + n) == *(a + n)) {
		n++;
		if (*(str + n) != *(a + n)) {
			return 0;
		}
	}
	return 1;
}

void print_lst(list p) {
	if (p) {
		printf("%s ", p->elem);
		print_lst(p->next);
	}
}

list create(char *s, int len) {
	list res;
	res = (link) malloc(sizeof(node));
	link last = (list) malloc(sizeof(node));
	char * elem = calloc(sizeof(s), len);
	int n = 0;
	while (*(s + n)) {
		*(elem + n) = *(s + n);
		n++;
	}
	*(elem + n) = '\0';
	res->next = last;
	last->elem = elem;
	elem = calloc(sizeof(s), len);
	*elem = '\0';
	res->elem = elem;
	last->next = NULL;
	return res;
}

int empty (list p){
/* is stack empty? */
    return p==NULL;
}

void in_last(list *p, char *s, int len){
/* insert element s at the end */
    link q;
    link t;
    q = malloc(sizeof(node));
    char * elem = calloc(sizeof(s), len);
	int n = 0;
	while (*(s + n)) {
		*(elem + n) = *(s + n);
		n++;
	}
	*(elem + n) = '\0';
    q->elem = elem;
    q->next = NULL;
    t = *p;
    while(t->next) 
		t = t->next;
    t->next = q;   
}

void free_lst(list *p){
	link t;
    if(empty(*p))
        return;
    if((*p)->next == NULL){
        free((*p)->elem);
        free(*p);
        return;
    }
    t = *p;
    while(t->next->next != NULL){
        t = t->next;
    }
    free(t->next->elem);
    free(t->next);
    t->next = NULL;
    free_lst(p);
}

void delete_equal_to_last(link cur) {
	if (cur == NULL)
		return;
	if (cur->next == NULL)
		return;
	if (cur->next->next == NULL)
		return;
	if (equal_to_str(cur->next->elem)) {
		link rem = cur->next->next;
		free(cur->next->elem);
		free(cur->next);
		cur->next = rem;
		delete_equal_to_last(cur);
	} else {
		delete_equal_to_last(cur->next);
	}
}

int main(void) 
{	
	lst = NULL;
	if (scanf("%s", str) == 1) {
		lst = create(str, sizeof(str));
		while (scanf("%s", str) == 1) {
			in_last(&lst, str, sizeof(str));
		}
		delete_equal_to_last(lst);
		print_lst(lst->next);
		free_lst(&(lst));
	}
	printf("\n");
	return 0;
}
