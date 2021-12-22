///////////////////////////////////////////////////////////////////////////////
// NAME:            configuration.c
//
// AUTHOR:          Ethan D. Twardy <ethan.twardy@gmail.com>
//
// DESCRIPTION:     Logic for loading/parsing configuration.
//
// CREATED:         12/21/2021
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
#include <stdlib.h>
#include <string.h>

#include <glib-2.0/glib.h>
#include <gobiserde/yaml.h>

#include "configuration.h"

///////////////////////////////////////////////////////////////////////////////
// Private API
////

static int priv_argp_config_visit_arg_map(yaml_deserializer* deser,
    void* user_data, const char* key)
{
    ArgpArgument* object = (ArgpArgument*)user_data;
    int result = -1;
    if (!strcmp(key, "short")) {
        char* string = NULL;
        result = gobiserde_yaml_deserialize_string(deser, &string);
        if (1 > result) {
            return -1;
        }

        size_t string_length = strlen(string);
        if (1 == string_length) {
            object->short_name = string[0];
        } else {
            // TODO: Handle error case
        }
        free(string);
    }

    else if (!strcmp(key, "long")) {
        result = gobiserde_yaml_deserialize_string(deser, &object->long_name);
    } else if (!strcmp(key, "value_name")) {
        result = gobiserde_yaml_deserialize_string(deser, &object->value_name);
    } else if (!strcmp(key, "help")) {
        result = gobiserde_yaml_deserialize_string(deser, &object->help);
    } else if (!strcmp(key, "takes_value")) {
        result = gobiserde_yaml_deserialize_bool(deser, &object->takes_value);
    } else if (!strcmp(key, "required")) {
        result = gobiserde_yaml_deserialize_bool(deser, &object->required);
    } else if (!strcmp(key, "index")) {
        result = gobiserde_yaml_deserialize_int(deser, &object->index);
    } else if (!strcmp(key, "multiple")) {
        result = gobiserde_yaml_deserialize_bool(deser, &object->multiple);
    }

    return result;
}

static int priv_argp_config_visit_arg_map_entry(yaml_deserializer* deser,
    void* user_data, const char* key)
{
    ArgpConfig* config = (ArgpConfig*)user_data;
    ArgpArgument* argument = malloc(sizeof(ArgpArgument));
    if (NULL == argument) {
        return -1 * errno;
    }

    memset(argument, 0, sizeof(ArgpArgument));
    int result = gobiserde_yaml_deserialize_map(deser,
        priv_argp_config_visit_arg_map, argument);
    if (1 > result) {
        free(argument);
        return result;
    }

    g_hash_table_insert(config->args, g_strdup(key), argument);
    return result;
}

static int priv_argp_config_visit_map(yaml_deserializer* deser,
    void* user_data, const char* key)
{
    ArgpConfig* config = (ArgpConfig*)user_data;
    int result = -1;
    if (!strcmp(key, "name")) {
        result = gobiserde_yaml_deserialize_string(deser, &config->name);
    } else if (!strcmp(key, "version")) {
        result = gobiserde_yaml_deserialize_string(deser, &config->version);
    } else if (!strcmp(key, "author")) {
        result = gobiserde_yaml_deserialize_string(deser, &config->author);
    } else if (!strcmp(key, "about")) {
        result = gobiserde_yaml_deserialize_string(deser, &config->about);
    } else if (!strcmp(key, "args")) {
        result = gobiserde_yaml_deserialize_map(deser,
            priv_argp_config_visit_arg_map_entry, config);
    }

    return result;
}

static int priv_argp_config_deserialize_yaml(yaml_deserializer* deser,
    ArgpConfig* config)
{
    return gobiserde_yaml_deserialize_map(deser, priv_argp_config_visit_map,
        config);
}

///////////////////////////////////////////////////////////////////////////////
// Public API
////

ArgpConfig* gobiargp_load_configuration(const char* filename) {
    ArgpConfig* config = malloc(sizeof(ArgpConfig));
    if (NULL == config) {
        return NULL;
    }

    FILE* input = fopen(filename, "rb");
    yaml_deserializer* deser = gobiserde_yaml_deserializer_new_file(input);
    config->args = g_hash_table_new(g_str_hash, g_str_equal);
    if (0 > priv_argp_config_deserialize_yaml(deser, config)) {
        g_hash_table_unref(config->args);
        free(config);
        fclose(input);
        return NULL;
    }

    fclose(input);
    return config;
}

void gobiargp_free_configuration(ArgpConfig** configuration) {
    if (NULL == *configuration) {
        return;
    }

    free((*configuration)->name);
    free((*configuration)->version);
    free((*configuration)->author);
    free((*configuration)->about);
    free(*configuration);
    *configuration = NULL;
}

///////////////////////////////////////////////////////////////////////////////
