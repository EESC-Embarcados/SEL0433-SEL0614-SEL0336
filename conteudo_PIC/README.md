# Repositório de Projetos com Microcontroladores PIC

Este repositório centraliza projetos, exemplos de código e documentação para o desenvolvimento de sistemas embarcados com microcontroladores da família PIC da Microchip. O foco está na utilização das placas de desenvolvimento **EasyPIC** e **PICGenios**, com exemplos práticos e tutoriais.

## Estrutura do Repositório

O projeto está organizado da seguinte forma para facilitar a navegação:

```
/
|-- datasheets/      # Manuais e folhas de dados de componentes e MCUs.
|-- Kits/
|   |-- EasyPic/     # Projetos e exemplos para a placa EasyPIC.
|   `-- PICGenios/   # Projetos e exemplos para a placa PICGenios.
|       `-- README.md # Guia específico sobre como usar o PICSimLab com esta placa.
`-- README.md        # Este arquivo de visão geral.
```

## Ferramentas de Desenvolvimento e Simulação

Para compilar e testar os projetos deste repositório, utilizamos um conjunto de IDEs (Ambientes de Desenvolvimento Integrado) e simuladores.

### Compiladores e IDEs

Estas são as ferramentas para escrever, compilar e gerar o firmware (`.hex`) para os microcontroladores.

* #### **MikroC PRO for PIC**
    * **O que é:** Um ambiente de desenvolvimento e compilador C da empresa MikroElektronika. É muito popular em ambientes educacionais por possuir uma vasta quantidade de bibliotecas prontas que abstraem o hardware e simplificam a programação de periféricos como LCDs, ADC, UART, etc.
    * **Download e Uso:**
        * **Página Oficial:** [https://www.mikroe.com/mikroc-pic](https://www.mikroe.com/mikroc-pic)
        * **Guia Rápido (Recomendado):** [Guia de Início Rápido do Compilador](https://www.mikroe.com/blog/compiler-quick-start-guide)

* #### **MPLAB X IDE**
    * **O que é:** É a IDE oficial e gratuita da Microchip, fabricante dos PICs. Oferece um ambiente robusto com depurador integrado (*debugger*), compiladores oficiais (como o XC8) e total suporte ao ecossistema da Microchip. É a ferramenta padrão da indústria para desenvolvimento profissional.
    * **Download e Uso:**
        * Faça o download na página oficial da Microchip, selecionando a versão para o seu sistema operacional: [MPLAB X IDE Download](https://www.microchip.com/en-us/tools-resources/develop/mplab-x-ide)
        * Após instalar a IDE, você também precisará instalar o compilador C, como o **MPLAB XC8**, disponível na mesma página.

---

### Simuladores

Após gerar o arquivo `.hex`, utilizamos os simuladores abaixo para testar o comportamento do programa sem a necessidade do hardware físico.

* #### **PICSimLab**
    * **O que é:** Um simulador em tempo real de placas de desenvolvimento. Sua grande vantagem é emular placas completas como a **PICGenios**, com todos os seus periféricos (LCD, LEDs, botões, ventoinha, etc.) já conectados. Isso torna a simulação extremamente fiel à placa real.
    * **Download e Uso:**
        * O PICSimLab é de código aberto e pode ser baixado em sua página no SourceForge: [PICSimLab Download](https://sourceforge.net/projects/picsimlab/files/latest/download)
        * Para um guia detalhado sobre como usar o PICSimLab especificamente com os projetos deste repositório, consulte o **[guia dentro da pasta PICGenios](./Kits/PICGenios/README.md)**.
    * **Exemplos**: Os **[exemplos](./Kits/PICGenios/Exemplos)** encontrados nesse repositório para uso do PICSimLab são para a placa PICGenios, criados utilizando a IDE MikroC. 

* #### **SimulIDE**
    * **O que é:** Um simulador de circuitos eletrônicos em tempo real. Diferente do PICSimLab, ele é focado em simulação a nível de componentes. É ideal para criar e testar circuitos customizados do zero, onde você mesmo conecta o microcontrolador, resistores, LEDs e outros CIs.
    * **Download e Uso:**
        * O SimulIDE também é de código aberto e pode ser baixado em sua página oficial: [SimulIDE Download](https://www.simulide.com/p/downloads.html)
        * Para usá-lo, crie um novo circuito, adicione um PIC18F4550 da biblioteca de componentes, clique com o botão direito sobre ele e carregue o firmware `.hex`. Em seguida, adicione e conecte os demais componentes (LEDs, botões, etc.) aos pinos correspondentes.
    * **Exemplos**: Os **[exemplos](./Kits/EasyPIC/Exemplos)** encontrados nesse repositório para uso do SimulIDE são baseados na placa EasyPIC, utilizados em aula e criados utilizando a IDE MikroC. 
