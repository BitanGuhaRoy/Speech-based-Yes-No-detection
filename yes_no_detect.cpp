// yes_no_detect.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<stdio.h>
#include<stdlib.h>


int _tmain(int argc, _TCHAR* argv[])
{

	FILE *fp,*fw,*fpd,*fp1,*fpn,*fp2;
float sum=0.0;


fw=fopen("zcr.txt","w");

int num,num1,count=0,en=0,i=0,start=0,end=0,dc=0;

float *energy=(float*)malloc(sizeof(float)*10000);  //stores energy of each frame

int *zcrarray=(int*)malloc(sizeof(int)*10000); //stores zcr value of each frame

   
char file[100]="";		//Storing File name

scanf("%s",&file);  //scanning the file name

fpd=fopen(file,"r");    //scanned file is opened 
  
 if(fpd==NULL)
 {
	 printf("File Error");
 }
         // took first 100 samples to compute the DC Shift. 
 
while(fscanf(fpd,"%d",&num1)!=EOF)
{
   i++;
  
   dc+= num1;
  
   if(i==100)
   {
   	
   	dc=dc/100;
   	
   	i=0;
   	
   	break;
   	
	}
	   
	   	
}



//finding the maximum absolute value among all amplitude values.

fp1 =fopen(file,"r");

int max=-1; //Initiating max value as -1

while(fscanf(fp1,"%d",&num1)==1)
{
   if(num1<0) 
   {
   	
   	if(max<(-1*num1)){
   		
   		max=(-1*num1);   // if current amplitude is negative then here it is multiplied by (-1)
	   }
	  
}
else {
	if(max<(num1)){
   		
   		max=(num1);
	   }
}
}
fclose(fp1);

//Now we have the max value


//Data Normalisation step starts here

fpn=fopen("Normalised.txt","w"); //Normalised.txt file holds the normalised values

fp2 =fopen(file,"r");

double b1=(double)5000/max;  //computing the normalisation factor


while(fscanf(fp2,"%d",&num1)==1)
{
  
  num1= (num1-dc)*b1; //dc shift is removed and multiplied with the normalisation factor
  
  fprintf(fpn,"%d",num1); // writting the normalised value in Normalised.txt
  
  
}

fclose(fpn);
fclose(fp2);

fp =fopen("Normalised.txt","r");// Normalised.txt file is opened for further calculation 

while(fscanf(fp,"%d",&num)==1){
	
count++;   // count variable maintains number of samples counted so far

sum=sum+(num*num);

  if(count==100)    //when the count value reaches 100, now a frame is found
  {   
     
  	sum=(sum*1.0)/100; // sum value holds the STE of the frame
  
  	energy[en++]=sum;// the energy is stored in the array called energy
  	
  	sum=0;
  	
	count=0; 

  }
 
}
fclose(fp);

fp=fopen("Normalised.txt","r");
int prev=0,zcr=0,zc=0;
count=0;
while(fscanf(fp,"%d",&num)==1)
{    
         	 
    if(prev<0 && num>0 || prev>0 && num <0)  //when previous amplitude and current amplitude having different sign then we increased zcr
	 
	 zcr++;
	 
    count++;


  if(count==100)
  {      
    fprintf(fw,"%d\n",zcr);  //storing zcr value of each frame in a txt file.
    
    zcrarray[zc++]=zcr;// storing zcr values in an array for further calculations
    
  	count=0;
  	
  	 
  	 zcr=0;
          
prev=0;
  }
  if(num!=0)
  prev=num;
  
 }
 
  fclose(fp);

int k=en-1;

 for(k=en-1;k>0;k--)
{

    if(energy[k]*3<=energy[k-1] )  //when 3times energy fall is noticed then end point is marked
         {
         	
         	 end=(k);
         	 break;
		  }

}
end=k;
 k=6;
    while(k<en)
    {   
	  if((energy[k]*3)<=(energy[k+1])) //when 3 times energy increase is noticed then start point is marked 
	  { 
		  start=k+1; 
	      break;
	  }
	  k++;
	 
     }
start=k;

	
	    int length=end-start+1,avgzcr=0,zcrlast=0;
	    k=0;
	    int f=length*0.3,m=length*0.4,l=length*0.3;
	    //f value stores 30 % of length
	    // m value stores 40 % of length
	    // l value stores 30 % of length
	    for(k=0;k<f;k++)
	    {
	    	avgzcr+= zcrarray[k];
		}
	    
		avgzcr/=f;  // avg zcr is calculated for 1st f frames (1st 30% of length)
		int b;
		for(b=f+m;b<f+m+l;b++)
		{
			zcrlast+= zcrarray[b];
		}
		zcrlast/=l;    // avg zcr is calculated for last l frames (last 30% of length)

	    
	    if(zcrlast>=(1.3)*avgzcr)   // when last 30% data has at least 30% higher avg zcr than 1st 30% data then 
	                                 //we tag it  as YES else NO
		printf("YES");
	    
	    else
		 printf("NO");
	    
		
	    return 0;
}

