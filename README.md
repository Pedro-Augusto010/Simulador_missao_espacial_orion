# 🛸 Monitoramento e Telemetria Espacial — Missão Estelar Orion

Este projeto documenta o processo completo de engenharia e desenvolvimento do software de telemetria da **Missão Estelar Orion**, um sistema de suporte a missões espaciais de exploração lunar fictícias. A iniciativa surgiu da necessidade de monitorar, em tempo real, a alocação e o consumo de insumos vitais de sobrevivência a bordo de uma nave espacial, substituindo estimativas manuais por um sistema de processamento de dados robusto, capaz de prevenir crises catastróficas e garantir o cumprimento dos objetivos científicos da missão.

O desenvolvimento abrangeu desde a fase de imersão no cenário operacional da NASA até a modelagem estruturada em C, incluindo o mapeamento de variáveis telemétricas, implementação de regras de restrição de recursos e a criação de um motor de decisão narrativa baseado em dados.

---

## 🎯 Contexto e Objetivos

No ano de 2045, a humanidade enfrenta uma grave crise energética. A nave **Orion** foi enviada à Lua com uma equipe de **5 astronautas** para investigar minerais raros capazes de gerar energia limpa. Para garantir a sobrevivência da tripulação durante a jornada de **7 dias**, o operador do sistema precisa gerenciar rigidamente as cotas diárias de recursos.

Para resolver essa dor de monitoramento operacional, o projeto foi estruturado para entregar:
- **Centralização de Dados Cadastrais:** Cadastro unificado do corpo de astronautas integrantes da expedição.
- **Matriz de Consumo Telemétrico:** Registro contínuo do consumo diário de Oxigênio, Água e Energia em uma estrutura bidimensional.
- **Análise Estatística e Contingência:** Processamento de médias, identificação de picos de consumo e emissão automática de alertas críticos de esgotamento.

---

## 📋 Levantamento de Requisitos e Dados

A partir das especificações do protocolo de navegação da missão, foram consolidados os requisitos essenciais do sistema:

### **Requisitos Funcionais**
1. Manter o cadastro dos 5 tripulantes a bordo da nave espacial.
2. Registrar diariamente o consumo dos 3 recursos vitais em uma matriz telemétrica ($7 \times 3$).
3. Calcular estatísticas acumuladas (totais e médias diárias de cada insumo).
4. Detectar o dia exato de maior pico de consumo por variável.
5. Avaliar o estouro de cotas globais e gerar relatórios condicionais sobre o desfecho da missão.

### **Dados Mapeados por Entidade**
* **Tripulante:** Nome completo do astronauta e código identificador.
* **Recurso Vital:** Tipo (Oxigênio, Água, Energia), Unidade de medida ($\text{Kg}$, $\text{L}$, $\text{kWh}$), Cota limite diária.
* **Telemetria:** Dia do registro ($1 \text{ a } 7$), Quantidade consumida por recurso.

---

## 📐 Regras de Negócio Traduzidas para o Código

As restrições operacionais do ambiente espacial exigiram a implementação das seguintes regras diretas na lógica do sistema:

- **Teto Crítico Diário:** O sistema dispara alertas no terminal caso o consumo individual diário ultrapasse os limites de **$135\text{ Kg}$ para Oxigênio**, **$85\text{ L}$ para Água** ou **$320\text{ kWh}$ para Energia**.
- **Cota Acumulada de Sobrevivência:** O limite global seguro para os 7 dias é de $945\text{ Kg}$ de Oxigênio, $595\text{ L}$ de Água e $2.240\text{ kWh}$ de Energia.
- **Matriz de Falha Narrativa:** O algoritmo avalia os estouros das cotas globais e seleciona um dos **8 desfechos possíveis** para a missão (desde o sucesso absoluto até fatalidades causadas por vício em café ou maratona de jogos).
- **Integridade da Entrada de Dados:** O sistema deve tratar resíduos de memória do teclado (`stdin`) para impedir saltos no fluxo de navegação do menu.

---

## 🛠️ O Ciclo de Engenharia de Software

Toda a arquitetura do programa foi desenhada em **Linguagem C**, dividida estritamente nas três fases clássicas do desenvolvimento de baixo nível:

1. **Estrutura de Dados em Memória:** Alocação de matrizes multidimensionais (`float consumo[7][3]`) e vetores de caracteres (`char tripulantes[5][50]`) para armazenar o estado operacional da nave sem dependência de banco de dados externo.
2. **Modularização e Ponteiros:** Separação da lógica em funções isoladas de responsabilidade única e uso de ponteiros (passagem por referência) para busca e atualização eficiente de valores máximos na memória.
3. **Portabilidade e UX Multiplataforma:** Implementação de diretivas de pré-processador (`#ifdef _WIN32`) para mapeamento dinâmico de bibliotecas de tempo no Windows e Unix, aliadas a efeitos de carregamento e interface estilo *typewriter*.

---

## 📁 Estrutura do Repositório

```text
.
├── docs/                 # Documentação detalhada dos requisitos, tabela de cotas e matriz narrativa
├── src/                  # Código-fonte principal da aplicação em C
│   └── main.c            # Implementação completa do sistema da Missão Orion
└── README.md             # Documentação principal do repositório
