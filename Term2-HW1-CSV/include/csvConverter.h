#pragma once

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readLine(FILE* f);
int getTrimmedLen(const char* start, int len);
void printRowSeparation(
    const char* lSymb, const char* mSymb, const char* rSymb, const char* symb, int cols, int colLength, FILE* file);
int trimCsvField(char* field);
int isDouble(const char* str);
int convertCsvToTxt(FILE* csvFile, FILE* txtFile);
