#include "header.h"

int addtwonum()
{
    // 函数内声明变量 x 和 y 为外部变量
    extern int x;
    extern int y;
    // 给外部变量（全局变量）x 和 y 赋值
    x = 1;
    y = 2;
    return x+y;
}

typedef struct Book{
    char title[50];
    char author[50];
    char subject[100];
    int book_id;
}Books;
void printBook(Books *book);

int main()
{
//    强制类型转换
    int sum = 17, count = 5;
    double mean;
    mean = (double) sum / count;
    printf("Value of mean : %f\n", mean );

    int result;
    // 调用函数 addtwonum
    result = addtwonum();
    printf("X:%d Y:%d\n",x,y);
    printf("result 为: %d\n",result);

    int area = LENGTH * WIDTH;
    printf("area: %d\n",area);

    const char NEWLINE = '\n';
    printf("%c",NEWLINE);

    while(count--){
        func1();
    }

    int n[10];
    for(int i=0;i<10;i++){
        n[i] = i+100;
    }
    for(int i=0;i<10;i++){
        printf("%d ",n[i]);
    }
    printf("\n");

    const char *names[] = {"one","two","three"};
    for(int i=0;i<3;i++){
        printf("%s\t",names[i]);
    }
    printf("\n");

//    int (*p)(int,int) = max;
//    int a,b,c,d;
//    printf("please input three number: ");
//    scanf("%d %d %d",&a,&b,&c);
//    d = p(p(a,b),c);
//    printf("max number is: %d ",d);

    char str1[12] = "hello";
    char str2[12] = "world";
    char str3[12];
    int  len ;

    /* 复制 str1 到 str3 */
    strcpy(str3, str1);
    printf("strcpy( str3, str1) :  %s\n", str3 );

    /* 连接 str1 和 str2 */
    strcat( str1, str2);
    printf("strcat( str1, str2):   %s\n", str1 );

    /* 连接后，str1 的总长度 */
    len = strlen(str1);
    printf("strlen(str1) :  %d\n", len );

    Books book1;
    Books book2;
    strcpy(book1.title, "C Programming");
    strcpy(book1.author, "Nuha Ali");
    strcpy(book1.subject, "C Programming Tutorial");
    book1.book_id = 6495407;
    printBook(&book1);

//    字符串输入
//    int c;
//    printf( "Enter a value :");
//    c = getchar( );
//    printf( "You entered: ");
//    putchar( c );
//    printf( "\n");
//    getchar();
//
//    char str[100];
//    printf( "Enter a value :");
//    fgets(str, sizeof(str), stdin); //stdin 意思是键盘输入
//    printf( "You entered: ");
//    fputs(str, stdout); //stdout 意思是通过打印设备输出
//    printf( "\n");
//
//    printf( "Enter a value :");
//    scanf("%s", str);
//    printf( "You entered: ");
//    printf("%s", str);

//    文件读写
//    FILE *fp = NULL;
//    fp = fopen("test.txt","w+");
//    fprintf(fp,"this is testing for fprintf...\n");
//    fputs("this is testing for puts ...\n",fp);
//    fclose(fp);
//
//    char buff[255];
//    fp = fopen("test.txt", "r");
//    fscanf(fp, "%s", buff);
//    printf("1: %s\n", buff );
//    fgets(buff, 255, (FILE*)fp);
//    printf("2: %s\n", buff );
//    fgets(buff, 255, (FILE*)fp);
//    printf("3: %s\n", buff );
//    fclose(fp);

    for(int i=0;i<10;i++){
        printf("%d ",fibonaci(i));
    }

    char *description;
    description = (char *)malloc(200 * sizeof(char));
    strcpy(description,"zara ali a dps student in class 10th");
    printf("\n%s\n",description);
    description = (char *) realloc( description, 100 * sizeof(char) );
    free(description);

    //冒泡排序
    int arr[] = {22, 34, 3, 32, 82, 55, 89, 50, 37, 5, 64, 35, 9, 70};
    len = (int)sizeof(arr) / sizeof(*arr);
    bubble_sort(arr,len);
    for(int i=0;i<len;i++)
        printf("%d ",arr[i]);
    printf("\n");

    return 0;
}

void bubble_sort(int arr[],int len){
    int temp=0;
    for(int i=0;i<len-1;i++){
        for(int j=0;j<len-i-1;j++){
            if(arr[j]>arr[j+1]){
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
        }
    }
}

int fibonaci(int i){
    if(i<=0)
        return 0;
    if (i<=1)
        return 1;
    return fibonaci(i-1)+fibonaci(i-2);

}

void printBook(Books *book){
       printf( "Book title : %s\n", book->title);
       printf( "Book author : %s\n", book->author);
       printf( "Book subject : %s\n", book->subject);
       printf( "Book book_id : %d\n", book->book_id);
}

int max(int x,int y){
    return x>y?x:y;
}

void func1(void){
    static int x=5;
    x++;
    printf("X为%d\t count为%d\n",x,count);
}
