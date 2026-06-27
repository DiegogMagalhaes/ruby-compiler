def buscar()
  while lerProximo()
    if extrairValor() == 0
      return obterPadrao()
    end
  end
end