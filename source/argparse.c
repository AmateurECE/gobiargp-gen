///////////////////////////////////////////////////////////////////////////////
// NAME:            argparse.c
//
// AUTHOR:          Ethan D. Twardy <ethan.twardy@gmail.com>
//
// DESCRIPTION:     Logic implementing argument parser
//
// CREATED:         12/22/2021
//
// LAST EDITED:     12/23/2021
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
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "argparse.h"

///////////////////////////////////////////////////////////////////////////////
// Private API
////

static const char* PROGRAM_VERSION = CONFIG_VERSION;
static const char* PROGRAM_AUTHOR = "Ethan D. Twardy <ethan.twardy@gmail.com>";
static const char* PROGRAM_DESCRIPTION = "\
Command-line argument parser generator written in C, for C. Inspired by\n\
Rust's clap crate (https://crates.io/crates/clap/).\n\
";
static const char* PROGRAM_USAGE = "\
gobiargp-gen %s\n\
Copyright (c) 2021 %s. All rights reserved.\n\
This program is free software.\n\
%s\
\n\
usage: gobiargp-gen [options]\n\
\n\
Options:\n\
    -f,--file[ =]<file>: The YAML input file to the program. This file has a\n\
        format very similar to the YAML schema accepted by clap. See either\n\
        the manpage for this program, gobiargp-gen(1), or the docs for \n\
        clap.rs (https://docs.rs/clap/) to get a better understanding.\n\
    -o,--output[ =]<output>: The filename stem to use when creating output\n\
        files. For example, with -o dir/test, the program creates test.h and\n\
        test.c in the directory ./dir.\n\
";

static _Noreturn inline void priv_takes_arg(char* bad_argument) {
    fprintf(stderr, "Argument '%s' takes a value of the form '%s=<value>' or "
        "'%s <value>'. See --help.\n", bad_argument, bad_argument,
        bad_argument);
    exit(1);
}

static _Noreturn inline void priv_bad_arg(char* bad_argument) {
    fprintf(stderr, "Unknown argument '%s'\nSee --help for usage\n",
        bad_argument);
    exit(1);
}

static _Noreturn inline void priv_usage() {
    fprintf(stderr, PROGRAM_USAGE, PROGRAM_VERSION, PROGRAM_AUTHOR,
        PROGRAM_DESCRIPTION);
    exit(1);
}

// Parse a single flag argument. This function accepts flags that take a value,
// which can be of the form (e.g. for a flag '-f') "-f=value", "-f value". If
// the value starts with '-', then the first form must be used, or else the
// value is taken to be the start of a new flag.
static void priv_parse_flag_arg(char** output, int* index, int argc,
    char** argv)
{
    char* argument = strchr(argv[*index], '=');
    if (NULL != argument) {
        *output = argument + 1;
        return;
    }

    if (*index + 1 >= argc || '-' == argv[*index + 1][0]) {
        priv_usage();
    }

    *index += 1;
    *output = argv[*index];
}

///////////////////////////////////////////////////////////////////////////////
// Public API
////

// Parse command line arguments. Some advantages of this parser:
//  * This program currently has no positional arguments, which means we can
//    ignore '--'.
//  * There are no subcommands.
//  * All flags currently take arguments.
void gobi_argp_parse_args(ArgpArguments* arguments, int argc, char** argv) {
    for (int i = 1; i < argc; ++i) {
        if ('-' == argv[i][0]) {
            switch (argv[i][1]) {
            case 'f': // TODO
                priv_parse_flag_arg(&arguments->input_file, &i, argc, argv);
                break;
            case 'o': // TODO
                priv_parse_flag_arg(&arguments->output_basename, &i, argc,
                    argv);
                break;

            case '?': // Currently, -h, --help and -? are supported for usage.
                priv_usage();
                break;
            case 'h':
                priv_usage();
                break;
            case '-': // Currently, the only long flag is --help.
                priv_usage();
                break;
            default:
                priv_bad_arg(argv[i]);
                break;
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
