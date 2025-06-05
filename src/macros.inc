;;; Executes a conditional instruction if `a` is equal to the first argument
;;; (constant or register).
;;;
;;; For example:
;;;     if_eq 9, jr, .label
;;; Will jump-relative to .label if a == 9.
MACRO if_eq
    cp \1
    \2 z, \3
ENDM

;;; Executes a conditional instruction if `a` is not equal to the first
;;; argument (constant or register).
;;;
;;; For example:
;;;     if_ne 9, jr, .label
;;; Will jump-relative to .label if a != 9.
MACRO if_ne
    cp \1
    \2 nz, \3
ENDM

;;; Executes a conditional instruction if `a` is strictly less than the first
;;; argument (constant or register) when treated as unsigned.
;;;
;;; For example:
;;;     if_lt 9, jr, .label
;;; Will jump-relative to .label if a < 9 (unsigned).
MACRO if_lt
    cp \1
    \2 c, \3
ENDM

;;; Executes a conditional instruction if `a` is less than or equal to the
;;; first argument (which must be a constant) when treated as unsigned.
;;;
;;; For example:
;;;     if_le 9, jr, .label
;;; Will jump-relative to .label if a <= 9 (unsigned).
MACRO if_le
  IF (\1) >= $ff
    \2 \3
  ELSE
    if_lt (\1) + 1, \2, \3
  ENDC
ENDM

;;; Executes a conditional instruction if `a` is greater than or equal to the
;;; first argument (which must be a constant) when treated as unsigned.
;;;
;;; For example:
;;;     if_le 9, jr, .label
;;; Will jump-relative to .label if a <= 9 (unsigned).
MACRO if_gt
  IF (\1) == 0
    or a
    \2 nz, \3
  ELSE
    if_ge (\1) - 1, \2, \3
  ENDC
ENDM

;;; Executes a conditional instruction if `a` is greater than or equal to the
;;; first argument (constant or register) when treated as unsigned.
;;;
;;; For example:
;;;     if_ge 9, jr, .label
;;; Will jump-relative to .label if a >= 9 (unsigned).
MACRO if_ge
    cp \1
    \2 nc, \3
ENDM

;;; Executes a conditional instruction if `a` is negative when treated as
;;; signed.
;;;
;;; For example:
;;;     if_neg jr, .label
;;; Will jump-relative to .label if a < 0 (signed).
MACRO if_neg
    if_ge $80, \1, \2
ENDM

;;; Executes a conditional instruction if `a` is non-negative when treated as
;;; signed.
;;;
;;; For example:
;;;     if_nonneg jr, .label
;;; Will jump-relative to .label if a >= 0 (signed).
MACRO if_nonneg
    if_lt $80, \1, \2
ENDM
