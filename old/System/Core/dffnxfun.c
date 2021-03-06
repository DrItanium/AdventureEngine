   /*******************************************************/
   /*      "C" Language Integrated Production System      */
   /*                                                     */
   /*             CLIPS Version 6.24  06/02/06            */
   /*                                                     */
   /*                 DEFFUNCTION MODULE                  */
   /*******************************************************/

/*************************************************************/
/* Purpose:                                                  */
/*                                                           */
/* Principal Programmer(s):                                  */
/*      Brian L. Dantes                                      */
/*                                                           */
/* Contributing Programmer(s):                               */
/*      Gary D. Riley                                        */
/*                                                           */
/* Revision History:                                         */
/*      6.23: Correction for FalseSymbol/TrueSymbol. DR0859  */
/*                                                           */
/*            Corrected compilation errors for files         */
/*            generated by constructs-to-c. DR0861           */
/*                                                           */
/*            Changed name of variable log to logName        */
/*            because of Unix compiler warnings of shadowed  */
/*            definitions.                                   */
/*                                                           */
/*      6.24: Renamed BOOLEAN macro type to intBool.         */
/*                                                           */
/*            Corrected code to remove run-time program      */
/*            compiler warning.                              */
/*                                                           */
/*************************************************************/

/* =========================================
   *****************************************
               EXTERNAL DEFINITIONS
   =========================================
   ***************************************** */
#include "setup.h"

#if DEFFUNCTION_CONSTRUCT

#if (BLOAD || BLOAD_ONLY || BLOAD_AND_BSAVE)
#include "bload.h"
#include "dffnxbin.h"
#endif

#if CONSTRUCT_COMPILER && (! RUN_TIME)
#include "dffnxcmp.h"
#endif

#if (! BLOAD_ONLY) && (! RUN_TIME)
#include "constrct.h"
#include "cstrcpsr.h"
#include "dffnxpsr.h"
#include "modulpsr.h"
#endif

#include "envrnmnt.h"

#if (! RUN_TIME)
#include "extnfunc.h"
#endif

#include "dffnxexe.h"

#if DEBUGGING_FUNCTIONS
#include "watch.h"
#endif

#include "argacces.h"
#include "memalloc.h"
#include "cstrccom.h"
#include "router.h"

#define _DFFNXFUN_SOURCE_
#include "dffnxfun.h"

/* =========================================
   *****************************************
      INTERNALLY VISIBLE FUNCTION HEADERS
   =========================================
   ***************************************** */

static void PrintDeffunctionCall(void *,char *,void *);
static intBool EvaluateDeffunctionCall(void *,void *,DATA_OBJECT *);
static void DecrementDeffunctionBusyCount(void *,void *);
static void IncrementDeffunctionBusyCount(void *,void *);
static void DeallocateDeffunctionData(void *);

#if ! RUN_TIME
static void DestroyDeffunctionAction(void *,struct constructHeader *,void *);
static void *AllocateModule(void *);
static void  ReturnModule(void *,void *);
static intBool ClearDeffunctionsReady(void *);
#endif

#if (! BLOAD_ONLY) && (! RUN_TIME)
static intBool RemoveAllDeffunctions(void *);
static void DeffunctionDeleteError(void *,char *);
static void SaveDeffunctionHeaders(void *,void *,char *);
static void SaveDeffunctionHeader(void *,struct constructHeader *,void *);
static void SaveDeffunctions(void *,void *,char *);
#endif

#if DEBUGGING_FUNCTIONS
static unsigned DeffunctionWatchAccess(void *,int,unsigned,EXPRESSION *);
static unsigned DeffunctionWatchPrint(void *,char *,int,EXPRESSION *);
#endif

/* =========================================
   *****************************************
          EXTERNALLY VISIBLE FUNCTIONS
   =========================================
   ***************************************** */

/***************************************************
  NAME         : SetupDeffunctions
  DESCRIPTION  : Initializes parsers and access
                 functions for deffunctions
  INPUTS       : None
  RETURNS      : Nothing useful
  SIDE EFFECTS : Deffunction environment initialized
  NOTES        : None
 ***************************************************/
