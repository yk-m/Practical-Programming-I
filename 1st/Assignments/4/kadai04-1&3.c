#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>

typedef struct{
	int feat[7][7][4];
}feature;

void printimg(char data[]);
void expand(char data[512],char pattern[64][64]);
void compress(char data[512],char pattern[64][64]);
void outline(char p[64][64]);
void smooth(char p[64][64]);
void normalize(char p[64][64]);
void fit_center(char p[64][64]);
int label(char p[64][64]);
void erosion(char p[64][64],int x,int y,int cnt);
void noise(char p[64][64],int size);
void thinning(char p[64][64]);
int thin(char p[64][64],int flag);
int thin_match(int fcs[3][3],char p[64][64],int ii,int jj);
feature extract(char p[64][64]);
void extract_dir(char p[64][64],int dir[4],int ii,int jj);
void save_feat(FILE *fp,feature value);
void get_dicdata(FILE *fp,feature data[]);
int compare_feat(feature data[],feature fdata);
int get_dis(feature a,feature b,int *mindis);

main(int argc,char *argv[])
{
	FILE *fdr,*dic;
	char data[512],pattern[64][64];
	int j,num,class[46]={0},index,cnt=0;
	feature dicdata[46];

	if(argc != 2){
		fprintf(stderr,"usage:%s image-file\n",argv[0]);
		exit(0);
	}

	if((dic=fopen("ave.dic","rb"))==NULL){
		fprintf(stderr,"cannot open ave.dic\n");
		exit(1);
	}

	get_dicdata(dic,dicdata);

	if((fdr=fopen(argv[1],"rb"))==NULL){
		fprintf(stderr,"cannot open %s\n",argv[1]);
		exit(1);
	}
	fseek(fdr,0,SEEK_END);
	num=ftell(fdr)/512;
	fseek(fdr,0,SEEK_SET);

	index=atoi(strtok(argv[1],"."))-1;

	for(j=0;j<num;j++){
		if(fread(data,512,1,fdr) != 1){
			fprintf(stderr,"cannot read %s\n",argv[1]);
			exit(3);
		}
		expand(data,pattern);

		noise(pattern,15);
		smooth(pattern);
		normalize(pattern);
		thinning(pattern);
		if(compare_feat(dicdata,extract(pattern))==index) cnt++;
	}

	printf("%d / %d\n",cnt,num);

	fclose(fdr);
	fclose(dic);
}

//•\Ž¦ŠÖ”
void printimg(char data[])
{
	unsigned char mask;
	int i,j,k;

	for(k=0;k<64;k++){
		for(i=k*8;i<k*8+8;i++){
			mask=0x80;
			for(j=0;j<8;j++){
				if((data[i]&mask)==0){
					printf(".");
				}else{
					printf("*");
				}
				mask>>=1;
			}
		}
		printf("\n");
	}
	for(i=0;i<64;i++) printf("-");
	printf("\n");
}

void expand(char data[512],char pattern[64][64])
{
	unsigned char mask;
	int i,j,k;

	for(k=0;k<64;k++){
		for(i=k*8;i<k*8+8;i++){
			mask=0x80;
			for(j=0;j<8;j++){
				if((data[i]&mask)==0){
					pattern[k][j+(i*8)%64]=0;
				}else{
					pattern[k][j+(i*8)%64]=1;
				}
				mask>>=1;
			}
		}
	}
}

void compress(char data[512],char pattern[64][64])
{
	int i,j,k,cnt=0;
	unsigned char tmp=128,buf=0;

	for(i=0;i<64;i++){
		for(j=0;j<8;j++){
			for(k=j*8;k<j*8+8;k++){
				if(pattern[i][k]==1){
					buf+=0x80>>k%8;
				}
			}
			data[cnt]=buf;
			cnt++;
			buf=0;
			tmp=128;
		}
	}
}

