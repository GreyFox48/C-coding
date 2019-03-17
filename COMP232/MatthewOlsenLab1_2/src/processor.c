/*
 * Name: Matthew Olsen
 * Lab: Lab1_2 C Tutorial
 * Date: 02/09/18
 */

#include "processor.h"

MESSAGE messageCache[CACHE_SIZE];
int msgIndex = -1; // -1 means empty cache
int msgTypes[NUMBER_OF_MSG_TYPES];
int batchesProcessed = 0;

void addMessageToCache(char *inputLine) {
    //if full might as well process
    if (msgIndex >= (CACHE_SIZE - 1)) {
        messageDispatcher();
    }

    msgIndex++;
    size_t size;



    sscanf(inputLine, "%u %[^\n]", &messageCache[msgIndex].type, inputLine);

    switch (messageCache[msgIndex].type) {
        case 1:
            size = strlen(inputLine);
            if (size > BUFFER_SIZE) {
                size = BUFFER_SIZE;
            }

            // free in processMessage
            messageCache[msgIndex].content.string =
                    (char *) malloc(sizeof(char) * (size + 1)); //+1 to ensure null terminated
            strncpy(messageCache[msgIndex].content.string, inputLine, size);
            break;
        case 2:
            /* better ways exist to read a variable number of contents per line
             * but they requires something different than sscanf. Note to self
             * in case of funky errors if this code is reused under different
             * parameters */
            sscanf(inputLine, "%d %d %d %d %d",
                   &messageCache[msgIndex].content.integers[0],
                   &messageCache[msgIndex].content.integers[1],
                   &messageCache[msgIndex].content.integers[2],
                   &messageCache[msgIndex].content.integers[3],
                   &messageCache[msgIndex].content.integers[4]);
            break;

        case 3:
            sscanf(inputLine, "%lf %lf %lf %lf",
                   &messageCache[msgIndex].content.doubles[0],
                   &messageCache[msgIndex].content.doubles[1],
                   &messageCache[msgIndex].content.doubles[2],
                   &messageCache[msgIndex].content.doubles[3]);
            break;
        case 4:
            sscanf(inputLine, "%s %s %s %s %s",
                   messageCache[msgIndex].content.words[0],
                   messageCache[msgIndex].content.words[1],
                   messageCache[msgIndex].content.words[2],
                   messageCache[msgIndex].content.words[3],
                   messageCache[msgIndex].content.words[4]);
            break;
        default:
            printf("Error:  Invalid case. File: %s Line: %d\n", __FILE__, __LINE__);

    }



}

void messageDispatcher(void) {
    int i;

    /*
    if (msgIndex == -1) {
        return;
        /* lazy fix to a bug where batches was incremented even
         * if batch was empty and this function was invoked. */
    //}


    // double check in case msgIndex exceeds cache size somehow
    // <= because msgIndex saves the last -valid- index value
    for (i = 0; i <= msgIndex && i < CACHE_SIZE; i++) {
        processMessage(&messageCache[i]);
    }

    batchesProcessed++;
    msgIndex = -1;

}

void processMessage(MESSAGE *message) {
    int i;

    switch (message->type) {
        case MSG_TYPE_1:
            printf("TYPE 1: %s\n", message->content.string);
            free(message->content.string);
            break;
        case MSG_TYPE_2:
            printf("TYPE 2: ");
            // scalable friendly printing
            for (i = 0; i < NUM_OF_INTEGERS - 1; i++) {
                printf("%d,", message->content.integers[i]);
            }
            printf("%d", message->content.integers[i]);
            puts("");
            break;
        case MSG_TYPE_3:
            printf("TYPE 3: ");
            for (i = 0; i < NUM_OF_DOUBLES - 1; i++) {
                printf("%lf/", message->content.doubles[i]);
            }
            printf("%lf", message->content.doubles[i]);
            puts("");
            break;
        case MSG_TYPE_4:
            printf("TYPE 4:");
            for (i = 0; i < NUM_OF_STRINGS; i++) {
                printf(" %s", message->content.words[i]);
            }
            puts("");
            break;
        default:
            printf("Error:  Invalid case. File: %s Line: %d\n", __FILE__, __LINE__);
    }

    msgTypes[(int) (message->type - 1)]++;
}

void printStatistics(void) {
    int sum = 0, i = 0;

    for (i = 0; i < NUMBER_OF_MSG_TYPES; i++) {
        sum += msgTypes[i];
    }

    printf("Number of message batches: %d\n", batchesProcessed);
    printf("Messages processed: %d\n", sum);

    for (i = 0; i < NUMBER_OF_MSG_TYPES; i++) {
        printf("Type %d: %d\n", i + 1, msgTypes[i]);
    }


}