globle void SetupDeffunctions(
  void *theEnv)
  {
   ENTITY_RECORD deffunctionEntityRecord =
                     { (char*)"PCALL", PCALL,0,0,1,
                       PrintDeffunctionCall,PrintDeffunctionCall,
                       NULL,EvaluateDeffunctionCall,NULL,
                       DecrementDeffunctionBusyCount,IncrementDeffunctionBusyCount,
                       NULL,NULL,NULL,NULL,NULL };

   AllocateEnvironmentData(theEnv,DEFFUNCTION_DATA,sizeof(struct deffunctionData),DeallocateDeffunctionData);
   memcpy(&DeffunctionData(theEnv)->DeffunctionEntityRecord,&deffunctionEntityRecord,sizeof(struct entityRecord));   

   InstallPrimitive(theEnv,&DeffunctionData(theEnv)->DeffunctionEntityRecord,PCALL);

   DeffunctionData(theEnv)->DeffunctionModuleIndex =
                RegisterModuleItem(theEnv,(char*)"deffunction",
#if (! RUN_TIME)
                                    AllocateModule,ReturnModule,
#else
                                    NULL,NULL,
#endif
#if BLOAD_AND_BSAVE || BLOAD || BLOAD_ONLY
                                    BloadDeffunctionModuleReference,
#else
                                    NULL,
#endif
#if CONSTRUCT_COMPILER && (! RUN_TIME)
                                    DeffunctionCModuleReference,
#else
                                    NULL,
#endif
                                    EnvFindDeffunction);

   DeffunctionData(theEnv)->DeffunctionConstruct = AddConstruct(theEnv,(char*)"deffunction",(char*)"deffunctions",
#if (! BLOAD_ONLY) && (! RUN_TIME)
                                       ParseDeffunction,
#else
                                       NULL,
#endif
                                       EnvFindDeffunction,
                                       GetConstructNamePointer,GetConstructPPForm,
                                       GetConstructModuleItem,EnvGetNextDeffunction,
                                       SetNextConstruct,EnvIsDeffunctionDeletable,
                                       EnvUndeffunction,
#if (! BLOAD_ONLY) && (! RUN_TIME)
                                       RemoveDeffunction
#else
                                       NULL
#endif
                                       );
#if ! RUN_TIME
   AddClearReadyFunction(theEnv,(char*)"deffunction",ClearDeffunctionsReady,0);

#if ! BLOAD_ONLY
#if DEFMODULE_CONSTRUCT
   AddPortConstructItem(theEnv,(char*)"deffunction",SYMBOL);
#endif
   AddSaveFunction(theEnv,(char*)"deffunction-headers",SaveDeffunctionHeaders,1000);
   AddSaveFunction(theEnv,(char*)"deffunctions",SaveDeffunctions,0);
   EnvDefineFunction2(theEnv,(char*)"undeffunction",'v',PTIEF UndeffunctionCommand,(char*)"UndeffunctionCommand",(char*)"11w");
#endif

#if DEBUGGING_FUNCTIONS
   EnvDefineFunction2(theEnv,(char*)"list-deffunctions",'v',PTIEF ListDeffunctionsCommand,(char*)"ListDeffunctionsCommand",(char*)"01");
   EnvDefineFunction2(theEnv,(char*)"ppdeffunction",'v',PTIEF PPDeffunctionCommand,(char*)"PPDeffunctionCommand",(char*)"11w");
#endif

   EnvDefineFunction2(theEnv,(char*)"get-deffunction-list",'m',PTIEF GetDeffunctionListFunction,
                   (char*)"GetDeffunctionListFunction",(char*)"01");

   EnvDefineFunction2(theEnv,(char*)"deffunction-module",'w',PTIEF GetDeffunctionModuleCommand,
                   (char*)"GetDeffunctionModuleCommand",(char*)"11w");

#if BLOAD_AND_BSAVE || BLOAD || BLOAD_ONLY
   SetupDeffunctionsBload(theEnv);
#endif

#if CONSTRUCT_COMPILER
   SetupDeffunctionCompiler(theEnv);
#endif

#endif

#if DEBUGGING_FUNCTIONS
   AddWatchItem(theEnv,(char*)"deffunctions",0,&DeffunctionData(theEnv)->WatchDeffunctions,32,
                DeffunctionWatchAccess,DeffunctionWatchPrint);
#endif

  }
  
/******************************************************/
/* DeallocateDeffunctionData: Deallocates environment */
/*    data for the deffunction construct.             */
/******************************************************/
static void DeallocateDeffunctionData(
  void *theEnv)
  {
#if ! RUN_TIME
   struct deffunctionModule *theModuleItem;
   void *theModule;

#if BLOAD || BLOAD_AND_BSAVE
   if (Bloaded(theEnv)) return;
#endif

   DoForAllConstructs(theEnv,DestroyDeffunctionAction,DeffunctionData(theEnv)->DeffunctionModuleIndex,FALSE,NULL); 

   for (theModule = EnvGetNextDefmodule(theEnv,NULL);
        theModule != NULL;
        theModule = EnvGetNextDefmodule(theEnv,theModule))
     {
      theModuleItem = (struct deffunctionModule *)
                      GetModuleItem(theEnv,(struct defmodule *) theModule,
                                    DeffunctionData(theEnv)->DeffunctionModuleIndex);
      rtn_struct(theEnv,deffunctionModule,theModuleItem);
     }
#else
#endif
  }
  
