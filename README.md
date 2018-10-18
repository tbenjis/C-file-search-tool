# Simple Search Tool in C

[![Build Status](https://travis-ci.com/tbenjis/C-file-search-tool.svg?branch=master)](https://travis-ci.com/tbenjis/C-file-search-tool)

The application searches through a file, replaces words, underlines the search results, specifies the line number, starting character location, and writes results to an output file.

<strong>Sample output: </strong>
```
Searched for word "application"

L4/1: The application searches through a file, replaces words, marks search results...
          ^^^^^^^^^^^     
```

## Compiling
Execute `gcc -o search_tool search_tool.c`


## Usage 
`./search_tool -f input_filename -s search_word -r replace_word -o output_file -h`

or 

`./search_tool -f input_filename -s search_word`

or

`./search_tool -f input_filename -s search_word -r replace_word`

## Licence

```
Copyright (c) [2018] tbenjis

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
```
