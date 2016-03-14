#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ALPHA_SIZE  256  //26
#define  WORD_LEN   500

typedef struct n
{
    bool isEOW;
    struct n *next[ALPHA_SIZE];
}Node;

Node *CreateNode()
{
    int i;
    Node *newNode = malloc(sizeof(Node));
    newNode->isEOW = false;
    for(i=0;i<ALPHA_SIZE;i++)
        newNode->next[i] = NULL;
    return newNode;
}

void insertWord(Node *root, char word[])
{
    int i, idx;
    Node *tmp = root;
    for(i=0;word[i]!='\0';i++)
    {
        idx = word[i];// - 'a';
        if(tmp->next[idx] == NULL)
            tmp->next[idx] = CreateNode();
        tmp = tmp->next[idx];
    }
    tmp->isEOW = true;
    printf("\nInserted '%s'", word);
}

void PrintAllWords(Node *root, char prefix[])
{
    if(root->isEOW == true)
        printf("\n%s", prefix);

    int i;
    for(i=0;i<ALPHA_SIZE;i++)
    {
        if(root->next[i] != NULL)
        {
            int len = strlen(prefix);
            char *newPrefix = malloc(len+2);
            strcpy(newPrefix, prefix);
            newPrefix[len] = i;//+'a';
            newPrefix[len+1] = '\0';
            PrintAllWords(root->next[i],newPrefix);
            free(newPrefix);
        }
    }
}

void AutoSuggest(Node *root, char prefix[])
{
    int i, idx;
    for(i=0;prefix[i]!='\0';i++)
    {
        idx = prefix[i];// - 'a';
        if(root->next[idx] == NULL)
        {
            printf("\nNo sentences starting with prefix '%s'", prefix);
            return;
        }
        root = root->next[idx];
    }
    PrintAllWords(root, prefix);
}

int showMenu()
{
    int choice;
    printf("\nMENU");
    printf("\n1. Insert Sentence");
    printf("\n2. AutoSuggest Sentence");
    printf("\n3. Print All Sentences");
    printf("\n4. EXIT");
    printf("\nYour Choice: ");
    scanf("%d", &choice);
    return choice;
}

int main()
{
    int ch;
    int len;
    char word[WORD_LEN+1];
    Node *root = CreateNode();
    FILE *fp = fopen("dictionary.txt", "r");
    if(fp == NULL)
    {
        printf("\nError opening file.");
        return -1;
    }
    while(!feof(fp))
    {
        fgets(word, WORD_LEN, fp);
        // Remove NewLine Character
        len = strlen(word);
        if(word[len-2]='\n')
            word[len-2]='\0';
        insertWord(root, word);
    }
    fclose(fp);

    while(1)
    {
        ch = showMenu();
        fflush(stdin);
        switch(ch)
        {
        case 1:
            printf("\nEnter Sentence: ");
            gets(word);
            insertWord(root, word);
            break;
        case 2:
            printf("\nEnter prefix Sentence: ");
            gets(word);
            AutoSuggest(root, word);
            break;
        case 3:
            PrintAllWords(root, "");
            break;
        case 4:
            return 0;
        default:
            printf("\nBad choice...");
        }
    }

    return 0;
}
