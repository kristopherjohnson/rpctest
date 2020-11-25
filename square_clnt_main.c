#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "square.h"

int
main (int argc,char **argv)
{
  CLIENT *cl;

  cl = clnt_create("127.0.0.1", SQUARE_PROG, SQUARE_VERS, "tcp");
  if (cl == NULL) {
    clnt_perror(cl, "call failed");
    exit (1);
  }

  square_in in = { 2 };
  fprintf(stderr, "Calling square_proc_1...\n");
  square_out *out = square_proc_1(&in, cl);
  fprintf(stderr, "square_proc_1 returned\n");
  if (out != NULL)
  {
      printf("The result is %d\n", out->res1);
  }
  else
  {
      clnt_perror(cl, "square_proc_1");
  }


  sleep(1);
  exit(0);
}