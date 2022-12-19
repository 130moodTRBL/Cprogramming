#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

typedef struct node {
    char eng[30];
    char kor[30];
    struct node *next;
}node;
typedef struct node NODE;
typedef NODE* LINK;

void wordGame(LINK head);
void fileToList(LINK head);
void addNode(LINK head, char eng[], char kor[]);
void sortList(LINK head);

int cnt = 0;

int main()
{
    LINK head = malloc(sizeof(NODE));
    fileToList(head);
    sortList(head);
    while(1)
    {
        int cho;
        printf(">> 영어 단어 맞추기 프로그램 <<\n");
        printf("1. 영어 단어 맞추기        2) 프로그램 종료\n\n");
        printf("번호를 선택하세요: ");
        scanf("%d", &cho);
        switch (cho)
        {
        case 1:
            system("clear");
            wordGame(head);
            system("clear");
            break;
        case 2:
            system("clear");
            return 0;
            break;
        }
    }

    return 0;
}

void wordGame(LINK head)
{

    LINK word = head;
    word = word->next;
    char ans[30];
    float score = 0;
    int check = 0;
    printf(">> 영어 단어 맞추기 <<\n");
    while(word != NULL) {
        printf("%s -> ", word->kor);
        scanf("%s", ans);

        if(strcmp(ans, ".quit") == 0) {
            printf("당신의 점수는 %.2f 점 입니다.", (score/cnt)*100.0);
            getchar();
            getchar();
            check = 1;
            break;
        }
        if(strcmp(ans, word->eng) == 0) {
            score++;
            printf("correct!\n");
        }
        else  {
            printf("incorrect!\n");
        }
        word = word->next;
    }
    if(!check) {
        printf("당신의 점수는 %.2f 점 입니다.", (score/cnt)*100.0);
        getchar();
        getchar();
    }
}

void fileToList(LINK head)
{
    char eng[30];
    char kor[30];
    FILE *fp = fopen("dic.txt", "r");
    while(fscanf(fp, "%s %s\n", eng, kor) != EOF)
    {
        addNode(head, eng, kor);
        cnt++;
    }
}

void addNode(LINK head, char eng[], char kor[])
{
    if(head->next == NULL) {
		LINK now = malloc(sizeof(NODE));
		strcpy(now->eng, eng);
		strcpy(now->kor, kor);
        now->next = NULL;
        head->next = now;
	}
	else {
		LINK cur = head;
		while(cur->next != NULL) 
        {
			cur = cur->next;
		}
		LINK now = malloc(sizeof(NODE));
		strcpy(now->eng, eng);
		strcpy(now->kor, kor);
        now->next = NULL;
        cur->next = now;
	}
}

void sortList(LINK head)
{
    LINK cur = head;
    char tempE[30];
    char tempK[30];

    cur = cur->next;
    for(int i=0; i<cnt; i++) {
        for(int j=0; j<cnt-1-i; j++) {
            if(strcmp(cur->eng, cur->next->eng) > 0) {
                strcpy(tempE, cur->eng);
                strcpy(cur->eng, cur->next->eng);
                strcpy(cur->next->eng, tempE);

                strcpy(tempK, cur->kor);
                strcpy(cur->kor, cur->next->kor);
                strcpy(cur->next->kor, tempK);
            }
            cur = cur->next;
        }
        cur = head->next;
        //head = head->next;
    }
}