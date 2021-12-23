///////////////////////////////////////////////////////////////////////////////
// NAME:            parser-generator.c
//
// AUTHOR:          Ethan D. Twardy <ethan.twardy@gmail.com>
//
// DESCRIPTION:     Implementation of the parser generator.
//
// CREATED:         12/23/2021
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

#include <ctype.h>
#include <stdio.h>
#include <string.h>

#include <libxml/xpath.h>

#include "parser-generator.h"

///////////////////////////////////////////////////////////////////////////////
// Private API
////

static char* trim_whitespace(char *string) {
    char* end = NULL;

    // Trim leading space
    while(isspace((unsigned char)*string)) string++;

    if(0 == *string)  // All spaces?
        return string;

    // Trim trailing space
    end = string + strlen(string) - 1;
    while(end > string && isspace((unsigned char)*end)) end--;

    // Write new null terminator character
    end[1] = '\0';
    return string;
}

///////////////////////////////////////////////////////////////////////////////
// Public API
////

void generate_argument_parser(xmlDoc* document, FILE* output_source,
    FILE* output_header)
{
    xmlXPathContext* xpathContext = xmlXPathNewContext(document);
    if (NULL == xpathContext) {
        fprintf(stderr, "Unable to create XPath context!\n");
        return;
    }

    static const char* node_path = "//parser/chunk[@id=\"comment\"]";
    xmlXPathObject* xpathObject = xmlXPathEvalExpression(
        (const xmlChar*)node_path, xpathContext);
    if (NULL == xpathObject) {
        fprintf(stderr, "Unable to evaluate XPath expression '%s'\n",
            node_path);
        xmlXPathFreeContext(xpathContext);
        return;
    }

    xmlNode* text_node = xpathObject->nodesetval->nodeTab[0]->children;
    const char* comment = trim_whitespace((char*)text_node->content);
    fprintf(output_source, "%s\n", comment);
    fprintf(output_header, "%s\n", comment);
}

///////////////////////////////////////////////////////////////////////////////
