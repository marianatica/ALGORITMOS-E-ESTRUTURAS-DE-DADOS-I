#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO_CONTROLES (sizeof(int) * 4)
#define AREA_TEMP 100
#define INICIO_DADOS (TAMANHO_CONTROLES + AREA_TEMP) //116 bytes


void AdicionarPessoa(void **pBuffer) {

    //[0]=tamanhoNome, [1]=tamanhoEmail, [2]=idade, [3]=bytesDestaPessoa, [4]=novoTamanhoTotal
    int *pInteiroTemp = (int *)malloc(sizeof(int) * 5);
    //variavel temp
    char *temp = (char *)(*pBuffer) + TAMANHO_CONTROLES;
    
    printf("Nome: "); 
    fgets(temp, 50, stdin);
    pInteiroTemp[0] = strlen(temp) + 1; // tamanhoNome e +1 para o \0

    printf("Email: "); 
    fgets(temp + 50, 50, stdin);
    pInteiroTemp[1] = strlen(temp + 50) + 1;

    printf("Idade: "); 
    scanf("%d", &pInteiroTemp[2]); 
    getchar();

    //bytesDestaPessoa
    pInteiroTemp[3] = (sizeof(int) * 3) + pInteiroTemp[0] + pInteiroTemp[1];
    //novoTamanhoTotal
    pInteiroTemp[4] = ((int *)(*pBuffer))[3] + pInteiroTemp[3]; //((int *)(*pBuffer))[3] e o tamanhoatual + o tamanho dos dados da nova pessoa

    //realloc
    void *pNovoBuffer = realloc(*pBuffer, pInteiroTemp[4]);
    if (!pNovoBuffer) {
        printf("Erro de alocacao de memoria.\n");
        return;
    }
    *pBuffer = pNovoBuffer;

    //a nova pessoa sera add a partir do antigo tamanho total
    void *posicaoAtual = (*pBuffer) + ((int *)(*pBuffer))[3];

    //salvando os dados da nova pessoa
    *(int *)(posicaoAtual + sizeof(int)) = pInteiroTemp[0];
    *(int *)(posicaoAtual + sizeof(int) * 2) = pInteiroTemp[1];
    *(int *)posicaoAtual = pInteiroTemp[2]; //usa "casts" como (int *) para dizer ao compilador: escreva esse numero inteiro nestes bytes especificos
    
    strcpy((char *)(posicaoAtual + sizeof(int) * 3), temp); //como ja temos o tmnho e o dado podemos quardar ele
    strcpy((char *)(posicaoAtual + sizeof(int) * 3 + pInteiroTemp[0]), temp + 50);

    ((int *)(*pBuffer))[3] = pInteiroTemp[4];
    ((int *)(*pBuffer))[1] += 1; //incrementa qtd de pessoas


    free(pInteiroTemp);
    printf("Sucesso: pessoa adicionada!\n");
}

void ListarTodos(void *pBuffer) {

    //[0]=qtdPessoas, [1]=tamanhoNome, [2]=tamanhoEmail
    int *pInteiroTemp = (int *)malloc(sizeof(int) * 3); 
    pInteiroTemp[0] = ((int *)pBuffer)[1]; //indice 1 pega a qtd de pessoas
    
    if (pInteiroTemp[0] == 0) {
        printf("\nAgenda vazia!\n");
        free(pInteiroTemp);
        return;
    }

    //a leitura comeca apos o cabeçalho e temp
    void *ponteiroPessoa = pBuffer + INICIO_DADOS;

    for (((int *)pBuffer)[2] = 0; ((int *)pBuffer)[2] < pInteiroTemp[0]; ((int *)pBuffer)[2]++) {
        
        pInteiroTemp[1] = *(int *)(ponteiroPessoa + sizeof(int)); //tamanhoNome
        pInteiroTemp[2] = *(int *)(ponteiroPessoa + sizeof(int) * 2); ////tamanhoEmail

        printf("\n--- Registro %d ---", ((int *)pBuffer)[2] + 1);
        printf("\nNome: %s", (char *)(ponteiroPessoa + sizeof(int) * 3));
        printf("Idade: %d\n", *(int *)ponteiroPessoa);
        printf("Email: %s", (char *)(ponteiroPessoa + sizeof(int) * 3 + pInteiroTemp[1]));

        //avanca o ponteiro para o inicio da proxima pessoa
        ponteiroPessoa += (sizeof(int) * 3) + pInteiroTemp[1] + pInteiroTemp[2];
    }
    free(pInteiroTemp);
}

