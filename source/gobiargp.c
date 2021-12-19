///////////////////////////////////////////////////////////////////////////////
// NAME:            gobiargp.c
//
// AUTHOR:          Ethan D. Twardy <ethan.twardy@gmail.com>
//
// DESCRIPTION:     Argument Parser
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

#include <stdio.h>

#include <gobiargp.h>

typedef struct GobiOption {
    char short_name;
    const char* long_name;
} GobiOption;

typedef struct GobiArgument {
    const char* name;
} GobiArgument;

typedef struct GobiProgram GobiProgram;
typedef struct GobiProgram {
    const char* name;
    const char* version;
    const char* author_name;
    const char* author_email;
    const char* copyright;
    const GobiOption* options;
    const GobiArgument* arguments;
    const GobiProgram* subcommands;
} GobiProgram;

static const char* GOBI_HELP_FORMAT = "\
%s %s %s <%s>\n\
%s%s\
%s\n\
";
static const char* GOBI_USAGE = "usage: gobitest [--test=<test>]";
static const char* GOBI_HELP = "\n\
Optional arguments:\n\
  -t,--test <test>: The value of the test argument\n\
";

static const GobiOption gobi_options[] = {
    { 0 },
};

static const GobiArgument gobi_arguments[] = {
    { 0 },
};

static const GobiProgram gobi_subcommands[] = {
    { 0 },
};

static const GobiProgram gobi_program = {
    .name = "gobitest",
    .version = "v0.1.0",
    .author_name = "Ethan D. Twardy",
    .author_email = "ethan.twardy@gmail.com",
    .copyright = NULL,
    .options = gobi_options,
    .arguments = gobi_arguments,
    .subcommands = gobi_subcommands,
};

static void gobiargp_print_usage() {
    fprintf(stderr, GOBI_HELP_FORMAT,
        gobi_program.name, gobi_program.version,
        gobi_program.author_name, gobi_program.author_email,
        gobi_program.copyright ? gobi_program.copyright : "",
        gobi_program.copyright ? "\n\n" : "",
        GOBI_USAGE);
}

static void gobiargp_print_help(const char* message) {
    gobiargp_print_usage();
    fprintf(stderr, GOBI_HELP);
}

GobiProgramArguments* gobiargp_parse_args(int argc, char** argv) {
    gobiargp_print_help(GOBI_HELP);
}

int gobiargp_get_argument_int(GobiProgramArguments* arguments,
    const char* argument_name, int default_value)
{ return 0; }

void gobiargp_args_free(GobiProgramArguments** arguments) {
    if (NULL == *arguments) {
        return;
    }

    free(*arguments);
    *arguments = NULL;
}

///////////////////////////////////////////////////////////////////////////////
