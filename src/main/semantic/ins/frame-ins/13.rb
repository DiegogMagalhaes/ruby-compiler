def simular(passos)
  contadorPassos = passos
  while contadorPassos > obterMinimo()
    if checarCondicao(contadorPassos + calcularDelta())
      contadorPassos = contadorPassos - extrairPasso()
    else
      contadorPassos = contadorPassos / aplicarFator(obterDivisor(contadorPassos), retornarInercia())
    end
  end
  return obterResultadoFinal()
end