#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct bst Bst;
struct bst { //트리구조를 표현하기 위한 구조체(데이터를 저장하는 char*변수와 왼쪽 오른쪽 차일드를 저장할 구조체 변수
	Bst* leftchild;
	Bst* rightchild;
	char* value;
};

Bst* allocationTree(char data[]); //새로 삽입되는 노드들에게 메모리를 할당하고 값을 지정하는 함수
void insertTree(Bst* bst, Bst* insertnode); //노드를 추가하여 트리를 확장하는 함수
void inorderprint(Bst* bst); //중위순회로 트리를 출력하는 함수
Bst* removeTree(Bst* bst, char data[]); //data에 해당하는 값을 가진 노드를 제거하는 함수
int accountNumnode(Bst* bst); //서브트리의 노드 수를 계산하는 함수
int accountDepth(Bst* bst); //서브트리의 최대 깊이를 계산하는 함수
Bst* selectmin(Bst* bst); //오른쪽 서브트리에서 교체할 가장 작은 값을 고르는 함수
Bst* selectmax(Bst* bst); //왼쪽 서브트리에서 교체할 가장 큰 값을 고르는 함수

int leftdepth=0; //왼쪽 오른쪽 서브트리의 깊이와 노드수를 저장하는 전역변수
int rightdepth=0;
int leftnumnode=0;
int rightnumnode=0;

void main(void) {
	int i;
	Bst* bst=allocationTree("one"); //첫 루트 트리노드를 생성
	char* data; //입력시 사용자 입력을 받을 변수
	char removedata[5]; //삭제시 사용자 입력을 받을 변수

	inorderprint(bst);
	printf("\n");
	for(i=1; i<=19; i++) { //19번 반복하면서 twet까지 입력한다.
		printf("새로운 노드 입력 : ");
		data=(char*)malloc(sizeof(char)*5);
		scanf("%s", data);
		insertTree(bst, allocationTree(data));
		inorderprint(bst);
		printf("\n");
	}
	for(i=1; i<=20; i++) { //총 20번 입력의 역순과 입력순서로 삭제하기 위한 반복문이다.
		printf("삭제 할 노드 입력 : ");
		scanf("%s", removedata);
		removeTree(bst, removedata);
		inorderprint(bst);
		printf("\n");
		leftdepth=0; //삭제할 노드의 양쪽 서브트리를 비교하기 위한 전역변수를 할때마다 초기화한다.
		rightdepth=0;
		leftnumnode=0;
		rightnumnode=0;
	}
}

void inorderprint(Bst* bst) { //중위 순회를 구현한 함수
	if(bst==NULL)
		return;
	inorderprint(bst->leftchild);
	printf("%s ", bst->value);
	inorderprint(bst->rightchild);
}

Bst* allocationTree(char data[]) { //새 노드를 위해 메모리 할당을 하는 함수
	Bst* temp=(Bst*)malloc(sizeof(Bst));
	temp->leftchild=NULL;
	temp->rightchild=NULL;
	temp->value=data;

	return temp;
}

void insertTree(Bst* bst, Bst* insertnode) { //노드를 삽입하는 함수
	if(strcmp(bst->value,insertnode->value)>0) { //문자열이기 때문에 strcmp를 사용하여 크기비교
		if(bst->leftchild==NULL) //작은 값이기 때문에 왼쪽이 널이면 대입하고 아니면 재귀로 계속 부른다.
			bst->leftchild=insertnode;
		else
			insertTree(bst->leftchild, insertnode);
	}
	else {
		if(bst->rightchild==NULL) //입력 문자열이 큰값일때 오른쪽을 확인하고 대입하고 재귀로 부른다.
			bst->rightchild=insertnode;
		else
			insertTree(bst->rightchild, insertnode);
	}
}

Bst* removeTree(Bst* bst, char data[]) { //노드 삭제 함수
	Bst* temp;

	if(bst==NULL)
		return bst;
	else if(strcmp(bst->value,data)>0) //데이터를 비교하여 왼쪽 오른쪽으로 트리를 이동시킨다.
		bst->leftchild=removeTree(bst->leftchild, data);
	else if(strcmp(data,bst->value)>0)
		bst->rightchild=removeTree(bst->rightchild, data);
	else if(strcmp(data,bst->value)==0) { //삭제할 노드를 찾은 경우
		if(bst->leftchild!=NULL && bst->rightchild!=NULL) { //삭제할 노드의 자식이 두개인 경우
			leftdepth=accountDepth(bst->leftchild); //양 서브트리의 깊이와 노드수를 계산
			leftnumnode=accountNumnode(bst->leftchild);
			rightdepth=accountDepth(bst->rightchild);
			rightnumnode=accountNumnode(bst->rightchild);

			if(leftdepth>rightdepth) { //노드의 깊이가 깊은 쪽에서 작거나 큰값의 노드를 골라서 제거
				temp=selectmax(bst->leftchild);
				bst->value=temp->value;
				bst->leftchild=removeTree(bst->leftchild, temp->value);
			}
			if(leftdepth<rightdepth) {
				temp=selectmin(bst->rightchild);
				bst->value=temp->value;
				bst->rightchild=removeTree(bst->rightchild, temp->value);
			}
			if(leftdepth==rightdepth && leftnumnode>rightnumnode) { //깊이가 같아서 노드수를 비교하여 노드를 고른다.
				temp=selectmax(bst->leftchild);
				bst->value=temp->value;
				bst->leftchild=removeTree(bst->leftchild, temp->value);
			}
			if(leftdepth==rightdepth && leftnumnode<rightnumnode) {
				temp=selectmin(bst->rightchild);
				bst->value=temp->value;
				bst->rightchild=removeTree(bst->rightchild, temp->value);
			}
			if(leftdepth==rightdepth && leftnumnode==rightnumnode) { //깊이와 노드수 모두 같아 왼쪽서브트리에서 선택한다.
				temp=selectmax(bst->leftchild);
				bst->value=temp->value;
				bst->leftchild=removeTree(bst->leftchild, temp->value);
			}
		}
		else { //자식 노드가 하나거나 없을 경우의 제거 수행
			temp=bst;
			if(bst->leftchild==NULL)
				bst=bst->rightchild;
			else if(bst->rightchild==NULL)
				bst=bst->leftchild;
			free(temp);
		}
	}
	return bst;
}

int accountNumnode(Bst* bst) {
	if(bst==NULL)
		return 0;
	else
		return 1+accountNumnode(bst->leftchild)+accountNumnode(bst->rightchild);
}

int accountDepth(Bst* bst) {
	if(bst==NULL)
		return 0;
	else {
		int templeft,tempright;
		templeft=accountDepth(bst->leftchild)+1;
		tempright=accountDepth(bst->rightchild)+1;
		if(templeft<tempright)
			return tempright;
		else
			return templeft;
	}
}

Bst* selectmin(Bst* bst) {
	if(bst==NULL)
		return NULL;
	if(bst->leftchild!=NULL)
		return selectmin(bst->leftchild);
	else
		return bst;
}

Bst* selectmax(Bst* bst) {
	if(bst==NULL)
		return NULL;
	if(bst->rightchild!=NULL)
		return selectmax(bst->rightchild);
	else
		return bst;
}