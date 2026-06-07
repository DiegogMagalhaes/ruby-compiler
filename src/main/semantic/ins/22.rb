# Importante resaltar, que Begin e End, não cria novo escopo em ruby
# Desta forma ruby não possui shadowing

def sombraRetornoExterno(x)
    resultado = x * 100
    begin
        resultado = x*1
    end
    return resultado
end