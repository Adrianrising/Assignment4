//
// Created by BMT on 9/18/2022.
//
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "stdbool.h"
#define MAX_LINE 2048

int main(){
    //file pointers
    FILE *fptr,*tempF;
    //for case 1
    int id;
    char username[30];
    char password[30];
    int amount;
    int choice;
    int inputCount=0;
    int count=0;
    //for case 2
    char temp[1000];
    char search[30];
    int lineNum=1;
    int findResult=0;
//    for case 3
    char buffer[MAX_LINE];
    char replace[MAX_LINE];
    int replaceLineNo;
    int currentLine=1;

    do {
        //prints user options
        puts("Press 1 to insert data,Press 2 to Find data,Press 3 to update data,Press 4 to exit.");
        scanf(" %d",&choice);
        switch (choice) {
            case 1:
                //opens the file in apppend mode
                fptr= fopen("assignment4.txt","a");
                //if null opens file in write mode
                if(fptr==NULL){
                    fptr= fopen("assignment4.txt","w");
                }
                //ask for the input count
                printf("Enter the number of data you want to input: ");
                scanf("%d",&inputCount);
                //prints data into file
                while(count<inputCount){
                    puts("Enter id,username,password,amount");
                    scanf("%d%s%s%d",&id,username,password,&amount);
                    fprintf(fptr,"%d%8s%8s%5d\n",id,username,password,amount);
                    count+=1;
                };
                break;
            case 2:
                //opens file in read mode
                fptr= fopen("assignment4.txt","r");
                //if file does not exist or is null exit with code 1
                if(fptr==NULL){
                    printf("File cannot be opened!");
                    exit(1);
                }
                //asks for the word to search
                printf("Enter the data you want to search: ");
                scanf("%s",search);
                //search in the file for word
                //fgets searchs the file line by line with while loop
                while(fgets(temp,sizeof temp,fptr)!=NULL){
                    //strstr() search for the word in file and store it in the temp array
                    if(strstr(temp,search)!=NULL){
                        printf("we found %s at line %d \n",search,lineNum);
                        printf(" %s",temp);
                        findResult++;
                    }
                    lineNum++;
                }
                lineNum=1;
                if(findResult==0){
                    puts("we couldn't find your data.");
                }
                break;
            case 3:
                //opens file in read mode
                fptr= fopen("assignment4.txt","r");
                if(fptr==NULL){
                    printf("Cannot open file or file does not exist");
                    return 1;
                }
                //opens temporary file in write mode
                tempF= fopen("temporaryFile.txt","w");
                if(tempF==NULL){
                    printf("Cannot open file or file does not exist");
                    return 1;
                }
                //asks for the line to remove
                printf("Enter the line to remove: ");
                scanf("%d",&replaceLineNo);
                //using fflush() to get rid of "\n" cuz scanf leaves at the end of line"\n"
                //fgets will stop working if it meets new line char
                fflush(stdin);//removes the new line char
                bool keepReading=true;
                do {
                    //gets each line of fptr into buffer array
                    fgets(buffer,MAX_LINE,fptr);
                    //array terminating point
                    if(feof(fptr)){
                        keepReading=false;
                    }
                    //if replace line>>prints the replace line to the file instead of ori line
                    else if(currentLine==replaceLineNo){
                        puts("Enter id,username,password,amount");
                        scanf("%d%s%s%d",&id,username,password,&amount);
                        fprintf(tempF,"%d%8s%8s%5d\n",id,username,password,amount);
                    }else{
                        //if not replace line>>puts ori line in file
                        fputs(buffer,tempF);
                    }
                    currentLine++;

                } while (keepReading);
                fclose(fptr);
                fclose(tempF);
                remove("assignment4.txt");
                rename("temporaryFile.txt","assignment4.txt");
                break;
            default:break;
        }
    }while(choice!=4);
    fclose(fptr);
    return 0;
}

