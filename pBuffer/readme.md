
# Trabalho Agenda pBuffer
# Mariana Ferreira Tica

O desafio proibe declarar qualquer variavel normal, int, char,  no programa. A solução e reservar um unico bloco de memoria dinamica — o pBuffer — e guardar TUDO dentro

minha gaveta, a questao e: como organizar? 

TAMANHO_CONTROLES	-> sizeof(int) * 4	-> 16 bytes
AREA_TEMP	        -> 100	            -> 100 bytes
INICIO_DADOS	    -> 16 + 100	        -> 116 bytes

MAPA DE MEMÓRIA DO pBuffer:
   índice [0] -> Opção escolhida no Menu -> ((int*)pBuffer)[0] 
   índice [1] -> Quantidade total de pessoas cadastradas
   índice [2] -> Variável de auxílio para os laços 'for' (o nosso 'i')
   índice [3] -> Armazena o tamanho total do buffer em bytes (para o realloc), (atualizado a cada add/remove)
   
   ÁREA TEMPORÁRIA:
   Logo após os 4 inteiros acima, temos 100 bytes para usar como temp
   para o fgets (50 bytes para nome e 50 para email).



[0]menu | [1]qtdPessoas | [2]contador | [3]tamTotal | temp[0..49]nome (fgets) | temp[50..99]email (fgets) | pessoa 1 ......



