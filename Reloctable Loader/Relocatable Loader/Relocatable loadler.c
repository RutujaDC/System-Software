#include<stdio.h>
#include<string.h>
void hexToBinary(char hexChar, char *binaryString) {
    int value;

    sscanf(&hexChar, "%1x", &value);
    for (int i = 3; i >= 0; --i) {
        binaryString[i] = (value & 1) + '0';
        value >>= 1;
    }

    binaryString[4] = '\0';
};
int main()
{
    char binaryString[9],b[9],binaryString1[9];
    FILE *f2,*f3;
    f2=fopen("loader_file.txt","w");
    printf("Read OS address\n");
    unsigned int aa;
    scanf("%x",&aa);
   // printf("%x\n",aa);
    FILE *f1;
    char line[1000],line2[10],line3[10];
    f1=fopen("object_program.txt","r");
    f3=fopen("object_program.txt","r");
    char l[10],l2[7],l3[3];
    while(fgets(l,sizeof(l),f3)!=NULL)
    {
        if(l[0]=='M')
            break;
    }
    printf("%s\n",l);
    strncpy(l2,l + 1,6 );
    strncpy(l3,l+7,3);
  unsigned int ll;

sscanf(l2, "%x", &ll);


    fscanf(f1,"%s",line);
    strncpy(line2, line + 1, 6);
    line2[6]='\0';
    printf("Name of the program :%s\n",line2);
    strncpy(line3, line +7, 6);
    line3[6]='\0';
    unsigned int li;

    sscanf(line3, "%x", &li);
    printf("Start Address of program :%s\n",line3);
    unsigned int add,add1;
    add=strtol(line3,NULL,16);
    add1=strtol(line3,NULL,16);
    //printf("%x-%x",add1,add);
    strncpy(line2, line + 13, 6);
    line2[6]='\0';
    printf("Length of program :%s\n",line2);
    fscanf(f1,"%s",line);

add=aa;
   // printf("==%x\n",add);

    while(line[0]!='E')
    {
         while(line[0]=='T')
         {
              printf("Text record-%s\n",line);
        strcpy(line2, line + 9);
        int i=0;
        char by[3],by2[3];

    while(line2[i]!='\0')
        {

            strncpy(by,line2 + i,2 );

            char str[9];

           // printf("\n%x--%x\n",ll,add1);
             if(ll==add1)
            {

                char z[2];
                strncpy(z,line2+i,1);//printf("%s..",z);
                strncpy(by2,line2+ i+1,5);//printf("gi");
              //  printf("%s===\n",by2);

                    unsigned int t;
                    unsigned int t1;
                    sscanf(by2, "%x", &t1);
                    // Convert hexadecimal string to integer
                   // printf("%x==",li);
                    if (li != 0) {
                            //printf("djfjkd");
                        t1 = t1 - li;

                       // printf("%x-----\n",t1);
                    }
                    t = t1 + aa;
                   // printf("%05x---\n", t);
                    char str[6];
                    sprintf(str, "%05X", t);
                if(z[0]=='0')
                {
                  strcpy(b,"0000");

               }
                 else
                 hexToBinary(z, b);
                //  printf("%s\n",z);
                //  printf("%s--]]",b);
                //  printf("%c\n",str[0]);
                 hexToBinary(str[0],binaryString );
                  strcat(b,binaryString);
               //  printf("--%s,,\n",b);
                      printf("%06x  %s\n",add,b);
                      fprintf(f2,"%06x  %s\n",add,b);
                      add=add+1;
                      add1=add1+1;

            for (int c = 1; c < strlen(str); c=c+2) {

                          //printf("%s===", binaryString);

                            hexToBinary(str[c], binaryString);

                            hexToBinary(str[c+1], binaryString1);
                          strcat(binaryString,binaryString1);
                          // printf("%s,,\n",binaryString);
                      printf("%06x %s\n",add,binaryString);
                      fprintf(f2,"%06x %s\n",add,binaryString);
                      add=add+1;
                      add1=add1+1;

                      }
                      i=i+4;



        }
        else{
        {

         for (int j = 0; j < strlen(by); ++j) {

                          //printf("%s===", binaryString);
                          if(j==0)
                            hexToBinary(by[j], binaryString);
                          else if(j==1)
                            hexToBinary(by[j], binaryString1);

                      }
                      strcat(binaryString,binaryString1);
                      printf("%06x  %s\n",add,binaryString);
                      fprintf(f2,"%06x  %s\n",add,binaryString);
                      add=add+1;
                      add1=add1+1;
            }}




i=i+2;
        }

        fscanf(f1,"%s",line);
         }




    fclose(f1);
    fclose(f2);
    return 0;
}
}
