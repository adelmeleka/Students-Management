#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <stdbool.h>
//The maximum size of the program is 1000 students(can be changed from here)
#define SIZE 1000

//defining structures and their fields
typedef struct{
    char city[50];
    int MobileNumber;
    char email[50];
}ContactInfo;

typedef struct{
    char name[50];
    int id;
    int age;
    ContactInfo contact;
    float score;
}Students;
Students st[SIZE];

//Load Function
void Read(char *name,int m,Students *ptr,int n,int *act_size){
    FILE *f1;
    int i=0;
    char c;
    printf("\n\t\t\t\tReading The File");
    printf("\n\t\t\t\t----------------");
    f1=fopen(name,"r");
    if(f1==NULL){
        printf("Error opening the file!\n");
        exit(-1);
    }
    c=getc(f1);
    if(c==EOF)
        printf("\n The File is empty!");
        else{
    //saving the file values from the file into the array each of them in it's fields
    while(!feof(f1)){
            fscanf(f1,"%[^,], %d, %[^,], %d, %[^,], %d, %f",ptr[i].name,&ptr[i].id,ptr[i].contact.city,&ptr[i].contact.MobileNumber,ptr[i].contact.email,&ptr[i].age,&ptr[i].score);
            fscanf(f1,"\n");
    i++;
    }
    (*act_size)=i;
    fclose(f1);
        }
    printf("\n\t\t\t\tReading The File DONE!");
    printf("\n\n\n");
    printf("\n-----------------------------------------------------------------------------------------------------------------------");
}

//Print Function
void Print(Students *ptr,int n){
    printf("\n\t\t\t\tPrinting The Data");
    printf("\n\t\t\t\t-----------------");
    int i,pass;
    int swapp=1;
    Students temp;
    if(n==0)
        printf("\n  File Is Empty !");
    else{
    //sorting the array
   for(pass=1;pass<n&&swapp==1;pass++){
        swapp=0;
    for(i=0;i<n-pass;i++){
        if(ptr[i].id>ptr[i+1].id){
            temp=ptr[i];
            ptr[i]=ptr[i+1];
            ptr[i+1]=temp;
            swapp=1;
        }
    }
   }
    //printig the array
    printf("\n ID\tNAME\t\t   CITY\t\t   MOBILE NUMBER\tEMAIL\t\t       AGE\t      GPA\n");
        for(i=0;i<n;i++){
            printf("% d\t\%s\t   %s\t   0%d\t\t%s\t       %d\t      %.2f\n",ptr[i].id,ptr[i].name,ptr[i].contact.city,ptr[i].contact.MobileNumber,ptr[i].contact.email,ptr[i].age,ptr[i].score);
        }
    }
    printf("\n\t\t\t\tPrinting Data DONE!");
    printf("\n\n\n");
    printf("\n-----------------------------------------------------------------------------------------------------------------------");
}

//String Validation (Bonus)
void StringValidation(char *ptr){
    gets(ptr);
    int i;
    int check=1;
    while(1){
    for(i=0;i<strlen(ptr);i++){
        if(isdigit(ptr[i])){
            check=0;
            break;
        }
    }
    if(check==0){
        printf("\n Invalid Input ! You must only enter charcters !\n");
        getchar();
        gets(ptr);
        check=1;
    }
    else
        break;
    }
}

//Number Validation Function (Bonus)
void NumberValidation(int *num){
    char term;
    while(scanf("%d%c", num, &term) != 2 || term != '\n'){
        printf("\n Invalid Input ! You must enter a valid number consisting of digits only !\n");
        scanf("%*s");
    }
}

//GPA(score) Validation Function (Bonus)
void GpaValidation(float *num){
    //first check if it's a valid float (digits only)
    char term;
        while(scanf(" %f%c", num, &term) != 2 || term != '\n'){
        printf("\nInvalid Input ! GPA must be only digits !\n");
        scanf("%*s");
    }
    //secondly,checking if it's in the range from 0 to 4
    while(!(*num<=4 &&*num>=0)){
        printf("\nInvalid Input ! GPA must be digits in range from 0 to 4 only !\n");
        scanf("%f",num);
        while(scanf("%f%c", num, &term) != 2 || term != '\n'){
        printf("\nInvalid Input ! GPA must be only digits !\n");
        scanf("%*s");

    }
    }
}

