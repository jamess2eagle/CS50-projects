#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


typedef uint8_t BYTE;
BYTE buffer[512] = {0};

int main(int argc, char *argv[])
{
    //check for correct usage
    if (argc != 2)
    {
        fprintf(stderr, "Usage: recover filename\n");
        return 1;
    }

    //save file name
    char *infile = argv[1];

    //open memory card
    FILE *inptr = fopen(infile, "r");

    //check if file can be open
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    FILE *outptr = NULL;

    char filename[8];

    int count = 0;

    //repeat until end of card:
    while (fread(buffer, 512, 1, inptr) == 1)
    {

        //check for JPEG
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (outptr != NULL)
            {
                fclose(outptr);
            }
            sprintf(filename, "%03i.jpg", count);
            outptr = fopen(filename, "w");
            count++;
            if (outptr != NULL)
            {
                fwrite(buffer, 512, 1, outptr);
            }
        }
        else
        {
            if (outptr != NULL)
            {
                fwrite(buffer, 512, 1, outptr);
            }
        }
    }
    fclose(inptr);
    fclose(outptr);
    return 0;
}