void outline(char p[64][64])
{
	char tmp[64][64];
	int i,j;

	for(i=0;i<64;i++){
		for(j=0;j<64;j++){
			tmp[i][j]=p[i][j];
		}
	}

	for(i=0;i<64;i++){
		for(j=0;j<64;j++){
			if(tmp[i+1][j] && tmp[i-1][j] && tmp[i][j+1] && tmp[i][j-1]) p[i][j]=0;
		}
	}
}

void smooth(char p[64][64])
{
	int i,j,k,l,o,q;
	int sum;

	for(i=1;i<64-1;i++){
		for(j=1;j<64-1;j++){
			if(p[i][j] == 1){
				sum=0;
				for(o=-1;o<2;o++){
					for(q=-1;q<2;q++){
						sum+=p[i+o][j+q];
					}
				}
				if(sum==7){
					if(p[i-1][j-1]==0 && p[i-1][j+1]==0) p[i-1][j]=0;
					else if(p[i-1][j+1]==0 && p[i+1][j+1]==0) p[i][j+1]=0;
					else if(p[i+1][j+1]==0 && p[i+1][j-1]==0) p[i+1][j]=0;
					else if(p[i+1][j-1]==0 && p[i-1][j-1]==0) p[i][j-1]=0;
				}else if(sum==8){
					if(p[i-1][j]==0) p[i-1][j]=1;
					else if(p[i][j+1]==0) p[i][j+1]=1;
					else if(p[i+1][j]==0) p[i+1][j]=1;
					else if(p[i][j-1]==0) p[i][j-1]=1;
				}
			}
		}
	}
}

void normalize(char p[64][64])
{
	int i,j,x0=-1,y0=-1,x1=-1,y1=-1,x,y,W=64,H=64;
	double w,h;
	char norm[64][64];

	for(i=0;i<64;i++){
		for(j=0;j<64;j++){
			if(p[j][i]==1 && x0==-1) x0=i;
			if(p[i][j]==1 && y0==-1) y0=i;
			if(p[j][63-i]==1 && x1==-1) x1=63-i;
			if(p[63-i][j]==1 && y1==-1) y1=63-i;
		}
	}
	w=(double)(x1-x0);
	h=(double)(y1-y0);

	for(i=0;i<64;i++){
		for(j=0;j<64;j++){
			/*
			   if(w>h){
			   x=(int)(j*(w/W)+x0+0.5);
			   y=(int)(i*(w/W)+y0+0.5);
			   }else{
			   x=(int)(j*(h/H)+x0+0.5);
			   y=(int)(i*(h/H)+y0+0.5);
			   }*/
			x=(int)(j*(w/W)+x0+0.5);
			y=(int)(i*(h/H)+y0+0.5);
			if(p[y][x]!=0){
				norm[i][j]=1;
			}else{
				norm[i][j]=0;
			}
		}
	}

	for(i=0;i<64;i++){
		for(j=0;j<64;j++){
			p[i][j]=norm[i][j];
		}
	}

	//fit_center(p);

}

void fit_center(char p[64][64])
{
	int i,j,x0=-1,y0=-1,x1=-1,y1=-1,x,y;
	char tmp[64][64];

	for(i=0;i<64;i++){
		for(j=0;j<64;j++){
			if(p[j][i]==1 && x0==-1) x0=i;
			if(p[i][j]==1 && y0==-1) y0=i;
			if(p[j][63-i]==1 && x1==-1) x1=63-i;
			if(p[63-i][j]==1 && y1==-1) y1=63-i;
		}
	}

	if(x0+(63-x1)+y0+(63-y1)==0) return;
	x=(x0<(63-x1))?(x0+(63-x1))/2:-1*(x0+(63-x1))/2;
	y=(y0<(63-y1))?(y0+(63-y1))/2:-1*(y0+(63-y1))/2;

	for(i=0;i<64;i++){
		for(j=0;j<64;j++){
			if(i-y<0 || 63<i-y || j-x<0 || 63<j-x){
				tmp[i][j]=0;
			}else{
				tmp[i][j]=p[i-y][j-x];
			}
		}
	}

	for(i=0;i<64;i++){
		for(j=0;j<64;j++){
			p[i][j]=tmp[i][j];
		}
	}
}

