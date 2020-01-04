#include <math.h>
#define MAXLEN 1000
void displayBoard(void);
int win(int p,int q,int c);	//ÅÐ¶ÏÊäÓ®£» 
void defence(void);	//ÈË»ú¶ÔÕœÊ±£¬µçÄÔÖŽ°×Æå£¬Îª±£ÊØ·œ£»
void attack(void);	//ÈË»ú¶ÔÕœÊ±£¬µçÄÔÖŽºÚÆå£¬Îªœø¹¥·œ£»
int changlianjinshou(int p, int q,int c);	//ÅÐ¶Ï³€Á¬œûÊÖ£»
int shuanghuosanjinshou(int p, int q,int c);	//ÅÐ¶ÏË«»îÈýœûÊÖ£»
int sisijinshou(int p,int q, int c);	//ÅÐ¶ÏËÄËÄœûÊÖ£»
int panduan_huosi(int p,int q,int c);	//ÅÐ¶ÏÊÇ·ñÐÎ³É»îËÄ£»
int panduan_chongsi(int p,int q,int c);	//ÅÐ¶ÏÊÇ·ñÐÎ³É³åËÄ£»
int panduan_huosan(int p,int q,int c);	//ÅÐ¶ÏÊÇ·ñÐÎ³É»îÈý£»
int panduan_huoer(int p,int q,int c);	//ÅÐ¶ÏÊÇ·ñÐÎ³É»î¶þ£»
int defence_score(int p,int q,int c);	//Œº·œŒÆËã±£ÊØµÃ·Ö£»
int attack_score(int p,int q,int c);	//»»³É¶Ô·œµÄÆå×Ó£¬ŒÆËã¶Ô·œµÄœø¹¥µÃ·Ö£»
void yiwei(int n,int *i,int *j);
 
char play1Pic[]="¡ñ";//ºÚÆå×Ó;
char play1CurrentPic[]="¡ø"; 

char play2Pic[]="¡ò";//°×Æå×Ó;
char play2CurrentPic[]="¡÷";

