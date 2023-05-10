#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Freezer {
    char nome[10];
    float capacidade;
    float economia;
    int garantia;
    float temp_minima;
};

void criar_freezer() {
    struct Freezer novo;
    printf("Digite o nome do freezer: ");
    scanf("%s", novo.nome);
    printf("Digite a capacidade do freezer em litros: ");
    scanf("%f", &novo.capacidade);
    printf("Digite a economia do freezer em kWh/mes: ");
    scanf("%f", &novo.economia);
    printf("Digite a duracao da garantia em meses: ");
    scanf("%d", &novo.garantia);
    printf("Digite a temperatura minima suportada pelo freezer: ");
    scanf("%f", &novo.temp_minima);
    
    FILE *arquivo;
    arquivo = fopen("freezers.dat", "ab");
    fwrite(&novo, sizeof(struct Freezer), 1, arquivo);
    fclose(arquivo);
    
    printf("Freezer cadastrado com sucesso!\n");
}

void exibir_freezer() {
    struct Freezer freezer;
    FILE *arquivo;
    arquivo = fopen("freezers.dat", "rb");
    while (fread(&freezer, sizeof(struct Freezer), 1, arquivo)) {
		printf("---------------\n");
        printf("Nome: %s\n", freezer.nome);
        printf("Capacidade: %.2f litros\n", freezer.capacidade);
        printf("Economia: %.2f kWh/mes\n", freezer.economia);
        printf("Garantia: %d meses\n", freezer.garantia);
        printf("Temperatura minima: %.2f C\n", freezer.temp_minima);
        printf("---------------\n");
    }
    fclose(arquivo);
}

void editar_freezer() {
    char nome[10];
    printf("Digite o nome do freezer que deseja editar: ");
    scanf("%s", nome);
    
    FILE *arquivo;
    arquivo = fopen("freezers.dat", "rb+");
    if (arquivo == NULL) {
        printf("Nao foi possivel abrir o arquivo.\n");
        return;
    }

    struct Freezer freezer;
    int encontrou = 0;
    while (fread(&freezer, sizeof(struct Freezer), 1, arquivo)) {
        if (strcmp(freezer.nome, nome) == 0) {
            encontrou = 1;
            printf("O que deseja editar?\n");
            printf("1 - Nome\n");
            printf("2 - Capacidade\n");
            printf("3 - Economia\n");
            printf("4 - Garantia\n");
            printf("5 - Temperatura minima\n");
            printf("Escolha uma opcao: ");
            int opcao;
            scanf("%d", &opcao);
            switch (opcao) {
                case 1:
                    printf("Digite o novo nome do freezer: ");
                    scanf("%s", freezer.nome);
                    break;
                case 2:
                    printf("Digite a nova capacidade do freezer em litros: ");
                    scanf("%f", &freezer.capacidade);
                    break;
                case 3:
                    printf("Digite a nova economia do freezer em kWh/mes: ");
                    scanf("%f", &freezer.economia);
                    break;
                case 4:
                    printf("Digite a nova duracao da garantia em meses: ");
                    scanf("%d", &freezer.garantia);
                    break;
                case 5:
                    printf("Digite a nova temperatura minima suportada pelo freezer: ");
                    scanf("%f", &freezer.temp_minima);
                    break;
                default:
                    printf("Opcao invalida. Nada foi alterado.\n");
                    break;
            }
            size_t tamanho = sizeof(struct Freezer);
            fseek(arquivo, -tamanho, SEEK_CUR);
            fwrite(&freezer, sizeof(struct Freezer), 1, arquivo);
            printf("Dados do freezer atualizados com sucesso.\n");
            break;
        }
    }
    if (!encontrou) {
        printf("Freezer nao encontrado.\n");
    }
    fclose(arquivo);
}

void listar_caracteristica() {
    int opcao;
    printf("Escolha a caracteristica que deseja listar:\n");
    printf("1 - Capacidade\n");
    printf("2 - Economia\n");
    printf("3 - Garantia\n");
    printf("4 - Temperatura minima\n");
    printf("Escolha uma opcao: \n\n");
    scanf("%d", &opcao);

    struct Freezer freezer;
    FILE *arquivo;
    arquivo = fopen("freezers.dat", "rb");
    if (arquivo == NULL) {
        printf("Nao foi possivel abrir o arquivo.\n");
        return;
    }

    printf("Lista de freezers:\n\n");
    while (fread(&freezer, sizeof(struct Freezer), 1, arquivo)) {
        switch (opcao) {
            case 1:
                printf("\nFreezer %s - Capacidade: %.2f litros\n\n", freezer.nome, freezer.capacidade);
                break;
            case 2:
                printf("Freezer %s - Economia: %.2f kWh/mes\n\n", freezer.nome, freezer.economia);
                break;
            case 3:
                printf("Freezer %s - Garantia: %d meses\n\n", freezer.nome, freezer.garantia);
                break;
            case 4:
                printf("Freezer %s - Temperatura minima: %.2f C\n\n", freezer.nome, freezer.temp_minima);
                break;
            default:
                printf("Opcao invalida.\n");
                break;
        }
    }
    fclose(arquivo);
}

void melhor_capacidade() {
    FILE *arquivo;
    arquivo = fopen("freezers.dat", "rb");
    if (arquivo == NULL) {
        printf("Nao foi possivel abrir o arquivo.\n");
        return;
    }

    struct Freezer freezer;
    struct Freezer melhor_freezer;
    float capacidade_maxima = 0;
    while (fread(&freezer, sizeof(struct Freezer), 1, arquivo)) {
        if (freezer.capacidade > capacidade_maxima) {
            capacidade_maxima = freezer.capacidade;
            melhor_freezer = freezer;
        }
    }

    if (capacidade_maxima == 0) {
        printf("Nenhum freezer cadastrado.\n");
    } else {
        printf("O melhor freezer em capacidade e:\n");
        printf("---------------\n");
        printf("Nome: %s\n", melhor_freezer.nome);
        printf("Capacidade: %.2f litros\n", melhor_freezer.capacidade);
        printf("---------------\n");
    }

    fclose(arquivo);
}

