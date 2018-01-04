#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// function to print out lines without critical info

void printlines() {
  printf("\t=================================\n"
	 "\t=================================\n"
	 "\t=================================\n");
}

int main (int argc, char **argv) {

  // prints top of the map
  printf("\t================================= FFFFFFFF\n"
	 "\t=================================\n"
	 "\t=================================\n"); 

  
  // find the number of lines to store words and then make those blocks
  int number_of_chars = 0;
  int null_terminator = 2;
  int execute_command = 2;
  char *null_char_term = "\\0";


  for(int k = 0; k < argc; k++) {
    number_of_chars += strlen(argv[k]) + 1;
  }
  
  int number_of_lines = (number_of_chars) / 4;

  if (((number_of_chars) % 4) > 0)
    number_of_lines++;


  char *base_address = argv[0];
  base_address += ( 4 * (number_of_lines));
  int current_argv = argc - 1;
  int argv_placeholder = strlen(argv[current_argv]);
  
  for (int i = number_of_lines; i > 0; i--) {

    if ((i == number_of_lines) && ((number_of_chars % 4) > 0)) {
      int leftover = number_of_chars % 4;
      int spaces_prior = 4 - leftover;
      while (spaces_prior != 0) {
	printf("\t|");
	spaces_prior--;
      }
      while (leftover != 0) {
	if (*(*(argv+current_argv)+argv_placeholder) == '\0') {
	  printf("\t|%s","\\0");
	  argv_placeholder -= 1;
	}
	else {
	  printf("\t|%c ",*(*(argv+current_argv)+argv_placeholder));
	  argv_placeholder--;
	  if (argv_placeholder < 0) {
	    current_argv -= 1;
	    argv_placeholder = strlen(argv[current_argv]);
	  }
	}
	leftover--;
      }
    }

    if ((i != number_of_lines) || ((number_of_chars % 4) == 0)) {
      for (int j = 0; j < 4; j++) {
        if (*(*(argv+current_argv)+argv_placeholder) == '\0') {
	  printf("\t|%s","\\0");
	  argv_placeholder -= 1;
	}
	else {
	  printf("\t|%c ",*(*(argv+current_argv)+argv_placeholder));
	  argv_placeholder--;
	  if ((argv_placeholder < 0) && (current_argv != 0)) {
	    current_argv -= 1;
	    argv_placeholder = strlen(argv[current_argv]);
	  }
	}
      }
    }
    printf("\t| %x\n", *(argv+current_argv)+argv_placeholder+1,number_of_lines);

    printf("\t=================================\n");

  }

 

  printlines();

  // print all *argv values and addresses
  printf("\t|  \t|  \t|  \t|  \t| %x\n",&argv[argc+1]);
  printf("\t=================================\n");
  printf("\t|00\t|00\t|00\t|00\t|\n");
  printf("\t=================================\n");
  printf("argv+%i\t|00\t|00\t|00\t|00\t| %x\n",argc,&argv[argc]);
  printf("\t=================================\n");

  char argv_split[8];
  

  for (int i = argc - 1; i >= 0; i--) {
    sprintf(argv_split, "%x", argv[i]);
    printf("argv+%i\t|", i);
    for (int j = 0; j < 8; j += 2)
      printf("%c%c\t|",argv_split[j],argv_split[j+1]);
    printf(" %x\n",&argv[i]);
    printf("\t=================================\n");
  }
    
  printlines();

  // print argc and argv values
  printf("argc\t|00\t|00\t|00\t|%02i\t| %x\n",argc,&argc);
  printf("\t=================================\n");
  sprintf(argv_split, "%x", argv);
  printf("argv\t|");
  for (int j = 0; j < 8; j += 2)
    printf("%c%c\t|",argv_split[j],argv_split[j+1]);
  printf(" %x\n",&argv);

  printf("\t=================================\n");
  printf("\t=================================\n");
  printf("\t================================= 00000000\n");
  
  
  return 0;
}
