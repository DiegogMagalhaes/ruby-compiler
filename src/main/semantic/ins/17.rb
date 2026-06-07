def triplo_aninhado()
    a = 1
    begin
        b = a+2
        begin
            c = b * 3
            begin
                d = c - 1
                return d
            end
        end
    end
end