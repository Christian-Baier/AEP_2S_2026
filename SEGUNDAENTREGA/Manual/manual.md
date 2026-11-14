# Manual do Usuário – NutriEscola

## 1. Objetivo

O NutriEscola é um programa de terminal para **planejar e acompanhar ações coletivas de alimentação saudável** feitas nas escolas, no contexto do Programa Saúde na Escola (PSE): oficinas, hortas, rodas de conversa, campanhas de incentivo ao consumo de água e outras atividades parecidas.

Com ele você consegue:

- registrar cada ação planejada (escola, tema, data, público, responsável e quantidade prevista);
- consultar e pesquisar as ações cadastradas;
- marcar o que foi realizado ou cancelado;
- informar **quantas** pessoas participaram (apenas o número, nunca quem);
- ver um resumo com os totais e o percentual de participação.

> **Importante:** o NutriEscola **não** é um sistema clínico. Ele não faz consulta, diagnóstico nem prescrição de dieta, e não guarda nome, matrícula ou qualquer dado de saúde de crianças. Use sempre dados fictícios ou coletivos.

## 2. A quem se destina

À equipe escolar (direção, coordenação pedagógica e professores) e à equipe de saúde da Atenção Primária que organizam as ações do PSE. As duas equipes usam o programa do mesmo jeito, com as mesmas funções.

## 3. O que é preciso para usar

- Um computador com Windows, Linux ou macOS.
- Um compilador de C++ (por exemplo, o `g++`) ou uma IDE que já traga um compilador, como Dev-C++ ou Code::Blocks (versões com MinGW).
- O arquivo `src/main.cpp` deste repositório.

Não é preciso internet, banco de dados nem instalar bibliotecas.

## 4. Como compilar e executar

### 4.1 Linux e macOS

Abra o terminal na pasta do projeto e rode:

```bash
g++ -Wall -Wextra -o nutriescola src/main.cpp
./nutriescola
```

Se o `g++` não estiver instalado: no Ubuntu/Debian use `sudo apt install g++`; no macOS use `xcode-select --install`.

### 4.2 Windows (terminal)

Com o `g++` instalado (por exemplo, MinGW-w64 pelo MSYS2) e no PATH, abra o Prompt de Comando ou o PowerShell na pasta do projeto:

```bat
g++ -Wall -Wextra -o nutriescola.exe src\main.cpp
.\nutriescola.exe
```

No Prompt de Comando (cmd) basta escrever `nutriescola.exe`.

### 4.3 Usando uma IDE

Abra o arquivo `src/main.cpp` no Dev-C++ ou no Code::Blocks e use o comando de compilar e executar (F11 no Dev-C++, F9 no Code::Blocks). Se a janela fechar sozinha assim que o programa terminar, rode pelo terminal como nas seções acima.

### 4.4 O que você deve ver

A compilação **não mostra nenhuma mensagem** quando está tudo certo. Ao executar, aparece o menu principal e o programa fica esperando você digitar uma opção.

![Compilação e abertura do programa](img/01_compilar_e_executar.png)

*Figura 1 – Compilação sem mensagens e menu principal do NutriEscola.*

> **Teste rápido sem digitar nada:** `./nutriescola < testes/entrada_teste.txt` executa uma sequência pronta de respostas, com acertos e erros misturados. A saída esperada está em `testes/saida_teste.txt`.

## 5. Regras gerais de uso

- Digite a resposta e aperte **Enter** para confirmar.
- Os dados ficam **só na memória**: ao fechar o programa, tudo é apagado. Faça o cadastro e as consultas na mesma execução.
- Datas sempre no formato `dd/mm/aaaa` (exemplo: `15/10/2026`).
- Quantidades são números inteiros, de 0 a 999999. Não use vírgula, ponto, letras nem sinal de menos.
- O **código** da ação é único e o programa diferencia maiúsculas de minúsculas: `A01` e `a01` são códigos diferentes. Para mexer numa ação, digite o código exatamente como cadastrou.
- Campos de texto não podem ficar em branco.
- O programa guarda até **50 ações**.
- Se digitar algo inválido, o programa explica o erro e **pede o mesmo dado de novo**. Ele não fecha por causa disso.
- Para sair, use a opção 7. Em caso de emergência, `Ctrl+C` interrompe o programa.
- As mensagens do programa não usam acentos de propósito, para não aparecerem caracteres trocados em alguns terminais. Prefira também não usar acentos ao digitar.

