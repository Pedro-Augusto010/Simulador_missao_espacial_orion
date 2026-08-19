
#include <stdio.h>
#include <string.h>
#include <windows.h>


// Valores padrões que são usados ao longo do código. Foram aqui definidos para evitar erros e repetição no código.
#define DIAS 7
#define RECURSOS 3
#define TRIPULANTES 5
#define TAM_NOME 50

//--- FUNÇÕES DO CÓDIGO ---

void cadastrarTripulantes(char tripulantes[TRIPULANTES][TAM_NOME]) {
    int i;

    for (i = 0; i < TRIPULANTES; i++) {
        printf("Digite o nome do tripulante %d: ", i + 1);
        fgets(tripulantes[i], TAM_NOME, stdin);
        tripulantes[i][strcspn(tripulantes[i], "\n")] = '\0';
    }
}

void registrarConsumo(float consumo[DIAS][RECURSOS]) {
    int dia;

    for (dia = 0; dia < DIAS; dia++) {
        printf("\nDia %d\n", dia + 1);

        printf("Oxigenio(Kg): ");
        scanf("%f", &consumo[dia][0]);

        printf("Agua(L): ");
        scanf("%f", &consumo[dia][1]);

        printf("Energia(kWh): ");
        scanf("%f", &consumo[dia][2]);
    }
}

void exibirConsumo(float consumo[DIAS][RECURSOS]) {
    int dia;

    printf("\nMATRIZ DE CONSUMO\n");
    printf("Dia\tOxigenio(Kg)\tAgua(L)\tEnergia(kWh)\n");

    for (dia = 0; dia < DIAS; dia++) {
        printf("%d\t%.2f\t\t%.2f\t%.2f\n",
               dia + 1,
               consumo[dia][0],
               consumo[dia][1],
               consumo[dia][2]);
    }
}

float calcularTotalRecurso(float consumo[DIAS][RECURSOS], int recurso) {
    int dia;
    float total = 0;

    for (dia = 0; dia < DIAS; dia++) {
        total += consumo[dia][recurso];
    }

    return total;
}

float calcularMediaRecurso(float consumo[DIAS][RECURSOS], int recurso) {
    return calcularTotalRecurso(consumo, recurso) / DIAS;
}

void verificarAlertas(float consumo[DIAS][RECURSOS]) {
    int dia;
    int encontrouAlerta = 0;

    for (dia = 0; dia < DIAS; dia++) {

        if (consumo[dia][0] > 135 ||
            consumo[dia][1] > 85 ||
            consumo[dia][2] > 320) {

            encontrouAlerta = 1;

            printf("\nALERTA NO DIA %d:\n", dia + 1);

            if (consumo[dia][0] > 135)
                printf("Consumo de oxigenio acima do limite de 135 Kg.\n");

            if (consumo[dia][1] > 85)
                printf("Consumo de agua acima do limite de 85 L.\n");

            if (consumo[dia][2] > 320)
                printf("Consumo de energia acima do limite de 320 kWh.\n");
        }
    }

    if (!encontrouAlerta) {
        printf("\nNenhum alerta critico foi encontrado na missao.\n");
    }
}

//Função para comparar os totais dos recursos e identificar qual teve o maior consumo acumulado na missão.
void atualizarMaiorValor(float valor, float *maior) {
    if (valor > *maior) {
        *maior = valor;
    }
}

//Função para encontrar o dia de maior consumo de cada um dos recursos.
int encontrarDiaMaiorConsumo(float consumo[DIAS][RECURSOS], int recurso) {
    int diaMaior = 0;
    float maior = consumo[0][recurso];

    for (int dia = 1; dia < DIAS; dia++) {
        if (consumo[dia][recurso] > maior) {
            maior = consumo[dia][recurso];
            diaMaior = dia;
        }
    }

    return diaMaior;
}

float encontrarMaiorConsumoMissao(float consumo[DIAS][RECURSOS]) {
    float maior = consumo[0][0];

    for (int dia = 0; dia < DIAS; dia++) {
        for (int recurso = 0; recurso < RECURSOS; recurso++) {
            atualizarMaiorValor(consumo[dia][recurso], &maior);
        }
    }

    return maior;
}

void gerarRelatorio(float consumo[DIAS][RECURSOS]) {
    printf("\n===== RELATORIO FINAL =====\n");

    printf("Total de Oxigenio: %.2f Kg\n",
           calcularTotalRecurso(consumo, 0));

    printf("Total de Agua: %.2f L\n",
           calcularTotalRecurso(consumo, 1));

    printf("Total de Energia: %.2f kWh\n",
           calcularTotalRecurso(consumo, 2));

    printf("\n=== Medias Diarias ===\n");

    printf("\nMedia diaria de Oxigenio: %.2f Kg\n",
           calcularMediaRecurso(consumo, 0));

    printf("Media diaria de Agua: %.2f L\n",
           calcularMediaRecurso(consumo, 1));

    printf("Media diaria de Energia: %.2f kWh\n",
           calcularMediaRecurso(consumo, 2));

    printf("\n=== Dias de maior consumo ===\n");

    printf("\nDia de maior consumo de Oxigenio: %d\n",
       encontrarDiaMaiorConsumo(consumo, 0) + 1);

    printf("Dia de maior consumo de Agua: %d\n",
           encontrarDiaMaiorConsumo(consumo, 1) + 1);

    printf("Dia de maior consumo de Energia: %d\n",
           encontrarDiaMaiorConsumo(consumo, 2) + 1);

    printf("\n=== Maior consumo registrado ===\n");

    printf("\nMaior consumo registrado durante a missao: %.2f\n",
       encontrarMaiorConsumoMissao(consumo));

    printf("\n=== Alertas registrados ===\n");

    verificarAlertas(consumo);
}

