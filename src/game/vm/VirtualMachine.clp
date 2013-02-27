;------------------------------------------------------------------------------
;Another World Expert System Virtual Machine Implementation
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
; Virtual Machine declaration as a set of rules.
; Written by Joshua Scoggins
;
; It is important to understand that CLIPS executes rules to perform actions.
; This makes it a great target for conversational systems. However, it is
; capable of performing normal computation as well. The only different is that
; it is up to the programmer to handle rule execution order if it is necessary
;
; This is usually done through the use of control facts or modules. In this
; case, I'm using a chained technique which causes rules to be fired via
; "leading" where each rule generates knowledge for the next one.
;------------------------------------------------------------------------------
; Section: Thread Execution 
;------------------------------------------------------------------------------

;------------------------------------------------------------------------------
; Section: Opcode Acquisition
;------------------------------------------------------------------------------

;------------------------------------------------------------------------------
; Section: Opcode Execution 
;------------------------------------------------------------------------------

