/*
File Name: student.txt
File Content: 
5
01 Pritha 50
02 Anurina 70
03 Bijeta 30
04 Arapita 40
05 Susmita 60
Problem:
A set of students information roll, name, marks are given in a file. Read the name of file through command line arguments. Allocate an array of students records ( structure) using dynamic memory allocation. Print the list of students along with their marks (one per line) in increasing order and write their ranks: i.e  rank, roll, name, marks.*/
/* Name - Pratham Agarwal Roll - 224051*/

#include<stdio.h>
#include<stdlib.h>
int main(){
    struct student {
        int rank;
        int roll;
        char name[50];
        int marks;
    };
    struct student *std;
    struct student temp;
    FILE *fpr;
    fpr = fopen( "student.txt","r");
    int n;
    fscanf(fpr,"%d", &n);
    std = (struct student *)malloc(n * sizeof(struct student));
    for (int i = 0; i < n; ++i) {
    fscanf(fpr,"%d %s %d",&std[i].roll,std[i].name,&std[i].marks);
    }
    for (int i = 0; i < n; ++i)
    {
        for(int j = i+1; j < n; j++){
            if(std[i].marks<std[j].marks){
                temp=std[i];
                std[i]=std[j];
                std[j]=temp;
            }
        }
    }
    for (int i = 0; i < n; ++i)
        {
            std[i].rank = i+1;
        }
    printf("Displaying Information: in increasing order with their ranks\n");
    for (int i = 0; i < n; ++i) {
    printf("%d\t%d\t%s\t%10d\n",std[i].rank,std[i].roll,std[i].name,std[i].marks);
    }
    fclose(fpr);
    free(std);
    return 0;
}