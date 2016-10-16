//!includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <io.h>

//!defines


//!functions
char * GetDocName  ();
char * ReadBuffer  (const char * , int * );
char * MakeStrings (char ** , const char * , int , int );
char * OutputFile  ();
int    CountLines  (char * , int );
int CompareFirst  (const void * , const void * );
void PrintStrings  (char ** , int ,char * );

using namespace std;

int main()
{
    char * filename = GetDocName();
    char * filename2 = OutputFile();

    int size = 0;
    char * buffer = ReadBuffer(filename, &size);
    int nLines = CountLines(buffer, size);
    char ** strings = (char **)calloc(nLines, sizeof(* strings));

    MakeStrings(strings, buffer, nLines, size);
    qsort(strings, nLines, sizeof (char *), CompareFirst);
    PrintStrings(strings, nLines, filename2);

    free(filename);
    //free(buffer);
    free(strings);

    return 0;
}

char * GetDocName()
{
    printf("Hello, dear user! This program sorts the strings in the document and\nprints them in another one.\nPlease, input the name of the document:\n");

    char * filename = (char *)calloc(100, sizeof(*filename));

    fgets(filename, 100, stdin);

    printf("Today we are sorting document %s", filename);

    filename[strlen(filename) -1] = '\0';

    return filename;
}

char * ReadBuffer(const char * filename, int * sz)
{
    FILE * StartDocument = fopen(filename, "r");
    assert(StartDocument);

    long size = filelength(fileno(StartDocument));
    assert(size >= 0);

    char * buffer = (char *)calloc(size, sizeof(* buffer));

    if (fread(buffer, sizeof(* buffer), size, StartDocument) == size)
        printf("Impossible to read file %s!!!\nTry again later!\n", filename);

    fclose(StartDocument);

    *sz = size;

    return buffer;
}

char * MakeStrings(char ** Strings, const char * buffer, int lines, int strlength)
{
    bool flag = false;
    int StrCount = 0, pos = 0;

    for (int i = 0; i < strlength; i++)
    {
        if (buffer[i] == '\0')
            flag = true;

        if (flag)
        {
            Strings[StrCount] = ( char * )buffer + pos;
            pos = i + 1;
            StrCount++;

            flag = false;
        }
    }
}

int CountLines(char * strings, int len)
{
    char EndOfStr = '\n';
    char * point;
    int count = 0;

    while (point = strrchr(strings, EndOfStr))
    {
        *point = '\0';
        count++;
    }

    return count;
}

int CompareFirst(const void * a, const void * b)
{
    return strcasecmp ( * ( char ** ) a, * ( char ** ) b );
}

char * OutputFile()
{
    printf("Input the filename\n where you want to printout new strings:\n");

    char * OutFilename = (char *)calloc(100, sizeof(* OutFilename));
    fgets(OutFilename, 100, stdin);
    OutFilename[strlen(OutFilename) - 1] = '\0';

    return OutFilename;
}

void PrintStrings  (char ** strings, int len, char * OutFilename)
{
    FILE * PrintFile = fopen(OutFilename, "w");
    for (int i = 0; i < len; i++)
    {
        if (!strlen(strings[i]))
            continue;
        else
            fprintf(PrintFile, "%s\n", strings[i]);
    }
}
