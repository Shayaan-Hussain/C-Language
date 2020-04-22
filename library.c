#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct
{
	int accno,issue;
	char name[50],auth[50],user[50];
	float price;
	char info[500];
}book;
void add()
{
	book b,b1;
	char ch;
	FILE *fp;
	fp=fopen("library","a+");
	for(ch='y';ch=='y'||ch=='Y';scanf(" %c",&ch))
	{
accno:
		printf("\tEnter book accession number : ");
		scanf("%d",&b.accno);
		b.issue=0;
		rewind(fp);
		while(fread(&b1,sizeof(b1),1,fp))
		{
			if((ch=getc(fp))!='\n')
				fseek(fp,ftell(fp)-1,SEEK_SET);
			if(b1.accno==b.accno)
			{
				printf("\tAccession number is already taken\n");
				goto accno;
			}
		}
bname:
		printf("\tEnter book name : ");
		scanf(" %[^\n]s",b.name);
		rewind(fp);
		while(fread(&b1,sizeof(b1),1,fp))
		{
			if((ch=getc(fp))!='\n')
				fseek(fp,ftell(fp)-1,SEEK_SET);
			if(strcmp(b.name,b1.name)==0)
			{
				printf("\tThe book name is already registered\n");
				goto bname;
			}
		}
		printf("\tEnter book author name : ");
		scanf(" %[^\n]s",b.auth);
		printf("\tEnter book information : ");
		scanf(" %[^\n]s",b.info);
		printf("\tEnter book price : ");
		scanf("%f",&b.price);
		printf("Do you want to add boke books (y/n) : ");
		fseek(fp,0,SEEK_END);
		fwrite(&b,sizeof(b),1,fp);
	}
	printf("Data successfully written\n");
	fclose(fp);
}
void display(book b)
{
	printf("\tBook Accession Number : %d\n",b.accno);
	printf("\tBook Name : %s\n",b.name);
	printf("\tBook Author : %s\n",b.auth);
	printf("\tBook Info : %s\n",b.info);
	printf("\tBook Price : %f\n",b.price);
	//printf("%d\n",b.issue);
	if(b.issue==0)
		printf("\tBook is not issued\n");
	else
		printf("\tBook is issued by %s\n",b.user);

}
void dispacc()
{
	int n,i=0;
	char ch;
	FILE *fp;
	book b;
	fp=fopen("library","a+");
	printf("Enter accession number of book\n");
	scanf("%d",&n);
	while(fread(&b,sizeof(b),1,fp))
	{
		if((ch=getc(fp))!='\n')
			fseek(fp,ftell(fp)-1,SEEK_SET);
		if(b.accno==n)
		{
			display(b);
			i=1;
		}
	}
	if(i==0)
		printf("Book not found\n");
	fclose(fp);
}
void dispname()
{
	int i=0;
	char ch,name[50];
	FILE *fp;
	book b;
	fp=fopen("library","a+");
	printf("Enter the book name : ");
	scanf(" %[^\n]s",name);
	while(fread(&b,sizeof(b),1,fp))
	{
		if((ch=getc(fp))!='\n')
			fseek(fp,ftell(fp)-1,SEEK_SET);
		if(strcmp(b.name,name)==0)
		{
			display(b);
			i=1;
		}
	}
	if(i==0)
		printf("Book not found\n");
	fclose(fp);
}
void author()
{
	FILE *fp;
	char name[50],ch;
	book b;
	int i=0;
	printf("Enter author name : ");
	scanf(" %[^\n]s",name);
	fp=fopen("library","a+");
	while(fread(&b,sizeof(b),1,fp))
	{
		if((ch=getc(fp))!='\n')
			fseek(fp,ftell(fp)-1,SEEK_SET);
		if(strcmp(name,b.auth)==0)
		{
			printf("\n");
			display(b);
			i=1;
		}
	}
	fclose(fp);
	if(i==0)
		printf("No books found\n");
}
void count()
{
	int i=0;
	book b;
	FILE *fp;
	char ch;
	fp=fopen("library","a+");
	while(fread(&b,sizeof(b),1,fp))
	{
		if((ch=getc(fp))!='\n')
			fseek(fp,ftell(fp)-1,SEEK_SET);
		i++;
	}
	fclose(fp);
	printf("There are %d books in the library\n",i);
}
void replace(book b);
void issue()
{
	book b;
	char ch,name[50];
	int acc,i=0;
	FILE *fp;
	printf("Enter book accession number : ");
	scanf("%d",&acc);
	fp=fopen("library","a+");
	while(fread(&b,sizeof(b),1,fp))
	{
		if((ch=fgetc(fp))!='\n')
			fseek(fp,ftell(fp)-1,SEEK_SET);
		if(b.accno==acc)
		{
			i=1;
			printf("Book found\n");
			display(b);
			if(b.issue==0)
			{
				printf("Enter your name to issue book : ");
				scanf(" %[^\n]s",name);
				b.issue=1;
				strcpy(b.user,name);
				printf("Book issued successfully\n");
			}
			else
				printf("Book is already issued\n");
			break;
		}
	}
	fclose(fp);
	if(i==0)
		printf("Book not found\n");
	else
	{
		replace(b);
		//printf("Replace successful\n");
	}
}
void replace(book b)
{
	FILE *fp,*fp1;
	book b1;
	char ch;
	//printf("In replace function\n");
	fp=fopen("library","a+");
	fp1=fopen("temp","a+");
	while(fread(&b1,sizeof(b1),1,fp))
	{
		if((ch=getc(fp))!='\n')
			fseek(fp,ftell(fp)-1,SEEK_SET);
		if(strcmp(b1.name,b.name)==0)
		{
			b1.issue=b.issue;
			strcpy(b1.user,b.user);
			//printf("%d %s\n",b1.issue,b.user);
		}
		fwrite(&b1,sizeof(b1),1,fp1);
	}
	fclose(fp);
	fclose(fp1);
	remove("library");
	rename("temp","library");
}
void returnbook()
{
	FILE *fp;
	int i=0,j;
	char ch;
	book b;
	fp=fopen("library","a+");
	printf("Enter book accession number : ");
	scanf("%d",&j);
	while(fread(&b,sizeof(b),1,fp))
	{
		if((ch=getc(fp))!='\n')
			fseek(fp,ftell(fp)-1,SEEK_SET);
		if(b.accno==j)
		{
			i=1;
			if(b.issue==1)
			{
				printf("Book is returned by %s successfully\n",b.user);
				b.issue=0;
			}
			else
				printf("Book is not issued\n");
			break;
		}
	}
	fclose(fp);
	if(i==0)
		printf("Book not found\n");
	else
		replace(b);
}
int main()
{
	int n;
	FILE *fp;
	char ch;
	book b;
	fp=fopen("library","a");
	fclose(fp);
repeat:
	printf("1. Add Book Information\n");
	printf("2. Display Book Information\n");
	printf("3. List all books of given author\n");
	printf("4. List the count of books in library\n");
	printf("5. Issue a book\n");
	printf("6. Return a book\n");
	printf("7. Exit\nChoice : ");
	scanf("%d",&n);
	switch(n)
	{
		case 1:
			add();
			break;
		case 2:
			printf("1. Display by accession number\n");
			printf("2. Display by book name\nChoice : ");
			scanf("%d",&n);
			if(n==1)
				dispacc();
			else if(n==2)
				dispname();
			else
				printf("Invalid choice\n");
			break;
		case 3:
			author();
			break;
		case 4:
			count();
			break;
		case 5:
			issue();
			break;
		case 6:
			returnbook();
			break;
		case 7:
			return 0;
			break;
		default:
			printf("Invalid Choice\n");
	}
	printf("Do you want to do more operations (y/n) : ");
	scanf(" %c",&ch);
	if(ch=='y'||ch=='Y')
		goto repeat;
}