void BuscarPessoa(void *pBuffer) {

    //[0]=tamanhoNome, [1]=tamanhoEmail
    int *pInteiroTemp = (int *)malloc(sizeof(int) * 2); 

    if (((int *)pBuffer)[1] == 0) {
        printf("\nAgenda vazia!\n");
        free(pInteiroTemp);
        return;
    }

    char *nomeBusca = (char *)pBuffer + TAMANHO_CONTROLES;
    printf("Digite o nome para buscar: "); 
    fgets(nomeBusca, 50, stdin);

    void *ponteiroPessoa = pBuffer + INICIO_DADOS;

    for (((int *)pBuffer)[2] = 0; ((int *)pBuffer)[2] < ((int *)pBuffer)[1]; ((int *)pBuffer)[2]++) {
        
        pInteiroTemp[0] = *(int *)(ponteiroPessoa + sizeof(int));
        pInteiroTemp[1] = *(int *)(ponteiroPessoa + sizeof(int) * 2);
        char *nomeAtual = (char *)(ponteiroPessoa + sizeof(int) * 3);

        if (strcmp(nomeBusca, nomeAtual) == 0) {
            printf("\nEncontrado!");
            printf("Idade: %d | Email: %s", *(int *)ponteiroPessoa, (char *)(ponteiroPessoa + sizeof(int) * 3 + pInteiroTemp[0]));
            free(pInteiroTemp);
            return;
        }
        ponteiroPessoa += (sizeof(int) * 3) + pInteiroTemp[0] + pInteiroTemp[1];
        free(pInteiroTemp);
    }
    printf("\nPessoa nao encontrada!\n");
}

void RemoverPessoa(void **pBuffer) {
    if (((int *)(*pBuffer))[1] == 0) {
        printf("\nAgenda vazia!\n");
        return;
    }

    char *nomeBusca = (char *)(*pBuffer) + TAMANHO_CONTROLES;
    printf("Digite um nome para remover: "); 
    fgets(nomeBusca, 50, stdin);

    void *ponteiroPessoa = (*pBuffer) + INICIO_DADOS;

    //[0]=tamanhoNome, [1]=tamanhoEmail, [2]=bytesDestaPessoa, [3]=tamanhorestante
    int *pInteiroTemp = (int *)malloc(sizeof(int) * 4); 

    for (((int *)(*pBuffer))[2] = 0; ((int *)(*pBuffer))[2] < ((int *)(*pBuffer))[1]; ((int *)(*pBuffer))[2]++) {
        
        pInteiroTemp[0] = *(int *)(ponteiroPessoa + sizeof(int));
        pInteiroTemp[1] = *(int *)(ponteiroPessoa + sizeof(int) * 2);
        pInteiroTemp[2] = (sizeof(int) * 3) + pInteiroTemp[0] + pInteiroTemp[1];

        if (strcmp(nomeBusca, (char *)(ponteiroPessoa + sizeof(int) * 3)) == 0) {
            
            void *proximaPessoa = ponteiroPessoa + pInteiroTemp[2];
            
            //e calculado quanto resta de memoria apos a pessoa que sera removida
            //para sabermos quanto o memmove deve arrastar
            pInteiroTemp[3] = ((int *)(*pBuffer))[3] - (proximaPessoa - (*pBuffer));
            
            if (pInteiroTemp[3] > 0) {
                memmove(ponteiroPessoa, proximaPessoa, pInteiroTemp[3]);
            }

            //o cabecalho e atualizado ANTES de diminuir o tamanho do buffer real
            ((int *)(*pBuffer))[1] -= 1; //reduz qtd pessoas
            ((int *)(*pBuffer))[3] -= pInteiroTemp[2]; //reduz tamanho total

            *pBuffer = realloc(*pBuffer, ((int *)(*pBuffer))[3]);
            printf("\nRemovido com sucesso!\n");
            free(pInteiroTemp);
            return;
        }
        ponteiroPessoa += pInteiroTemp[2];
    }
    printf("\nNome nao encontrado!\n");
}



int main() {
    void *pBuffer = malloc(INICIO_DADOS);
    
    if (!pBuffer) {
        printf("Erro de alocacao de memoria.\n");
        return 1;
    }

    // Inicializando as variaveis de controle dentro do buffer
    ((int *)pBuffer)[0] = 0;             // Menu
    ((int *)pBuffer)[1] = 0;             // Quantidade de pessoas
    ((int *)pBuffer)[2] = 0;             // Contador do loop
    ((int *)pBuffer)[3] = INICIO_DADOS;  // Tamanho total alocado

    while (((int *)pBuffer)[0] != 5) {
        printf("\n--- Agenda dinamica---");
        printf("\n1 - Adicionar\n2 - Remover\n3 - Buscar\n4 - Listar\n5 - Sair\nOpcao: ");
        
        // a opçao escolhida esta no indice [0] do buffer
        scanf("%d", &((int *)pBuffer)[0]);
        getchar(); // Limpa o '\n' do teclado

        switch (((int *)pBuffer)[0]) {
            case 1:
                AdicionarPessoa(&pBuffer);
                break;
            case 2:
                RemoverPessoa(&pBuffer);
                break;
            case 3:
                BuscarPessoa(pBuffer);
                break;
            case 4:
                ListarTodos(pBuffer);
                break;
            case 5:
                printf("Saindo e liberando memoria...\n");
                break;
            default:
                printf("Opcao invalida!\n");
                break;
        }
    }

    free(pBuffer);
    return 0;
}
