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
; Definition of a Pointer used to interact with 
; Written by Joshua Scoggins
;------------------------------------------------------------------------------
(defclass another-world::SystemPointer
  (is-a Object)
  (slot address (type EXTERNAL-ADDRESS INTEGER))
  (message-handler fetch-byte primary)
  (message-handler fetch-word primary))
;------------------------------------------------------------------------------
;TODO: Implement fetch-byte-native
;(defmessage-handler another-world::SystemPointer fetch-byte ()
;                    (bind ?mf (fetch-byte-native ?self:address))
;                    (bind ?self:address (nth$ 1 ?mf))
;                    (return (nth$ 2 ?mf)))
;------------------------------------------------------------------------------
;TODO: Implement fetch-word-native
;(defmessage-handler another-world::SystemPointer fetch-word ()
;                    (bind ?mf (fetch-word-native ?self:address))
;                    (bind ?self:address (nth$ 1 ?mf))
;                    (return (nth$ 2 ?mf)))
;------------------------------------------------------------------------------