// com mail validation2 (Bouns)
int MyStringComp(char *str){
    if((str[0]=='c' ||str[0]=='C') && (str[1]=='o' ||str[1]=='O') && (str[2]=='m' ||str[2]=='M') && str[3]=='\0' )
        return 1;
    else
        return -1;
}
//mail Validation1 (Bonus)
bool EmailCheck(char *str){
    int i=0;
    int j=0;
    int z;
    char com[10];
    bool atflag=false;
    bool dtflag=false;

    while(str[i]){
        if(i==0 && (str[i]=='@' || (str[i])=='.') ){
            return false;
        }
        else if(str[i]=='@' && atflag ){

            return false;
        }
        else if(str[i]=='@'){
            if(str[i+1]=='.'){
                return false;
            }else atflag=true;
        }
        else if(str[i]=='.' && atflag && !dtflag ){
            if(!str[i+1]){
                return false;
            }
            dtflag=true;
        }
        else if(str[i]=='.' && atflag && dtflag){
            return false;
        }
        else if(atflag && dtflag ){
            com[j]=str[i];
            j++;
        }
        i++;
    }
    com[j]='\0';
    z=MyStringComp(com);
    if(atflag && dtflag && z==1){
        return true;
    }
    else{
        return false;
    }
}
//Mail Validation Function (Bonus)
void EmailValidation(char *ptr){
    int z;
    //getchar();
    gets(ptr);
    z=EmailCheck(ptr);
    while(z==0){
            printf("\n Invalaid Email! Please enter a Valid email!\n");
            gets(ptr);
            z=EmailCheck(ptr);
    }
}

//Query Function
void Search(Students *ptr,int n){
    printf("\n\t\t\t\tSearch");
    printf("\n\t\t\t\t------");
    int i,found=0;
    int id;
    if(n==0)
        printf("\n  File Is Empty !");
    else{
    printf("\n-->Enter the Student's ID: ");
    NumberValidation(&id);
    for(i=0;i<n;i++){
        if(id==ptr[i].id){
                found=1;
            printf("\n Name: %s",ptr[i].name);
            printf("\n ID: %d",ptr[i].id);
            printf("\n City: %s",ptr[i].contact.city);
            printf("\n Mobile Number: 0%d",ptr[i].contact.MobileNumber);
            printf("\n Email: %s",ptr[i].contact.email);
            printf("\n Age: %d",ptr[i].age);
            printf("\n GPA: %.2f",ptr[i].score);
        }
        if(found)
        break;
    }
        if(!found)
            printf("\n Student with the entered ID not found!\n");
    }
    printf("\n\t\t\t\tSearch DONE!");
    printf("\n\n\n");
    printf("\n-----------------------------------------------------------------------------------------------------------------------");
}

//Update_Score Function
void UpdateGPA(Students *ptr,int n){
    printf("\n\t\t\t\tUpdate GPA");
    printf("\n\t\t\t\t------------");
    int id;
    int i,found=0;
    if(n==0)
        printf("\n  File Is Empty !");
    else{
    printf("\nPlease enter the Student's ID: ");
    NumberValidation(&id);
        for(i=0;i<n;i++){
        if(id==ptr[i].id){
                found=1;
                printf("\nCurrent Score: %.2f",ptr[i].score);
                printf("\n-->Enter the new score: ");
                GpaValidation(&ptr[i].score);
        }
        if(found)
        break;
    }
        if(!found)
            printf("\n Student with the entered ID not found!");
    }
    printf("\n\t\t\t\tUpdate Score DONE!");
    printf("\n\n\n");
    printf("\n-----------------------------------------------------------------------------------------------------------------------");
 }

