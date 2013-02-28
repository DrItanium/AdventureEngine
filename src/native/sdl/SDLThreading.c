/*
Copyright (c) 2013, Joshua Scoggins 
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the name of Joshua Scoggins nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL Joshua Scoggins BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#include "../clips.h"
#include "SDL/SDL.h"
#include "SDL/SDL_thread.h"
#include "SDLThreading.h"

extern void* SDLThread_SDLCreateMutexCommand(void* theEnv);
extern int SDLThread_SDLLockMutexCommand(void* theEnv);
extern int SDLThread_SDLUnlockMutexCommand(void* theEnv);
extern void SDLThread_SDLDestroyMutexCommand(void* theEnv);

extern void SDLThreadDefinitions(void* theEnv) {
   EnvDefineFunction2(theEnv, (char*)"sdl-create-mutex", 'a',
         PTIEF SDLThread_SDLCreateMutexCommand,
         (char*)"SDLThread_SDLCreateMutexCommand", 
         (char*)"00a");
   EnvDefineFunction(theEnv, (char*)"sdl-lock-mutex", 'g',
         PTIEF SDLThread_SDLLockMutexCommand,
         (char*)"SDLThread_SDLLockMutexCommand");
   EnvDefineFunction(theEnv, (char*)"sdl-unlock-mutex", 'g',
         PTIEF SDLThread_SDLUnlockMutexCommand,
         (char*)"SDLThread_SDLUnlockMutexCommand");
   EnvDefineFunction2(theEnv, (char*)"sdl-destroy-mutex", 'v',
         PTIEF SDLThread_SDLDestroyMutexCommand,
         (char*)"SDLThread_DestroyMutexCommand",
         (char*)"11a");
}

void* SDLThread_SDLCreateMutexCommand(void* theEnv) {
   return (void*)SDL_CreateMutex();
}

int SDLThread_SDLLockMutexCommand(void* theEnv) {
   SDL_mutex* mutex;
   DATA_OBJECT arg0;
   if(EnvArgCountCheck(theEnv, (char*)"sdl-lock-mutex", EXACTLY, 1) == -1) {
      EnvPrintRouter(theEnv, (char*)"werror", "ERROR: sdl-lock-mutex expected exactly one argument\n");
      return -1;
   }

   if(EnvArgTypeCheck(theEnv, (char*)"sdl-lock-mutex", 1, EXTERNAL_ADDRESS, &arg0) == FALSE) {
      EnvPrintRouter(theEnv, (char*)"werror", "ERROR: sdl-lock-mutex expected an external-address\n");
      return -1;
   }

   mutex = (SDL_mutex*)GetValue(arg0);
   return SDL_mutexP(mutex);
}

int SDLThread_SDLUnlockMutexCommand(void* theEnv) {
   SDL_mutex* mutex;
   DATA_OBJECT arg0;
   if(EnvArgCountCheck(theEnv, (char*)"sdl-unlock-mutex", EXACTLY, 1) == -1) {
      EnvPrintRouter(theEnv, (char*)"werror", "ERROR: sdl-unlock-mutex expected exactly one argument\n");
      return -1;
   }

   if(EnvArgTypeCheck(theEnv, (char*)"sdl-unlock-mutex", 1, EXTERNAL_ADDRESS, &arg0) == FALSE) {
      EnvPrintRouter(theEnv, (char*)"werror", "ERROR: sdl-unlock-mutex expected an external-address\n");
      return -1;
   }

   mutex = (SDL_mutex*)GetValue(arg0);
   return SDL_mutexV(mutex);
}

void SDLThread_SDLDestroyMutexCommand(void* theEnv) {
   SDL_mutex* mutex;
   DATA_OBJECT arg0;
   if(EnvArgCountCheck(theEnv, (char*)"sdl-destroy-mutex", EXACTLY, 1) == -1) {
      EnvPrintRouter(theEnv, (char*)"werror", "ERROR: sdl-destroy-mutex expected exactly one argument\n");
      return;
   }

   if(EnvArgTypeCheck(theEnv, (char*)"sdl-destroy-mutex", 1, EXTERNAL_ADDRESS, &arg0) == FALSE) {
      EnvPrintRouter(theEnv, (char*)"werror", "ERROR: sdl-destroy-mutex expected an external-address\n");
      return;
   }

   mutex = (SDL_mutex*)GetValue(arg0);
   SDL_DestroyMutex(mutex);
}
