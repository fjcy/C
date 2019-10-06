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
                printf("请重新输入\n");
                break;
        }
    }while(choice != 5);

    return 0;
}

//菜单
void menu(){
    printf("-------------------------------------------------\n");
    printf("--  1 - 输入选手信息                           --\n");
    printf("--  2 - 计算得分并排名                         --\n");
    printf("--  3 - 查询                                   --\n");
    printf("--  4 - 打印所有选手信息                       --\n");
    printf("--  5 - 退出                                   --\n");
    printf("-------------------------------------------------\n");
}

//打印所有选手信息
void printAllSingerInfo(){
    if(singerLength == 0){
        printf("请先录入选手信息！\n");
    }else{
        for(int i=0;i<singerLength;i++){
            printf("编号 %d\t", singer[i].number);
            printf("姓名： %s\n", singer[i].name);
//            如果没有进行排名，则输出裁判评分，否则输出排名与最终得分
            if(isSorted) {
                printf("最终得分：%.2lf\n", singer[i].finalScore);
                printf("排名：%d\n", i+1);
            }else{
                printf("裁判评分：");
                for(int j=0;j<10;j++){
                    printf("%lf  ",singer[i].score[j]);
                }
                printf("\n");
            }
            printf("\n");
        }
    }
}

//输入选手信息
void inputInfo(){
    printf("请输入选手人数：");
    scanf("%d",&singerLength);
    while(singerLength > 10){
        printf("选手数大于10，请重新输入!\n");
        printf("请输入选手人数：");
        scanf("%d",&singerLength);
    }
    printf("请输入各位选手的信息！\n");
    for(int i=0;i<singerLength;i++){
        printf("第%d位选手\n", i+1);
        printf("编号： ");
        scanf("%d", &singer[i].number);

        int nameLength=0;
        do{
            if(nameLength != 0){
                printf("字符数大于20,请重新输入！\n");
            }
            singer[i].name[0] = '\0';
            printf("姓名： ");
            scanf("%s", singer[i].name);
            nameLength = strlen(singer[i].name);
        }while(nameLength > 20);

        printf("请分别输入十位裁判打出的分数（以空格隔开）： ");
        for(int j=0;j<10;j++){
            scanf("%lf", &singer[i].score[j]);
        }
    }
    printf("\n输入完成");
}

void search(){
    if(singerLength == 0){
        printf("请先录入选手信息！\n");
    }else{
        if(isSorted == 0){
            printf("请先进行排名！\n");
        }else{
            int choice;
            printf("按编号查找请输入0，按姓名查找请输入1\n");
            scanf("%d", &choice);
            if (choice == 0)
                searchByNumber(singer);
            if (choice == 1)
                searchByName(singer);
        }
    }
}

//按名字查找
void searchByName(){
    char name[20];
    printf("请输入待查询的姓名:");
    scanf("%s", name);
    for (int i = 0; i < singerLength; i ++) {
        if (strcmp(singer[i].name, name) == 0) {
            printf("编号: %d\n", singer[i].number);
            printf("姓名: %s\n", name);
            printf("得分: %.2lf\n", singer[i].finalScore);
            printf("排名: %d\n", i+1);
            return;
        }
    }
}

//按编号查找
void searchByNumber(){
    int number;
    printf("请输入待查询的编号:");
    scanf("%d", &number);
    for (int i = 0; i < singerLength; i ++) {
        if (singer[i].number == number) {
            printf("编号: %d\n", singer[i].number);
            printf("姓名: %s\n", singer[i].name);
            printf("得分: %.2lf\n", singer[i].finalScore);
            printf("排名: %d\n", i+1);
            return;
        }
    }
}

//计算最终得分和排名
void getFinalScore(){
    if(singerLength == 0){
        printf("请先录入选手信息！\n");
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

//对成绩进行排名
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

//去除极大值和极小值
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
