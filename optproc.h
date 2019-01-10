/**
 *  CS 537
 *  Project 1 optproc.h
 *  Authors: Kenny Jin, Ying Zhang
 */

#ifndef HEADER_OPTPROC
#define HEADER_OPTPROC

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 *	This is the structure of cmdline option
 *	This structure contains information about options
 */
typedef struct X
{
    int p;
    int pid;
    int s;
    int U;
    int S;
    int v;
    int c;
} Opt_info;

/**
 *	Get the command line option information
 *	@param argc the number of cmdline options
 *	@param argv the array of cmdline option string
 *  @return a pointer of a structure
 */
Opt_info *get_opt_info(int argc, char *argv[]);

#endif