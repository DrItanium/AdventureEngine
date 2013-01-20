   /*******************************************************/
   /*      "C" Language Integrated Production System      */
   /*                                                     */
   /*             CLIPS Version 6.22  06/15/04            */
   /*                                                     */
   /*           FACT RETE PRINT FUNCTIONS MODULE          */
   /*******************************************************/

/*************************************************************/
/* Purpose: Print routines for the fact rete primitives.     */
/*                                                           */
/* Principal Programmer(s):                                  */
/*      Gary D. Riley                                        */
/*                                                           */
/* Contributing Programmer(s):                               */
/*                                                           */
/* Revision History:                                         */
/*                                                           */
/*************************************************************/

#define _FACTPRT_SOURCE_

#include <stdio.h>
#define _STDIO_INCLUDED_

#include "setup.h"

#if DEFTEMPLATE_CONSTRUCT && DEFRULE_CONSTRUCT

#include "envrnmnt.h"
#include "symbol.h"
#include "router.h"
#include "factgen.h"

#include "factprt.h"

/***************************************/
/* PrintFactJNCompVars1: Print routine */
/*   for the FactJNCompVars1 function. */
/***************************************/
#if WIN_BTC && (! DEVELOPER)
#pragma argsused
#endif
globle void PrintFactJNCompVars1(
  void *theEnv,
  char *logicalName,
  void *theValue)
  {
#if DEVELOPER
   struct factCompVarsJN1Call *hack;

   hack = (struct factCompVarsJN1Call *) ValueToBitMap(theValue);
   EnvPrintRouter(theEnv,logicalName,(char*)"(fact-jn-cmp-vars1 ");
   if (hack->pass) EnvPrintRouter(theEnv,logicalName,(char*)"= ");
   else EnvPrintRouter(theEnv,logicalName,(char*)"<> ");
   
   EnvPrintRouter(theEnv,logicalName,(char*)"p");
   PrintLongInteger(theEnv,logicalName,(long long) hack->pattern1);

   if (hack->p1lhs)
     { EnvPrintRouter(theEnv,logicalName,(char*)" L"); }
   else if (hack->p1rhs)
     { EnvPrintRouter(theEnv,logicalName,(char*)" R"); }
   
   EnvPrintRouter(theEnv,logicalName,(char*)" s");
   PrintLongInteger(theEnv,logicalName,(long long) hack->slot1);

   EnvPrintRouter(theEnv,logicalName,(char*)" p");
   PrintLongInteger(theEnv,logicalName,(long long) hack->pattern2);

   if (hack->p2lhs)
     { EnvPrintRouter(theEnv,logicalName,(char*)" L"); }
   else if (hack->p2rhs)
     { EnvPrintRouter(theEnv,logicalName,(char*)" R"); }

   EnvPrintRouter(theEnv,logicalName,(char*)" s");
   PrintLongInteger(theEnv,logicalName,(long long) hack->slot2);
   EnvPrintRouter(theEnv,logicalName,(char*)")");
#else
#if MAC_MCW || WIN_MCW || MAC_XCD
#pragma unused(theEnv)
#pragma unused(logicalName)
#pragma unused(theValue)
#endif
#endif
  }