// Função para criar o efeito de carregar o sistema da Missão Orion. Esta função será chamada antes de carregar o menu
// para o switch case.
void carregandoSistema() {
    printf("\nIniciando processamento da nave");

    for (int i = 0; i < 5; i++) {
        printf(".");
        fflush(stdout);


        Sleep(1000);

    }

    printf("\nSistema atualizado com sucesso!\n");

    Sleep(1500);

}

// Função para criar o efeito de digitação no case 8 (Ler a história da missão).
void digitarTexto(const char *texto) {
    int i = 0;

    while (texto[i] != '\0') {
        printf("%c", texto[i]);
        fflush(stdout);

        Sleep(3);

        i++;
    }
}

// Função para criar a historia que sera exibida após escolher a case 8 (Ler a história da missão).
void contarHistoria(char tripulantes[TRIPULANTES][TAM_NOME],
float consumo[DIAS][RECURSOS]) {

float oxigenio = calcularTotalRecurso(consumo, 0);
float agua = calcularTotalRecurso(consumo, 1);
float energia = calcularTotalRecurso(consumo, 2);

int falhaOxigenio = (oxigenio > 135 * DIAS);
int falhaAgua = (agua > 85 * DIAS);
int falhaEnergia = (energia > 320 * DIAS);

char introducao[2000];

sprintf(introducao,
    "\n========== HISTORIA DA MISSAO ORION ==========\n\n"
    "Os astronautas %s, %s, %s, %s e %s foram escolhidos pela NASA "
    "para participar da Missao Espacial Orion. A humanidade vivia "
    "uma grave crise energetica e corria o risco de mergulhar em "
    "uma guerra global pela disputa dos ultimos recursos disponiveis "
    "na Terra. A missao tinha como objetivo viajar ate a Lua para "
    "investigar minerais raros capazes de produzir uma nova "
    "fonte de energia e salvar a civilizacao humana.\n\n",
    tripulantes[0],
    tripulantes[1],
    tripulantes[2],
    tripulantes[3],
    tripulantes[4]);

digitarTexto(introducao);

if (!falhaOxigenio && !falhaAgua && !falhaEnergia) {

    digitarTexto(
    "A tripulacao administrou todos os recursos com extrema "
    "responsabilidade durante a viagem.\n\n"

    "Depois de semanas de pesquisa na superficie lunar, os "
    "astronautas descobriram um mineral com capacidade de gerar "
    "energia limpa em quantidades jamais vistas.\n\n"

    "Ao retornar para a Terra, a descoberta revolucionou a ciencia "
    "e encerrou a crise energetica mundial. A Missao Orion evitou uma "
    "guerra devastadora e tornou-se um dos maiores "
    "sucessos da historia.\n");
}

else if (falhaOxigenio && !falhaAgua && !falhaEnergia) {

    digitarTexto(
    "Um dos membros da tripulacao era extremamente vaidoso com "
    "o corpo e nao quis abandonar sua rotina diaria de "
    "calistenia. \n\n"

    "Com o passar dos dias, devido as atividades intensas do"
    "tripulante vaidoso o consumo de oxigenio aumentou ate "
    "atingir niveis criticos.\n\n"

    "Quando a tripulacao percebeu a gravidade da situacao, os "
    "reservatorios estavam praticamente vazios. Sem oxigenio "
    "suficiente para retornar a Terra, a equipe nao resistiu e a "
    "missao terminou em tragedia.\n");
}

else if (!falhaOxigenio && falhaAgua && !falhaEnergia) {

    digitarTexto(
    "Devido ao vicio em cafeina dos membros da tripulacao, estes passaram a "
    "utilizar a agua em quantidades excessivas para fazer cafe, de modo que"
    "varias garrafas da bebida eram feitas todos os dias .\n\n"

    "O desperdicio acumulado levou os reservatorios a niveis "
    "criticos. Logo surgiram conflitos internos sobre como dividir "
    "o restante da agua.\n\n"

    "A desidratacao comprometeu a capacidade da equipe de operar os "
    "sistemas da nave. Sem condicoes de concluir a viagem, a Orion "
    "perdeu sua rota e desapareceu no espaco.\n");
}

else if (!falhaOxigenio && !falhaAgua && falhaEnergia) {

    digitarTexto(
    "Os tripulantes nao conseguiram se conter e ficaram por "
    "tempo demais assistindo aos jogos da Copa do Mundo "
    "e consumiram muito mais energia do que o planejado.\n\n"

    "Pouco antes da volta para casa, os sistemas principais da nave "
    "comecaram a desligar.\n\n"

    "Sem energia para alimentar os motores e os sistemas de "
    "navegacao, a Orion ficou perdida no espaco e a missao "
    "fracassou.\n");
}

else if (falhaOxigenio && falhaAgua && !falhaEnergia) {

    digitarTexto(
    "O consumo excessivo de oxigenio e agua criou uma crise sem "
    "precedentes a bordo.\n\n"

    "A tripulacao precisou interromper os experimentos para tentar "
    "sobreviver. Apesar dos esforcos, os recursos acabaram antes "
    "do previsto.\n\n"

    "Sem condicoes de concluir a jornada, a Missao Orion foi "
    "abandonada e jamais retornou a Terra.\n");
}

else if (falhaOxigenio && !falhaAgua && falhaEnergia) {

    digitarTexto(
    "As atividades na superficie lunar exigiram esforco intenso e "
    "consumiram grandes quantidades de oxigenio.\n\n"

    "Ao mesmo tempo, diversos equipamentos permaneceram ligados por "
    "tempo excessivo, drenando rapidamente as reservas de energia.\n\n"

    "Quando finalmente encontraram um mineral promissor, os "
    "astronautas descobriram que nao possuíam recursos suficientes "
    "para retornar.\n\n"

    "Sem energia para os motores e com pouco oxigenio restante, a "
    "tripulacao ficou presa no espaco. Os dados da descoberta que "
    "poderiam salvar a humanidade jamais foram enviados para a "
    "Terra.\n");
}

else if (!falhaOxigenio && falhaAgua && falhaEnergia) {

    digitarTexto(
    "A administracao da agua e da energia saiu completamente do "
    "controle durante a missao.\n\n"

    "Grandes quantidades de agua foram desperdicadas e diversos "
    "equipamentos consumiram energia muito acima dos limites "
    "planejados.\n\n"

    "Quando os recursos chegaram a niveis criticos, os sistemas da "
    "nave comecaram a falhar e a tripulacao entrou em desespero.\n\n"

    "Sem agua suficiente para sobreviver e sem energia para manter "
    "a nave operacional, a Orion perdeu sua rota e desapareceu "
    "nas profundezas do espaco.\n");
}

else {

    digitarTexto(
    "A administracao dos recursos foi um desastre completo.\n\n"

    "Oxigenio, agua e energia foram consumidos muito acima dos "
    "limites previstos pela NASA.\n\n"

    "Diversos avisos dos sistemas da nave foram ignorados e os "
    "suprimentos essenciais acabaram simultaneamente.\n\n"

    "Sem oxigenio para respirar, sem agua para sobreviver e sem "
    "energia para operar a nave, a tripulacao nao teve qualquer "
    "chance de concluir a missao.\n\n"

    "A humanidade perdeu sua melhor oportunidade de resolver a "
    "crise energetica e a Missao Orion entrou para a historia como "
    "um grande fracasso.\n");
}

}

