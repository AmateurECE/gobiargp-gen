///////////////////////////////////////////////////////////////////////////////
// NAME:            gobiargp.h
//
// AUTHOR:          Ethan D. Twardy <ethan.twardy@gmail.com>
//
// DESCRIPTION:     Parser declarations
//
// CREATED:         12/03/2021
//
// LAST EDITED:     12/03/2021
//
// Copyright 2021, Ethan D. Twardy
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to
// deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
// IN THE SOFTWARE.
////

#ifndef GOBIARGP_H
#define GOBIARGP_H

// Structure holding the parsed program arguments. Query this container using
// the functions available below to get configuration passed to the program.
typedef struct GobiProgramArguments {
    int unused;
} GobiProgramArguments;

// Parse arguments passed to main, allocating a GobiProgramArguments object
// using malloc(3).
GobiProgramArguments* gobiargp_parse_args(int argc, char** argv);

// Free a GobiProgramArguments object and all internally allocated memory. The
// pointer-to-pointer here allows internal logic to prevent accidental
// double-freeing
void gobiargp_args_free(GobiProgramArguments** args);

// Attempt to obtain the value of the argument with name <argument_name> as an
// integer. If no argument matching the name was provided, return
// <default_value>.
int gobiargp_get_argument_int(GobiProgramArguments* arguments,
    const char* argument_name, int default_value);

#endif // GOBIARGP_H

///////////////////////////////////////////////////////////////////////////////