/***************************************/
/* PrintFactJNCompVars2: Print routine */
/*   for the FactJNCompVars2 function. */
/***************************************/
#if WIN_BTC && (! DEVELOPER)
#pragma argsused
#endif
globle void PrintFactJNCompVars2(
  void *theEnv,
  char *logicalName,
  void *theValue)
  {
#if DEVELOPER
   struct factCompVarsJN2Call *hack;

   hack = (struct factCompVarsJN2Call *) ValueToBitMap(theValue);
   EnvPrintRouter(theEnv,logicalName,(char*)"(fact-jn-cmp-vars2 ");
   if (hack->pass) EnvPrintRouter(theEnv,logicalName,(char*)"= ");
   else EnvPrintRouter(theEnv,logicalName,(char*)"<> ");

   EnvPrintRouter(theEnv,logicalName,(char*)"p");
   PrintLongInteger(theEnv,logicalName,(long long) hack->pattern1);

   if (hack->p1lhs)
     { EnvPrintRouter(theEnv,logicalName,(char*)" L"); }
   else if (hack->p1rhs)
     { EnvPrintRouter(theEnv,logicalName,(char*)" R"); }

   EnvPrintRouter(theEnv,logicalName,(char*)" s");
   PrintLongInteger(theEnv,logicalName,(long long) hack->slot1);

   if (hack->fromBeginning1) EnvPrintRouter(theEnv,logicalName, (char*)" b");
   else EnvPrintRouter(theEnv,logicalName,(char*)" e");

   EnvPrintRouter(theEnv,logicalName,(char*)" f");
   PrintLongInteger(theEnv,logicalName,(long long) hack->offset1);

   EnvPrintRouter(theEnv,logicalName,(char*)" p");
   PrintLongInteger(theEnv,logicalName,(long long) hack->pattern2);

   if (hack->p2lhs)
     { EnvPrintRouter(theEnv,logicalName,(char*)" L"); }
   else if (hack->p2rhs)
     { EnvPrintRouter(theEnv,logicalName,(char*)" R"); }

   EnvPrintRouter(theEnv,logicalName,(char*)" s");
   PrintLongInteger(theEnv,logicalName,(long long) hack->slot2);

   if (hack->fromBeginning2) EnvPrintRouter(theEnv,logicalName,(char*)" b");
   else EnvPrintRouter(theEnv,logicalName,(char*)" e");

   EnvPrintRouter(theEnv,logicalName,(char*)" f");
   PrintLongInteger(theEnv,logicalName,(long long) hack->offset2);
   EnvPrintRouter(theEnv,logicalName,(char*)")");
#else
#if MAC_MCW || WIN_MCW || MAC_XCD
#pragma unused(theEnv)
#pragma unused(logicalName)
#pragma unused(theValue)
#endif
#endif
  }

/***************************************/
/* PrintFactPNCompVars1: Print routine */
/*   for the FactPNCompVars1 function. */
/***************************************/
#if WIN_BTC && (! DEVELOPER)
#pragma argsused
#endif
globle void PrintFactPNCompVars1(
  void *theEnv,
  char *logicalName,
  void *theValue)
  {
#if DEVELOPER
   struct factCompVarsPN1Call *hack;

   hack = (struct factCompVarsPN1Call *) ValueToBitMap(theValue);
   EnvPrintRouter(theEnv,logicalName,(char*)"(fact-pn-cmp-vars ");
   if (hack->pass) EnvPrintRouter(theEnv,logicalName,(char*)"p ");
   else EnvPrintRouter(theEnv,logicalName,(char*)"n ");
   PrintLongInteger(theEnv,logicalName,(long long) hack->field1);
   EnvPrintRouter(theEnv,logicalName,(char*)" ");
   PrintLongInteger(theEnv,logicalName,(long long) hack->field2);
   EnvPrintRouter(theEnv,logicalName,(char*)")");
#else
#if MAC_MCW || WIN_MCW || MAC_XCD
#pragma unused(theEnv)
#pragma unused(logicalName)
#pragma unused(theValue)
#endif
#endif
  }

/**************************************/
/* PrintFactSlotLength: Print routine */
/*   for the FactSlotLength function. */
/**************************************/
#if WIN_BTC && (! DEVELOPER)
#pragma argsused
#endif
globle void PrintFactSlotLength(
  void *theEnv,
  char *logicalName,
  void *theValue)
  {
#if DEVELOPER
   struct factCheckLengthPNCall *hack;

   hack = (struct factCheckLengthPNCall *) ValueToBitMap(theValue);

   EnvPrintRouter(theEnv,logicalName,(char*)"(slot-length ");
   PrintLongInteger(theEnv,logicalName,(long long) hack->whichSlot);
   EnvPrintRouter(theEnv,logicalName,(char*)" ");
   if (hack->exactly) EnvPrintRouter(theEnv,logicalName,(char*)"= ");
   else EnvPrintRouter(theEnv,logicalName,(char*)">= ");
   PrintLongInteger(theEnv,logicalName,(long long) hack->minLength);
   EnvPrintRouter(theEnv,logicalName,(char*)")");
#else
#if MAC_MCW || WIN_MCW || MAC_XCD
#pragma unused(theEnv)
#pragma unused(logicalName)
#pragma unused(theValue)
#endif
#endif
  }

