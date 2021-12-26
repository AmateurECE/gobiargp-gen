///////////////////////////////////////////////////////////////////////////////
// NAME:            parser-generator.c
//
// AUTHOR:          Ethan D. Twardy <ethan.twardy@gmail.com>
//
// DESCRIPTION:     Implementation of the parser generator.
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

#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>

#include <handlebars.h>

#include "parser-generator.h"
#include "configuration.h"

// Forward declarations from generated frozen chunks.
extern const char file_banner[];
extern const char priv_functions[];
extern const char priv_parse_flag_arg[];
extern const char parse_args_entrypoint[];

static const char* PROGRAM_USAGE_TEMPLATE = "\
static const char* PROGRAM_USAGE = \"\\\n\
%s %s\\n\\\n\
%s\\n\\\n\
%s\\n\\\n\
\\n\\\n\
\";\n\
";

typedef struct ParserGenerator {
    Handlebars* file_banner;
} ParserGenerator;

///////////////////////////////////////////////////////////////////////////////
// Private API
////

void priv_write_banner(Handlebars* file_banner, ParserContext* context,
    FILE* output)
{
    HbTemplateContext* file_banner_input = handlebars_template_context_init();
    handlebars_template_context_set_string(file_banner_input, "filename",
        context->filename);

    time_t current_time = time(NULL);
    struct tm* date = gmtime(&current_time);
    char date_string[11] = {0};
    snprintf(date_string, sizeof(date_string), "%d/%d/%d", date->tm_mon + 1,
        date->tm_mday, date->tm_year + 1900);
    handlebars_template_context_set_string(file_banner_input, "date",
        date_string);
    HbString* file_banner_content = handlebars_template_render(
        file_banner, file_banner_input);
    handlebars_template_context_free(&file_banner_input);
    fprintf(output, file_banner_content->string);
    hb_string_free(&file_banner_content);
}

void priv_write_program_usage(ParserContext* context, FILE* output) {
    fprintf(output, PROGRAM_USAGE_TEMPLATE,
        context->config->name, context->config->version,
        context->config->author,
        context->config->about);
}

///////////////////////////////////////////////////////////////////////////////
// Public API
////

ParserGenerator* parser_generator_new() {
    ParserGenerator* parser = malloc(sizeof(ParserGenerator));
    if (NULL == parser) {
        return NULL;
    }

    memset(parser, 0, sizeof(ParserGenerator));

    static const char* const blobs[] = {file_banner, NULL};
    Handlebars** templates[] = {&parser->file_banner, NULL};
    ssize_t index = -1;
    while (NULL != blobs[++index]) {
        HbInputContext* input = handlebars_input_context_from_string(
            blobs[index]);
        *templates[index] = handlebars_template_load(input);
        handlebars_input_context_free(&input);
    }
    return parser;
}

void parser_generator_free(ParserGenerator** parser) {
    if (NULL == *parser) {
        return;
    }

    handlebars_template_free(&(*parser)->file_banner);
    free(*parser);
    *parser = NULL;
}

void parser_generator_write_header(ParserGenerator* parser,
    ParserContext* context, FILE* output_header)
{
    priv_write_banner(parser->file_banner, context, output_header);
}

void parser_generator_write_source(ParserGenerator* parser,
    ParserContext* context, FILE* output_source)
{
    priv_write_banner(parser->file_banner, context, output_source);
    fprintf(output_source, "\n");
    priv_write_program_usage(context, output_source);
    fprintf(output_source, "%s\n", priv_functions);
}

///////////////////////////////////////////////////////////////////////////////
