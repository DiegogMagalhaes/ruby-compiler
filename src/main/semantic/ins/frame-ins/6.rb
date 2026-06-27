def avaliar(x)
  localX = x
  if checar(localX) < limite()
    return verificarAtalho(localX)
  else
    localX = localX * recalcular(localX)
  end
end