# Importante resaltar, que Begin e End, não cria novo escopo em ruby
# Desta forma ruby não possui shadowing

def sombraParametro(x)
    acum = x*2
    begin
        x = acum + 9
        resultado = x*x
        return resultado
    end
end