int aRecordBoard[SIZE][SIZE];	
int p = -1;
int q = -1;
int x_current1=0,x_current2=0,x_current3=0,y_current1=0,y_current2=0,y_current3=0;
int *x_max,*y_max;
int x_c=1,y_c=1;
int main()
{
	int a,b,k,c=0;
	initRecordBorard();
	printf("~~WangZhen~~\n");	
	printf("if you wan to quit, please put in q\n");
	printf("with another player input 1\nwith computer input 2\n");
	scanf("%d",&a);	//ŽÓŒüÅÌÉÏ¶ÁÈëÓÎÏ·Ä£ÊœÑ¡Ôñ£»
    if(a==1){	//ÈËÈË¶ÔÕœ£»
	
			printf("the player put at %d %d\n",p,q);
			if(win(p,q,1) && (changlianjinshou(p,q,1)!=1)){	//ÅÐ¶ÏÊäÓ®£»
				printf("BLACK WIN\n");
				return 0;
			}
			if(changlianjinshou(p,q,1) || sisijinshou(p,q,1) || shuanghuosanjinshou(p,q,1)){	//ÅÐ¶ÏœûÊÖ£»
				printf("WHITE WIN\n");
				return 0;
			}
			c=1;		
		}
		else if(c==1){	//c=1±íÊŸºóÊÖ£»
			n1=0,n2=0,m1=0,m2=0,m3=0;
			printf("player with white pic:\n");
			n1=getchar();	n2=getchar();	//ÓÃgetcharº¯ÊýŽÓŒüÅÌÉÏ¶ÁÈë×ø±ê£»
			if(n1=='q'){	
				return 0;
			}
			if(n2!=' '){
				p=(n1-48)*10+(n2-48);
				m1=getchar();
			}else{
				p=n1-48;
			}
			m2=getchar();	m3=getchar();
			if(m2>='A' && m2<='O'){
				q=m2-'A'+1;
			}else{
				if(m3!=10){
					q=(m2-48)*10+(m3-48);
				}else{
					q=(m2-48);
				}
			}
			if(p>SIZE || q>SIZE){
				printf("Input Wrong\n");
			}
			aRecordBoard[p][q]=2;
			recordtoDisplayArray();
			displayBoard();
			getchar();
			printf("the player put at %d %d\n",p,q); 
			if(win(p,q,2)){	//ÅÐ¶ÏÊäÓ®£»
				printf("WHITE WIN\n");
			}
			c=0;
		}
	}
    }
    else if(a==2){	//ÈË»ú¶ÔÕœ
	int d;	//ÍæŒÒÑ¡ÔñÏÈÊÖorºóÊÖ£»
	printf("play with black pic input 1\nplay with white pic input 2\n");
	scanf("%d",&d);
	if(d==1){	//ÍæŒÒÏÈÊÖ£¬ÖŽºÚÆå£»
	    for(k=0;k<MAXLEN;k++){
		int n1=0,n2=0,m1=0,m2=0,m3=0;
	    	if(c==0){	//ÍæŒÒÏÂÆå£»
			printf("player:\n");
			if((n1=getchar())==10){	//ÓÃgetcharº¯ÊýŽÓŒüÅÌÉÏ¶ÁÈë×ø±ê£»	
				n1=getchar();	n2=getchar();
			}else{
				n2=getchar();
			}
			if(n1=='q'){
				return 0;
			}
			if(n2!=' '){
				p=(n1-48)*10+(n2-48);
				m1=getchar();
			}else{
				p=n1-48;
			}
			m2=getchar();	m3=getchar();
			if(m2>='A' && m2<='O'){
				q=m2-'A'+1;
			}else{
				if(m3!=10){
					q=(m2-48)*10+(m3-48);
				}else{
					q=(m2-48);
				}
			}
			if(p>SIZE || q>SIZE){
				printf("Input Wrong\n");
			}
			aRecordBoard[p][q]=1;
			recordtoDisplayArray();
			displayBoard();
			getchar();
			printf("the player put at %d %d\n",p,q);
			if(win(p,q,1) && (changlianjinshou(p,q,1)!=1)){	//ÅÐ¶ÏÊäÓ®£»
				printf("Player WIN\n");
				return 0;
			}
			if(changlianjinshou(p,q,1) || sisijinshou(p,q,1) || shuanghuosanjinshou(p,q,1) ){	//ÅÐ¶ÏœûÊÖ£»
				printf("Computer Win\n");
				return 0;
			}
			c=1;
	    	}
	    	else if(c==1){	//µçÄÔÏÂÆå£»
			printf("Computer:\n");
			defence();
			p=*x_max;	q=*y_max;
			aRecordBoard[p][q]=2;
			recordtoDisplayArray();
			displayBoard();
			getchar();
			printf("the computer put at %d %d\n",p,q); 
			if(win(p,q,2)){
				printf("Computer WIN\n");
				return 0;
			}
			c=0;
	    	}
	    }
	}
	else if(d==2){	//ÍæŒÒºóÊÖ£¬ÖŽ°×Æå£»
	    aRecordBoard[8][8]=1;	//ÔÚÖÐÐÄŽŠÏÂ×Ó£»
	    recordtoDisplayArray();
	    displayBoard();
	    printf("the computer put at 8 8\n");
	    for(k=0;k<MAXLEN;k++){
		int n1=0,n2=0,m1=0,m2=0,m3=0;
		if(c==0){	//ÍæŒÒÏÂÆå£»
			printf("Player:\n");
			if((n1=getchar())==10){			
				n1=getchar();	n2=getchar();
			}else{
				n2=getchar();
			}
			if(n1=='q'){
				return 0;
			}
			if(n2!=' '){
				p=(n1-48)*10+(n2-48);
				m1=getchar();
			}else{
				p=n1-48;
			}
			m2=getchar();	m3=getchar();
			if(m2>='A' && m2<='O'){
				q=m2-'A'+1;
			}else{
				if(m3!=10){
					q=(m2-48)*10+(m3-48);
				}else{
					q=(m2-48);
				}
			}
			if(p>SIZE || q>SIZE){
				printf("Input Wrong\n");
			}
			aRecordBoard[p][q]=2;
			recordtoDisplayArray();
			displayBoard();
			getchar();
			printf("the player put at %d %d\n",p,q);
			if(win(p,q,2)){
				printf("player WIN\n");
				return 0;
			}
		c=1;
		}
		if(c==1){	//µçÄÔÏÂÆå£»
			attack();
			p=*x_max;	q=*y_max;
			aRecordBoard[p][q]=1;
			recordtoDisplayArray();
			displayBoard();
			getchar();
			printf("the computer put at %d %d\n",p,q);
			if(win(p,q,1)){
				printf("Computer WIN\n");
				return 0;
			}
			c=0;
		}
	    }  
	}
    }	
}

