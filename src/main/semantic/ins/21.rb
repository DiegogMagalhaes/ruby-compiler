# Importante resaltar, que Begin e End, não cria novo escopo em ruby
# Desta forma ruby não possui shadowing

def sombra(x)
    resultado = x * 100
    begin
        resultado = x*1
        return resultado
    end
end
