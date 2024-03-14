#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define SIZE 15
struct opTab {
    char mnemonic[10];
    char opcode[5];
    int len;
    struct opTab *next;
} *hash_table[SIZE];

struct symTab {
    char sym[10];
    char address[10];
    struct symTab *next1;
} *hash_table2[SIZE];

struct token {
    char label[10];
    char opcode[10];
    char operand[10];
} token[40];

void init_hash() {
    for (int i = 0; i < SIZE; i++) {
        hash_table2[i] = NULL;
        hash_table[i] = NULL;
    }
}

void print_hash() {
    printf("Symbol Table:\n");
    for (int i = 0; i < SIZE; i++) {
        if (hash_table2[i] == NULL) {
            printf("---\n");
        } else {
            struct symTab *tmp = hash_table2[i];

            while(tmp!=NULL)
            {
           printf("-->%i\t%s\t%s\t", i,tmp->sym, tmp->address);
            tmp=tmp->next1;
            }

            printf("\n");
        }
    }

    printf("Opcode Table:\n");
    for (int i = 0; i < SIZE; i++) {
        if (hash_table[i] == NULL) {
            printf("---\n");
        } else {
            struct opTab *tmp = hash_table[i];

            while(tmp!=NULL)
            {
           printf("-->%i\t%s\t%s\t%d\t", i,tmp->mnemonic, tmp->opcode, tmp->len);
            tmp=tmp->next;
            }

            printf("\n");
        }
    }
}

int hash(char *m) {
    int length = strlen(m);
    int hash_value = 0;
    for (int i = 0; i < length; i++) {
        hash_value = (hash_value + m[i]) % SIZE;
    }
    //printf("%d <-- hash \n", hash_value);
    return hash_value;
}

bool hash_table_insert1(struct opTab *p, FILE *f4) {
    if (p == NULL)
        return false;

    int index = hash(p->mnemonic);
    if (index >= SIZE)
        return false;

    p->next = hash_table[index];
    hash_table[index] = p;
    fprintf(f4, "%s\t%s\t%d\n", p->mnemonic, p->opcode, p->len);
    return true;
}

bool hash_table_insert2(struct symTab *p, FILE *f5) {
    if (p == NULL)
        return false;

    int index = hash(p->sym);
    if (index >= SIZE)
        return false;

    p->next1 = hash_table2[index];
    hash_table2[index] = p;
    fprintf(f5, "%s\t%s\n", p->sym, p->address);
    return true;
}


struct opTab *hash_search1(char *name) {
    int index = hash(name);
    struct opTab *tmp = hash_table[index];
    while (tmp != NULL && strcmp(tmp->mnemonic, name) != 0) {
        tmp = tmp->next;
    }
    return tmp;
}

