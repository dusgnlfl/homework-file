#include <stdio.h>
#include <stdlib.h>

typedef struct trans Trans;
struct trans { //Ʈ����� ������ ���ϴ� ����ü
	int record[30]; //���ڵ�
	int time[30]; //�߻��ð�
	char type[30]; //���ڵ� ����
};

void printTrans(Trans* transaction); //Ʈ����� ���� ��� �Լ�
void inputOldMaster(int* oldmaster); //�� ������ ���� �ʱ� �ۼ� �Լ�
void createTrans(Trans* transaction); //Ʈ����� ���� �ʱ� �ۼ� �Լ�
void sortTrans(Trans* transaction); //Ʈ����� ���� ���� �Լ�
void createNewMaster(int* oldmst, int* newmst, Trans* transaction); //�������� ȭ�� �ۼ� �Լ�

void main(void) {
	int* oldmaster=0;
	int* newmaster=0;
	Trans* trans=0;

	oldmaster=(int *)malloc(sizeof(int)*10); //�� ũ�⿡ �ش��ϴ� ��ŭ �޸� �����Ҵ�
	newmaster=(int *)malloc(sizeof(int)*20);
	trans=(Trans *)malloc(sizeof(Trans));

	inputOldMaster(oldmaster);
	createTrans(trans);
	printf("Ʈ����� ������ �ʱ����\n");
	printTrans(trans);
	printf("\n");
	sortTrans(trans);
	printf("Ʈ����� ������ ����\n");
	printTrans(trans);
	printf("\n");
	printf("�� ������ ���� �ۼ��� �����޼���\n");
	createNewMaster(oldmaster, newmaster, trans);

	free(trans); //�޸� ��ȯ
	free(oldmaster);
}

void printTrans(Trans* transaction) {
	int i;
	for(i=0; i<30; i++) {
		printf("%d/t%d(%c) ",transaction->record[i],transaction->time[i],transaction->type[i]);
		if((i+1)%6==0)
			printf("\n");
	}
}

void inputOldMaster(int* oldmst) {
	int i;
	for(i=0; i<10; i++)
		oldmst[i]=2*(i+1);
}

void createTrans(Trans* transaction) {
	int i;
	for(i=0; i<30; i++) {
		transaction->record[i]=rand()%20+1;
		transaction->time[i]=i+1;
		if(i%3==0)
			transaction->type[i]='i';
		else if(i%3==1)
			transaction->type[i]='m';
		else
			transaction->type[i]='d';
	}
}

void sortTrans(Trans* transaction) {
	int i,j;
	int tmprecord, tmptime;
	char tmptype;
	for(i=0; i<29; i++) {
		for(j=i+1; j<30; j++) {
			if(transaction->record[i]>transaction->record[j]) {
				tmprecord=transaction->record[i];
				tmptime=transaction->time[i];
				tmptype=transaction->type[i];
				transaction->record[i]=transaction->record[j];
				transaction->time[i]=transaction->time[j];
				transaction->type[i]=transaction->type[j];
				transaction->record[j]=tmprecord;
				transaction->time[j]=tmptime;
				transaction->type[j]=tmptype;
			}
			else if(transaction->record[i]==transaction->record[j]) {
				if(transaction->time[i]>transaction->time[j]) {
					tmptime=transaction->time[i];
					tmptype=transaction->type[i];
					transaction->time[i]=transaction->time[j];
					transaction->type[i]=transaction->type[j];
					transaction->time[j]=tmptime;
					transaction->type[j]=tmptype;
				}
			}
		}
	}
}

void createNewMaster(int* oldmst, int* newmst, Trans* transaction) {
	int oldcnt=0, newcnt=0, transcnt=0;
	int i;
	while(1) {
		if(transcnt==30) {
			if(oldcnt==10)
				break;
			else {
				while(oldcnt<10) {
					newmst[newcnt]=oldmst[oldcnt];
					newcnt++;
					oldcnt++;
				}
				break;
			}
		}
		else {
			if(oldcnt==10) {
				while(transcnt==30) {
					if(transaction->record[transcnt]==newmst[newcnt-1]) {
						if(transaction->type[transcnt]=='d') {
							newcnt--;
							transcnt++;
						}
						else if(transaction->type[transcnt]=='m') {
							printf("%d���ڵ带 �����߽��ϴ�.\n", transaction->record[transcnt]);
							transcnt++;
						}
						else {
							printf("%d���ڵ尡 �̹� �����մϴ�.\n", transaction->record[transcnt]);
							transcnt++;
						}
					}
					else {
						if(transaction->type[transcnt]=='i') {
							newmst[newcnt]=transaction->record[transcnt];
							transcnt++;
							newcnt++;
						}
						else {
							printf("%d���ڵ尡 �������� �ʽ��ϴ�.\n", transaction->record[transcnt]);
							transcnt++;
						}
					}
				}
				break;
			}
			else {
				if(transaction->record[transcnt]>oldmst[oldcnt]) {
					newmst[newcnt]=oldmst[oldcnt];
					oldcnt++;
					newcnt++;
				}
				else if(transaction->record[transcnt]==oldmst[oldcnt]) {
					if(transaction->type[transcnt]=='d') {
						oldcnt++;
						transcnt++;
					}
					else if(transaction->type[transcnt]=='m') {
						newmst[newcnt]=oldmst[oldcnt];
						printf("%d���ڵ带 �����Ŀ� �����߽��ϴ�.\n", oldmst[oldcnt]);
						transcnt++;
						oldcnt++;
						newcnt++;
					}
					else {
						printf("%d���ڵ尡 �̹� �����մϴ�.\n", transaction->record[transcnt]);
						transcnt++;
					}
				}
				else {
					if(newcnt!=0 && (transaction->record[transcnt]==newmst[newcnt-1])) {
						if(transaction->type[transcnt]=='d') {
							newcnt--;
							transcnt++;
						}
						else if(transaction->type[transcnt]=='m') {
							printf("%d���ڵ带 �����߽��ϴ�.\n", transaction->record[transcnt]);
							transcnt++;
						}
						else {
							printf("%d���ڵ尡 �̹� �����մϴ�.\n", transaction->record[transcnt]);
							transcnt++;
						}
					}
					else {
						if(transaction->type[transcnt]=='i') {
							newmst[newcnt]=transaction->record[transcnt];
							transcnt++;
							newcnt++;
						}
						else {
							printf("%d���ڵ尡 �������� �ʽ��ϴ�.\n", transaction->record[transcnt]);
							transcnt++;
						}
					}
				}
			}
		}
	}
	printf("\n");
	printf("���� �� ������ ����\n");
	for(i=0; i<newcnt; i++)
		printf("%d ", newmst[i]);
	printf("\n");
}