void melhor_garantia() {
    FILE *arquivo;
    arquivo = fopen("freezers.dat", "rb");
    if (arquivo == NULL) {
        printf("Nao foi possivel abrir o arquivo.\n");
        return;
    }

    struct Freezer freezer;
    struct Freezer melhor_freezer;
    int garantia_maxima = 0;
    while (fread(&freezer, sizeof(struct Freezer), 1, arquivo)) {
        if (freezer.garantia > garantia_maxima) {
            garantia_maxima = freezer.garantia;
            melhor_freezer = freezer;
        }
    }

    if (garantia_maxima == 0) {
        printf("Nenhum freezer cadastrado.\n");
    } else {
        printf("O melhor freezer em garantia e:\n");
        printf("---------------\n");
        printf("Nome: %s\n", melhor_freezer.nome);
        printf("Garantia: %d meses\n", melhor_freezer.garantia);
        printf("---------------\n");
    }

    fclose(arquivo);
}

void melhor_economia() {
    FILE *arquivo;
    arquivo = fopen("freezers.dat", "rb");
    if (arquivo == NULL) {
        printf("Nao foi possivel abrir o arquivo.\n");
        return;
    }

    struct Freezer freezer;
    struct Freezer melhor_freezer;
    int economia_maxima = 0;
    while (fread(&freezer, sizeof(struct Freezer), 1, arquivo)) {
        if (freezer.economia > economia_maxima) {
            economia_maxima = freezer.economia;
            melhor_freezer = freezer;
        }
    }

    if (economia_maxima == 0) {
        printf("Nenhum freezer cadastrado.\n");
    } else {
        printf("O melhor freezer em economia e:\n");
        printf("---------------\n");
        printf("Nome: %s\n", melhor_freezer.nome);
        printf("Economia: %.2f KWh/mes\n", melhor_freezer.economia);
        printf("---------------\n");
    }

    fclose(arquivo);
}

void melhor_temp() {
    FILE *arquivo;
    arquivo = fopen("freezers.dat", "rb");
    if (arquivo == NULL) {
        printf("Nao foi possivel abrir o arquivo.\n");
        return;
    }

    struct Freezer freezer;
    struct Freezer melhor_freezer;
    float temp_minima_maxima = 0;
    while (fread(&freezer, sizeof(struct Freezer), 1, arquivo)) {
        if (freezer.temp_minima < temp_minima_maxima) {
            temp_minima_maxima = freezer.temp_minima;
            melhor_freezer = freezer;
        }
    }

    if (temp_minima_maxima == 0) {
        printf("Nenhum freezer cadastrado.\n");
    } else {
        printf("O melhor freezer em Temperatura e:\n");
        printf("---------------\n");
        printf("Nome: %s\n", melhor_freezer.nome);
        printf("Temperatura: %.2f graus C \n", melhor_freezer.temp_minima);
        printf("---------------\n");
    }

    fclose(arquivo);
}

void pesquisar_freezer() {
    char nome[10];
    printf("Digite o nome do freezer que deseja pesquisar: ");
    scanf("%s", nome);

    struct Freezer freezer;
    FILE *arquivo;
    arquivo = fopen("freezers.dat", "rb");
    if (arquivo == NULL) {
        printf("Nao foi possivel abrir o arquivo.\n");
        return;
    }

    int encontrou = 0;
    while (fread(&freezer, sizeof(struct Freezer), 1, arquivo)) {
        if (strcmp(freezer.nome, nome) == 0) {
            encontrou = 1;
            printf("---------------\n");
            printf("Nome: %s\n", freezer.nome);
            printf("Capacidade: %.2f litros\n", freezer.capacidade);
            printf("Economia: %.2f kWh/mes\n", freezer.economia);
            printf("Garantia: %d meses\n", freezer.garantia);
            printf("Temperatura minima: %.2f C\n", freezer.temp_minima);
            printf("---------------\n");
            break;
        }
    }
    if (!encontrou) {
        printf("Freezer nao encontrado.\n");
    }
    fclose(arquivo);
}

int main() {
    int opcao;
    do {
        printf("1 - Cadastrar freezer\n");
        printf("2 - Exibir Levantamento\n");
        printf("3 - Editar dados de um Freezer\n");
        printf("4 - Listar Caracteristica\n");
        printf("5 - Melhor Freezer em capacidade\n");
        printf("6 - Melhor Freezer em garantia\n");
        printf("7 - Melhor Freezer em economia\n");
        printf("8 - Melhor Freezer em temperatura\n");
        printf("9 - Pesquisar Freezer\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                criar_freezer();
                break;
            case 2:
                exibir_freezer();
                break;
            case 3:
                editar_freezer();
                break;
            case 4:
                listar_caracteristica();
                break;
            case 5:
                melhor_capacidade();
                break;
            case 6:
                melhor_garantia();
                break;
            case 7:
                melhor_economia();
                break;
            case 8:
                melhor_temp();
                break;
            case 9:
                pesquisar_freezer();
                break;
            case 0:
                printf("Programa encerrado.\n");
                break;
            default:
                printf("Opção invalida. Tente novamente.\n");
        }
    } while (opcao != 0);
    return 0;
}


