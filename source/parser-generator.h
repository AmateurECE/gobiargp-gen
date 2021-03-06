///////////////////////////////////////////////////////////////////////////////
// NAME:            parser-generator.h
//
// AUTHOR:          Ethan D. Twardy <ethan.twardy@gmail.com>
//
// DESCRIPTION:     Interface for the parser generator.
//
// CREATED:         12/23/2021
//
// LAST EDITED:     12/25/2021
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

#ifndef PARSER_GENERATOR_H
#define PARSER_GENERATOR_H

#include <stdlib.h>

typedef struct ParserGenerator ParserGenerator;
typedef struct ArgpConfig ArgpConfig;

typedef struct ParserContext {
    const char* filename;
    ArgpConfig* config;
} ParserContext;

ParserGenerator* parser_generator_new();
void parser_generator_free(ParserGenerator** parser);
void parser_generator_write_header(ParserGenerator* parser,
    ParserContext* context, FILE* output);
void parser_generator_write_source(ParserGenerator* parser,
    ParserContext* context, FILE* output);

#endif // PARSER_GENERATOR_H

///////////////////////////////////////////////////////////////////////////////
