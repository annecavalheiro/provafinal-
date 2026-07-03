//agenda sem arquivos

#include <stdio.h>
#include <string.h>

#define MAX_CONTATOS 100

// Enum para representar a situação do contato
typedef enum {
    INATIVO = 0, // Usado para a remoção lógica
    NORMAL,
    FAVORITO,
    BLOQUEADO
} SituacaoContato;

// Struct aninhada para o endereço
typedef struct {
    char rua[50];
    int numero;
    char bairro[50];
    char cidade[50];
} DadosEndereco;

// Struct principal do contato
typedef struct {
    int id;
    char nome[50];
    char telefone[20];
    char email[50];
    DadosEndereco endereco;
    SituacaoContato status;
} Contato;

// --- Protótipos das Funções ---
void cadastrarContato(Contato agenda[], int *contador);
void listarContatos(Contato agenda[], int contador);
void buscarContatoPorId(Contato agenda[], int contador);
void atualizarTelefone(Contato agenda[], int contador);
void removerContato(Contato agenda[], int contador);

int main() {
    Contato agenda[MAX_CONTATOS];
    int contador = 0; // Controla a quantidade de cadastros e ajuda a gerar IDs
    int opcao;

    do {
        printf("\n===== AGENDA =====\n");
        printf("1 - Cadastrar contato\n");
        printf("2 - Listar contatos\n");
        printf("3 - Buscar contato por ID\n");
        printf("4 - Atualizar telefone\n");
        printf("5 - Remover contato\n");
        printf("0 - Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);
        getchar(); // Limpa o buffer do teclado

        switch (opcao) {
            case 1:
                cadastrarContato(agenda, &contador);
                break;
            case 2:
                listarContatos(agenda, contador);
                break;
            case 3:
                buscarContatoPorId(agenda, contador);
                break;
            case 4:
                atualizarTelefone(agenda, contador);
                break;
            case 5:
                removerContato(agenda, contador);
                break;
            case 0:
                printf("Encerrando o programa...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
        }
    } while (opcao != 0);

    return 0;
}

// --- Implementação das Funções ---

void cadastrarContato(Contato agenda[], int *contador) {
    if (*contador >= MAX_CONTATOS) {
        printf("Agenda cheia! Nao e possivel cadastrar mais contatos.\n");
        return;
    }

    int pos = *contador;
    agenda[pos].id = pos + 1; // ID gerado automaticamente com base na posição
    agenda[pos].status = NORMAL; // Definido como normal por padrão

    printf("\n--- Cadastrar Contato (ID: %d) ---\n", agenda[pos].id);
    
    printf("Nome: ");
    fgets(agenda[pos].nome, sizeof(agenda[pos].nome), stdin);
    strtok(agenda[pos].nome, "\n"); // Remove o \n do final

    printf("Telefone: ");
    fgets(agenda[pos].telefone, sizeof(agenda[pos].telefone), stdin);
    strtok(agenda[pos].telefone, "\n");

    printf("E-mail: ");
    fgets(agenda[pos].email, sizeof(agenda[pos].email), stdin);
    strtok(agenda[pos].email, "\n");

    printf("\n--- Endereco ---\n");
    printf("Rua: ");
    fgets(agenda[pos].endereco.rua, sizeof(agenda[pos].endereco.rua), stdin);
    strtok(agenda[pos].endereco.rua, "\n");

    printf("Numero: ");
    scanf("%d", &agenda[pos].endereco.numero);
    getchar(); // Limpa o buffer

    printf("Bairro: ");
    fgets(agenda[pos].endereco.bairro, sizeof(agenda[pos].endereco.bairro), stdin);
    strtok(agenda[pos].endereco.bairro, "\n");

    printf("Cidade: ");
    fgets(agenda[pos].endereco.cidade, sizeof(agenda[pos].endereco.cidade), stdin);
    strtok(agenda[pos].endereco.cidade, "\n");

    (*contador)++;
    printf("Contato cadastrado com sucesso!\n");
}

void listarContatos(Contato agenda[], int contador) {
    printf("\n--- Lista de Contatos ---\n");
    int encontrou = 0;

    for (int i = 0; i < contador; i++) {
        if (agenda[i].status != INATIVO) {
            printf("ID: %d | Nome: %s | Telefone: %s\n", agenda[i].id, agenda[i].nome, agenda[i].telefone);
            encontrou = 1;
        }
    }

    if (!encontrou) {
        printf("Nenhum contato cadastrado ou ativo na agenda.\n");
    }
}

void buscarContatoPorId(Contato agenda[], int contador) {
    int idBusca;
    printf("\nDigite o ID do contato que deseja buscar: ");
    scanf("%d", &idBusca);

    int encontrou = 0;

    for (int i = 0; i < contador; i++) {
        if (agenda[i].id == idBusca && agenda[i].status != INATIVO) {
            printf("\n--- Dados do Contato ---\n");
            printf("ID: %d\n", agenda[i].id);
            printf("Nome: %s\n", agenda[i].nome);
            printf("Telefone: %s\n", agenda[i].email);
            printf("E-mail: %s\n", agenda[i].email);
            printf("Endereco: %s, %d - %s (%s)\n", 
                   agenda[i].endereco.rua, agenda[i].endereco.numero, 
                   agenda[i].endereco.bairro, agenda[i].endereco.cidade);
            printf("-------------------------\n");
            encontrou = 1;
            break;
        }
    }

    if (!encontrou) {
        printf("Contato com ID %d nao encontrado ou inativo.\n", idBusca);
    }
}

void atualizarTelefone(Contato agenda[], int contador) {
    int idBusca;
    printf("\nDigite o ID do contato que deseja atualizar o telefone: ");
    scanf("%d", &idBusca);
    getchar(); // Limpa o buffer

    int encontrou = 0;

    for (int i = 0; i < contador; i++) {
        if (agenda[i].id == idBusca && agenda[i].status != INATIVO) {
            printf("Novo telefone para %s: ", agenda[i].nome);
            fgets(agenda[i].telefone, sizeof(agenda[i].telefone), stdin);
            strtok(agenda[i].telefone, "\n");
            
            printf("Telefone atualizado com sucesso!\n");
            encontrou = 1;
            break;
        }
    }

    if (!encontrou) {
        printf("Contato com ID %d nao encontrado.\n", idBusca);
    }
}

void removerContato(Contato agenda[], int contador) {
    int idBusca;
    printf("\nDigite o ID do contato que deseja remover: ");
    scanf("%d", &idBusca);

    int encontrou = 0;

    for (int i = 0; i < contador; i++) {
        if (agenda[i].id == idBusca && agenda[i].status != INATIVO) {
            agenda[i].status = INATIVO; // Remoção lógica
            printf("Contato removido logicamente com sucesso!\n");
            encontrou = 1;
            break;
        }
    }

    if (!encontrou) {
        printf("Contato com ID %d nao encontrado ou ja inativo.\n", idBusca);
    }
} 