//Add Function
void Add(Students *ptr,int *act_size){
     printf("\n\t\t\t\tAdd");
     printf("\n\t\t\t\t---");
     if(*act_size==SIZE)
        printf("\n  Memory Full !");
     else{
     printf("\nPlease fill in the new Student's Information:");
     printf("\n -->Name: ");
    // getchar();
     StringValidation(ptr[*act_size].name);
     printf("\n -->ID: ");
     NumberValidation(&ptr[*act_size].id);
     printf("\n -->City: ");
     StringValidation(ptr[*act_size].contact.city);
     printf("\n -->Mobile Number: ");
     NumberValidation(&ptr[*act_size].contact.MobileNumber);
     printf("\n -->Email: ");
     EmailValidation(ptr[*act_size].contact.email);
     printf("\n -->Age: ");
     NumberValidation(&ptr[*act_size].age);
     printf("\n -->GPA: ");
     GpaValidation(&ptr[*act_size].score);
     (*act_size)+=1;
     }
    printf("\n\t\t\t\tADD DONE!");
    printf("\n\n\n");
    printf("\n-----------------------------------------------------------------------------------------------------------------------");
}

//Delete Function
void Delete(Students *ptr,int *act_size){
    int id,swapp=1;
    int i,found=0;
    printf("\n\t\t\t\tDelete");
    printf("\n\t\t\t\t------");
    if(*act_size==0)
        printf("\n  File Is Empty !");
    else{
    printf("\n-->Enter the Student's ID: ");
    NumberValidation(&id);
    for(i=0;i<(*act_size);i++){
        if(id==ptr[i].id){
                found=1;
                ptr[i].id=999999;
        }
        if(found)
        break;
    }
    if(found==0)
        printf("\n Student with the entered ID not found!\n");
    int pass;
    Students temp;
    for(pass=1;pass<*act_size&&swapp==1;pass++){
        swapp=0;
    for(i=0;i<(*act_size)-pass;i++){
        if(ptr[i].id>ptr[i+1].id){
            temp=ptr[i];
            ptr[i]=ptr[i+1];
            ptr[i+1]=temp;
            swapp=1;
        }
    }
   }
   (*act_size)-=1;
    }
    printf("\n\t\t\t\tDelete DONE!");
    printf("\n\n\n");
    printf("\n-----------------------------------------------------------------------------------------------------------------------");
}

//Statistics Fumction
void Statistics(Students *ptr,int n){
     printf("\n\t\t\t\tStatistics");
     printf("\n\t\t\t\t----------");
    int i,pass;
    int swapp=1;
    Students temp;
    float average=0;
    if(n==0)
        printf("\n  File Is Empty !");
    else{
    //sorting the array
   for(pass=1;pass<n&&swapp==1;pass++){
        swapp=0;
    for(i=0;i<n-pass;i++){
        if(ptr[i].score<ptr[i+1].score){
            temp=ptr[i];
            ptr[i]=ptr[i+1];
            ptr[i+1]=temp;
            swapp=1;
        }
    }
   }
   printf("\nTop 5 students:");
   printf("\n\tNAME\t\t\t\tID");
   for(i=0;i<5;i++){
    printf("\n\t%s\t\t\t%d",ptr[i].name,ptr[i].id);
   }
   //finding the average
   for(i=0;i<n;i++){
    average+=ptr[i].score;
   }
   average/=(n*1.0);
   printf("\n\nMaximum Score: %.2f",ptr[0].score);
   printf("\n\nMinimum Score: %.2f",ptr[n-1].score);
   printf("\n\nAverage score: %.2f",average);
    }
   printf("\n\t\t\t\tStaistics DONE!");
   printf("\n\n\n");
   printf("\n-----------------------------------------------------------------------------------------------------------------------");
}