## 6. O menu principal

| Opção | Nome | Para que serve |
|:-----:|------|----------------|
| 1 | Cadastrar acao | Registrar uma nova ação (começa como "planejada"). |
| 2 | Listar acoes | Ver todas as ações cadastradas. |
| 3 | Pesquisar acao | Achar ações por código, escola ou tema. |
| 4 | Atualizar situacao | Marcar uma ação como planejada, realizada ou cancelada. |
| 5 | Registrar participantes | Informar ou corrigir quantas pessoas participaram de uma ação realizada. |
| 6 | Gerar resumo estatistico | Ver totais e percentual de participação. |
| 7 | Sair | Encerrar o programa. |

Depois de cada operação o menu volta sozinho.

## 7. Passo a passo de cada operação

Os exemplos abaixo usam dados **fictícios**. As figuras são de execuções diferentes do programa, por isso cada uma começa do zero e repete os cadastros necessários.

### 7.1 Cadastrar ação (opção 1)

**Quando usar:** quando uma atividade foi planejada e você quer registrá-la.

**Como fazer:** escolha `1` e responda às sete perguntas, uma de cada vez.

| Pergunta | O que digitar | Exemplo |
|----------|---------------|---------|
| Codigo da acao | Um código que ainda não foi usado | `A01` |
| Escola | Nome da escola | `Escola Municipal Sol` |
| Tema | Assunto da ação (o subtema pode ir junto) | `Oficina de frutas` |
| Data prevista (dd/mm/aaaa) | Data da ação | `15/10/2026` |
| Publico-alvo | Turma ou faixa de alunos | `3o ano` |
| Responsavel (cargo ou setor) | Cargo ou setor, **nunca nome de aluno** | `Coordenacao pedagogica` |
| Quantidade prevista de participantes | Número inteiro | `30` |

No fim aparece **"Acao cadastrada com sucesso."**. A ação fica com situação "planejada" e 0 participantes.

![Cadastro de uma ação](img/02_cadastrar_acao.png)

*Figura 2 – Cadastro de uma ação com todos os dados válidos.*

**Se você errar**, o programa avisa e pergunta de novo só aquele dado. A Figura 3 mostra os erros mais comuns: código repetido, campo em branco (ou só com espaços), data que não existe (`31/02/2026`), data fora do formato (`20-11-2026`) e quantidade inválida (`-40` e `abc`).

![Cadastro com erros de digitação](img/03_cadastro_validacoes.png)

*Figura 3 – Mensagens de erro durante o cadastro. Depois de cada erro o programa pede o mesmo dado novamente.*

Se já houver 50 ações cadastradas, o programa mostra "Capacidade maxima de acoes atingida." e não cadastra.

### 7.2 Listar ações (opção 2)

**Quando usar:** para ver tudo o que já foi registrado.

**Como fazer:** escolha `2`. Cada ação aparece em uma ficha, na ordem em que foi cadastrada, com código, escola, tema, data, público-alvo, responsável, quantidade prevista, participantes efetivos e situação.

![Lista de ações](img/04_listar_acoes.png)

*Figura 4 – Listagem com duas ações cadastradas. Ambas estão "planejadas" e com 0 participantes.*

Se não houver nada cadastrado, aparece "Nenhuma acao cadastrada.".

### 7.3 Pesquisar ação (opção 3)

**Quando usar:** quando há muitas ações e você quer ver só algumas, por exemplo "o que a Escola Municipal Sol tem planejado?".

**Como fazer:**

