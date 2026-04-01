/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include "tests-common.h"

void
run_test_in_child(int (*func)(void), const char *funcname)
{
    int cpid;
    int csts;
    int exit_code = -1;

    printf("\n---------------------\n%s...\n", funcname);
    cpid = fork();
    if (cpid) {
        waitpid(cpid, &csts, 0);
        if (!WIFEXITED(csts))
            goto child_failed;
        exit_code = WEXITSTATUS(csts);
        if (exit_code == 0)
            printf(" Pass\n");
        else {
child_failed:
            printf(" FAIL\n");
            exit(exit_code);
        }
    } else {
        exit(func());
    }
}
