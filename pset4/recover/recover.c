#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


// JPEG Header in bytes
// FAT block size
const int HEADER_SIZE = 4;
const int BLOCK_SIZE = 512;

// Buffer to read 512 bytes into
typedef uint8_t BYTE;
BYTE buffer[BLOCK_SIZE];

// Buffer for filename
char filename[8];

int main(int argc, char *argv[])
{
    // Check for proper usage
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    // Open file in read mode
    FILE *file = fopen(argv[1], "r");
    if (file == NULL)
    {
        printf("Could not open file.\n");

        return 1;
    }
    // Initialising counter for JPEG filenames
    int cntr = 0;

    // Initialising image NULL pointer
    FILE *img = NULL;

    // Reading from buffer
    while (fread(&buffer, sizeof(BYTE), BLOCK_SIZE, file) == BLOCK_SIZE)
    {
        // Checking for JPEG header
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // If first, image initialise parameters to write to file
            if (cntr == 0)
            {
                sprintf(filename, "%03i.jpg", cntr);
                img = fopen(filename, "w");
                fwrite(&buffer, sizeof(BYTE), BLOCK_SIZE, img);
                cntr++;
            }
            // If not first JPEG, close file
            else if (cntr > 0)
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", cntr);
                img = fopen(filename, "w");
                fwrite(&buffer, sizeof(BYTE), BLOCK_SIZE, img);
                cntr++;
            }
        }
        // If header not found keep writing
        else if (cntr > 0)
        {
            fwrite(&buffer, sizeof(BYTE), BLOCK_SIZE, img);
        }
    }

    fclose(file);
    fclose(img);

    return 0;
}