/*************************************/
/* PrintFactJNGetVar1: Print routine */
/*   for the FactJNGetvar1 function. */
/*************************************/
#if WIN_BTC && (! DEVELOPER)
#pragma argsused
#endif
globle void PrintFactJNGetVar1(
  void *theEnv,
  char *logicalName,
  void *theValue)
  {
#if DEVELOPER
   struct factGetVarJN1Call *hack;

   hack = (struct factGetVarJN1Call *) ValueToBitMap(theValue);
   EnvPrintRouter(theEnv,logicalName,(char*)"(fact-jn-getvar-1 ");
   if (hack->factAddress) EnvPrintRouter(theEnv,logicalName,(char*)"t ");
   else EnvPrintRouter(theEnv,logicalName,(char*)"f ");
   if (hack->allFields) EnvPrintRouter(theEnv,logicalName,(char*)"t ");
   else EnvPrintRouter(theEnv,logicalName,(char*)"f ");

   EnvPrintRouter(theEnv,logicalName,(char*)"p");
   PrintLongInteger(theEnv,logicalName,(long long) hack->whichPattern + 1);
   EnvPrintRouter(theEnv,logicalName,(char*)" ");
   PrintLongInteger(theEnv,logicalName,(long long) hack->whichField);
   EnvPrintRouter(theEnv,logicalName,(char*)" s");
   PrintLongInteger(theEnv,logicalName,(long long) hack->whichSlot);
   
   if (hack->lhs)
     { EnvPrintRouter(theEnv,logicalName,(char*)" L"); }
   else if (hack->rhs)
     { EnvPrintRouter(theEnv,logicalName,(char*)" R"); }
   EnvPrintRouter(theEnv,logicalName,(char*)")");
#else
#if MAC_MCW || WIN_MCW || MAC_XCD
#pragma unused(theEnv)
#pragma unused(logicalName)
#pragma unused(theValue)
#endif
#endif
  }

/*************************************/
/* PrintFactJNGetVar2: Print routine */
/*   for the FactJNGetvar2 function. */
/*************************************/
#if WIN_BTC && (! DEVELOPER)
#pragma argsused
#endif
globle void PrintFactJNGetVar2(
  void *theEnv,
  char *logicalName,
  void *theValue)
  {
#if DEVELOPER
   struct factGetVarJN2Call *hack;

   hack = (struct factGetVarJN2Call *) ValueToBitMap(theValue);
   EnvPrintRouter(theEnv,logicalName,(char*)"(fact-jn-getvar-2");

   EnvPrintRouter(theEnv,logicalName,(char*)" p");
   PrintLongInteger(theEnv,logicalName,(long long) hack->whichPattern + 1);
   EnvPrintRouter(theEnv,logicalName,(char*)" s");
   PrintLongInteger(theEnv,logicalName,(long long) hack->whichSlot);
   if (hack->lhs)
     { EnvPrintRouter(theEnv,logicalName,(char*)" L"); }
   else if (hack->rhs)
     { EnvPrintRouter(theEnv,logicalName,(char*)" R"); }
   EnvPrintRouter(theEnv,logicalName,(char*)")");
#else
#if MAC_MCW || WIN_MCW || MAC_XCD
#pragma unused(theEnv)
#pragma unused(logicalName)
#pragma unused(theValue)
#endif
#endif
  }

