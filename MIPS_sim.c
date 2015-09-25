//MIPS-Simulator, compression and decompression algorithm impltemented

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void getins();
void count();
void diction();
int countn();


typedef struct node {
char data[40];
int num;
struct node* next;
}nd;
nd *startinp=NULL;

typedef struct dnode {
char data[40];
char bin[5];
struct dnode* next;
}nd1;
nd1 *startdict=NULL;

typedef struct dnode3 {
char data[40];
char bin[5];
struct dnode* next;
}nd3;
nd3 *startdict3=NULL;

typedef struct node2 {
char data[40];
int num;
struct node* next;
}nd2;
nd2 *startcom=NULL;

char str[2000];
char dc[2000];

void getins()
{
FILE *source;
char text1[35];

source = fopen("original.txt", "r");
struct node *nnode, *current;

if(source != NULL)
    {
    while(fscanf(source, "%s\n", text1) !=EOF)
        {
            nnode = (struct node *)malloc(sizeof(struct node));
            strcpy(nnode->data, text1);
            nnode->next= NULL;
            if(startinp==NULL)
            {
                startinp=nnode;
                current=nnode;
            }
            else{
                current->next=nnode;
                current=nnode;
            }
        }
    }
else
    {
    fprintf(stdout, "Cannot open file.\n");
    exit(-1);
    }
fclose(source);

}

void getcomp()
{
   FILE *source;
   char text2[35];

source = fopen("compressed.txt", "r");
struct node2 *nnode, *current;

if(source!= NULL)
    {
    while(fscanf(source, "%s\n", text2) !=EOF)
        {
            nnode = (struct node2 *)malloc(sizeof(struct node2));
            strcpy(nnode->data, text2);
            nnode->next= NULL;
            if(startcom==NULL)
            {
                startcom=nnode;
                current=nnode;
            }
            else
            {
                current->next=nnode;
                current=nnode;
            }
        }
    }
else
    {
    fprintf(stdout, "Cannot open file.\n");
    exit(-1);
    }
fclose(source);
}

void count()
{
    nd *cnt,*cnt1;
    int ct=0;
    cnt=startinp;
    cnt1=startinp;
    while(cnt!=NULL){
    while(cnt1!=NULL){
        if(strcmp(cnt->data,cnt1->data)==0)
        {
            ct++;
            //printf("%d",ct);
        }
        cnt1=cnt1->next;
    }
    cnt1=startinp;
    cnt->num=ct;
    cnt = cnt->next;
    ct=0;
    }
}

int countn()
{
    nd *q;
    int count=0;
    q=startinp;
    while(q!=NULL){
        count++;
        q=q->next;
    }
    return count;
}

void diction()
{
    nd *high,*cur;
    nd1 *q1,*current = startdict,*nnode;
    int ar[100],n=0,i=0,j,k,size,t=0;

    //n=countn();
    //size=n;
    //printf("%d\n",n);
    //nnode=(nd *)malloc(sizeof(nd));

    //cur=startinp;

for(i=0;i<8;i++)
{
    high=startinp;
    cur=startinp->next;

    while(cur!=NULL){

    if(cur->num > high->num)
    {
        high=cur;
        cur=cur->next;
    }
    if(cur->num==high->num && strcmp(high->data,cur->data)==0){
      high->num=0;
      high=cur;
      cur=cur->next;
    }
    else
        cur=cur->next;

    }

    nnode = (struct dnode *)malloc(sizeof(struct dnode));
        if(i==0)
            strcpy(nnode->bin,"000");
        if(i==1)
            strcpy(nnode->bin,"001");
        if(i==2)
            strcpy(nnode->bin,"010");
        if(i==3)
            strcpy(nnode->bin,"011");
        if(i==4)
            strcpy(nnode->bin,"100");
        if(i==5)
            strcpy(nnode->bin,"101");
        if(i==6)
            strcpy(nnode->bin,"110");
        if(i==7)
            strcpy(nnode->bin,"111");
        strcpy(nnode->data, high->data);
        high->num=0;
        //nnode->num=startinp->num;

        nnode->next=NULL;
        if(startdict==NULL)
        {
            startdict=nnode;
            current=nnode;
        }
        else
        {
            current->next=nnode;
            current=nnode;
        }
}

        

}

