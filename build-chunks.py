###############################################################################
# NAME:             build-chunks.py
#
# AUTHOR:           Ethan D. Twardy <ethan.twardy@gmail.com>
#
# DESCRIPTION:      Take the input file and generate a C source file.
#
# CREATED:          12/24/2021
#
# LAST EDITED:      12/24/2021
#
# Copyright 2021, Ethan D. Twardy
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to
# deal in the Software without restriction, including without limitation the
# rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
# sell copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
# IN THE SOFTWARE.
###

import argparse
from subprocess import Popen, PIPE, STDOUT
import sys
import os

def freeze_blobs(input_file, output_file):
    """Write the frozen blobs to the output file"""
    blob_lines = []
    for line in input_file:
        if line.startswith('//!'):
            output_file.write(b'const char '
                              + bytearray(line[4:].strip(), 'ascii')
                              + b'[] = {\n')
            xxd = Popen(['xxd', '-i'], stdout=PIPE, stdin=PIPE, stderr=PIPE)
            output_file.write(xxd.communicate(input=bytearray(
                ''.join(blob_lines), 'ascii'))[0])
            output_file.write(b'};\n\n')
            blob_lines = []
        else:
            blob_lines.append(line)

def main():
    """Entrypoint for the program"""
    parser = argparse.ArgumentParser()
    parser.add_argument('input_file', help='Input file')
    parser.add_argument('output_file', help='Output file', default='-')
    args = parser.parse_args()

    with open(args.input_file) as input_file:
        if '-' == args.output_file:
            with os.fdopen(sys.stdout.fileno(), "wb", closefd=False) as out:
                freeze_blobs(input_file, out)
        else:
            with open(args.output_file, 'wb') as output_file:
                freeze_blobs(input_file, output_file)

if __name__ == '__main__':
    main()

###############################################################################
