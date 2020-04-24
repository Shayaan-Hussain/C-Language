#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct duration
{
	int h,m;
}d;
typedef struct
{
	long int bookid;
	char name[30],airline[30],ppno[10],fltno[6],origin[30],dest[30],aircraft[20];
	float price;
	struct duration d,tod,toa;
	int dd,m,y;
}ticket;
typedef struct
{
	char fltno[6],origin[30],dest[30],airline[30],aircraft[20];
	float price;
	struct duration d,tod,toa;
}flight;
void displayflight(flight plane)
{
	printf("\t-------------------------------------------------\n");
	printf("\tAirline           :  %s\n",plane.airline);
	printf("\tOrigin            :  %s\n",plane.origin);
	printf("\tDestination       :  %s\n",plane.dest);
	printf("\tFlight Time       :  %.2d:%.2d\n",plane.d.h,plane.d.m);
	printf("\tFlight Number     :  %s\n",plane.fltno);
	printf("\tTime of Departure :  %.2d:%.2d\n",plane.tod.h,plane.tod.m);
	printf("\tTime of Arrival   :  %.2d:%.2d\n",plane.toa.h,plane.toa.m);
	printf("\tAircraft          :  %s\n",plane.aircraft);
	printf("\tTicket Cost       :  %f\n",plane.price);
	printf("\t-------------------------------------------------\n");
}
void displayticket(ticket t)
{
	printf("\t|---------------------------------------------------------|\n");
	printf("\t|Booking ID               : %-30ld|\n",t.bookid);
	printf("\t|Passenger Name           : %-30s|\n",t.name);
	printf("\t|Passport Number          : %-30s|\n",t.ppno);
	printf("\t|Airline                  : %-30s|\n",t.airline);
	printf("\t|Flight Number            : %-30s|\n",t.fltno);
	printf("\t|Origin                   : %-30s|\n",t.origin);
	printf("\t|Destination              : %-30s|\n",t.dest);
	printf("\t|Time of Departure        : %.2d:%-27.2d|\n",t.tod.h,t.tod.m);
	printf("\t|Time of Arrival          : %.2d:%-27.2d|\n",t.toa.h,t.toa.m);
	printf("\t|Flight Duration          : %.2d:%-27.2d|\n",t.d.h,t.d.m);
	printf("\t|Ticket Cost              : %-30f|\n",t.price);
	printf("\t|---------------------------------------------------------|\n");
}
int payment(float cost,int n)
{
	float f;
	int i;
	char ch;
payment:
	if(n==1)
	{
		printf("\t\tTotal amount is : %f\n",cost);
		printf("\t\t1. Credit Card\n");
		printf("\t\t2. Debit Card\n");
		printf("\t\t3. Cash Payment\n");
		printf("\t\tPlease select mode of payment : ");
	}
	else if(n==2)
	{
		printf("\t\tReturn amount is : %f\n",cost);
		printf("\t\t1. Credit Card\n");
		printf("\t\t2. Debit Card\n");
		printf("\t\t3. Cash Return\n");
		printf("\t\tPlease select mode of return : ");
	}
	scanf("%d",&i);
	if(i==1)
	{
		printf("\t\tPress Y to swipe your card : ");
		scanf(" %c",&ch);
		if(ch=='Y'||ch=='y')
			return 1;
	}
	else if(i==2)
	{
		printf("\t\tDebit Card No : 9876 5432 1098 7654\n");
		printf("\t\tPlease enter pin : ");
		scanf("%d",&i);
		if(i==5678)
			return 1;
	}
	else if(i==3)
	{
		if(n==1)
		{
			printf("\t\tEnter amount submitted : ");
			scanf("%f",&f);
			if(f<cost)
				printf("\t\tSubmitted amount is insufficient\n");
			else if(f==cost)
				return 1;
			else if(f>cost)
			{
				printf("\t\tReturned cash : %.2f\n",f-cost);
				return 1;
			}
		}
		else if(n==2)
		{
			printf("\t\tReturned amount : %f\n",cost);
			return 1;
		}
	}
	printf("\t\tDo you want to try again? (Y|N) : ");
	scanf(" %c",&ch);
	if(ch=='y'||ch=='Y')
		goto payment;
	else
		return 0;
}
void modflight(flight flt,int n)
{
	FILE *fp,*fp1;
	flight flt1;
	char ch;
	fp=fopen("flightdata","r");
	fp1=fopen("temp","w");
	if((ch=getc(fp))!='\n')
		fseek(fp,-1,SEEK_CUR);
	while(fread(&flt1,sizeof(flt1),1,fp))
	{
		if((ch=getc(fp))!='\n')
			fseek(fp,-1,SEEK_CUR);
		if(strcmp(flt1.fltno,flt.fltno)==0)
		{
			if(n==1)
				continue;
			else if(n==2)
				flt1=flt;
		}
		fwrite(&flt1,sizeof(flt1),1,fp1);
	}
	fclose(fp);
	fclose(fp1);
	remove("flightdata");
	rename("temp","flightdata");
}
void addflight()
{
	FILE *fp;
	char ch;
	flight flt,flt1;
fltaddrepeat:
	fp=fopen("flightdata","a+");
	printf("\tPlease enter airline name : ");
	scanf(" %[^\n]s",flt.airline);
	printf("\tPlease enter aircraft operating : ");
	scanf(" %[^\n]s",flt.aircraft);
	printf("\tPlease enter flight origin : ");
	scanf(" %[^\n]s",flt.origin);
	printf("\tPlease enter flight destination : ");
	scanf(" %[^\n]s",flt.dest);
	printf("\tPlease enter flight number : ");
fltnocheck:
	scanf(" %[^\n]s",flt.fltno);
	if((ch=getc(fp))!='\n')
		fseek(fp,-1,SEEK_CUR);
	while(fread(&flt1,sizeof(flt1),1,fp))
	{
		if((ch=getc(fp))!='\n')
			fseek(fp,-1,SEEK_CUR);
		if(strcmp(flt1.fltno,flt.fltno)==0)
		{
			printf("\tFlight number already in use. Please select another flight number : ");
			goto fltnocheck;
		}
	}
	printf("\tPlease enter flight duration (hh mm) : ");
	scanf("%d%d",&flt.d.h,&flt.d.m);
	printf("\tPlease enter time of departure (hh mm) : ");
	scanf("%d%d",&flt.tod.h,&flt.tod.m);
	printf("\tPlease enter time of arrival (hh mm) : ");
	scanf("%d%d",&flt.toa.h,&flt.toa.m);
	printf("\tPlease enter the flight ticket cost : ");
	scanf("%f",&flt.price);
	fwrite(&flt,sizeof(flt),1,fp);
	fclose(fp);
	printf("\tDo you want to add more flights? (Y|N) : ");
	scanf(" %c",&ch);
	if(ch=='y'||ch=='Y')
		goto fltaddrepeat;
	else
		printf("\tData has been written successfully\n");
}
flight findflight()
{
	FILE *fp;
	char str[6],ch;
	int n=0;
	flight flt;
	printf("\tEnter flight number to find : ");
	scanf(" %[^\n]s",str);
	fp=fopen("flightdata","r");
	if((ch=getc(fp))!='\n')
		fseek(fp,-1,SEEK_CUR);
	while(fread(&flt,sizeof(flt),1,fp))
	{
		if((ch=getc(fp))!='\n')
			fseek(fp,-1,SEEK_CUR);
		if(strcmp(str,flt.fltno)==0)
		{
			n=1;
			break;
		}
	}
	fclose(fp);
	if(n==0){
		printf("\tFlight not found\n");
		flt.fltno[0]=0;
	}
	return flt;
}
void editflight()
{
	FILE *fp;
	char ch,str[6];
	int n=0,i;
	flight flt;
edflight:
	fp=fopen("flightdata","r");
	printf("\tEnter flight number to edit : ");
	scanf(" %[^\n]s",str);
	if((ch=getc(fp))!='\n')
		fseek(fp,-1,SEEK_CUR);
	while(fread(&flt,sizeof(flt),1,fp))
	{
		if((ch=fgetc(fp))!='\n')
			fseek(fp,-1,SEEK_CUR);
		if(strcmp(str,flt.fltno)==0)
		{
			n=1;
			break;
		}
	}
	fclose(fp);
	if(n==0)
	{
		printf("\tFlight not found\n");
		printf("\tDo you want to try again? (Y|N) : ");
		scanf(" %c",&ch);
		if(ch=='y'||ch=='Y')
			goto edflight;
	}
	else
	{
editmore:
		printf("\tPlease select the parameter that you want to edit\n");
		printf("\t1. Edit origin\n");
		printf("\t2. Edit destination\n");
		printf("\t3. Edit flight duration\n");
		printf("\t4. Edit flight time of departure and arrival\n\tChoice : ");
		scanf("%d",&i);
		if(i==1)
		{
			printf("\tEnter new origin : ");
			scanf(" %[^\n]s",str);
			strcpy(flt.origin,str);
		}
		else if(i==2)
		{
			printf("\tEnter new destination : ");
			scanf(" %[^\n]s",str);
			strcpy(flt.dest,str);
		}
		else if(i==3)
		{
			printf("\tEnter flight duration (hh mm) : ");
			scanf("%d%d",&flt.d.h,&flt.d.m);
		}
		else if(i==4)
		{
			printf("\tEnter time of departure (hh mm) : ");
			scanf("%d%d",&flt.tod.h,&flt.tod.m);
			printf("\tEnter time of arrival (hh mm) : ");
			scanf("%d%d",&flt.toa.h,&flt.toa.m);
		}
		else
			printf("\tInvalid Choice\n");
		displayflight(flt);
		printf("\tDo you want to edit more parameters? (Y|N) : ");
		scanf(" %c",&ch);
		if(ch=='y'||ch=='Y')
			goto editmore;
		else
		{
			modflight(flt,2);
			printf("\tData has been updated successfully\n");
		}
	}
}
void modticket(ticket,int);
void removeflight()
{
	FILE *fp;
	char ch,str[6];
	int n=0,i=0;
	flight flt;
	ticket t[10],t1;
remflight:
	fp=fopen("flightdata","r");
	printf("\tEnter flight number to remove flight : ");
	scanf(" %[^\n]s",str);
	if((ch=getc(fp))!='\n')
		fseek(fp,-1,SEEK_CUR);
	while(fread(&flt,sizeof(flt),1,fp))
	{
		if((ch=getc(fp))!='\n')
			fseek(fp,-1,SEEK_CUR);
		if(strcmp(str,flt.fltno)==0)
		{
			n=1;
			break;
		}
	}
	fclose(fp);
	if(n==0)
	{
		printf("\tFlight not found\n");
		printf("\tDo you want to try again? (Y|N) : ");
		scanf(" %c",&ch);
		if(ch=='y'||ch=='Y')
			goto remflight;
	}
	else
	{
		displayflight(flt);
		printf("\tAre you sure you want to delete the flight? (Y|N) : ");
		scanf(" %c",&ch);
		if(ch=='y'||ch=='Y'){
			fp=fopen("ticketdata","r");
			if((ch=getc(fp))!='\n')
				fseek(fp,-1,SEEK_CUR);
			while(fread(&t1,sizeof(t1),1,fp))
			{
				if((ch=getc(fp))!='\n')
					fseek(fp,-1,SEEK_CUR);
				if(strcmp(t1.fltno,flt.fltno)==0){
					t[i]=t1;
					i++;
				}
			}
			fclose(fp);
			for(n=0;n<i;n++)
				modticket(t[n],1);
			modflight(flt,1);
			printf("\tFlight removed successfully\n");
		}
	}
}
void modticket(ticket t,int n)
{
	FILE *fp1,*fp;
	ticket t1;
	char ch;
	fp=fopen("ticketdata","r");
	fp1=fopen("temp","w");
	if((ch=getc(fp))!='\n')
		fseek(fp,-1,SEEK_CUR);
	while(fread(&t1,sizeof(t1),1,fp))
	{
		if((ch=getc(fp))!='\n')
			fseek(fp,-1,SEEK_CUR);
		if(strcmp(t1.fltno,t.fltno)==0)
		{
			if(n==1)
				continue;
			else if(n==2)
				fwrite(&t,sizeof(t),1,fp1);
		}
		else
			fwrite(&t1,sizeof(t1),1,fp1);
	}
	fclose(fp);
	fclose(fp1);
	remove("ticketdata");
	rename("temp","ticketdata");
}
int bookticket()
{
	FILE *fp,*fp1;
	ticket t,t1;
	int i;
	flight flt;
	char ch;
bookmore:
	i=0;
	fp=fopen("flightdata","r");
	fp1=fopen("ticketdata","a+");
	if((ch=getc(fp))!='\n')
		fseek(fp,-1,SEEK_CUR);
	while(fread(&t1,sizeof(t),1,fp1))
	{
		t.bookid=t1.bookid+1;
		if((ch=getc(fp1))!='\n')
			fseek(fp1,-1,SEEK_SET);
		i++;
	}
	if(i==0)
		t.bookid=10200;
	printf("\tBooking ID : %ld\n",t.bookid);
	printf("\tEnter passenger name : ");
	scanf(" %[^\n]s",t.name);
	printf("\tEnter passport number : ");
	scanf(" %[^\n]s",t.ppno);
	printf("\tEnter journey origin : ");
	scanf(" %[^\n]s",t.origin);
	printf("\tEnter journet destination : ");
	scanf(" %[^\n]s",t.dest);
	i=0;
	if((ch=getc(fp))!='\n')
		fseek(fp,-1,SEEK_CUR);
	while(fread(&flt,sizeof(flt),1,fp))
	{
		if((ch=getc(fp))!='\n')
			fseek(fp,-1,SEEK_CUR);
		if(strcmp(flt.origin,t.origin)==0&&strcmp(flt.dest,t.dest)==0)
		{
			displayflight(flt);
			i=1;
		}
	}
	if(i==0)
		printf("\tNo flights found on given route\n");
	else
	{
		printf("\tEnter desired flight number : ");
		scanf(" %[^\n]s",t.fltno);
		i=0;
		rewind(fp);
		if((ch=getc(fp))!='\n')
			fseek(fp,-1,SEEK_CUR);
		while(fread(&flt,sizeof(flt),1,fp))
		{
			if((ch=getc(fp))!='\n')
				fseek(fp,-1,SEEK_CUR);
			if(strcmp(t.fltno,flt.fltno)==0)
			{
				i=1;
				break;
			}
		}
		if(i==0)
			printf("\tInvalid Flight Number\n");
		else
		{
			strcpy(t.airline,flt.airline);
			strcpy(t.aircraft,flt.aircraft);
			t.price=flt.price;
			t.d.h=flt.d.h;
			t.d.m=flt.d.m;
			t.tod=flt.tod;
			t.toa=flt.toa;
			displayticket(t);
			if(payment(t.price,1))
			{
				fseek(fp,0,SEEK_END);
				fwrite(&t,sizeof(t),1,fp1);
				printf("\tBooking Successful\n");
			}
			else
				printf("\tBooking Failed\n");
		}
	}
	fclose(fp);
	fclose(fp1);
	printf("\tDo you want to book more tickets? (Y|N) : ");
	scanf(" %c",&ch);
	if(ch=='y'||ch=='Y')
		goto bookmore;
	else
		printf("Data has been written successfully\n");
}
void origindest()
{
	FILE *fp;
	flight flt;
	char str1[30],str2[30],ch;
	int n=0;
ordest:
	fp=fopen("flightdata","r");
	printf("\tEnter origin : ");
	scanf(" %[^\n]s",str1);
	printf("\tEnter destination : ");
	scanf(" %[^\n]s",str2);
	if((ch=getc(fp))!='\n')
		fseek(fp,-1,SEEK_CUR);
	while(fread(&flt,sizeof(flt),1,fp))
	{
		if((ch=getc(fp))!='\n')
			fseek(fp,-1,SEEK_CUR);
		if(strcmp(flt.origin,str1)==0&&strcmp(flt.dest,str2)==0)
		{
			displayflight(flt);
			n=1;
		}
	}
	fclose(fp);
	if(n==0)
	{
		printf("\tNo flights found with given origin and destination\n");
		printf("\tDo you want to check more flights? (Y|N) : ");
		scanf(" %c",&ch);
		if(ch=='y'||ch=='Y')
			goto ordest;
	}
}
void viewticket()
{
	FILE *fp;
	ticket t;
	long int id;
	int n=0;
	char ch;
view:
	fp=fopen("ticketdata","r");
	printf("\tEnter booking ID to view details : ");
	scanf("%ld",&id);
	if((ch=getc(fp))!='\n')
		fseek(fp,-1,SEEK_CUR);
	while(fread(&t,sizeof(t),1,fp))
	{
		if((ch=getc(fp))!='\n')
			fseek(fp,-1,SEEK_CUR);
		if(t.bookid==id)
		{
			displayticket(t);
			n=1;
		}
	}
	fclose(fp);
	if(n==0)
	{
		printf("\tTicket not found\n");
		printf("\tDo you want to try again? (Y|N) : ");
		scanf(" %c",&ch);
		if(ch=='y'||ch=='Y')
			goto view;
	}
}
void editticket()
{
	FILE *fp;
	ticket t;
	char ch,str[30];
	int n=0;
	long int id;
reedit:
	fp=fopen("ticketdata","r");
	printf("\tEnter Booking ID to edit : ");
	scanf("%ld",&id);
	if((ch=getc(fp))!='\n')
		fseek(fp,-1,SEEK_CUR);
	while(fread(&t,sizeof(t),1,fp))
	{
		if((ch=getc(fp))!='\n')
			fseek(fp,-1,SEEK_CUR);
		if(t.bookid==id)
		{
			n=1;
			break;
		}
	}
	if(n==0)
	{
		printf("\tBooking not found\n");
		printf("\tDo you want to try again? (Y|N) : ");
		scanf(" %c",&ch);
		if(ch=='y'||ch=='Y')
			goto reedit;
	}
	else
	{
tickedit:
		printf("\tPlease enter the parameter that you want to edit\n");
		printf("\t1. Edit passenger's name\n");
		printf("\t2. Edit Passport Number\n\tChoice : ");
		scanf("%d",&n);
		if(n==1)
		{
			printf("\tEnter passenger's name : ");
			scanf(" %[^\n]s",t.name);
		}
		else if(n==2)
		{
			printf("\tEnter passport number : ");
			scanf(" %[^\n]s",t.ppno);
		}
		else
			printf("Invalid Choice\n");
		displayticket(t);
		printf("\tDo you want to make any more changes? (Y|N) : ");
		scanf(" %c",&ch);
		if(ch=='y'||ch=='Y')
			goto tickedit;
		else
		{
			modticket(t,2);
			printf("\tData updated succesfully\n");
		}
	}
}
void cancelticket()
{
	FILE *fp;
	ticket t;
	long int id;
	int n=0;
	char ch;
cancel:
	fp=fopen("ticketdata","r");
	printf("\tEnter booking ID : ");
	scanf("%ld",&id);
	if((ch=getc(fp))!='\n')
		fseek(fp,-1,SEEK_CUR);
	while(fread(&t,sizeof(t),1,fp))
	{
		if((ch=getc(fp))!='\n')
			fseek(fp,-1,SEEK_CUR);
		if(t.bookid==id)
		{
			n=1;
			break;
		}
	}
	fclose(fp);
	if(n==0)
	{
		printf("\tTicket not found\n");
		printf("\tDo you want to try again? (Y|N) : ");
		scanf(" %c",&ch);
		if(ch=='y'||ch=='Y')
			goto cancel;
	}
	else
	{
		if(payment(t.price,2))
		{
			modticket(t,1);
			printf("\tTicket has been cancelled\n");
		}
		else
			printf("\tRefund failed. Ticket not cancelled\n");
	}
}
void allflights()
{
	FILE *fp;
	int n=0;
	flight flt;
	char ch;
	fp=fopen("flightdata","r");
	if((ch=getc(fp))!='\n')
		fseek(fp,-1,SEEK_CUR);
	while(fread(&flt,sizeof(flt),1,fp))
	{
		if((ch=getc(fp))!='\n')
			fseek(fp,-1,SEEK_CUR);
		displayflight(flt);
		n=1;
	}
	fclose(fp);
	if(n==0)
		printf("No flights found in database\n");
}
void viewalltkt()
{
	FILE *fp;
	int n=0;
	ticket tkt;
	char ch;
	fp=fopen("ticketdata","r");
	if((ch=getc(fp))!='\n')
		fseek(fp,-1,SEEK_CUR);
	while(fread(&tkt,sizeof(tkt),1,fp))
	{
		if((ch=getc(fp))!='\n')
			fseek(fp,-1,SEEK_CUR);
		displayticket(tkt);
		n=1;
	}
	fclose(fp);
	if(n==0)
		printf("No tickets found in database\n");
}
int ticketdata()
{
	int n;
	char ch;
ticketrestart:
	printf("\n1. Book a ticket\n");
	printf("2. View a booked ticket\n");
	printf("3. Edit a booked ticked\n");
	printf("4. Cancel a booked ticket\n");
	printf("5. View all booked tickets\n");
	printf("6. Go back to main menu\n");
	printf("7. Exit program\nChoice : ");
	scanf("%d",&n);
	if(n==1)
		bookticket();
	else if(n==2)
		viewticket();
	else if(n==3)
		editticket();
	else if(n==4)
		cancelticket();
	else if(n==5)
		viewalltkt();
	else if(n==6)
		return 2;
	else if(n==7)
		return 0;
	else
		printf("Invalid Choice\n");
	printf("Do you want to do more operations on tickets? (Y|N) : ");
	scanf(" %c",&ch);
	if(ch=='y'||ch=='Y')
		goto ticketrestart;
	else
		return 1;
}
int flightdata()
{
	char ch;
	int n;
	flight flt;
flightrepeat:
	printf("\n1. Add a flight\n");
	printf("2. Remove a flight\n");
	printf("3. Edit a flight\n");
	printf("4. Check flight by flight number\n");
	printf("5. Check flight by origin and destination\n");
	printf("6. View all registered flights\n");
	printf("7. Go back to main menu\n");
	printf("8. Exit program\nChoice : ");
	scanf("%d",&n);
	if(n==1)
		addflight();
	else if(n==2)
		removeflight();
	else if(n==3)
		editflight();
	else if(n==4)
	{
		flt=findflight();
		if(flt.fltno[0])
		displayflight(flt);
	}
	else if(n==5)
		origindest();
	else if(n==6)
		allflights();
	else if(n==7)
		return 2;
	else if(n==8)
		return 0;
	else
		printf("Invalid Choice\n");
	printf("Do you want to do more operations on flights? (Y|N) : ");
	scanf(" %c",&ch);
	if(ch=='y'||ch=='Y')
		goto flightrepeat;
	else
		return 1;
}
void main()
{
	FILE *fp;
	int n,i;
	char ch;
	fp=fopen("flightdata","a+");
	fclose(fp);
	fp=fopen("ticketdata","a+");
	fclose(fp);
	printf("*************************Welcome to Saudi Arabian Airline Databse*************************\n");
restart:
	printf("\n1. Modify Flight Database\n");
	printf("2. Book or edit a flight booking\nChoice : ");
	scanf("%d",&n);
	if(n==1)
	{
		i=flightdata();
		if(i==0)
			goto endprogram;
		else if(i==2)
			goto restart;
	}
	else if(n==2)
	{
		i=ticketdata();
		if(i==0)
			goto endprogram;
		else if(i==2)
			goto restart;
	}
	else
		printf("Invalid Choice\n");
	printf("Do you want to do more operations on flights or tickets? (Y|N) : ");
	scanf(" %c",&ch);
	if(ch=='y'||ch=='Y')
		goto restart;
endprogram:
	printf("--------------------By Shayaan Hussain-------------------\n");
}
