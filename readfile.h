/**
 *  CS 537
 *  Project 1 readfile.h
 *  Authors: Kenny Jin, Ying Zhang
 */

#ifndef HEADER_READFILE
#define HEADER_READFILE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFSIZE 1024

char state;
int utime;
int stime;

/**
 *	Read the stat file and set the global variables
 *	@param pid The id of the process
 */
void read_stat(int pid);
/**
 *	Read the statm file and prints the information
 *	@param pid The id of the process
 */
void read_statm(int pid);
/**
 *	Read the cmdline file and prints the information
 *	@param pid The id of the process
 */
void read_cmdline(int pid);
/**
 *	Check if the process belongs to current user
 *	@param pid The id of the process
 *  @param this_uid the current user id
 *  @return if the process belongs to the current user
 */
int check_user_id(int pid, int this_uid);

#endif