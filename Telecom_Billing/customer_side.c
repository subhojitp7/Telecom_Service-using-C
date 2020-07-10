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

void searchrecords();
void payment();

int main() {
	system("cls");
	
	char choice;

	printf("\n\n\n\n\n\n\n\n\n\t\t****************************************************************");
	printf("\n\t\t-----------WELCOME TO THE TELECOM BILL PAYMENT SYSTEM-----------");
	printf("\n\t\t****************************************************************");
	Sleep(1000);
	
    system("cls");
    
    while (1) {
		system("cls");
		printf("\n\n\n\t\t Enter:");
		printf("\n\t\t S : for searching records");
		printf("\n\t\t P : payment");
		printf("\n\t\t E : for exit\n");
		choice = getche();
		choice = toupper(choice);
		switch(choice) {
			case 'S':
				searchrecords();
				break;
			case 'P':
				payment();
				break;
			case 'E':
				system("cls");
				printf("\n\n\n\n\t\t\t     THANK YOU");
				printf("\n\n\n\t\t\tFOR USING OUR SERVICE");
				Sleep(1000);
				exit(0);
				break;
			default:
				system("cls");
				printf("\n\n\n\t\t Incorrect Input");
				printf("\n\t\tAny key to continue");
				getch();
		}
	}
    
}

void searchrecords() {
	FILE *f;
	char phonenumber[20];
	int flag=1;
	f = fopen("file.ojs","rb+");
	if(f == 0)
		exit(0);
	fflush(stdin);
	system("cls");
	printf("\n\n\tEnter Phone Number to search in our database: ");
	scanf("%s", phonenumber);
	while(fread(&s,sizeof(s),1,f) == 1) {
		if(strcmp(s.phonenumber,phonenumber) == 0) {
			system("cls");
			printf("\n\n\n\t**Record Found**");
			printf("\n\n\tPhonenumber: %s\n\tName: %s\n\tAmount: Rs.%0.2f\n",s.phonenumber,s.name,s.amount);
			flag=0;
			break;
		}
		else if(flag == 1) {
			system("cls");
			printf("\n\n\n\tRequested Phone Number Not found in our database");
		}
	}
	fclose(f);
	printf("\n\n\tPress ENTER to continue.");
	getch();
}

void payment() {
	FILE *f;
	char phonenumber[20];
	long int size = sizeof(s);
	float amt;
	int i;
	if((f = fopen("file.ojs","rb+")) == NULL)
		exit(0);
	system("cls");
	printf("\n\n\tEnter phone number of the subscriber for payment: ");
	scanf("%[^\n]",phonenumber);
	fflush(stdin);
	while(fread(&s,sizeof(s),1,f) == 1) {
		if(strcmp(s.phonenumber,phonenumber) == 0) {
			system("cls");
			printf("\n\tPhone No.: %s",s.phonenumber);
			printf("\n\tName: %s",s.name);
			printf("\n\tCurrent amount: %f",s.amount);
			printf("\n");
			for(i=0;i<79;i++)
				printf("-");
			printf("\n\n\tEnter amount of payment: ");
			fflush(stdin);
			scanf(" %f",&amt);
			s.amount = s.amount - amt;
			fseek(f,-size,SEEK_CUR);
			fwrite(&s,sizeof(s),1,f);
			break;
		}
	}
	system("cls");
	printf("\n\n\n\t\tTHANK YOU %s FOR YOUR TIMELY PAYMENTS",s.name);
	Sleep(1000);
	fclose(f);
}