#if ! RUN_TIME
/*****************************************************/
/* DestroyDeffunctionAction: Action used to remove   */
/*   deffunctions as a result of DestroyEnvironment. */
/*****************************************************/
static void DestroyDeffunctionAction(
  void *theEnv,
  struct constructHeader *theConstruct,
  void *buffer)
  {
#if (! BLOAD_ONLY) && (! RUN_TIME)
   struct deffunctionStruct *theDeffunction = (struct deffunctionStruct *) theConstruct;
   
   if (theDeffunction == NULL) return;
   
   ReturnPackedExpression(theEnv,theDeffunction->code);

   DestroyConstructHeader(theEnv,&theDeffunction->header);
   
   rtn_struct(theEnv,deffunctionStruct,theDeffunction);
#else
#endif
  }
#endif

/***************************************************
  NAME         : EnvFindDeffunction
  DESCRIPTION  : Searches for a deffunction
  INPUTS       : The name of the deffunction
                 (possibly including a module name)
  RETURNS      : Pointer to the deffunction if
                 found, otherwise NULL
  SIDE EFFECTS : None
  NOTES        : None
 ***************************************************/
globle void *EnvFindDeffunction(
  void *theEnv,
  char *dfnxModuleAndName)
  {
   return(FindNamedConstruct(theEnv,dfnxModuleAndName,DeffunctionData(theEnv)->DeffunctionConstruct));
  }

/***************************************************
  NAME         : LookupDeffunctionByMdlOrScope
  DESCRIPTION  : Finds a deffunction anywhere (if
                 module is specified) or in current
                 or imported modules
  INPUTS       : The deffunction name
  RETURNS      : The deffunction (NULL if not found)
  SIDE EFFECTS : Error message printed on
                  ambiguous references
  NOTES        : None
 ***************************************************/
globle DEFFUNCTION *LookupDeffunctionByMdlOrScope(
  void *theEnv,
  char *deffunctionName)
  {
   return((DEFFUNCTION *) LookupConstruct(theEnv,DeffunctionData(theEnv)->DeffunctionConstruct,deffunctionName,TRUE));
  }

/***************************************************
  NAME         : LookupDeffunctionInScope
  DESCRIPTION  : Finds a deffunction in current or
                   imported modules (module
                   specifier is not allowed)
  INPUTS       : The deffunction name
  RETURNS      : The deffunction (NULL if not found)
  SIDE EFFECTS : Error message printed on
                  ambiguous references
  NOTES        : None
 ***************************************************/
globle DEFFUNCTION *LookupDeffunctionInScope(
  void *theEnv,
  char *deffunctionName)
  {
   return((DEFFUNCTION *) LookupConstruct(theEnv,DeffunctionData(theEnv)->DeffunctionConstruct,deffunctionName,FALSE));
  }

/***************************************************
  NAME         : EnvUndeffunction
  DESCRIPTION  : External interface routine for
                 removing a deffunction
  INPUTS       : Deffunction pointer
  RETURNS      : FALSE if unsuccessful,
                 TRUE otherwise
  SIDE EFFECTS : Deffunction deleted, if possible
  NOTES        : None
 ***************************************************/
globle intBool EnvUndeffunction(
  void *theEnv,
  void *vptr)
  {

#if BLOAD_ONLY || RUN_TIME
   return(FALSE);
#else

#if BLOAD || BLOAD_AND_BSAVE

   if (Bloaded(theEnv) == TRUE)
     return(FALSE);
#endif
   if (vptr == NULL)
      return(RemoveAllDeffunctions(theEnv));
   if (EnvIsDeffunctionDeletable(theEnv,vptr) == FALSE)
     return(FALSE);
   RemoveConstructFromModule(theEnv,(struct constructHeader *) vptr);
   RemoveDeffunction(theEnv,vptr);
   return(TRUE);
#endif
  }

