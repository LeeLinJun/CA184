
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#define LANE 1000
#define TBEGIN	2000
#define T 3000
#define Vmax 5
#define P 0.5


void init(int);
void move();
float calc(int);
int FindFront(int,int);
int cars[T][LANE];	

int main()
{  
    int i,j;
    float v[100];
    srand(time(NULL));
    for(i=10;i<=1000;i+=10){
    	init(i);
    	move();
    	v[i/10]=calc(i);
    }


    FILE *fp;
	if( ( fp = fopen("NSModel.m","ab") ) == NULL ){
		printf("error");
		exit(2);
	}
	else{
		fprintf(fp,"d=[ ");
		for(i=10;i<=1000;i+=10){
			fprintf(fp,"%d",i);
			fprintf(fp,",");				
		}


		fprintf(fp,"];");
		char line[] = "\r\n";
		fwrite(line, strlen(line), 1, fp);
        
        fprintf(fp,"v=[ ");
		for(i=10;i<=1000;i+=10){
			printf("quantity of vehicls:%d,average velocity：%.2f\n",i,v[i/10]);
			fprintf(fp,"%.2f",v[i/10]);
			if(i!=1000)
			    fprintf(fp,",");			
		}
		fprintf(fp,"];\nplot(d,v);");
	}

	
	fclose(fp);
    return 0;

}



void init(int n){
    int i,j,location,speed;
    for(i=0;i<T;i++)
    for(j=0;j<LANE;j++)
    cars[i][j]=-1;
    for(i=0;i<n;i++)
    {
        location=rand()%1000;
        if( cars[0][location] ==-1){
        	cars[0][location]=rand()%(Vmax+1);
        }
        else
        	i--;
    }
}



void move(){
    int i=0,j,x,v,gap;
    for(i=0;i<T-1;i++){
    	for(j=0;j<LANE;j++){
    		if( cars[i][j] >= 0 )
    		{
    			v=cars[i][j];
    			gap=FindFront(i,j);	
    			if( (v+1) <= Vmax)
    				v++;
    			if( v > gap )
    				v = gap;
    			if( v>0 && ( rand()%100 <= P*100 ) )
    				v--;


    			x=v+j;
    			x=x%1000;
    			if( cars[i+1][x] == -1 ){
    				cars[i+1][x]=v;
    			}
    			else{
    				printf("Crash at %d in %d seconds",i,j);
    				exit(1);
    			}
    		}
    	}
    }
}



int FindFront(int i,int j){
	int front=0;
	while( cars[i][(++j)%1000] == -1 ){
		front++;
	}
	return front;
}



float calc(int n){
	long s=0,i,j;
	float v=0;
	for(i=TBEGIN;i<T;i++)

		for(j=0;j<LANE;j++){
			if( cars[i][j] >= 0 ){
				s+=cars[i][j];
			}
		}
		v=(float)s/n/(T-TBEGIN);
		
		return v;

}
