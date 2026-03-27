/*menu: 1 add nome
        2 remove nome
        3 lista
        4 sair
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Nome{
    char snome[200];
    struct Nome *ponteiro; 
} Nome; 

Nome* criarNome() {
    Nome *nova = (Nome*)malloc(sizeof(Nome));

    printf("Nome: ");
    fgets(nova->snome, 100, stdin);
    nova->snome[strcspn(nova->snome, "\n")] = '\0';

    nova->ponteiro = NULL;

    return nova;
}

void addNome(Nome **lista) {
    Nome *nova = criarNome();
    nova->ponteiro = *lista;
    *lista = nova;
}
/*
void removeNome(**lista){

    printf("Digite o nome que voce deseja excluir: ");

}
*/
void listaNome(Nome *lista){
    while (lista != NULL) {
        printf("\nNome: %s", lista->snome);
        lista = lista->ponteiro;
    }
}
void menu(){
    printf("----MENU----\n");
    printf("1. Adicionar nome\n");
    printf("2. Remover nome\n");
    printf("3. Listar nomes\n");
    printf("4. Sair\n");
    printf("Digite uma opcao: ");
}

int main(){

    int opcao; 
    Nome *lista = NULL;
    
    do {
        menu();
        scanf("%d", &opcao);
        
        switch(opcao){
        case 1: 
            addNome(&lista);
            break;
        /*case 2: 
            removeNome(&lista);
            break;*/
        case 3: 
            listaNome(lista);
            break;
        default:
            printf("Opcao invalida!");
        }
    }
    while(opcao != 4);

    printf("Programa encerrado!");

    return 0;
}