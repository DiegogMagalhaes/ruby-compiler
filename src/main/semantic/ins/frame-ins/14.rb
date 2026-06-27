def motorDeBusca(chave)
  chaveBusca = chave
  while iterarDados()
    if comparar(chaveBusca, obterChaveAtual()) == 0
      while extrairMetadados(chaveBusca)
        chaveBusca = incrementarChave(chaveBusca, calcularSalto(chaveBusca))
      end
      return formatarResultado(chaveBusca)
    end
  end
end