//
//  interpreter.h
//  hush
//
//  Created by huseyin oguz albayrak on 04.05.2013.
//  Copyright (c) 2013 huseyin oguz albayrak. All rights reserved.
//

#ifndef hush_interpreter_h
#define hush_interpreter_h

#include <stdio.h>
#include <errno.h>
#include <unistd.h>

#include "datatypes/list.h"
#include "datatypes/tree.h"
void run_command(TreeNode* stmt);
#endif
