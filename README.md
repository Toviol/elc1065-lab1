Markdown

# ELC1065 - Laboratório de Programação 1: Trabalhos Finais

Este repositório contém os trabalhos **t4** e **t5**, que compõem a entrega final da disciplina de Laboratório de Programação 1 (ELC1065), ministrada pelo professor Benhur de Oliveira Stein.

## Pré-requisitos

Para compilar e executar o projeto, é necessário ter o compilador GCC e a biblioteca Allegro 5 devidamente instalada no seu sistema. O projeto foi desenvolvido e testado em um ambiente Linux (Ubuntu/Debian).

## Instruções de Instalação

Siga os passos abaixo para configurar o ambiente e instalar todas as dependências necessárias.

### 1. Atualizar os Pacotes do Sistema

Primeiro, atualize a lista de pacotes do seu sistema para garantir que você está baixando as versões mais recentes das dependências.

```bash
sudo apt-get update
2. Instalar Dependências Essenciais
sudo apt-get install build-essential cmake xorg-dev libgl1-mesa-dev libglu1-mesa-dev

3. Instalar Dependências Específicas do Allegro 5
sudo apt-get install libpng-dev libcurl4-openssl-dev libfreetype6-dev libjpeg-dev libvorbis-dev libopenal-dev libphysfs-dev libgtk2.0-dev libasound2-dev libpulse-dev libflac-dev libdumb1-dev

4. Baixar e Instalar o Allegro 5
Se a sua distribuição não fornecer pacotes dev para o Allegro 5, você pode compilá-lo a partir do código-fonte.
Baixe o código-fonte do site oficial do Allegro.
Descompacte o arquivo baixado. Substitua allegro-5.x.x.tar.gz pelo nome do arquivo que você baixou.


tar -xvzf allegro-5.x.x.tar.gz
Navegue até o diretório extraído, crie uma pasta de compilação e execute o CMake, make e make install.

cd allegro-5.x.x/
mkdir build
cd build
cmake .. -DCMAKE_INSTALL_PREFIX=/usr
make
sudo make install

Como Compilar e Executar o Projeto:
gcc -o exe tobiasT4.c tela.c $(allegro-config --libs --cflags)
Observação: O comando allegro-config --libs --cflags adiciona automaticamente todas as flags necessárias para linkar a biblioteca Allegro.

Para rodar o programa, execute o arquivo gerado:
./exe
