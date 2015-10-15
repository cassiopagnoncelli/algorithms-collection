# -*- coding: utf-8 -*-
require 'singleton'

class MinhaClasse
  include Singleton
  
  def qualNome(nome)
    @nome = nome
  end
  
  def imprime
    puts @nome
  end
  
  public :qualNome, :imprime
end

a = MinhaClasse.instance              # não se usa MinhaClasse.new, usa-se
b = MinhaClasse.instance              # MinhaClasse.instance para criar inst.

a.qualNome "Joãozinho"
b.qualNome "Mariazinha"

a.imprime
b.imprime
