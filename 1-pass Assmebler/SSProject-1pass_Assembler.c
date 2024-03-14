#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

int a1 = 0;

struct token {
    char label[10];
    char opcode[10];
    char operand[10];
} token[40];

struct HeaderRecord {
    char programName[8];
    char startingAddress[8];
    char programLength[9];
} header;

struct TextRecord {
    char startAddress[10];
    char length[5];
    char objectCode[70];
} textRecords[30], textRecords1[10];

struct LinkedListNode {
    char address[10];
    struct LinkedListNode *next;
};

struct SymbolTableEntry {
    char name[10];
    char value[10];
    struct LinkedListNode *linkedList;
};

struct SymbolTableEntry symtab[100];

struct SymbolTableEntry *searchSymbolTable(struct SymbolTableEntry symtab[], char *name) {
    for (int l = 0; l < a1; l++) {
        if (strcmp(symtab[l].name, name) == 0) {
            return &symtab[l];
        }
    }
    return NULL;
}

int searchIndex(char *opr) {
    int oprlen = strlen(opr);
    for (int c = 0; c < oprlen; c++) {
        if (opr[c] == ',')
            return 1;
    }
    return 0;
}

void freeLinkedList(struct LinkedListNode *head) {
    struct LinkedListNode *current = head;
    while (current != NULL) {
        struct LinkedListNode *nextNode = current->next;
        free(current);
        current = nextNode;
    }
}
void displayLinkedList(const struct LinkedListNode *head) {
    const struct LinkedListNode *current = head;

    printf("Linked List: ");
    while (current != NULL) {
        printf("%s->", current->address);
        current = current->next;
    }
    printf("\n");
}
void showSymbolTable(struct SymbolTableEntry symtab[])
{
    for(int l=0;l<a1;l++)
    {

    if(strcmp(symtab[l].name,"")==0)
    {

    }
    else{
    printf("Name: %s\n", symtab[l].name);
    printf("Value: %s\n", symtab[l].value);
     displayLinkedList(symtab[l].linkedList);

    printf("\n");
    }

    }
}
int searchOpcodeTable(FILE *f2, char *opcode, char *mnemonic) {
    char currentOpcode[10];
    char currentMnemonic[10];

    rewind(f2);

    while (fscanf(f2, "%9s %9s", currentOpcode, currentMnemonic) == 2) {
        if (strcmp(currentOpcode, opcode) == 0) {
            strcpy(mnemonic, currentMnemonic);
            return 1;
        }
    }

    return 0;
}

