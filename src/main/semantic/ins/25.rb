# Importante resaltar, que Begin e End, não cria novo escopo em ruby
# Desta forma ruby não possui shadowing

def sombraDupla(a,b)
    v = a*10
    w = b+1
    begin
        v = w*2
        begin
            w = v+v
            return w
        end
    end
end