#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <time.h>

void flashCard();
void flashAuto(int);
void flashMan(int);
void fill();
void priHeader(char[]);
void game();
void priHangMan(int);
void suffle();

typedef struct {
    char eng[30];
    char kor[30];
} word;

word w[7][10] = {
    {{"provide", "공급하다"}, {"develop", "개발하다"}, {"service", "서비스"}, {"inform", "알리다"}, {"act", "연기"}, {"address", "주소"}, {"afraid", "두려움"}, {"again", "다시"}, {"age", "나이"}, {"air", "공기"}},
    {{"airport", "공항"}, {"album", "앨범"}, {"all", "모두"}, {"always", "항상"}, {"and", "그리고"}, {"answer", "답"}, {"any", "아무"}, {"apple", "사과"}, {"arm", "팔"}, {"ask", "묻다"}},
    {{"aunt", "고모"}, {"autumn", "가을"}, {"baby", "아기"}, {"back", "뒤"}, {"bad", "나쁜"}, {"bag", "가방"}, {"ball", "공"}, {"balloon", "풍선"}, {"band", "밴드"}, {"basket", "바구니"}},
    {{"bath", "목욕"}, {"beach", "해변"}, {"bear", "배"}, {"beautiful", "아름다운"}, {"because", "왜나하면"}, {"bed", "침대"}, {"bell", "벨"}, {"below", "아래"}, {"bench", "벤치"}, {"beside", "옆에"}},
    {{"between", "사이에"}, {"big", "큰"}, {"bird", "새"}, {"black", "검정"}, {"blow", "불다"}, {"blue", "파랑"}, {"board", "판"}, {"boat", "보트"}, {"body", "몸"}, {"book", "책"}},
    {{"bottle", "병"}, {"bowl", "그릇"}, {"box", "상자"}, {"boy", "소년"}, {"bread", "빵"}, {"break", "멈추다"}, {"breakfast", "아침"}, {"bridege", "다리"}, {"bring", "가져오다"}, {"brother", "형제"}},
    {{"brown", "갈색"}, {"burn", "불타다"}, {"bus", "버스"}, {"but", "하지만"}, {"butter", "버터"}, {"button", "버튼"}, {"cake", "케이크"}, {"call", "부르다"}, {"candle", "양초"}, {"capital", "수도"}}};
char arr[50];
int seq[10];
int num = 0;

int main()
{
    while(1)
    {
        printf(">> 영어 단어 암기 프로그램 <<\n");
        printf("1. 플래쉬 카드    2. 게임    3. 프로그램 종료\n");

        int cho;
        printf("번호를 선택하세요: ");
        scanf("%d", &cho);
        num++;
        switch (cho)
        {
        case 1:
            flashCard();
            break;
        case 2:
            game();
            break;
        case 3:
            system("clear");
            return 0;
            break;
        }
    }
    
    return 0;
}

void flashCard()
{
    int day, cho;
    printf("학습 일차: ");
    scanf("%d", &day);

    printf("출력방식(수동모드: 1, 자동모드: 2): ");
    scanf("%d", &cho);
    switch (cho)
    {
    case 1:
        flashMan(day);
        break;
    case 2:
        flashAuto(day);
        break;
    }
}

void suffle()
{
    srand(time(NULL));
    for(int i=0; i<10; i++) {
        int idx = rand() % 10;
        seq[i] = idx;
        for(int j=0; j<i; j++) {
            if(seq[j] == seq[i]) i--;
        }
    }   
}

void flashAuto(int day)
{
    suffle();
    system("clear");
    day--;
    for(int i=0;i<10;i++) {
        printf(">> 영어 단어 암기 프로그램 : 플래쉬카드 <<\n\n\n\n");
        printf("%s", w[day][seq[i]].eng);
        putchar('\n');
        sleep(1);
        system("clear");

        printf(">> 영어 단어 암기 프로그램 : 플래쉬카드 <<\n\n\n\n");
        printf("%s", w[day][seq[i]].kor);
        putchar('\n');
        sleep(1);
        system("clear");
    }
}

void flashMan(int day)
{
    suffle();
    getchar();
    system("clear");
    day--;
    for(int i=0;i<10;i++) {
        printf(">> 영어 단어 암기 프로그램 : 플래쉬카드 <<\n\n\n\n");
        printf("%s", w[day][seq[i]].eng);
        //putchar('\n');
        getchar();
        system("clear");

        printf(">> 영어 단어 암기 프로그램 : 플래쉬카드 <<\n\n\n\n");
        printf("%s", w[day][seq[i]].kor);
        //putchar('\n');
        getchar();
        system("clear");
    }
}

void game()
{
    int day;
    printf("학습 일차: ");
    scanf("%d", &day);

    system("clear");
    putchar('\n');
    fill();
    day--;

    srand(time(NULL));
    int idx = rand() % 10;
    char ans[50];
    char hint[50];
    strcpy(ans, w[day][idx].eng);
    strcpy(hint, w[day][idx].kor);

    int try = 1;
    int wrong = 0;
    int temp = 0;
    int cnt = 0;
    char input;
    while (1)
    {
        getchar();
        temp=0;
        putchar('\n');
        system("clear");
        priHeader(hint);
        if(wrong >= 1) printf("                   O\n");
        if(wrong >= 2) printf("                 /");
        if(wrong >= 3) printf(" |");
        if(wrong >= 4) printf(" \\");
        if(wrong >= 5) printf("\n                  /\n");

        if(wrong == 0) printf("\n\n\n\n");
        else if(wrong == 1) printf("\n\n\n");
        else if(wrong == 2 || wrong == 3 || wrong == 4) printf("\n\n\n");
        else if(wrong == 5) printf("\n");

        for(int i=0; i<strlen(ans); i++) {
            printf("%c", arr[i]);
        }
        printf("\n%d번째 시도: ", try);
        scanf("%c", &input);
        //getchar();

        for(int i=0; i<strlen(ans); i++) {
            if(ans[i] == input && arr[i] == '_') {
                arr[i] = input;
                cnt++;
                temp=1;
            }
        }
        if(temp == 0) {
            wrong++;
        }

        try++;
        // printf("\ntry: %d, cnt: %d\n", try, cnt);
        // sleep(5);
        if(cnt == strlen(ans)) {
            printf("\n");
            printf("   ##########################\n");
            printf("   ### Congratulations!!! ###\n");
            printf("   ##########################\n");
            sleep(2);
            //getchar(); getchar();
            system("clear");
            break;
        }
        else if(wrong == 6) {
            printf("\n");
            printf("   ##########################\n");
            printf("   ######### Fail!!! ########\n");
            printf("   ##########################\n");
            sleep(2);
            //getchar(); getchar();
            system("clear");
            break;
        }
    }
}

void priHeader(char hint[])
{
    printf(">> 영어 단어 암기 프로그램 : 게임 <<\n");
    printf("(힌트) %s\n\n", hint);
    printf("-------------------+\n");
}

void fill() 
{
    for(int i=0; i<50; i++) {
        arr[i] = '_';
    }
}