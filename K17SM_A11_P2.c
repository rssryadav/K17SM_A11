#include<stdio.h>
#include<stdlib.h>
char s[]="|       PROCESS          |       ALLOCATION       |        MAXIMUM         |       REMAINING        |        AVAILABLE       |";
char s1[]="|    A    B    C    D    ";
int allocated[5][4]={{0,0,1,2},{1,0,0,0},{1,3,5,4},{0,6,3,2},{0,0,1,4}},
maximum[5][4]={{0,0,1,2},{1,7,5,0},{2,3,5,6},{0,6,5,2},{0,6,5,6}},
needed[5][4]={{0,0,0,0},{0,7,5,0},{1,0,0,2},{0,0,2,0},{0,6,4,2}},
available[4]={1,5,2,0},
alloc[5][4],need[5][4],avail[4],safe_sequence[5];
char ret[5];
char* fill_value(int i,int j){//returns a string to be filled in table
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
		if(j==5)
		return itoa(allocated[i][0],ret,10);
		if(j==10)
		return itoa(allocated[i][1],ret,10);
		if(j==15)
		return itoa(allocated[i][2],ret,10);
		if(j==20)
		return itoa(allocated[i][3],ret,10);
		if(j==0)
		return "|";
		return " ";
	}
	if(j<75){
		j%=25;
		if(j==5)
		return itoa(maximum[i][0],ret,10);
		if(j==10)
		return itoa(maximum[i][1],ret,10);
		if(j==15)
		return itoa(maximum[i][2],ret,10);
		if(j==20)
		return itoa(maximum[i][3],ret,10);
		if(j==0)
		return "|";
		return " ";
	}
	if(j<100){
		j%=25;
		if(j==5)
		return itoa(needed[i][0],ret,10);
		if(j==10)
		return itoa(needed[i][1],ret,10);
		if(j==15)
		return itoa(needed[i][2],ret,10);
		if(j==20)
		return itoa(needed[i][3],ret,10);
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
		if(j==5)
		return itoa(available[0],ret,10);
		if(j==10)
		return itoa(available[1],ret,10);
		if(j==15)
		return itoa(available[2],ret,10);
		if(j==20)
		return itoa(available[3],ret,10);
		if(j==0)
		return "|";
		return " ";
	}
	return "|";
}
void print_status(){
	int i,j,k=0,check,need[5][4],avail[4],alloc[5][4];//local variables to avoid changes in original arrays
	for(i=0;i<5;i++){
		for(j=0;j<4;j++)
		need[i][j]=needed[i][j];
	}
	for(i=0;i<5;i++){
		for(j=0;j<4;j++)
		alloc[i][j]=allocated[i][j];
	}
	for(i=0;i<4;i++)
	avail[i]=available[i];
	for(i=0;i<5;i++){//initial check if any process has been allocated all resources
		if(need[i][0]==0&&need[i][1]==0&&need[i][2]==0&&need[i][3]==0){
			safe_sequence[k]=i+1;k++;
			avail[0]+=alloc[i][0];
			avail[1]+=alloc[i][1];
			avail[2]+=alloc[i][2];
			avail[3]+=alloc[i][3];
		}
	}
	while(1){
		check=1;
		for(i=0;i<5;i++){//runtime check until  processes can be allocated resources or a deadlock state
			int tt=need[i][0]+need[i][1]+need[i][2]+need[i][3];
			if(tt>0&&need[i][0]<=avail[0]&&need[i][1]<=avail[1]&&need[i][2]<=avail[2]&&need[i][3]<=avail[3]){
				avail[0]+=alloc[i][0];
				avail[1]+=alloc[i][1];
				avail[2]+=alloc[i][2];
				avail[3]+=alloc[i][3];
				safe_sequence[k]=i+1;k++;//storing the process numbers of safe sequences
				check=0;
				need[i][0]=need[i][1]=need[i][2]=need[i][3]=0;
			}
		}
		if(check)
		break;
	}
	for(i=0;i<5;i++){
		for(j=0;j<4;j++)
		if(need[i][j]>0)
		check=2;
	}
	if(check==2)
	printf("\nSYSTEM IN UNSAFE STATE\n");
	else
	printf("\nSYSTEM IN SAFE STATE\nSAFE SEQUENCE WILL BE P->%d P->%d P->%d P->%d P->%d\n",safe_sequence[0],safe_sequence[1],safe_sequence[2],safe_sequence[3],safe_sequence[4]);
}
void print_header(){//used to print first row of table
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
void print_table(){//print other rows of table and fill values in it
	int i,j;
	for(i=0;i<20;i++){
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
	printf(" PROJECT-II " );
	for(i=0;i<55;i++)
	printf("*");
	printf("\n\n");
	print_header();
	print_table();
	print_status();
	while(1){
		printf("CHOOSE ONE OF THE BELOW OPTIONS\n1 CHECK STATE FOR OTHER SYSTEM\t2 EXIT\n");
		scanf("%d",&choice);
		if(choice==2)
		exit(0);
		else if(choice!=1)
		printf("INVALID CHOICE\n");
		else{
			printf("ENTER AVAILABLE RESOURCES A B C D IN THE SYSTEM\n");
			scanf("%d %d %d %d",&available[0],&available[1],&available[2],&available[3]);
			for(i=0;i<5;i++){
				printf("ENTER ALLOCATED RESOURCES A B C D FOR P%d\n",i+1);
				scanf("%d %d %d %d",&allocated[i][0],&allocated[i][1],&allocated[i][2],&allocated[i][3]);
			}
			for(i=0;i<5;i++){
				printf("ENTER MAXIMUM NEEDED RESOURCES A B C D FOR P%d\n",i+1);
				scanf("%d %d %d %d",&maximum[i][0],&maximum[i][1],&maximum[i][2],&maximum[i][3]);
			}
			for(i=0;i<5;i++){
				for(j=0;j<4;j++)
				needed[i][j]=maximum[i][j]-allocated[i][j];
			}
			print_header();
			print_table();
			print_status();
		}
	}	
}