void compress()
{
    nd *cur=startinp;
    nd1 *current;
    int count;
    int i=0,m=0,x=0,p=0,q=0,j,ml1,ml2;
    char ar[10];

    while(cur!=NULL)
    {
        count=0;
        current=startdict;
        while(current!=NULL)
        {
           if(strcmp(cur->data,current->data)==0)
           {
               strcat(str,"00");
               strcat(str,current->bin);
               count=1;
               goto a;
           }
           current=current->next;
        }

        current=startdict;
        while(current!=NULL)
        {
            for(i=0;i<32;i++)
            {
                 if(cur->data[i]==current->data[i])
                 m++;
            }
            if(m==30){
                for(i=0;i<32;i++){
                 if(cur->data[i+1]!=current->data[i+1]&&cur->data[i+2]!=current->data[i+2])
                {
                   x=0;
                   strcat(str,"01");
                   x=dectobin(i+1);
                   sprintf(ar,"%ld",x);
                   strcat(str,ar);
                   strcat(str,current->bin);
                   m++;
                   count=2;
                   goto a;
                }}
                //strcat(str,"01");

            }
            //printf("%d\n",m);
            current=current->next;
            m=0;
        }
        current=startdict;
        while(current!=NULL)
        {
            for(i=0;i<32;i++)
            {
                 if(cur->data[i]==current->data[i])
                 m++;
            }
            if(m==30){
                for(i=0;i<32;i++){
                 if(cur->data[i]!=current->data[i])
                {
                    ml1=i;
                   for(j=i+2;j<32;j++){
                        if(cur->data[j]!=current->data[j])
                            ml2=j;
                   }

                   p=0;
                   q=0;
                   strcat(str,"10");
                   p=dectobin(ml1);
                   sprintf(ar,"%ld",p);
                   if(strlen(ar)==1)
                   {
                       strcat(str,"0000");
                   }
                   if(strlen(ar)==2)
                   {
                       strcat(str,"000");
                   }
                   if(strlen(ar)==3)
                   {
                       strcat(str,"00");
                   }
                   if(strlen(ar)==4)
                   {
                       strcat(str,"0");
                   }
                   strcat(str,ar);

                   q=dectobin(ml2);
                   sprintf(ar,"%ld",q);
                    if(strlen(ar)==1)
                   {
                       strcat(str,"0000");
                   }
                   if(strlen(ar)==2)
                   {
                       strcat(str,"000");
                   }
                   if(strlen(ar)==3)
                   {
                       strcat(str,"00");
                   }
                   if(strlen(ar)==4)
                   {
                       strcat(str,"0");
                   }
                   strcat(str,ar);

                   strcat(str,current->bin);
                   m++;
                   count=3;
                   goto a;
                }}
                //strcat(str,"01");

            }
            //printf("%d\n",m);
            current=current->next;
            m=0;
        }
        /*if(m==30){
            for(i=0<;i<32;i++){
                if(cur->data[i]!=cur->data[i])

            }
        }*/
        a:
        if(count==0)
        {
            strcat(str,"11");
            strcat(str,cur->data);
        }
        //m=0;
        cur=cur->next;
    }
}


void setlines()
{
    nd2 *q,*current;
    nd3 *p,*nnode;

    p=startdict3;
    q=startcom;

    int a=1,x=0;
    char ar[5];

    while(q!=NULL&&(strcmp(q->data,"xxxx")!=0))
    {
        strcat(dc,q->data);
       // printf("%s\n",q->data);

        q=q->next;
    }
    while(q!=NULL)
    {
        nnode = (struct dnode3 *)malloc(sizeof(struct dnode3));
        strcpy(nnode->data,q->data);
        x=dectobin(a);
        sprintf(ar,"%ld",x);
        strcpy(nnode->bin,ar);
        nnode->next= NULL;
        printf("%s\n",nnode->data);
        if(startdict3==NULL)
            {
                startdict3=nnode;
                current=nnode;
            }
            else{
                current->next=nnode;
                current=nnode;
            }
        a++;
        q=q->next;
    }
}

void decompress()
{
  getins();
}

int dectobin(int dec){

    if (dec == 0)
    {
        return 0;
    }
    else
    {
        return (dec % 2 + 10 * dectobin(dec / 2));
    }

}

int bintodec(int bi)
{
    int binary_val, decimal_val = 0, base = 1, rem=0;

    while (bi > 0)
    {
        rem = bi % 10;
        decimal_val = decimal_val + rem * base;
        bi = bi / 10 ;
        base = base * 2;
    }
    return decimal_val;
}


int main(int argc, char const *argv[])
{
    int i,j,k;

  if (strcmp(argv[1],"2") == 0)
    {
        decompress();
        FILE *output2;
      output2 = fopen("dout.txt", "w");
      nd *q;
        q=startinp;
        while(q!=NULL)
        {
        fprintf(output2,"%s\n",q->data);
        q=q->next;
        }

    }
    if(strcmp(argv[1],"1")==0)
    {
      FILE *cout;
      cout = fopen("cout.txt", "w");
    int i, j, k=0;
    getins();
    nd1 *show;
    count();
    diction();
    compress();
    getcomp();

    for (i = 0; i < (32-(strlen(str)%32)); i++)
    {      }

    for (j = 0; j < i; ++j)
    {
      strcat(str,"1");
    }

    strcat(str,"\0");

    for (i = 0; i < (strlen(str)/32); ++i)
    {
      for (j = 0; j < 32; ++j)
      {
        fprintf(cout,"%c", str[k]);
        k++;
      }
      fprintf(cout,"\n");
    }
    fprintf(cout,"xxxx\n");

    show=startdict;

    while(show!=NULL)
    {
      fprintf(cout, "%s\n", show->data);
      show=show->next;
    }
    }


}

