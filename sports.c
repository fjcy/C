#include <stdio.h>
#include <string.h>

typedef struct{
    char id[30];
    char name[50];
    int college[6]; //collect[0]=1 表示为“工商”，其余类推（“工商”，“数学”、“金融”、“信息”、“人文”、“经济”）
    double competition[5];//competition[0] 表示100米赛跑，其余类推（100m，400m，跳远、接力、铅球）
}Student;

void menu();
void inputInfo();
void readFile(char path[]);
void writeFile(char path[]);
void printAllStudentInfo();
void queryScoreByCompetition();
void queryScoreByCollege();
int getRank(Student studentTemp, int competitionItem);

Student student[100];
int number=0;

int main(){
    int choice; //选择菜单项
    char path[] = "sportsScore";
    int selection; //选择查询的方式
    readFile(path);
    do{
        menu();
        scanf("%d",&choice);
        switch(choice){
            case 1:
                inputInfo();
                break;
            case 2:
                printf("--  1 - 按比赛项目查询     \n");
                printf("--  2 - 按学院查询        \n");
                do{
                    printf("请输入：");
                    scanf("%d",&selection);
                    if(selection == 1){
                        queryScoreByCompetition();
                        break;
                    }else if(selection == 2){
                        queryScoreByCollege();
                        break;
                    }else{
                        printf("请重新输入！\n");
                    }
                }while(1);
                break;
            case 3:
//                printAllBooksInfo();
                break;
            case 4:
                printAllStudentInfo();
                break;
            case 5:
                break;
            default:
                printf("请重新输入\n");
                break;
        }
    }while(choice != 5);

    writeFile(path);

    return 0;
}

//读取文件
void readFile(char path[]){
    FILE *fp;
    if((fp=fopen(path,"rb+")) == NULL)
    {
        printf("读取文件失败!");
        return;
    }

    while(fread(&student[number], sizeof(Student), 1, fp)){ //将结构体从文件中读出
        number++;
    }

    fclose(fp);
}

//写入文件
void writeFile(char path[]){
    FILE *fp;
    if((fp=fopen(path,"wb+")) == NULL)
    {
        printf("写入文件失败!");
        return;
    }

    for (int i=0;i<number;i++){
        fwrite(&student[i],sizeof(student[0]),1,fp); //将结构体写入数组
    }

    fclose(fp);
}

//菜单
void menu(){
    printf("-------------------------------------------------\n");
    printf("--  1 - 录入成绩                                --\n");
    printf("--  2 - 成绩查询                                --\n");
    printf("--  3 - 综合成绩计算                            --\n");
    printf("--  4 - 打印学生信息                            --\n");
    printf("--  5 - 退出                                   --\n");
    printf("-------------------------------------------------\n");
}

//录入成绩
void inputInfo(){
    int temp;
    int isFalse;
    int isContinue;
    printf("请录入学生信息\n");
    do{
        printf("学生ID：");
        scanf("%s",student[number].id);
        printf("姓名：");
        scanf("%s",student[number].name);
        printf("请选择学院：1.工商 2.数学 3.金融 4.信息 5.人文 6.经济\n");
        do{
            scanf("%d", &temp);
            if(temp >= 1 && temp <= 6){
                student[number].college[temp - 1] = 1;
                isFalse = 0;
            }else{
                printf("输入错误，请重新输入！\n");
                isFalse = 1;
            }
        }while(isFalse);
        printf("100米成绩：");
        scanf("%lf",&student[number].competition[0]);
        printf("400米成绩：");
        scanf("%lf",&student[number].competition[1]);
        printf("跳远成绩：");
        scanf("%lf",&student[number].competition[2]);
        printf("接力成绩：");
        scanf("%lf",&student[number].competition[3]);
        printf("铅球成绩：");
        scanf("%lf",&student[number].competition[4]);
        number++;
        printf("是否要继续录入：是(1) 否(2)\t");
        scanf("%d",&isContinue);
        if(isContinue == 1){
            isFalse = 1;
        }else{
            isFalse = 0;
        }
    }while(isFalse);
}