/****************************************************
  NAME         : EnvGetNextDeffunction
  DESCRIPTION  : Accesses list of deffunctions
  INPUTS       : Deffunction pointer
  RETURNS      : The next deffunction, or the
                 first deffunction (if input is NULL)
  SIDE EFFECTS : None
  NOTES        : None
 ****************************************************/
globle void *EnvGetNextDeffunction(
  void *theEnv,
  void *ptr)
  {
   return((void *) GetNextConstructItem(theEnv,(struct constructHeader *) ptr,DeffunctionData(theEnv)->DeffunctionModuleIndex));
  }

/***************************************************
  NAME         : EnvIsDeffunctionDeletable
  DESCRIPTION  : Determines if a deffunction is
                 executing or referenced by another
                 expression
  INPUTS       : Deffunction pointer
  RETURNS      : TRUE if the deffunction can
                 be deleted, FALSE otherwise
  SIDE EFFECTS : None
  NOTES        : None
 ***************************************************/
globle int EnvIsDeffunctionDeletable(
  void *theEnv,
  void *ptr)
  {
   DEFFUNCTION *dptr;

   if (! ConstructsDeletable(theEnv))
     { return FALSE; }

   dptr = (DEFFUNCTION *) ptr;

   return(((dptr->busy == 0) && (dptr->executing == 0)) ? TRUE : FALSE);
  }

#if (! BLOAD_ONLY) && (! RUN_TIME)

/***************************************************
  NAME         : RemoveDeffunction
  DESCRIPTION  : Removes a deffunction
  INPUTS       : Deffunction pointer
  RETURNS      : Nothing useful
  SIDE EFFECTS : Deffunction deallocated
  NOTES        : Assumes deffunction is not in use!!
 ***************************************************/
globle void RemoveDeffunction(
  void *theEnv,
  void *vdptr)
  {
   DEFFUNCTION *dptr = (DEFFUNCTION *) vdptr;

   if (dptr == NULL)
     return;
   DecrementSymbolCount(theEnv,GetDeffunctionNamePointer((void *) dptr));
   ExpressionDeinstall(theEnv,dptr->code);
   ReturnPackedExpression(theEnv,dptr->code);
   SetDeffunctionPPForm((void *) dptr,NULL);
   ClearUserDataList(theEnv,dptr->header.usrData);
   rtn_struct(theEnv,deffunctionStruct,dptr);
  }

#endif

/********************************************************
  NAME         : UndeffunctionCommand
  DESCRIPTION  : Deletes the named deffunction(s)
  INPUTS       : None
  RETURNS      : Nothing useful
  SIDE EFFECTS : Deffunction(s) removed
  NOTES        : H/L Syntax: (undeffunction <name> | *)
 ********************************************************/
globle void UndeffunctionCommand(
  void *theEnv)
  {
   UndefconstructCommand(theEnv,(char*)"undeffunction",DeffunctionData(theEnv)->DeffunctionConstruct);
  }

/****************************************************************
  NAME         : GetDeffunctionModuleCommand
  DESCRIPTION  : Determines to which module a deffunction belongs
  INPUTS       : None
  RETURNS      : The symbolic name of the module
  SIDE EFFECTS : None
  NOTES        : H/L Syntax: (deffunction-module <dfnx-name>)
 ****************************************************************/
globle void *GetDeffunctionModuleCommand(
  void *theEnv)
  {
   return(GetConstructModuleCommand(theEnv,(char*)"deffunction-module",DeffunctionData(theEnv)->DeffunctionConstruct));
  }

#if DEBUGGING_FUNCTIONS

/****************************************************
  NAME         : PPDeffunctionCommand
  DESCRIPTION  : Displays the pretty-print form of a
                 deffunction
  INPUTS       : None
  RETURNS      : Nothing useful
  SIDE EFFECTS : Pretty-print form displayed to
                 WDISPLAY logical name
  NOTES        : H/L Syntax: (ppdeffunction <name>)
 ****************************************************/
globle void PPDeffunctionCommand(
  void *theEnv)
  {
   PPConstructCommand(theEnv,(char*)"ppdeffunction",DeffunctionData(theEnv)->DeffunctionConstruct);
  }

/***************************************************
  NAME         : ListDeffunctionsCommand
  DESCRIPTION  : Displays all deffunction names
  INPUTS       : None
  RETURNS      : Nothing useful
  SIDE EFFECTS : Deffunction name sprinted
  NOTES        : H/L Interface
 ***************************************************/
globle void ListDeffunctionsCommand(
  void *theEnv)
  {
   ListConstructCommand(theEnv,(char*)"list-deffunctions",DeffunctionData(theEnv)->DeffunctionConstruct);
  }

