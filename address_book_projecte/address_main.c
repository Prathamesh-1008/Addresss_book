/*
      Name : Prathamesh N. Patil 
      Description : AddessBook Project Using  the File I/O
*/
//--------------------------------------- *** AddessBook Project Using  the File I/O *** ---------------------------------------------------------------


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "address_Book.h"         //own header file inside prototype function and globle variable 

int main()
{
    char ch = 'y';
    int ch1;
    while((ch == 'Y') || (ch == 'y'))
    {
      system("clear");
      printf("----------Disply Details----------\n");
      printf("1. Add Details\n2. Print Data\n3. Search Data\n4. Edit Data\n5. Delete Data\n6. Exit\n");
      printf("------------------------------------------\n\nEnter your Choice : ");
      scanf("%d",&ch1);
      switch(ch1)
      {
        case 1:
          add();
          break;
        
        case 2:
          print();
          break;
        
        case 3:
          search();
          break;

        
        case 4:
          edit();
          break;

        
        case 5:
          delete();
          break;

        case 6:
          return 0; 

        default :
            printf("Invalid Choice...!\n");  
      }
      printf("\n------------------------------------------\nDo you Want continue (y/Y) : ");
      scanf(" %c",&ch);
      system("clear");
    }
}

void add()             //data add function 
{
  FILE *fptr1 = fopen("main_data.csv","r");                  //open main file in read mode 
  FILE *fptr2 = fopen("temp_data.csv","w");                  //open temp file in write mode 
  fscanf(fptr1,"%d\n", &count);                     //take count from main file 
  count++;
  fprintf(fptr2, "%d\n", count);                    //print in temp file 
  for(int i=0; i < (count-1); i++)
  {
    fscanf(fptr1,"%[^,],%[^,],%[^,],%[^\n]\n",info.name,info.mobile_no,info.gmail,info.loction);    //take data from main file print in temp file 
    fprintf(fptr2,"%s,%s,%s,%s\n",info.name,info.mobile_no,info.gmail,info.loction);
  }

  printf("------------------------------------------\n\nEnter the Name : ");            //take data from user 
  scanf(" %[^\n]",info.name);

  mo_no();

  gmail();

  printf("------------------------------------------\n\nEnter the Loction : ");
  scanf(" %[^\n]",info.loction);

  fprintf(fptr2,"%s,%s,%s,%s\n",info.name,info.mobile_no,info.gmail,info.loction);      //print in temp file 
  fclose(fptr1);
  fclose(fptr2);
  copy(fptr1,fptr2);       //call copy function this function use for temp all data copy into main file 
  system("clear");
  printf("-----------------------------------------\nData Addede Succsesfully...!\n-----------------------------------------\n");
}

void copy(FILE * fptr1,FILE * fptr2)    //copy function 
{
                                                 //copy function this function use for temp all data copy into main file 
  fptr1 = fopen("main_data.csv","w");         
  fptr2 = fopen("temp_data.csv","r");

  char ch2;
  while((ch2 =fgetc(fptr2))!= EOF)
  {
    putc(ch2,fptr1);
  }
  
  fclose(fptr1);
  fclose(fptr2);
}

void print()               //print function 
{
  FILE *fptr1=fopen("main_data.csv","r");                         // Opening the file in read mode  
	int ch;
	int (*fptr)(char *,char *);     //crete function pointer 
	fscanf(fptr1,"%d\n",&count);        //take count from main file 
	struct Address_book info[count];               //create structure array 
	if(count==0)    //count is 0 than print and stop function 
	{
    system("clear");
		printf("-------------------------\nEmpty File ... !\n-------------------------\n");
		return;
	}
	while(1)       
	{
		printf("----------------------------\nDisplay Menu : \n----------------------------\n1.A to Z\n2.Z to A\n3.Regular\n4.Exit\n----------------------------\nEnter the choice : ");
		scanf("%d",&ch);         //take choice from user  assending or disending order for printing 
    system("clear");
		if(ch==1)
		{
			fptr=ascend;          
			break;
		}
		else if(ch==2)
		{
			fptr=descend;
			break;
		}
		else if(ch==3)
			break;
		else if(ch==4)
		{
			return;
		}
		else
			printf("-------------------------\nInvalid Choice...!\n");
	}

	if(ch==1 || ch==2)
	{
		for(int j=0; j<count; j++)
			fscanf(fptr1,"%[^,],%[^,],%[^,],%[^\n]\n",info[j].name,info[j].gmail,info[j].loction,info[j].mobile_no);
	}

	if(ch==1 || ch==2)
	{
		for(int i=0;i<count-1;i++)     //apply here bubble sort technique
		{
			for(int j=0;j<count-i-1; j++)
			{
				if(fptr(info[j].name,info[j+1].name))
				{
					char temp[30];
					strcpy(temp,info[j].name);
					strcpy(info[j].name,info[j+1].name);
					strcpy(info[j+1].name,temp);
					strcpy(temp,info[j].gmail);
					strcpy(info[j].gmail,info[j+1].gmail);
					strcpy(info[j+1].gmail,temp);
					strcpy(temp,info[j].loction);
					strcpy(info[j].loction,info[j+1].loction);
					strcpy(info[j+1].loction,temp);
					strcpy(temp,info[j].mobile_no);
					strcpy(info[j].mobile_no,info[j+1].mobile_no);
					strcpy(info[j+1].mobile_no,temp);
				}
			}
		}
	}
	for(int i=0;i<count;i++)         //print the data
	{
		if(ch==3)
			fscanf(fptr1,"%[^,],%[^,],%[^,],%[^\n]\n",info[i].name,info[i].gmail,info[i].loction,info[i].mobile_no);
		printf("-----------------------------------------------\n");
    printf("\t\tCONTACT %d\n",i+1);                                          // Print All Data
    printf("-----------------------------------------------\n");
		printf("Name\t\t: %s\nEmail Address   : %s\nLocation\t: %s\nMobile No.\t: %s\n",info[i].name,info[i].gmail,info[i].loction,info[i].mobile_no);
    printf("-----------------------------------------------\n");
	}
	                                                        
	fclose(fptr1);
}

