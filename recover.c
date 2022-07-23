#include <stdio.h>
#include <stdlib.h>
 
int main(int argc, char *argv[])
{
    #include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#define BLOCK_SIZE 512

typedef uint8_t BYTE;



int main(int argc, char *argv[])
{
  
    if (argc > 2)
    {
        printf("Usage: recover nameOfCard\n");
        return 1;
    }

    char *infile = argv[1];


    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open file");
        return 1;
    }

    BYTE buffer[512];
    int imageCount = 0;

    char filename[8];
    FILE *outFile = NULL;

    while (true)
    {
        
        size_t bytesRead = fread(buffer, sizeof(BYTE), BLOCK_SIZE, inptr);

        if (bytesRead == 0 && feof(inptr))
        {
            break;
        }

    
        bool containsJpegHeader = buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0;


        if (containsJpegHeader && outFile != NULL)
        {
            fclose(outFile);
            imageCount++;
        }

        if (containsJpegHeader)
        {
            sprintf(filename, "%03i.jpg", imageCount);
            outFile = fopen(filename, "w");
        }

        if (outFile != NULL)
        {
            fwrite(buffer, sizeof(BYTE), bytesRead, outFile);
        }

    }

    fclose(outFile);
    fclose(inptr);

    // success
    return 0;
}
 
}