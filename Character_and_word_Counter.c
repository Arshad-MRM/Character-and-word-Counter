#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int strInt(char s[]){
    int i,count=0;
    if(s[0]=='-'){
        for(i=0; i<strlen(s); i++){
            if(isdigit(s[i])==1)
                count++;
        }
        count++;
    }else{
        for(i=0; i<strlen(s); i++){
            if(isdigit(s[i])==1)
                count++;
        }
    }

    if(count==strlen(s))
        return 1;
    else
        return 0;
}

typedef struct _ {      //CHAR COUNTING STRUCTURE FUNCTION
    char ch;
    int count;
    int rank;
} countChar;


typedef struct node {   //WORD COUNTING LINKED LIST FUNCTION
	char wrd[100];
	int wcount;
	int rank;
	struct node * wnext;
} nodew;

nodew * head = NULL;
int tot=0;

int addW(char s[]){     //WORD COUNT FUNCTION , ADD A "NEW NODE" OR ADD COUNT "+1" TO CURRENT NODE

    nodew *tmp;
    tmp= (nodew*)malloc(sizeof(nodew));

    strcpy(tmp->wrd,s);
    tmp->wcount=1;
    tmp->wnext=NULL;

    if(head!=NULL){
        nodew *p, *q;
        p=head;
        while(p != NULL){
            if(strcmp(p->wrd,s)==0){
               p->wcount++;
               return 0;
            }
            q=p;
            p= p->wnext;
        }

        q->wnext=tmp;
        return 0;

    }else{
       head=tmp;
       return 0;
    }
}

void ptc(char c, int count, float f, int p, int s, int max){    //PRINT ONE BAR FOR A CHAR

    int i,g,b;
    float a;

    g=76-p;

    if(s==0){
        a=(float)count/tot*g;
        b=(int)a;
    }
    else if(s==1){
        a=(float)count/max*g;
        b=(int)a;
    }
        printf("   ");      //1
        printf("\u2502");
        for(i=0; i<b; i++){
            printf("\u2591");
        }
        printf("\n ");      //2
        printf("%c ",c);
        printf("\u2502");
        for(i=0; i<b; i++){
            printf("\u2591");
        }
        printf("%.2f%%\n",f);
        printf("   ");
        printf("\u2502");
        for(i=0; i<b; i++){
            printf("\u2591");
        }
        printf("\n   ");    //3
        printf("\u2502");
        printf("\n");
}

void ptcU(){                //PRINT CHAR FOR LAST LINE
    printf("   \u2514");
    int i;
    for(i=0; i<76; i++)
        printf("\u2500");
    printf("\n");
}

void ptw(char str[], int count, float f, int p, int s, int max, int Wmax){  //PRINT ONE BAR FOR A WORD

    int i,g,b;
    float a;

    g=77-p-Wmax;

    if(s==0){
        a=(float)count/tot*g;
        b=(int)a;
    }
    else if(s==1){
        a=(float)count/max*g;
        b=(int)a;
    }

        for(i=0; i<Wmax+2; i++)     //1
            printf(" ");
        printf("\u2502");
        for(i=0; i<b; i++){
            printf("\u2591");
        }
        printf("\n ");      //2
        printf("%s",str);
        for(i=0; i<=Wmax-strlen(str); i++)
            printf(" ");
        printf("\u2502");
        for(i=0; i<b; i++){
            printf("\u2591");
        }
        printf("%.2f%%\n",f);
        for(i=0; i<Wmax+2; i++)
            printf(" ");
        printf("\u2502");
        for(i=0; i<b; i++){
            printf("\u2591");
        }
        printf("\n");
        for(i=0; i<Wmax+2; i++)
            printf(" ");
        printf("\u2502");
        printf("\n");
}

void ptwU(int Wmax){        //PRINT WORD GRAPH LAST LINE
    int i;

    for(i=0; i<Wmax+2; i++)
        printf(" ");

    printf("\u2514");
    for(i=0; i<77-Wmax; i++)
        printf("\u2500");
    printf("\n");
}


