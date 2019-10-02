#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node{
   char s[100];
   int len;
}Digit;

//将字符串赋值到串里
void init(Digit *a, char *data){
   int i, len;
   len = strlen(data);
   for(i=0; i < len; i++){
        a->s[i] = 0;
        a->s[i] = data[i];
   }
   a->s[i] = '\0';
   a->len = len;
}

int com(Digit *a1,Digit *b1){//比较两数的大小。
    if(a1->len>b1->len){ return 1;}
    else if(a1->len==b1->len) {
       int i=0;
       while(a1->s[i]==b1->s[i]&&i<a1->len){
            i++;
       }
       if(i==a1->len) return 0;
       else if(a1->s[i]>b1->s[i]) return 1;
       else return -1;
    }
    else return -1;

}

void add(Digit *a1,Digit *b1,Digit *c1){
    char pp[100];
    int a[100];//加数
    int b[100];//被加数
    int c[100]={0};//和
    int i,j=0,k;//i用来循环，j表示进位 ，两加数中较小加数的长度放到k里
    int l1,l2,d;
    l1=a1->len;
    l2=b1->len;
    k=l1>l2?l2:l1;
    for(i=0;i<a1->len;i++){//字符串逆序导入数组中
         a[i]=a1->s[l1-1-i]-'0';
    }
    for(i=0;i<b1->len;i++){
         b[i]=b1->s[l2-1-i]-'0';
    }
    for(i=0;i<k;i++){
       d=a[i]+b[i]+j;
       j=d/10;
       c[i]=d%10;
    }
    while(i<l1){
        d=a[i]+j;
        j=d/10;
        c[i]=d%10;
        i++;
    }
     while(i<l2){
        d=b[i]+j;
        j=d/10;
        c[i]=d%10;
        i++;
    }
   if(j>0){c[i]=j;i++;}
   for(j=0,k=i-1;k>-1;k--,j++)
    pp[j]=c[k]+'0';
    pp[j]='\0';
   init(c1,pp);

}

void subtract(Digit *a1,Digit *b1,Digit *c1){
    int a[100];//把较大的数放于减数
    int b[100];//把较小的数放于被减数
    int c[100]={0};//差
    int i,j,k;//i用来循环 ,两加数中较大加数的长度放到j里，两加数中较小加数的长度放到k里
    int flag;//标志结果为正还是负。
    int l1,l2;
    char pp[100];
    l1=a1->len;
    l2=b1->len;
    k=l1>l2?l2:l1;
    j=l1<l2?l2:l1;
    if(strcmp(a1->s,b1->s)==0){
        init(c1,"0");
    }
    else{
        if(com(a1,b1)>=0){//减数必须大于被减数。方便计算。如果小于，就调换位置。
            flag=0;
            for(i=0;i<l1;i++){//字符串逆序导入数组中
               a[i]=a1->s[l1-1-i]-'0';
            }
             for(i=0;i<l2;i++){
               b[i]=b1->s[l2-1-i]-'0';
            }
        }
        else{
             flag=1;
             for(i=0;i<l2;i++){
               a[i]=b1->s[l2-1-i]-'0';
            }
             for(i=0;i<l1;i++){
               b[i]=a1->s[l1-1-i]-'0';
            }
        }
        for(i=0;i<k;i++){
           if(a[i]>=b[i]) c[i]=a[i]-b[i];
              else{
              c[i]=a[i]+10-b[i];
              --a[i+1];
           }

         }

    while(i<j){
           if(a[i]>=0) c[i]=a[i];
           else{
               c[i]=a[i]+10;
              --a[i+1];
           }
          i++;
        }
        while(c[i-1]==0) i--;
         j=0;
        if(flag==1)
           pp[j++]='-';
        for(k=i-1;k>-1;k--,j++)
            pp[j]=c[k]+'0';
        pp[j]='\0';
       init(c1,pp);
    }
}

