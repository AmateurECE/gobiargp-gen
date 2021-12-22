///////////////////////////////////////////////////////////////////////////////
// NAME:            main.c
//
// AUTHOR:          Ethan D. Twardy <ethan.twardy@gmail.com>
//
// DESCRIPTION:     Entrypoint for the application
//
// CREATED:         12/03/2021
//
// LAST EDITED:     12/22/2021
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

#include <glib-2.0/glib.h>

#include "configuration.h"

int main() {
    ArgpConfig* config = gobiargp_load_configuration("test.yaml");
    printf("name=%s,version=%s\nAuthor: %s\nAbout: %s\n", config->name,
        config->version, config->author, config->about);

    GHashTableIter iterator;
    g_hash_table_iter_init(&iterator, config->args);
    ArgpArgument* element = NULL;
    const char* key = NULL;
    printf("Args:\n");
    while (g_hash_table_iter_next(&iterator, (void**)&key, (void**)&element)) {
        printf("    %s=%p\n", key, (void*)element);
        printf("        long_name=%s\n", element->long_name);
        printf("        short_name=%c\n", element->short_name);
        printf("        takes_value=%s\n",
            element->takes_value ? "true" : "false");
        printf("        value_name=%s\n", element->value_name);
        printf("        help=%s\n", element->help);
        printf("        required=%s\n", element->required ? "true" : "false");
        printf("        index=%d\n", element->index);
        printf("        multiple=%s\n", element->multiple ? "true" : "false");
    }
}

///////////////////////////////////////////////////////////////////////////////
