#include<stdio.h>
#include<conio.h>
#include<ctype.h>
#include<windows.h>
#include<stdlib.h>

struct subscriber {
	char phonenumber[20];
	char name[50];
	float amount;
}s;

void addrecords();
void listrecords();
void modifyrecords();
void deleterecords();

int main() {
	system("cls");
	
	int password;
	int phonenumber;
	char choice;

	printf("\n\n\n\n\n\n\n\n\n\t\t****************************************************************");
	printf("\n\t\t--------WELCOME TO THE TELECOM BILLING MANAGEMENT SYSTEM--------");
	printf("\n\t\t****************************************************************");
	Sleep(2000);
	
    system("cls");
    
	while (1) {
		system("cls");
		printf("\n Enter:");
		printf("\n A : for adding new records.\t L : for list of records");
		printf("\n M : for modifying records. \t S : for searching records.");
		printf("\n D : for deleting records.  \t E : for exit\n");
		choice = getche();
		choice = toupper(choice);
		switch(choice) {
			case 'A':
				addrecords();
				break;
			case 'L':
				listrecords();
				break;
			case 'M':
				modifyrecords();
				break;
			case 'S':
				searchrecords();
				break;
			case 'D':
				deleterecords();
				break;
			case 'E':
				system("cls");
				printf("\n\n\n\n\t\t\t     THANK YOU");
				printf("\n\n\n\t\t\tFOR USING OUR SERVICE");
				Sleep(1500);
				exit(0);
				break;
			default:
				system("cls");
				printf("Incorrect Input");
				printf("\nAny key to continue");
				getch();
		}
	}
}

void addrecords() {
	FILE *f;
	char test;
	f = fopen("file.ojs","ab+");
	if(f == 0) {
		f = fopen("file.ojs","wb+");
		system("cls");
		printf("\n\n\n\t\tPlease wait while we configure your computer");
		Sleep(4000);
	}
	while(1) {
		system("cls");
		printf("\n\n\tEnter phone number: ");
		scanf("%s",&s.phonenumber);
		printf("\n\n\tEnter name: ");
		fflush(stdin);
		scanf("%[^\n]",&s.name);
		printf("\n\n\tEnter amount: ");
		scanf("%f",&s.amount);
		fwrite(&s,sizeof(s),1,f);
		fflush(stdin);
		system("cls");
		printf("\n\n\t\tOne record successfully added");
		printf("\n\n\t\tPress esc key to exit, any other key to add other record:");
		test = getche();
		if(test == 27)
			break;
	}
	fclose(f);
}

void listrecords() {
	FILE *f;
	int i;
	if((f = fopen("file.ojs","rb")) == NULL)
		exit(0);
	system("cls");
	printf("Phone Number\t\tUser Name\t\t\tAmount\n");
	
	for(i=0;i<79;i++)
		printf("-");
	
	while(fread(&s,sizeof(s),1,f) == 1)
		printf("\n%-10s\t\t%-20s\t\tRs. %.2f /-",s.phonenumber,s.name,s.amount);
	
	printf("\n");
	
	for(i=0;i<79;i++)
		printf("-");

	fclose(f);
	printf("\n\nPress ENTER to continue.");
	getch();
}

void deleterecords() {
	FILE *f,*t;
	int i = 1;
	char phonenumber[20];
	if((t = fopen("temp.ojs","w+")) == NULL)
	exit(0);
	if((f = fopen("file.ojs","rb")) == NULL)
	exit(0);
	system("cls");
	printf("Enter the phone number to be deleted from the Database");
	fflush(stdin);
	scanf("%[^\n]",phonenumber);
	while(fread(&s,sizeof(s),1,f) == 1) {
		if(strcmp(s.phonenumber,phonenumber) == 0) {
			i=0;
		}
		else
			fwrite(&s,sizeof(s),1,t);
	}
	if(i == 1) {
		system("cls");
		printf("Phone number \"%s\" not found",phonenumber);
		remove("file.ojs");
		rename("temp.ojs","file.ojs");
		getch();
		fclose(f);
		fclose(t);
		main();
	}
	remove("file.ojs");
	rename("temp.ojs","file.ojs");
	system("cls");
	printf("The Number %s Successfully Deleted!!!!",phonenumber);
	fclose(f);
	fclose(t);
	printf("\n\nPress ENTER to continue.");
	getch();
}

void searchrecords() {
	FILE *f;
	char phonenumber[20];
	int flag=1;
	f=fopen("file.ojs","rb+");
	if(f==0)
		exit(0);
	fflush(stdin);
	system("cls");
	printf("\n\n\tEnter Phone Number to search in our database");
	scanf("%s", phonenumber);
	while(fread(&s,sizeof(s),1,f) == 1) {
		if(strcmp(s.phonenumber,phonenumber) == 0) {
			system("cls");
			printf(" Record Found ");
			printf("\n\nPhonenumber: %s\nName: %s\nAmount: Rs.%0.2f\n",s.phonenumber,s.name,s.amount);
			flag=0;
			break;
		}
		else if(flag == 1) {
			system("cls");
			printf("Requested Phone Number Not found in our database");
		}
	}
	fclose(f);
	printf("\n\nPress ENTER to continue.");
	getch();
}

void modifyrecords() {
	FILE *f;
	char phonenumber[20];
	long int size=sizeof(s);
	if((f=fopen("file.ojs","rb+")) == NULL)
		exit(0);
	system("cls");
	printf("Enter phone number of the subscriber to modify:");
	scanf("%[^\n]",phonenumber);
	fflush(stdin);
	while(fread(&s,sizeof(s),1,f) == 1) {
		if(strcmp(s.phonenumber,phonenumber) == 0) {
			system("cls");
			printf("\n Enter phone number:");
			scanf("%s",&s.phonenumber);
			printf("\n Enter name: ");
			fflush(stdin);
			scanf("%[^\n]",&s.name);
			printf("\n Enter amount: ");
			scanf("%f",&s.amount);
			fseek(f,-size,SEEK_CUR);
			fwrite(&s,sizeof(s),1,f);
			break;
		}
	}
	fclose(f);
}


