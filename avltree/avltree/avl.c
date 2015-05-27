#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct avl Avl; //트리 구조를 표현할 구조체이다.
struct avl {
	Avl* leftchild; //왼쪽 오른쪽 차일드를 저장할 구조체 변수
	Avl* rightchild;
	char* value; //데이터를 저장할 변수
};

Avl* avl; //root노드로 삽입해가며 메모리 할당을 통해 추가된다.
int recnt=0; //재균형 여부를 판단하기 위한 변수
int recycletype=0; //재균형을 할시에 어떤 타입의 회전을 하는지 판단하는 변수

Avl* allocationTree(char data[]); //새로 삽입되는 노드들에게 메모리를 할당하고 값을 지정하는 함수
Avl* insertTree(Avl* avl, char data[]); //노드를 추가하여 트리를 확장하는 함수
void inorderprint(Avl* avl); //중위순회로 트리를 출력하는 함수
int accountDepth(Avl* avl); //서브트리의 최대 깊이를 계산하는 함수
Avl* rebalanceLL(Avl* node); //LL회전 기능을 수행하는 함수
Avl* rebalanceRR(Avl* node); //RR회전 기능을 수행하는 함수
Avl* rebalanceRL(Avl* node); //RL회전 기능을 수행하는 함수
Avl* rebalanceLR(Avl* node); //LR회전 기능을 수행하는 함수
Avl* recycletree(Avl* recycleavl); //트리가 재균형을 해야하는지 판단하는 함수

void main(void) {
	int i;
	char* data; //입력시 사용자 입력을 받을 변수

	for(i=1; i<=30; i++) { //30개의 입력을 하기위한 반복문
		printf("새로운 노드 입력 : ");
		data=(char*)malloc(sizeof(char)*5); //입력 문자열을 저장하는 변수의 메모리 할당
		scanf("%s", data);
		avl=insertTree(avl, data); //새로운 노드를 삽입하고 avl여부를 판단하는 함수를 부른다.
		if(recnt==0) //변수값이 0일시에는 재균형이 일어나지 않은 조건
			printf("재균형 No\n");
		else { //0이 아닌 값으로 변경되고 재균형이 일어난 조건
			printf("재균형 Yes ---");
			if(recycletype==1) //변수의 값이 1,2,3,4에 따라 회전 유형 출력
				printf("재균형 타입 : LL\n");
			else if(recycletype==2)
				printf("재균형 타입 : LR\n");
			else if(recycletype==3)
				printf("재균형 타입 : RR\n");
			else
				printf("재균형 타입 : RL\n");
		}
		inorderprint(avl);
		printf("\n");
		recnt=0;
	}
}

void inorderprint(Avl* avl) { //중위 순회를 구현한 함수
	if(avl==NULL)
		return;
	inorderprint(avl->leftchild);
	printf("%s ", avl->value);
	inorderprint(avl->rightchild);
}

Avl* allocationTree(char data[]) { //새 노드를 위해 메모리 할당을 하는 함수
	Avl* temp=(Avl*)malloc(sizeof(Avl));
	temp->leftchild=NULL;
	temp->rightchild=NULL;
	temp->value=data;

	return temp;
}

Avl* insertTree(Avl* avl, char data[]) { //노드를 삽입하는 함수
	if(avl==NULL) //노드가 공백일시에 메모리할당을 해주고 삽입한다.
		avl=allocationTree(data);
	else if(strcmp(avl->value,data)>0) { //문자열이기 때문에 strcmp를 사용하여 크기비교
		avl->leftchild=insertTree(avl->leftchild, data); //문자열 값이 작은 경우 왼쪽 차일드로 재귀를 통해 계속 이동한다.
		avl=recycletree(avl); //재균형이 필요한지 판단하는 함수 호출
	}
	else { //문자열 값이 큰 경우의 조건
		avl->rightchild=insertTree(avl->rightchild, data);
		avl=recycletree(avl);
	}
	return avl;
}

int accountDepth(Avl* avl) { //노드의 깊이를 정수형으로 반환하는 함수
	if(avl==NULL)
		return 0;
	else {
		int templeft,tempright;
		templeft=accountDepth(avl->leftchild)+1; //왼쪽 오른쪽 차일드로 재귀로 불려지면서 깊이가 1씩 더해진다.
		tempright=accountDepth(avl->rightchild)+1;
		if(templeft<tempright) //값이 큰 변수가 최대 깊이로 반환된다.
			return tempright;
		else
			return templeft;
	}
}

Avl* recycletree(Avl* recycleavl) { //재균형이 필요한지 판단하는 함수
	int avldepth=accountDepth(recycleavl->leftchild)-accountDepth(recycleavl->rightchild); //정수형으로 왼쪽과 오른쪽 차일드 깊이를 구해서 차를 구한다.
    if(avldepth>1) { //왼쪽 차일드의 균형이 깨진 경우이다.
		recnt=1; //균형이 깨졌으므로 재균형을 하기때문에 재균형 판단 변수값을 변경한다.
        if((accountDepth((recycleavl->leftchild)->leftchild)-accountDepth((recycleavl->leftchild)->rightchild))>0) {
			//왼쪽 차일드의 서브트리 깊이가 왼쪽, 오른쪽이 더 깊은지 판단하는 조건
			recycleavl=rebalanceLL(recycleavl);  //왼쪽이 더 깊으면 LL회전 경우이다.
			recycletype=1;
		}
        else  {
            recycleavl=rebalanceLR(recycleavl);  //오른쪽이 더 깊으므로 LR회전 경우이다.
			recycletype=2;
		}
    } 
    else if(avldepth<-1) { //오른쪽 차일드의 균형이 깨진 경우이다.
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

Avl* rebalanceLL(Avl* node) { //LL회전을 수행하는 함수
    Avl* subnode=node->leftchild; //서브 노드를 생성해서 회전을 시켜준다.
    node->leftchild=subnode->rightchild; 
    subnode->rightchild=node; 
    return subnode; 
} 

Avl* rebalanceRR(Avl* node) { //RR회전을 수행하는 함수
    Avl* subnode=node->rightchild; 
    node->rightchild=subnode->leftchild; 
    subnode->leftchild=node; 
    return subnode; 
} 

Avl* rebalanceRL(Avl* node) { //RL회전을 수행하는 함수
    Avl* subnode=node->rightchild; //RL의 경우 부분적으로 먼저 LL회전을 해주고 전체적으로 RR회전을 다시해서 반환한다.
    node->rightchild=rebalanceLL(subnode); 
    return rebalanceRR(node); 
} 

Avl* rebalanceLR(Avl* node) { //LR회전을 수행하는 함수
    Avl* subnode=node->leftchild; 
    node->leftchild=rebalanceRR(subnode); 
    return rebalanceLL(node); 
}