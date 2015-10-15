;; "Faca um programa que fusiona duas listas ordenadas
;;  em uma lista ordenada."
;;
;;;; veja a funcao LISTA-FUSIONA
;;

; entrada de dados (particularmente util para inteiros).
(defun scanf-int (rotulo indice)
  (if (= indice 0)
    (format *query-io* 
      "Entre com o numero de elementos da lista ~a~%|~a| = " rotulo rotulo)
    (format *query-io* "~a[~d] = " rotulo indice))
  (force-output *query-io*)
  (or (parse-integer (read-line *query-io*) :junk-allowed t) 0))

; adiciona 'limite' inteiros (oriundos da entrada padrao)
; na lista 'lista' e devolve a lista resultante.
(defun ordenada-constroi (lista limite rotulo)
  (if (< limite 1) (sort lista #'<)
    (append (list (scanf-int rotulo limite)) (ordenada-constroi lista (- limite 1) rotulo))))

; recebe como entrada duas listas, podendo ou nao estarem ordenadas,
; e devolve a fusao ordenada das mesmas.
(defun lista-fusiona (lista-1 lista-2)
  (sort (append lista-1 lista-2) #'<))

; inicia o programa
(print (lista-fusiona 
  (ordenada-constroi () (scanf-int "A" 0) "A") 
  (ordenada-constroi () (scanf-int "B" 0) "B")))
