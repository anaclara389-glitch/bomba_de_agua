# Sistema de Nível de Reservatório

## 📖 Sobre o Projeto
O projeto consiste em um sistema desenvolvido com Arduino e outros componentes eletrônicos. Seu objetivo principal é controlar o nível de um reservatório de água, monitorar em que nível a água se encontra e exibir essas informações em tempo real em um display LCD. 

Este projeto foi desenvolvido por alunos do CentroWEG (Turma MA - 78).

## 👥 Equipe
* Ana Clara Rodrigues Abreu - código da Bomba (Servo motor);
* Luíza da Silva - código base e dos Sensores;
* Matheus Scherer Jardim - código do Display.

## ⚙️ Funcionalidades do Sistema
O sistema de controle de nível e consumo possui as seguintes características operacionais:

* **Monitoramento Preciso:** Utiliza 5 sensores físicos (15% a 85%) com lógica em cascata para evitar falsas leituras.
* **Cálculo de Consumo:** Quedas no nível da água são somadas ao Consumo Total, e um potenciômetro é utilizado para simular a variação fina do volume.
* **Segurança Automatizada:** A bomba de água (representada por um Servo Motor) liga de forma automática e desliga apenas ao atingir o nível máximo ou se ocorrer algum erro.
* **Detecção de Falhas:** O sistema é capaz de identificar sensores travados ou desconectados.
* **Memória Não-Volátil (EEPROM):** O histórico de consumo é salvo a cada 5 segundos para prevenir a perda de dados em caso de queda de energia.
* **Interface LCD:** Exibe em tempo real o nível (N), volume (V), consumo (Cons) e o status da bomba (B).

## 🛠️ Componentes Físicos (Hardware)
O protótipo do projeto foi construído utilizando os seguintes componentes:
* **Arduino UNO:** Microcontrolador responsável por processar o código e gerenciar todo o sistema.
* **Protoboard:** Utilizada para a montagem e conexão dos componentes sem a necessidade de solda.
* **5 Sensores (Switches):** Responsáveis por detectar o nível físico da água na caixa d'água (de 15% a 85%).
* **Potenciômetro:** Botão giratório utilizado para simular o volume e o consumo de água entre as leituras dos sensores.
* **Servo Motor:** Representa a bomba de água, movendo-se para indicar se ela está ligada ou desligada.
* **Display LCD (I2C):** Tela que mostra o Nível, o Volume, o Consumo Total e o status da Bomba.

## 💻 Ferramentas e Tecnologias
Diversas ferramentas foram utilizadas para o planejamento, desenvolvimento e apresentação do projeto:
* **Linguagem:** C++.
* **Arduino IDE:** Utilizado para programar e passar o código para o Arduino UNO.
* **Wokwi:** Plataforma usada para simular o circuito e testar o código antes da montagem física do protótipo.
* **Trello:** Utilizado para organizar as tarefas e dar direção ao projeto através de um modelo Kanban.
* **Git e GitHub:** Ferramentas utilizadas para armazenar, versionar e compartilhar o código, além de manter o histórico de modificações.
* **Canva:** Usado na criação da apresentação visual do trabalho.
* **Google Docs e Gmail:** Usados para a elaboração do relatório do projeto e para a troca de informações e comunicação da equipe.

## 📌 Conclusão
A execução do projeto provou que é possível desenvolver uma solução de engenharia altamente eficiente utilizando uma boa organização e hardware acessível. O Arduino Uno demonstrou ser uma ferramenta bastante precisa para o monitoramento do reservatório. 
Através da lógica de sensores em cascata (para evitar erros de leitura) e da simulação de consumo com o potenciômetro, o sistema garante o acompanhamento e a exibição dos dados com sucesso e em tempo real.
