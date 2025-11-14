#include <stdio.h>
#include <string.h>
#include <ctype.h>

char key[20][20] = {"int", "void", "float", "char", "if", "else", "for", "while"};

int main()
{
    FILE *fp;
    char c, word[20], dig[10];
    int i = 0, j, flag = 0, d = 0;

    fp = fopen("input.txt", "r");
    if (fp == NULL)
    {
        printf("Error: Cannot open input file.\n");
        return 1;
    }

    while ((c = getc(fp)) != EOF)
    {
        // ---------- WORDS / IDENTIFIERS / KEYWORDS ----------
        if (isalpha(c) || c == '_')
        {
            i = 0;
            while (isalpha(c) || c == '_' || isdigit(c))
            {
                word[i++] = c;
                c = getc(fp);
            }
            word[i] = '\0';

            // Push back last read character for next iteration
            ungetc(c, fp);

            flag = 0;
            for (j = 0; j < 8; j++)
            {
                if (strcmp(word, key[j]) == 0)
                {
                    flag = 1;
                    break;
                }
            }

            if (flag)
                printf("Keyword: %s\n", word);
            else
                printf("Identifier: %s\n", word);
        }

        // ---------- NUMERIC CONSTANTS ----------
        else if (isdigit(c))
        {
            d = 0;
            while (isdigit(c))
            {
                dig[d++] = c;
                c = getc(fp);
            }
            dig[d] = '\0';
            ungetc(c, fp);
            printf("Constant: %s\n", dig);
        }

        // ---------- OPERATORS ----------
        else if (c == '+' || c == '-' || c == '*' || c == '/')
        {
            printf("Operator: %c\n", c);
        }

        // ---------- PUNCTUATION ----------
        else if (c == '(' || c == ')' || c == '{' || c == '}' || c == ';' || c == ',')
        {
            printf("Punctuation: %c\n", c);
        }
    }

    fclose(fp);
    return 0;
}