//按比赛查询成绩
void queryScoreByCompetition(){
    Student studentTemp[20];
    int numberParticipants=0;
    int choice;

    printf("请选择比赛项目：\n");
    printf("--  1 - 100米赛跑     \n");
    printf("--  2 - 400米赛跑      \n");
    printf("--  3 - 跳远     \n");
    printf("--  4 - 接力      \n");
    printf("--  5 - 铅球     \n");
    do{
        printf("请输入：");
        scanf("%d",&choice);
        if(choice >= 1 && choice <= 5)
            break;
        else
            printf("请重新输入！\n");
    }while(1);

//    将参加了该比赛的同学挑出来
    for(int i=0;i<number;i++){
        if(student[i].competition[choice-1] != 0){
            studentTemp[numberParticipants] = student[i];
            numberParticipants++;
        }
    }

    Student temp;
    for(int i=0;i<numberParticipants;i++){
        for(int j=0;j<numberParticipants-i-1;j++){
            if(studentTemp[j].competition[choice-1] < studentTemp[j+1].competition[choice-1]){
                temp = studentTemp[j];
                studentTemp[j] = studentTemp[j+1];
                studentTemp[j+1] = temp;
            }
        }
    }

    printf("该比赛情况为：\n");
    for(int i=0;i<numberParticipants;i++){
        printf("姓名：%s\t",studentTemp[i].name);
        printf("学院：");
        convert(studentTemp[i].college, 6);
        printf("\t");
        printf("成绩：%.2lf\t",studentTemp[i].competition[choice-1]);
        printf("排名：%d\n",i+1);
    }
}

//按学院查询成绩
void queryScoreByCollege(){
    int choice;
    Student studentTemp[20];
    int numberColleges = 0;
    printf("请选择学院：1.工商 2.数学 3.金融 4.信息 5.人文 6.经济\n");
    do{
        scanf("%d", &choice);
        if(choice >= 1 && choice <= 6){
            break;
        }else{
            printf("请重新输入！\n");
        }
    }while(1);

//    将该学院的人挑出来
    for(int i=0;i<number;i++){
        if(student[i].college[choice-1] == 1){
            studentTemp[numberColleges] = student[i];
            numberColleges++;
        }
    }

    int rank[5]; //当前比赛选手五项比赛的排名
    printf("该学院所有参赛的人员信息：\n");
    for(int i=0;i<numberColleges;i++){
        printf("姓名：%s\t",studentTemp[i].name);
        for(int j=0;j<5;j++){
            if(studentTemp[i].competition[j] != 0){
                switch(j){
                    case 0:
                        printf("100米成绩：%.2lf\t",studentTemp[i].competition[0]);
                        break;
                    case 1:
                        printf("400米成绩：%.2lf\t",studentTemp[i].competition[1]);
                        break;
                    case 2:
                        printf("跳远成绩：%.2lf\t",studentTemp[i].competition[2]);
                        break;
                    case 3:
                        printf("接力成绩：%.2lf\t",studentTemp[i].competition[3]);
                        break;
                    case 4:
                        printf("铅球成绩：%.2lf\t",studentTemp[i].competition[4]);
                        break;
                }
                printf("排名：%d\t",getRank(studentTemp[i], j));
            }
        }
        printf("\n");
    }
}

//在按学院查询成绩时，给出每个选手的排名
int getRank(Student studentTemp, int competitionItem){
    int rank=1;
    for(int i=0;i<number;i++){ //循环所有比赛选手
        if(strcmp(student[i].id,studentTemp.id) != 0){ //判断是不是同一个人
            if(studentTemp.competition[competitionItem] != 0 && student[i].competition[competitionItem] != 0){ //判断两人是否都参加了该项比赛
                if(studentTemp.competition[competitionItem] < student[i].competition[competitionItem])
                    rank++;
            }
        }
    }
    return rank;
}

//打印所有学生信息
void printAllStudentInfo(){
    for(int i=0;i<number;i++){
        printf("学生ID：%s\n",student[i].id);
        printf("姓名：%s\n",student[i].name);
        printf("学院：");
        convert(student[i].college,6);
        printf("\n");
        printf("100米成绩：%.2lf\n",student[i].competition[0]);
        printf("400米成绩：%.2lf\n",student[i].competition[1]);
        printf("跳远成绩：%.2lf\n",student[i].competition[2]);
        printf("接力成绩：%.2lf\n",student[i].competition[3]);
        printf("铅球成绩：%.2lf\n",student[i].competition[4]);
        printf("-------------------------------------------------\n");
    }
}

//输出该学生的学院
void convert(int college[], int count){
    for(int i=0;i<count;i++){
        if(college[i] == 1){
            switch(i){//“工商”，“数学”、“金融”、“信息”、“人文”、“经济”
                case 0:
                    printf("工商");
                    break;
                case 1:
                    printf("数学");
                    break;
                case 2:
                    printf("金融");
                    break;
                case 3:
                    printf("信息");
                    break;
                case 4:
                    printf("人文");
                    break;
                case 5:
                    printf("经济");
                    break;
                default:
                    break;
            }
            break;
        }
    }
}
