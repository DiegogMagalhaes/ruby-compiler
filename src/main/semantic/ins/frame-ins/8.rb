def calcularTaxa(tipo)
  if estaAtivo(tipo)
    if obterDesconto() > 50
      return aplicarBonus(total() + 10)
    end
  end
end