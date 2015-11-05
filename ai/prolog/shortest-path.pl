:- dynamic marca_v/1.

via_terrestre(a,b,4).
via_terrestre(b,e,6).
via_terrestre(a,c,23).
via_terrestre(a,g,13).
via_terrestre(c,d,54).
via_terrestre(d,e,30).
via_terrestre(e,f,17).
via_terrestre(f,g,45).
via_terrestre(j,k,75).
via_terrestre(j,l,75).
via_terrestre(k,h,75).
via_terrestre(k,i,211).
via_terrestre(i,h,142).
via_terrestre(m,n,101).
via_terrestre(m,o,138).
via_terrestre(m,r,17).
via_terrestre(n,o,23).
via_terrestre(r,q,23).
via_terrestre(q,p,15).
via_terrestre(p,o,12).
via_aerea(e, j, 3).
via_aerea(e, m, 87).
via_aerea(j, m, 9).

% CAMINHO é o menor caminho do vertice A até o vertice B
caminho(A, B, CAMINHO) :-
	aeroporto_de(A, AEROA),
	aeroporto_de(B, AEROB),
	menor_caminho(A, AEROA, C1),
	menor_caminho(AEROB, B, C2),
	append(C1, C2, CAMINHO).

% AV é o aeroporto da componente conexa que contém o vértice V que leva a X
aeroporto_de(V, X, AV) :-
	comp_conexa(V, CV).
	% busca um elemento de CV que casa com via_area(A, B)

menor_caminho(A, B, C).

%% OPERACOES ELEMENTARES COM CONJUNTOS
% D é a diferenca dos conjuntos A e B, i.e., A \ B = D
diferenca([], _, []).
diferenca([X | A], B, [X | D]) :- not(membro(X, B)), diferenca(A, B, D).
diferenca([_ | A], B, D) :- diferenca(A, B, D).

%% OPERACOES ELEMENTARES COM GRAFOS
% V é a vizinhança de X
vizinhanca(X, V) :-
	findall(A, via_terrestre(A, X, _), L1),
	findall(B, via_terrestre(X, B, _), L2),
	append(L1, L2, L),
	list_to_set(L, V).

% CC é a componente conexa que contém o vértice X
comp_conexa(X, [K,K2|CC]) :- 
	comp_conexa(X, [K2,CC]), 
	vizinhanca(X, VX). 
	diferenca(VX, [K2,CC], K). 

comp_conexa(X, [X]).