struct symTab *hash_search2(char *name) {
    int index = hash(name);
    struct symTab *tmp = hash_table2[index];
    while (tmp != NULL && strcmp(tmp->sym, name) != 0) {
        tmp = tmp->next1;
    }
    return tmp;
}
int main()
{
    FILE *f1,*f2,*f4,*f5;
    char line[100];
    init_hash();
    print_hash();
    f4=fopen("optab.txt","w");
    f5=fopen("symtab.txt","w");
    f1=fopen("input1.txt","r");
    f2=fopen("output.txt","w");
    int i=0;

    struct opTab LDA = {"LDA", "00", 3, NULL};
    struct opTab STL = {"STL", "14", 3, NULL};
    struct opTab JSUB = {"JSUB", "48", 3, NULL};
    struct opTab COMP = {"COMP", "28", 3, NULL};
    struct opTab JEQ = {"JEQ", "30", 3, NULL};
    struct opTab STA = {"STA", "0C", 3, NULL};
    struct opTab J = {"J", "3C", 3, NULL};
    struct opTab LDS = {"LDS", "6C", 3, NULL};
    struct opTab LDL = {"LDL", "08", 3, NULL};
    struct opTab RSUB = {"RSUB", "4C", 3, NULL};
    hash_table_insert1(&LDA,f4);
    hash_table_insert1(&STL,f4);
    hash_table_insert1(&JSUB,f4);
    hash_table_insert1(&LDL,f4);
    hash_table_insert1(&STA,f4);
    hash_table_insert1(&COMP,f4);
    hash_table_insert1(&JEQ,f4);
    hash_table_insert1(&J,f4);
    hash_table_insert1(&RSUB,f4);
    hash_table_insert1(&LDS,f4);

    unsigned int start_add,add;
    fgets(line,sizeof(line),f1);
    int x=sscanf(line,"%s %s %s",token[i].label,token[i].opcode,token[i].operand);
    printf("%s\n",token[i].opcode);
    if(strcmp(token[i].opcode,"START")==0)
    {
         start_add=strtol(token[i].operand,NULL,16);
         add=start_add;
         printf("Start of the ALP\n");
         fprintf(f2,"%x\t%s\t%s\t%s\n",add,token[i].label,token[i].opcode,token[i].operand);
         printf("%x Label:%s \t Opcode:%s\t Operand:%s\n",add,token[i].label,token[i].opcode,token[i].operand);
    }
    else
    {
        start_add=0000;
        add=0000;
    }
    fgets(line,sizeof(line),f1);
    x=sscanf(line,"%s %s %s",token[i].label,token[i].opcode,token[i].operand);
    while(strcmp(token[i].label,"END")!=0)
    {
        if(x==3)
        {
           struct symTab *t=hash_search2(token[i].label);
           if(t!=NULL)
           {
               printf("Symbol Present already!!\n Invalid opcode!\n");
           }
           else
           {
                  struct symTab *sy = malloc(sizeof(struct symTab));
                  strcpy(sy->sym, token[i].label);
                  sprintf(sy->address, "%x", add);
                  sy->next1 = NULL;
                  hash_table_insert2(sy,f5);
                  struct opTab *t=hash_search1(token[i].opcode);
                  if(t!=NULL)
                  {
                       fprintf(f2,"%x\t%s\t%s\t%s\n",add,token[i].label,token[i].opcode,token[i].operand);
                       printf("%x Label:%s     \t Opcode:%s\t Operand:%s\n",add,token[i].label,token[i].opcode,token[i].operand);
                       add=add+3;
                  }
                  else if(strcmp(token[i].opcode,"BYTE")==0)
                  {
                       char aa[10];
                       strcpy(aa,token[i].operand);
                       int len=strlen(aa);
                       len=len-3;
                       fprintf(f2,"%x\t%s\t%s\t%s\n",add,token[i].label,token[i].opcode,token[i].operand);
                       printf("%x Label:%s     \t Opcode:%s\t Operand:%s\n",add,token[i].label,token[i].opcode,token[i].operand);
                       if(token[i].operand[0]=='C')
                       {
                           add=add+len;
                       }
                       else
                       {
                           add=add+(len/2);
                       }

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
                       fprintf(f2,"%x\t%s\t%s\t%s\n",add,token[i].label,token[i].opcode,token[i].operand);
                       printf("%x Label:%s     \t Opcode:%s\t Operand:%s\n",add,token[i].label,token[i].opcode,token[i].operand);
                       add=add+3;
                  }
                  else
                  {
                       printf("Invalid Opcode!\n");
                  }
           }


        }
         else if(x==2)
        {
           struct opTab *t=hash_search1(token[i].label);

           if(t!=NULL)
           {
              fprintf(f2,"%x\t%s%s\t%s\n",add,"\t",token[i].label,token[i].opcode);
              printf("%x Label:%s \t Opcode:%s\t Operand:%s\n",add,"\t",token[i].label,token[i].opcode);
              add=add+3;
           }
           else
            printf("Invalid Opcode!\n");
       }
        else if(x==1)
       {
           struct opTab *t=hash_search1(token[i].label);
           if(t!=NULL)
           {
              fprintf(f2,"%x\t%s\t%s\t%s\n",add,"\t",token[i].label,"\t");
              printf("%x Label:%s \t Opcode:%s\t Operand:%s\n",add,"\t",token[i].label,"\t");
              add=add+3;
           }
       }
        fgets(line,sizeof(line),f1);
        x=sscanf(line,"%s %s %s",token[i].label,token[i].opcode,token[i].operand);
    }
    print_hash();
    fclose(f1);
    fclose(f2);
    fclose(f4);
    fclose(f5);

  return 0;
}