//Quit & Save Function
void QuitSave(char *name,int m,Students *ptr,int n){
     FILE *f1;
     printf("\n\t\t\t\tQuit");
     printf("\n\t\t\t\t----");
     int i;
     int option;
     printf("\nAre you sure you want to quit?...All changes including Adding or Deleteing data will be lost!");
     printf("\n\t1. Exit without saving\n\t2. Save changes and exit");
     printf("\n\n-->Enter an option: ");
     scanf("%d",&option);
     if(option==1){
        printf("\n\t\t\t\tChanges not saved!");
        printf("\n\t\t\t\tExiting!");
        exit(1);
     }
     else if(option==2){
        f1=fopen(name,"w");
        for(i=0;i<n;i++){
            fprintf(f1," %s,%d,%s,%d,%s,%d,%.2f",ptr[i].name,ptr[i].id,ptr[i].contact.city,ptr[i].contact.MobileNumber,ptr[i].contact.email,ptr[i].age,ptr[i].score);
            fprintf(f1,"\n");
        }
        fclose(f1);
        printf("\n\t\t\t\tSaved!");
        printf("\n\t\t\t\tExiting!\n");
        printf("\n\n\n");
        exit(1);
     }
     else{
        printf(" Wrong entry!");
     }
}

//Normalize Function (Bonus)
void Normalize(Students *ptr,int n){
    printf("\n\t\t\t\tNormalize Mode");
    printf("\n\t\t\t\t--------------");
    float average=0;
    int i;
    float percent;
    if(n==0)
        printf("\n  File Is Empty !");
    else{
    //finding the average
    for(i=0;i<n;i++){
    average+=ptr[i].score;
    }
   average/=(n*1.0);
   percent=average*5.0/100.0;
   for(i=0;i<n;i++){
    ptr[i].score+=percent;
    if(ptr[i].score>4)
        ptr[i].score=4;
   }
    }
    printf("\n\t\t\t\tNormalize DONE!");
    printf("\n\n\n");
    printf("\n-----------------------------------------------------------------------------------------------------------------------");
}

//Half Load Function (Bonus)
void HalfLoad(Students *ptr,int n){
     printf("\n\t\t\t\tHalf Load Mode");
     printf("\n\t\t\t\t--------------");
    int i;
    for(i=0;i<n;i++){
        if(ptr[i].score<2)
            ptr[i].score+=0.2;
    }
    printf("\n\t\t\t\tHalf Load DONE!");
    printf("\n\n\n");
    printf("\n-----------------------------------------------------------------------------------------------------------------------");
}

int main(){
    int actual_size=0;
   int option;
   //User Interface
    printf("\t\t\t\t\t\t\tSTUDENT MANAGEMNET");
    printf("\n-----------------------------------------------------------------------------------------------------------------------");
    while(1){
     printf("\n\t\t\t\tMAIN MENU");
     printf("\n\t\t\t\t---------");
     printf("\n\t\t\t\t1. Read The File");
     printf("\n\t\t\t\t2. Show All Data");
     printf("\n\t\t\t\t3. Add Data");
     printf("\n\t\t\t\t4. Delete Data");
     printf("\n\t\t\t\t5. Search");
     printf("\n\t\t\t\t6. Statistics");
     printf("\n\t\t\t\t7. Update GPA");
     printf("\n\t\t\t\t8. Activate Half Load Mode");
     printf("\n\t\t\t\t9. Activate Normalize Mode");
     printf("\n\t\t\t\t10. Exit");
     printf("\n\n-->Enter an option: ");
     scanf("%d",&option);
     getchar();
     switch(option){
     case 1:
         Read("Std_Mang.txt",10,st,SIZE,&actual_size);
         break;
     case 2:
        Print(st,actual_size);
        break;
     case 3:
        Add(st,&actual_size);
        break;
     case 4:
        Delete(st,&actual_size);
        break;
     case 5:
        Search(st,actual_size);
        break;
     case 6:
        Statistics(st,actual_size);
        break;
     case 7:
        UpdateGPA(st,actual_size);
        break;
     case 8:
         HalfLoad(st,actual_size);
         break;
     case 9:
        Normalize(st,actual_size
                  );
         break;
     case 10:
        QuitSave("Std_Mang.txt",10,st,actual_size);
        break;
     default:
        printf("\nInvalid option!");
     }
    }
    return 0;
}