void multiply(Digit *a1,Digit *b1,Digit *c1){

    int a[100];
    int b[100];
    int c[100]={0};
    int d,i,j,k;//i,j用来循环
    int flag=0;//进位
    int l1,l2;
    l1=a1->len;
    l2=b1->len;
     init(c1,"0");
    for(i=0;i<a1->len;i++){
         a[i]=a1->s[l1-1-i]-'0';
    }
    for(i=0;i<b1->len;i++){
         b[i]=b1->s[l2-1-i]-'0';
    }
    for(i=0;i<l2;i++){
        flag=0;
        for(j=0;j<l1;j++){
            d=a[j]*b[i]+flag;
            c[j]=d%10;
            flag=d/10;
        }
        if(flag>0){
            c[j]=flag;
            j++;
        }
        while(c[j-1]==0)j--;

        char str[100];
        for(k=0;k<j;k++)
            str[k]=c[j-1-k]+'0';
        for(j=0;j<i;j++)str[k++]='0';
        str[k]='\0';
        Digit *ff;
        ff=(Digit *)malloc(sizeof(Digit));
        init(ff,str);
        add(c1,ff,c1);
    }

}

void one(char *a){
    int i,l=strlen(a);
    int carry=1;
    char t;
    for(i=0;i<l;i++){
        t=a[i]+carry;
        if(t>9+'0'){
            t='0';
            carry=1;
        }else{
            carry=0;
        }
        a[i]=t;
    }
    if(carry==1)a[i++]='1';
    a[i]='\0';
}

void divide(Digit *a1,Digit *b1,Digit *c1,Digit *d1){//C为商，D为余数
  // int i,j,k,
    char t[100]={0};
    char b[2]="0";
    if(com(a1,b1)==0){
        init(d1,"0");
        init(c1,"1");
    }else if(com(a1,b1)<0){
        init(d1, a1->s );
        init(c1, "0");
   }else{
        Digit *aa;
        aa=(Digit *)malloc(sizeof(Digit));
        init(aa,a1->s);
        while(com(aa,b1)>=0){
            subtract(aa,b1,c1);
            init(aa,c1->s);
            one(t);
        }
        init(c1,t);
        init(d1,aa->s);
   }
}

void menu(){
    printf("--------------------------------------------------------------\n");
    printf("-- 1.两数相加 \n");
    printf("-- 2.两数相减\n");
    printf("-- 3.两数相乘\n");
    printf("-- 4.两数相除\n");
    printf("-- 0.退出\n");
    printf("--------------------------------------------------------------\n");
}

int main(){
    Digit  *a, *b, *c, *d;;
    a = (Digit *)malloc(sizeof(Digit));
    b = (Digit *)malloc(sizeof(Digit));
    c = (Digit *)malloc(sizeof(Digit));
    d = (Digit *)malloc(sizeof(Digit));
    char a1[100], b1[100];
    int operation;

    printf("请输入第一个操作数：");
    scanf("%s", &a1);
    printf("请输入第二个操作数：");
    scanf("%s", &b1);
    init(a, a1);
    init(b, b1);

   do{
        menu();
        printf("请选择操作： \n");
        scanf("%d",&operation);
        switch(operation){
            case 1:
                add(a,b,c);
                printf("两者之和为：%s\n",c->s);
                break;
            case 2:
                subtract(a,b,c);
                printf("两者之差为：%s\n",c->s);
                break;
            case 3:
                multiply(a,b,c);
                printf("两者之积为：%s\n",c->s);
                break;
            case 4:
                if(strcmp(b->s,"0") == 0){
                    printf("除数不能为0");break;
                }else{
                    divide(a,b,c,d);
                    printf("商为:  ") ;
                    int i = strlen(c->s)-1;
                    for(;i>=0;i--){
                        printf("%c", c->s[i]);
                    }
                    printf("\t余数为:%s\n",d->s);
                }
                break;
            case 0:
                break;
            default:
                printf("输入错误，请重新输入!\n");
                break;
        }
    }while(operation != 0);

    return 0;
}
