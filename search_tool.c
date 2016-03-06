 /**
 * Search and replace word application
 * Usage: ./search_tool -f <input_filename> -s <search word> -r <replace word> -o <output_file> -h
 * tunde@stackarena.com
 * @Author: Tunde Olabenjo
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>

#define MAX_STRLEN 512

//Functions we are using
int search_file(char *str, char *fname); //the main search function
void Usage(char *arg); //usage function
void Help(char *arg); //help menu
void markLine(char *, char *, char *); //used to underline a found string with ^
int countSubstring(const char *str, const char *sub); //used to count the number of occurence of string
int replaceString(char *find, char *replace, char *infile, char *outfile, int is_out); //replace proc
void outputLine(char *); //stdoutput proc
char *str_replace(char *orig, char *rep, char *with); // the main *ptr replace proc

//Our main function.
/**
 * Get the arguments from the command line
 * @param argc
 * @param argv
 * @return 
 */
int main(int argc, char *argv[]) {
    int result;

    // init empty strings
    char opt_filename[MAX_STRLEN] = {0};
    char opt_string[MAX_STRLEN] = {0};
    char opt_replace[MAX_STRLEN] = {0};
    char opt_output[MAX_STRLEN] = {0};
    int opt_help = 0;
    int option = 0;

    while ((option = getopt(argc, argv,"hf:s:r:o:")) != -1) {
        switch (option) {
            case 'h':
                opt_help = 1;
                break;
            case 'f':
                strncpy(optarg, opt_filename, MAX_STRLEN);
                break;
            case 's':
                strncpy(optarg, opt_string, MAX_STRLEN);
                break;
            case 'r':
                strncpy(optarg, opt_replace, MAX_STRLEN);
                break;
            case 'o':
                strncpy(optarg, opt_output, MAX_STRLEN);
                break;
            default:
                printf("Invalid option: -%c", option);
                Usage(argv[0]);
                exit(1);
        }
    }

    if (opt_help != 0) {
        Help(argv[0]);
        exit(1);
    }
    if (opt_filename[0] == 0) {
    	printf("Missing mandatory argument (-f)\n");
        Usage(argv[0]);
        exit(1);
    }
    if (opt_string[0] == 0) {
    	printf("Missing mandatory argument (-s)\n");
        Usage(argv[0]);
        exit(1);
    }

    // arguments OK, can proceed
    system("clear");

    if (opt_replace[0] == 0)
        result = search_file(opt_filename, opt_string);
    else
        result = replaceString(opt_string, opt_replace, opt_filename, opt_output);

    if (result == -1) {
        perror("Error"); //perror
        exit(1);
    }

    return (0);
}

//help part

void Help(char *arg) {
    printf("Usage: %s -f <input_filename> -s <search word> -r <replace word> -o <output_file> -h\n", arg);
    printf("-f : This option defines the input file name to be searched through\n");
    printf("-s : This option defines the word or phrase which we need to search\n");
    printf(" (Ex: \"sample word\")\n");
    printf("-r : This option is used to replace a word or phrase with searched word or phrase. \n");
    printf("-o : This option defines the output filename in this case the result is redirected to this file.\n");
    printf("-h : Help.\n");
}

//usage part

void Usage(char *arg) {
    printf("Usage: %s -f <input_filename> -s <search word> -r <replace word> -o <output_file> -h\n", arg);
}

/**
 * Gets the file name and the string you are searching for
 * @param fname
 * @param str
 * @return 
 */
