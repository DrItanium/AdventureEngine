;The Test Text Adventure
;Copyright (C) 2013 Joshua Scoggins 
;
;This program is free software; you can redistribute it and/or
;modify it under the terms of the GNU General Public License
;as published by the Free Software Foundation; either version 2
;of the License, or (at your option) any later version.
;
;This program is distributed in the hope that it will be useful,
;but WITHOUT ANY WARRANTY; without even the implied warranty of
;MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
;GNU General Public License for more details.
;
;You should have received a copy of the GNU General Public License
;along with this program; if not, write to the Free Software
;Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
;------------------------------------------------------------------------------
; UserInput.clp - Defines rules to take input from the user
; 
; Written by Joshua Scoggins
;------------------------------------------------------------------------------
(defrule test-text-adventure::take-in-input-from-user
			?msg <- (message (action get-input))
			=>
			(printout t "> ")
			(modify ?msg (action parse-input))
			(assert (TextInput (input (explode$ (readline))))))

;------------------------------------------------------------------------------
(defrule test-text-adventure::quit-execution
			(declare (salience 1))
			?msg <- (message (action parse-input))
			?f <- (TextInput (input exit))
			=>
			(retract ?msg ?f)
			(printout t "Exiting...." crlf)
			(exit))
;------------------------------------------------------------------------------
(defrule test-text-adventure::halt-execution
			(declare (salience 1))
			?msg <- (message (action parse-input))
			?f <- (TextInput (input facts))
			=>
			(facts)
			(retract ?f)
			(modify ?msg (action get-input)))
;------------------------------------------------------------------------------
(defrule test-text-adventure::printout-input
			?msg <- (message (action parse-input))
			?f <- (TextInput (input ?input))
			=>
			(modify ?msg (action get-input))
			(retract ?f)
			(printout t ?input crlf))
;------------------------------------------------------------------------------
