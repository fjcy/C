#include <stdio.h>

typedef struct{
    char name[10];
    int position; //0为教授，1为副教授
    int course; //1为高数，类推：高数，英语，程序设计，马列，体育，线代，数据挖掘
    int preferenceCount; //偏好上课时间有几天
    int preference[5];
    int isArrangement; // 是否已经被排课，0为未排课，1为排了一堂课，2为排了两堂课
}Teacher;

Teacher teacher[8];
int teacherNumber = 7;
int arrangement[5][3]; //5代表周一至周五，3代表上午，下午和晚上。arrangement[x][y]值为-1表示未排课
int totalTrafficExpense = 0;

void courseArrangement();
void display();

void init(){
    strcpy(teacher[0].name , "钱");
    teacher[0].position = 0;
    teacher[0].course = 1;
    teacher[0].preferenceCount = 3;
    teacher[0].preference[0] = 0;
    teacher[0].preference[1] = 2;
    teacher[0].preference[2] = 3;
    teacher[0].isArrangement = 0;

    strcpy(teacher[1].name, "赵");
    teacher[1].position = 0;
    teacher[1].course = 2;
    teacher[1].preferenceCount = 2;
    teacher[1].preference[0] = 1;
    teacher[1].preference[1] = 3;
    teacher[1].isArrangement = 0;

    strcpy(teacher[2].name, "孙");
    teacher[2].position = 1;
    teacher[2].course = 3;
    teacher[2].preferenceCount = 2;
    teacher[2].preference[0] = 2;
    teacher[2].preference[1] = 4;
    teacher[2].isArrangement = 0;

    strcpy(teacher[3].name, "李");
    teacher[3].position = 1;
    teacher[3].course = 4;
    teacher[3].preferenceCount = 2;
    teacher[3].preference[0] = 0;
    teacher[3].preference[1] = 4;
    teacher[3].isArrangement = 0;

    strcpy(teacher[4].name, "周");
    teacher[4].position = 1;
    teacher[4].course = 5;
    teacher[4].preferenceCount = 2;
    teacher[4].preference[0] = 0;
    teacher[4].preference[1] = 3;
    teacher[4].isArrangement = 0;

    strcpy(teacher[5].name, "吴");
    teacher[5].position = 1;
    teacher[5].course = 6;
    teacher[5].preferenceCount = 2;
    teacher[5].preference[0] = 1;
    teacher[5].preference[1] = 4;
    teacher[5].isArrangement = 0;

    strcpy(teacher[6].name, "陈");
    teacher[6].position = 1;
    teacher[6].course = 7;
    teacher[6].preferenceCount = 2;
    teacher[6].preference[0] = 1;
    teacher[6].preference[1] = 3;
    teacher[6].isArrangement = 0;

    for(int i=0;i < 5; i++)
        for(int j=0; j < 3; j++)
            arrangement[i][j] = -1;
}

int main(){
    init();

//    int isOk=0;
//    printf("录入教师信息\n");
//    for(int i=0;i < 8; i++){
//        printf("请输入姓名：");
//        scanf("%s",teacher[i].name);
//        printf("请选择职位：0.教授 1.副教授\n");
//        scanf("%d",&teacher[i].position);
//        printf("请选择所教授课程：1.高数 2.英语 3.程序设计 4.马列 5.体育 6.线代 7.数据挖掘\n");
//        scanf("%d",&teacher[i].course);
//        printf("偏好上课时间有几天？\t");
//        do{
//            scanf("%d",&teacher[i].preferenceCount);
//            if(teacher[i].preferenceCount > 5){
//                printf("不能大于5，请重新输入！\n");
//            }else{
//                break;
//            }
//        }while(1);
//
//        printf("分别是：");
//        for(int j=0; j < teacher[i].preferenceCount; j++){
//            scanf("%d",&teacher[i].preference[j]);
//        }
//
//        teacherNumber++;
//
//        printf("请问是否要继续录入（1为录入，2为结束录入）\n");
//        scanf("%d",&isOk);
//        if(isOk == 2){
//            break;
//        }
//    }

    courseArrangement();

    display();

    return 0;
}

void courseArrangement(){
    //先给教授按照偏好排课
    for(int i=0; i < teacherNumber; i++){
        if(teacher[i].position == 0 && teacher[i].isArrangement == 0){
            //根据老师的偏好进行排课
            for(int j=0; j < teacher[i].preferenceCount; j++){
                if(teacher[i].isArrangement < 2){ //如果给老师的两堂课都排好了，就进行下一个老师
                    for(int k=0; k < 3; k++){ //循环上午、下午，晚上
                        if(arrangement[teacher[i].preference[j]][k] == -1){
                            arrangement[teacher[i].preference[j]][k] = i;
                            teacher[i].isArrangement++;
                            break;
                        }
                    }
                }else{
                    break;
                }
            }
        }
    }

    //给副教授按照偏好排课
    for(int i=0; i < teacherNumber; i++){
        if(teacher[i].position == 1 && teacher[i].isArrangement == 0){
            //根据老师的偏好进行排课
            for(int j=0; j < teacher[i].preferenceCount; j++){
                if(teacher[i].isArrangement < 2){ //如果给老师的两堂课都排好了，就进行下一个老师
                    for(int k=0; k < 3; k++){ //循环上午、下午，晚上
                        if(arrangement[teacher[i].preference[j]][k] == -1){
                            arrangement[teacher[i].preference[j]][k] = i;
                            teacher[i].isArrangement++;
                            break;
                        }
                    }
                }else{
                    break;
                }
            }
        }
    }

    //给未排满课的老师排课，现在需要计算交通费了
    for(int i=0; i < teacherNumber; i++){
        if(teacher[i].isArrangement < 2){
            //查看周一至周五哪些时间还没排课
            for(int j=0; j < 5; j++){
                if(teacher[i].isArrangement < 2){ //如果给老师的两堂课都排好了，就进行下一个老师
                    for(int k=0; k < 3; k++){ //循环上午、下午，晚上
                        if(arrangement[teacher[i].preference[j]][k] == -1){
                            //计算交通费
                            if(teacher[i].position == 0){
                                totalTrafficExpense += 150;
                            }else{
                                totalTrafficExpense += 100;
                            }
                            arrangement[teacher[i].preference[j]][k] = i;
                            teacher[i].isArrangement++;
                            break;
                        }
                    }
                }else{
                    break;
                }
            }
        }
    }
}

void display(){
    printf("   星期一  星期二  星期三  星期四  星期五\n");
    for(int i=0; i < 3; i++){
        switch(i){
            case 0:
                printf("上午 ");
                break;
            case 1:
                printf("下午 ");
                break;
            case 2:
                printf("晚上 ");
                break;
        }
        for(int j=0; j < 5; j++){
            if(arrangement[j][i] != -1){
                printf("%s      ", teacher[arrangement[j][i]].name);
            }else{
                printf("        ");
            }
        }
        printf("\n");
    }

    printf("交通费用为：%d\n", totalTrafficExpense);
}