int label(char p[64][64])
{
	int i,j,cnt=2;
	for(i=0;i<64;i++){
		for(j=0;j<64;j++){
			if(p[i][j]==1){
				if(cnt>=255) return 1;
				erosion(p,i,j,cnt);
				cnt++;
			}
		}
	}
	return 0;
}

void erosion(char p[64][64],int x,int y,int cnt)
{
	int o,q;

	for(o=-1;o<2;o++){
		for(q=-1;q<2;q++){
			if((o==0 && q==0) || x+o<0 || x+o>63 || y+q<0 || y+q>63) continue;
			if(p[x+o][y+q]==1){
				p[x+o][y+q]=cnt;
				erosion(p,x+o,y+q,cnt);
			}
		}
	}
}


void noise(char p[64][64],int size)
{
	int i,j,lsize[254]={0};

	if(label(p)==1) return;
	for(i=0;i<64;i++){
		for(j=0;j<64;j++){
			if(p[i][j]!=0) lsize[p[i][j]]++;
		}
	}
	for(i=0;i<254;i++){
		if(lsize[i]<=size) lsize[i]=-1;
	}
	for(i=0;i<64;i++){
		for(j=0;j<64;j++){
			if(p[i][j]!=0){
				if(lsize[p[i][j]]==-1){
					p[i][j]=0;
				}else{
					p[i][j]=1;
				}
			}
		}
	}
}

void thinning(char p[64][64])
{
	while(1){
		if(thin(p,0)==0) return;
		if(thin(p,1)==0) return;
	}
}

int thin(char p[64][64],int flag)
{
	int i,j,k,check=0,count=0;
	char tmp[64][64]={0};
	int rmv[2][2][3][3]=
	{
		{
			{
				{2,0,2},
				{2,1,2},
				{2,2,2}},
			{
				{2,2,2},
				{2,1,0},
				{2,2,2}}},
		{
			{
				{2,2,2},
				{2,1,2},
				{2,0,2}},
			{
				{2,2,2},
				{0,1,2},
				{2,2,2}}}
	};

	int nrmv[2][14][3][3]=
	{
		{
			{
				{2,0,2},
				{2,1,1},
				{2,1,0}},
			{
				{0,1,2},
				{1,1,0},
				{2,2,2}},
			{
				{2,2,2},
				{0,1,0},
				{2,1,2}},
			{
				{2,0,2},
				{1,1,2},
				{2,0,2}},
			{
				{2,1,2},
				{0,1,0},
				{2,2,2}},
			{
				{2,0,2},
				{2,1,1},
				{2,0,2}},
			{
				{2,2,2},
				{0,1,2},
				{1,0,2}},
			{
				{1,0,2},
				{0,1,2},
				{2,2,2}},
			{
				{2,0,1},
				{2,1,0},
				{2,2,2}},
			{
				{2,2,2},
				{2,1,0},
				{2,0,1}},
			{
				{0,1,0},
				{1,1,1},
				{0,2,0}},
			{
				{0,1,0},
				{2,1,1},
				{0,1,0}},
			{
				{0,2,0},
				{1,1,1},
				{0,1,0}},
			{
				{0,1,0},
				{1,1,2},
				{0,1,0}}},
		{
			{
				{0,1,2},
				{1,1,2},
				{2,0,2}},
			{
				{2,2,2},
				{0,1,1},
				{2,1,0}},
			{
				{2,2,2},
				{0,1,0},
				{2,1,2}},
			{
				{2,0,2},
				{1,1,2},
				{2,0,2}},
			{
				{2,1,2},
				{0,1,0},
				{2,2,2}},
			{
				{2,0,2},
				{2,1,1},
				{2,0,2}},
			{
				{2,2,2},
				{0,1,2},
				{1,0,2}},
			{
				{1,0,2},
				{0,1,2},
				{2,2,2}},
			{
				{2,0,1},
				{2,1,0},
				{2,2,2}},
			{
				{2,2,2},
				{2,1,0},
				{2,0,1}},
			{
				{0,1,0},
				{1,1,1},
				{0,2,0}},
			{
				{0,1,0},
				{2,1,1},
				{0,1,0}},
			{
				{0,2,0},
				{1,1,1},
				{0,1,0}},
			{
				{0,1,0},
				{1,1,2},
				{0,1,0}}}
	};



	for(i=0;i<64;i++){
		for(j=0;j<64;j++){
			if(thin_match(rmv[flag][0],p,i,j)==1 && thin_match(rmv[flag][1],p,i,j)==1) continue;
			for(k=0;k<14;k++){
				if(thin_match(nrmv[flag][k],p,i,j)==0){
					check=1;
					break;
				}
			}
			if(check==0){
				tmp[i][j]=1;
			}
			check=0;
		}
	}

	for(i=0;i<64;i++){
		for(j=0;j<64;j++){
			if(tmp[i][j]==1){
				p[i][j]=0;
				count++;
			}
		}
	}

	return count;
}


