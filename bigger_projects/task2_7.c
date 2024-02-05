#include <stdio.h>
#include <setjmp.h>
#include <stdlib.h>

jmp_buf begin;

typedef struct el_exp *link;

struct el_exp {
	long long elem;
	link pointer_to_next;
	link pointer_to_prev;
	char end_true;
} node;

typedef link list;

list lst = NULL;

link cur;

char curlex;

void getlex(void);

long long expr(void); 
long long add(void); 
long long mult(void);
long long expon(void); 
void free_lst(list *p);
int empty (list p);
long long exp_n(long long n, long long x);
void error();

void print_lst(list p) {
	if (p) {
		printf("%lld ", p->elem);
		print_lst(p->pointer_to_next);
	}
}

list create (long long n) {
	link cur;
	list res;
	res = malloc(sizeof(node));
	res->pointer_to_next = NULL;
	res->elem = n;
	res->pointer_to_prev = NULL;
	res->end_true = 1;
	return res;
}


int empty (list p){
/* is stack empty? */
    return p==NULL;
}

void free_lst(list *p) {
	link t;
    if(empty(*p)) {
        return;
    }
    if((*p)->pointer_to_next == NULL) {
		free(*p);
		lst = NULL;
		return;
	}
    t = *p;
    while(t->pointer_to_next->pointer_to_next != NULL){
        t = t->pointer_to_next;
    }
    free(t->pointer_to_next);
    t->pointer_to_next = NULL;
    free_lst(p);
}

void add_list (list *cur, long long n) {
	link new_list = malloc(sizeof(node));
	new_list->elem = n;
	new_list->pointer_to_next = NULL;
	new_list->pointer_to_prev = *cur;
	(*cur)->pointer_to_next = new_list;
	new_list->end_true = 0;
}

int main(void)
{ 
	long long result;
	setjmp(begin);
	printf("==>");
	getlex();
	result = expr();
	if (curlex != '\n') 
		error();
	printf("\n%lld\n", result);
	free_lst(&lst);
	free(lst);
	return 0;
}

void getlex() 
{
	 while ((curlex=getchar()) == ' ');
}

void error(void)
{ 
	printf("\nОШИБКА!\n");
	while(getchar() != '\n');
	longjmp(begin,1);
}

long long expr()
{ 
	long long e = add();
	while (curlex == '+' || curlex == '-') { 
		if (curlex == '+') {
			getlex(); 
			e += add();
		} else {
			getlex(); 
			e -= add();
		}
	}
	return e;
}

long long add()
{ 
	long long a = mult();
	while (curlex == '*' || curlex == '/'){ 
		if (curlex == '*') {
			getlex(); 
			a *= mult();
		} else {
			getlex(); 
			a /= mult();
		}
	}
	return a;
}

long long mult(void) {
	long long a = expon();
	if (lst == NULL) {
		lst = create(a);
		lst->end_true = 1;
	} else {
		cur = lst;               
		while (cur->pointer_to_next)
			cur = cur->pointer_to_next;
		add_list(&cur, a);
		cur->end_true = 1;
	}
	while (curlex == '^'){
		getlex();
		a = expon();
		cur = lst;
		while (cur->pointer_to_next)
			cur = cur->pointer_to_next;
		add_list(&cur, a);
		cur->end_true = 0;
	}
	cur = lst;
	while (cur->pointer_to_next)
		cur = cur->pointer_to_next;
	while (cur->pointer_to_prev && cur->pointer_to_prev->end_true == 0) {
		a = exp_n(cur->elem, cur->pointer_to_prev->elem);
		cur = cur->pointer_to_prev;
		free(cur->pointer_to_next);
		cur->pointer_to_next = NULL;
		cur->elem = a;
	}
	if (cur->pointer_to_prev && cur->pointer_to_prev->end_true) {
		link del = cur;
		cur = cur->pointer_to_prev;
		free(del);
		cur->pointer_to_next = NULL;
	}
	return a;
}

long long exp_n(long long n, long long x) {
	long long res = 1;
	if (n < 0) {
		error();
		free_lst(&lst);
	} else {
		for (long long i = 0; i < n; i++) {
			res *= x;
		}	
	}
	return res;
}

long long expon()
{
	long long m;
	switch(curlex){
		case '0': case '1': case '2': case '3': case '4': 
		case '5':case '6': case '7': case '8': case '9': 
			m = curlex - '0'; 
			break;
		case '(': 
			getlex(); 
			m = expr();
			if (curlex == ')') 
				break;
		default: error();
	}
	getlex();
	return m;
}	 
