;; "Faça um programa que solicita o limite inferior e superior de um 
;;  intervalo. O usuario deve tentar adivinhar e o programa responde
;;  'muito alto' ou 'muito baixo', ate o usuario adivinhar."
;;
;;;; O programa inicia com a funcao ADIVINHA.
;;

; limite superior do intervalo no qual o numero sera sorteado.
(setq maximo 10000)

; sorteia um numero natural nao maior que 'maximo'
(setq numero (random maximo))

; apresentacao
(format t "Um numero natural nao maior que ~d foi sorteado. Tente adivinha-lo.~%" maximo)

; entrada de dados
(defun scanf-int ()
  (format *query-io* "tentativa: ")
  (force-output *query-io*)
  (or (parse-integer (read-line *query-io*) :junk-allowed t) 0))

; solicita os limites inferior e superior do intervalo recursivamente
; ate o usuario acertar o numero que foi sorteado.
(defun adivinha ()
  (setf chute (scanf-int))
  (if (= numero chute) (format t "Acertou!~%")
    (if (> numero chute) (format t "Muito baixo.~%") (format t "Muito alto.~%")))
  (if (not (= numero chute)) (adivinha)))

; inicia o jogo
(adivinha)
