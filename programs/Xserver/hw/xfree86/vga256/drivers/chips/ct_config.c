/* $XFree86$ */
/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */



/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#include "X.h"

#include "input.h"
#include "screenint.h"
#include "xf86.h"
#include "xf86_Option.h"
#include "xf86_Config.h"
#include "xf86Priv.h"
#include "compiler.h"
#include "xf86DCConf.h"

#include "vga.h"

/* This is a sample implementation of a driver config file */

OptFlagRec tab[] = {
  { "test",    1 },
  { "",       -1 },
};

static SymTabRec ct_tab[] = {
  { 1,  "test" },
  { -1, ""},
};


void ctConfig()
{
  char *DCointer, *OPointer;
  int lineno;
  int token;
  OFlagSet *OFlags; 
  
  DCointer = vga256InfoRec.DCConfig;
  OPointer = vga256InfoRec.DCOptions;
  ErrorF("testing DCointer\n");
  while ((token = xf86DCGetToken(DCointer,ct_tab,DeviceTab)) != EOF){
    switch (token) {
    case STRING:
      ErrorF("string: %s\n",DCval.str);
      break;
    case NUMBER:
      ErrorF("number: int: %i; float %f\n",DCval.num,DCval.realnum);
      break;
    case ERROR_TOKEN:
      ErrorF("error_token\n");
      xf86DCConfigError("Error Token\n");
      break;
    case DASH:
      ErrorF("dash\n");
      break;
    case COMMA:
      ErrorF("Comma\n");
      break;
    case 1:
      ErrorF("valid token:  ");
      token = xf86DCGetToken(DCointer,NULL,DeviceTab);
      if(token == NUMBER)
	ErrorF("argument: %i, %f\n",DCval.num, DCval.realnum);
      else {
	DCpushToken = token;
	ErrorF("\n");
      }
      break;
    default:
      ErrorF("default\n");
    }
 }

  ErrorF("testing OPointer\n");
OFlags = xf86DCGetOption(OPointer, tab);
}