int win(int a,int b,int c)	//ÅÐ¶ÏÊäÓ®£»
{ 
	int n=1,m,P,Q;
	P=a; Q=b; 
	while(n!=5){ 
		m=0; 
		while(aRecordBoard[a][b]==c){ 
			m++; 
			if(m==5){
				return 1;
			} 
			yiwei(n,&a,&b); 
			if(a<1||a>15||b<1||b>15){
				break;
			}
		} 
		n+=4; m-=1; a=P; b=Q;
		while(aRecordBoard[a][b]==c){ 
			m++; 
			if(m==5){
				return 1;
			} 
			yiwei(n,&a,&b);
			if(a<1||a>15||b<1||b>15){
				break;
			} 
		} 
		n-=3; a=P; b=Q;
	} 
	return 0;
}
void yiwei(int n,int *i,int *j)	//ÒÔ£ši,j£©ÎªÖÐÐÄ£¬ÈÆÉÏÏÂ¡¢×óÓÒ¡¢×óÐ±¡¢ÓÒÐ±ËÄžö·œÏòÉšÃè£»
{ 
	switch(n){ 
	case 1: *i+=1; break;
	case 2: *i+=1; *j+=1; break;
	case 3: *j+=1; break; 
	case 4: *i-=1; *j+=1; break;
	case 5: *i-=1; break;
	case 6: *i-=1; *j-=1; break; 
	case 7: *j-=1; break; 
	case 8: *i+=1; *j-=1; break;
	}
}
int changlianjinshou(int a, int b,int c)	//ÅÐ¶Ï³€Á¬œûÊÖ£¬ÒÔ£ši£¬j£©ÎªÖÐÐÄµÄËÄžö·œÏòÁ¬Ðø³¬¹ý5žöŒŽÎª³€Á¬£»
{
	int n=1,m,P,Q;
	int jifang=0, duifang=0;
	P=a; Q=b; 
	if(c==1){
		jifang=1;	duifang=2;
	}else if(c==2){
		jifang=2;	duifang=1;
	}
	while(n!=5){ 
		m=0; 
		while(aRecordBoard[a][b]==jifang){ 
			m++; 
			if(m>5){
				return 1;
			} 
			yiwei(n,&a,&b); 
			if(a<1||a>15||b<1||b>15){
				break;
			}
		} 
		n+=4; m-=1; a=P; b=Q;
		while(aRecordBoard[a][b]==jifang){ 
			m++; 
			if(m>5){
				return 1;
			} 
			yiwei(n,&a,&b);
			if(a<1||a>15||b<1||b>15){
				break;
			} 
		} 
		n-=3; a=P; b=Q;
	} 
	return 0;
}
int shuanghuosanjinshou(int a, int b,int c)	//ÅÐ¶ÏË«»îÈýœûÊÖ£¬ÔÚËÄžö·œÏòÖÐµÄÁœžöÓÐ»îÈý£¬ŒŽÎªË«»îÈý£»
{											//a£¬bÎª×ø±ê£¬cŽú±íÆå×ÓµÄÀàÐÍ£¬c=1ÎªºÚ×Ó£¬c=0Îª°××Ó£»
	int n=1,m,P,Q,huosan=0,liangduan1,liangduan2,temp,kong;	//liangduan1£¬liangduan2ÓÃÀŽÅÐ¶ÏÊÇ»îÈý»¹ÊÇ³åÈý£»
	int jifang=0, duifang=0;	
	P=a; Q=b; 
	if(c==1){
		jifang=1;	duifang=2;
	}else if(c==2){
		jifang=2;	duifang=1;
	}
	while(n!=5){ 
		m=0; liangduan1=-1;	liangduan2=-1;	temp=0;	kong=0;
		while(aRecordBoard[a][b]==jifang && temp<=3){ //tempÓÃÀŽŒÇÂŒÏòÃ¿žö·œÏòÒÑŸ­ÅÐ¶ÏÁË¶àÉÙ²œ£»
			m++; 
			yiwei(n,&a,&b);	temp+=1;
			if(a<1||a>15||b<1||b>15){
				liangduan1=1;
				break;
			}
			if(aRecordBoard[a][b]==0){
				yiwei(n,&a,&b);	temp+=1;
				if(aRecordBoard[a][b]==jifang){
					kong+=1;					
					continue;	//³öÏÖÃ»ÓÐ×ÓµÄÇé¿ö£¬ÔÙÍùºó¿ŽÒ»ÏÂºóÃæµÄÆåÐÎ£»
				}
				liangduan1=0;
				break;
			}
		} 
		n+=4; m-=1; a=P; b=Q;	temp=0;
		while(aRecordBoard[a][b]==jifang && temp<=3){ 
			m++;  
			yiwei(n,&a,&b);	temp+=1;
			if(a<1||a>15||b<1||b>15){
				liangduan2=1;
				break;
			}
			if(aRecordBoard[a][b]==0){
				yiwei(n,&a,&b);	temp+=1;
				if(aRecordBoard[a][b]==jifang){
					kong+=1;
					continue;
				}
				liangduan2=0;
				break;
			}
		}
		if(m==3 && liangduan1==0 && liangduan2==0 && kong<2){	//Áœ¶ËÎª¿Õ£¬²¢ÇÒÖÐŒä×î¶àÓÐÒ»žö¿Õ°×Î»ÖÃ£¬ÔòÎª»îÈý£»
			huosan+=1;
			if(huosan==2){
				return 1;
			}
		} 
		n-=3; a=P; b=Q;
	} 
	return 0;
}
int sisijinshou(int a, int b,int c)	//ÅÐ¶ÏËÄËÄœûÊÖ£»
{
	int i,j,n=1,m,P,Q,huosi=0,chongsi=0,liangduan1,liangduan2;
	int jifang=0,duifang=0;
	int K[SIZE],L[SIZE];	//ÓÃÀŽŒÇÂŒ¿Õ°×Î»ÖÃŸàÀëÖÐÐÄÆå×ÓµÄŸàÀë£»
	float temp;
	P=a; Q=b;
	if(c==1){
		jifang=1;	duifang=2;
	}else if(c==2){
		jifang=2;	duifang=1;
	}
	while(n!=5){
		for(i=0,j=0;i<SIZE,j<SIZE;i++,j++){
			K[i]=0;	L[j]=0;
		}
		m=0; liangduan1=-1;	liangduan2=-1;	temp=0.0;
		while(aRecordBoard[a][b]==jifang && temp<4.0){ //tempÓÃÀŽŒÇÂŒÏòÃ¿žö·œÏòÒÑŸ­ÅÐ¶ÏÁË¶àÉÙ²œ£¬³öÏÖ0.6ÊÇÓÃÀŽÌÖÂÛ³öÏÖ¿ÕÎ»ÖÃµÄÇé¿ö£»
			m++; 
			yiwei(n,&a,&b);	temp+=1.0;
			if(a<1||a>15||b<1||b>15){
				liangduan1=1;
				break;
			}
			if(aRecordBoard[a][b]==0){
				temp+=0.6;	K[m]=a;	L[m]=b;	
				yiwei(n,&a,&b);
				if(aRecordBoard[a][b]==jifang){
					continue;
				}
				liangduan1=0;
				break;
			}
			if(aRecordBoard[a][b]==duifang){
				liangduan1=1;
				break;
			}
		} 
		n+=4; m-=1; a=P; b=Q;	temp=0;
		while(aRecordBoard[a][b]==jifang && temp<4.0){ 
			m++;  
			yiwei(n,&a,&b);	temp+=1.0;
			if(a<1||a>15||b<1||b>15){
				liangduan2=1;
				break;
			}
			if(aRecordBoard[a][b]==0){
				temp+=0.6;	K[m]=a;	L[m]=b;
				yiwei(n,&a,&b);
				if(aRecordBoard[a][b]==jifang){
					continue;
				}
				liangduan2=0;
				break;
			}
			if(aRecordBoard[a][b]==duifang){
				liangduan2=1;
				break;
			} 
		}
		if(m==4 && liangduan1==0 && liangduan2==0){
			huosi+=1;
			if(huosi==2){
				return 1;
			}
		}
		if(m==4 && ((liangduan1==1 && liangduan2==0) || (liangduan1==0 && liangduan2==1))){
			chongsi+=1;
			if(chongsi==2){
				return 1;
			}
		}
		if(chongsi+huosi==2){
			return 1;
		} 
		n-=3; a=P; b=Q;	//ÒÔÏÂÊÇÌØÊâµÄËÄËÄœûÊÖµÄÇé¿ö£¬ŒŽ³öÏÖÔÚÒ»žö·œÏòÉÏ£¬²»ÊÇÔÚÁœžö·œÏòÉÏµÄË«ËÄ£»
		if(m==5 && (K[2]-2==a || K[2]+2==a || L[2]-2==b || L[2]+2==b) && (K[4]-2==a || K[4]+2==a || L[4]-2==b || L[4]+2==b)){
			return 1;
		}
		if(m==6 &&( ((K[1]-1==a || K[1]+1==a || L[1]-1==b || L[1]+1==b) && (K[4]-2==a || K[4]+2==a || L[4]-2==b || L[4]+2==b)) || ((K[2]-2==a || K[2]+2==a || L[2]-2==b || L[2]+2==b) && (K[4]-1==a || K[4]+1==a || L[4]-1==b || L[4]+1==b)) )){
			return 1;
		}
		if(m==7 && (K[1]-1==a || K[1]+1==a || L[1]-1==b || L[1]+1==b) && (K[4]-1==a || K[4]+1==a || L[4]-1==b || L[4]+1==b)){
			return 1;
		}
	} 
	return 0;
}
int panduan_huosi(int a,int b,int c)	//ÅÐ¶ÏÔÚ£ša£¬b£©ŽŠÏÂ×Ó£¬ÊÇ·ñÐÎ³É»îËÄ£»
{
	int i,j,n=1,m,P,Q,huosi=0,chongsi=0,liangduan1,liangduan2;
	int jifang=0,duifang=0;
	float temp;
	P=a; Q=b;
	if(c==1){
		jifang=1;	duifang=2;
	}else if(c==2){
		jifang=2;	duifang=1;
	}
	while(n!=5){
		m=0; liangduan1=-1;	liangduan2=-1;	temp=0.0;
		while(aRecordBoard[a][b]==jifang && temp<4.0){ 
			m++; 
			yiwei(n,&a,&b);	temp+=1.0;
			if(a<1||a>15||b<1||b>15){
				liangduan1=1;
				break;
			}
			if(aRecordBoard[a][b]==0){
				liangduan1=0;
				break;
			}
			if(aRecordBoard[a][b]==duifang){
				liangduan1=1;
				break;
			}
		} 
		n+=4; m-=1; a=P; b=Q;	temp=0;
		while(aRecordBoard[a][b]==jifang && temp<4.0){ 
			m++;  
			yiwei(n,&a,&b);	temp+=1.0;
			if(a<1||a>15||b<1||b>15){
				liangduan2=1;
				break;
			}
			if(aRecordBoard[a][b]==0){
				liangduan2=0;
				break;
			}
			if(aRecordBoard[a][b]==duifang){
				liangduan2=1;
				break;
			} 
		}
		if(m==4 && liangduan1==0 && liangduan2==0){
			huosi+=1;
		}
		n-=3; a=P; b=Q;
	}
	return huosi;
}
int panduan_chongsi(int a,int b,int c)	//ÅÐ¶ÏÔÚ£ša£¬b£©ŽŠÏÂ×Ó£¬ÊÇ·ñÐÎ³É³åËÄ£»
{
	int i,j,n=1,m,P,Q,huosi=0,chongsi=0,liangduan1,liangduan2,kong;
	int jifang=0,duifang=0;
	int K[SIZE],L[SIZE];
	float temp;
	P=a; Q=b; 
	if(c==1){
		jifang=1;	duifang=2;
	}else if(c==2){
		jifang=2;	duifang=1;
	}
	while(n!=5){
		for(i=0,j=0;i<SIZE,j<SIZE;i++,j++){
			K[i]=0;	L[j]=0;
		}
		m=0; liangduan1=-1;	liangduan2=-1;	temp=0.0;	kong=0;
		while(aRecordBoard[a][b]==jifang && temp<4.0){	//tempÓÃÀŽŒÇÂŒÏòÃ¿žö·œÏòÒÑŸ­ÅÐ¶ÏÁË¶àÉÙ²œ£¬³öÏÖ0.6ÊÇÓÃÀŽÌÖÂÛ³öÏÖ¿ÕÎ»ÖÃµÄÇé¿ö£»
			m++; 
			yiwei(n,&a,&b);	temp+=1.0;
			if(a<1||a>15||b<1||b>15){
				liangduan1=1;
				break;
			}
			if(aRecordBoard[a][b]==0){
				temp+=0.6;	K[m]=a;	L[m]=b;
				yiwei(n,&a,&b);
				if(aRecordBoard[a][b]==jifang){
					kong+=1;
					continue;
				}
				liangduan1=0;
			}
			if(aRecordBoard[a][b]==duifang){
				liangduan1=1;
				break;
			}
		} 
		n+=4; m-=1; a=P; b=Q;	temp=0;
		while(aRecordBoard[a][b]==jifang && temp<4.0){ 
			m++;  
			yiwei(n,&a,&b);	temp+=1.0;
			if(a<1||a>15||b<1||b>15){
				liangduan2=1;
				break;
			} 
			if(aRecordBoard[a][b]==0){
				temp+=0.6;	K[m]=a;	L[m]=b;
				yiwei(n,&a,&b);
				if(aRecordBoard[a][b]==jifang){
					kong+=1;
					continue;
				}
				liangduan2=0;
			}
			if(aRecordBoard[a][b]==duifang){
				liangduan2=1;
				break;
			} 
		}
		if(m==4 && ((liangduan1==1 && liangduan2==0) || (liangduan1==0 && liangduan2==1)) && kong<2 ){
			chongsi+=1;
		}
		n-=3; a=P; b=Q;
	}
	if(chongsi>0){
		printf("chongsi=%d n=%d\n",chongsi,n);
	}
	return chongsi;
}
int panduan_huosan(int a,int b,int c)	//ÅÐ¶ÏÔÚ£ša£¬b£©ŽŠÏÂ×Ó£¬ÊÇ·ñÐÎ³É»îÈý£»
{
	int n=1,m,P,Q,huosan=0,liangduan1,liangduan2,temp;
	int jifang=0, duifang=0;
	P=a; Q=b; 
	if(c==1){
		jifang=1;	duifang=2;
	}else if(c==2){
		jifang=2;	duifang=1;
	}
	while(n!=5){ 
		m=0; liangduan1=-1;	liangduan2=-1;	temp=0;
		while(aRecordBoard[a][b]==jifang && temp<=3){ 
			m++; 
			yiwei(n,&a,&b);	temp+=1;
			if(a<1||a>15||b<1||b>15){
				liangduan1=1;
				break;
			}
			if(aRecordBoard[a][b]==0){
				yiwei(n,&a,&b);	temp+=1;
				if(aRecordBoard[a][b]==duifang){
					continue;
				}
				liangduan1=0;
				break;
			}
		} 
		n+=4; m-=1; a=P; b=Q;	temp=0;
		while(aRecordBoard[a][b]==jifang && temp<=3){ 
			m++;  
			yiwei(n,&a,&b);	temp+=1;
			if(a<1||a>15||b<1||b>15){
				liangduan2=1;
				break;
			}
			if(aRecordBoard[a][b]==0){
				yiwei(n,&a,&b);	temp+=1;
				if(aRecordBoard[a][b]==jifang){
					continue;
				}
				liangduan2=0;
				break;
			} 
		}
		if(m==3 && liangduan1==0 && liangduan2==0){
			huosan+=1;
		}
		n-=3; a=P; b=Q;
	}
	return huosan;
}
int panduan_huoer(int a, int b,int c)	//ÅÐ¶ÏÊÇ·ñÐÎ³É»î¶þ£»
{
	int n=1,m,P,Q,l,liangduan1,liangduan2,temp;	//lÊÇÓÃÀŽŒÇÂŒÁ¬ÐøµÄ×ÓÊý£»
	int jifang=-1, duifang=-1;
	P=a; Q=b; 
	if(c==1){
	  	jifang=1;	duifang=2;
	}else if(c==2){
		jifang=2;	duifang=1;
	}
	while(n!=5){ 
		m=0;	l=0;	liangduan1=-1;	liangduan2=-1;	temp=0;
		while(aRecordBoard[a][b]==jifang && temp<2){ 
			m++;	temp+=1;
			yiwei(n,&a,&b);
			if(a<1||a>15||b<1||b>15){
				liangduan1=1;
				break;
			}
			if(aRecordBoard[a][b]==jifang){
				yiwei(n,&a,&b);	temp+=1;
				if(aRecordBoard[a][b]==0){
					l++;
					break;
				}
			}
			else if(aRecordBoard[a][b]==0){
				yiwei(n,&a,&b);	temp+=1;
				if(aRecordBoard[a][b]==0){
					l++;	liangduan1=0;
					break;
				}
			}
		} 
		n+=4; m-=1; a=P; b=Q;	temp=0;
		while(aRecordBoard[a][b]==jifang && temp<2){ 
			m++; 
			yiwei(n,&a,&b);	temp+=1;
			if(a<1||a>15||b<1||b>15){
				liangduan2=1;
				break;
			}
			if(aRecordBoard[a][b]==0){
				yiwei(n,&a,&b);	temp+=1;
				if(aRecordBoard[a][b]==0){
					l++;	liangduan2=0;
				}
				if(l==2 && liangduan2==0 && liangduan1==-1){
					return 1;
				}
			}
			else if(aRecordBoard[a][b]==jifang){
				yiwei(n,&a,&b);	temp+=1;
				if(aRecordBoard[a][b]==0){
					l++;
				}
				if(l==2 && liangduan1==0 && liangduan2==-1){
					return 1;
				}
			}
		} 
		n-=3; a=P; b=Q;
	} 
	return 0;
}	
void defence(void)	//µçÄÔÖŽ°×Æå£¬Îª±£ÊØ·œ£»
{
	int i,j,m,n,temp1=0,temp2=0,reset=0;
	int c1[SIZE+1][SIZE+1],c2=0,e1[SIZE+1][SIZE+1],e2=0,d1[SIZE+1][SIZE+1],d2=0;
	int a1,a2,a11,a12,a111,a112;
	x_c=1;	y_c=1;
	for(i=1;i<=SIZE;i++){
		for(j=1;j<=SIZE;j++){
			c1[i][j]=0;	e1[i][j]=0;	d1[i][j]=0;
		}
	}
	for(x_c=1;x_c<=SIZE;x_c++){	//ÉšÃèÕûžöÆåÅÌ£¬žøÃ»ÓÐ×ÓµÄÎ»ÖÃÆÀ·Ö£»
		for(y_c=1;y_c<=SIZE;y_c++){
			a1=0;	a2=0;
			if(aRecordBoard[x_c][y_c]==0){
				a1=defence_score(x_c,y_c,1);	//ŒÆËãŽËŽŠÂäÏÂŒº·œ×ÓµÄµÃ·Ö£»
				a2=attack_score(x_c,y_c,2);		//ŒÆËãŽËŽŠÂäÏÂ¶Ô·œ×ÓµÄµÃ·Ö£»
			}
			else if(aRecordBoard[x_c][y_c]==1)
				;
			else if(aRecordBoard[x_c][y_c]==2)
				;
			c1[x_c][y_c]=a1+a2;
			if(c1[x_c][y_c]>c2){
				c2=c1[x_c][y_c];	x_current1=x_c;	y_current1=y_c;
				if(c1[x_c][y_c]>=400000){	//Èç¹ûŽËÊ±¶Ô·œ³öÏÖ»îÈý»ò±È»îÈýžüœôŒ±£¬»òÕßÎªœûÊÖ£¬ÖÜÎ§Îª¿ÕµÈÇé¿ö£¬²»ÔÙÏòÏÂ¿Ž¶Ô·œµÄÂä×ÓÎ»ÖÃ£»
					x_max=&x_current1;	y_max=&y_current1;
					temp1=1;	temp2=1;	reset=0;
				}
				printf("c[%d][%d]=%d c2=%d \n",x_c,y_c,c1[x_c][y_c],c2);
			}
		}
	}
	while(temp1<1){		//ÏòºóÔ€²â¶Ô·œµÄÂä×ÓÎ»ÖÃ£»
		aRecordBoard[x_current1][y_current1]=2;	x_c=1;	y_c=1;
		for(x_c=1;x_c<=SIZE;x_c++){
			for(y_c=1;y_c<=SIZE;y_c++){
				a11=0;	a12=0;
				if(aRecordBoard[x_c][y_c]==0){
					a11=defence_score(x_c,y_c,2);
					a12=attack_score(x_c,y_c,1);
				}
				else if(aRecordBoard[x_c][y_c]==1)
					;
				else if(aRecordBoard[x_c][y_c]==2)
					;
				d1[x_c][y_c]=a11+a12;
				if(d1[x_c][y_c]>d2){
					d2=d1[x_c][y_c];	x_current2=x_c;	y_current2=y_c;
					printf("d2=%d d1[%d][%d]=%d ",d2,x_c,y_c,d1[x_c][y_c]);
				}
			}
		}
		temp1++;	reset=1;	
	}
	while(temp2<1){		//Ô€²âÍêÒÔºó£¬ÔÚÂäŒº·œ×Ó£¬e2ŒÇÂŒÕûÌå×ÜÆÀ·Ö£»
		aRecordBoard[x_current2][y_current2]=1;	x_c=1;	y_c=1;
		for(x_c=1;x_c<=SIZE;x_c++){
			for(y_c=1;y_c<=SIZE;y_c++){
				a111=0;	a112=0;
				if(aRecordBoard[x_c][y_c]==0){
					a111=defence_score(x_c,y_c,1);
					a112=attack_score(x_c,y_c,2);
				}
				else if(aRecordBoard[x_c][y_c]==1)
					;
				else if(aRecordBoard[x_c][y_c]==2)
					;
				e1[x_c][y_c]=a111+a112;
				if((0.6*d1[x_c][y_c]+0.5*e1[x_c][y_c]+c1[x_c][y_c])>e2){
					e2=0.6*d1[x_c][y_c]+0.5*e1[x_c][y_c]+c1[x_c][y_c];
					x_current3=x_c;	y_current3=y_c;
					x_max=&x_current3;	y_max=&y_current3;
					printf("e[%d][%d]=%d e2=%d\n",x_c,y_c,e1[x_c][y_c],e2);
				}
			}	
		}
		temp2++;	reset=1;
	}
	if(reset==1){
		aRecordBoard[x_current1][y_current1]=0;
		aRecordBoard[x_current2][y_current2]=0;	
	}
}
void attack(void)	//µçÄÔÖŽºÚÆå£¬Îªœø¹¥·œ£»
{
	int i,j,m,n,reset=0,temp1=0,temp2=0;
	int c1[SIZE+1][SIZE+1],c2=0,e1[SIZE+1][SIZE+1],e2=0,d1[SIZE+1][SIZE+1],d2=0;
	int a1,a2,a11,a12,a111,a112;
	x_c=1;	y_c=1;
	for(i=1;i<=SIZE;i++){
		for(j=0;j<=SIZE;j++){
			c1[i][j]=0;	e1[i][j]=0;	d1[i][j]=0;
		}
	}
	for(x_c=1;x_c<=SIZE;x_c++){		//ÉšÃèÕûžöÆåÅÌ£¬žøÃ»ÓÐ×ÓµÄÎ»ÖÃÆÀ·Ö£»
		for(y_c=1;y_c<=SIZE;y_c++){
			a1=0;	a2=0;
			if(aRecordBoard[x_c][y_c]==0){
				a1=defence_score(x_c,y_c,2);	//ŒÆËãŽËŽŠÂäÏÂŒº·œ×ÓµÄµÃ·Ö£»
				a2=attack_score(x_c,y_c,1);		//ŒÆËãŽËŽŠÂäÏÂ¶Ô·œ×ÓµÄµÃ·Ö£»
			}
			else if(aRecordBoard[x_c][y_c]==1)
				;
			else if(aRecordBoard[x_c][y_c]==2)
				;
			c1[x_c][y_c]=a1+a2;
			if(c1[x_c][y_c]>c2){
				c2=c1[x_c][y_c];	x_current1=x_c;	y_current1=y_c;
				if(c1[x_c][y_c]>=400000){	//ÈôŽËŽŠ³öÏÖ»îÈý»òžüœôŒ±µÄÇé¿ö²»ÔÙÏòºóÔ€²â£»
					x_max=&x_current1;	y_max=&y_current1;
					temp1=1;	temp2=1;	reset=0;
				}
				printf("c[%d][%d]=%d c2=%d \n",x_c,y_c,c1[x_c][y_c],c2);
			}
		}
	}
	while(temp1<1){		//ÏòºóÔ€²â¶Ô·œµÄÂä×ÓÎ»ÖÃ£»
		aRecordBoard[x_current1][y_current1]=1;	x_c=1;	y_c=1;
		for(x_c=1;x_c<=SIZE;x_c++){
			for(y_c=1;y_c<=SIZE;y_c++){
				a11=0;	a12=0;
				if(aRecordBoard[x_c][y_c]==0){
					a11=defence_score(x_c,y_c,1);
					a12=attack_score(x_c,y_c,2);
				}
				else if(aRecordBoard[x_c][y_c]==1)
					;
				else if(aRecordBoard[x_c][y_c]==2)
					;
				d1[x_c][y_c]=a11+a12;
				if(d1[x_c][y_c]>d2){
					d2=d1[x_c][y_c];	x_current2=x_c;	y_current2=y_c;
					printf("d[%d][%d]=%d d2=%d ",x_c,y_c,d1[x_c][y_c],d2);
				}
			}
		}
		temp1++;	reset=1;
	}
	while(temp2<1){		//Ô€²âÍêÒÔºó£¬ÔÚÂäŒº·œ×Ó£¬e2ŒÇÂŒÕûÌå×ÜÆÀ·Ö£»
		aRecordBoard[x_current2][y_current2]=2;	x_c=1;	y_c=1;
		for(x_c=1;x_c<=SIZE;x_c++){
			for(y_c=1;y_c<=SIZE;y_c++){
				a111=0;	a112=0;
				if(aRecordBoard[x_c][y_c]==0){
					a111=defence_score(x_c,y_c,2);
					a112=attack_score(x_c,y_c,1);
				}
				else if(aRecordBoard[x_c][y_c]==1)
					;
				else if(aRecordBoard[x_c][y_c]==2)
					;
				e1[x_c][y_c]=a111+a112;
				if((0.6*d1[x_c][y_c]+0.5*e1[x_c][y_c]+c1[x_c][y_c])>e2){
					e2=0.6*d1[x_c][y_c]+0.5*e1[x_c][y_c]+c1[x_c][y_c];
					x_current3=x_c;	y_current3=y_c;
					x_max=&x_current3;	y_max=&y_current3;
					printf("e[%d][%d]=%d e2=%d\n",x_c,y_c,e1[x_c][y_c],e2);
				}
			}	
		}
		temp2++;	reset=1;
	}
	if(reset==1){
		aRecordBoard[x_current1][y_current1]=0;
		aRecordBoard[x_current2][y_current2]=0;
	}
}	
int defence_score(int a,int b,int c)	//Œº·œ×ÓµÄ·ÀÊØµÃ·Ö£»
{
	int dscore=0;
	aRecordBoard[a][b]=c;
	if(c==1 && win(a,b,c)){
		if(changlianjinshou(a,b,c)){
			dscore=0;
			aRecordBoard[a][b]=0;
			return dscore;
		}else{
			dscore=5000000;		//ºÚÆåÓ®£¬ÇÒÎÞœûÊÖ
			aRecordBoard[a][b]=0;
			return dscore;
		}
	}else if(c==2 && win(a,b,c)){
		dscore=5000000;		//°×ÆåÓ®£»
		aRecordBoard[a][b]=0;
		return dscore;
	}	
	if(c==2 && sisijinshou(a,b,c)){
		dscore=4000000;		//°×Æå³öÏÖ¡°Ë«»îËÄ¡±
		aRecordBoard[a][b]=0;
		return dscore;
	}else if(c==1 && (sisijinshou(a,b,c) || changlianjinshou(a,b,c))){
		dscore=0;		//ºÚÆå³öÏÖË«»îËÄœûÊÖ£»
		aRecordBoard[a][b]=0;
		return dscore;
	}
	if((panduan_huosi(a,b,c)==1 || panduan_chongsi(a,b,c)==1)&& panduan_huosan(a,b,c)==1){
		dscore+=600000;			//³öÏÖÈý¡¢ËÄµÄÇé¿ö£»
	}
	if(panduan_huosi(a,b,c)==1){
		dscore+=800000;		//³öÏÖ»îËÄ£»
		aRecordBoard[a][b]=0;
		return dscore;
	}
	if(panduan_chongsi(a,b,c)==1){
		dscore+=35000;		//³öÏÖ³åËÄ£»
	}
	if(c==2 && shuanghuosanjinshou(a,b,c)){
		dscore+=400000;		//°×Æå³öÏÖ¡°Ë«»îÈý¡±
		aRecordBoard[a][b]=0;
		return dscore;
	}else if(c==1 && shuanghuosanjinshou(a,b,c)){
		dscore=0;		//ºÚÆå³öÏÖË«»îÈýœûÊÖ£»
		aRecordBoard[a][b]=0;
		return dscore;
	}
	if(panduan_huosan(a,b,c)==1){
		dscore+=60000;	//³öÏÖ»îÈý£»
		aRecordBoard[a][b]=0;
		return dscore;
	}
	if(panduan_huoer(a,b,c)==1){
		dscore+=20000;		//³öÏÖ»î¶þ£»
	}
	aRecordBoard[a][b]=0;
	return dscore;
}
int attack_score(int a,int b,int c)		//ÓÃ¶Ô·œ×ÓµÄœø¹¥µÃ·Ö£¬ÆÀ·Ö·œÊœÓëdefence_scoreÏàÍ¬£»
{
	int dscore=0;
	aRecordBoard[a][b]=c;
	if(c==1 && win(a,b,c)){
		if(changlianjinshou(a,b,c)){
			dscore=0;
			aRecordBoard[a][b]=0;
			return dscore;
		}else{
			dscore=5000000;
			aRecordBoard[a][b]=0;
			return dscore;
		}
	}else if(c==2 && win(a,b,c)){
		dscore=5000000;
		aRecordBoard[a][b]=0;
		return dscore;
	}
	if(c==2 && sisijinshou(a,b,c)){
		dscore=4000000;
		aRecordBoard[a][b]=0;
		return dscore;
	}else if(c==1 && (sisijinshou(a,b,c) || changlianjinshou(a,b,c))){
		dscore=0;
		aRecordBoard[a][b]=0;
		return dscore;
	}
	if((panduan_huosi(a,b,c)==1 || panduan_chongsi(a,b,c)==1) && panduan_huosan(a,b,c)==1){
		dscore+=600000;
	}
	if(panduan_huosi(a,b,c)==1){
		dscore+=800000;
		aRecordBoard[a][b]=0;
		return dscore;
	}
	if(panduan_chongsi(a,b,c)==1){
		dscore+=35000;
	}
	if(c==2 && shuanghuosanjinshou(a,b,c)){
		dscore+=400000;
		aRecordBoard[a][b]=0;
		return dscore;
	}else if(c==1 && shuanghuosanjinshou(a,b,c)){
		dscore=0;
		aRecordBoard[a][b]=0;
		return dscore;
	}
	if(panduan_huosan(a,b,c)==1){
		dscore+=60000;
		aRecordBoard[a][b]=0;
		return dscore;
	}
	if(panduan_huoer(a,b,c)==1){
		dscore+=20000;
	}
	aRecordBoard[a][b]=0;
	return dscore;
}