;; "Defina uma funcao que le uma lista de inteiros e retorna
;;  uma lista que alterna par e impar."
;;
;;;;  veja a funcao PRINCIPAL.
;;

; entrada de dados (particularmente util para inteiros).
(defun scanf-int (&key (indice 0))
  (if (= indice 0)
    (format *query-io* "Entre com o numero de elementos da lista L~%|L| = ")
    (format *query-io* "L[~d] = " indice))
  (force-output *query-io*)
  (or (parse-integer (read-line *query-io*) :junk-allowed t) 0))

; adiciona 'limite' inteiros (oriundos da entrada padrao)
; na lista 'lista' e devolve a lista resultante.
(defun lista-constroi (&key (limite 1) (lista (list)))
  (if (< limite 1) 
    lista
    (append (list (scanf-int :indice limite)) 
      (lista-constroi :limite (- limite 1) :lista lista))))

; funcao que coloca em 'restante' a intercalacao dos 'pares'
; e 'impares'.
(defun alterna (pares impares restante)
  (if (< 0 (max (length pares) (length impares)))
    (alterna (rest pares) (rest impares)
      (append restante 
        (if (< 0 (length pares)) (list (first pares)))
        (if (< 0 (length impares)) (list (first impares)))
      ))
   restante))

; funcao que le uma lista de inteiros e retorna uma lista
; que alterna par e impar.
(defun principal (lista-de-inteiros)
  (alterna 
    (remove-if-not #'evenp lista-de-inteiros)
    (remove-if-not #'oddp lista-de-inteiros)
    (list)))

; exemplo
(defun exemplo ()
  (print (principal (lista-constroi :limite (scanf-int)))))

(exemplo)
