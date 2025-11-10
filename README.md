# 🎮 Jogo em C com Ranking

Projeto individual que implementa um jogo estilo match-3 em matriz 10×5.

## 💡 Funcionalidades
- Mecânica de combinação de números iguais
- Atualização de valores e reorganização automática do tabuleiro via algoritmo de gravidade
- Pontuação dinâmica
- Progressão de dificuldade
- Recurso de “martelo” como vida extra
- Salvamento e leitura de ranking em arquivo binário, com ordenação por Bubble Sort e persistência entre partidas
- Validação de entrada do usuário e interface interativa no terminal

## 🧰 Tecnologias
- Linguagem C
- Manipulação de arquivos (fopen, fread, fwrite)
- Struct
- Ordenação
- Controle de fluxo

## ▶️ Como executar
```bash
gcc LETRIS.c -o LETRIS
./LETRIS