/*************************************/
/* PrintFactJNGetVar3: Print routine */
/*   for the FactJNGetVar3 function. */
/*************************************/
#if WIN_BTC && (! DEVELOPER)
#pragma argsused
#endif
globle void PrintFactJNGetVar3(
  void *theEnv,
  char *logicalName,
  void *theValue)
  {
#if DEVELOPER
   struct factGetVarJN3Call *hack;

   hack = (struct factGetVarJN3Call *) ValueToBitMap(theValue);
   EnvPrintRouter(theEnv,logicalName,(char*)"(fact-jn-getvar-3 ");
   if (hack->fromBeginning) EnvPrintRouter(theEnv,logicalName,(char*)"t ");
   else EnvPrintRouter(theEnv,logicalName,(char*)"f ");
   if (hack->fromEnd) EnvPrintRouter(theEnv,logicalName,(char*)"t ");
   else EnvPrintRouter(theEnv,logicalName,(char*)"f ");

   PrintLongInteger(theEnv,logicalName,(long long) hack->beginOffset);
   EnvPrintRouter(theEnv,logicalName,(char*)" ");
   PrintLongInteger(theEnv,logicalName,(long long) hack->endOffset);
   EnvPrintRouter(theEnv,logicalName,(char*)" ");
   PrintLongInteger(theEnv,logicalName,(long long) hack->whichSlot);

   EnvPrintRouter(theEnv,logicalName,(char*)" p");
   PrintLongInteger(theEnv,logicalName,(long long) hack->whichPattern + 1);

   if (hack->lhs)
     { EnvPrintRouter(theEnv,logicalName,(char*)" L"); }
   else if (hack->rhs)
     { EnvPrintRouter(theEnv,logicalName,(char*)" R"); }
     
   EnvPrintRouter(theEnv,logicalName,(char*)")");
#else
#if MAC_MCW || WIN_MCW || MAC_XCD
#pragma unused(theEnv)
#pragma unused(logicalName)
#pragma unused(theValue)
#endif
#endif
  }

/*************************************/
/* PrintFactPNGetVar1: Print routine */
/*   for the FactPNGetvar1 function. */
/*************************************/
#if WIN_BTC && (! DEVELOPER)
#pragma argsused
#endif
globle void PrintFactPNGetVar1(
  void *theEnv,
  char *logicalName,
  void *theValue)
  {
#if DEVELOPER
   struct factGetVarPN1Call *hack;

   hack = (struct factGetVarPN1Call *) ValueToBitMap(theValue);
   EnvPrintRouter(theEnv,logicalName,(char*)"(fact-pn-getvar-1 ");
   if (hack->factAddress) EnvPrintRouter(theEnv,logicalName,(char*)"t ");
   else EnvPrintRouter(theEnv,logicalName,(char*)"f ");
   if (hack->allFields) EnvPrintRouter(theEnv,logicalName,(char*)"t F");
   else EnvPrintRouter(theEnv,logicalName,(char*)"f F");

   PrintLongInteger(theEnv,logicalName,(long long) hack->whichField);
   EnvPrintRouter(theEnv,logicalName,(char*)" S");
   PrintLongInteger(theEnv,logicalName,(long long) hack->whichSlot);
   EnvPrintRouter(theEnv,logicalName,(char*)")");
#else
#if MAC_MCW || WIN_MCW || MAC_XCD
#pragma unused(theEnv)
#pragma unused(logicalName)
#pragma unused(theValue)
#endif
#endif
  }

/*************************************/
/* PrintFactPNGetVar2: Print routine */
/*   for the FactPNGetvar2 function. */
/*************************************/
#if WIN_BTC && (! DEVELOPER)
#pragma argsused
#endif
globle void PrintFactPNGetVar2(
  void *theEnv,
  char *logicalName,
  void *theValue)
  {
#if DEVELOPER
   struct factGetVarPN2Call *hack;

   hack = (struct factGetVarPN2Call *) ValueToBitMap(theValue);;
   EnvPrintRouter(theEnv,logicalName,(char*)"(fact-pn-getvar-2 S");
   PrintLongInteger(theEnv,logicalName,(long long) hack->whichSlot);
   EnvPrintRouter(theEnv,logicalName,(char*)")");
#else
#if MAC_MCW || WIN_MCW || MAC_XCD
#pragma unused(theEnv)
#pragma unused(logicalName)
#pragma unused(theValue)
#endif
#endif
  }

