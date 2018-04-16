/* 2016112120 오주연 */

#include<stdio.h>

struct node  // 트리를 구현한 구조체 생성
{
	struct node *l;
	int key;
	struct node *r;
}

TreeInit()
{
	struct node *t, *head;
	head = (struct node *) malloc(sizeof *head);  //나무 뿌리 가르키는 head 노드이용
	head->l = NULL;  //빈 나무
	; head->r = NULL;
	head->key = 0;
}

struct node *TreeSearch(struct node *head, int xkey)
	/* input : head - 헤드 포인터
	xkey - 탐색 키
	output : 노드 포인터 */
{
	struct node *t;
	t = head->r;
	while (t != NULL) {
		if (xkey == t->key) return(t);  // 키 탐색
		if (xkey < t->key) t = t->l;  // 더 작은 경우 왼쪽 노드 탐색
		if (xkey > t->key) t = t->r;  // 더 큰 경우 오른쪽 노드 탐색
	}
	return(NULL);
}

TreeInsert(struct node *head, int xkey)
/* input: head - 헤드 포인터
xkey – 삽입 키 */
{
	struct node *p, *t;
	p = head; t = p->r; // 헤드의 오른쪽 노드 확인
	while (t != NULL) {  // 삽입할 곳 탐색
		p = t;
		if (xkey == t->key) return;  // 같은 키가 존재하면 삽입하지 않고 리턴
		else if (xkey < t->key) t = t->l;
		else t = t->r;
	}
	t = (struct node *) malloc(sizeof *t);  // 삽입할 노드 생성
	t->key = xkey; t->l = NULL; t->r = NULL;  // 키와 리스트 생성
	if (xkey < p->key) p->l = t;  // 부모키와 비교
	else p->r = t;  // 위치에 맞게 오른쪽 또는 왼쪽에 삽입
}

TreeDel(struct node *head, int xkey)
{
	struct node *p, *c, *t, *x;
	p = head; x = head;
	x = TreeSearch(x, xkey);  // 삭제할 키 탐색
	if (x == NULL)
		return;
	else t = x;
	if (t->r == NULL)
		x = t->l;
	else if (t->r->l == NULL) {
		x = t->r; x->l = t->l;
	}
	else {
		c = x->r;
		while (c->l->l != NULL)
			c = c->l;  // 오른쪽 트리에서 가장 작은 키 찾기
		x = c->l; c->l = x->r;
		x->l = t->l; x->r = t->r;
	}
	free(t);
	if (xkey < p->key) p->l = x;
	else p->r = x;
}

int main() {
	struct node tree = TreeInit();
	int T1[] = { 20, 6, 2, 4, 16, 10, 8, 12, 14, 9 };
	for (int i = 0; i < 10; i++) {
		TreeInsert(&tree, T1[i]);
	}
	printf("(1) T1 트리에서 10 값 찾고, 10의 오른쪽과 왼쪽 노드 출력하기.\n");
	printf("=> 탐색한 키 '%d'의 오른쪽 노드는 '%d', 왼쪽 노드는 '%d'\n\n\n", TreeSearch(&tree, 10)->key,
		TreeSearch(&tree, 10)->l->key, TreeSearch(&tree, 10)->r->key);

	printf("(2) T1 트리에서 6을 지우고, 다시 10 값을 찾은 후 10의 오른쪽과 왼쪽 노드 출력하기.\n");
	TreeDel(&tree, 6);
	printf("=> 탐색한 키 '%d'의 오른쪽 노드는 '%d', 왼쪽 노드는 '%d'\n", TreeSearch(&tree, 10)->key,
		TreeSearch(&tree, 10)->l->key, TreeSearch(&tree, 10)->r->key);
}
