# Cadastro_Reserva_Hotel
# Sistema de Gerenciamento de Reservas de Hotel

Este é um sistema de gerenciamento de reservas para um hotel, implementado em linguagem C. Ele permite a inserção, remoção, alteração e consulta de clientes, quartos e reservas, além de fornecer funcionalidades para verificar a disponibilidade de quartos em datas específicas e calcular o custo de uma reserva.

## Estruturas de Dados

O sistema utiliza as seguintes estruturas de dados:

- **Cliente**: Armazena informações sobre um cliente, incluindo ID, nome, email e data de nascimento.
- **Quarto**: Armazena informações sobre um quarto, incluindo número, capacidade, preço da diária e disponibilidade.
- **Reserva**: Armazena informações sobre uma reserva, incluindo ID, ID do cliente, número do quarto, data de início, data de fim, valor pago, horário de chegada e horário de saída.

## Funcionalidades Principais

O sistema oferece as seguintes funcionalidades principais:

- **Inserir Cliente**: Adiciona um novo cliente ao sistema.
- **Alterar Cliente**: Permite alterar as informações de um cliente existente.
- **Remover Cliente**: Remove um cliente do sistema.
- **Consultar Cliente**: Exibe uma lista de todos os clientes cadastrados.
- **Inserir Quarto**: Adiciona um novo quarto ao sistema.
- **Alterar Quarto**: Permite alterar as informações de um quarto existente.
- **Remover Quarto**: Remove um quarto do sistema.
- **Consultar Quarto**: Exibe uma lista de todos os quartos cadastrados.
- **Fazer Reserva**: Cria uma nova reserva para um cliente em um quarto específico.
- **Verificar Disponibilidade**: Verifica se um quarto está disponível em uma data específica.
- **Consultar Reserva**: Exibe uma lista de todas as reservas feitas.
- **Alterar Reserva**: Permite alterar as informações de uma reserva existente.
- **Remover Reserva**: Remove uma reserva do sistema.

## Funcionalidades Auxiliares

O sistema também inclui algumas funcionalidades auxiliares, como:

- **Comparar Datas**: Compara duas datas para determinar qual é mais antiga.
- **Calcular Número de Dias**: Calcula o número de dias entre duas datas.
- **Calcular Custo da Reserva**: Calcula o custo total de uma reserva com base na diária do quarto e no número de dias.
- **Atualizar Valor das Reservas**: Atualiza o valor total das reservas de um quarto após a alteração do preço da diária.

## Como Utilizar

Para utilizar o sistema, compile o código-fonte em um ambiente compatível com C e execute o programa. O sistema apresentará um menu principal com opções para cada funcionalidade. Basta selecionar a operação desejada e seguir as instruções apresentadas na tela.

## Contribuição

Contribuições são bem-vindas! Se você encontrou algum problema, tem uma ideia para uma nova funcionalidade ou deseja fazer melhorias no código, sinta-se à vontade para abrir uma issue ou enviar um pull request.
