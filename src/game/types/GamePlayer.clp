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
; GamePlayer.clp - Defines the player in the context of this game
;
; Written by Joshua Scoggins
;------------------------------------------------------------------------------
(defclass GamePlayer 
          "An extension of the base player class which is specific to the game"
			 (is-a Player)
			 (slot health (type INTEGER) (range 0 ?VARIABLE))
			 (slot name (type SYMBOL STRING))
			 (multislot status)
			 (message-handler status primary))
;------------------------------------------------------------------------------
(defmessage-handler GamePlayer status primary ()
 (printout t "Name: " ?self:name crlf
             "Health: " ?self:health crlf
				 "Status: " (implode$ ?self:status) crlf))
;------------------------------------------------------------------------------
