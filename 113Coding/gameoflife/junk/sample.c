#include <stdio.h>
#include <stdlib.h>

#define LEN 128

int main(void)
{
        FILE *fp;
        char in[LEN];
        int x, y;
        unsigned char i;
        int j = 1;
        i = j;

        fp = fopen("1beacon_106.lif", "r");
        if (fp == NULL) {
                printf("failed to open file\n");
                exit(EXIT_FAILURE);
        }

        while (fgets(in, LEN, fp)) {
                if(in[0] != '#'){
                        sscanf(in, "%d %d", &x, &y);
                        printf("%d %d\n", x, y);
                }
        }

        printf("is %d.\n", -30 % 60);
        printf("Char is %u\n", i);

        fclose(fp);
        return 0;
}
