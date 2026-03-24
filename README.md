# [cite_start]Sistema de Nível de Reservatório [cite: 34]

## 📖 Sobre o Projeto
[cite_start]O projeto consiste em um sistema desenvolvido com Arduino e outros componentes eletrônicos[cite: 43]. [cite_start]Seu objetivo principal é controlar o nível de um reservatório de água, monitorar em que nível a água se encontra e exibir essas informações em tempo real em um display LCD[cite: 43]. 

[cite_start]Este projeto foi desenvolvido por alunos do SENAI (Turma MA - 78)[cite: 33, 40].

## 👥 Equipe
* [cite_start]Ana Clara Rodrigues Abreu [cite: 39]
* [cite_start]Matheus Scherer Jardim [cite: 39]
* [cite_start]Luíza da Silva [cite: 39]

## ⚙️ Funcionalidades do Sistema
[cite_start]O sistema de controle de nível e consumo possui as seguintes características operacionais[cite: 132]:
* [cite_start]**Monitoramento Preciso:** Utiliza 5 sensores físicos (15% a 85%) com lógica em cascata para evitar falsas leituras[cite: 133].
* [cite_start]**Cálculo de Consumo:** Quedas no nível da água são somadas ao Consumo Total, e um potenciômetro é utilizado para simular a variação fina do volume[cite: 134].
* [cite_start]**Segurança Automatizada:** A bomba de água (representada por um Servo Motor) liga de forma automática e desliga apenas ao atingir o nível máximo ou se ocorrer algum erro[cite: 136].
* [cite_start]**Detecção de Falhas:** O sistema é capaz de identificar sensores travados ou desconectados[cite: 137].
* [cite_start]**Memória Não-Volátil (EEPROM):** O histórico de consumo é salvo a cada 5 segundos para prevenir a perda de dados em caso de queda de energia[cite: 138].
* [cite_start]**Interface LCD:** Exibe em tempo real o nível (N), volume (V), consumo (Cons) e o status da bomba (B)[cite: 139].

## 🛠️ Componentes Físicos (Hardware)
O protótipo do projeto foi construído utilizando os seguintes componentes:
* [cite_start]**Arduino UNO:** Microcontrolador responsável por processar o código e gerenciar todo o sistema[cite: 143].
* [cite_start]**Protoboard:** Utilizada para a montagem e conexão dos componentes sem a necessidade de solda[cite: 144].
* [cite_start]**5 Sensores (Switches):** Responsáveis por detectar o nível físico da água na caixa d'água (de 15% a 85%)[cite: 147].
* [cite_start]**Potenciômetro:** Botão giratório utilizado para simular o volume e o consumo de água entre as leituras dos sensores[cite: 148].
* [cite_start]**Servo Motor:** Representa a bomba de água, movendo-se para indicar se ela está ligada ou desligada[cite: 149].
* [cite_start]**Display LCD (I2C):** Tela que mostra o Nível, o Volume, o Consumo Total e o status da Bomba[cite: 150].

## 💻 Ferramentas e Tecnologias
Diversas ferramentas foram utilizadas para o planejamento, desenvolvimento e apresentação do projeto:
* [cite_start]**Linguagem:** C++[cite: 45].
* [cite_start]**Arduino IDE:** Utilizado para programar e passar o código para o Arduino UNO[cite: 63, 64].
* [cite_start]**Wokwi:** Plataforma usada para simular o circuito e testar o código antes da montagem física do protótipo[cite: 53, 54].
* [cite_start]**Trello:** Utilizado para organizar as tarefas e dar direção ao projeto através de um modelo Kanban[cite: 51, 52].
* [cite_start]**Git e GitHub:** Ferramentas utilizadas para armazenar, versionar e compartilhar o código, além de manter o histórico de modificações[cite: 58, 60, 61].
* [cite_start]**Canva:** Usado na criação da apresentação visual do trabalho[cite: 47, 49].
* [cite_start]**Google Docs e Gmail:** Usados para a elaboração do relatório do projeto e para a troca de informações e comunicação da equipe[cite: 56, 59].

## 📌 Conclusão
[cite_start]A execução do projeto provou que é possível desenvolver uma solução de engenharia altamente eficiente utilizando uma boa organização e hardware acessível[cite: 28]. [cite_start]O Arduino Uno demonstrou ser uma ferramenta bastante precisa para o monitoramento do reservatório[cite: 29]. [cite_start]Através da lógica de sensores em cascata (para evitar erros de leitura) e da simulação de consumo com o potenciômetro, o sistema garante o acompanhamento e a exibição dos dados com sucesso e em tempo real[cite: 30].
