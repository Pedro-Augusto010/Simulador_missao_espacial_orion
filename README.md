# 🛸 Sistema de Telemetria e Monitoramento — Missão Estelar Orion

Este projeto documenta o desenvolvimento do software de gerenciamento e telemetria da **Missão Estelar Orion**, uma aplicação interativa desenvolvida em **Linguagem C**. A iniciativa surgiu da necessidade de monitorar, em tempo real, os insumos vitais de sobrevivência a bordo de uma nave espacial enviada à Lua, substituindo estimativas manuais por um controle de dados preciso, capaz de emitir alertas de crise e determinar o desfecho da expedição.

O desenvolvimento abrangeu desde a implementação de estruturas de dados multidimensionais em memória para o registro do consumo diário de recursos até a criação de um motor de decisão narrativa dinâmico, que altera a história final com base na eficiência da gestão da tripulação.

---

## 🎯 Contexto e Objetivos

No ano de 2045, em meio a uma crise energética global, a NASA envia a nave **Orion** com uma equipe de **5 astronautas** para investigar minerais raros na superfície lunar. Para garantir a sobrevivência da equipe durante a jornada de **7 dias**, o operador precisa controlar rigidamente o uso de Oxigênio, Água e Energia.

Para resolver essa dor de monitoramento operacional, o projeto foi estruturado para entregar:
- **Centralização de Dados da Tripulação:** Cadastro unificado dos astronautas integrantes da expedição diretamente via terminal.
- **Matriz de Consumo Telemétrico:** Registro contínuo do consumo diário dos recursos vitais em uma estrutura bidimensional.
- **Análise Estatística e Contingência:** Processamento de médias, identificação de picos de consumo e emissão automática de alertas de esgotamento.

---

## 📋 Funcionalidades do Sistema

A partir da dinâmica operacional da missão espacial, foram consolidadas as principais entregas do software:

### **Recursos Operacionais**
1. Cadastrar e armazenar o nome dos 5 tripulantes a bordo da nave.
2. Registrar o consumo diário de Oxigênio, Água e Energia ao longo dos 7 dias de missão.
3. Exibir a matriz de consumo organizada e calcular médias diárias e totais acumulados.
4. Identificar o dia de maior pico de consumo para cada recurso individual.
5. Avaliar o estouro de cotas globais e gerar um relatório final com narrativa dinâmica.

### **Indicadores Monitorados**
* **Oxigênio ($\text{Kg}$):** Limite crítico diário de $135\text{ Kg}$ (Teto global de $945\text{ Kg}$).
* **Água ($\text{L}$):** Limite crítico diário de $85\text{ L}$ (Teto global de $595\text{ L}$).
* **Energia ($\text{kWh}$):** Limite crítico diário de $320\text{ kWh}$ (Teto global de $2.240\text{ kWh}$).
* **Relatório Narrativo:** 8 desfechos diferentes adaptados ao comportamento da equipe.

---

## 📖 O Motor de Narrativa Dinâmica

O grande diferencial interativo do sistema é o seu gerador de histórias adaptativo. Em vez de apenas apresentar dados numéricos estáticos no relatório final, o software processa os totais acumulados ao término dos 7 dias e aciona ramificações narrativas únicas baseadas no comportamento de uso dos recursos:

- **Ramificações Contingenciais:** O algoritmo mapeia quais combinações de insumos ultrapassaram o teto global e gera desfechos temáticos (ex.: crises por excesso de treinos físicos, consumo desmedido de café ou maratonas de jogos eletrônicos).
- **Condição de Vitória:** O final bem-sucedido — onde a equipe retorna à Terra e salva o planeta da crise energética — só é desbloqueado se todos os 3 recursos permanecerem estritamente dentro da margem de segurança.
- **Imersão no Terminal:** A exibição do texto final utiliza um algoritmo de animação no estilo *typewriter* (digitação caractere por caractere com atrasos controlados em milissegundos), elevando a imersão do usuário durante a leitura do relatório.

---

## 💻 Arquitetura e Lógica do Programa

Para suportar o fluxo de dados e a interface da aplicação, a estrutura lógica foi organizada nos seguintes pilares:

- **Controle de Estados e Menu:** O programa utiliza um laço principal com estrutura de seleção (`switch-case`) para navegar entre o cadastro, inserção de matriz, cálculo de estatísticas e emissão de relatórios.
- **Tratamento de Fluxo de Entrada:** Implementação de rotinas para higienização do buffer de entrada (`stdin`), prevenindo falhas de leitura ou saltos no terminal durante o uso de comandos de texto e número.
- **Processamento Estatístico de Picos:** Algoritmos de varredura que percorrem a matriz telemétrica para extrair os maiores valores registrados por coluna e mapear em qual dia ocorreram os picos operacionais.
- **Motor de Decisão Narrativa:** Sistema condicional que calcula o balanço final dos 7 dias e direciona a exibição para diferentes ramificações da história da missão.

---

## 🛠️ O Ciclo de Desenvolvimento (Linguagem C)

Toda a arquitetura do programa foi desenhada em **Linguagem C**, estruturada nas seguintes etapas de engenharia de software:

1. **Estrutura de Dados em Memória:** Organização do estado operacional da nave através de matrizes multidimensionais (`float consumo[7][3]`) e vetores de texto (`char tripulantes[5][50]`).
2. **Modularização e Ponteiros:** Separação do código em funções de responsabilidade única e uso de ponteiros (passagem por referência) para atualização e busca de picos de uso na memória.
3. **Portabilidade e UX Multiplataforma:** Uso de diretivas de pré-processador (`#ifdef _WIN32`) para compatibilidade de funções de tempo em qualquer sistema operacional, com animações de carregamento e efeito de digitação no terminal.

---

## 📁 Estrutura do Repositório

```text
.
├── src/                  # Código-fonte principal do sistema
│   └── main.c            # Implementação completa do programa em C
└── README.md             # Documentação principal do repositório
