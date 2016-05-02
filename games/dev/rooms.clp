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
         (printout ?*router-out* tab "Ok" crlf)
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
(defrule game::list-command
         ?f <- (object (is-a input-state)
                       (should-prompt FALSE)
                       (processed-input FALSE)
                       (input list ?group))
         =>
         (modify-instance ?f
                          (processed-input TRUE))
         (assert (list ?group)))

(defrule game::list-rooms
         ?f <- (list rooms)
         =>
         (retract ?f)
         (printout ?*router-out*
                   tab "Currently defined rooms" crlf)
         (do-for-all-instances ((?r room))
                               TRUE
                               (printout ?*router-out*
                                         tab tab (instance-name ?r) crlf)))
(defrule game::list-unknown
         (declare (salience ?*after-normal-priority*))
         ?f <- (list ?target)
         =>
         (retract ?f)
         (printout ?*router-out*
                   tab ?target " is not a valid item to list" crlf))

(defrule game::new-room::with-title
         ?f <- (object (is-a input-state)
                       (should-prompt FALSE)
                       (processed-input FALSE)
                       (input new-room ?room-name&:(symbolp ?room-name)))
         =>
         (modify-instance ?f
                          (processed-input TRUE))
         (printout ?*router-out* 
                   tab "Made a new blank room named: " 
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
                   tab "Made a new blank room named: " 
                   (make-instance of room) crlf))

(defrule game::set-title:symbolp
         ?f <- (object (is-a input-state)
                       (should-prompt FALSE)
                       (processed-input FALSE)
                       (input set-title 
                              ?target&:(symbolp ?target)
                              ?title))
         (object (is-a room)
                 (name ?room&:(eq (symbol-to-instance-name ?target)
                                  ?room)))
         =>
         (modify-instance ?f
                          (processed-input TRUE))
         (modify-instance ?room
                          (title ?title))
         (printout ?*router-out*
                   tab "Set " ?room "'s title to " ?title crlf))

(defrule game::set-title:instancep
         ?f <- (object (is-a input-state)
                       (should-prompt FALSE)
                       (processed-input FALSE)
                       (input set-title 
                              ?room&:(instancep ?room)
                              ?title))
         (object (is-a room)
                 (name ?room))
         =>
         (modify-instance ?f
                          (processed-input TRUE))
         (modify-instance ?room
                          (title ?title))
         (printout ?*router-out*
                   tab "Set " ?room "'s title to " ?title crlf))

(defrule game::parse-print-contents:symbolp
         ?f <- (object (is-a input-state)
                       (should-prompt FALSE)
                       (processed-input FALSE)
                       (input print ?instance&:(symbolp ?instance)))
         =>
         (modify-instance ?f
                          (processed-input TRUE))
         (assert (print (symbol-to-instance-name ?instance))))

(defrule game::parse-print-contents
         ?f <- (object (is-a input-state)
                       (should-prompt FALSE)
                       (processed-input FALSE)
                       (input print ?instance&:(instancep ?instance)))
         =>
         (modify-instance ?f
                          (processed-input TRUE))
         (assert (print ?instance)))

(defrule game::print-contents
         ?f <- (print ?instance)
         (test (instance-existp ?instance))
         =>
         (retract ?f)
         (send ?instance print))

(defrule game::print-contents:doesnt-exist
         ?f <- (print ?instance)
         (test (not (instance-existp ?instance)))
         =>
         (retract ?f)
         (printout ?*router-out*
                   tab ?instance " is not a defined instance" crlf))

(defrule game::set-description:symbolp
         ?f <- (object (is-a input-state)
                       (should-prompt FALSE)
                       (processed-input FALSE)
                       (input set-description 
                              ?target&:(symbolp ?target)
                              ?description))
         (object (is-a room)
                 (name ?room&:(eq (symbol-to-instance-name ?target)
                                  ?room)))
         =>
         (modify-instance ?f
                          (processed-input TRUE))
         (modify-instance ?room
                          (description ?description))
         (printout ?*router-out*
                   tab "Set " ?room "'s description to " ?description crlf))

(defrule game::set-description:instancep
         ?f <- (object (is-a input-state)
                       (should-prompt FALSE)
                       (processed-input FALSE)
                       (input set-description 
                              ?room&:(instancep ?room)
                              ?description))
         (object (is-a room)
                 (name ?room))
         =>
         (modify-instance ?f
                          (processed-input TRUE))
         (modify-instance ?room
                          (description ?description))
         (printout ?*router-out*
                   tab "Set " ?room "'s description to " ?description crlf))

(defrule game::parse:link-room-to-another-room
         ?f <- (object (is-a input-state)
                       (should-prompt FALSE)
                       (processed-input FALSE)
                       (input link
                              ?room0 ?direction0
                              to
                              ?room1 ?direction1))
         =>
         (modify-instance ?f
                          (processed-input TRUE))
         (bind ?r0 
               (if (symbolp ?room0) then
                 (symbol-to-instance-name ?room0)
                 else
                 ?room0))
         (bind ?r1
               (if (symbolp ?room1) then
                 (symbol-to-instance-name ?room1)
                 else
                 ?room1))
         (assert (connect ?r0 to ?r1 via ?direction0)
                 (connect ?r1 to ?r0 via ?direction1)))

(defrule game::link-room-to-another-room:illegal-direction
         (declare (salience ?*before-normal-priority*))
         ?f <- (connect ? to ? via ?direction)
         (test (neq ?direction north south east west))
         =>
         (retract ?f)
         (printout ?*router-out*
                   tab ?direction " is not a legal linkage direction" crlf))

(defrule game::link-room-to-another-room:primary-room-is-bad
         (declare (salience ?*before-normal-priority*))
         ?f <- (connect ?bad-room to ? via ?)
         (not (exists (object (is-a room)
                              (name ?bad-room))))
         =>
         (retract ?f)
         (printout ?*router-out*
                   tab ?bad-room " is not a room" crlf))

(defrule game::link-room-to-another-room:secondary-room-is-bad
         (declare (salience ?*before-normal-priority*))
         ?f <- (connect ? to ?bad-room via ?)
         (not (exists (object (is-a room)
                              (name ?bad-room))))
         =>
         (retract ?f)
         (printout ?*router-out*
                   tab ?bad-room " is not a room" crlf))

(defrule game::link-room-to-another-room
         ?f <- (connect ?curr to ?other via ?direction)
         (object (is-a room)
                 (name ?curr))
         (object (is-a room)
                 (name ?other))
         =>
         (retract ?f)
         (send ?curr 
               (sym-cat put- ?direction)
               ?other))

(defrule game::link-room-to-another-room
         ?f <- (connect ?curr to ?other via ?direction)
         (object (is-a room)
                 (name ?curr))
         (object (is-a room)
                 (name ?other))
         =>
         (retract ?f)
         (printout ?*router-out* 
                   tab "linked " ?curr " to " ?other " via " ?direction " direction" crlf)
         (send ?curr 
               (sym-cat put- ?direction)
               ?other))



