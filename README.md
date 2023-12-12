# 📚 Trabalho 3 de Estrutura de dados

Este repositório contém arquivos fontes para um Simulador de Realização de Exames de Raio-X

**Autores**

* Ryan Lima Peçanha: [@ryanlimap] (https://github.com/ryanlimap/)
* Paulo Vitor Callegari Dalvi: [@paulovitorcallegari] (https://github.com/paulovitorcallegari/)

# 📌 Objetivo

Este trabalho consiste em simular o processo de realização de exames de raio-X em um hospital, com
ênfase na organização da fila para laudo médico. A cada momento, pacientes chegam ao hospital e
exames são realizados mediante disponibilidade de aparelhos. A IA1
sugere diagnósticos preliminares
e os exames são encaminhados para laudo de acordo com a disponibilidade da equipe de radiologistas.
Métricas de desempenho, como tempo médio de laudo e exames realizados fora do prazo, são calculadas.
O objetivo é entender o processo e avaliar a eficiência do sistema, contribuindo para futuras otimizações.

# 💻 Instalação

**Como Executar o programa usando o Makefile:**

* Passo 1: Abra o Terminal
* Passo 2: Navegue até o Diretório do Projeto:

```
cd caminho/para/o/seu/projeto
```

* Passo 3: Execute o Makefile:

```
Make
```

* Passo 4: Execute o Programa

Se a compilação for bem-sucedida, você verá um executável na pasta especificada no Makefile (geralmente em um diretório chamado bin). Agora, você pode executar o programa diretamente do terminal.

# ⚙️ Funcionamento do programa

Ao rodar o programa em sua máquina, o mesmo rodará no terminal do seu sistema operacional e ao final resultará um arquivo chamado "Log.txt" onde mostrará o tempo do ínicio/fim de exames e laudos juntamente com o ID dos seus respectivos pacientes.

* Exemplo de saída:

Novo paciente chegou ao hospital - ID do paciente: 1, Tempo: 0 <br />
Início do exame para o paciente - ID do paciente: 1, Tempo: 0 <br />
Término do exame para o paciente - ID do paciente: 1, Tempo: 0 <br />
...

