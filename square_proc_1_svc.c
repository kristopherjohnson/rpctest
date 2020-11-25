#include <stdio.h>
#include "square.h"

square_out * square_proc_1_svc(square_in *in, struct svc_req *req)
{
    // TODO: Figure out the right way to manage memory for the result.
    // TODO: Write to the same log/console used by square_svc/main().
    static square_out result;
    fprintf(stderr, "%s: calculating square of %d and returning result\n",
        __FUNCTION__, in->arg1);
    result.res1 = in->arg1 * in->arg1;
    return &result;
}