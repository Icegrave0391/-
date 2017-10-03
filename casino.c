#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mem.h>

enum operation{ YES = 0, NO = 1, QUIT = 2};
enum suit{ CLUBS = 0, DIAMONDS = 1, HEARTS = 2, SPADES = 3};
enum number { A = 1, J =11, Q = 12, K = 13};
char color[4][10] = {"÷��","��Ƭ","����","����"};

struct Card{
    enum number num;
    enum suit type;
}card[52];

//��δʵ�ֵ�����
//������չʾ����ʱ��������
int cmp(const struct Card *a1, const struct Card *a2){
    if((*a1).num>(*a2).num) return 1;
    else if((*a1).num<(*a2).num) return -1;
    else
        return (*a1).type<(*a2).type?1:-1;
}

//ϴ��
void shuffle(struct Card a[], int n){
    struct Card tmp;
    for(int i=0; i<n; i++){
        int index = rand()%(n-i)+i;
        if(index != i){
            tmp = a[i];
            a[i] = a[index];
            a[index] = tmp;
        }
    }
}

//��ʼ����������
void initCard(struct Card a[]){
    for(int i = 0; i<4; i++){
        for(int j = 1; j <= 13; j++){
            a[i*13+j-1].num = j;
            a[i*13+j-1].type = i;
        }
    }
}

enum operation getChoice() {
    printf("(y/n/q?)\n");
    char str[100];
    scanf("%s",str);
    if(str[1]!=0)
        return QUIT;
    switch(str[0]){
        case 'y':
            printf("OK\n");
            return YES;
        case 'n':
            printf("Not bad\n");
            return NO;
        case 'q':
            printf("Bye\n");
            return QUIT;
        default:
            return QUIT;
    }
}

void displayHand(struct Card a[], int size,int score){
    for(int i =0 ;i < size; i++){
        printf("��%s%d�� ",color[a[i].type],a[i].num);
    }
    if(size>0) printf("\n����%d��\n\n",score);
}

int main() {
    srand((unsigned )time(NULL));
    printf("��������˹�ĳ���������\n�Ըкɹ����߷���\n###21����Ϸ###\n");
    initCard(card);
    while(1){
        shuffle(card,52);
        printf("\n###��Ϸ��ʼ###\n");
        /*
        for(int i =0 ;i < 52; i++){
            printf("��%s%d�� ",color[card[i].type],card[i].num);
        }
         */

        putchar('\n');
        int ran = rand();
        if(ran*2<RAND_MAX) printf("������Ϸ�У���� 1 Ϊׯ��\n");
        else printf("������Ϸ�У���� 2 Ϊׯ��\n");
        int turn = 1;
        int score[2], handSize[2];
        struct Card hand[2][6];
        memset(score,0,2*sizeof(int));
        memset(handSize,0,2*sizeof(int));
        memset(hand,0,12*sizeof(struct Card));
        int index = 0;
        int flag ;
        while(1) {
            flag = 0;
            printf("@TURN %d:\n", turn++);
            for (int i = 0; i < 2; i++) {
                printf("$��� %d �Ļغ�\n",i+1);
                displayHand(hand[i], handSize[i], score[i]);
                printf("\n�����Ƿ��һ���ƣ�");
                enum operation o = getChoice();
                if (o == YES) {
                    hand[i][handSize[i]++]=card[index];
                    score[i]+=card[index++].num;
                    displayHand(hand[i], handSize[i], score[i]);
                    if(score[i]>21){
                        flag =2 ;
                        printf("��� %d ���֣����¿�ʼ��Ϸ\n",i+1);
                        break;
                    }
                }else if (o == NO) {
                    continue;
                }else {
                    flag = 1;
                    break;
                }
                if(flag>0) break;
            }
            if(flag>0) break;
        }
        if(flag==1) break;
        else if(flag==2) continue;
    }
    return 0;
}