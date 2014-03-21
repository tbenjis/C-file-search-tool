C-file-search-tool
==================

The application searches through a file, replaces words, marks search results and writes results to an output file.

Works on Linux. 

Usage: ./search_tool -f input_filename -s search_word -r replace_word -o output_file -h



-f : This option define input file name which is used for processing

-s : This option define search word which we need to search in input file. If user want to search two words in this case you can use with double quote chars. (Ex: \"sample word\")

-r : This option define replace word which replaced with searched one. This option also should support double quote input as -s option have.

-o : This option define output file in this case result redirect into this file.

-h : This option gives help text to user.
