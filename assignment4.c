//
// Created by BMT on 9/18/2022.
//
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
int main(){
    FILE *fptr;
    FILE *fTemp;
    int id;
    char username[30];
    char password[30];
    int amount;
    fptr= fopen("assignment4.txt","r");
    if(fptr==NULL){
        printf("File cannot be opened!");
        exit(1);
    }

    int choice;
    int inputCount=0;
    int count=0;
    char temp[1000];
    char search[30];
    int lineNum=1;
    int findResult=0;
    do {
        puts("Press 1 to insert data,Press 2 to Find data,Press 3 to reload ,Press 4 to exit.");
        scanf(" %d",&choice);
        switch (choice) {
            case 1:
                fptr= fopen("assignment4.txt","a");
                printf("Enter the number of data you want to input: ");
                scanf("%d",&inputCount);
                while(count<inputCount){
                    puts("Enter id,username,password,amount");
                    scanf("%d%s%s%d",&id,username,password,&amount);
                    fprintf(fptr,"%d%8s%8s%5d\n",id,username,password,amount);
                    count+=1;
                };break;
            case 2:
                fptr= fopen("assignment4.txt","r");
                printf("Enter the data you want to search: ");
                scanf("%s",search);
                while(fgets(temp,sizeof temp,fptr)!=NULL){
                    if(strstr(temp,search)!=NULL){
                        printf("we found %s at line %d \n",search,lineNum);
                        printf(" %s",temp);
                        findResult++;
                    }
                    lineNum++;
                }
                if(findResult==0){
                    puts("we couldn't find your data.");
                }
                break;
            case 3:
                fptr= fopen("assignment4.txt","w");
                printf("Enter the number of data you want to input: ");
                scanf("%d",&inputCount);
                while(count<inputCount){
                    puts("Enter id,username,password,amount");
                    scanf("%d%s%s%d",&id,username,password,&amount);
                    fprintf(fptr,"%d%8s%8s%5d\n",id,username,password,amount);
                    count+=1;
                }
                break;

            default:break;
        }
    }while(choice!=4);
    fclose(fptr);

    return 0;
}