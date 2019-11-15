/*Source:   assign2main.c
  Author:   Petar Kandic, 500876167
  Purpose:  Calls the rest of the program
  Input:    None
  Output:   None
*/

#include "assign2funcs.c"

/*
 * The main method of the program.
 * Here, main only calls parseInput() from assign2funcs.c.
 * It takes no arguments and only returns 0 (although more meaningful exit codes
 * are implemented in assign2funcs.c).
 */

int main(void)
{
    parseInput();
    return 0;
}
