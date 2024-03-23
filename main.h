#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define FAIL 1
#define SUCCESS 0
#define GDMAX 20
#define GMDEX 4

//Structs
typedef struct {
    unsigned int SongID;
    char *LevelName;
    char *LevelBuffer;
    char *GmdOut;
    unsigned int GmdOutSize;
    unsigned int RawBufferSize;
    bool IsNewgrounds;
} GD_LEVEL_STRUCT;

//Constants

const char *ErrorMessages[12] = {
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

const char *Messages[6] = {
    "The file is:\0",
    "Bytes\0",
    "\nExported Successfully\0",
    "RawToGMD\n\0",
    "Size of parsed string:\0",
    "Bytes\0"

};

//Functuion prototypes
unsigned int GenerateString(GD_LEVEL_STRUCT *StructLevel);