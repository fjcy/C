#include <stdio.h>
#include <string.h>

char content[100][1000];
int maxline = 0; // 文章的总行数

int ReadDat (void);
void WriteDat(void);

void encryptChar(){
    for(int i=0; i < maxline; i++){
        for(int j=0; j < strlen(content[i]); j++)
            if(content[i][j] * 11 % 256 <= 32 || content[i][j] % 2 == 0)
                continue;
            else
                content[i][j] = content[i][j] * 11 % 256;
    }
}

int main(){
    if (ReadDat()){
        printf("数据文件file.txt读取失败!\n");
        return;
    }
    encryptChar();
    WriteDat();
}

int ReadDat (void){
    FILE *fp;
    int i = 0;
    char *p;

    if((fp = fopen("file.txt", "r")) == NULL)
        return 1;

    while(fgets(content[i], 500, fp) != NULL){
        p = strchr(content[i], '\n'); //去掉换行符
        if(p){
            *p = 0;
        }
        i++;
    }

    maxline = i;
    fclose(fp);
    return 0;
}

void WriteDat(void){
    FILE *fp;

    if((fp = fopen("encryptfile.txt", "w")) == NULL){
        printf("encryptfile.txt写入失败");
    }

    for(int i=0; i < maxline; i++){
        fprintf(fp, "%s\n", content[i]);
    }

    fclose(fp);
}
