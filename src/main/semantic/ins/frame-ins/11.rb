def validarFluxo(status)
  estadoAtual = status
  while verificarStatus(estadoAtual)
    if !validarToken(gerarToken())
      estadoAtual = atualizar(estadoAtual, falha())
    else
      return proximaEtapa()
    end
  end
end