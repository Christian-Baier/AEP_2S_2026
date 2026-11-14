# Considerações Finais – NutriEscola

## 1. Resultados

O objetivo desta etapa era transformar o planejamento da primeira entrega em um protótipo funcionando, mantendo a proposta de apoiar ações coletivas de alimentação saudável sem expor dados dos estudantes. O resultado:

| Item | Resultado |
|------|-----------|
| **Funcionalidades** | Os 8 requisitos funcionais (RF01 a RF08) foram implementados: cadastrar, listar, pesquisar, atualizar situação, registrar participantes, gerar resumo, validar entradas e encerrar. |
| **Código** | Um arquivo (`src/main.cpp`) com cerca de 400 linhas, 1 `struct` (`Acao`), 1 `vector` e 16 funções, cada uma com uma responsabilidade. |
| **Compilação** | Sem erros e sem avisos em C++98, C++11 e C++17, com `g++ -Wall -Wextra -pedantic`. |
| **Testes** | 24 casos de teste executados e aprovados, além de testes extras: entrada com final de linha do Windows, 51 cadastros seguidos para testar o limite, entrada interrompida e 3000 linhas aleatórias. O programa não travou nem encerrou com erro em nenhum deles. Detalhes em [relatorio_de_testes.md](relatorio_de_testes.md). |
| **Engenharia de software** | Diagrama de casos de uso, 7 casos de uso descritos (mais 2 de apoio), diagrama de estados, 10 regras de negócio, requisitos atualizados com 15 mudanças justificadas e matriz de rastreabilidade. |
| **Documentação do usuário** | Manual com instruções de compilação e execução, explicação de cada opção, roteiro de demonstração e 9 capturas de tela. |
| **Privacidade** | A estrutura `Acao` não tem nenhum campo de dado pessoal ou clínico. O sistema só guarda informações coletivas e quantidades. |

Voltando à pergunta de pesquisa do documento da primeira etapa, o protótipo mostra, em um cenário simulado e com dados fictícios, que uma aplicação de terminal simples consegue reunir em um só lugar o que foi planejado, realizado e cancelado, e calcular o alcance das ações usando apenas números agregados. A privacidade é garantida por desenho: como não existe campo para identificar crianças, o sistema não tem onde guardar esses dados.

## 2. Limitações

| # | Limitação | Efeito para o usuário |
|---|-----------|-----------------------|
| 1 | Os dados ficam só na memória (RNF03). | Ao fechar o programa, tudo é perdido. A demonstração precisa ser feita em uma única execução. |
| 2 | Não existe editar nem excluir uma ação. | Um erro de digitação no cadastro só se corrige cadastrando de novo com outro código; a ação errada continua na lista até o programa ser fechado. |
| 3 | Qualquer mudança de situação é permitida. | Uma ação cancelada pode voltar a "realizada" sem nenhum aviso. Não há ordem obrigatória entre as situações. |
| 4 | O percentual geral considera todas as ações, inclusive planejadas e canceladas. | O número pode parecer baixo enquanto muitas ações ainda não aconteceram, ou por causa de uma ação cancelada com previsão alta. |
| 5 | O código da ação diferencia maiúsculas de minúsculas e espaços. | `A01`, `a01` e `A01 ` (com espaço no fim) são códigos diferentes, o que pode causar "acao nao encontrada" por engano. |
| 6 | A pesquisa ignora maiúsculas apenas para letras sem acento. | Pesquisar `SAÚDE` não encontra `saúde`. |
| 7 | Os campos de texto aceitam qualquer coisa. | Nada impede que alguém digite um nome de aluno em "Responsável". A proteção depende do uso correto e dos dados fictícios, como previsto no documento. |
| 8 | Limites fixos: 50 ações e quantidades até 999999. | Escolas com muitas ações precisariam de outra versão. |
| 9 | A data é validada quanto ao formato e ao calendário, mas não é comparada com a data de hoje. | É possível cadastrar uma ação "realizada" com data futura, ou planejar uma ação no passado. |
| 10 | A listagem não é ordenada nem filtrada. | Mostra sempre na ordem de cadastro. |
| 11 | O resumo não indica qual ação teve maior participação. | A introdução do documento cita esse tipo de análise, mas o RF06 só exigia os totais e o percentual. |
| 12 | Os textos não têm acentos (RNF08). | A interface fica menos polida, em troca de funcionar em qualquer terminal. |
| 13 | Os testes são feitos com entradas prontas e conferidos por quem executa. | Não há teste automatizado que compare a saída sozinho. |