void insertIntoLinkedList(struct LinkedListNode **list, char *address) {
    struct LinkedListNode *newNode = (struct LinkedListNode *)malloc(sizeof(struct LinkedListNode));
    strcpy(newNode->address, address);
    newNode->next = NULL;

    if (*list == NULL) {
        *list = newNode;
    } else {
        struct LinkedListNode *current = *list;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

void asciiToHex(const char *ascii, char *hex) {
    for (int i = 0; i < strlen(ascii); ++i) {
        sprintf(hex + 2 * i, "%02X", ascii[i]);
    }
}

void writeTextRecord(struct TextRecord *record, FILE *f3) {
    if (strlen(record->objectCode) > 0) {
        fprintf(f3, "%s%s%s\n", record->startAddress, record->length, record->objectCode);
    }
}

void insertIntoSymbolTable(struct SymbolTableEntry symtab[], char *label1, char *value1, struct LinkedListNode *linkedList) {
    int g = 0;
    for (int l = 0; l < a1; l++) {
        if (strcmp(symtab[l].name, label1) == 0) {
            printf("Duplicate symbol");
            g = 1;
        }
    }
    if (g != 1) {
        strcpy(symtab[a1].name, label1);
        strcpy(symtab[a1].value, value1);

        symtab[a1].linkedList = linkedList;
        a1++;
    }
}

int main() {
    int j = 0, i = 0, k = 0,m=0;
    int store[10];
    char line[100];
    FILE *f1 = fopen("input.txt", "r");
    FILE *f2 = fopen("optab.txt", "r");
    FILE *f3 = fopen("objectProgram.txt", "w");

    fgets(line, sizeof(line), f1);
    int x = sscanf(line, "%06s %s %s", token[i].label, token[i].opcode, token[i].operand);
    unsigned int loc_ctr, lc1;

    if (strcmp(token[i].opcode, "START") == 0) {
        loc_ctr = strtoul(token[i].operand, NULL, 16);
    } else {
        loc_ctr = 0000;
    }
    lc1 = loc_ctr;
    char hex_string[10];
    sprintf(hex_string, "%06x", loc_ctr);
    insertIntoSymbolTable(symtab, token[i].label, hex_string, NULL);
    showSymbolTable(symtab);
    printf("--------------------------------------------------------------------------------------\n");





    char stAd[20];
    sprintf(stAd, "%06x", loc_ctr);
    strcpy(header.programName, "H^");
    strcat(header.programName, token[i].label);
    char temp[100];
    strcpy(temp, "^");
    strcat(temp, stAd);
    strcpy(header.startingAddress, temp);
    fprintf(f3, "%s%s%s\n", header.programName, header.startingAddress, "^000000");
    fgets(line, sizeof(line), f1);
    x = sscanf(line, "%06s %s %s", token[i].label, token[i].opcode, token[i].operand);

    textRecords[0] = (struct TextRecord){"", "", ""};
    snprintf(textRecords[0].startAddress, sizeof(textRecords[0].startAddress), "T^%06x^", loc_ctr);

    char objectCode[10];
    while (strcmp(token[i].label, "END") != 0 || strcmp(token[i].opcode, "END") != 0) {
        int x = sscanf(line, "%s %s %s", token[i].label, token[i].opcode, token[i].operand);
        if (strcmp(token[i].label, "END") == 0 || strcmp(token[i].opcode, "END") == 0)
            break;
        char searchOpcode[4];
        char opr[10];
        if (x == 3) {
            struct SymbolTableEntry *labelEntry = NULL;
            labelEntry = searchSymbolTable(symtab, token[i].label);

            if (labelEntry != NULL) {
                if (strcmp(labelEntry->value, "") == 0) {
                    char hex_string[10];
                    sprintf(hex_string, "%06x", loc_ctr);
                    strcpy(labelEntry->value, hex_string);

                    struct LinkedListNode *currentNode = labelEntry->linkedList;
                    while (currentNode != NULL) {
                        textRecords1[k] = (struct TextRecord){"", "", ""};
                        snprintf(textRecords1[k].startAddress, sizeof(textRecords1[k].startAddress), "T^%06s", currentNode->address);
                        snprintf(textRecords1[k].length, sizeof(textRecords1[k].length), "^%02s", "02");
                        char sm[5];
                        strcpy(sm, labelEntry->value + 2);
                        snprintf(textRecords1[k].objectCode, sizeof(textRecords1[k].objectCode), "^%s", sm);
                        store[m]=k;
                        m++;
                        k++;
                        currentNode = currentNode->next;
                    }

                    freeLinkedList(labelEntry->linkedList);
                    labelEntry->linkedList = NULL;
                }
            } else {
                char hex_string[10];
                sprintf(hex_string, "%06x", loc_ctr);
                insertIntoSymbolTable(symtab, token[i].label, hex_string, NULL);
                showSymbolTable(symtab);
                  printf("--------------------------------------------------------------------------------------\n");

            }

            strcpy(searchOpcode, token[i].opcode);
            strcpy(opr, token[i].operand);
        } else if (x == 2) {
            strcpy(searchOpcode, token[i].label);
            strcpy(opr, token[i].opcode);
        } else {
            strcpy(searchOpcode, token[i].label);
            strcpy(opr, "");
        }

        char searchMnemonic[10];
        char aa[10];

        if (searchOpcodeTable(f2, searchOpcode, searchMnemonic)) {
            int z = searchIndex(opr);
            if (z == 1) {
                int oprlen = strlen(opr);
                char newop[10];
                int c1 = 0;
                for (int c = 0; c < oprlen; c++) {
                    if (opr[c] != ',' && opr[c] != 'X') {
                        newop[c1] = opr[c];
                        c1++;
                    }
                }
                strcpy(opr, newop);
            }
            struct SymbolTableEntry *labelEntry = NULL;
            labelEntry = searchSymbolTable(symtab, opr);

            if (labelEntry != NULL) {
                if (strcmp(labelEntry->value, "") != 0) {
                    strcpy(aa, labelEntry->value + 2);
                    if (z == 1) {
                        char onechar = aa[0];
                        int charint = onechar - '0';
                        if (charint == 0)
                            aa[0] = '8';
                        else if (charint == 1)
                            aa[0] = '9';
                        else if (charint == 2)
                            aa[0] = 'a';
                        else if (charint == 3)
                            aa[0] = 'b';
                    }
                } else {
                    struct LinkedListNode *newNode = (struct LinkedListNode *)malloc(sizeof(struct LinkedListNode));
                    unsigned int s = loc_ctr + 1;
                    char hex_string[10];
                    sprintf(hex_string, "%06x", s);
                    strcpy(newNode->address, hex_string);

                    newNode->next = NULL;

                    if (labelEntry->linkedList == NULL) {
                        labelEntry->linkedList = newNode;
                    } else {
                        struct LinkedListNode *current = labelEntry->linkedList;
                        while (current->next != NULL) {
                            current = current->next;
                        }
                        current->next = newNode;
                    }
                    strcpy(aa, "0000");
                }
            } else {
                struct LinkedListNode *newNode = (struct LinkedListNode *)malloc(sizeof(struct LinkedListNode));
                unsigned int s = loc_ctr + 1;
                char hex_string[10];
                sprintf(hex_string, "%06x", s);
                strcpy(newNode->address, hex_string);
                newNode->next = NULL;
                insertIntoSymbolTable(symtab, opr, "", newNode);
                showSymbolTable(symtab);
                  printf("--------------------------------------------------------------------------------------\n");

                strcpy(aa, "0000");
            }

            strcpy(objectCode, searchMnemonic);
            strcat(objectCode, aa);
            loc_ctr = loc_ctr + 3;
        } else if (strcmp(searchOpcode, "WORD") == 0) {
            int operandValue = (int)strtol(opr, NULL, 16);
            loc_ctr += 3;
            snprintf(objectCode, sizeof(objectCode), "%06X", operandValue);
        } else if (strcmp(searchOpcode, "RESW") == 0) {
            unsigned int lo = strtoul(token[i].operand, NULL, 10);
            loc_ctr = loc_ctr + (lo * 3);
            if (strcmp(textRecords[j].objectCode, "^") == 0) {
            } else {
                int len = strlen(textRecords[j].objectCode);
                int f = 0;
                int count = 0;
                while (textRecords[j].objectCode[f] != '\0') {
                    if (textRecords[j].objectCode[f] != '^')
                        count++;
                    f++;
                }
                count = count / 2;
                sprintf(textRecords[j].length, "%02x^", count);

                if (strcmp(textRecords[j].objectCode, "") != 0) {

                    writeTextRecord(&textRecords[j], f3);
                      for(int n=0;n<m;n++)
                        {
                            int ar=store[n];
                            writeTextRecord(&textRecords1[ar], f3);

                        }
                        m=0;
                }

                j++;
                textRecords[j] = (struct TextRecord){"", "", ""};
                snprintf(textRecords[j].startAddress, sizeof(textRecords[j].startAddress), "T^%06x", loc_ctr);
                strcpy(textRecords[j].objectCode,"");

            }
        } else if (strcmp(searchOpcode, "RESB") == 0) {
            int y = token[i].operand;
            unsigned int lo = strtoul(token[i].operand, NULL, 10);
            loc_ctr = loc_ctr + lo;
            textRecords[j] = (struct TextRecord){"", "", ""};
                snprintf(textRecords[j].startAddress, sizeof(textRecords[j].startAddress), "T^%06x^", loc_ctr);
            if (strcmp(textRecords[j].objectCode, "") == 0) {
            } else {
                int len = strlen(textRecords[j].objectCode);
                int f = 0;
                int count = 0;
                while (textRecords[j].objectCode[f] != '\0') {
                    if (textRecords[j].objectCode[f] != '^')
                        count++;
                    f++;
                }
                count = count / 2;
                sprintf(textRecords[j].length, "%02x^", count);
                if (strcmp(textRecords[j].objectCode, "") != 0) {

                    writeTextRecord(&textRecords[j], f3);
                      for(int n=0;n<m;n++)
                        {
                            int ar=store[n];
                            writeTextRecord(&textRecords1[ar], f3);

                        }
                        m=0;
                }
                j++;
                textRecords[j] = (struct TextRecord){"", "", ""};
                snprintf(textRecords[j].startAddress, sizeof(textRecords[j].startAddress), "T^%06x^", loc_ctr);
                //strcpy(textRecords[j].objectCode,"");

            }
        } else if (strcmp(searchOpcode, "BYTE") == 0) {
            int constantLength = strlen(opr) - 3;

            if (opr[0] == 'X') {
                char hexValue[5];
                sscanf(opr, "X'%[^']'", hexValue);
                loc_ctr = loc_ctr + (constantLength / 2);
                strcpy(objectCode, hexValue);
            } else {
                char stringValue[10];
                sscanf(opr, "C'%[^']'", stringValue);
                asciiToHex(stringValue, objectCode);
                loc_ctr = loc_ctr + constantLength;
            }
        }
          char ss[2];
    strcpy(ss, "^");
    if (strlen(objectCode) > 0) {
    strcat(objectCode, ss);
}
//strcat(objectCode, ss);

    if (strlen(textRecords[j].objectCode) + strlen(objectCode) > 71) {
        if (strcmp(textRecords[j].objectCode, "^") == 0) {

        } else {
            int len = strlen(textRecords[j].objectCode);
            int f = 0;
            int count = 0;

            while (textRecords[j].objectCode[f] != '\0') {
                if (textRecords[j].objectCode[f] != '^')
                    count++;
                f++;
            }

            count = count / 2;
            sprintf(textRecords[j].length, "%02x^", count);

            if (strcmp(textRecords[j].objectCode, "^") != 0) {
                writeTextRecord(&textRecords[j], f3);
                  for(int n=0;n<m;n++)
                        {
                            int ar=store[n];
                            writeTextRecord(&textRecords1[ar], f3);

                        }
                        m=0;
            }
        }

        j++;
        textRecords[j] = (struct TextRecord){"", "", ""};
        snprintf(textRecords[j].startAddress, sizeof(textRecords[j].startAddress), "T^%06x^", loc_ctr);

    }

    strcat(textRecords[j].objectCode, objectCode);
    i++;
    fgets(line, sizeof(line), f1);
}

if (strcmp(textRecords[j].objectCode, "^") == 0) {

} else {
    int len = strlen(textRecords[j].objectCode);
    int f = 0;
    int count = 0;

    while (textRecords[j].objectCode[f] != '\0') {
        if (textRecords[j].objectCode[f] != '^')
            count++;
        f++;
    }

    count = count / 2;
    sprintf(textRecords[j].length, "%02x^", count);

    if (strcmp(textRecords[j].objectCode, "^") != 0) {
        writeTextRecord(&textRecords[j], f3);
          for(int n=0;n<m;n++)
                        {
                            int ar=store[n];
                            writeTextRecord(&textRecords1[ar], f3);

                        }
                        m=0;
    }
}

snprintf(header.programLength, sizeof(header.programLength), "^%06x", loc_ctr-lc1);
fprintf(f3, "%s^%06x\n", "E", lc1);


printf("End of 1-PASS ASSEMBLER\nSee the object program in objectProgram File\n");
fclose(f1);
fclose(f2);
fclose(f3);
f3=fopen("objectProgram.txt","r+");
fprintf(f3, "%s%s%s\n", header.programName, header.startingAddress, header.programLength);
fclose(f3);
return 0;
}
