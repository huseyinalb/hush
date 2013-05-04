//
//  parser.h
//  hush
//
//  Created by huseyin oguz albayrak on 04.05.2013.
//  Copyright (c) 2013 huseyin oguz albayrak. All rights reserved.
//

#ifndef hush_parser_h
#define hush_parser_h

#include <regex.h>
#include <string.h>

#include "datatypes/list.h"
#include "datatypes/tree.h"

List* tokenize(char*);
struct Tree* parse_command(List*);

#define PARSER_MAX_BUFF 512

#endif