//--- MAIN ---

int main() {
    char tripulantes[TRIPULANTES][TAM_NOME];
    float consumo[DIAS][RECURSOS] = {0};

    int opcao;

    do {
        printf("\n===== SISTEMA DA MISSAO ESTELAR ORION =====\n");
        printf("1. Cadastrar tripulantes\n");
        printf("2. Registrar consumo dos recursos\n");
        printf("3. Exibir matriz de consumo\n");
        printf("4. Exibir consumo total de cada recurso\n");
        printf("5. Exibir consumo medio diario\n");
        printf("6. Verificar alertas da missao\n");
        printf("7. Gerar relatorio final\n");
        printf("8. Ler a historia da missao\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");

        scanf("%d", &opcao);
        getchar();

        switch (opcao) {
            case 1:
                cadastrarTripulantes(tripulantes);
                break;

            case 2:
                registrarConsumo(consumo);
                break;

            case 3:
                exibirConsumo(consumo);
                break;

            case 4:
                printf("\nTotal de oxigenio(Kg): %.2f\n",
                       calcularTotalRecurso(consumo, 0));

                printf("Total de agua(L): %.2f\n",
                       calcularTotalRecurso(consumo, 1));

                printf("Total de energia(kWh): %.2f\n",
                       calcularTotalRecurso(consumo, 2));
                break;

            case 5:
                printf("\nMedia diaria de oxigenio(Kg): %.2f\n",
                       calcularMediaRecurso(consumo, 0));

                printf("Media diaria de agua(L): %.2f\n",
                       calcularMediaRecurso(consumo, 1));

                printf("Media diaria de energia(kWh): %.2f\n",
                       calcularMediaRecurso(consumo, 2));
                break;

            case 6:
                verificarAlertas(consumo);
                break;

            case 7:
                gerarRelatorio(consumo);
                break;

            case 8:
                contarHistoria(tripulantes, consumo);
                break;

            case 0:
                printf("Encerrando o sistema...\n");
                break;

            default:
                printf("Opcao invalida. Tente novamente.\n");
        }

        // Pausa antes de redesenhar o menu.
        carregandoSistema();

    } while (opcao != 0);

    return 0;
}
