#include<stdio.h>
#include<stdlib.h>
char s[]="|       PROCESS          |       ALLOCATION       |        MAXIMUM         |       REMAINING        |        AVAILABLE       |";
char s1[]="|   A       B       C    ";
int allocated[3][3]={0},maximum[3][3]={0},needed[3][3]={0},available[3]={0}, 
alloc[3][3]={{0,0,1},{3,2,0},{2,1,1}},
need[3][3]={{8,4,3},{6,2,0},{3,3,3}},
avail[3]={3,2,2},
safe_sequence[3];
char ret[5];
void update(){
	int i,j;
	for(i=0;i<3;i++){
		for(j=0;j<3;j++)
		maximum[i][j]=need[i][j];
	}
	for(i=0;i<3;i++){
		for(j=0;j<3;j++)
		allocated[i][j]=alloc[i][j];
	}
	for(i=0;i<3;i++)
	available[i]=avail[i];
	for(i=0;i<3;i++){
		for(j=0;j<3;j++)
		needed[i][j]=maximum[i][j]-allocated[i][j];
	}
}
char* fill_value(int i,int j){
	if(j<25){
		if(j==12)
		return "P";
		if(j==13)
		return itoa(i+1,ret,10);
		if(j==0)
		return "|";
		return " ";
	}
	if(j<50){
		j%=25;
		if(j==4)
		return itoa(allocated[i][0],ret,10);
		if(j==12)
		return itoa(allocated[i][1],ret,10);
		if(j==20)
		return itoa(allocated[i][2],ret,10);
		if(j==0)
		return "|";
		return " ";
	}
	if(j<75){
		j%=25;
		if(j==4)
		return itoa(maximum[i][0],ret,10);
		if(j==12)
		return itoa(maximum[i][1],ret,10);
		if(j==20)
		return itoa(maximum[i][2],ret,10);
		if(j==0)
		return "|";
		return " ";
	}
	if(j<100){
		j%=25;
		if(j==4)
		return itoa(needed[i][0],ret,10);
		if(j==12)
		return itoa(needed[i][1],ret,10);
		if(j==20)
		return itoa(needed[i][2],ret,10);
		if(j==0)
		return "|";
		return " ";
	}
	if(j<125){
		j%=25;
		if(i>0){
			if(j==0)
			return "|";
			return " ";
		}
		if(j==4)
		return itoa(available[0],ret,10);
		if(j==12)
		return itoa(available[1],ret,10);
		if(j==20)
		return itoa(available[2],ret,10);
		if(j==0)
		return "|";
		return " ";
	}
	return "|";
}
void print_status(){
	int i,j,k=0,check,need[3][3],avail[3],alloc[3][3];
	for(i=0;i<3;i++){
		for(j=0;j<3;j++)
		need[i][j]=needed[i][j];
	}
	for(i=0;i<3;i++){
		for(j=0;j<3;j++)
		alloc[i][j]=allocated[i][j];
	}
	for(i=0;i<3;i++)
	avail[i]=available[i];
	for(i=0;i<3;i++){
		if(need[i][0]==0&&need[i][1]==0&&need[i][2]==0){
			safe_sequence[k]=i+1;k++;
			avail[0]+=alloc[i][0];
			avail[1]+=alloc[i][1];
			avail[2]+=alloc[i][2];
		}
	}
	while(1){
		check=1;
		for(i=0;i<3;i++){
			int tt=need[i][0]+need[i][1]+need[i][2];
			if(tt>0&&need[i][0]<=avail[0]&&need[i][1]<=avail[1]&&need[i][2]<=avail[2]){
				avail[0]+=alloc[i][0];
				avail[1]+=alloc[i][1];
				avail[2]+=alloc[i][2];
				safe_sequence[k]=i+1;k++;
				check=0;
				need[i][0]=need[i][1]=need[i][2]=0;
			}
		}
		if(check)
		break;
	}
	for(i=0;i<3;i++){
		for(j=0;j<3;j++)
		if(need[i][j]>0)
		check=2;
	}
	if(check==2)
	printf("\nSYSTEM IN UNSAFE STATE\n");
	else
	printf("\nSYSTEM IN SAFE STATE\nSAFE SEQUENCE WILL BE P->%d P->%d P->%d\n",safe_sequence[0],safe_sequence[1],safe_sequence[2]);
}
void print_header(){
	int i,j;
	for(i=0;i<6;i++){
		for(j=0;j<126;j++){
			if(i==2)
			printf("%c",s[j]);
			else if(i==4&&j>24){
				if(j<125)
				printf("%c",s1[j%25]);
				else
				printf("|");
			}
			else if(j%25==0&&i>0)
			printf("|");
			else if(i%5==0)
			printf("_");
			else
			printf(" ");
		}
		printf("\n");
	}
}
void print_table(){
	int i,j;
	for(i=0;i<12;i++){
		for(j=0;j<126;j++){
			if((i-1)%4==0)
			printf("%s",fill_value(i/4,j));
			else if(j%25==0)
			printf("|");
			else if((i+1)%4==0&&i>0)
			printf("_");
			else
			printf(" ");
		}
		printf("\n");
	}
	printf("\n\n");
}
int main(){
	int i,j,choice,a,b,c,process_number,temp[3];
	printf("\n\n");
	for(i=0;i<60;i++)
	printf("*");
	printf(" PROJECT-I " );
	for(i=0;i<55;i++)
	printf("*");
	
	// uncomment following lines if you want to give your own values of resources and processes
	
	//printf("\n\n");
	//printf("ENTER AVAILABLE RESOURCES A B C IN THE SYSTEM\n");
	//scanf("%d%d%d",&available[0],&available[1],&available[2]);
	//for(i=0;i<3;i++){
	//	printf("ENTER ALLOCATED RESOURCES A B C FOR P%d\n",i+1);
	//	scanf("%d %d %d",&allocated[i][0],&allocated[i][1],&allocated[i][2]);
	//}
	//for(i=0;i<3;i++){
	//	printf("ENTER MAXIMUM NEEDED RESOURCES A B C FOR P%d\n",i+1);
	//	scanf("%d %d %d",&maximum[i][0],&maximum[i][1],&maximum[i][2]);
	//}
	
	
	update();//updating all the values of table
	printf("\n\n");
	print_header();//used to print header of table
	print_table();//print values in the table
	print_status();//printing that system in safe or unsafe state,if safe then also printing safe sequence
	printf("PLEASE CHOOSE ONE OF THE FOLLOWING OPTIONS\n");
	while(1){
		printf("1 ADD NEW REQUEST\t\t2 EXIT\n");
		scanf("%d",&choice);
		switch(choice){
			case 1:
				printf("CHOOSE ONE PROCESS\n1 P1\t2 P2\t3 P3\n");
				scanf("%d",&process_number);
				process_number--;
				if(process_number<0||process_number>2)
				printf("INVALID PROCESS CHOOSEN\n");
				else{
					printf("ENTER RESOUCES NEEDED A B C\n");
					scanf("%d %d %d",&temp[0],&temp[1],&temp[2]);
					for(i=0;i<3;i++){
						allocated[process_number][i]+=temp[i];
						available[i]-=temp[i];
						needed[process_number][i]-=temp[i];
					}
					print_header();
					print_table();
					print_status();
					update();
				}
				break;
			case 2:
				exit(0);
			default:
				printf("INVALID CHOICE\n");
		}
	}
	
}
