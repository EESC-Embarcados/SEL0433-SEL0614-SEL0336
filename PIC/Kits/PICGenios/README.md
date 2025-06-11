# PICSimLab como Alternativa ao SimulIDE para a Placa PICGenios

Este repositório serve como um guia e uma coleção de exemplos práticos para utilizar o simulador **PICSimLab** como uma poderosa alternativa ao SimulIDE, ferramenta comumente utilizada na disciplina de microprocessadores.

O foco aqui é o desenvolvimento para o microcontrolador **PIC18F4550** utilizando a placa de desenvolvimento **PICGenios**, que é totalmente emulada no PICSimLab, permitindo um ciclo de desenvolvimento e teste rápido e fiel ao hardware real.

## Por que usar o PICSimLab em vez do SimulIDE?

Embora o SimulIDE seja uma ferramenta flexível para simulação de circuitos genéricos, o PICSimLab oferece vantagens significativas quando o projeto é baseado em uma placa de desenvolvimento específica, como a PICGenios.

### Vantagens do PICSimLab

* [cite_start]**Simulação de Placa de Desenvolvimento (Board-Level):** A principal vantagem é que o PICSimLab simula a **placa PICGenios completa**, e não apenas os componentes individuais. Você não precisa montar o circuito, conectar fios, resistores ou o display LCD. Você carrega o `.hex` e a placa virtual já está pronta para usar, assim como a física.

* **Fidelidade ao Hardware Real:** Como o simulador emula a placa real, o mesmo firmware (`.hex`) que funciona no PICSimLab tem altíssima probabilidade de funcionar diretamente na placa física sem nenhuma alteração, pois as conexões dos periféricos são idênticas.

* [cite_start]**Periféricos Complexos Integrados:** A placa PICGenios no simulador já inclui a **ventoinha com controle PWM**, o **sensor de velocidade infravermelho**, o display LCD, botões, LEDs e outros componentes já conectados aos pinos corretos do PIC18F4550. Isso permite focar na programação do firmware em vez de na montagem do circuito.

* **Interface Intuitiva:** A interação é totalmente visual. Você clica nos botões, gira os potenciômetros, vê os LEDs acenderem e o texto aparecer no display, tornando a depuração mais intuitiva.

## Como Baixar o PICSimLab

O simulador é gratuito e de código aberto. Você pode baixá-lo diretamente pelo link disponibilizado na documentação de apoio do projeto.

1.  [cite_start]Acesse a página de download do PICSimLab (o link pode ser encontrado na documentação de referência do projeto ).
2.  Uma alternativa é a página oficial do projeto no SourceForge: [https://sourceforge.net/projects/picsim/](https://sourceforge.net/projects/picsim/)
3.  Baixe a versão compatível com o seu sistema operacional e descompacte o arquivo. Não é necessário instalar, basta executar o programa.

## Exemplos Práticos neste Repositório

Este repositório foi criado para centralizar exemplos práticos da disciplina, todos desenvolvidos ou testados na plataforma PICSimLab com a placa PICGenios. O objetivo é fornecer uma base de código funcional para acelerar o desenvolvimento de projetos futuros.

Aqui você encontrará exemplos como:

* Uso de PWM
* Controle do Display de 7 Segmentos
* Uso de LCD
* Blink de LED com e sem debounce
* Conversão ADC
* Timers e interrupções


Sinta-se à vontade para explorar, usar e contribuir com os códigos.

## Problemas comums

1. PICSimLab fechando ao tentar trocar de board (crash): clique em File -> Exit. A próxima vez que você abrir, ele abrirá na placa correta e não irá mais quebrar.
