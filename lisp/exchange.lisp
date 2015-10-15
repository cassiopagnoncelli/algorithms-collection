;; "Defina uma funcao 'troco' que recebe em argumento uma soma
;;  e uma lista de moedas disponiveis e retorna a lista de moedas
;;  que completam a soma."
;;
;;;; veja a funcao TROCO
;;

; entrada de dados (particularmente util para inteiros).
(defun scanf-int (indice &key (str ""))
  (if (= indice 0)
    (format *query-io* "~a" str)
    (format *query-io* "Moeda[~d] = " indice))
  (force-output *query-io*)
  (or (parse-integer (read-line *query-io*) :junk-allowed t) 0))

; adiciona 'limite' inteiros (oriundos da entrada padrao)
; na lista 'lista' e devolve a lista resultante.
(defun lista-constroi (&key (limite 1) (lista (list)))
  (if (< limite 1) 
    lista
    (append (list (scanf-int limite)) 
      (lista-constroi :limite (- limite 1) :lista lista))))

; devolve os elementos da lista que sao multiplos de 'multi'.
(defun multiplos (quantia lista)
  (remove-if-not #'(lambda (m) (= (truncate (/ quantia m)) (/ quantia m))) lista))

; secciona a 'quantia' em uma soma de 'moedas'.
(defun troco (quantia moedas)
  (if (> quantia 0)
    (progn
      (setf m (multiplos quantia (sort moedas #'>)))
      (format t "~d " (first m))
      (troco (- quantia (first m)) moedas))))

; exemplo
(defun exemplo()
  (format t "Entre com:~% - ~a~% - ~a~%~%"
    "quantia financeira"
    "quantas moedas diferentes sao (e as especifique quais sao)")
  (troco 
    (scanf-int 0 :str "Quantia: ")
    (lista-constroi 
      :limite (scanf-int 0 :str "Quantidade de moedas diferentes: "))))

(exemplo)