int thin_match(int fcs[3][3],char p[64][64],int ii,int jj)
{
	int i,j;
	for(i=0;i<3;i++){
		for(j=0;j<3;j++){
			if(ii+i-1<0 || ii+i-1>63 || jj+j-1<0 || jj+j-1>63) continue;
			if(fcs[i][j]!=2  &&  fcs[i][j]!=p[ii+i-1][jj+j-1]) return 1;
		}
	}

	return 0;
}

feature extract(char p[64][64])
{
	feature value;
	int i,j;
	for(i=0;i<7;i++){
		for(j=0;j<7;j++){
			extract_dir(p,value.feat[i][j],i*8,j*8);
		}
	}
	return value;
}

void extract_dir(char p[64][64],int dir[4],int ii,int jj)
{
	int i,j;
	for(i=0;i<4;i++) dir[i]=0;
	for(i=ii;i<ii+16;i++){
		for(j=jj;j<jj+16;j++){
			if(p[i][j]==1){
				if(i-1>=0  && j-1>=0  && p[i-1][j-1]) dir[3]++;
				if(i-1>=0  && j+1<=63 && p[i-1][j+1]) dir[1]++;
				if(i+1<=63 && j+1<=63 && p[i+1][j+1]) dir[3]++;
				if(i+1<=63 && j-1>=0  && p[i+1][j-1]) dir[1]++;
				if(i-1>=0  && p[i-1][j]) dir[0]++;
				if(i+1<=63 && p[i+1][j]) dir[0]++;
				if(j-1>=0  && p[i][j-1]) dir[2]++;
				if(j+1<=63 && p[i][j+1]) dir[2]++;
			}
		}
	}
}

void save_feat(FILE *fp,feature value)
{
	int i,j,k;
	for(i=0;i<7;i++){
		for(j=0;j<7;j++){
			for(k=0;k<4;k++){
				fprintf(fp,(k==0)?"%d":",%d",value.feat[i][j][k]);
			}
			fprintf(fp,"\n");
		}
	}
}

void get_dicdata(FILE *fp,feature data[])
{
	int i,j,k,l;
	char buf[32];

	for(i=0;i<46;i++){
		for(j=0;j<7;j++){
			for(k=0;k<7;k++){
				fscanf(fp,"%s",buf);
				for(l=0;l<4;l++){
					data[i].feat[j][k][l]=atoi(strtok((l==0)?buf:NULL,","));
				}
			}
		}
	}
}

int compare_feat(feature data[],feature fdata)
{
	int i,flag=0,mindis=-1;
	for(i=0;i<46;i++){
		if(get_dis(data[i],fdata,&mindis)==1){
			flag=i;
		}
	}
	return flag;
}

int get_dis(feature a,feature b,int *mindis)
{
	int i,j,k,dis=0;
	for(i=0;i<7;i++){
		for(j=0;j<7;j++){
			for(k=0;k<4;k++){
				dis+=(a.feat[i][j][k]-b.feat[i][j][k])*(a.feat[i][j][k]-b.feat[i][j][k]);
				if(*mindis!=-1 && dis>*mindis) return -1;
			}
		}
	}
	*mindis=dis;
	return 1;
}

