/*Source:   assign2main.h
  Author:   Petar Kandic, 500876167
  Purpose:  Used to store prototypes of functions in
            assign2funcs.c
  Input:    None
  Output:   None
*/
void printBaseVector(double* baseVector, size_t vectorSize);

double calcLength(double* baseVector, size_t vectorSize);

void calcAndPrintNorm(double* baseVector, size_t vectorSize, double vectorLength);

void parseInput(void);