/***************************************************
  NAME         : EnvListDeffunctions
  DESCRIPTION  : Displays all deffunction names
  INPUTS       : 1) The logical name of the output
                 2) The module
  RETURNS      : Nothing useful
  SIDE EFFECTS : Deffunction name sprinted
  NOTES        : C Interface
 ***************************************************/
globle void EnvListDeffunctions(
  void *theEnv,
  char *logicalName,
  struct defmodule *theModule)
  {
   ListConstruct(theEnv,DeffunctionData(theEnv)->DeffunctionConstruct,logicalName,theModule);
  }

#endif

/***************************************************************
  NAME         : GetDeffunctionListFunction
  DESCRIPTION  : Groups all deffunction names into
                 a multifield list
  INPUTS       : A data object buffer to hold
                 the multifield result
  RETURNS      : Nothing useful
  SIDE EFFECTS : Multifield allocated and filled
  NOTES        : H/L Syntax: (get-deffunction-list [<module>])
 ***************************************************************/
globle void GetDeffunctionListFunction(
  void *theEnv,
  DATA_OBJECT *returnValue)
  {
   GetConstructListFunction(theEnv,(char*)"get-deffunction-list",returnValue,DeffunctionData(theEnv)->DeffunctionConstruct);
  }

/***************************************************************
  NAME         : EnvGetDeffunctionList
  DESCRIPTION  : Groups all deffunction names into
                 a multifield list
  INPUTS       : 1) A data object buffer to hold
                    the multifield result
                 2) The module from which to obtain deffunctions
  RETURNS      : Nothing useful
  SIDE EFFECTS : Multifield allocated and filled
  NOTES        : External C access
 ***************************************************************/
globle void EnvGetDeffunctionList(
  void *theEnv,
  DATA_OBJECT *returnValue,
  struct defmodule *theModule)
  {
   GetConstructList(theEnv,returnValue,DeffunctionData(theEnv)->DeffunctionConstruct,theModule);
  }

/*******************************************************
  NAME         : CheckDeffunctionCall
  DESCRIPTION  : Checks the number of arguments
                 passed to a deffunction
  INPUTS       : 1) Deffunction pointer
                 2) The number of arguments
  RETURNS      : TRUE if OK, FALSE otherwise
  SIDE EFFECTS : Message printed on errors
  NOTES        : None
 *******************************************************/
globle int CheckDeffunctionCall(
  void *theEnv,
  void *vdptr,
  int args)
  {
   DEFFUNCTION *dptr;

   if (vdptr == NULL)
     return(FALSE);
   dptr = (DEFFUNCTION *) vdptr;
   if (args < dptr->minNumberOfParameters)
     {
      if (dptr->maxNumberOfParameters == -1)
        ExpectedCountError(theEnv,EnvGetDeffunctionName(theEnv,(void *) dptr),
                           AT_LEAST,dptr->minNumberOfParameters);
      else
        ExpectedCountError(theEnv,EnvGetDeffunctionName(theEnv,(void *) dptr),
                           EXACTLY,dptr->minNumberOfParameters);
      return(FALSE);
     }
   else if ((args > dptr->minNumberOfParameters) &&
            (dptr->maxNumberOfParameters != -1))
     {
      ExpectedCountError(theEnv,EnvGetDeffunctionName(theEnv,(void *) dptr),
                         EXACTLY,dptr->minNumberOfParameters);
      return(FALSE);
     }
   return(TRUE);
  }

/* =========================================
   *****************************************
          INTERNALLY VISIBLE FUNCTIONS
   =========================================
   ***************************************** */

/***************************************************
  NAME         : PrintDeffunctionCall
  DESCRIPTION  : PrintExpression() support function
                 for deffunction calls
  INPUTS       : 1) The output logical name
                 2) The deffunction
  RETURNS      : Nothing useful
  SIDE EFFECTS : Call expression printed
  NOTES        : None
 ***************************************************/
static void PrintDeffunctionCall(
  void *theEnv,
  char *logName,
  void *value)
  {
#if DEVELOPER

   EnvPrintRouter(theEnv,logName,(char*)"(");
   EnvPrintRouter(theEnv,logName,EnvGetDeffunctionName(theEnv,value));
   if (GetFirstArgument() != NULL)
     {
      EnvPrintRouter(theEnv,logName,(char*)" ");
      PrintExpression(theEnv,logName,GetFirstArgument());
     }
   EnvPrintRouter(theEnv,logName,(char*)")");
#else
#endif
  }

