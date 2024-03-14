include<stdio.h>
#include<string.h>
#include<stdbool.h>
#define SIZE 49
#define MAX_NAME 10
typedef struct opTab
{
   char mnemonic[10];
   char opcode[5];
   int len;
   struct opTab *next;
}opTab;

typedef struct symTab
{
    char sym[10];
    char address[10];
    struct symTab *next1;
}symTab;
int hash(char *mnemonic)
{
    int length=strlen(mnemonic);
    int hash_value=1;
    for(int i=0;i<length;i++)
    {
        hash_value=hash_value+mnemonic[i];
        hash_value=(hash_value*mnemonic[i])%SIZE;
    }
    printf("%d<-- hash \n",hash_value);
     return hash_value;
}
opTab *hash_table[SIZE];
symTab *hash_table2[SIZE];
void init_hash()
{
    for(int i=0;i<SIZE;i++)
    {
        hash_table[i]=NULL;
        hash_table2[i]=NULL;
    }
}
void print_hash()
{
    for(int i=0;i<SIZE;i++)
    {
        if(hash_table[i]==NULL)
        {
            printf("---\n");
        }
        else
        {

            opTab *tmp=hash_table[i];
            while(tmp!=NULL)
            {

           printf("%i\t%s\t%s\t%d",i,tmp->mnemonic, tmp->opcode, tmp->len);
            tmp=tmp->next;
            }

            printf("\n");

        }
    }

}

void print_hash1()
{
    for(int i=0;i<SIZE;i++)
    {
        if(hash_table2[i]==NULL)
        {
            printf("---\n");
        }
        else
        {

            symTab *tmp=hash_table2[i];
            while(tmp!=NULL)
            {
           printf("%i\t%s\t%s\t", i,tmp->sym, tmp->address);
            tmp=tmp->next1;
            }

            printf("\n");

        }
    }
}
bool hash_table_insert(opTab *p)
{
    if(p==NULL)
        return false;
    int index=hash(p->mnemonic);
    p->next=hash_table[index];
    hash_table[index]=p;
    return true;
}
bool hash_table_insert2(symTab *p,FILE *f3)
{
    printf("%s-------------------------------------%s\n",p->sym,p->address);
    fprintf(f3,"%s\t%s\n",p->sym,p->address);
    if(p==NULL)
        return false;
    int index=hash(p->sym);
    p->next1=hash_table2[index];
    hash_table2[index]=p;
        printf("%s---------------------------------=----%s\n",hash_table2[index]->sym,hash_table2[index]->address);


    return true;
}

opTab *hash_search(char *name)
{
    int index=hash(name);
    opTab *tmp=hash_table[index];
    while(tmp!=NULL&& strcmp(tmp->mnemonic,name)!=0)
    {
        tmp=tmp->next;
    }
   return tmp;
}
symTab *hash_search1(char *name)
{
    int index=hash(name);
    symTab*tmp=hash_table2[index];
    while(tmp!=NULL&& strcmp(tmp->sym,name)!=0)
    {
        tmp=tmp->next1;
    }
   return tmp;
}
struct token
{
    char label[10];
    char opcode[10];
    char operand[10];
} token[40];

