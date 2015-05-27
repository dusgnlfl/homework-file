#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct avl Avl; //Ʈ�� ������ ǥ���� ����ü�̴�.
struct avl {
	Avl* leftchild; //���� ������ ���ϵ带 ������ ����ü ����
	Avl* rightchild;
	char* value; //�����͸� ������ ����
};

Avl* avl; //root���� �����ذ��� �޸� �Ҵ��� ���� �߰��ȴ�.
int recnt=0; //����� ���θ� �Ǵ��ϱ� ���� ����
int recycletype=0; //������� �ҽÿ� � Ÿ���� ȸ���� �ϴ��� �Ǵ��ϴ� ����

Avl* allocationTree(char data[]); //���� ���ԵǴ� ���鿡�� �޸𸮸� �Ҵ��ϰ� ���� �����ϴ� �Լ�
Avl* insertTree(Avl* avl, char data[]); //��带 �߰��Ͽ� Ʈ���� Ȯ���ϴ� �Լ�
void inorderprint(Avl* avl); //������ȸ�� Ʈ���� ����ϴ� �Լ�
int accountDepth(Avl* avl); //����Ʈ���� �ִ� ���̸� ����ϴ� �Լ�
Avl* rebalanceLL(Avl* node); //LLȸ�� ����� �����ϴ� �Լ�
Avl* rebalanceRR(Avl* node); //RRȸ�� ����� �����ϴ� �Լ�
Avl* rebalanceRL(Avl* node); //RLȸ�� ����� �����ϴ� �Լ�
Avl* rebalanceLR(Avl* node); //LRȸ�� ����� �����ϴ� �Լ�
Avl* recycletree(Avl* recycleavl); //Ʈ���� ������� �ؾ��ϴ��� �Ǵ��ϴ� �Լ�

void main(void) {
	int i;
	char* data; //�Է½� ����� �Է��� ���� ����

	for(i=1; i<=30; i++) { //30���� �Է��� �ϱ����� �ݺ���
		printf("���ο� ��� �Է� : ");
		data=(char*)malloc(sizeof(char)*5); //�Է� ���ڿ��� �����ϴ� ������ �޸� �Ҵ�
		scanf("%s", data);
		avl=insertTree(avl, data); //���ο� ��带 �����ϰ� avl���θ� �Ǵ��ϴ� �Լ��� �θ���.
		if(recnt==0) //�������� 0�Ͻÿ��� ������� �Ͼ�� ���� ����
			printf("����� No\n");
		else { //0�� �ƴ� ������ ����ǰ� ������� �Ͼ ����
			printf("����� Yes ---");
			if(recycletype==1) //������ ���� 1,2,3,4�� ���� ȸ�� ���� ���
				printf("����� Ÿ�� : LL\n");
			else if(recycletype==2)
				printf("����� Ÿ�� : LR\n");
			else if(recycletype==3)
				printf("����� Ÿ�� : RR\n");
			else
				printf("����� Ÿ�� : RL\n");
		}
		inorderprint(avl);
		printf("\n");
		recnt=0;
	}
}

void inorderprint(Avl* avl) { //���� ��ȸ�� ������ �Լ�
	if(avl==NULL)
		return;
	inorderprint(avl->leftchild);
	printf("%s ", avl->value);
	inorderprint(avl->rightchild);
}

Avl* allocationTree(char data[]) { //�� ��带 ���� �޸� �Ҵ��� �ϴ� �Լ�
	Avl* temp=(Avl*)malloc(sizeof(Avl));
	temp->leftchild=NULL;
	temp->rightchild=NULL;
	temp->value=data;

	return temp;
}

