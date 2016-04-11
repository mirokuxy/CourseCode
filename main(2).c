#include <stdio.h>
#include <string.h>

int main ()
{
    char buf[50];
    int i;
    char *p;
    char *array[10];
    int x;

    //for (x=0;x<3;x++)
    while(1)
    {
        printf("Type a command:");
        fgets (buf, 200, stdin);

        /// This part breaks the string into tokens and stores a pointer to each token into "array[]"
        i = 0;
        p = strtok (buf," ");
        while (p != NULL)
        {
            array[i++] = p;
            p = strtok (NULL, " ");
        }

        /// This section iterates through "array[]" and displays each token on screen
        for (i=0;i<3; ++i)
        {
            printf("%s\n", array[i]);
        }
    }
    return 0;
}
