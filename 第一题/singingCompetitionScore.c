#include <stdio.h>
#include <string.h>

typedef struct{
    int number;
    char name[20];
    double score[10];
    double finalScore;
}Singer;

void menu();
void inputInfo();
void getFinalScore();
void removeExtreme(double score[]);
void bubble_sort();
void search();
void searchByName();
void searchByNumber();

int singerLength;
Singer singer[10];
int isSorted = 0;

int main(){
    singerLength = 0;
    int choice;
    do{
        menu();
        scanf("%d",&choice);
        switch(choice){
            case 1:
                inputInfo();
                break;
            case 2:
                getFinalScore();
                break;
            case 3:
                search();
                break;
            case 4:
                printAllSingerInfo();
            case 5:
                break;
            default:
                printf("����������\n");
                break;
        }
    }while(choice != 5);

    return 0;
}

//�˵�
void menu(){
    printf("-------------------------------------------------\n");
    printf("--  1 - ����ѡ����Ϣ                           --\n");
    printf("--  2 - ����÷ֲ�����                         --\n");
    printf("--  3 - ��ѯ                                   --\n");
    printf("--  4 - ��ӡ����ѡ����Ϣ                       --\n");
    printf("--  5 - �˳�                                   --\n");
    printf("-------------------------------------------------\n");
}

//��ӡ����ѡ����Ϣ
void printAllSingerInfo(){
    if(singerLength == 0){
        printf("����¼��ѡ����Ϣ��\n");
    }else{
        for(int i=0;i<singerLength;i++){
            printf("��� %d\t", singer[i].number);
            printf("������ %s\n", singer[i].name);
//            ���û�н���������������������֣�����������������յ÷�
            if(isSorted) {
                printf("���յ÷֣�%.2lf\n", singer[i].finalScore);
                printf("������%d\n", i+1);
            }else{
                printf("�������֣�");
                for(int j=0;j<10;j++){
                    printf("%lf  ",singer[i].score[j]);
                }
                printf("\n");
            }
            printf("\n");
        }
    }
}

//����ѡ����Ϣ
void inputInfo(){
    printf("������ѡ��������");
    scanf("%d",&singerLength);
    while(singerLength > 10){
        printf("ѡ��������10������������!\n");
        printf("������ѡ��������");
        scanf("%d",&singerLength);
    }
    printf("�������λѡ�ֵ���Ϣ��\n");
    for(int i=0;i<singerLength;i++){
        printf("��%dλѡ��\n", i+1);
        printf("��ţ� ");
        scanf("%d", &singer[i].number);

        int nameLength=0;
        do{
            if(nameLength != 0){
                printf("�ַ�������20,���������룡\n");
            }
            singer[i].name[0] = '\0';
            printf("������ ");
            scanf("%s", singer[i].name);
            nameLength = strlen(singer[i].name);
        }while(nameLength > 20);

        printf("��ֱ�����ʮλ���д���ķ������Կո�������� ");
        for(int j=0;j<10;j++){
            scanf("%lf", &singer[i].score[j]);
        }
    }
    printf("\n�������");
}

void search(){
    if(singerLength == 0){
        printf("����¼��ѡ����Ϣ��\n");
    }else{
        if(isSorted == 0){
            printf("���Ƚ���������\n");
        }else{
            int choice;
            printf("����Ų���������0������������������1\n");
            scanf("%d", &choice);
            if (choice == 0)
                searchByNumber(singer);
            if (choice == 1)
                searchByName(singer);
        }
    }
}

//�����ֲ���
void searchByName(){
    char name[20];
    printf("���������ѯ������:");
    scanf("%s", name);
    for (int i = 0; i < singerLength; i ++) {
        if (strcmp(singer[i].name, name) == 0) {
            printf("���: %d\n", singer[i].number);
            printf("����: %s\n", name);
            printf("�÷�: %.2lf\n", singer[i].finalScore);
            printf("����: %d\n", i+1);
            return;
        }
    }
}

//����Ų���
void searchByNumber(){
    int number;
    printf("���������ѯ�ı��:");
    scanf("%d", &number);
    for (int i = 0; i < singerLength; i ++) {
        if (singer[i].number == number) {
            printf("���: %d\n", singer[i].number);
            printf("����: %s\n", singer[i].name);
            printf("�÷�: %.2lf\n", singer[i].finalScore);
            printf("����: %d\n", i+1);
            return;
        }
    }
}

//�������յ÷ֺ�����
void getFinalScore(){
    if(singerLength == 0){
        printf("����¼��ѡ����Ϣ��\n");
    }else{
        double sum;
        for(int i=0;i<singerLength;i++){
            removeExtreme(singer[i].score);
            sum = 0;
            for(int j=0;j<10;j++){
                sum += singer[i].score[j];
            }
            singer[i].finalScore = sum / 8;
        }

        bubble_sort();
        isSorted = 1;
    }
}

//�Գɼ���������
void bubble_sort(){
    Singer temp;
    for(int i=0;i<singerLength-1;i++){
        for(int j=0;j<singerLength-i-1;j++){
            if(singer[j].finalScore<singer[j+1].finalScore){
                temp = singer[j];
                singer[j] = singer[j+1];
                singer[j+1] = temp;
            }
        }
    }
}

//ȥ������ֵ�ͼ�Сֵ
void removeExtreme(double score[]){
    int max=score[0],min=score[0],maxIndex=0,minIndex=0;
    for(int i=0;i<10;i++){
        if(score[i] > max){
            max = score[i];
            maxIndex = i;
        }
        if(score[i] < min){
            min = score[i];
            minIndex = i;
        }
    }
    score[maxIndex] = 0;
    score[minIndex] = 0;
}
