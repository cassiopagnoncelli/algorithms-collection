;; "Defina uma funcao booleana que diz se uma expressao
;;  tem o numero correto de parenteses."
;;
;;;; veja a funcao CHECA-PARENTESES
;;

; recebe uma expressao em forma de string e avalia se os
; parenteses sao abertos e fechados corretamente.
; um exemplo de uso:
;
;  (checa-parenteses "(()()((()))(())()((())))")
;
; e' avaliado como T.
;
(defun checa-parenteses (expressao)
  (setf nivel 0)
  (dotimes (i (length expressao))
    (if (equal (char expressao i) #\()
      (setf nivel (+ nivel 1)))
    (if (equal (char expressao i) #\)) 
      (progn 
        (setf nivel (- nivel 1))
        (< nivel 0)))
    (if (< nivel 0) 
      (return)))
  (= nivel 0)
)

; execucao
(format t "Entre com uma expressao usando parenteses: ")
(format t "Validade: ~d" (checa-parenteses (read-line)))
