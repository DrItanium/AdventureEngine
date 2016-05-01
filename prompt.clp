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
; The user input prompt, located in the USER-INPUT module
;------------------------------------------------------------------------------
(defmodule USER-INPUT
           (export ?ALL))
(defclass USER-INPUT::input-state
 (is-a USER)
 (slot should-prompt
       (type SYMBOL)
       (allowed-symbols TRUE
                        FALSE))
 (slot prompt
       (type STRING)
       (storage local)
       (visibility public)
       (default ?NONE))
 (slot raw-input
       (type STRING)
       (default-dynamic ""))
 (multislot decomposed-elements
            (visibility public)))

(definstances USER-INPUT::initialization-of-input-state
              (of input-state
                  (prompt "> ")))

(defrule USER-INPUT::read-input
         "Read input from the end user"
         ?f <- (object (is-a input-state)
                       (should-prompt TRUE)
                       (prompt ?prompt))
         =>
         (printout t ?prompt tab)
         (modify-instance ?f 
                          (should-prompt FALSE)
                          (raw-input (bind ?rinput (readline)))
                          (decomposed-elements (explode$ ?rinput))))

(defrule USER-INPUT::reset-input
         (declare (salience -1))
         ?f <- (object (is-a input-state)
                       (should-prompt FALSE))
         =>
         (modify-instance ?f (should-prompt TRUE)))


