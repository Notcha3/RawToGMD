#include "main.h"

int main(int argc, char *argv[]) {

    if(argc<5) {
        printf(
            "%s\n%s",
            Messages[3],
            ErrorMessages[0]
        );
        return EXIT_FAILURE;
    }

    if(argc>5) {
        printf(
            "%s\n%s",
            Messages[3],
            ErrorMessages[1]
        );
        return EXIT_FAILURE;
    }

    GD_LEVEL_STRUCT stGdLevel;

    if(strcmp(
        argv[4],
        "TRUE"
    ) == 0)
            stGdLevel.IsNewgrounds = true;

    else if(strcmp(
        argv[4],
        "FALSE"
        ) == 0)
            stGdLevel.IsNewgrounds = false;
    else {
        puts(ErrorMessages[11]);
        return EXIT_FAILURE;
    }

    strcpy(
        stGdLevel.LevelName, 
        argv[2]
    );

    if(strlen(stGdLevel.LevelName) > 20) {
        puts(ErrorMessages[7]);
        return EXIT_FAILURE;
    }
    stGdLevel.SongID = 0;
    stGdLevel.SongID = atoi(argv[3]);

    FILE *File = fopen(
        argv[1],
        "r\0"
    );

    if(File != NULL) {
        //Get file size to allocate a buffer
        if(fseek(
             File,
             0,
             SEEK_END
             ) == 0) {
             stGdLevel.RawBufferSize = ftell(File);
             rewind(File);

             printf(
                "\n%s\t%u\t%s", 
                Messages[0], 
                stGdLevel.RawBufferSize, 
                Messages[1]
                );

                stGdLevel.LevelBuffer = malloc(stGdLevel.RawBufferSize);
                
                if(stGdLevel.LevelBuffer == NULL) {
                    puts(ErrorMessages[4]);
                    return EXIT_FAILURE;
                }

                if (fread(
                    stGdLevel.LevelBuffer,
                    1,
                    stGdLevel.RawBufferSize,
                    File
                ) < 0) {
                    puts(ErrorMessages[6]);
                    fclose(File);
                    return EXIT_FAILURE;
                }

                unsigned int StringStatus = GenerateString(&stGdLevel);
                
                fclose(File);

                free(stGdLevel.LevelBuffer);

                if(StringStatus) return EXIT_FAILURE;;

                char FileNameWithEx[GDMAX + GMDEX];

                strcpy(
                    FileNameWithEx,
                    stGdLevel.LevelName
                );

                strcat(
                    FileNameWithEx,
                    ".gmd\0"
                );

                File = fopen(
                    FileNameWithEx,
                    "w\0"
                );
                if(File != NULL) {
                    if(fprintf(
                        File,
                        "%s",
                         stGdLevel.GmdOut
                    ) < 0 ) {
                        puts(ErrorMessages[9]);
                        exit(EXIT_FAILURE);
                    } 
                    free(stGdLevel.GmdOut);
                    fclose(File);
                    puts(Messages[2]);
                } 

                else {
                    puts(ErrorMessages[3]);
                    return EXIT_FAILURE;
                }


            }

        else {
             fclose(File);
             puts(ErrorMessages[3]);
             return EXIT_FAILURE;
        }
    }

    else {
        puts(ErrorMessages[2]);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

unsigned int GenerateString(PGD_LEVEL_STRUCT pstLevel) {
    if(pstLevel->IsNewgrounds == false) {
                if(pstLevel->SongID > 0) {
                        if(pstLevel->SongID > 22) {
                            puts(ErrorMessages[10]);
                            return FAIL;
                        }

                    pstLevel->GmdOutSize = snprintf(
                    NULL,
                    0,
                    "%s%s%s%s%s%u%s",
                    "<d><k>kCEK</k><i>4</i><k>k2</k><s>\0",
                    pstLevel->LevelName,
                    "</s><k>k3</k><s></s><k>k4</k><s>\0",
                    pstLevel->LevelBuffer,
                    "</s><k>k8</k><i>\0",
                    pstLevel->SongID,
                    "</i><k>k13</k><t/><k>k21</k><i>2</i><k>k50</k><i>35</i></d>\0"
                    );

                pstLevel->GmdOut = malloc(pstLevel->GmdOutSize);

                if(pstLevel->GmdOut == NULL) {
                    puts(ErrorMessages[5]);
                    return FAIL;
                }

                sprintf(
                    pstLevel->GmdOut,
                    "%s%s%s%s%s%u%s",
                    "<d><k>kCEK</k><i>4</i><k>k2</k><s>\0",
                    pstLevel->LevelName,
                    "</s><k>k3</k><s></s><k>k4</k><s>\0",
                    pstLevel->LevelBuffer,
                    "</s><k>k8</k><i>\0",
                    pstLevel->SongID,
                    "</i><k>k13</k><t/><k>k21</k><i>2</i><k>k50</k><i>35</i></d>\0"
                    );

                printf(
                    "\n%s\t%u\t%s", 
                    Messages[4], 
                    pstLevel->GmdOutSize, 
                    Messages[5]
                );
        }

                else {
                    pstLevel->GmdOutSize = snprintf(
                    NULL,
                    0,
                    "%s%s%s%s%s",
                    "<d><k>kCEK</k><i>4</i><k>k2</k><s>\0",
                    pstLevel->LevelName,
                    "</s><k>k3</k><s></s><k>k4</k><s>\0",
                    pstLevel->LevelBuffer,
                    "</s><k>k13</k><t/><k>k21</k><i>2</i><k>k50</k><i>35</i></d>\0"
                    );

                pstLevel->GmdOut = malloc(pstLevel->GmdOutSize);

                if(pstLevel->GmdOut == NULL) {
                    puts(ErrorMessages[5]);
                    return FAIL;
                }

                sprintf(
                    pstLevel->GmdOut,
                    "%s%s%s%s%s",
                    "<d><k>kCEK</k><i>4</i><k>k2</k><s>\0",
                    pstLevel->LevelName,
                    "</s><k>k3</k><s></s><k>k4</k><s>\0",
                    pstLevel->LevelBuffer,
                    "</s><k>k13</k><t/><k>k21</k><i>2</i><k>k50</k><i>35</i></d>\0"
                    );

                printf(
                    "\n%s\t%u\t%s", 
                    Messages[4], 
                    pstLevel->GmdOutSize, 
                    Messages[5]
                );
            }
    }

    else {
                    pstLevel->GmdOutSize = snprintf(
                    NULL,
                    0,
                    "%s%s%s%s%s%u%s",
                    "<d><k>kCEK</k><i>4</i><k>k2</k><s>\0",
                    pstLevel->LevelName,
                    "</s><k>k3</k><s></s><k>k4</k><s>\0",
                    pstLevel->LevelBuffer,
                    "</s><k>k45</k><i>\0",
                    pstLevel->SongID,
                    "</i><k>k13</k><t/><k>k21</k><i>2</i><k>k50</k><i>35</i></d>\0"
                    );

                pstLevel->GmdOut = malloc(pstLevel->GmdOutSize);

                if(pstLevel->GmdOut == NULL) {
                    puts(ErrorMessages[5]);
                    return FAIL;
                }


                sprintf(
                    pstLevel->GmdOut,
                    "%s%s%s%s%s%u%s",
                    "<d><k>kCEK</k><i>4</i><k>k2</k><s>\0",
                    pstLevel->LevelName,
                    "</s><k>k3</k><s></s><k>k4</k><s>\0",
                    pstLevel->LevelBuffer,
                    "</s><k>k45</k><i>\0",
                    pstLevel->SongID,
                    "</i><k>k13</k><t/><k>k21</k><i>2</i><k>k50</k><i>35</i></d>\0"
                    );

                printf(
                    "\n%s\t%u\t%s", 
                    Messages[4], 
                    pstLevel->GmdOutSize, 
                    Messages[5]
                );
    }
    
    return SUCCESS;

}