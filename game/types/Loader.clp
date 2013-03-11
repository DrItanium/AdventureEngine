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
; Loader for all the different types
; Written by Joshua Scoggins
;
; This is loaded ahead of the rules to make sure that the RETE network will
; evaluate all types correctly. If a rule is defined before a subtype is
; defined then the rule will not match against it.
;------------------------------------------------------------------------------
(load* "game/types/Polygon.clp")
(load* "game/types/StringEntry.clp")
(load* "game/types/Point.clp")
(load* "game/types/SystemPointer.clp")

