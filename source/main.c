///////////////////////////////////////////////////////////////////////////////
// NAME:            main.c
//
// AUTHOR:          Ethan D. Twardy <ethan.twardy@gmail.com>
//
// DESCRIPTION:     Entrypoint for the application
//
// CREATED:         12/03/2021
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

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <glib-2.0/glib.h>

#include "config.h"
#include "configuration.h"
#include "argparse.h"
#include "parser-generator.h"

int main(int argc, char** argv) {
    int result = 0;
    ArgpArguments arguments = {
        .output_basename="argparse",
        .input_file="gobiargp-config.yaml",
    };

    // Parse arguments, load configuration from input file.
    gobi_argp_parse_args(&arguments, argc, argv);
    ArgpConfig* config = gobiargp_load_configuration(arguments.input_file);

    size_t output_file_path_length = strlen(arguments.output_basename) + 3;
    char* output_header = malloc(output_file_path_length);
    if (NULL == output_header) {
        fprintf(stderr, "Couldn't allocate memory: %s\n", strerror(errno));
        result = __LINE__;
        goto error_malloc_header;
    }

    char* output_source = malloc(output_file_path_length);
    if (NULL == output_source) {
        fprintf(stderr, "Couldn't allocate memory: %s\n", strerror(errno));
        result = __LINE__;
        goto error_malloc_source;
    }

    // Setup path names for output source, <base>.c and <base>.h
    strcpy(output_source, arguments.output_basename);
    strcat(output_source, ".c");
    strcpy(output_header, arguments.output_basename);
    strcat(output_header, ".h");

    FILE* output_source_file = fopen(output_source, "w");
    if (NULL == output_source_file) {
        fprintf(stderr, "Couldn't open source file for writing: %s\n",
            strerror(errno));
        result = __LINE__;
        goto error_open_source;
    }

    FILE* output_header_file = fopen(output_header, "w");
    if (NULL == output_header_file) {
        fprintf(stderr, "Couldn't open header file for writing: %s\n",
            strerror(errno));
        result = __LINE__;
        goto error_open_header;
    }

    ParserGenerator* parser = parser_generator_new();

    ParserContext header_context = {
        .filename = output_header,
    };

    parser_generator_write_header(parser, &header_context, output_header_file);

    ParserContext source_context = {
        .filename = output_source,
    };

    parser_generator_write_source(parser, &source_context, output_source_file);
    parser_generator_free(&parser);

    fclose(output_header_file);
 error_open_header:
    fclose(output_source_file);
 error_open_source:
    free(output_source);
 error_malloc_source:
    free(output_header);
 error_malloc_header:
    gobiargp_free_configuration(&config);
    return result;
}

///////////////////////////////////////////////////////////////////////////////
