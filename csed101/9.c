#include <stdio.h>
#include <stdlib.h>
void copy_file (FILE* infile, FILE* outfile);

int main()
{
    char filename[FILENAME_MAX];
    FILE* infile;
    FILE* outfile;
    printf("This program copies files\n");
    printf("Original file: ");
    scanf("%s", filename);
    infile = fopen(filename, "r");

    if (infile == NULL) printf("Cannot open %s\n", filename);
    else {
        printf("Copy: ");
        scanf("%s", filename);
        outfile = fopen(filename, "w");
        copy_file(infile, outfile);
        fclose(infile);
        fclose(outfile);
    }

    return 0;
}

void copy_file(FILE* infile, FILE* outfile)
{
    int c;
    while ((c = fgetc(infile)) != EOF) {
        fputs(c, outfile);
    }
}