void search()                    //search function 
{
  int fg=0;
  system("clear");
  FILE * fptr = fopen("main_data.csv","r");     //open main file in read mode 
  fscanf(fptr,"%d\n",&count);
  while(1)
  {
    if(choice()==NULL)       //call choice function and return null stop function otherwise search data 
        return;
    for(int i=1; i<=count; i++)    //search data into main file 
    {
        fscanf(fptr,"%[^,],%[^,],%[^,],%[^\n]\n",info.name,info.mobile_no,info.gmail,info.loction);
        if((!strcmp((info.mobile_no),(search_by))) || (!strcmp((info.gmail),(search_by))))
        {
          fg++;
          system("clear");
          printf("------------------------------ Contact ------------------------------\n");
          printf("Name : %s\nMobile No : %s\nGmail : %s\nLocation : %s\n",info.name,info.mobile_no,info.gmail,info.loction);
          fclose(fptr); 
          return;
        }
    }
    if(!fg)
    {
      system("clear");
      printf("------------------------------------------\nData Not Found...!\n------------------------------------------\n");
      continue;
    }
    break;
  }
}

void edit()                                     //edit function  
{
  int ch,flag=0;
  system("clear");
  FILE * fptr1 = fopen("main_data.csv","r");    //open main file in read mode 
  FILE * fptr2 = fopen("temp_data.csv","w");    //open temp file in write mode 
  fscanf(fptr1,"%d\n",&count);     //take count from main file print in temp file  
  fprintf(fptr2,"%d\n",count);
  while(1)
  {
    if(choice()==NULL)         //call choice function 
        return;
    for(int i=1; i<=count; i++)    
    {
      fscanf(fptr1,"%[^,],%[^,],%[^,],%[^\n]\n",info.name,info.mobile_no,info.gmail,info.loction);
      if((!strcmp((info.mobile_no),(search_by))) || (!strcmp((info.gmail),(search_by))))         //comapre enter data and main file data than equal edit this data
      {
        flag++;
        while(1)
        {
          printf("----------Menu----------\n");
          printf("1. Name\n2. Mobile No\n3. Gmail\n4. Location\n");       //which data edit choice from user 
          printf("Enter No. of which data edite : ");
          scanf("%d",&ch);
          system("clear");
          switch(ch)
          {
            case 1:
              printf("------------------------------------------\n\nEnter the new Name : ");
              scanf(" %[^\n]",info.name);
              break;
            case 2:
              mo_no();
              break;
            case 3:
              gmail();
              break;
            case 4:
              printf("------------------------------------------\n\nEnter the new Loction : ");
              scanf(" %[^\n]",info.loction);
              break;
            default:
              printf("------------------------------------------\nInvalid input...!\n------------------------------------------\n");
              continue;
          } 
          break;
        }
      }
      fprintf(fptr2, "%s,%s,%s,%s\n",info.name,info.mobile_no,info.gmail,info.loction);
    }
    if(!flag)
    {
      system("clear");
      printf("------------------------------------------\n\t\tData Not Found\n------------------------------------------\n");
      continue;
    }
    break;
  }
  fclose(fptr1);
  fclose(fptr2);
  copy(fptr1,fptr2);    //call copy function 
  system("clear");
  printf("------------------------------------------\nData Edit Succsesfully...!\n------------------------------------------\n");
}