1. Escolha `3`.
2. Escolha o critério: `1` código, `2` escola ou `3` tema.
3. Digite o texto procurado. Pode ser só um pedaço, em maiúsculas ou minúsculas.

O programa mostra as fichas encontradas e a linha **"Total encontrado: N"**. Se nada for encontrado, mostra "Nenhuma acao encontrada.".

![Pesquisa por tema](img/05_pesquisar_acoes.png)

*Figura 5 – Pesquisa por tema com o texto `HORTA`. O programa encontra "Horta escolar" mesmo com letras maiúsculas.*

### 7.4 Atualizar situação (opção 4)

**Quando usar:** quando uma ação aconteceu ou foi cancelada.

**Como fazer:**

1. Escolha `4` e digite o código da ação (exemplo: `A01`).
2. O programa mostra a situação atual. Escolha a nova: `1` Planejada, `2` Realizada ou `3` Cancelada.
3. Se escolher **Realizada**, o programa pergunta quantas pessoas participaram. Digite o número (exemplo: `28`).

![Atualização de situação](img/06_atualizar_situacao.png)

*Figura 6 – A ação A01 passa de "planejada" para "realizada", com 28 participantes.*

Duas regras importantes:

- Se escolher **Planejada** ou **Cancelada**, os participantes voltam a 0, porque uma ação que não aconteceu não tem participantes.
- Se o código não existir, o programa mostra "Erro: acao nao encontrada." e volta ao menu. Refaça a operação digitando o código certo.

### 7.5 Registrar participantes (opção 5)

**Quando usar:** para informar ou **corrigir** quantas pessoas participaram de uma ação já realizada (por exemplo, quando a contagem final só ficou pronta no dia seguinte).

**Como fazer:** escolha `5`, digite o código e depois a quantidade. O valor novo **substitui** o anterior (não é somado).

Só funciona para ações com situação **realizada**. Se a ação estiver planejada ou cancelada, o programa explica e orienta a usar antes a opção 4.

![Registro de participantes](img/07_registrar_participantes.png)

*Figura 7 – Primeiro, uma tentativa na ação A02 (ainda planejada), que é recusada. Depois, na ação A01 (realizada), o valor `-3` é recusado e o valor `25` corrige os 28 participantes anteriores.*

O programa guarda **apenas o número**. Ele nunca pergunta quem participou.

### 7.6 Gerar resumo estatístico (opção 6)

**Quando usar:** no fim de um período, para prestar contas ou decidir quais ações repetir.

**Como fazer:** escolha `6`. O programa mostra:

- total de ações;
- quantas estão planejadas, realizadas e canceladas;
- total previsto e total efetivo de participantes;
- percentual geral de participação.

![Resumo estatístico](img/08_resumo_estatistico.png)

*Figura 8 – Resumo com três ações: uma planejada (A02, previsão 40), uma realizada (A01, previsão 30, 25 participantes) e uma cancelada (A03, previsão 25).*

Como o percentual é calculado: **total efetivo ÷ total previsto × 100**. No exemplo, 25 ÷ (30 + 40 + 25) × 100 = 26,3% (o programa escreve `26.3%`, com ponto).

Atenção ao interpretar: o cálculo considera **todas** as ações, inclusive as planejadas e as canceladas, então ele só fica mais próximo da realidade quando a maioria das ações já foi realizada. O percentual pode passar de 100% se vier mais gente do que o previsto. Se o total previsto for zero, o programa avisa que não há previsão para calcular.

### 7.7 Sair (opção 7)

Escolha `7`. O programa mostra "NutriEscola encerrado." e fecha. Lembre-se: **todos os dados são apagados** ao sair.

### 7.8 Opção inválida e sistema vazio

Se você digitar uma opção que não existe, letras ou deixar em branco, o programa avisa e mostra o menu de novo. Se tentar listar, pesquisar, atualizar ou gerar resumo sem ter cadastrado nada, ele responde "Nenhuma acao cadastrada.".

