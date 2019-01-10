/**
 *  CS 537
 *  Project 1 optproc.c
 *  Authors: Kenny Jin, Ying Zhang
 */

#include "optproc.h"

Opt_info *get_opt_info(int argc, char *argv[]) {
    // opt_info is a variable that contains all the information 
    // about command line options.
    // For example, the field 's' in the show_info decides 
    // if the single character state of the process will be shown.
    Opt_info *opt_info = malloc(sizeof(Opt_info));
    if (opt_info == NULL) {
        fprintf(stderr, "error: failed to allocate memory\n");
        exit(EXIT_FAILURE);
    }
    // Except for pid and opt, all of the vars are boolean values
    int show_one_proc = 0; // -p. If this is false, all processes are displayed
    int pid = 0; // process id, useful only when show_one_proc is true
    int show_state = 0; // -s
    int show_utime = 1; // -U
    int show_stime = 0; // -S
    int show_vmem = 0; // -v
    int show_cmd = 1; // -c
    int opt;
    while ((opt = getopt(argc, argv, ":p:s::U::S::v::c::")) != -1) {
        switch (opt) {
            case 'p' :
            // If multiple -p are present, just process the last -p option and ignoring the previous ones.
                show_one_proc = 1;
                if (optarg == NULL || optarg[0] == '-')
                {
                	fprintf(stderr, "Option -%c is missing a required argument.\n", opt);
                	fprintf(stderr, "\nUsage: %s [-p [pid]] [-s|-s-] [-U|-U-] [-S|-S-] [-v|-v-] [-c|-c-]\n",
                            argv[0]);
                	printf("\n");
                	exit(EXIT_FAILURE);
                }
                // The code below determines if optarg only consists of numbers
                int arg_size = strlen(optarg);
                for (int i = 0; i < arg_size; i++)
                {
                	if (optarg[i] < '0' || optarg[i] > '9')
                	{
                		fprintf(stderr, "error: process ID is not a number\n");
                    	fprintf(stderr, "\nUsage: %s [-p [pid]] [-s|-s-] [-U|-U-] [-S|-S-] [-v|-v-] [-c|-c-]\n",
                            argv[0]);
                    	printf("\n");
                    	exit(EXIT_FAILURE); 
                	}
                }
                // The code below determines if the number is out of range
                pid = atoi(optarg);
                if (pid < 1) {
                    fprintf(stderr, "error: process ID out of range\n");
                    fprintf(stderr, "\nUsage: %s [-p [pid]] [-s|-s-] [-U|-U-] [-S|-S-] [-v|-v-] [-c|-c-]\n",
                            argv[0]);
                    printf("\n");
                    exit(EXIT_FAILURE); 
                }
                // -p 1000 and -p1000 are both valid
                break;
            case 's' :
                if (optarg == NULL) {
                    show_state = 1;
                } else if (strcmp(optarg, "-") != 0) {
                    fprintf(stderr, "error: process ID list syntax error\n");
                    fprintf(stderr, "\nUsage: %s [-p [pid]] [-s|-s-] [-U|-U-] [-S|-S-] [-v|-v-] [-c|-c-]\n",
                            argv[0]);
                    printf("\n");
                    exit(EXIT_FAILURE); 
                } else {
                	show_state = 0;
                }
                break;
            case 'U' :
                if (optarg != NULL) {
                    if (strcmp(optarg, "-") == 0) {
                        show_utime = 0;
                    } else {
                        fprintf(stderr, "error: process ID list syntax error\n");
                        fprintf(stderr, "\nUsage: %s [-p [pid]] [-s|-s-] [-U|-U-] [-S|-S-] [-v|-v-] [-c|-c-]\n",
                            argv[0]);
                        printf("\n");
                        exit(EXIT_FAILURE);
                    } 
                } else {
                	show_utime = 1;
                }
                break;
            case 'S' :
                if (optarg == NULL) {
                    show_stime = 1;
                } else if (strcmp(optarg, "-") != 0) {
                    fprintf(stderr, "error: process ID list syntax error\n");
                    fprintf(stderr, "\nUsage: %s [-p [pid]] [-s|-s-] [-U|-U-] [-S|-S-] [-v|-v-] [-c|-c-]\n",
                            argv[0]);
                    printf("\n");
                    exit(EXIT_FAILURE); 
                } else {
                	show_stime = 0;
                }
                break;
            case 'v' :
                if (optarg == NULL) {
                    show_vmem = 1;
                } else if (strcmp(optarg, "-") != 0) {
                    fprintf(stderr, "error: process ID list syntax error\n");
                    fprintf(stderr, "\nUsage: %s [-p [pid]] [-s|-s-] [-U|-U-] [-S|-S-] [-v|-v-] [-c|-c-]\n",
                            argv[0]);
                    printf("\n");
                    exit(EXIT_FAILURE); 
                } else {
                	show_vmem = 0;
                }
                break;
            case 'c' :
                if (optarg != NULL) {
                    if (strcmp(optarg, "-") == 0) {
                        show_cmd = 0;
                    } else {
                        fprintf(stderr, "error: process ID list syntax error\n");
                        fprintf(stderr, "\nUsage: %s [-p [pid]] [-s|-s-] [-U|-U-] [-S|-S-] [-v|-v-] [-c|-c-]\n",
                            argv[0]);
                        printf("\n");
                        exit(EXIT_FAILURE);
                    } 
                } else {
                	show_cmd = 1;
                }
                break;
            case ':':
                fprintf(stderr, "Option -%c is missing a required argument.\n", optopt);
                fprintf(stderr, "\nUsage: %s [-p [pid]] [-s|-s-] [-U|-U-] [-S|-S-] [-v|-v-] [-c|-c-]\n",
                    argv[0]);
                printf("\n");
                exit(EXIT_FAILURE);
            default: /* '?' */
                fprintf(stderr, "\nUsage: %s [-p [pid]] [-s|-s-] [-U|-U-] [-S|-S-] [-v|-v-] [-c|-c-]\n",
                    argv[0]);
                printf("\n");
                exit(EXIT_FAILURE); 
        }
    }
    // The code below is intended to determine if there are any extra arguments
    if (optind < argc) {
        printf("non-option ARGV-elements: ");
        while (optind < argc)
            printf("%s ", argv[optind++]);
        printf("\n");
        fprintf(stderr, "\nUsage: %s [-p [pid]] [-s|-s-] [-U|-U-] [-S|-S-] [-v|-v-] [-c|-c-]\n",
            argv[0]);
        printf("\n");
        exit(EXIT_FAILURE); 
    }
    opt_info -> p = show_one_proc;
    opt_info -> pid = pid;
    opt_info -> s = show_state;
    opt_info -> U = show_utime;
    opt_info -> S = show_stime;
    opt_info -> v = show_vmem;
    opt_info -> c = show_cmd;
    return opt_info;
}