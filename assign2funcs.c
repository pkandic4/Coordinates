/*Source:   assign2main.c
  Author:   Petar Kandic, 500876167
  Purpose:  Takes in a vector (or vectors) from stdin.
            The length of this vector is calculated, as is the
            normalized version (see below) of the vector.
            Both the normalized and base vectors are printed on stdout.
  Input:    Vectors from stdin.
  Output:   The base and normalized vectors.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "assign2funcs.h"

/*
 * MAX denotes the largest accepted size of a vector, 9 elements.
 * Because the lowest acceptable size (1) was never needed for computation or control flows (loops, if
 * statements), I elected to exclude a corresponding MIN macro.
 * If there is a problem with the input, the program will exit with code ERROREXIT.
 * Otherwise, it will exit with NORMALEXIT.
 */

#define MAX 9
#define NORMALEXIT 0
#define ERROREXIT 1

/*
 * printBaseVector:
 * Takes an inputted vector as an argument, as well as the vector's size
 * (the number of coordinates, or entries/elements).
 * It returns nothing as all it does is print the vector on stdout
 * (plus brackets and commas).
 * Note that the printed elements are truncated to 3 decimal places as shown in the instructions file.
 * It does this with a simple for loop.
 */

void printBaseVector(double* baseVector, size_t vectorSize)
{
    printf("VECTOR: [");
    for (int i = 0; i < vectorSize; i++) //where i is used for indexing through vector array
    {
        if (i == vectorSize - 1)
        {
            printf(" %.3lf ", baseVector[i]);
        }
        else
        {
            printf(" %.3lf,", baseVector[i]); //each element printed w/ space and comma (note %lf is a double)
        }
    }
    printf("]"); //Closing bracket
}

/*
 * The length of a vector can be found by squaring all of its coordinates,
 * adding them up, and then finding the square root of that sum.
 * calcLength takes an inputted vector and that vector's size as arguments.
 * The variable sum is initially set to 0, then it is added to.
 * The math.h functions pow and sqrt are used here.
 */

double calcLength(double* baseVector, size_t vectorSize)
{
    double sum = 0;
    for (int i = 0; i < vectorSize; i++)
    {
        sum += pow(baseVector[i], 2); //Sum is added to by each element, squared
    }
    return sqrt(sum);
}

/*
 * calcAndPrintNorm is a "combo" function.
 * Once again, the arguments are the inputted vector, the size of the vector,
 * and now the length of the vector as calculated above.
 * A new vector array, normVector, is created that can hold as many as 9 coordinates.
 * This array is populated in a for loop with normalized coordinates; that is,
 * the original coordinates divided by the vector's length.
 * normVector is then printed on stdout using much the same process as in
 * printBaseVector.
 */

void calcAndPrintNorm(double* baseVector, __size_t vectorSize, double vectorLength)
{
    double normVector[MAX] = {}; //Initialized to size of 9, but may hold less than that
    for (int i = 0; i < vectorSize; i++)
    {
        normVector[i] = (baseVector[i]/vectorLength);
    }

    printf(" NORMALIZED: [");
    for (int i = 0; i < vectorSize; i++)
    {
        if (i == vectorSize - 1)
        {
            printf(" %.3lf ", normVector[i]);
        }
        else
        {
            printf(" %.3lf, ", normVector[i]);
        }
    }
    printf("]\n"); // \n so that new inputs can be placed on separate line

}

/*
 * The most important function of the program.
 * A number of variables are created (all briefly described in the function itself).
 *
 * The vectors are read from stdin using a while loop.
 * The first valid input (that is, a double, see more below) will be the size of the vector.
 * The char control is used to determine if EOF is inputted (ctrl+d, that is).
 * However, the use of getc in the loop conditions means that an input must be taken and assigned to control
 * the first time the program begins.
 * To compensate, the int value is obtained from control (NOT the ASCII value).
 * If this is indeed the first vector being inputted, the int control denotes will be set as the size
 * of the vector.
 * However, getc will not take another input afterwords, so the control variable for this scenario
 * (countControlUses) is incremented, allowing the first valid input of any new vector line to be the size
 * of that vector.
 *
 * If vectorSize is larger than MAX (9 elements) or smaller than 0, BAD INPUT is printed on
 * stderr, and the program exits with ERROREXIT code 1.
 * If vectorSize is exactly 0, the program simply exits with ERROREXIT.
 *
 * If the vectorSize is valid, the other inputs are checked.
 * If one of the inputs is not a valid double (contains a character than is not an integer digit,
 * a period, or a plus sign, or a minus sign), BAD INPUT is printed on stderr.
 * Then a new loop checks if enter has been pressed (\n) or if ctrl-d has been pressed (EOF).
 * If either are true, the index is reset to zero, and the program starts taking new vectors.
 * This loop is included to ensure that the invalid character is not fed into the array.
 *
 * The vector array will be filled with valid input elements until the index equals the inputted vector size.
 * When this happens, the original vector is printed, as is the normalized vector.
 * The index is also reset to zero, so that new vectors can be read into the same array.
 *
 * If everything was ok with the inputs, and the while loop is broken out of through ctrl-d,
 * the program exits with code NORMALEXIT.
 */

void parseInput(void)
{
    double baseVector[MAX]={}; //Up to 9 elements
    char control; //Controls main loop below
    int vectorSize,
    index = 0,
    countControlUses = 0,
    charToInt; //This is equal to the first input of the line

    while((control = getc(stdin)) != EOF ) //Checks for EOF, but also takes input once
    {
        here:
        charToInt = control - '0'; //Extracts int CHARACTER from control, not ASCII value
        if (countControlUses == 0)
        {
            if (charToInt < 0 || charToInt > MAX) //control=getc been has not been dealt with yet
            {
                fprintf(stderr, "BAD INPUT\n");
                scanf("%*[^\n]%*1[\n]");
                countControlUses++;
                goto here;
            }
            else
            {
                vectorSize = charToInt;
                countControlUses++;
            }
        }
        else
        {
            scanf("%d", &vectorSize);
        }
        if (vectorSize < 0 || vectorSize > MAX)
        {
            fprintf(stderr, "BAD INPUT");
            exit(ERROREXIT);
        }
        if (vectorSize == 0)
        {
            exit(ERROREXIT);
        }

        while (index < vectorSize)
        {
            if (scanf("%lf", &baseVector[index]) == 0) //Is input a valid double?
            {
                fprintf(stderr, "BAD INPUT\n");
                for (;;) //loops indefinitely until break appears
                {
                    control = getc(stdin); //this does not take an input
                    if (control == '\n' || control == EOF) //When vector w/ invalid input is finished, break
                    {
                        break;
                    }
                }
                index = 0; //reset index, so new vector can be fed into array
                goto here;
            }
            index++;
            if (index == vectorSize)
            {
                index = 0;
                printBaseVector(baseVector, vectorSize);
                calcAndPrintNorm(baseVector, vectorSize, calcLength(baseVector, vectorSize));
                break;
            }
        }
    }
    exit(NORMALEXIT);
}