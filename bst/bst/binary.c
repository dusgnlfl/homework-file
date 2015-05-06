#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct bst Bst;
struct bst { //Ʈ�������� ǥ���ϱ� ���� ����ü(�����͸� �����ϴ� char*������ ���� ������ ���ϵ带 ������ ����ü ����
	Bst* leftchild;
	Bst* rightchild;
	char* value;
};

Bst* allocationTree(char data[]); //���� ���ԵǴ� ���鿡�� �޸𸮸� �Ҵ��ϰ� ���� �����ϴ� �Լ�
void insertTree(Bst* bst, Bst* insertnode); //��带 �߰��Ͽ� Ʈ���� Ȯ���ϴ� �Լ�
void inorderprint(Bst* bst); //������ȸ�� Ʈ���� ����ϴ� �Լ�
Bst* removeTree(Bst* bst, char data[]); //data�� �ش��ϴ� ���� ���� ��带 �����ϴ� �Լ�
int accountNumnode(Bst* bst); //����Ʈ���� ��� ���� ����ϴ� �Լ�
int accountDepth(Bst* bst); //����Ʈ���� �ִ� ���̸� ����ϴ� �Լ�
Bst* selectmin(Bst* bst); //������ ����Ʈ������ ��ü�� ���� ���� ���� ���� �Լ�
Bst* selectmax(Bst* bst); //���� ����Ʈ������ ��ü�� ���� ū ���� ���� �Լ�

int leftdepth=0; //���� ������ ����Ʈ���� ���̿� ������ �����ϴ� ��������
int rightdepth=0;
int leftnumnode=0;
int rightnumnode=0;

void main(void) {
	int i;
	Bst* bst=allocationTree("one"); //ù ��Ʈ Ʈ����带 ����
	char* data; //�Է½� ����� �Է��� ���� ����
	char removedata[5]; //������ ����� �Է��� ���� ����

	inorderprint(bst);
	printf("\n");
	for(i=1; i<=19; i++) { //19�� �ݺ��ϸ鼭 twet���� �Է��Ѵ�.
		printf("���ο� ��� �Է� : ");
		data=(char*)malloc(sizeof(char)*5);
		scanf("%s", data);
		insertTree(bst, allocationTree(data));
		inorderprint(bst);
		printf("\n");
	}
	for(i=1; i<=20; i++) { //�� 20�� �Է��� ������ �Է¼����� �����ϱ� ���� �ݺ����̴�.
		printf("���� �� ��� �Է� : ");
		scanf("%s", removedata);
		removeTree(bst, removedata);
		inorderprint(bst);
		printf("\n");
		leftdepth=0; //������ ����� ���� ����Ʈ���� ���ϱ� ���� ���������� �Ҷ����� �ʱ�ȭ�Ѵ�.
		rightdepth=0;
		leftnumnode=0;
		rightnumnode=0;
	}
}

void inorderprint(Bst* bst) { //���� ��ȸ�� ������ �Լ�
	if(bst==NULL)
		return;
	inorderprint(bst->leftchild);
	printf("%s ", bst->value);
	inorderprint(bst->rightchild);
}

Bst* allocationTree(char data[]) { //�� ��带 ���� �޸� �Ҵ��� �ϴ� �Լ�
	Bst* temp=(Bst*)malloc(sizeof(Bst));
	temp->leftchild=NULL;
	temp->rightchild=NULL;
	temp->value=data;

	return temp;
}

void insertTree(Bst* bst, Bst* insertnode) { //��带 �����ϴ� �Լ�
	if(strcmp(bst->value,insertnode->value)>0) { //���ڿ��̱� ������ strcmp�� ����Ͽ� ũ���
		if(bst->leftchild==NULL) //���� ���̱� ������ ������ ���̸� �����ϰ� �ƴϸ� ��ͷ� ��� �θ���.
			bst->leftchild=insertnode;
		else
			insertTree(bst->leftchild, insertnode);
	}
	else {
		if(bst->rightchild==NULL) //�Է� ���ڿ��� ū���϶� �������� Ȯ���ϰ� �����ϰ� ��ͷ� �θ���.
			bst->rightchild=insertnode;
		else
			insertTree(bst->rightchild, insertnode);
	}
}

Bst* removeTree(Bst* bst, char data[]) { //��� ���� �Լ�
	Bst* temp;

	if(bst==NULL)
		return bst;
	else if(strcmp(bst->value,data)>0) //�����͸� ���Ͽ� ���� ���������� Ʈ���� �̵���Ų��.
		bst->leftchild=removeTree(bst->leftchild, data);
	else if(strcmp(data,bst->value)>0)
		bst->rightchild=removeTree(bst->rightchild, data);
	else if(strcmp(data,bst->value)==0) { //������ ��带 ã�� ���
		if(bst->leftchild!=NULL && bst->rightchild!=NULL) { //������ ����� �ڽ��� �ΰ��� ���
			leftdepth=accountDepth(bst->leftchild); //�� ����Ʈ���� ���̿� ������ ���
			leftnumnode=accountNumnode(bst->leftchild);
			rightdepth=accountDepth(bst->rightchild);
			rightnumnode=accountNumnode(bst->rightchild);

			if(leftdepth>rightdepth) { //����� ���̰� ���� �ʿ��� �۰ų� ū���� ��带 ��� ����
				temp=selectmax(bst->leftchild);
				bst->value=temp->value;
				bst->leftchild=removeTree(bst->leftchild, temp->value);
			}
			if(leftdepth<rightdepth) {
				temp=selectmin(bst->rightchild);
				bst->value=temp->value;
				bst->rightchild=removeTree(bst->rightchild, temp->value);
			}
			if(leftdepth==rightdepth && leftnumnode>rightnumnode) { //���̰� ���Ƽ� ������ ���Ͽ� ��带 ����.
				temp=selectmax(bst->leftchild);
				bst->value=temp->value;
				bst->leftchild=removeTree(bst->leftchild, temp->value);
			}
			if(leftdepth==rightdepth && leftnumnode<rightnumnode) {
				temp=selectmin(bst->rightchild);
				bst->value=temp->value;
				bst->rightchild=removeTree(bst->rightchild, temp->value);
			}
			if(leftdepth==rightdepth && leftnumnode==rightnumnode) { //���̿� ���� ��� ���� ���ʼ���Ʈ������ �����Ѵ�.
				temp=selectmax(bst->leftchild);
				bst->value=temp->value;
				bst->leftchild=removeTree(bst->leftchild, temp->value);
			}
		}
		else { //�ڽ� ��尡 �ϳ��ų� ���� ����� ���� ����
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