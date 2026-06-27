def pipelineComplexo(id, peso)
  idInterno = id
  pesoInterno = peso
  if !sistemaIniciado() == checarTrava(obterSeguranca())
    return abortar()
  else
    while atualizarCiclo(idInterno) < obterMaxCiclos(calcularEspera(idInterno))
      if validarMetrica(pesoInterno + transformar(idInterno))
        while lerBuffer()
          pesoInterno = pesoInterno * fatorCorrecao(obterMetricaAtual())
        end
      else
        if logarErro(gerarMensagem(idInterno))
          idInterno = redefinirId(idInterno, puxarBackup())
        end
      end
    end
  end
  return verificarSucessoFinal(idInterno, finalizarPeso(pesoInterno))
end