int main(int argc, char **argv)
{
    if(argc==1){
        printf("No input files were given\n");
        printf("usage: %s [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n",argv[0]);
        return 0;
    }

    int i,count=0,c=0,w=0;

    for(i=1; i<argc; i++){

        if( strcmp(argv[i],"-l")==0 && (i+1)==argc ){
            printf("Not enough options for [-l]\n");
            printf("usage: %s [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n",argv[0]);
            return 0;
        }
        if( strcmp(argv[i],"-l")==0 && atoi(argv[i+1])<0 && argv[i+1][0]=='-'){
            printf("Invalid option(negative) for [-l]\n");
            printf("usage: %s [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n",argv[0]);
            return 0;
        }
        if( strcmp(argv[i],"-l")==0 && (i+1)!=argc && atoi(argv[i+1])==0 ){
	    if( strcmp(argv[i+1],"0")!=0 ){
                printf("Invalid options for [-l]\n");
                printf("usage: %s [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n",argv[0]);
                return 0;
	    }
        }
        if( argv[i][0]=='-' ){
            if( (strcmp(argv[i],"-c"))!=0 && (strcmp(argv[i],"--scaled"))!=0 && (strcmp(argv[i],"-w"))!=0 && (strcmp(argv[i],"-l"))!=0 ){
                printf("Invalid option [%s]\n",argv[i]);
                printf("usage: %s [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n",argv[0]);
                return 0;
            }
            if(strcmp(argv[i],"-c")==0)     //IF "-c" GIVEN ADD +1 TO "c"
                c++;
            if(strcmp(argv[i],"-w")==0)     //IF "-w" GIVEN ADD +1 TO "w"
                w++;
        }

        if(c!=0 && w!=0){
            printf("[-c] and [-w] cannot use together\n");
            printf("usage: %s [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n",argv[0]);
            return 0;
        }

        if(argv[i][0]=='-'){
            count++;
            if( strcmp(argv[i],"-l")==0)
                count++;
        }
        if(i+1==argc && count+1==argc){
            printf("No input files were given\n");
            printf("usage: %s [-l length] [-w | -c] [--scaled] filename1 filename2 ..\n",argv[0]);
            return 0;
        }
    }

//ARGUMENT FINISH

//
    countChar chArray[36], temp;
    FILE *infile, *outfile;
    int j,ch,pr,val=0, s=0, max=0, Wmax=0;
    float f;
    char word[100];

    for(i=1; i<argc; i++){          //IF "-l 0", PRINT NOTHING
        if( strcmp(argv[i],"-l")==0 ){
            if(atoi(argv[i+1])==0)
                return 0;
        }
    }

    for(i=1; i<argc; i++){          //IF CHECK "-l" & "--scaled"
        if( strcmp(argv[i],"-l")==0 )
            val = atoi(argv[i+1]);      //IF "-l" NOT GIVEN val=0
        if(strcmp(argv[i],"--scaled")==0)
            s=1;                        //IF "--scaled" NOT GIVEN S=0, ELSE S=1
    }

//
    //CHAR WORKING
    if(c!=0){

        for(j=0; j<26; j++){    //SET LETTER & No TO ARRAY
            chArray[j].ch=(char)(j+'a');
            chArray[j].count=0;
            chArray[j].rank=-1;
        }
        for(j=26; j<36; j++){
            chArray[j].ch=(char)(j+22);
            chArray[j].count=0;
            chArray[j].rank=-1;
        }

        for(i=1; i<argc; i++){
            if(argv[i][0]!='-' && strcmp(argv[i-1],"-l")!=0 ){
                infile= fopen(argv[i],"r");

                if(infile==NULL){
                    printf("Cannot open one or more given files\n");
                    return 0;
                }else{          //CHAR COUNT
                    while((ch=fgetc(infile))!=EOF){
                        if(isalpha(ch=tolower(ch))){
                            tot++;
                            chArray[ch-'a'].count++;
                            if(chArray[ch-'a'].rank==-1)
                                chArray[ch-'a'].rank=tot;
                        }else if(ch>='0' && ch<='9'){
                            tot++;
                            chArray[ch-22].count++;
                            if(chArray[ch-22].rank==-1)
                                chArray[ch-22].rank=tot;
                        }
                    }
                }
            }
        }

        for(i=1; i<36; i++){    //SORT ARRAY
            for(j=0; j<i; j++){
                if(chArray[j].count<chArray[i].count){
                    temp=chArray[j];
                    chArray[j]=chArray[i];
                    chArray[i]=temp;
                }
            }
        }

        for(i=1; i<36; i++){    //SORT ARRAY 1ST GIVE CHAR
            for(j=0; j<i; j++){
                if(chArray[i].count==chArray[j].count){
                    if(chArray[i].rank<chArray[j].rank){
                        temp=chArray[j];
                        chArray[j]=chArray[i];
                        chArray[i]=temp;
                    }
                }
            }
        }

        //printing CHAR//

        if(chArray[0].count==0){
            printf("No data to process\n");
            return 0;
        }

        f=(float)chArray[0].count/tot*100.0;
        max=chArray[0].count;

        if(f==100.00f)      //LEN CHAR OF 1ST CHAR PERCENTAGE
            pr=7;
        else if(f>=10.00f)
            pr=6;
        else
            pr=5;

        printf("\n");       //PRINTING START THE GRAPH
        if(val==0){
            for(i=0; i<10; i++){
                if(chArray[i].count==0)
                    break;
                else{
                    ptc( chArray[i].ch, chArray[i].count, (float)chArray[i].count/tot*100.0, pr, s, max );
                }
            }
            ptcU();
        }
        else{
            for(i=0; i<val; i++){
                if(chArray[i].count==0)
                    break;
                else{
                    ptc( chArray[i].ch, chArray[i].count, (float)chArray[i].count/tot*100.0, pr, s, max );
                }
            }
            ptcU();
        }
    }
 //

 //WORD WORKING

    else{
        outfile= fopen("out.txt","w");  //OPEN A NEW FILE "OUT.TXT"
        for(i=1; i<argc; i++){
            if(argv[i][0]!='-' && strcmp(argv[i-1],"-l")!=0 ){
                infile= fopen(argv[i],"r");
                if(infile==NULL){
                    remove("out.txt");
                    printf("Cannot open one or more given files\n");
                    return 0;
                }else{                  //  PRINT IN TO THE OUT FILE ALPHANUMERIC AND ' '
                    while((ch=fgetc(infile))!=EOF){
                        if(isalpha(ch=tolower(ch)) || (ch>='0' && ch<='9') || ch==' ' || ch=='\n'){
                            if(ch=='\n')
                                ch=' ';
                            fputc(ch,outfile);
                        }
                    }
                }
                fclose(infile);		//FILE CLOSE
            }
        }
        fclose(outfile);
        infile= fopen("out.txt","r");

      	while(fscanf(outfile,"%s",word) != EOF ){
            tot++;
            addW(word);
      	}

        if( head==NULL){        //EMPTY FILE
            printf("No data to process\n");
            return 0;
        }

        nodew *p,*q;
        int tmp,tmp1;
        char tmpc[100];

        p=head;
        int nt=1;   //NODE COUNT

        for(p=head; p->wnext!=NULL; p=p->wnext){    //NODE COUNT
            p->rank=nt;
            nt++;
        }
        p->rank=nt;

        p=head;

        for(p=head; p->wnext!=NULL; p=p->wnext){    //SORT
            for(q=p->wnext; q!=NULL; q=q->wnext){
                if(p->wcount < q->wcount){
                    tmp= p->wcount;
                    p->wcount=  q->wcount;
                    q->wcount=tmp;

                    strcpy(tmpc,p->wrd);
                    strcpy(p->wrd,q->wrd);
                    strcpy(q->wrd,tmpc);

                    tmp1= p->rank;
                    p->rank=  q->rank;
                    q->rank=tmp1;
                }
            }
        }

        p=head;
        q=head->wnext;

        for(p=head; p->wnext!=NULL; p=p->wnext){    //SORT
            for(q=p->wnext; q!=NULL; q=q->wnext){
                if(p->wcount == q->wcount){
                    if(p->rank > q->rank){
                        tmp= p->wcount;
                        p->wcount=  q->wcount;
                        q->wcount=tmp;

                        strcpy(tmpc,p->wrd);
                        strcpy(p->wrd,q->wrd);
                        strcpy(q->wrd,tmpc);

                        tmp1= p->rank;
                        p->rank=  q->rank;
                        q->rank=tmp1;
                    }
                }
            }
        }





        //PRINTING WORD

        f=(float)head->wcount/tot*100.0;
        max=head->wcount;

        if(f==100.00f)  //LEN 1ST WORD OF PERCENTAGE
            pr=7;
        else if(f>=10.00f)
            pr=6;
        else
            pr=5;

        p=head;
        int z;

        printf("\n");
        if(val==0){     //SEARCH MAX LENTH OF THE STRING
            for(i=0; i<10; i++){
                if(p->wnext == NULL){
                    z=strlen(p->wrd);
                    if(z>Wmax)
                        Wmax=z;
                    break;
                }
                else{
                    z=strlen(p->wrd);
                    if(z>Wmax)
                        Wmax=z;
                }
                p=p->wnext;
            }
        }
        else{
            for(i=0; i<val; i++){
                if(p->wnext == NULL){
                     z=strlen(p->wrd);
                    if(z>Wmax)
                        Wmax=z;
                    break;
                }else{
                    z=strlen(p->wrd);
                    if(z>Wmax)
                        Wmax=z;
                }
                p=p->wnext;
            }
        }

        //PRINTING WORD GRAPH
        p=head;
        if(val==0){     //PRINT NOT FULL SCALE
            for(i=0; i<10; i++){
                if(p->wnext == NULL){
                    ptw( p->wrd, p->wcount, (float)p->wcount/tot*100.0, pr, s, max, Wmax );
                    break;
                }else{
                    ptw( p->wrd, p->wcount, (float)p->wcount/tot*100.0, pr, s, max, Wmax );
                }
                p=p->wnext;
            }
            ptwU(Wmax);
        }
        else{       //PRINT FULL SCALE
            for(i=0; i<val; i++){
                if(p->wnext == NULL){
                    ptw( p->wrd, p->wcount, (float)p->wcount/tot*100.0, pr, s, max, Wmax );
                    break;
                }else{
                    ptw( p->wrd, p->wcount, (float)p->wcount/tot*100.0, pr, s, max, Wmax );
                }
                p=p->wnext;
            }
            ptwU(Wmax);
        }
        remove("out.txt");      //REMOVE OUT FILE
    }
//
  return 0;
}
