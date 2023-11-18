#include <stdio.h>


void printDivisors(int num,int divideNum){
    if(divideNum>num || num<=1)
    return;
    if(num%divideNum==0){
        printf("%d ",divideNum);
        printDivisors(num/divideNum,divideNum);
    }
    else{
        printDivisors(num,divideNum+1);
    }
}

int main(){
    printDivisors(20,2);
    return 0;
}