#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct{
	int accn,id;
	char name[50],type[20];
	float balance;
}acc;
acc accnum(int i,FILE *fp){
	acc n;
	while(fread(&n,sizeof(acc),1,fp)){
		if(i==n.accn)
			break;
		if(getc(fp)!='\n')
			fseek(fp,ftell(fp)-1,SEEK_SET);
	}
	if(n.accn!=i)
		n.accn=0;
	return n;
}
acc accid(int i,FILE *fp){
	acc n;
	while(fread(&n,sizeof(acc),1,fp)){
		if(i==n.id)
			break;
		if(getc(fp)!='\n')
			fseek(fp,ftell(fp)-1,SEEK_SET);
	}
	if(n.id!=i)
		n.id=0;
	return n;
}
void modify(FILE *fp,int n,acc m){
	FILE *fp1;
	acc t;
	fp1=fopen("temp","w");
	while(fread(&t,sizeof(acc),1,fp)){
		if(t.accn!=n)
			fwrite(&t,sizeof(acc),1,fp1);
		else
			fwrite(&m,sizeof(acc),1,fp1);
		if(getc(fp)!='\n')
			fseek(fp,ftell(fp)-1,SEEK_SET);
	}
	fclose(fp);
	fclose(fp1);
	remove("bankdata");
	rename("temp","bankdata");
}
void delete(FILE *fp,int n){
	FILE *fp1;
	acc t;
	fp1=fopen("temp","w");
	fp=fopen("bankdata","r");
	while(fread(&t,sizeof(acc),1,fp)){
		if(t.accn!=n)
			fwrite(&t,sizeof(acc),1,fp1);
		if(getc(fp)!='\n')
			fseek(fp,ftell(fp)-1,SEEK_SET);
	}
	fclose(fp);
	fclose(fp1);
	remove("bankdata");
	rename("temp","bankdata");
}
void display(acc n){
	printf("-----------------------------------------------------\n");
	printf("\t\tAccount Number : %d\n",n.accn);
	printf("\t\tAccount Holder's Name : %s\n",n.name);
	printf("\t\tPersonal ID : %d\n",n.id);
	printf("\t\tAccount Type : %s\n",n.type);
	printf("\t\tAccount Balance : %f\n",n.balance);
	printf("-----------------------------------------------------\n");
}
int main(){
	int accinfo,i,j;
	char ch;
	FILE *fp,*f;
	fp=fopen("bankdata","a");
	fclose(fp);
	acc m,n,o;
	printf("------------------------------Welcome To Bank------------------------------\n");
repeat:
	printf("1. Check Account Details\n");
	printf("2. Add a New Account\n");
	printf("3. Deposit or Withdraw from Account\n");
	printf("4. Delete Account\n");
	printf("5. Exit\n");
	printf("Choice : ");
	scanf("%d",&i);
	switch(i){
		case 1:
			printf("\t1. Check account details by account number\n");
			printf("\t2. Check account details by account ID\n");
			printf("\t3. Exit\n");
			printf("\tChoice : ");
			scanf("%d",&i);
			switch(i){
				case 1:
					printf("\t\tEnter account number : ");
					scanf("%d",&accinfo);
					fp=fopen("bankdata","r");
					n=accnum(accinfo,fp);
					fclose(fp);
					if(n.accn==accinfo)
						display(n);
					else
						printf("\tAccount not found\n");
					break;
				case 2:
					printf("\t\tEnter your personal account ID : ");
					scanf("%d",&accinfo);
					fp=fopen("bankdata","r");
					n=accid(accinfo,fp);
					fclose(fp);
					if(n.id==accinfo)
						display(n);
					else
						printf("\tAccount not found\n");
					break;
				case 3:
					return 0;
				default:
					printf("\t\tInvalid Choice\n");
					break;
			}
			break;
		case 2:
			for(ch='y';ch=='y'||ch=='Y';scanf(" %c",&ch)){
				//fseek(fp,0,SEEK_END);
				//j=ftell(fp);
				//fseek(fp,j-sizeof(acc),SEEK_SET);
				/*if(ftell(fp)==0)
					n.accn=10123;
				else{
					fread(&m,sizeof(acc),1,fp);
					n.accn=m.accn+1;
				}*/
				fp=fopen("bankdata","a+");
				while(fread(&m,sizeof(acc),1,fp)){
					n.accn=m.accn+1;
					if(getc(fp)!='\n')
					fseek(fp,ftell(fp)-1,SEEK_SET);
				}
				if(ftell(fp)==0)
					n.accn=10123;
				//printf("%d\n",m.accn);
				printf("\n\tAccount Number : %d\n",n.accn);
ID:
				printf("\tEnter personal account ID : ");
				scanf("%d",&n.id);
				rewind(fp);
				while(fread(&m,sizeof(acc),1,fp)){
					if(getc(fp)!='\n')
						fseek(fp,ftell(fp)-1,SEEK_SET);
					if(m.id==n.id){
						printf("\tID is already taken. Please enter another ID\n");
						goto ID;
					}
				}
deposit:
				printf("\tEnter initial deposit : ");
				scanf("%f",&n.balance);
				if(n.balance<3000){
					printf("\tMinimum deposit is 3000 rupees\n");
					goto deposit;
				}
				printf("\tEnter account holder's name : ");
				scanf(" %[^\n]s",n.name);
acctype:
				printf("\t1. Savings Account\n\t2. Current Account\n\tChoice : ");
				scanf("%d",&j);
				if(j==1)
					strcpy(n.type,"Savings Account");
				else if(j==2)
					strcpy(n.type,"Current Account");
				else{
					printf("\tInvalid choice. Please select again\n");
					goto acctype;
				}
				fseek(fp,0,SEEK_END);
				j=ftell(fp);
				fseek(fp,j-1,SEEK_SET);
				fwrite(&n,sizeof(acc),1,fp);
				fclose(fp);
				//fprintf(fp,"%d%d%s%s%f",n.accn,n.id,n.name,n.type,n.balance);
				printf("\tDo you want to add more data (y/n) : ");
			}
			printf("\tData written succesfully\n");
			break;
		case 3:
			printf("\t1. Withdrawal\n\t2. Deposit\n\t3. Exit\n\tChoice : ");
			scanf("%d",&i);
opp:
			if(i==1||i==2){
				printf("\t\tPlease open your account:\n\t\t1. Using account number\n\t\t2. Using personal ID\n\t\t3. Exit\n\t\tChoice : ");
				scanf("%d",&j);
				switch(j){
					case 1:
						printf("\t\t\tEnter your account number : ");
						scanf("%d",&accinfo);
						fp=fopen("bankdata","r");
						n=accnum(accinfo,fp);
						fclose(fp);
						if(n.accn==0)
						{
							printf("\t\t\tAccount not found. Do you want to try again (y/n) : ");
							scanf(" %c",&ch);
							if(ch=='Y'||ch=='y')
								goto opp;
							else
								goto forward;
						}
						display(n);
						break;
					case 2:
						printf("\t\t\tEnter your personal account ID : ");
						scanf("%d",&accinfo);
						fp=fopen("bankdata","r");
						n=accid(accinfo,fp);
						fclose(fp);
						if(n.id==0)
						{
							printf("\t\t\tAccount not found. Do you want to try again (y/n) : ");
							scanf(" %c",&ch);
							if(ch=='y'||ch=='Y')
								goto opp;
							else
								goto forward;
						}
						display(n);
						break;
					case 3:
						return 0;
				}
			}
			switch(i){
				case 2:
					printf("\t\tEnter amount to deposit : ");
					scanf("%d",&j);
					n.balance+=j;
					break;
				case 1: printf("\t\tEnter amount to withdraw : ");
					scanf("%d",&j);
					if(n.balance<=j)
						printf("\t\tInsufficient Balance\n");
					else
						n.balance-=j;
					break;
				case 3:
					return 0;
				default:
					printf("\t\tInvalid Choice\n");
					break;
			}
			fp=fopen("bankdata","a+");
			modify(fp,n.accn,n);
			break;
		case 4:
			printf("\tPlease enter the account number to delete : ");
			scanf("%d",&accinfo);
			fp=fopen("bankdata","r");
			while(fread(&n,sizeof(acc),1,fp)){
				if(getc(fp)!='\n')
					fseek(fp,ftell(fp)-1,SEEK_SET);
				if(n.accn==accinfo){
					break;
					j=100;
				}
			}
			fclose(fp);
			if(j=100){
				display(n);
				printf("Are you sure you want to delete the account (y/n) : ");
				scanf(" %c",&ch);
				if(ch=='y'||ch=='Y'){
					delete(fp,accinfo);
					printf("Account Deleted successfully\n");
				}
				else
					printf("Operation Cancelled\n");
			}
			else
				printf("\tAccount not found\n");
			break;
		case 5:
			return 0;
			break;
		default:
			printf("\tInvalid Choice\n");
	}
forward:
	printf("Do you want to do more operations (y/n) : ");
	scanf(" %c",&ch);
	if(ch=='y'||ch=='Y')
		goto repeat;
	printf("--------------------By Shayaan Hussain--------------------\n");
}