int search_file(char *fname, char *str) {    
    int count_line = 1;    
    char temp[MAX_STRLEN];
    char *p;
    char *d; //content pointer
    FILE *file_pointer; //file pointer
    char a[MAX_STRLEN]; //we use this to copy the content
    char data[MAX_STRLEN]; //our final data
    int its_found = 0;

    //open file
    if ((file_pointer = fopen(fname, "r")) == NULL) {
        return (-1);
    } else {
        printf("%s, file searched for word \"%s\"\n", fname, str);
    }

    while (fgets(temp, MAX_STRLEN, file_pointer) != NULL) {

        //count the number of occurrences
        int count = countSubstring(temp, str);

        if ((p = strstr(temp, str)) != NULL) {
            //display and copy the initial temp to data
            printf("\nL%d/%d: %s", count_line, count, temp);
            //adds a new line to the end of the last line
            if(feof(file_pointer)) {
        	sprintf(temp,"%s \n",temp);
        	printf("\n");
            }
            //copy the line into data array including the line numbers
            sprintf(data, "L%d/%d: %s", count_line, count, temp);

            while ((p = strstr(temp, str)) != NULL) {
                //copy the cut string to a
                strcpy(a, p);
                //reset the d pointer and move the pointer by the length of search str
                d = strstr(a, str);
                d += strlen(str);
                //check if the cut line is in the whole line data[512]
                if ((p = strstr(data, d)) != NULL) {
                    //mark the line
                    markLine(d, p - strlen(str), p - 1);
                }
                //now copy the content of *d to temp and increment 
                strcpy(temp, d);
                its_found++;
            }

            int i;
            for (i = 0; i < strlen(data); i++) {
                if (data[i] != '^') {
                    //replace all other chrs apart from ^
                    data[i] = ' ';
                }
            }
               
            //print the marker ^ and add the spaces used by "L%d/%d:"
            printf("%s", data);
        }
        //increment line number	
        count_line++;
    }
    printf("\n");

    if (its_found == 0) {
        printf("\nSorry, couldn't find \"%s\" in file.\n\n", str);
    }

    //Close the file if still open.
    if (file_pointer) {
        fclose(file_pointer);
    }
    return (0);
}

/**
 * @param find
 * @param replace
 * @param infile
 * @param outfile
 * @return 
 */
int replaceString(char *find, char *replace, char *infile, char *outfile) {
    char buff[BUFSIZ]; // the input line
    FILE *in, *out; //input and output files
    char *srchstr;

    if ((in = fopen(infile, "r")) == NULL) {
        return (-1);
    }
    //output file option added
    if (*outfile != 0) {
        if ((out = fopen(outfile, "w")) == NULL) {
            return (-1);
        }
        while (fgets(buff, BUFSIZ, in) != NULL) {
            srchstr = str_replace(buff, find, replace);
            fputs(srchstr, out);
        }
        fclose(in);
        fclose(out);
    } else {
        // display on stdout since no output file is added
        while (fgets(buff, BUFSIZ, in) != NULL) {
            srchstr = str_replace(buff, find, replace);
            outputLine(srchstr);
        }

        fclose(in);
    }
    return 0;
}

/**
 * Mark the strings with ^
 * @param line
 * @param start
 * @param stop
 */
void markLine(char *line, char *start, char *stop) {
    char *p;

    for (p = line; p < start; p++)
        *p = ' ';

    for (p = start; p <= stop; p++)
        *p = '^';
}

//count the number of occurrences of the searched string

int countSubstring(const char *str, const char *sub) {
    int length = strlen(sub);
    if (length == 0) return 0;
    int count = 0;
    for (str = strstr(str, sub); str; str = strstr(str + length, sub))
        ++count;
    return count;
}

//print out to stdout, gotten from ch02 but modified

void outputLine(char *line) {
    char *p;

    for (p = line; *p != '\0'; p++)
        putc(*p, stdout);

    // putc('\n', stdout);
}

/**
 * The main replacement function char *
 * @param orig
 * @param rep
 * @param with
 * @return 
 */
char *str_replace(char *orig, char *rep, char *with) {
    char *result; // the return string
    char *ins; // the next insert point
    char *tmp; // varies
    int len_rep; // length of rep
    int len_with; // length of with
    int len_front; // distance between rep and end of last rep
    int count; // number of replacements

    if (!orig)
        return NULL;
    if (!rep)
        rep = "";
    len_rep = strlen(rep);
    if (!with)
        with = "";
    len_with = strlen(with);

    ins = orig;
    for (count = 0; tmp = strstr(ins, rep); ++count) {
        ins = tmp + len_rep;
    }

    // first time through the loop, all the variable are set correctly
    // from here on,
    //    tmp points to the end of the result string
    //    ins points to the next occurrence of rep in orig
    //    orig points to the remainder of orig after "end of rep"

    tmp = result = malloc(strlen(orig) + (len_with - len_rep) * count + 1);

    if (!result)
        return NULL;

    while (count--) {
        ins = strstr(orig, rep);
        len_front = ins - orig;
        tmp = strncpy(tmp, orig, len_front) + len_front;
        tmp = strcpy(tmp, with) + len_with;
        orig += len_front + len_rep; // move to next "end of rep"
    }
    strcpy(tmp, orig);
    return result;
}