![Opções inválidas e saída](img/09_menu_invalido_e_sair.png)

*Figura 9 – Listar sem ações cadastradas, opção inexistente (`9`), letras (`abc`), campo em branco e saída pela opção `7`.*

## 8. Roteiro completo de demonstração

Use esta sequência para conhecer o programa de ponta a ponta. Ela usa os mesmos dados das figuras.

**Dados fictícios das três ações**

| Código | Escola | Tema | Data | Público-alvo | Responsável | Previsto |
|--------|--------|------|------|--------------|-------------|:--------:|
| A01 | Escola Municipal Sol | Oficina de frutas | 15/10/2026 | 3o ano | Coordenacao pedagogica | 30 |
| A02 | Escola Estadual Lua | Horta escolar | 20/11/2026 | 5o ano | Professor de ciencias | 40 |
| A03 | Escola Municipal Sol | Campanha da agua | 05/12/2026 | 1o ao 5o ano | Equipe de saude | 25 |

**Sequência**

| Passo | Opção | O que fazer | O que esperar |
|:-----:|:-----:|-------------|---------------|
| 1 | 1 | Cadastre A01, A02 e A03 com os dados da tabela. | "Acao cadastrada com sucesso." três vezes. |
| 2 | 2 | Liste as ações. | Três fichas, todas "planejada", com 0 participantes. |
| 3 | 3 | No critério Tema (`3`), pesquise o texto `horta`. | Só a ação A02. "Total encontrado: 1". |
| 4 | 4 | Em A01, escolha Realizada (`2`) com `28` participantes. | A01 fica "realizada". |
| 5 | 5 | Em A01, registre `25` participantes. | O valor 28 é substituído por 25. |
| 6 | 5 | Tente registrar participantes em A02. | Erro: só ações realizadas aceitam participantes. |
| 7 | 4 | Em A03, escolha Cancelada (`3`). | A03 fica "cancelada". |
| 8 | 6 | Gere o resumo. | 1 planejada, 1 realizada, 1 cancelada, previsto 95, efetivo 25, **26.3%**. |
| 9 | 7 | Saia do programa. | "NutriEscola encerrado." |

## 9. Mensagens do programa e o que fazer

| Mensagem | O que significa | O que fazer |
|----------|-----------------|-------------|
| Opcao invalida. Escolha de 1 a 7. | A opção digitada não existe no menu. (Em telas com 3 opções, o intervalo é 1 a 3.) | Digite um número do intervalo indicado. |
| Erro: digite apenas numeros, sem sinal de menos. | Foi digitado algo que não é número inteiro (letra, vírgula, ponto, sinal de menos) ou com mais de 6 dígitos. | Digite só dígitos, por exemplo `30`. |
| Erro: campo vazio. | O campo foi deixado em branco ou só com espaços. | Digite o dado pedido. |
| Erro: data invalida. Use dd/mm/aaaa (exemplo: 15/10/2026). | A data está fora do formato ou não existe no calendário. | Digite uma data real, com barras, por exemplo `15/10/2026`. |
| Erro: codigo ja cadastrado. | Já existe uma ação com esse código. | Escolha outro código. |
| Erro: acao nao encontrada. | Não existe ação com o código digitado. | Confira o código na opção 2 e repita a operação. |
| Erro: so e possivel registrar participantes de acao realizada. | A ação está planejada ou cancelada. | Use a opção 4 para marcá-la como realizada primeiro. |
| Capacidade maxima de acoes atingida. | Já há 50 ações cadastradas. | Feche o programa e comece de novo, ou use o que já foi cadastrado. |
| Nenhuma acao cadastrada. | Ainda não há ações. | Cadastre pela opção 1. |
| Nenhuma acao encontrada. | A pesquisa não achou nada. | Tente outro texto ou outro critério. |
| Entrada encerrada. | A entrada de dados foi interrompida (fim do arquivo ou `Ctrl+D` / `Ctrl+Z`). | Abra o programa de novo. |