int main()
{
unsigned  int z;


    FILE *f1,*f2,*f3;

    init_hash();
    print_hash();
    opTab LDA={.mnemonic="LDA",.opcode="00",.len=3};
    opTab LDS={.mnemonic="LDS",.opcode="6C",.len=3};
    opTab LDX={.mnemonic="LDX",.opcode="04",.len=3};
    opTab LDT={.mnemonic="LDT",.opcode="74",.len=3};
    opTab LDF={.mnemonic="LDF",.opcode="70",.len=3};
    opTab STA={.mnemonic="STA",.opcode="0C",.len=3};
    opTab ADD={.mnemonic="ADD",.opcode="18",.len=3};
    opTab COMP={.mnemonic="COMP",.opcode="28",.len=3};
    opTab JLT={.mnemonic="JLT",.opcode="38",.len=3};
    opTab LDCH={.mnemonic="LDCH",.opcode="50",.len=3};
    opTab STC={.mnemonic="STCH",.opcode="54",.len=3};
    opTab LDL={.mnemonic="LDL",.opcode="0C",.len=3};
    opTab JSUB={.mnemonic="JSUB",.opcode="0C",.len=3};
    opTab J={.mnemonic="J",.opcode="0C",.len=3};
    opTab JEQ={.mnemonic="JEQ",.opcode="0C",.len=3};
        opTab STL={.mnemonic="STL",.opcode="54",.len=3};




printf("-------------------------------------------\n");
    hash_table_insert(&LDA);
        hash_table_insert(&LDL);
    hash_table_insert(&JSUB);
    hash_table_insert(&J);
    hash_table_insert(&JEQ);
    hash_table_insert(&STL);



    hash_table_insert(&LDS);
    hash_table_insert(&LDX);
    hash_table_insert(&LDT);
    hash_table_insert(&STA);
    hash_table_insert(&COMP);
    hash_table_insert(&JLT);
    hash_table_insert(&ADD);
    hash_table_insert(&LDF);
    hash_table_insert(&LDCH);
    hash_table_insert(&STC);
    print_hash();
    char line[100];

    f1=fopen("input1.txt","r");
    f2=fopen("output.txt","w");
    f3=fopen("symtab.txt","w");
    int i=0,j=0;
    unsigned int add;
    while(fgets(line,sizeof(line),f1)!=NULL)
  {

       int x=sscanf(line,"%s %s %s",token[i].label,token[i].opcode,token[i].operand);

       if(strcmp(token[i].opcode,"START")==0)
       {


           add=strtol(token[i].operand,NULL,16);
            unsigned int z=add;
      printf("Start of the ALP\n");
           fprintf(f2,"%x\t%s\t%s\t%s\n",add,token[i].label,token[i].opcode,token[i].operand);
           printf("%x Label:%s \t Opcode:%s\t Operand:%s\n",add,token[i].label,token[i].opcode,token[i].operand);
           j=1;
           /*add=token[i].operand;
           printf("%s\n",add);*/
       }
       else
       {
           if(j==0)
           {
               unsigned int z=0000;
               printf("%u",z);
                add=0000;
                j=1;
           }

       }
       if(strcmp(token[i].label,"END")==0)
       {
            fprintf(f2,"%x\t%s\t%s\t%s\n",add,"",token[i].label,token[i].opcode);
            printf("%x Label:%s     \t Opcode:%s\t Operand:%s\n",add,"",token[i].label,token[i].opcode);
            printf("End of program");
           break;
       }
       if(x==3)
       {printf("hi");

           symTab *t=hash_search1(token[i].label);
           if(t==NULL)
           {
               char hex[15];
               sprintf(hex,"%X",add);
               printf("%s %s \n",token[i].label,hex);
                symTab ST;

                strcpy(ST.sym,token[i].label);
                strcpy(ST.address,hex);
                printf("%s----------%s\n",ST.sym,ST.address);

        hash_table_insert2(&ST,f3);

                 if(i==0)
           {

           }

           else if(strcmp(token[i].opcode,"BYTE")==0){

                char aa[10];
           strcpy(aa,token[i].operand);
           int len=strlen(aa);
           len=len-3;
            fprintf(f2,"%x\t%s\t%s\t%s\n",add,token[i].label,token[i].opcode,token[i].operand);
            printf("%x Label:%s     \t Opcode:%s\t Operand:%s\n",add,token[i].label,token[i].opcode,token[i].operand);


           add=add+len;
           }

           else if(strcmp(token[i].opcode,"RESB")==0)
           {
              int y=token[i].operand;
              unsigned int w=strtol(y,NULL,10);

               fprintf(f2,"%x\t%s\t%s\t%s\n",add,token[i].label,token[i].opcode,token[i].operand);
            printf("%x Label:%s     \t Opcode:%s\t Operand:%s\n",add,token[i].label,token[i].opcode,token[i].operand);
            add=add+w;
           }
           else if(strcmp(token[i].opcode,"RESW")==0)
           {
              int y=token[i].operand;
              unsigned int w=strtol(y,NULL,10);
              w=w*3;

               fprintf(f2,"%x\t%s\t%s\t%s\n",add,token[i].label,token[i].opcode,token[i].operand);
            printf("%x Label:%s     \t Opcode:%s\t Operand:%s\n",add,token[i].label,token[i].opcode,token[i].operand);
            add=add+w;
           }
           else if(strcmp(token[i].opcode,"WORD")==0)
           {
              int y=token[i].operand;
              unsigned int w=strtol(y,NULL,10);


               fprintf(f2,"%x\t%s\t%s\t%s\n",add,token[i].label,token[i].opcode,token[i].operand);
            printf("%x Label:%s     \t Opcode:%s\t Operand:%s\n",add,token[i].label,token[i].opcode,token[i].operand);
            add=add+w;



           }


           else{
                opTab *t=hash_search(token[i].opcode);
                if(t!=NULL){
             fprintf(f2,"%x\t%s\t%s\t%s\n",add,token[i].label,token[i].opcode,token[i].operand);
            printf("%x Label:%s \t Opcode:%s\t Operand:%s\n",add,token[i].label,token[i].opcode,token[i].operand);


           add=add+3;
           }
           else{
            printf("Opcode not found!\n");
           }

           }
           }
           else
           {
               printf("Label Already found!\n");


       }}
       else if(x==2)
       {
           opTab *t=hash_search(token[i].label);
           if(t!=NULL){
             fprintf(f2,"%x\t%s%s\t%s\n",add,"\t",token[i].label,token[i].opcode);
            printf("%x Label:%s \t Opcode:%s\t Operand:%s\n",add,"\t",token[i].label,token[i].opcode);
           add=add+3;
           }
           else{
            printf("opcode not found!\n");
           }

       }
        else if(x==1)
       {
           opTab *t=hash_search(token[i].label);
           if(t!=NULL){
            fprintf(f2,"%x\t%s\t%s\t%s\n",add,"\t",token[i].label,"\t");
            printf("%x Label:%s \t Opcode:%s\t Operand:%s\n",add,"\t",token[i].label,"\t");
            add=add+3;
           }
           else{
            printf("Opcode not found");
           }
       }
       i++;

    }


print_hash1();
print_hash();
printf("%d--",z);
printf("%d--",add);
fclose(f3);
  return 0;

}
