#include <stdio.h>

typedef struct{
    char id[30];
    char name[50];
    int college[6]; //collect[0]=1 表示为“工商”，其余类推（“工商”，“数学”、“金融”、“信息”、“人文”、“经济”）
    double meter100;
    double meter400;
    double jump;
    double relay;
    double shot;
}Student;

void menu();
void inputInfo();
void readFile(char path[]);
void writeFile(char path[]);
void printAllStudentInfo();
void queryScoreByCompetition();
void queryScoreByCollege();

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
                printf("请输入：");
                do{
                    scanf("%d",&selection);

                }while();
                queryScore();
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
        scanf("%lf",&student[number].meter100);
        printf("400米成绩：");
        scanf("%lf",&student[number].meter400);
        printf("跳远成绩：");
        scanf("%lf",&student[number].jump);
        printf("接力成绩：");
        scanf("%lf",&student[number].relay);
        printf("铅球成绩：");
        scanf("%lf",&student[number].shot);
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

}

//按学院查询成绩
void queryScoreByCollege(){

}

//打印所有学生信息
void printAllStudentInfo(){
    for(int i=0;i<number;i++){
        printf("学生ID：%s\n",student[i].id);
        printf("姓名：%s\n",student[i].name);
        printf("学院：");
        convert(student[i].college,6);
        printf("\n");
        printf("100米成绩：%.2lf\n",student[i].meter100);
        printf("400米成绩：%.2lf\n",student[i].meter400);
        printf("跳远成绩：%.2lf\n",student[i].jump);
        printf("接力成绩：%.2lf\n",student[i].relay);
        printf("铅球成绩：%.2lf\n",student[i].shot);
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
