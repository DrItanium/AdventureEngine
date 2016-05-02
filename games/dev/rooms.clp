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
; Inspect.clp - a simple inspect the room game
;------------------------------------------------------------------------------
; Required module implementations
;------------------------------------------------------------------------------
(defmodule pre-prompt
           (import constants defglobal router-out))
(defrule pre-prompt::print-objectives
         =>
         (printout ?*router-out* 
                   "This tools is meant to automate the construction of rooms" crlf))
(defmodule post-prompt
           (import constants 
                   defglobal 
                   router-out))
;(defrule post-prompt::say-thanks
;         =>
;         (printout ?*router-out*
;                   "Thanks for playing!" crlf))

;------------------------------------------------------------------------------

(defmodule game 
           (import constants ?ALL)
           (import core ?ALL)
           (import world ?ALL)
           (import prompt defclass input-state))

(definstances game::room-and-items
              (self of player)
              (entry of room 
                     (title "")
                     (description "A non descript room")))

(defrule game::handle-look-keyword:no-extra-input
         ?f <- (object (is-a input-state)
                       (should-prompt FALSE)
                       (processed-input FALSE)
                       (input look))
         (object (is-a player)
                 (name [self])
                 (current-room ?room))
         (object (is-a room)
                 (name ?room)
                 (description ?description))
         =>
         (modify-instance ?f
                          (processed-input TRUE))
         (printout ?*router-out* 
                   "You are in a " ?description crlf))

(defrule game::handle-go-keyword
         ?f <- (object (is-a input-state)
                       (should-prompt FALSE)
                       (processed-input FALSE)
                       (input go ?direction))
         =>
         (modify-instance ?f (processed-input TRUE))
         (assert (go ?direction)))
(defrule game::go-north
         ?f <- (go north)
         ?p <- (object (is-a player)
                       (name [self])
                       (current-room ?room))
         (object (is-a room)
                 (name ?room)
                 (north ?north))
         =>
         (retract ?f)
         (assert (go to room north ?north)))



(defrule game::go-south
         ?f <- (go south)
         ?p <- (object (is-a player)
                       (name [self])
                       (current-room ?room))
         (object (is-a room)
                 (name ?room)
                 (south ?south))
         =>
         (retract ?f)
         (assert (go to room south ?south)))
(defrule game::go-west
         ?f <- (go west)
         ?p <- (object (is-a player)
                       (name [self])
                       (current-room ?room))
         (object (is-a room)
                 (name ?room)
                 (west ?west))
         =>
         (retract ?f)
         (assert (go to room west ?west)))
(defrule game::go-east
         ?f <- (go east)
         ?p <- (object (is-a player)
                       (name [self])
                       (current-room ?room))
         (object (is-a room)
                 (name ?room)
                 (east ?east))
         =>
         (retract ?f)
         (assert (go to room east ?east)))

(defrule game::go-to-room:nope
         ?f <- (go to room ?dir FALSE)
         =>
         (retract ?f)
         (printout ?*router-out* 
                   "Can't go " ?dir " from this room!" crlf))

(defrule game::go-to-room
         ?f <- (go to room ? ?target&~FALSE)
         =>
         (retract ?f)
         (modify-instance [self]
                          (current-room ?target)))

(defrule game::list-inventory
         ?f <- (object (is-a input-state)
                       (should-prompt FALSE)
                       (processed-input FALSE)
                       (input inventory))
         (object (is-a player)
                 (name [self])
                 (items $?items))
         =>
         (printout ?*router-out*
                   tab "Currently have in inventory:" crlf)
         (progn$ (?item ?items)
                 (printout ?*router-out*
                           tab tab "- " (send ?item get-title) crlf))
         (modify-instance ?f 
                          (processed-input TRUE)))

(defrule game::inspect-item
         ?f <- (object (is-a input-state)
                       (should-prompt FALSE)
                       (processed-input FALSE)
                       (input inspect ?item))
         (object (is-a item)
                 (title ?item)
                 (description ?desc)
                 (name ?n))
         (object (is-a player)
                 (name [self])
                 (items $? ?n $?))
         =>
         (modify-instance ?f 
                          (processed-input TRUE))
         (printout ?*router-out* tab ?desc crlf))

(defrule game::inspect-item:not-in-inventory
         ?f <- (object (is-a input-state)
                       (should-prompt FALSE)
                       (processed-input FALSE)
                       (input inspect ?item))
         (object (is-a item)
                 (title ?item)
                 (name ?n))
         (object (is-a player)
                 (name [self])
                 (items $?elements&:(not (member$ ?n ?elements))))
         =>
         (modify-instance ?f
                          (processed-input TRUE))
         (printout ?*router-out* 
                   tab "This is not an item in your inventory" crlf))

(defrule game::inspect-item:doesn't-exist
         ?f <- (object (is-a input-state)
                       (should-prompt FALSE)
                       (processed-input FALSE)
                       (input inspect ?item))
         (not (exists (object (is-a item)
                              (title ?item))))
         =>
         (modify-instance ?f
                          (processed-input TRUE))
         (printout ?*router-out* 
                   tab "This is not an item in your inventory" crlf))

(defrule game::list-rooms
         ?f <- (object (is-a input-state)
                       (should-prompt FALSE)
                       (processed-input FALSE)
                       (input list rooms))
         =>
         (printout ?*router-out*
                   tab "Currently defined rooms" crlf)
         (do-for-all-instances ((?r room))
                               TRUE
                               (printout ?*router-out*
                                         tab tab (instance-name ?r) crlf)))
(defrule game::new-room::with-title
         ?f <- (object (is-a input-state)
                       (should-prompt FALSE)
                       (processed-input FALSE)
                       (input new-room ?room-name&:(symbolp ?room-name)))

         =>
         (modify-instance ?f
                          (processed-input TRUE))
         (printout ?*router-out* 
                   "Made a new blank room named: " 
                   (make-instance ?room-name of room) crlf))

(defrule game::new-room
         ?f <- (object (is-a input-state)
                       (should-prompt FALSE)
                       (processed-input FALSE)
                       (input new-room))

         =>
         (modify-instance ?f
                          (processed-input TRUE))
         (printout ?*router-out* 
                   "Made a new blank room named: " 
                   (make-instance of room) crlf))

(defrule game::set-title
         ?f <- (object (is-a input-state)
                       (should-prompt FALSE)
                       (processed-input FALSE)
                       (input set-title ?room ?title))
         (object (is-a room)
                 (name ?room))
         =>
         (modify-instance ?f
                          (processed-input TRUE))
         (modify-instance ?room
                          (title ?title))
         (printout ?*router-out*
                   "Set " ?room " to " ?title crlf))

