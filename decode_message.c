/*
-------------------------------------
File:    decode_message.c
Project: Lab3_cp264
file description
-------------------------------------
Author:  Tommy Le
ID:      200298530
Email:   lexx8530@mylaurier.ca
Version  2021-01-27
Modified: 2022-01-21
-------------------------------------

Program Description:
===================
   Given a 2D character array, called "scrambled", filled with ad hoc characters, this program uses the [row, col]
pair values stored in the 2D integer array, called "key", to retrieve characters from the "scrambled" array.
The retrieved individual characters are concatenated, left to right, and in the order that they are retrieved, to
form the complete decoded message. The message is then output.
------------------------------------------------------------------------------------------
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//===================== GLOBAL MACRO DEFINITIONS ==========================================================

#define  cNUL     '\0'          // NULL character
#define  sNUL     "\0"          // NULL String
#define  cBlank   ' '           // Blank character
#define  sBlank   " "           // Blank String
#define  cUScore  '_'           // Underscore character
#define  sUScore  "_"           // Underscore string.

                                // Define machine-independent TRUE and FALSE values
#ifdef TRUE
#undef TRUE
#undef FALSE
#endif
#define TRUE  (1==1)
#define FALSE (0==1)
                                // ======================== Statement Function Definitions.
#define  F_MIN(v1,v2) (((v1) <  (v2))? (v1):(v2))        // Return the less    of v1 and v2
#define  F_MAX(v1,v2) (((v1) >  (v2))? (v1):(v2))        // Return the greater of v1 and v2
#define ZF_MIN(v1,v2) (F_MAX(0, (F_MIN((v1),(v2)))))     // Like F_MIN, but lower bounds the result at ZERO
#define ZF(v)         (F_MAX(0, (v)))                    // Lower bounds the value "v" at ZERO.
#define  F_NOT(v)     (((v) == TRUE)? FALSE:TRUE)        // Logical Negation.
#define  F_ABS(v)     (((v) >= 0   )? (v):(-(v)))        // Absolute value

//====================== GLOBAL CONSTANTS ==================================================================
#define MAX_NUM_ROWS     5           // Max. number of rows.
#define MAX_NUM_COLS     6           // Max. number of columns.
#define MAX_KEY_PAIRS   15           // Max. number of [row, col] key pairs.

//<*** your GLOBAL CONSTANTS definitions here ***>

int main(int argc, char *argv[]) {
//==============================
    setbuf(stdout, NULL);            // Turns standard output buffering off

    //<*** Your Variable Declarations here ***>

                                     // "scrambled" - 2D Character Array storing adhoc characters.
    char scrambled[MAX_NUM_ROWS][MAX_NUM_COLS] = {{"zd_k83"},
                                                  {"Ju9_Tn"},
                                                  {"bgm7If"},
                                                  {"ax0DLU"},
                                                  {"p_QoiR"}                                                 };
                                     // "Key" - 2D Integer Array storing the message key pairs [row, col].
                                     //         Note: The range of the row, col pair values stored in the "key"
                                     //               array is as shown below:
                                     //               [row, col] ==> [1...5, 1...6], not [0...4, 0...5]!!!
    int  key[MAX_KEY_PAIRS][2] = { { 3, 5 }, { 5, 2 }, { 4, 1 }, { 3, 3 },
            { 1, 3 }, { 1, 2 }, { 5, 4 }, { 5, 5 }, { 2, 6 }, { 3, 2 },
            { 2, 4 }, { 4, 5 }, { 4, 1 }, { 3, 1 }, { 1, 6 } };

    //<*** Your Program Code here ***>
    char space[2];
    char *check;
    char code[MAX_KEY_PAIRS+1];
    code[0] = 0;

    for (int i = 0; i < MAX_KEY_PAIRS; i++) {

        space[0] = scrambled[key[i][0] - 1][key[i][1] - 1];

        if (space[0] == '_') {
            space[0] = ' ';
        }
        space[1] = '\0';
        strcat(code, space);
    }

    printf("::: Decoded Message: [%s]\n\n", code);
    printf("::: Program Terminated.\n");

    return 0;
}
