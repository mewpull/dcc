/*
 * Copyright (C) 1991-4, Cristina Cifuentes
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

// dcc project error messages

#include "dcc.h"
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

static char *errorMessage[] = {
    "Invalid option -%c\n",                                         // INVALID_ARG
    "Invalid instruction %02X at location %06lX\n",                 // INVALID_OPCODE
    "Don't understand 80386 instruction %02X at location %06lX\n",  // INVALID_386OP
    "Segment override with no memory operand at location %06lX\n",  // FUNNY_SEGOVR
    "REP prefix without a string instruction at location %06lX\n",  // FUNNY_REP
    "Cannot open %s\n",                                             // CANNOT_OPEN
    "Error while reading %s\n",                                     // CANNOT_READ
    "malloc of %ld bytes failed\n",                                 // MALLOC_FAILED
    "Don't understand new EXE format\n",                            // NEWEXE_FORMAT
    "Failed to find a BB for jump to %ld in proc %s\n",             // NO_BB
    "Basic Block is a synthetic jump\n",                            // INVALID_SYNTHETIC_BB
    "Failed to find a BB for interval\n",                           // INVALID_INT_BB
    "Instruction at location %06lX goes beyond loaded image\n",     // IP_OUT_OF_RANGE
    "Definition not found for condition code usage at opcode %d\n", // DEF_NOT_FOUND
    "JX use, definition not supported at opcode #%d\n",             // JX_NOT_DEF
    "Def - use not supported.  Def op = %d, use op = %d.\n",        // NOT_DEF_USE
    "Failed to construct repeat..until() condition.\n",             // REPEAT_FAIL
    "Failed to construct while() condition.\n",                     // WHILE_FAIL
};

// fatalError: displays error message and exits the program.
void fatalError(error_msg id, ...)
{
    va_list args;
    va_start(args, id);

    if (id == USAGE)
        fprintf(stderr, "Usage: %s [-hvVsmiaA][-f DOS_executable]\n", progname);
    else {
        fprintf(stderr, "%s: ", progname);
        vfprintf(stderr, errorMessage[id - 1], args);
    }
    va_end(args);
    exit(EXIT_FAILURE);
}

// reportError: reports the warning/error and continues with the program.
void reportError(error_msg id, ...)
{
    va_list args;
    va_start(args, id);

    fprintf(stderr, "%s: ", progname);
    vfprintf(stderr, errorMessage[id - 1], args);
    va_end(args);
}

void dcc_error(const char *str, ...)
{
    va_list arg;
    va_start(arg, str);
    fprintf(stderr, str, arg);
    va_end(arg);

    exit(EXIT_FAILURE);
}
