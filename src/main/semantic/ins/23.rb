# Importante resaltar, que Begin e End, não cria novo escopo em ruby
# Desta forma ruby não possui shadowing

def sombraTresNiveis(x)
    v = x*2
    begin
        v = v*3
        begin
            v = v+1
            return v
        end
    end
end