/*******************************************************
  NAME         : EvaluateDeffunctionCall
  DESCRIPTION  : Primitive support function for
                 calling a deffunction
  INPUTS       : 1) The deffunction
                 2) A data object buffer to hold
                    the evaluation result
  RETURNS      : FALSE if the deffunction
                 returns the symbol FALSE,
                 TRUE otherwise
  SIDE EFFECTS : Data obejct buffer set and any
                 side-effects of calling the deffunction
  NOTES        : None
 *******************************************************/
static intBool EvaluateDeffunctionCall(
  void *theEnv,
  void *value,
  DATA_OBJECT *result)
  {
   CallDeffunction(theEnv,(DEFFUNCTION *) value,GetFirstArgument(),result);
   if ((GetpType(result) == SYMBOL) &&
       (GetpValue(result) == EnvFalseSymbol(theEnv)))
     return(FALSE);
   return(TRUE);
  }

/***************************************************
  NAME         : DecrementDeffunctionBusyCount
  DESCRIPTION  : Lowers the busy count of a
                 deffunction construct
  INPUTS       : The deffunction
  RETURNS      : Nothing useful
  SIDE EFFECTS : Busy count decremented if a clear
                 is not in progress (see comment)
  NOTES        : None
 ***************************************************/
static void DecrementDeffunctionBusyCount(
  void *theEnv,
  void *value)
  {
   /* ==============================================
      The deffunctions to which expressions in other
      constructs may refer may already have been
      deleted - thus, it is important not to modify
      the busy flag during a clear.
      ============================================== */
   if (! ConstructData(theEnv)->ClearInProgress)
     ((DEFFUNCTION *) value)->busy--;
  }

/***************************************************
  NAME         : IncrementDeffunctionBusyCount
  DESCRIPTION  : Raises the busy count of a
                 deffunction construct
  INPUTS       : The deffunction
  RETURNS      : Nothing useful
  SIDE EFFECTS : Busy count incremented
  NOTES        : None
 ***************************************************/
static void IncrementDeffunctionBusyCount(
  void *theEnv,
  void *value)
  {

   ((DEFFUNCTION *) value)->busy++;
  }

#if ! RUN_TIME

/*****************************************************
  NAME         : AllocateModule
  DESCRIPTION  : Creates and initializes a
                 list of deffunctions for a new module
  INPUTS       : None
  RETURNS      : The new deffunction module
  SIDE EFFECTS : Deffunction module created
  NOTES        : None
 *****************************************************/
static void *AllocateModule(
  void *theEnv)
  {
   return((void *) get_struct(theEnv,deffunctionModule));
  }

/***************************************************
  NAME         : ReturnModule
  DESCRIPTION  : Removes a deffunction module and
                 all associated deffunctions
  INPUTS       : The deffunction module
  RETURNS      : Nothing useful
  SIDE EFFECTS : Module and deffunctions deleted
  NOTES        : None
 ***************************************************/
static void ReturnModule(
  void *theEnv,
  void *theItem)
  {
#if (! BLOAD_ONLY)
   FreeConstructHeaderModule(theEnv,(struct defmoduleItemHeader *) theItem,DeffunctionData(theEnv)->DeffunctionConstruct);
#endif
   rtn_struct(theEnv,deffunctionModule,theItem);
  }

/***************************************************
  NAME         : ClearDeffunctionsReady
  DESCRIPTION  : Determines if it is safe to
                 remove all deffunctions
                 Assumes *all* constructs will be
                 deleted - only checks to see if
                 any deffunctions are currently
                 executing
  INPUTS       : None
  RETURNS      : TRUE if no deffunctions are
                 executing, FALSE otherwise
  SIDE EFFECTS : None
  NOTES        : Used by (clear) and (bload)
 ***************************************************/
static intBool ClearDeffunctionsReady(
  void *theEnv)
  {
   return((DeffunctionData(theEnv)->ExecutingDeffunction != NULL) ? FALSE : TRUE);
  }

#endif

#if (! BLOAD_ONLY) && (! RUN_TIME)

/***************************************************
  NAME         : RemoveAllDeffunctions
  DESCRIPTION  : Removes all deffunctions
  INPUTS       : None
  RETURNS      : TRUE if all deffunctions
                 removed, FALSE otherwise
  SIDE EFFECTS : Deffunctions removed
  NOTES        : None
 ***************************************************/
