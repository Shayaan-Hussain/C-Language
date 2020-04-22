#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
typedef struct{
	char name[30],info[200];
	float price;
	int id,quantity;
}item;
void append()
{
	FILE *fp;
	item x,y;
	char ch;
	fp=fopen("items","a+");
addmore:
	printf("Enter item name\n");
	scanf(" %[^\n]s",x.name);
	printf("Enter item info\n");
	scanf(" %[^\n]s",x.info);
	printf("Enter item price (rs)\n");
	scanf("%f",&x.price);
	printf("Enter item quantity\n");
quant:
	scanf("%d",&x.quantity);
	if(x.quantity<1)
	{
		printf("Please add atleast one item\n");
		goto quant;
	}
	printf("Enter item id\n");
id:
	scanf("%d",&x.id);
	rewind(fp);
	while(fread(&y,sizeof(y),1,fp))
	{
		if(y.id==x.id)
		{
			printf("ID already in use. Please enter another ID\n");
			goto id;
		}
		if((ch=getc(fp))!='\n')
			fseek(fp,ftell(fp)-1,SEEK_SET);
	}
	fwrite(&x,sizeof(y),1,fp);
	printf("Do you want to add more items(y/n)?\n");
	scanf(" %c",&ch);
	if(ch=='Y'||ch=='y')
		goto addmore;
	else
		printf("Data successfully written\n");
	fclose(fp);
}
void itemcount()
{
	int i=0;
	item x;
	char ch;
	FILE *fp;
	fp=fopen("items","r");
	while(fread(&x,sizeof(x),1,fp))
	{
		i+=x.quantity;
		if((ch=getc(fp))!='\n')
			fseek(fp,ftell(fp)-1,SEEK_SET);
	}
	printf("There are %d items in the store\n",i);
	fclose(fp);
}
void delete()
{
	int n,i,j=0;
	FILE *fp,*fp1;
	char ch;
	item x;
	fp=fopen("items","r");
	fp1=fopen("items1","w");
	printf("Enter id number of item to delete\n");
	scanf("%d",&n);
	printf("Enter quantity to delete\n");
	scanf("%d",&i);
	while(fread(&x,sizeof(x),1,fp))
	{
		if(x.id==n)
		{
			j=1;
			if((x.quantity-i)>0)
				x.quantity=x.quantity-i;
			else if(x.quantity==i)
				continue;
			else
			{
				printf("Not enough quantity\n");
				j=2;
			}
		}
		fwrite(&x,sizeof(x),1,fp1);
		if((ch=getc(fp))!='\n')
			fseek(fp,ftell(fp)-1,SEEK_SET);
	}
	if(j==0)
		printf("Item not found\n");
	else if(j==1)
		printf("Items removed successfully\n");
	fclose(fp);
	fclose(fp1);
	remove("items");
	rename("items1","items");
}
int payment(float cost)
{
	int i,pin,j=0;
	printf("Total cost= %f\n",cost);
	printf("Select payment type\n");
	printf("1. Debit Card\n");
	printf("2. Credit Card\n");
	printf("3. Cash\n");
	printf("Select option: ");
	scanf("%d",&i);
	if(i==1)
	{
		printf("Card Number\n1234 5678 9101 2134\n");
		printf("Enter pin\n");
		scanf("%d",&pin);
		if(pin==1289)
			j=1;
	}
	else if(i==2)
	{
		printf("Press 1 to swipe card\n");
		scanf("%d",&pin);
		if(pin==1)
			j=1;
	}
	else if(i==3)
		j=1;
	if(j==0)
	{
		printf("Payment failed\n");
		return 0;
	}
	else
	{
		printf("Payment successful\n");
		return 1;
	}
}
void purchase()
{
	FILE *fp,*fp1;
	int a,b,c=0,i=0,j,nitem[10];
	char ch,items[10][30],name[30];
	item x;
	float cost,costlist[10];
buymore:
	fp=fopen("items","r");
	fp1=fopen("items1","w");
	printf("Enter item ID that you want to purchase\n");
	scanf("%d",&a);
	while(fread(&x,sizeof(x),1,fp))
	{
		if(x.id==a)
		{
			display(x);
			printf("Enter quantity that you want to purchase\n");
			scanf("%d",&b);
			strcpy(name,x.name);
			cost=x.price;
			if((x.quantity-b)>0)
			{
				c=1;
				x.quantity=x.quantity-b;
			}
			else if(x.quantity==b)
			{
				c=1;
				continue;
			}
			else
			{
				printf("Not enough quantity\n");
				c=2;
			}
		}
		fwrite(&x,sizeof(x),1,fp1);
		if((ch=getc(fp))!='\n')
			fseek(fp,ftell(fp)-1,SEEK_SET);
	}
	if(c==0)
		printf("Item not found\n");
	else if(c==1)
	{
		strcpy(items[i],name);
		costlist[i]=cost;
		nitem[i]=b;
		i++;
	}
	printf("Do you want to purchase more items (y/n)\n");
	scanf(" %c",&ch);
	fclose(fp);
	fclose(fp1);
	if(ch=='y'||ch=='Y')
		goto buymore;
	printf("------------------------------------------------------------------------\n");
	printf("Item Name\t\t\tQuantity\tItem Cost\tTotal Cost\n");
	cost=0;
	for(j=0;j<i;j++)
	{
		if(strlen(items[j])<8)
		printf("%s\t\t\t\t%d\t\t%f\t%f\n",items[j],nitem[j],costlist[j],costlist[j]*nitem[j]);
		else if(strlen(items[j])<15)
		printf("%s\t\t\t%d\t\t%f\t%f\n",items[j],nitem[j],costlist[j],costlist[j]*nitem[j]);
		else if(strlen(items[j])<24)
		printf("%s\t\t%d\t\t%f\t%f\n",items[j],nitem[j],costlist[j],costlist[j]*nitem[j]);
		else
		printf("%s\t%d\t\t%f\t%f\n",items[j],nitem[j],costlist[j],costlist[j]*nitem[j]);
		cost=cost+(costlist[j]*nitem[j]);
		
	}
	printf("------------------------------------------------------------------------\n");
	if(payment(cost)==1)
	{
		printf("Transaction successful. Thank you for shopping\n");
		remove("items");
		rename("items1","items");
	}
	else
	{
		printf("Transaction Failed. Please come again\n");
		remove("items1");
	}
}
void display(item x)
{
	printf("Item name= %s\n",x.name);
	printf("Item id= %d\n",x.id);
	printf("Item price= %f rs\n",x.price);
	printf("Item info= %s\n",x.info);
	printf("Item quantity= %d\n",x.quantity);
}
void check()
{
	int c=0,a;
	FILE *fp;
	item x;
	char ch;
	fp=fopen("items","r");
	printf("Enter item ID to check information\n");
	scanf("%d",&a);
	while(fread(&x,sizeof(x),1,fp))
	{
		if(x.id==a)
		{
			c=1;
			display(x);
			break;
		}
		if((ch=getc(fp))!='\n')
			fseek(fp,ftell(fp)-1,SEEK_SET);
	}
	if(c==0)
		printf("Item not found\n");
	fclose(fp);
}
void main()
{
	int n;
	FILE *fp;
	char ch;
	fp=fopen("items","a");
	fclose(fp);
doagain:
	printf("1. Add items to store\n");
	printf("2. Remove items from store\n");
	printf("3. Item purchase\n");
	printf("4. Check number of items in store\n");
	printf("5. Check item details\n");
	printf("Choice\n");
	scanf("%d",&n);
	switch(n)
	{
		case 1:
			append();
			break;
		case 2:
			delete();
			break;
		case 3:
			purchase();
			break;
		case 4:
			itemcount();
			break;
		case 5:
			check();
			break;
		default:
			printf("Invalid choice\n");
	}
	printf("Do you want to do anything else (y/n)?\n");
	scanf(" %c",&ch);
	if(ch=='Y'||ch=='y')
		goto doagain;
}
