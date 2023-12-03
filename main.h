#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

//sal2 like stuff
#define _In_
#define _Out_
#define _Inopt_
#define _In_Out_

// I prefer winapi style type names so yeah
#define INT int
#define CHAR char
#define UINT unsigned int
#define PSTR char *
#define PCSTR const char *
#define BOOL bool
#define FALSE false
#define TRUE true

#define FAIL 1
#define SUCCESS 0
#define GDMAX 20
#define GMDEX 4

//Structs
typedef struct {
    _In_ UINT uSongID;
    _In_ CHAR szLevelName[GDMAX];
    _In_ PSTR pszLevelBuffer;
    _Out_ PSTR pszGmdOut;
    _In_ size_t uGmdOutSize;
    _In_ size_t uRawBufferSize;
    _In_ BOOL bIsNewgrounds;
} GD_LEVEL_STRUCT, *PGD_LEVEL_STRUCT;

//Constants

PCSTR g_apszErrorMessages[12] = {
    "Not enough arguments. Usage: \
    \n[FILENAME]\
    \n[LEVELNAME] - Strictly ANSI name, only latin charecters\
    \n[SONGID]\
    \n[TRUE OR FALSE] - Use Newgrounds song ID\0",
    "Too many arguments. Usage: \
    \n[FILENAME]\
    \n[LEVELNAME] - Strictly ANSI name, only latin charecters\
    \n[SONGID]\
    \n[TRUE OR FALSE] - Use Newgrounds song ID.\0",
    "\nError: Such file does not exist.\0",
    "\nError: Can't read the file.\0",
    "\nCan't allocate memory to hold the original string.\0",
    "\nCan't allocate memory to hold the out string.\0",
    "\nGmd string size.\0",
    "\nThe level name is too long.\0",
    "\nFailed to read file.\0",
    "\nExport fail.\0",
    "\nInvalid song id. default songs range from 0 to 20.\0",
    "\nInvalid choice. Use TRUE or FALSE.\0"
};
//Functuion prototypes
UINT fnGenerateString(_In_Out_ PGD_LEVEL_STRUCT pstLevel);