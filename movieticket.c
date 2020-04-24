#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
typedef struct{
	char name[50],director[50],info[100],book[6][6];
	int id;
	float price,price2;
	int d,mm,y,h,m;
}movie;
typedef struct{
	char name[50];
	movie m;
	int id;
	char seat[2];
}ticket;
void moviedisp(movie m){
	printf("------------------------------------------------------------\n");
	printf("\tShow ID             : %d\n",m.id);
	printf("\tMovie Name          : %s\n",m.name);
	printf("\tDirected by         : %s\n",m.director);
	printf("\tInformation         : %s\n",m.info);
	printf("\tDate                : %.2d/%.2d/%.4d\n",m.d,m.mm,m.y);
	printf("\tShow time           : %.2d:%.2d\n",m.h,m.m);
	printf("\tCost of regular     : %.2f\n",m.price);
	printf("\tCost of premium     : %.2f\n",m.price2);
	printf("------------------------------------------------------------\n");
}
void tktdisp(ticket t){
	printf("\t|--------------------------------------------------------|\n");
	printf("\t|                                           Ticket ID:   |\n");
	printf("\t|Customer Name : %-27s%-13d|\n",t.name,t.id);
	printf("\t|Movie Name    : %-40s|\n",t.m.name);
	printf("\t|Date          : %.2d/%.2d/%-34.2d|\n",t.m.d,t.m.mm,t.m.y);
	printf("\t|Time          : %.2d:%-37.2d|\n",t.m.h,t.m.m);
	printf("\t|Seat          : %-40s|\n",t.seat);
	printf("\t|Cost          : %-25.2fMovie Bookings |\n",t.m.price);
	printf("\t|--------------------------------------------------------|\n");
}
void seatmap(char book[6][6]){
	printf("\tAsterisk '*' indicates the seat is booked\n");
	printf("\t      A     B     C     D     E     F\n");
	printf("                     Regular                   \n");
	printf("\t1     A1%c   B1%c   C1%c   D1%c   E1%c   F1%c\n",book[0][0],book[1][0],book[2][0],book[3][0],book[4][0],book[5][0]);
	printf("\t2     A2%c   B2%c   C2%c   D2%c   E2%c   F2%c\n",book[0][1],book[1][1],book[2][1],book[3][1],book[4][1],book[5][1]);
	printf("\t3     A3%c   B3%c   C3%c   D3%c   E3%c   F3%c\n",book[0][2],book[1][2],book[2][2],book[3][2],book[4][2],book[5][2]);
	printf("\t                   Premium                   \n");
	printf("\t4     A4%c   B4%c   C4%c   D4%c   E4%c   F4%c\n",book[0][3],book[1][3],book[2][3],book[3][3],book[4][3],book[5][3]);
	printf("\t5     A5%c   B5%c   C5%c   D5%c   E5%c   F5%c\n",book[0][4],book[1][4],book[2][4],book[3][4],book[4][4],book[5][4]);
	printf("\t6     A6%c   B6%c   C6%c   D6%c   E6%c   F6%c\n",book[0][5],book[1][5],book[2][5],book[3][5],book[4][5],book[5][5]);
}
int payment(int n,float f){
	int i,j;
	char ch;
repeatpayment:
	printf("\t\tSelect payment method :\n");
	printf("\t\t1. Cash\n");
	if(n==1){
		printf("\t\t2. Debit Card\n");
		printf("\t\t3. Credit Card\n");
	}
	printf("\t\tChoice : ");
	scanf("%d",&i);
	switch(i){
		case 1:
			if(n==1){
				printf("\t\tEnter amount paid : ");
				scanf("%d",&j);
				if(j>=f){
					printf("\t\tCash retured = %.2f\n",j-f);
					return 1;
				}
				else
					printf("\t\tTransaction Failed\n");
			}
			else if(n==2){
				printf("\t\tCash returned = %.2f\n",f*60/100);
				return 1;
			}
			break;
		case 2:
			if(n==1){
				printf("\t\tCard number : 1849 8429 0184 1847\n");
				printf("\t\tEnter PIN : ");
				scanf("%d",&j);
				if(j==1234){
					printf("\t\tTransaction successful\n");
					return 1;
				}
				else
					printf("\t\tPIN invalid. Transaction failed\n");
			}
			else if(n==2)
				printf("\t\tInvalid Choice\n");
			break;
		case 3:
			if(n==1){
				printf("\t\tPress 1 to swipe your card : ");
				scanf("%d",&j);
				if(j==1){
					printf("\t\tTransaction successful\n");
					return 1;
				}
				else
					printf("\t\tDo you want to try again\n");
			}
			else if(n==2)
				printf("\t\tInvalid Choice\n");
			break;
		default:
			printf("\t\tInvalid Choice\n");
	}
	printf("\t\tDo you want to try again? (Y|N) : ");
	scanf(" %c",&ch);
	if(ch=='y'||ch=='Y')
		goto repeatpayment;
	return 0;
}
void addmovie(){
	FILE *fp;
	int i=0,j;
	movie m,m1;
	char ch;
	fp=fopen("moviedata","a+");
addmoremovies:
	printf("\tPlease enter movie ID : ");
addid:
	scanf("%d",&m.id);
	rewind(fp);
	if(getc(fp)!='\n')
		fseek(fp,-1,SEEK_CUR);
	while(fread(&m1,sizeof(m1),1,fp)){
		if(getc(fp)!='\n')
			fseek(fp,-1,SEEK_CUR);
		if(m1.id==m.id){
			printf("\tMovie ID already taken. Please enter another ID : ");
			goto addid;
		}
	}
	printf("\tPlease enter movie name : ");
	scanf(" %[^\n]s",m.name);
	rewind(fp);
	if(getc(fp)!='\n')
		fseek(fp,-1,SEEK_CUR);
	while(fread(&m1,sizeof(m1),1,fp)){
		if(getc(fp)!='\n')
			fseek(fp,-1,SEEK_CUR);
		if(strcmp(m1.name,m.name)==0){
			strcpy(m.director,m1.director);
			strcpy(m.info,m1.info);
			i=1;
		}
	}
	if(i==0){
		printf("\tPlease enter movie director's name : ");
		scanf(" %[^\n]s",m.director);
		printf("\tPlease enter movie information : ");
		scanf(" %[^\n]s",m.info);
	}
	printf("\tEnter date of show (dd mm yyyy) : ");
	scanf("%d%d%d",&m.d,&m.mm,&m.y);
	printf("\tEnter time of show (hh mm) : ");
	scanf("%d%d",&m.h,&m.m);
	printf("\tEnter cost of regular : ");
	scanf("%f",&m.price);
	printf("\tEnter cost of premium : ");
	scanf("%f",&m.price2);
	for(i=0;i<6;i++)
		for(j=0;j<6;j++)
			m.book[i][j]=' ';
	fwrite(&m,sizeof(m),1,fp);
	printf("\tDo you want to add more movies? (Y|N) : ");
	scanf(" %c",&ch);
	if(ch=='Y'||ch=='y')
		goto addmoremovies;
	printf("\tData successfully written\n");
	fclose(fp);
}
void deletemovie(){
	FILE *fp,*fp1;
	int i=0,n;
	char ch;
	movie m;
	ticket t;
deleterepeat:
	fp=fopen("moviedata","r");
	fp1=fopen("temp","w");
	printf("\tEnter ID of movie to delete : ");
	scanf("%d",&n);
	rewind(fp);
	if(getc(fp)!='\n')
		fseek(fp,-1,SEEK_CUR);
	while(fread(&m,sizeof(m),1,fp)){
		if(getc(fp)!='\n')
			fseek(fp,-1,SEEK_CUR);
		if(m.id==n){
			i=1;
			moviedisp(m);
			printf("\tAre you sure you want to delete the movie? (Y|N) : ");
			scanf(" %c",&ch);
			if(ch=='y'||ch=='Y')
				continue;
		}
		fwrite(&m,sizeof(m),1,fp1);
	}
	fclose(fp);
	fclose(fp1);
	remove("moviedata");
	rename("temp","moviedata");
	if(i==0){
		printf("\tMovie not found. Do you want to try again? (Y|N) : ");
		scanf(" %c",&ch);
		if(ch=='y'||ch=='Y')
			goto deleterepeat;
	}
	else{
		if(ch=='y'||ch=='Y'){
			fp=fopen("ticketdata","r");
			fp1=fopen("temp","w");
			if(getc(fp)!='\n')
				fseek(fp,-1,SEEK_CUR);
			while(fread(&t,sizeof(t),1,fp)){
				if(getc(fp)!='\n')
				fseek(fp,-1,SEEK_CUR);
				if(t.m.id==n)
					continue;
				else
					fwrite(&t,sizeof(t),1,fp1);
			}
			fclose(fp);
			fclose(fp1);
			remove("ticketdata");
			rename("temp","ticketdata");
			printf("\tMovie deleted successfully\n");
		}
	}
}
void allmovies(){
	FILE *fp;
	int i=0;
	movie m;
	fp=fopen("moviedata","r");
	if(getc(fp)!='\n')
		fseek(fp,-1,SEEK_CUR);
	while(fread(&m,sizeof(m),1,fp)){
		if(getc(fp)!='\n')
			fseek(fp,-1,SEEK_CUR);
		i=1;
		moviedisp(m);
	}
	fclose(fp);
	if(i==0)
		printf("No movies available in the database\n");
}
void movieiddisp(){
	FILE *fp;
	int i=0,n;
	movie m;
	char ch;
dispmovie:
	fp=fopen("moviedata","r");
	printf("\tEnter movie ID to display : ");
	scanf("%d",&n);
	if(getc(fp)!='\n')
		fseek(fp,-1,SEEK_CUR);
	while(fread(&m,sizeof(m),1,fp)){
		if(getc(fp)!='\n')
			fseek(fp,-1,SEEK_CUR);
		if(m.id==n){
			i=1;
			break;
		}
	}
	fclose(fp);
	if(i==0){
		printf("\tMovie not found. Do you want to try again? (Y|N) : ");
		scanf(" %c",&ch);
		if(ch=='y'||ch=='Y')
			goto dispmovie;
	}
	else
		moviedisp(m);
}
void updatemovie(movie m){
	FILE *fp,*fp1;
	movie m1;
	fp=fopen("moviedata","r");
	fp1=fopen("temp","w");
	if(getc(fp)!='\n')
		fseek(fp,-1,SEEK_CUR);
	while(fread(&m1,sizeof(m1),1,fp)){
		if(getc(fp)!='\n')
			fseek(fp,-1,SEEK_CUR);
		if(m.id==m1.id)
			fwrite(&m,sizeof(m),1,fp1);
		else
			fwrite(&m1,sizeof(m1),1,fp1);
	}
	fclose(fp);
	fclose(fp1);
	remove("moviedata");
	rename("temp","moviedata");
}
int bookticket(){
	FILE *fp,*fp1;
	int n=0,i,j;
	movie m;
	char ch;
	ticket t,t1;
bookmoretick:
	fp1=fopen("moviedata","a+");
	fp=fopen("ticketdata","a+");
	rewind(fp);
	if(getc(fp)!='\n')
		fseek(fp,-1,SEEK_CUR);
	while(fread(&t1,sizeof(t1),1,fp)){
		if(getc(fp)!='\n')
			fseek(fp,-1,SEEK_CUR);
		n=1;
		t.id=t1.id+1;
	}
	if(n==0)
		t.id=501;
	printf("\tTicket ID : %d\n",t.id);
	printf("\tEnter Customer Name : ");
	scanf(" %[^\n]s",t.name);
searchmovie:
	n=0;
	printf("\tEnter Movie Name : ");
	scanf(" %[^\n]s",t.m.name);
	rewind(fp1);
	if(getc(fp1)!='\n')
		fseek(fp1,-1,SEEK_CUR);
	while(fread(&m,sizeof(m),1,fp1)){
		if(getc(fp1)!='\n')
			fseek(fp1,-1,SEEK_CUR);
		if(strcmp(t.m.name,m.name)==0){
			moviedisp(m);
			n=1;
		}
	}
	if(n==0){
		printf("\tMovie name not found in database. Do you want to try again? (Y|N) : ");
		scanf(" %c",&ch);
		if(ch=='y'||ch=='Y')
			goto searchmovie;
		fclose(fp);
		fclose(fp1);
		return 0;
	}
idallot:
	n=0;
	printf("\tEnter desired movie ID : ");
	scanf("%d",&t.m.id);
	rewind(fp1);
	if(getc(fp1)!='\n')
		fseek(fp1,-1,SEEK_CUR);
	while(fread(&m,sizeof(m),1,fp1)){
		if(getc(fp1)!='\n')
			fseek(fp1,-1,SEEK_CUR);
		if(m.id==t.m.id && strcmp(m.name,t.m.name)==0){
			n=1;
			t.m=m;
			break;
		}
	}
	if(n==0){
		printf("\tMovie ID entered is invalid. Do you want to try again? (Y|N) : ");
		scanf(" %c",&ch);
		if(ch=='y'||ch=='Y')
			goto idallot;
		fclose(fp);
		fclose(fp1);
		return 0;
	}
seatselect:
	seatmap(m.book);
	n=0;
	printf("\tSelect seat : ");
	scanf(" %[^\n]s",t.seat);
	i=t.seat[0]-65;
	j=t.seat[1]-49;
	if((i>=0&&i<=5)&&(j>=0&&j<=5)&&(m.book[i][j]==' ')){
		m.book[i][j]='*';
		if(j>=3&&j<=5)
			t.m.price=t.m.price2;
	}
	else{
		printf("\tEntered seat is invalid or already taken. Do you want to try again? (Y|N) : ");
		scanf(" %c",&ch);
		if(ch=='y'||ch=='Y')
			goto seatselect;
		fclose(fp);
		fclose(fp1);
		return 0;
	}
	fseek(fp,0,SEEK_END);
	tktdisp(t);
	printf("\tTotal Cost : %.2f\n",t.m.price);
	if(payment(1,t.m.price)==1){
		fwrite(&t,sizeof(t),1,fp);
		fclose(fp);
		fclose(fp1);
		updatemovie(m);
	}
	else{
		fclose(fp);
		fclose(fp1);
	}
	printf("\tDo you want to book more tickets? (Y|N) : ");
	scanf(" %c",&ch);
	if(ch=='y'||ch=='Y')
		goto bookmoretick;
	printf("\tData has been written successfully\n");
}
void alltickets(){
	FILE *fp;
	int i=0;
	ticket t;
	fp=fopen("ticketdata","r");
	if(getc(fp)!='\n')
		fseek(fp,-1,SEEK_CUR);
	while(fread(&t,sizeof(t),1,fp)){
		if(getc(fp)!='\n')
			fseek(fp,-1,SEEK_CUR);
		tktdisp(t);
		i=1;
	}
	if(i==0)
		printf("There are no tickets in the database\n");
}
void cancelticket(){
	FILE *fp,*fp1;
	int n=0,i;
	char ch;
	ticket t;
delagain:
	fp=fopen("ticketdata","r");
	fp1=fopen("temp","w");
	printf("\tEnter ticket ID to cancel : ");
	scanf("%d",&i);
	if(getc(fp)!='\n')
		fseek(fp,-1,SEEK_CUR);
	while(fread(&t,sizeof(t),1,fp)){
		if(getc(fp)!='\n')
			fseek(fp,-1,SEEK_CUR);
		if(t.id==i){
			n=2;
			tktdisp(t);
			printf("\tAre you sure you want to  cancel the ticket? (Y|N) : ");
			scanf(" %c",&ch);
			if(ch=='y'||ch=='Y'){
				if(payment(2,t.m.price)==1){
					n=1;
					continue;
				}
			}
		}
		fwrite(&t,sizeof(t),1,fp1);
	}
	fclose(fp);
	fclose(fp1);
	remove("ticketdata");
	rename("temp","ticketdata");
	if(n==1)
		printf("\tTicket cancelled successfully\n");
	else if(n==0){
		printf("\tTicket ID not found. Do you want to try again? (Y|N) : ");
		scanf(" %c",&ch);
		if(ch=='y'||ch=='Y')
			goto delagain;
	}
}
void tktiddisp(){
	FILE *fp;
	int n=0,i;
	char ch;
	ticket t;
iddisp:
	fp=fopen("ticketdata","r");
	printf("\tEnter ticket ID : ");
	scanf("%d",&i);
	if(getc(fp)!='\n')
		fseek(fp,-1,SEEK_CUR);
	while(fread(&t,sizeof(t),1,fp)){
		if(getc(fp)!='\n')
			fseek(fp,-1,SEEK_CUR);
		if(t.id==i){
			n=1;
			break;
		}
	}
	fclose(fp);
	if(n==0){
		printf("\tTicket not found. Do you want to try again? (Y|N) : ");
		scanf(" %c",&ch);
		if(ch=='y'||ch=='Y')
			goto iddisp;
	}
	else
		tktdisp(t);
}
int ticketdata(){
	int n;
	char ch;
ticketrepeat:
	printf("1. Book a movie ticket\n");
	printf("2. Cancel a ticket\n");
	printf("3. View all tickets in the database\n");
	printf("4. View ticket by ticket number\n");
	printf("5. Go back to main menu\n");
	printf("6. Exit\n");
	printf("Choice : ");
	scanf("%d",&n);
	switch(n){
		case 1:
			bookticket();
			break;
		case 2:
			cancelticket();
			break;
		case 3:
			alltickets();
			break;
		case 4:
			tktiddisp();
			break;
		case 5:
			return 2;
		case 6:
			return 0;
		default:
			printf("Invalid Choice\n");
	}
	printf("Do you want to do more operations in ticket databse? (Y|N) : ");
	scanf(" %c",&ch);
	if(ch=='y'||ch=='Y')
		goto ticketrepeat;
	return 1;
}
int moviedata(){
	int n;
	char ch;
movierepeat:
	printf("1. Add movie to database\n");
	printf("2. Delete movie from database\n");
	printf("3. View all movies in the database\n");
	printf("4. View movie by show ID\n");
	printf("5. Go back to main menu\n");
	printf("6. Exit\n");
	printf("Choice : ");
	scanf("%d",&n);
	switch(n){
		case 1:
			addmovie();
			break;
		case 2:
			deletemovie();
			break;
		case 3:
			allmovies();
			break;
		case 4:
			movieiddisp();
			break;
		case 5:
			return 2;
		case 6:
			return 0;
		default:
			printf("Invalid Choice\n");
	}
	printf("Do you want to do more operations in movie database? (Y|N) : ");
	scanf(" %c",&ch);
	if(ch=='y'||ch=='Y')
		goto movierepeat;
	return 1;
}
int main(){
	FILE *fp;
	int n,i;
	char ch;
	fp=fopen("moviedata","a");
	fclose(fp);
	fp=fopen("ticketdata","a");
	fclose(fp);
	printf("********************Welcome to Ticket Booking********************\n");
progrepeat:
	printf("1. Modify Ticket Database\n");
	printf("2. Modify Movie Database\n");
	printf("Choice : ");
	scanf("%d",&n);
	switch(n){
		case 1:
			i=ticketdata();
			if(i==0)
				goto endprogram;
			else if(i==2)
				goto progrepeat;
			break;
		case 2:
			i=moviedata();
			if(i==0)
				goto endprogram;
			else if(i==2)
				goto progrepeat;
			break;
		default:
			printf("Invalid Choice\n");
	}
	printf("Do you want to do more operations from main menu? (Y|N) : ");
	scanf(" %c",&ch);
	if(ch=='y'||ch=='Y')
		goto progrepeat;
endprogram:
	printf("---------------By Shayaan Hussain(19K41A04E6)---------------\n");
}