void delete()                             //delete funtion 
{  
  system("clear");
  FILE * fptr1 = fopen("main_data.csv","r");     //open main file in read mode 
  FILE * fptr2 = fopen("temp_data.csv","w");      //open tenp file in write mode 
  fscanf(fptr1,"%d\n",&count);     //take count from main file 
  fprintf(fptr2,"%d\n",--count);   //count decrement beacause delete data so count -1 
  int flag=0;
  while(1)
  {
    if(choice()==NULL)     //call choice function 
        return;
    for(int i=0; i<=count; i++)
    {
      fscanf(fptr1,"%[^,],%[^,],%[^,],%[^\n]\n",info.name,info.mobile_no,info.gmail,info.loction);
      if((!strcmp((info.mobile_no),(search_by))) || (!strcmp((info.gmail),(search_by))))      //compare main file data to enter data 
      {
        flag++;
        continue;
      }
      fprintf(fptr2,"%s,%s,%s,%s\n",info.name,info.mobile_no,info.gmail,info.loction);
    }
    if(flag)
      break;
    else
    {
      system("clear");
      printf("-----------------------------------------\nData Not Found...!\n-----------------------------------------\n"); 
    }
  }
  system("clear");
  printf("-----------------------------------------\nData Deleted Succsesfully...!\n-----------------------------------------\n");
  fclose(fptr1);
  fclose(fptr2);
  copy(fptr1,fptr2);   //call copy function 
        
}
  
void mo_no()                                        //mobile validation funtion 
{
  FILE *fptr1 = fopen("main_data.csv","r");
  
  char mo[14];
  while(1)
  {
    int fg=0;
    printf("------------------------------------------\n\nEnter the Mobile_no : ");
    scanf(" %[^\n]",mo);
    if(strlen(mo) != 10)
    {
      printf("-----------------------------------------\nInvalid Mobile no...!\n-----------------------------------------\n");
      continue;
    }
    int j=0;
    while(mo[j] != '\0')
    {
      if(!((mo[j] >= 48 )&& (mo[j] <= 57)))
      {
        printf("-----------------------------------------\nInvalid Mobile no...!\n-----------------------------------------\n");
        fg++;
        break;
      }
      j++;
    }
    if(fg)
    {
      continue;
    }
    fscanf(fptr1,"%d\n",&count);
    for(int i=1; i <=count; i++)
    {
      fscanf(fptr1,"%*[^,],%[^,],%*[^,],%*[^\n]\n",info.mobile_no);
      if(strcmp(info.mobile_no,mo)==0)
      {
        printf("-----------------------------------------\nMobile No. already exist...!\n-----------------------------------------\n");
        fg++;
        break;
      }
    }
    
    if(!fg)
    {
      strcpy(info.mobile_no,mo);
      fclose(fptr1);
      break;
    }
  }
}

void gmail()                                          //gmail validation funtion 
{
  FILE *fptr1= fopen("main_data.csv","r");
  char gm[25];
  char *ch="@gmail.com";
  while(1)
  {
    int f=0;
    printf("------------------------------------------\n\nEnter the Gmail : ");
    scanf(" %[^\n]",gm);
    if((!(strlen(gm) > 10)))
    {
      printf("-----------------------------------------\nInvalid Gmail...!\n-----------------------------------------\n");
      continue;
    }
    if( (strstr(gm,ch)) == NULL )
    {
      printf("-----------------------------------------\nInvalid Gmail...!\n-----------------------------------------\n");
      continue;
    }
    fscanf(fptr1,"%d\n",&count);
    for(int i=1; i<=count; i++)
    {
      fscanf(fptr1,"%*[^,],%*[^,],%[^,],%*[^\n]\n",info.gmail);
      if(!(strcmp(info.gmail,gm)))
      {
        printf("-----------------------------------------\nGmail already exist..!\n-----------------------------------------\n");
        f++;
        break;
      }
    }
    if(!f)
    {
      strcpy(info.gmail,gm);
      break;
      fclose(fptr1);
    }
  }
}

int ascend(char *a, char *b)        //assending function 
{
	return *a > *b;
}

int descend(char *a, char *b)       //desending function 
{
	return  *a < *b;
}

char * choice()
{
  int ch;
	while(1)
	{
		printf("----------------------------\nYou want to Search by :\n----------------------------\n1.Email\n2.Mobile No.\n3.Exit\n----------------------------\nEnter the Choice : ");
		scanf("%d",&ch);
		system("clear");
		if(ch==1)
		{
			printf("Enter the Email to Search : ");                   // take new email id  from user and return 
			scanf(" %[^\n]",search_by);
			return search_by;
		}
		else if(ch==2)
		{
			printf("Enter the Mobile No. to Search : ");                   // take new mobile no from user and return 
			scanf(" %[^\n]",search_by);
			system("clear");
			return search_by;
		}
		else if(ch==3)                                                       // exit from search 
			return NULL;
		else
			printf("-------------------------\nInvalid Choice...!\n");
	}
}

  