/*************************************/
/* PrintFactPNGetVar3: Print routine */
/*   for the FactPNGetvar3 function. */
/*************************************/
#if WIN_BTC && (! DEVELOPER)
#pragma argsused
#endif
globle void PrintFactPNGetVar3(
  void *theEnv,
  char *logicalName,
  void *theValue)
  {
#if DEVELOPER
   struct factGetVarPN3Call *hack;

   hack = (struct factGetVarPN3Call *) ValueToBitMap(theValue);
   EnvPrintRouter(theEnv,logicalName,(char*)"(fact-pn-getvar-3 ");

   if (hack->fromBeginning) EnvPrintRouter(theEnv,logicalName,(char*)"t ");
   else EnvPrintRouter(theEnv,logicalName,(char*)"f ");
   if (hack->fromEnd) EnvPrintRouter(theEnv,logicalName,(char*)"t B");
   else EnvPrintRouter(theEnv,logicalName,(char*)"f B");

   PrintLongInteger(theEnv,logicalName,(long long) hack->beginOffset);
   EnvPrintRouter(theEnv,logicalName,(char*)" E");
   PrintLongInteger(theEnv,logicalName,(long long) hack->endOffset);
   EnvPrintRouter(theEnv,logicalName,(char*)" S");
   PrintLongInteger(theEnv,logicalName,(long long) hack->whichSlot);
   EnvPrintRouter(theEnv,logicalName,(char*)")");
#else
#if MAC_MCW || WIN_MCW || MAC_XCD
#pragma unused(theEnv)
#pragma unused(logicalName)
#pragma unused(theValue)
#endif
#endif
  }

/***************************************/
/* PrintFactPNConstant1: Print routine */
/*   for the FactPNConstant1 function. */
/***************************************/
#if WIN_BTC && (! DEVELOPER)
#pragma argsused
#endif
globle void PrintFactPNConstant1(
  void *theEnv,
  char *logicalName,
  void *theValue)
  {
#if DEVELOPER
   struct factConstantPN1Call *hack;

   hack = (struct factConstantPN1Call *) ValueToBitMap(theValue);

   EnvPrintRouter(theEnv,logicalName,(char*)"(fact-pn-constant1 ");

   PrintLongInteger(theEnv,logicalName,(long long) hack->whichSlot);

   if (hack->testForEquality) EnvPrintRouter(theEnv,logicalName,(char*)" = ");
   else EnvPrintRouter(theEnv,logicalName,(char*)" != ");

   PrintAtom(theEnv,logicalName,GetFirstArgument()->type,GetFirstArgument()->value);
   EnvPrintRouter(theEnv,logicalName,(char*)")");
#else
#if MAC_MCW || WIN_MCW || MAC_XCD
#pragma unused(theEnv)
#pragma unused(logicalName)
#pragma unused(theValue)
#endif
#endif
  }

/***************************************/
/* PrintFactPNConstant2: Print routine */
/*   for the FactPNConstant2 function. */
/***************************************/
#if WIN_BTC && (! DEVELOPER)
#pragma argsused
#endif
globle void PrintFactPNConstant2(
  void *theEnv,
  char *logicalName,
  void *theValue)
  {
#if DEVELOPER
   struct factConstantPN2Call *hack;

   hack = (struct factConstantPN2Call *) ValueToBitMap(theValue);

   EnvPrintRouter(theEnv,logicalName,(char*)"(fact-pn-constant2 ");

   PrintLongInteger(theEnv,logicalName,(long long) hack->whichSlot);

   EnvPrintRouter(theEnv,logicalName,(char*)" ");

   PrintLongInteger(theEnv,logicalName,(long long) hack->offset);

   if (hack->testForEquality) EnvPrintRouter(theEnv,logicalName,(char*)" = ");
   else EnvPrintRouter(theEnv,logicalName,(char*)" != ");

   PrintAtom(theEnv,logicalName,GetFirstArgument()->type,GetFirstArgument()->value);
   EnvPrintRouter(theEnv,logicalName,(char*)")");
#else
#if MAC_MCW || WIN_MCW || MAC_XCD
#pragma unused(theEnv)
#pragma unused(logicalName)
#pragma unused(theValue)
#endif
#endif
  }

#endif /* DEFTEMPLATE_CONSTRUCT && DEFRULE_CONSTRUCT */