static intBool RemoveAllDeffunctions(
  void *theEnv)
  {
   DEFFUNCTION *dptr,*dtmp;
   unsigned oldbusy;
   intBool success = TRUE;

#if BLOAD || BLOAD_AND_BSAVE

   if (Bloaded(theEnv) == TRUE)
     return(FALSE);
#endif

   dptr = (DEFFUNCTION *) EnvGetNextDeffunction(theEnv,NULL);
   while (dptr != NULL)
     {
      if (dptr->executing > 0)
        {
         DeffunctionDeleteError(theEnv,EnvGetDeffunctionName(theEnv,(void *) dptr));
         success = FALSE;
        }
      else
        {
         oldbusy = dptr->busy;
         ExpressionDeinstall(theEnv,dptr->code);
         dptr->busy = oldbusy;
         ReturnPackedExpression(theEnv,dptr->code);
         dptr->code = NULL;
        }
      dptr = (DEFFUNCTION *) EnvGetNextDeffunction(theEnv,(void *) dptr);
     }

   dptr = (DEFFUNCTION *) EnvGetNextDeffunction(theEnv,NULL);
   while (dptr != NULL)
     {
      dtmp = dptr;
      dptr = (DEFFUNCTION *) EnvGetNextDeffunction(theEnv,(void *) dptr);
      if (dtmp->executing == 0)
        {
         if (dtmp->busy > 0)
           {
            PrintWarningID(theEnv,(char*)"DFFNXFUN",1,FALSE);
            EnvPrintRouter(theEnv,WWARNING,(char*)"Deffunction ");
            EnvPrintRouter(theEnv,WWARNING,EnvGetDeffunctionName(theEnv,(void *) dtmp));
            EnvPrintRouter(theEnv,WWARNING,(char*)" only partially deleted due to usage by other constructs.\n");
            SetDeffunctionPPForm((void *) dtmp,NULL);
            success = FALSE;
           }
         else
           {
            RemoveConstructFromModule(theEnv,(struct constructHeader *) dtmp);
            RemoveDeffunction(theEnv,dtmp);
           }
        }
     }
   return(success);
  }

/****************************************************
  NAME         : DeffunctionDeleteError
  DESCRIPTION  : Prints out an error message when
                 a deffunction deletion attempt fails
  INPUTS       : The deffunction name
  RETURNS      : Nothing useful
  SIDE EFFECTS : Error message printed
  NOTES        : None
 ****************************************************/
static void DeffunctionDeleteError(
  void *theEnv,
  char *dfnxName)
  {
   CantDeleteItemErrorMessage(theEnv,(char*)"deffunction",dfnxName);
  }

/***************************************************
  NAME         : SaveDeffunctionHeaders
  DESCRIPTION  : Writes out deffunction forward
                 declarations for (save) command
  INPUTS       : The logical output name
  RETURNS      : Nothing useful
  SIDE EFFECTS : Writes out deffunctions with no
                 body of actions
  NOTES        : Used for deffunctions which are
                 mutually recursive with other
                 constructs
 ***************************************************/
static void SaveDeffunctionHeaders(
  void *theEnv,
  void *theModule,
  char *logicalName)
  {
   DoForAllConstructsInModule(theEnv,theModule,SaveDeffunctionHeader,
                              DeffunctionData(theEnv)->DeffunctionModuleIndex,
                              FALSE,(void *) logicalName);
  }

/***************************************************
  NAME         : SaveDeffunctionHeader
  DESCRIPTION  : Writes a deffunction forward
                 declaration to the save file
  INPUTS       : 1) The deffunction
                 2) The logical name of the output
  RETURNS      : Nothing useful
  SIDE EFFECTS : Defffunction header written
  NOTES        : None
 ***************************************************/
static void SaveDeffunctionHeader(
  void *theEnv,
  struct constructHeader *theDeffunction,
  void *userBuffer)
  {
   DEFFUNCTION *dfnxPtr = (DEFFUNCTION *) theDeffunction;
   char *logicalName = (char *) userBuffer;
   register int i;

   if (EnvGetDeffunctionPPForm(theEnv,(void *) dfnxPtr) != NULL)
     {
      EnvPrintRouter(theEnv,logicalName,(char*)"(deffunction ");
      EnvPrintRouter(theEnv,logicalName,EnvDeffunctionModule(theEnv,(void *) dfnxPtr));
      EnvPrintRouter(theEnv,logicalName,(char*)"::");      
      EnvPrintRouter(theEnv,logicalName,EnvGetDeffunctionName(theEnv,(void *) dfnxPtr));
      EnvPrintRouter(theEnv,logicalName,(char*)" (");
      for (i = 0 ; i < dfnxPtr->minNumberOfParameters ; i++)
        {
         EnvPrintRouter(theEnv,logicalName,(char*)"?p");
         PrintLongInteger(theEnv,logicalName,(long long) i);
         if (i != dfnxPtr->minNumberOfParameters-1)
           EnvPrintRouter(theEnv,logicalName,(char*)" ");
        }
      if (dfnxPtr->maxNumberOfParameters == -1)
        {
         if (dfnxPtr->minNumberOfParameters != 0)
           EnvPrintRouter(theEnv,logicalName,(char*)" ");
         EnvPrintRouter(theEnv,logicalName,(char*)"$?wildargs))\n\n");
        }
      else
        EnvPrintRouter(theEnv,logicalName,(char*)"))\n\n");
     }
  }

