#include "main.h"

INT main(
   _In_ INT argc, 
   _In_ PSTR argv[]
) {

    if(argc<5) {
        printf(
            "%s\n%s",
            g_apszMessages[3],
            g_apszErrorMessages[0]
        );
        return EXIT_FAILURE;
    }

    if(argc>5) {
        printf(
            "%s\n%s",
            g_apszMessages[3],
            g_apszErrorMessages[1]
        );
        return EXIT_FAILURE;
    }

    GD_LEVEL_STRUCT stGdLevel;

    if(strcmp(
        argv[4],
        "TRUE"
    ) == 0)
            stGdLevel.bIsNewgrounds = TRUE;

    else if(strcmp(
        argv[4],
        "FALSE"
        ) == 0)
            stGdLevel.bIsNewgrounds = FALSE;
    else {
        puts(g_apszErrorMessages[11]);
        return EXIT_FAILURE;
    }

    strcpy(
        stGdLevel.szLevelName, 
        argv[2]
    );

    if(strlen(stGdLevel.szLevelName) > 20) {
        puts(g_apszErrorMessages[7]);
        return EXIT_FAILURE;
    }
    stGdLevel.uSongID = 0;
    stGdLevel.uSongID = atoi(argv[3]);

    FILE *pFile = fopen(
        argv[1],
        "r\0"
    );

    if(pFile != NULL) {
        //Get file size to allocate a buffer
        if(fseek(
            pFile,
             0,
             SEEK_END
             ) == 0) {
             stGdLevel.uRawBufferSize = ftell(pFile);
             rewind(pFile);

             printf(
                "\n%s\t%u\t%s", 
                g_apszMessages[0], 
                stGdLevel.uRawBufferSize, 
                g_apszMessages[1]
                );

                stGdLevel.pszLevelBuffer = malloc(stGdLevel.uRawBufferSize);
                
                if(stGdLevel.pszLevelBuffer == NULL) {
                    puts(g_apszErrorMessages[4]);
                    return EXIT_FAILURE;
                }

                if (fread(
                    stGdLevel.pszLevelBuffer,
                    1,
                    stGdLevel.uRawBufferSize,
                    pFile
                ) < 0) {
                    puts(g_apszErrorMessages[6]);
                    fclose(pFile);
                    return EXIT_FAILURE;
                }

                UINT uStringStatus = fnGenerateString(&stGdLevel);
                
                fclose(pFile);

                free(stGdLevel.pszLevelBuffer);

                if(uStringStatus) return EXIT_FAILURE;;

                CHAR szFileNameWithEx[GDMAX + GMDEX];

                strcpy(
                    szFileNameWithEx,
                    stGdLevel.szLevelName
                );

                strcat(
                    szFileNameWithEx,
                    ".gmd\0"
                );

                pFile = fopen(
                    szFileNameWithEx,
                    "w\0"
                );
                if(pFile != NULL) {
                    if(fprintf(
                        pFile,
                        "%s",
                         stGdLevel.pszGmdOut
                    ) < 0 ) {
                        puts(g_apszErrorMessages[9]);
                        exit(EXIT_FAILURE);
                    } 
                    free(stGdLevel.pszGmdOut);
                    fclose(pFile);
                    puts(g_apszMessages[2]);
                } 

                else {
                    puts(g_apszErrorMessages[3]);
                    return EXIT_FAILURE;
                }


            }

        else {
             fclose(pFile);
             puts(g_apszErrorMessages[3]);
             return EXIT_FAILURE;
        }
    }

    else {
        puts(g_apszErrorMessages[2]);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

UINT fnGenerateString(_In_Out_ PGD_LEVEL_STRUCT pstLevel) {
    if(pstLevel->bIsNewgrounds == FALSE) {
                if(pstLevel->uSongID > 0) {
                        if(pstLevel->uSongID > 22) {
                            puts(g_apszErrorMessages[10]);
                            return FAIL;
                        }

                    pstLevel->uGmdOutSize = snprintf(
                    NULL,
                    0,
                    "%s%s%s%s%s%u%s",
                    "<d><k>kCEK</k><i>4</i><k>k2</k><s>\0",
                    pstLevel->szLevelName,
                    "</s><k>k3</k><s></s><k>k4</k><s>\0",
                    pstLevel->pszLevelBuffer,
                    "</s><k>k8</k><i>\0",
                    pstLevel->uSongID,
                    "</i><k>k13</k><t/><k>k21</k><i>2</i><k>k50</k><i>35</i></d>\0"
                    );

                pstLevel->pszGmdOut = malloc(pstLevel->uGmdOutSize);

                if(pstLevel->pszGmdOut == NULL) {
                    puts(g_apszErrorMessages[5]);
                    return FAIL;
                }

                sprintf(
                    pstLevel->pszGmdOut,
                    "%s%s%s%s%s%u%s",
                    "<d><k>kCEK</k><i>4</i><k>k2</k><s>\0",
                    pstLevel->szLevelName,
                    "</s><k>k3</k><s></s><k>k4</k><s>\0",
                    pstLevel->pszLevelBuffer,
                    "</s><k>k8</k><i>\0",
                    pstLevel->uSongID,
                    "</i><k>k13</k><t/><k>k21</k><i>2</i><k>k50</k><i>35</i></d>\0"
                    );

                printf(
                    "\n%s\t%u\t%s", 
                    g_apszMessages[4], 
                    pstLevel->uGmdOutSize, 
                    g_apszMessages[5]
                );
        }

                else {
                    pstLevel->uGmdOutSize = snprintf(
                    NULL,
                    0,
                    "%s%s%s%s%s",
                    "<d><k>kCEK</k><i>4</i><k>k2</k><s>\0",
                    pstLevel->szLevelName,
                    "</s><k>k3</k><s></s><k>k4</k><s>\0",
                    pstLevel->pszLevelBuffer,
                    "</s><k>k13</k><t/><k>k21</k><i>2</i><k>k50</k><i>35</i></d>\0"
                    );

                pstLevel->pszGmdOut = malloc(pstLevel->uGmdOutSize);

                if(pstLevel->pszGmdOut == NULL) {
                    puts(g_apszErrorMessages[5]);
                    return FAIL;
                }

                sprintf(
                    pstLevel->pszGmdOut,
                    "%s%s%s%s%s",
                    "<d><k>kCEK</k><i>4</i><k>k2</k><s>\0",
                    pstLevel->szLevelName,
                    "</s><k>k3</k><s></s><k>k4</k><s>\0",
                    pstLevel->pszLevelBuffer,
                    "</s><k>k13</k><t/><k>k21</k><i>2</i><k>k50</k><i>35</i></d>\0"
                    );

                printf(
                    "\n%s\t%u\t%s", 
                    g_apszMessages[4], 
                    pstLevel->uGmdOutSize, 
                    g_apszMessages[5]
                );
            }
    }

    else {
                    pstLevel->uGmdOutSize = snprintf(
                    NULL,
                    0,
                    "%s%s%s%s%s%u%s",
                    "<d><k>kCEK</k><i>4</i><k>k2</k><s>\0",
                    pstLevel->szLevelName,
                    "</s><k>k3</k><s></s><k>k4</k><s>\0",
                    pstLevel->pszLevelBuffer,
                    "</s><k>k45</k><i>\0",
                    pstLevel->uSongID,
                    "</i><k>k13</k><t/><k>k21</k><i>2</i><k>k50</k><i>35</i></d>\0"
                    );

                pstLevel->pszGmdOut = malloc(pstLevel->uGmdOutSize);

                if(pstLevel->pszGmdOut == NULL) {
                    puts(g_apszErrorMessages[5]);
                    return FAIL;
                }


                sprintf(
                    pstLevel->pszGmdOut,
                    "%s%s%s%s%s%u%s",
                    "<d><k>kCEK</k><i>4</i><k>k2</k><s>\0",
                    pstLevel->szLevelName,
                    "</s><k>k3</k><s></s><k>k4</k><s>\0",
                    pstLevel->pszLevelBuffer,
                    "</s><k>k45</k><i>\0",
                    pstLevel->uSongID,
                    "</i><k>k13</k><t/><k>k21</k><i>2</i><k>k50</k><i>35</i></d>\0"
                    );

                printf(
                    "\n%s\t%u\t%s", 
                    g_apszMessages[4], 
                    pstLevel->uGmdOutSize, 
                    g_apszMessages[5]
                );
    }
    
    return SUCCESS;

}