## 3. Aprendizados

- **Requisitos só ficam completos quando se programa.** Ao implementar, apareceram lacunas que o planejamento não tinha visto: o valor de `LIMITE_MAXIMO`, a fórmula do percentual, o que fazer com participantes de ação cancelada e a falta de um requisito para a opção "Sair". Registrar cada uma como mudança justificada (MUD-01 a MUD-15) foi mais honesto e mais útil do que fingir que o plano já estava perfeito.
- **Os artefatos precisam ficar coerentes entre si.** A Figura 2 e o pseudocódigo 3.2.2 descreviam ordens diferentes para a verificação do código duplicado. Só percebemos ao transformar os dois em código. Manter fluxograma, pseudocódigo e implementação alinhados evita decisões no escuro.
- **Validar entrada dá mais trabalho do que a regra de negócio.** A primeira versão da data aceitava `31/02/2026` porque só conferia se o dia ia de 1 a 31. O defeito passou pelos testes iniciais e só apareceu na revisão (BUG-01). Aprendemos a testar valores de borda (fim de mês, ano bissexto) e não só um exemplo válido e um inválido.
- **Dividir em funções facilita testar e corrigir.** Como cada opção do menu é uma função e a leitura de dados fica em funções separadas, o defeito da data foi corrigido em um único lugar (`dataValida`), sem mexer no resto.
- **Testar com entrada pronta economiza tempo.** Guardar as respostas em um arquivo e redirecioná-las para o programa permite repetir a mesma bateria depois de cada mudança e comparar o resultado.
- **O que roda em uma máquina pode falhar em outra.** A primeira versão apresentou falhas em outro ambiente (OC-01). Simplificar o código e compilar em vários padrões do C++ reduziu esse risco. A causa exata não foi identificada, o que também é uma lição: registrar o ambiente (compilador e sistema) ao relatar um erro.
- **Documentar durante o desenvolvimento ajuda a achar erros.** A matriz de rastreabilidade mostrou, por exemplo, uma função do menu sem requisito (RF08).
- **Privacidade se decide no projeto, não no fim.** A decisão mais importante foi não criar campos para dados pessoais. É mais seguro do que criar e depois tentar bloquear.

## 4. Possibilidades de melhoria

| Prazo | Melhoria | Benefício |
|-------|----------|-----------|
| Curto | Calcular o percentual só com as ações realizadas, ou mostrar os dois valores. | Percentual mais fiel (limitação 4). |
| Curto | Indicar no resumo a ação com maior participação. | Atende a análise citada na introdução (limitação 11). |
| Curto | Ignorar espaços no começo e no fim do código e comparar sem diferenciar maiúsculas. | Menos erros de "acao nao encontrada" (limitação 5). |
| Curto | Permitir editar e excluir uma ação, com confirmação. | Corrigir erros sem reiniciar (limitação 2). |
| Curto | Restringir transições de situação (por exemplo, pedir confirmação para reabrir uma ação cancelada). | Menos erros de operação (limitação 3). |
| Médio | Salvar e carregar as ações em arquivo de texto ou CSV. | Os dados deixam de se perder ao fechar (limitação 1). |
| Médio | Ordenar a listagem por data e filtrar por situação. | Facilita o acompanhamento (limitação 10). |
| Médio | Relatórios por escola, por tema e por período. | Apoia o planejamento de novas ações. |
| Médio | Testes automatizados que comparem a saída com o resultado esperado. | Regressão sem conferência manual (limitação 13). |
| Médio | Interface com acentos usando UTF-8 e verificação de data futura ou passada. | Interface mais polida e mais coerente (limitações 9 e 12). |
| Longo | Banco de dados, perfis de usuário e interface gráfica ou web. | Uso real por várias escolas ao mesmo tempo. |

Qualquer melhoria que envolva guardar dados em arquivo ou banco exige antes uma nova avaliação de privacidade, para continuar respeitando a LGPD e o princípio de usar apenas dados coletivos.

## 5. Conclusão

O NutriEscola cumpre o escopo proposto: é simples, roda em terminal, usa estruturas de dados em memória e funções com responsabilidades claras, e mantém a proposta ética de não identificar crianças. As limitações acima são conhecidas e documentadas, e a maioria delas é de baixo custo para melhorar em uma próxima versão. Mais do que o programa em si, o principal ganho desta etapa foi percorrer o ciclo completo: do problema social ao requisito, do requisito ao código, do código ao teste e do teste de volta à documentação.