/***************************************************
  NAME         : SaveDeffunctions
  DESCRIPTION  : Writes out deffunctions
                 for (save) command
  INPUTS       : The logical output name
  RETURNS      : Nothing useful
  SIDE EFFECTS : Writes out deffunctions
  NOTES        : None
 ***************************************************/
static void SaveDeffunctions(
  void *theEnv,
  void *theModule,
  char *logicalName)
  {
   SaveConstruct(theEnv,theModule,logicalName,DeffunctionData(theEnv)->DeffunctionConstruct);
  }

#endif

#if DEBUGGING_FUNCTIONS

/******************************************************************
  NAME         : DeffunctionWatchAccess
  DESCRIPTION  : Parses a list of deffunction names passed by
                 AddWatchItem() and sets the traces accordingly
  INPUTS       : 1) A code indicating which trace flag is to be set
                    Ignored
                 2) The value to which to set the trace flags
                 3) A list of expressions containing the names
                    of the deffunctions for which to set traces
  RETURNS      : TRUE if all OK, FALSE otherwise
  SIDE EFFECTS : Watch flags set in specified deffunctions
  NOTES        : Accessory function for AddWatchItem()
 ******************************************************************/
static unsigned DeffunctionWatchAccess(
  void *theEnv,
  int code,
  unsigned newState,
  EXPRESSION *argExprs)
  {

   return(ConstructSetWatchAccess(theEnv,DeffunctionData(theEnv)->DeffunctionConstruct,newState,argExprs,
                                    EnvGetDeffunctionWatch,EnvSetDeffunctionWatch));
  }

/***********************************************************************
  NAME         : DeffunctionWatchPrint
  DESCRIPTION  : Parses a list of deffunction names passed by
                 AddWatchItem() and displays the traces accordingly
  INPUTS       : 1) The logical name of the output
                 2) A code indicating which trace flag is to be examined
                    Ignored
                 3) A list of expressions containing the names
                    of the deffunctions for which to examine traces
  RETURNS      : TRUE if all OK, FALSE otherwise
  SIDE EFFECTS : Watch flags displayed for specified deffunctions
  NOTES        : Accessory function for AddWatchItem()
 ***********************************************************************/
static unsigned DeffunctionWatchPrint(
  void *theEnv,
  char *logName,
  int code,
  EXPRESSION *argExprs)
  {

   return(ConstructPrintWatchAccess(theEnv,DeffunctionData(theEnv)->DeffunctionConstruct,logName,argExprs,
                                    EnvGetDeffunctionWatch,EnvSetDeffunctionWatch));
  }

/*********************************************************
  NAME         : EnvSetDeffunctionWatch
  DESCRIPTION  : Sets the trace to ON/OFF for the
                 deffunction
  INPUTS       : 1) TRUE to set the trace on,
                    FALSE to set it off
                 2) A pointer to the deffunction
  RETURNS      : Nothing useful
  SIDE EFFECTS : Watch flag for the deffunction set
  NOTES        : None
 *********************************************************/
globle void EnvSetDeffunctionWatch(
  void *theEnv,
  unsigned newState,
  void *dptr)
  {

   ((DEFFUNCTION *) dptr)->trace = (unsigned short) newState;
  }

/*********************************************************
  NAME         : EnvGetDeffunctionWatch
  DESCRIPTION  : Determines if trace messages are
                 gnerated when executing deffunction
  INPUTS       : A pointer to the deffunction
  RETURNS      : TRUE if a trace is active,
                 FALSE otherwise
  SIDE EFFECTS : None
  NOTES        : None
 *********************************************************/
globle unsigned EnvGetDeffunctionWatch(
  void *theEnv,
  void *dptr)
  {

   return(((DEFFUNCTION *) dptr)->trace);
  }

#endif

#endif