Avl* insertTree(Avl* avl, char data[]) { //��带 �����ϴ� �Լ�
	if(avl==NULL) //��尡 �����Ͻÿ� �޸��Ҵ��� ���ְ� �����Ѵ�.
		avl=allocationTree(data);
	else if(strcmp(avl->value,data)>0) { //���ڿ��̱� ������ strcmp�� ����Ͽ� ũ���
		avl->leftchild=insertTree(avl->leftchild, data); //���ڿ� ���� ���� ��� ���� ���ϵ�� ��͸� ���� ��� �̵��Ѵ�.
		avl=recycletree(avl); //������� �ʿ����� �Ǵ��ϴ� �Լ� ȣ��
	}
	else { //���ڿ� ���� ū ����� ����
		avl->rightchild=insertTree(avl->rightchild, data);
		avl=recycletree(avl);
	}
	return avl;
}

int accountDepth(Avl* avl) { //����� ���̸� ���������� ��ȯ�ϴ� �Լ�
	if(avl==NULL)
		return 0;
	else {
		int templeft,tempright;
		templeft=accountDepth(avl->leftchild)+1; //���� ������ ���ϵ�� ��ͷ� �ҷ����鼭 ���̰� 1�� ��������.
		tempright=accountDepth(avl->rightchild)+1;
		if(templeft<tempright) //���� ū ������ �ִ� ���̷� ��ȯ�ȴ�.
			return tempright;
		else
			return templeft;
	}
}

Avl* recycletree(Avl* recycleavl) { //������� �ʿ����� �Ǵ��ϴ� �Լ�
	int avldepth=accountDepth(recycleavl->leftchild)-accountDepth(recycleavl->rightchild); //���������� ���ʰ� ������ ���ϵ� ���̸� ���ؼ� ���� ���Ѵ�.
    if(avldepth>1) { //���� ���ϵ��� ������ ���� ����̴�.
		recnt=1; //������ �������Ƿ� ������� �ϱ⶧���� ����� �Ǵ� �������� �����Ѵ�.
        if((accountDepth((recycleavl->leftchild)->leftchild)-accountDepth((recycleavl->leftchild)->rightchild))>0) {
			//���� ���ϵ��� ����Ʈ�� ���̰� ����, �������� �� ������ �Ǵ��ϴ� ����
			recycleavl=rebalanceLL(recycleavl);  //������ �� ������ LLȸ�� ����̴�.
			recycletype=1;
		}
        else  {
            recycleavl=rebalanceLR(recycleavl);  //�������� �� �����Ƿ� LRȸ�� ����̴�.
			recycletype=2;
		}
    } 
    else if(avldepth<-1) { //������ ���ϵ��� ������ ���� ����̴�.
		recnt=1;
        if((accountDepth((recycleavl->rightchild)->leftchild)-accountDepth((recycleavl->rightchild)->rightchild))<0) {
            recycleavl=rebalanceRR(recycleavl); 
			recycletype=3;
		}
        else {
            recycleavl=rebalanceRL(recycleavl); 
			recycletype=4;
		}
    }
	return recycleavl;
}

Avl* rebalanceLL(Avl* node) { //LLȸ���� �����ϴ� �Լ�
    Avl* subnode=node->leftchild; //���� ��带 �����ؼ� ȸ���� �����ش�.
    node->leftchild=subnode->rightchild; 
    subnode->rightchild=node; 
    return subnode; 
} 

Avl* rebalanceRR(Avl* node) { //RRȸ���� �����ϴ� �Լ�
    Avl* subnode=node->rightchild; 
    node->rightchild=subnode->leftchild; 
    subnode->leftchild=node; 
    return subnode; 
} 

Avl* rebalanceRL(Avl* node) { //RLȸ���� �����ϴ� �Լ�
    Avl* subnode=node->rightchild; //RL�� ��� �κ������� ���� LLȸ���� ���ְ� ��ü������ RRȸ���� �ٽ��ؼ� ��ȯ�Ѵ�.
    node->rightchild=rebalanceLL(subnode); 
    return rebalanceRR(node); 
} 

Avl* rebalanceLR(Avl* node) { //LRȸ���� �����ϴ� �Լ�
    Avl* subnode=node->leftchild; 
    node->leftchild=rebalanceRR(subnode); 
    return rebalanceLL(node); 
}