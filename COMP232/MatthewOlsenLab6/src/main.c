/*
 * Matthew Olsen
 * Lab 6 Parser
 * March 12, 2019
 */

#include "eval.h"

int main(int argc, char* argv[])
{
    freopen(argv[1], "r", stdin);

    NODE *fullProgram = program();
    printf("Done parsing...\n");
    printProgram(fullProgram);
    freeNodeTree(fullProgram); /* what is malloced must be set FREEEEEEE! */

    exit(0);
}