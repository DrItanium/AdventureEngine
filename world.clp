;------------------------------------------------------------------------------
;The Adventure Engine
;Copyright (c) 2012-2016, Joshua Scoggins 
;All rights reserved.
;
;Redistribution and use in source and binary forms, with or without
;modification, are permitted provided that the following conditions are met:
;    * Redistributions of source code must retain the above copyright
;      notice, this list of conditions and the following disclaimer.
;    * Redistributions in binary form must reproduce the above copyright
;      notice, this list of conditions and the following disclaimer in the
;      documentation and/or other materials provided with the distribution.
;    * Neither the name of The Adventure Engine nor the
;      names of its contributors may be used to endorse or promote products
;      derived from this software without specific prior written permission.
;
;THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
;ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
;WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
;DISCLAIMED. IN NO EVENT SHALL Joshua Scoggins BE LIABLE FOR ANY
;DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
;(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
;LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
;ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
;(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
;SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
;------------------------------------------------------------------------------
; The concept of a world for a player to explore
;------------------------------------------------------------------------------
(defmodule world
           (import constants defglobal ?ALL)
           (import core defclass thing)
           (export defclass 
                   item
                   room
                   player))

(defclass world::player
  "The inventory container that the player uses / self"
  (is-a thing)
  (slot current-room
        (type INSTANCE)
        (visibility public)
        ;(allowed-classes room)
        (default-dynamic [entry]))
  (multislot items
             (type INSTANCE)
             (allowed-classes item)
             (visibility public)))

(defclass world::item
  "An thing that can be moved around"
  (is-a thing))

(defclass world::room
  "A place that contains items and can be exited from one of the four cardinal directions"
  (is-a thing)
  (multislot contents)
  ; TODO: eventually implement a description of the door
  (slot north
        (type INSTANCE
              SYMBOL)
        (visibility public)
        (allowed-classes room)
        (allowed-symbols FALSE))
  (slot south
        (type INSTANCE
              SYMBOL)
        (visibility public)
        (allowed-classes room)
        (allowed-symbols FALSE))
  (slot east 
        (type INSTANCE
              SYMBOL)
        (visibility public)
        (allowed-classes room)
        (allowed-symbols FALSE))
  (slot west
        (type INSTANCE
              SYMBOL)
        (visibility public)
        (allowed-classes room)
        (allowed-symbols FALSE)))

