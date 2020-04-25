#include<stdio.h>
#include<stdlib.h>
typedef struct{
	char iname[30],info[100];
	float cost;
	int id,quantity;
}item;
void display(item t){
	printf("---------------------------------------------------------------------\n");
	printf("\tItem ID            : %d\n",t.id);
	printf("\tItem name          : %s\n",t.iname);
	printf("\tItem info          : %s\n",t.info);
	printf("\tAvailable quantity : %d\n",t.quantity);
	printf("\tUnit cost of item  : %.2f\n",t.cost);
	printf("---------------------------------------------------------------------\n");
}	
void additem(){
	char ch;
	item t1,t2;
	FILE *fp;
	fp=fopen("item","a+");
addmore:
	rewind(fp);
	if(getc(fp)!='\n')
		fseek(fp,-1,SEEK_CUR);
	while(fread(&t2,sizeof(t2),1,fp)){
		t1.id=t2.id+1;
		if(getc(fp)!='\n')
			fseek(fp,-1,SEEK_CUR);
	}
	if(ftell(fp)==0)
		t1.id=1;
	printf("\tItem ID : %d\n",t1.id);
	printf("\tEnter item name : ");
	scanf(" %[^\n]s",t1.iname);
	printf("\tEnter item info : ");
	scanf(" %[^\n]s",t1.info);
quant:
	printf("\tEnter item quantity to add : ");
	scanf("%d",&t1.quantity);
	if(t1.quantity<1){
		printf("\tPlease add atleast one item\n");
		goto quant;
	}
price:
	printf("\tEnter item unit price (INR) : ");
	scanf("%f",&t1.cost);
	if(t1.cost<1){
		printf("\tAmount invalid\n");
		goto price;
	}
	fseek(fp,0,SEEK_END);
	fwrite(&t1,sizeof(t1),1,fp);
	printf("\tDo you want to add more items to the store? (Y|N) : ");
	scanf(" %c",&ch);
	if(ch=='y'||ch=='Y')
		goto addmore;
	fclose(fp);
	printf("\tData written successfully\n");
}
void remitem(){
	FILE *fp,*fp1;
	item t;
	int n,i;
	char ch;
delmore:
	fp=fopen("item","r");
	fp1=fopen("temp","w");
	printf("\tEnter item ID that you want to delete : ");
	scanf("%d",&n);
	if(getc(fp)!='\n')
		fseek(fp,-1,SEEK_CUR);
	while(fread(&t,sizeof(t),1,fp)){
		if(getc(fp)!='\n')
			fseek(fp,-1,SEEK_CUR);
		if(t.id==n){
			display(t);
			printf("\tEnter quantity to remove : ");
			scanf("%d",&i);
			if((t.quantity-i)>0){
				printf("\tEntered quantity has been removed\n");
				t.quantity-=i;
			}
			else if((t.quantity-i)==0){
				printf("\tItem has been deleted\n");
				continue;
			}
			else
				printf("\tEntered quantity is more than existing stock\n");
		}
		fwrite(&t,sizeof(t),1,fp1);
	}
	fclose(fp);
	fclose(fp1);
	remove("item");
	rename("temp","item");
	printf("\tDo you want to remove more items? (Y|N) : ");
	scanf(" %c",&ch);
	if(ch=='y'||ch=='Y')
		goto delmore;
}
void itemcount(){
	FILE *fp;
	int count=0;
	item t;
	fp=fopen("item","r");
	if(getc(fp)!='\n')
		fseek(fp,-1,SEEK_CUR);
	while(fread(&t,sizeof(t),1,fp)){
		if(getc(fp)!='\n')
			fseek(fp,-1,SEEK_CUR);
		count+=t.quantity;
	}
	fclose(fp);
	if(count==0)
		printf("There are no items in the store\n");
	else
		printf("There are %d items in the store\n",count);
}
void checkitem(){
	FILE *fp;
	int i,n;
	item t;
	char ch;
checkagain:
	i=0;
	fp=fopen("item","r");
	printf("\tEnter item ID to check info : ");
	scanf("%d",&n);
	if(getc(fp)!='\n')
		fseek(fp,-1,SEEK_CUR);
	while(fread(&t,sizeof(t),1,fp)){
		if(getc(fp)!='\n')
			fseek(fp,-1,SEEK_CUR);
		if(t.id==n){
			i=1;
			display(t);
			break;
		}
	}
	fclose(fp);
	if(i==0){
		printf("\tItem not found. Do you want to try again? (Y|N) : ");
		scanf(" %c",&ch);
		if(ch=='y'||ch=='Y')
			goto checkagain;
	}
}
void listitems(){
	FILE *fp;
	item t;
	int i=0;
	fp=fopen("item","r");
	if(getc(fp)!='\n')
		fseek(fp,-1,SEEK_CUR);
	while(fread(&t,sizeof(t),1,fp)){
		if(getc(fp)!='\n')
			fseek(fp,-1,SEEK_CUR);
		display(t);
		i=1;
	}
	fclose(fp);
	if(i==0)
		printf("There are no items in the store\n");
}
void bill(item t[10],int n,float total){
	int i;
	printf("\t|------------------------------------------------------------------------------|\n");
	printf("\t|   Item Name              |  Unit Cost       |  Quantity       |  Cost        |\n");
	printf("\t|------------------------------------------------------------------------------|\n");
	for(i=0;i<n;i++){
		printf("\t|   %-23s|  %-16.2f|  %-15.2d|  %-12.2f|\n",t[i].iname,t[i].cost,t[i].quantity,t[i].quantity*t[i].cost);
	}
	printf("\t|------------------------------------------------------------------------------|\n");
	printf("\t|  Total Number of items : %-27.2dTotal Cost : %-12.2f|\n",n,total);
	printf("\t|------------------------------------------------------------------------------|\n");
}
int payment(item t[10],int n){
	float total=0;
	int i;
	char ch;
	for(i=0;i<n;i++){
		total+=t[i].quantity*t[i].cost;
	}
	bill(t,n,total);
pay:
	printf("\t\tSelect payment method:\n");
	printf("\t\t1. Debit Card\n");
	printf("\t\t2. Credit Card\n");
	printf("\t\t3. Cash\n\t\tChoice : ");
	scanf("%d",&i);
	switch(i){
		case 1:
			printf("\t\tCard number : 1937 2749 1849 4638\n\t\tPlease enter pin : ");
			scanf("%d",&i);
			if(i==2345)
				return 1;
			break;
		case 2:
			printf("\t\tPress 1 to swipe your card : ");
			scanf("%d",&i);
			if(i==1)
				return 1;
			break;
		case 3:
			printf("\t\tPlease enter paid amount : ");
			scanf("%d",&i);
			if(i>total){
				printf("\t\tAmount returned = %.2f\n",i-total);
				return 1;
			}
			else if(i==total)
				return 1;
		default:
			printf("\t\tInvalid Choice\n");
	}
	printf("\t\tPayment failed. Do you want to try again? (Y|N) : ");
	scanf(" %c",&ch);
	if(ch=='y'||ch=='Y')
		goto pay;
	return 0;
}
void itempur(){
	FILE *fp,*fp1;
	int i=0,n,j,quant;
	char ch;
	item t,t1[10];
	fp=fopen("item","r");
	fp1=fopen("temp1","w");
	if(getc(fp)!='\n')
		fseek(fp,-1,SEEK_CUR);
	while(fread(&t,sizeof(t),1,fp)){
		if(getc(fp)!='\n')
			fseek(fp,-1,SEEK_CUR);
		fwrite(&t,sizeof(t),1,fp1);
	}
	fclose(fp1);
	fclose(fp);
purmore:
	fp=fopen("item","r");
	fp1=fopen("temp","w");
	j=0;
	printf("\tEnter item ID that you want to purchase : ");
	scanf("%d",&n);
	if(getc(fp)!='\n')
		fseek(fp,-1,SEEK_CUR);
	while(fread(&t,sizeof(t),1,fp)){
		if(getc(fp)!='\n')
			fseek(fp,-1,SEEK_CUR);
		if(t.id==n){
			j=1;
			display(t);
			printf("\tEnter required quantity : ");
			scanf("%d",&quant);
			if(quant==0)
				j=1;
			else if(quant>t.quantity)
				printf("\tEnough quantity not available\n");
			else if(quant==t.quantity){
				t1[i]=t;
				i++;
				continue;
			}
			else{
				t1[i]=t;
				t1[i].quantity=quant;
				t.quantity-=quant;
				i++;
			}
		}
		fwrite(&t,sizeof(t),1,fp1);
	}
	fclose(fp);
	fclose(fp1);
	remove("item");
	rename("temp","item");
	if(j==0)
		printf("\tItem not found\n");
	printf("\tDo you want to purchase more items? (Y|N) : ");
	scanf(" %c",&ch);
	if(ch=='y'||ch=='Y')
		goto purmore;
	else{
		if(i==0)
			printf("\tNo items purchased\n");
		else{
			if(payment(t1,i)){
				remove("temp1");
				printf("\tPurchase Successful\n");
			}
			else{
				remove("item");
				rename("temp1","item");
				printf("\tPurchase Cancelled\n");
			}
		}
	}
}
int main(){
	int n;
	FILE *fp;
	char ch;
	fp=fopen("item","a+");
	fclose(fp);
	printf("--------------------Welcome to Departmental Store--------------------\n");
progrepeat:
	printf("Please select the operation you want to do:\n");
	printf("1. Add items to store\n2. Remove items from store\n");
	printf("3. Purchase items\n4. Check number of items in the store\n");
	printf("5. Check item details\n6. List all items in the store\n7. Exit\nChoice : ");
	scanf("%d",&n);
	switch(n){
		case 1:
			additem();
			break;
		case 2:
			remitem();
			break;
		case 3:
			itempur();
			break;
		case 4:
			itemcount();
			break;
		case 5:
			checkitem();
			break;
		case 6:
			listitems();
			break;
		case 7:
			exit(0);
		default:
			printf("Invalid Choice\n");
	}
	printf("Do you want to do more operations? (Y|N) : ");
	scanf(" %c",&ch);
	if(ch=='y'||ch=='Y')
		goto progrepeat;
	printf("--------------------By Shayaan Hussain--------------------\n");
}
