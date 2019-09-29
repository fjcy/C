#include <stdio.h>
#include <string.h>

typedef struct{
    char id[30];
    char name[50];
    int college[6]; //collect[0]=1 表示为“工商”，其余类推（“工商”，“数学”、“金融”、“信息”、“人文”、“经济”）
    double competition[5];//competition[0] 表示100米赛跑，其余类推（100m，400m，跳远、接力、铅球）
}Student;

typedef struct{
    Student student[20];
    int rank[20][5];
    int number; //该学院有多少人
    int scoreComprehension;
    int collegeRank;
}College;

void menu();
void inputInfo();
void readFile(char path[]);
void writeFile(char path[]);
void printAllStudentInfo();
void queryScoreByCompetition();
void queryScoreByCollege();
int getRank(Student studentTemp, int competitionItem);
void sortByCollege();
void sortByComprehension();

Student student[100];
int number=0; //选手总人数
College college[6]; //collect[0] 表示为“工商”，其余类推（“工商”，“数学”、“金融”、“信息”、“人文”、“经济”）

int main(){
    int choice; //选择菜单项
    char path[] = "sportsScore";
    int selection; //选择查询的方式
    readFile(path);

    for(int j=0;j<6;j++){
        college[j].number = 0;
        college[j].scoreComprehension = 0;
        for(int i=0;i<20;i++)
            for(int k=0;k<5;k++)
                college[j].rank[i][k] = 0;
    }

    //将每个选手分到对应的学院
    for(int i=0;i<number;i++){
        for(int j=0;j<6;j++){
            if(student[i].college[j] == 1){
                college[j].student[college[j].number] = student[i];
                college[j].number++;
                break;
            }
        }
    }

    sortByCollege();

    do{
        menu();
        scanf("%d",&choice);
        switch(choice){
            case 1:
                inputInfo();
                sortByCollege();
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
                computeConprehension();
                for(int i=0;i<6;i++){
                    printf("学院：");
                    switch(i){
                        case 0:
                            printf("工商\t");
                            break;
                        case 1:
                            printf("数学\t");
                            break;
                        case 2:
                            printf("金融\t");
                            break;
                        case 3:
                            printf("信息\t");
                            break;
                        case 4:
                            printf("人文\t");
                            break;
                        case 5:
                            printf("经济\t");
                            break;
                    }
                    printf("分数：%d\t排名：%d\n",college[i].scoreComprehension, college[i].collegeRank);
                }
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
    printf("--  4 - 查看所有学生信息                         --\n");
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

        //将新加的学生加入到对应的学院结构体数组中
        college[temp-1].student[college[temp-1].number] = student[number];
        college[temp-1].number++;

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

//打印出学院每个选手的排名
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

    printf("该学院所有参赛的人员信息：\n");
    for(int i=0;i<college[choice-1].number;i++){
        printf("姓名：%s\t",college[choice-1].student[i].name);
        for(int j=0;j<5;j++){
            if(college[choice-1].student[i].competition[j] != 0){
                switch(j){
                    case 0:
                        printf("100米成绩：%.2lf\t",college[choice-1].student[i].competition[0]);
                        break;
                    case 1:
                        printf("400米成绩：%.2lf\t",college[choice-1].student[i].competition[1]);
                        break;
                    case 2:
                        printf("跳远成绩：%.2lf\t",college[choice-1].student[i].competition[2]);
                        break;
                    case 3:
                        printf("接力成绩：%.2lf\t",college[choice-1].student[i].competition[3]);
                        break;
                    case 4:
                        printf("铅球成绩：%.2lf\t",college[choice-1].student[i].competition[4]);
                        break;
                }
                printf("排名：%d\t",college[choice-1].rank[i][j]);
            }
        }
        printf("\n");
    }
}

//把学院的每个选手所参加比赛的排名计算出来
void sortByCollege(){
    for(int i=0;i<6;i++){
        for(int j=0;j<college[i].number;j++){
            for(int k=0;k<5;k++){
                if(college[i].student[j].competition[k] != 0){
                    college[i].rank[j][k] = getRank(college[i].student[j],k);
                }
            }
        }
    }
}

//给出每个选手所参加比赛项目的排名
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

//综合成绩计算
void computeConprehension(){
    int scoreComprehension;
    for(int i=0;i<6;i++){
        scoreComprehension = 0;
        for(int j=0;j<college[i].number;j++){
            for(int k=0;k<5;k++){
                if(college[i].rank[j][k] <= 5){
                    switch(college[i].rank[j][k]){ //第1名得分 7，第2名得分 5，第3名得分3，第4名得分2，第5名得分 1
                        case 1:
                            scoreComprehension += 7;
                            break;
                        case 2:
                            scoreComprehension += 5;
                            break;
                        case 3:
                            scoreComprehension += 3;
                            break;
                        case 4:
                            scoreComprehension += 2;
                            break;
                        case 5:
                            scoreComprehension += 1;
                            break;
                        default:
                            break;
                    }
                }
            }
        }
        college[i].scoreComprehension = scoreComprehension;
    }

    sortByComprehension();
}

void sortByComprehension(){
    int temp;
    for(int i=0;i<6;i++){
        temp = 1;
        for(int j=0;j<6;j++){
            if(college[i].scoreComprehension < college[j].scoreComprehension){
                temp++;
            }
        }
        college[i].collegeRank = temp;
    }
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
