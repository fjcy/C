#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct BookStore
{
    //书名
    char name[100];
    //作者
    char author[50];
    //出版社
    char publish[50];
    //出版日期
    char date[20];
    //价格
    double price;
    //图书的数量
    int bookCount;
    //卖掉的数量
    int saleCount;
    //在目录中的位置
    char location[50];
}Books;

void menu();
void readFIle(char path[]);
void printBookInfo(Books book);
void recommend();
void writeFile(char path[]);
void writeFile(char path[]);
void printAllBooksInfo();

Books books[100];
int bookCount=0; //有多少种书

int main(){
    int choice;
    char path[] = "bookInfo.txt";
    readFile(path);
    do{
        menu();
        scanf("%d",&choice);
        switch(choice){
            case 1:
                purchase();
                break;
            case 2:
                recommend();
                break;
            case 3:
                printAllBooksInfo();
                break;
            case 4:
                break;
            default:
                printf("请重新输入\n");
                break;
        }
    }while(choice != 4);

    writeFile(path);

    return 0;
}

void readFile(char path[]){
    FILE *fp = fopen(path,"r");
    if(!fp){
        printf("打开文件失败\n");
        return;
    }

    char temp[500]; //临时存储从文件中读取的每行字符串
    char *split; //用来存储分割后的字符串
    int column; //用来记录当前的字段
    while(fgets(temp, 500, fp) != NULL){
        column = 1;
        split = strtok(temp, ",");
        while (split != NULL) {
            switch(column){
                case 1:
                    strcpy(books[bookCount].name, split);
                    break;
                case 2:
                    strcpy(books[bookCount].author, split);
                    break;
                case 3:
                    strcpy(books[bookCount].publish, split);
                    break;
                case 4:
                    strcpy(books[bookCount].date, split);
                    break;
                case 5:
                    books[bookCount].bookCount = atoi(split);
                    break;
                case 6:
                    books[bookCount].saleCount = atoi(split);
                    break;
                case 7:
                    books[bookCount].price = atoi(split);
                    break;
                case 8:
                    strcpy(books[bookCount].location, split);
                    break;
            }
            column++;
            split = strtok(NULL, ",");
        }
        bookCount++;
    }

    fclose(fp);
}

void writeFile(char path[]){
    FILE *fp = fopen(path,"w+");
    if(!fp){
        printf("打开文件失败\n");
        return;
    }

    for(int i=0;i<bookCount;i++){
        fprintf(fp,"%s,%s,%s,%s,%d,%d,%lf,%s",
            books[i].name,books[i].author,books[i].publish,books[i].date,books[i].bookCount,books[i].saleCount,books[i].price,books[i].location);
    }

    fclose(fp);
}

//菜单
void menu(){
    printf("-------------------------------------------------\n");
    printf("--  1 - 购买书籍                                --\n");
    printf("--  2 - 热销书推荐                              --\n");
    printf("--  3 - 查看所有图书信息                        --\n");
    printf("--  4 - 退出                                   --\n");
    printf("-------------------------------------------------\n");
}

//购买图书
void purchase(){
    char name[100],author[50];
    int i; //用来判断是否找到
    int purchaseNumber=0;
    getchar();
    printf("请输入欲购买图书的信息\n");
    printf("书名：");
    scanf("%[^\n]",name); //[^\n]的作用是如果输入的字符属于方括号内字符串中某个字符，那么就提取该字符；如果一经发现不属于就结束提取
    getchar();
    printf("作者：");
    scanf("%[^\n]",author);

    for(i=0;i<bookCount;i++){
        if(strcmp(books[i].name,name) == 0 && strcmp(books[i].author,author) == 0){
            printBookInfo(books[i]);
            printf("请输入所需数量：");
            scanf("%d",&purchaseNumber);
            if(purchaseNumber <= books[i].bookCount){
                printf("总价为：%.2lf\n",purchaseNumber*books[i].price);
                books[i].bookCount -= purchaseNumber;
                books[i].saleCount += purchaseNumber;
                printf("购买成功\n");
            }else{
                printf("所需数量不在库存范围内\n");
            }
            break;
        }
    }

    if(i == bookCount){
        printf("谢谢，再见！\n");
    }
}

//推荐图书
void recommend(){
    srand((unsigned)time(NULL));
    int maxSale = 0,index;
    index = rand() % bookCount; //随即选择一本
    for(int i=0;i<bookCount;i++){
        if(books[i].saleCount > maxSale){
            maxSale = books[i].saleCount;
            index = i;
        }
    }
    printBookInfo(books[index]);
}

//打印所有图书信息
void printAllBooksInfo(){
    for(int i=0;i<bookCount;i++){
        printf("书名：%s\n", books[i].name);
        printf("作者：%s\n", books[i].author);
        printf("出版社：%s\n", books[i].publish);
        printf("出版时间：%s\n", books[i].date);
        printf("库存：%d本\n", books[i].bookCount);
        printf("价格：%.2lf元\n", books[i].price);
        printf("索书号：%s\n", books[i].location);
    }
}

//打印图书信息
void printBookInfo(Books book){
        printf("书名：%s\n", book.name);
        printf("作者：%s\n", book.author);
        printf("出版社：%s\n", book.publish);
        printf("出版时间：%s\n", book.date);
        printf("库存：%d本\n", book.bookCount);
        printf("价格：%.2lf元\n", book.price);
        printf("索书号：%s\n", book.location);
}
