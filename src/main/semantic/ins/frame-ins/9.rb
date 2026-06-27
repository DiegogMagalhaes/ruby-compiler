def formula(base)
  res = !estaVazio() + (calcular(base) * obterMultiplicador(ajustar(base)))
end