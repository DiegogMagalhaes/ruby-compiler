def processarMatriz()
  while possuiLinha()
    while possuiColuna()
      celula = processarCelula(obterX(), obterY(maximo()))
    end
  end
end