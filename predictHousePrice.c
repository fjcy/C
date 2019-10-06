#include <stdio.h>
#include <math.h>

double x[10][4] = {{2.5,0.5,0.0325,4000},{2.6,0.3,0.0325,4125},{2.7,0.4,0.03,4400},{2.4,0.2,0.03,4560},{2.5,0.15,0.0275,4700},
                    {2.2,0.1,0.025,4820},{1.8,-0.1,0.02,4900},{1.6,-0.3,0.0175,5050},{1.45,0.0,0.0175,5104},{1.5,0.1,0.015,5200}};
double y[10] = {6700,7100,7250,7500,7550,7500,7500,7420,7300,7460};
double theta[5]={0}; //teheta[0]表示一个偏置值

void cost(double theta[], double error[]){
    for(int i=0; i < 10; i++){
        error[i] = theta[0] + x[i][0] * theta[1] + x[i][1] * theta[2] + x[i][2] * theta[3] + x[i][3] * theta[4] - y[i];
    }
}

double getSum(double term[]){
    double sum = 0;
    for(int i=0; i < 10; i++){
        sum += term[i];
    }
}

void featureScaling(double x[][4]){
    static double avg = 0;
    static double std = 0;
    double sum=0;
    double squareSum=0;

    if(avg == 0 && std == 0){
        //这里面处理有标签的数据
        for(int i=0; i < 10; i++){
            sum += x[i][3];
        }
        avg = sum / 10.0;

        for(int i=0; i < 10; i++){
            squareSum += (x[i][3] - avg) * (x[i][3] - avg);
        }
        std = sqrt(squareSum / 10);

        for(int i=0; i < 10; i++){
            x[i][3] = (x[i][3] - avg) / std;
        }
    }else{
        //这里面处理代预测的数据
        for(int i=0; i < 4; i++){
            x[i][3] = (x[i][3] - avg) / std;
        }
    }
}

void gradientDescent(double alpha, int iters){
    double error[10] = {0};
    double term[10] = {0};

    for(int i=0;i < iters; i++){
        cost(theta, error);
        for(int j=0; j < 5; j++){
            if(j == 0){
                theta[0] -= (alpha/10) * getSum(error);
            }else{
                for(int k=0; k < 10; k++){
                    term[k] = error[k] * x[k][j-1];
                }

                theta[j] -= (alpha/10) * getSum(term);
            }
        }
    }
}

void predict(double predict_x[][4], double predict_y[]){
    featureScaling(predict_x);
    for(int i=0; i < 4; i++){
        predict_y[i] = theta[0] + predict_x[i][0] * theta[1] + predict_x[i][1] * theta[2] + predict_x[i][2] * theta[3] + predict_x[i][3] * theta[4];
    }
}

int main(){
//    double beforePrice[] = {6700,7100,7250,7500,7550,7500,7500,7420,7300,7460};
//    double beforeCPI[] = {2.5,2.6,2.7,2.4,2.5,2.2,1.8,1.6,1.45,1.5};
//    double beforePPI[] = {0.5,0.3,0.4,0.2,0.15,0.1,-0.1,-0.3,0.0,0.1};
//    double beforeRate[] = {0.0325,0.0325,0.03,0.03,0.0275,0.025,0.02,0.0175,0.0175,0.015};
//    double beforeIncome[] = {4000,4125,4400,4560,4700,4820,4900,5050,5104,5200};
//    double afterCPI[] = {1.5,1.6,1.7,1.7};
//    double afterPPI[] = {0.1,-0.2,0.1,0.2};
//    double afterRate[] = {0.175,0.175,0.2,0.225};
//    double afterIncome[4] = {0};

    double predict_x[4][4] = {{1.5,0.1,0.175,0},{1.6,-0.2,0.175,0},{1.7,0.1,0.2,0},{1.7,0.2,0.225,0}};
    double predict_y[4] = {0};
    for(int i=0; i < 4; i++){
        predict_x[i][3] = 5200 * pow(1.02,i+1);
    }

    featureScaling(x);

    double alpha=0.3;
    int iters=1000;
    gradientDescent(alpha,iters);
//    printf("theta: %lf  iters:%d\n",alpha,iters);
//    for(int i=0; i < 5; i++){
//        printf("%lf  ",theta[i]);
//    }
//    printf("\n");
//    for(int i=0;i<10;i++){
//        double temp_x,temp_loss;
//        temp_x = theta[0] + x[i][0] * theta[1] + x[i][1] * theta[2] + x[i][2] * theta[3] + x[i][3] * theta[4];
//        printf("%lf %lf %lf\n",temp_x,y[i],temp_x-y[i]);
//    }

    predict(predict_x, predict_y);

    printf("未来四个季度的房价分别为：\n");
    for(int i=0; i < 4; i++){
        printf("%.2lf  ",predict_y[i]);
    }
    printf("\n");

    return 0;
}
