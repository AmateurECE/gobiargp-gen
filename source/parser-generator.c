///////////////////////////////////////////////////////////////////////////////
// NAME:            parser-generator.c
//
// AUTHOR:          Ethan D. Twardy <ethan.twardy@gmail.com>
//
// DESCRIPTION:     Implementation of the parser generator.
//
// CREATED:         12/23/2021
//
// LAST EDITED:     12/24/2021
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

#include <stdio.h>

#include "parser-generator.h"

// Forward declarations from generated frozen chunks.
extern const char file_banner[];
extern const char program_usage[];
extern const char priv_functions[];
extern const char priv_parse_flag_arg[];
extern const char parse_args_entrypoint[];

///////////////////////////////////////////////////////////////////////////////
// Public API
////

void generate_argparse_header(FILE* output_header) {
    fprintf(output_header, file_banner);
}

void generate_argparse_source(FILE* output_source) {
    fprintf(output_source, file_banner);
    fprintf(output_source, program_usage);
}

///////////////////////////////////////////////////////////////////////////////
