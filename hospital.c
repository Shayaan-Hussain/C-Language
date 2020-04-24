#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct{
	int id,age;
	char name[30],address[100],gender[6],doc[30];
	struct date{
		int d,m,y;
	}doj;
}patient;
void mod(patient p,int x){
	FILE *fp,*fp1;
	patient p1;
	char ch;
	fp=fopen("hospital","r");
	fp1=fopen("temp","w");
	while(fread(&p1,sizeof(p1),1,fp)){
		if((ch=getc(fp))!='\n')
			fseek(fp,-1,SEEK_CUR);
		if(p1.id==p.id)
		{
			if(x==1)
				continue;
			else if(x==2)
				fwrite(&p,sizeof(p),1,fp1);
		}
		else
			fwrite(&p1,sizeof(p1),1,fp1);
	}
	fclose(fp);
	fclose(fp1);
	remove("hospital");
	rename("temp","hospital");
}
void display(patient p){
	printf("--------------------------------------------------------------\n");
	printf("\tPatient ID              : %d\n",p.id);
	printf("\tPatient Name            : %s\n",p.name);
	printf("\tPatient Gender          : %s\n",p.gender);
	printf("\tPatient Address         : %s\n",p.address);
	printf("\tPatient Date of Joining : %.2d/%.2d/%.4d\n",p.doj.d,p.doj.m,p.doj.y);
	printf("\tConsulting Doctor       : %s\n",p.doc);
	printf("--------------------------------------------------------------\n");
}
int main(){
	int i,n=0;
	FILE *fp;
	char ch,str[30];
	patient p,p1;
repeat:
	fp=fopen("hospital","a");
	fclose(fp);
	printf("----------------------Welcome to Hospital Database----------------------\n");
	printf("Please select what you want to do\n");
	printf("1. Add a new Patient Record\n");
	printf("2. Delete an existing Patient Record\n");
	printf("3. Check an existing Patient Record\n");
	printf("4. Edit an existing Patient Record\n");
	printf("5. Check total number of Patient Records\n");
	printf("6. Exit\n");
	printf("Choice : ");
	scanf("%d",&i);
	switch(i)
	{
		case 1:
addrecord:
			fp=fopen("hospital","a+");
			while(fread(&p1,sizeof(p1),1,fp)){
				if((ch=getc(fp))!='\n')
					fseek(fp,-1,SEEK_CUR);
				p.id=p1.id+1;
			}
			if(ftell(fp)==0)
				p.id=1001;
			printf("\tPatient's ID                                 : %d\n",p.id);
			printf("\tEnter Patient's Name                         : ");
			scanf(" %[^\n]s",p.name);
			printf("\tSelect Patient's Gender                      :\n");
gend:
			printf("\t1. Male\n\t2. Female\n\tChoice : ");
			scanf("%d",&i);
			if(i==1)
				strcpy(p.gender,"Male");
			else if(i==2)
				strcpy(p.gender,"Female");
			else{
				printf("\tInvalid Selection. Please select again\n");
				goto gend;
			}
			printf("\tEnter Patient's Address                      : ");
			scanf(" %[^\n]s",p.address);
			printf("\tEnter Patient's Date of Joining (dd mm yyyy) : ");
			scanf("%d%d%d",&p.doj.d,&p.doj.m,&p.doj.y);
			printf("\tEnter Patient's Consulting Doctor            : ");
			scanf(" %[^\n]s",p.doc);
			fwrite(&p,sizeof(p),1,fp);
			fclose(fp);
			printf("Do you want to enter more patient records? (Y|N) : ");
			scanf(" %c",&ch);
			if(ch=='y'||ch=='Y')
				goto addrecord;
			else
				printf("Data has been written successfully\n");
			break;
		case 2:
delete:
			printf("\tPlease enter ID of patient to delete record : ");
			scanf("%d",&i);
			n=0;
			fp=fopen("hospital","r");
			while(fread(&p,sizeof(p),1,fp)){
				if((ch=getc(fp))!='\n')
					fseek(fp,-1,SEEK_CUR);
				if(p.id==i){
					n=1;
					break;
				}
			}
			fclose(fp);
			if(n==0){
				printf("\tPatient not found. Do you want to try again? (Y|N) : ");
				scanf(" %c",&ch);
				if(ch=='y'||ch=='Y')
					goto delete;
			}
			else if(n==1){
				display(p);
				printf("\tAre you sure you want to delete the data? (Y|N) : ");
				scanf(" %c",&ch);
				if(ch=='Y'||ch=='y'){
					mod(p,1);
					printf("\tData deleted successfully\n");
				}
			}
			break;
		case 3:
checkdet:
			printf("\tPlease enter ID of patient to check record : ");
			scanf("%d",&i);
			n=0;
			fp=fopen("hospital","r");
			while(fread(&p,sizeof(p),1,fp)){
				if((ch=getc(fp))!='\n')
					fseek(fp,-1,SEEK_CUR);
				if(p.id==i){
					n=1;
					break;
				}
			}
			fclose(fp);
			if(n==0){
				printf("\tPatient not found. Do you want to try again? (Y|N) : ");
				scanf(" %c",&ch);
				if(ch=='y'||ch=='Y')
					goto checkdet;
			}
			else if(n==1)
				display(p);
			break;
		case 4:
edit:
			printf("\tPlease enter ID of patient to edit details : ");
			scanf("%d",&i);
			n=0;
			fp=fopen("hospital","r");
			while(fread(&p,sizeof(p),1,fp)){
				if((ch=getc(fp))!='\n')
					fseek(fp,-1,SEEK_CUR);
				if(p.id==i){
					n=1;
					break;
				}
			}
			fclose(fp);
			if(n==0){
				printf("\tPatient not found. Do you want to try again? (Y|N) : ");
				scanf(" %c", &ch);
				if(ch=='y'||ch=='Y')
					goto edit;
			}
			else if(n==1){
				display(p);
				printf("\tPlease select what you want to edit\n");
				printf("\t1. Patient's Consulting Doctor\n");
				printf("\t2. Patient's Address\n\tChoice : ");
				scanf("%d",&n);
				if(n==1){
					printf("\tPlease enter the name of new Consulting Doctor : ");
					scanf(" %[^\n]s",str);
					strcpy(p.doc,str);
					mod(p,2);
					printf("\tData successfully updated\n");
				}
				else if(n==2){
					printf("\tPlease enter the new address : ");
					scanf(" %[^\n]s",str);
					strcpy(p.address,str);
					mod(p,2);
					printf("\tData successfully updated\n");
				}
				else
					printf("\tInvalid Choice\n");
			}
			break;
		case 5:
			n=0;
			fp=fopen("hospital","r");
			while(fread(&p,sizeof(p),1,fp)){
				if((ch=getc(fp))!='\n')
					fseek(fp,-1,SEEK_CUR);
				n++;
			}
			printf("\tThere are %d patient records in the database\n",n);
			break;
		case 6:
			ch='n';
			goto close;
		default:
			printf("\tInvalid selection\n");
	}
	printf("Do you want to do any more operations? (Y|N) : ");
	scanf(" %c",&ch);
close:
	if(ch=='y'||ch=='Y')
		goto repeat;
	else
		printf("---------------------By Shayaan Hussain---------------------\n");
}
