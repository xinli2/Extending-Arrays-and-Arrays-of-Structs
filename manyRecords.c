#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct rec{
	int no;
	int x;
	int y;
	char c[16];
}rec; 

void printRecord(struct rec s){
	printf("[%d] %d %d %s\n",s.no,s.x,s.y,s.c);
}

int main(){
	int x,y,idx;
	char c[16];
	int num = 0;
	int len = 1;
	struct rec *s;
	s = (struct rec *)malloc(len*sizeof(struct rec));
	while(1){
		int ret = scanf("%d",&x);
		int ret2 = scanf("%d",&y);
		scanf("%16s",c); 
		// numeric input (x)
		if(ret==1){
			// non-numeric input (y)
			if(ret2==0){
				free(s);
				fprintf(stderr, "ERROR: scanf() rc=1\n");
				return 1;
			}
			// store the record
			s[num].no = num;
			s[num].x = x;
			s[num].y = y;
			strcpy(s[num].c,c);
			num += 1;
			if(len==num){
				printf("Need to extend the array; the buffer is full (with %d records)\n",num);
				printf("  Before extending the array, element 0 is: %d %d %s\n",s[0].x,s[0].y,s[0].c);
				// double the array
				len *= 2;
				int size = len*sizeof(struct rec);
				struct rec *s2 = (struct rec *)malloc(size);
				memcpy(s2, s, size/2);
				// free the old buffer
				free(s);
				s = s2;
				s2 = NULL;
				printf("  After  extending the array, element 0 is: %d %d %s\n",s[0].x,s[0].y,s[0].c);
			}
		}
		// non-numeric input (x)
		else{
			printf("scanf() returned 0, so now we'll check to see if the string is \"END\"...\n");
			// "END" found
			if(strcmp(c,"END")==0){
				printf("...\"END\" found.  Will now read the indices...\n");
				break;
			}
			// the string was not "END"
			else{	
				free(s);
				fprintf(stderr, "ERROR: the string was not \"END\".  Ending the program!\n");
				return 1;
			}
			
		}
		fflush(stdin);
	}
	fflush(stdin);
	int ret2;
	while((ret2=scanf("%d",&idx))!=EOF){
		if(ret2!=0){
			// valid index
			if(idx<num&&idx>-1){
				printRecord(s[idx]);
			}
			// invalid index
			else{
				printf("[%d] <invalid index>\n",idx);
			}
		}
		// non-numeric input
		else{
			free(s);
			fprintf(stderr, "ERROR: scanf() rc=0\n");
			return 1;
		}	
	}
	free(s);
	return 0;
}
