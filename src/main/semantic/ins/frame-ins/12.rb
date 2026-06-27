def checarSensor(leitura)
  copiaLeitura = leitura
  if calibrar(copiaLeitura) == obterAlvo()
    if dispararAlarme()
      return 1
    end
  end
  if !estaPronto() < limiteCritico()
    copiaLeitura = lerSegundaOpcao(copiaLeitura * ajustar())
  end
  return verificarSistema()
end