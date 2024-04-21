    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    typedef struct{
        int dia;
        int mes;
        int ano;
    }DataN;
    typedef struct{
        int hora;
        int min;
        int seg;
    }checking;
    typedef struct{
        int dia;
        int mes;
        int ano;
    }Datacheck;

    typedef struct noDR {
        int numeroQuarto;
        Datacheck data;
        struct noDR* prox;
    } DatasReservadas;

    typedef struct noC{
        int idCliente;
        char nome[50];
        char email[50];
        DataN nascimento;
        struct noC *prox,*ant;
    } Cliente;


    typedef struct noQ {
        int numeroQuarto;
        int capacidade;
        float preco_diaria;
        int disponibilidade;
        struct noQ* prox;
        struct noQ* ant;
    } Quarto;

    typedef struct noR{
        int idReserva;
        int id_cliente;
        Datacheck dataIni;
        Datacheck dataFim;
        int numeroQ;
        float valorPago;
        checking chegada;
        checking saida;
        struct noR* prox,*ant;
    } Reserva;


    void insere_Cliente(Cliente **iniFun, Cliente cli) {
        Cliente *novo = (Cliente*)malloc(sizeof(Cliente));
        Cliente *atual;

        novo->idCliente = cli.idCliente;
        strcpy(novo->nome, cli.nome);
        strcpy(novo->email, cli.email);
        novo->nascimento.dia = cli.nascimento.dia;
        novo->nascimento.mes = cli.nascimento.mes;
        novo->nascimento.ano = cli.nascimento.ano;
        novo->ant = NULL;
        novo->prox = NULL;

        if (*iniFun == NULL) {
            *iniFun = novo;
        } else if (novo->idCliente <= (*iniFun)->idCliente) {
            novo->prox = *iniFun;
            (*iniFun)->ant = novo;
            *iniFun = novo;
        } else {
            atual = *iniFun;
            while (atual->prox != NULL && atual->idCliente <= novo->idCliente) {
                atual = atual->prox;
            }
            if (atual->idCliente >= novo->idCliente) {
                novo->prox = atual;
                novo->ant = atual->ant;
                atual->ant->prox = novo;
                atual->ant = novo;
            } else {
                novo->prox = NULL;
                novo->ant = atual;
                atual->prox = novo;
            }
        }
    }
    void insere_Reserva(Reserva **iniFun,Reserva reser){
        Reserva *novo =(struct noR*)malloc(sizeof(Reserva));
        Reserva *atual;
        novo->idReserva =reser.idReserva;
        novo->id_cliente =reser.id_cliente;
        novo->numeroQ =reser.numeroQ;
        novo->valorPago =reser.valorPago;
        novo->dataIni.dia =reser.dataIni.dia;
        novo->dataIni.mes =reser.dataIni.mes;
        novo->dataIni.ano =reser.dataIni.ano;

        novo->dataFim.dia =reser.dataFim.dia;
        novo->dataFim.mes =reser.dataFim.mes;
        novo->dataFim.ano =reser.dataFim.ano;
        novo->chegada.hora=reser.chegada.hora;
        novo->chegada.min=reser.chegada.min;
        novo->chegada.seg=reser.chegada.seg;


        novo->saida.hora=reser.saida.hora;
        novo->saida.min=reser.saida.min;
        novo->saida.seg=reser.saida.seg;

        novo->ant = NULL;
        novo->prox = NULL;
        if (*iniFun == NULL) {
            *iniFun = novo;
        } else if (novo->idReserva <= (*iniFun)->idReserva ){
            novo->prox = *iniFun;
            (*iniFun)->ant = novo;
            *iniFun = novo;
        } else {
            atual = *iniFun;
            while (atual->prox != NULL && atual->idReserva <= novo->idReserva) {
                atual = atual->prox;
            }
            if (atual->idReserva >= novo->idReserva) {
                novo->prox = atual;
                novo->ant = atual->ant;
                atual->ant->prox = novo;
                atual->ant = novo;
            } else {
                novo->prox = NULL;
                novo->ant = atual;
                atual->prox = novo;
            }
        }

    }
    void insere_quarto(Quarto **iniFun,Quarto quarto){
        Quarto *novo =(struct noQ*)malloc(sizeof(Quarto));
        Quarto *atual;
        novo->numeroQuarto =quarto.numeroQuarto;
        novo->capacidade =quarto.capacidade;
        novo->preco_diaria =quarto.preco_diaria;
        novo->disponibilidade =quarto.disponibilidade;
        novo->ant = NULL;
        novo->prox = NULL;
        if (*iniFun == NULL) {
            *iniFun = novo;
        } else if (novo->numeroQuarto <= (*iniFun)->numeroQuarto  ){
            novo->prox = *iniFun;
            (*iniFun)->ant = novo;
            *iniFun = novo;
        } else {
            atual = *iniFun;
            while (atual->prox != NULL && atual->numeroQuarto  <= novo->numeroQuarto ) {
                atual = atual->prox;
            }
            if (atual->numeroQuarto  >= novo->numeroQuarto ) {
                novo->prox = atual;
                novo->ant = atual->ant;
                atual->ant->prox = novo;
                atual->ant = novo;
            } else {
                novo->prox = NULL;
                novo->ant = atual;
                atual->prox = novo;
            }
        }
    }

    int clienteAssociadoReserva(Reserva *iniReserva, int idCliente) {
        Reserva *atual = iniReserva;

        while (atual != NULL) {
            if (atual->id_cliente == idCliente) {
                return 1; // Cliente está associado a uma reserva
            }
            atual = atual->prox;
        }

        return 0; // Cliente não está associado a nenhuma reserva
    }

    void remove_Cliente(Cliente **inicio, Reserva *iniReserva, int idCliente) {
        Cliente *atual = *inicio;
        atual->ant = NULL;

        if (clienteAssociadoReserva(iniReserva, idCliente)) {
            printf("Cliente esta associado a uma reserva e nao pode ser removido.\n");
            return;
        }

        while (atual != NULL && atual->idCliente != idCliente) {
            atual->ant = atual;
            atual = atual->prox;
        }

        if (atual == NULL) {
            printf("Cliente com ID %d nao encontrado.\n", idCliente);
            return;
        }

        if (atual->ant == NULL) {
            *inicio = atual->prox;
        } else {
            atual->ant->prox = atual->prox;
        }

        if (atual->prox != NULL) {
            atual->prox->ant = atual->ant;
        }
        printf("Cliente do id %d foi removido com sucesso!!!\n",idCliente);
        free(atual);
    }
    void remove_reserva(Reserva **inicio, int idReserva, Quarto **iniQ) {
        Reserva *atual = *inicio;
        atual->ant = NULL;


        while (atual != NULL && atual->idReserva != idReserva) {
            atual->ant = atual;
            atual = atual->prox;
        }

        if (atual == NULL) {
            printf("Reserva com ID %d nao encontrada.\n", idReserva);
            return;
        }


        Quarto *quartoAtual = *iniQ;
        while (quartoAtual != NULL && quartoAtual->numeroQuarto != atual->numeroQ) {
            quartoAtual = quartoAtual->prox;
        }

        if (quartoAtual != NULL) {
            quartoAtual->disponibilidade = 1;
        }


        if (atual->ant == NULL) {
            *inicio = atual->prox;
        } else {
            atual->ant->prox = atual->prox;
        }

        if (atual->prox != NULL) {
            atual->prox->ant = atual->ant;
        }

        printf("Reserva com ID [%d] foi removida com sucesso!!!\n", idReserva);
        free(atual);
    }


    void remove_quarto(Quarto **inicio, Reserva *iniReserva, int idQuarto) {

        Reserva *atualReserva = iniReserva;
        Quarto *atualQuarto = *inicio;
        atualQuarto->ant = NULL;

        while (atualReserva != NULL) {
            if (atualReserva->numeroQ == idQuarto) {
                printf("Nao e possivel remover o quarto %d, pois existem reservas associadas a ele.\n", idQuarto);
                return;
            }
            atualReserva = atualReserva->prox;
        }




        while (atualQuarto != NULL && atualQuarto->numeroQuarto != idQuarto) {
            atualQuarto->ant = atualQuarto;
            atualQuarto = atualQuarto->prox;
        }

        if (atualQuarto == NULL) {
            printf("Quarto com ID %d nao encontrado.\n", idQuarto);
            return;
        }

        if (atualQuarto->ant == NULL) {
            *inicio = atualQuarto->prox;
        } else {
            atualQuarto->ant->prox = atualQuarto->prox;
        }

        if (atualQuarto->prox != NULL) {
            atualQuarto->prox->ant = atualQuarto->ant;
        }

        printf("Quarto com ID %d foi removido com sucesso!!!\n", idQuarto);
        free(atualQuarto);
    }


    void consulta_Cliente(Cliente *iniFun) {
        Cliente *atual = iniFun;

        if (atual == NULL) {
            printf("Nenhum cliente registrado.\n");
        } else {
            printf("Listagem de Clientes:\n");
             printf("\n-----------------------\n");
            while (atual != NULL) {
                printf("ID: %d\n", atual->idCliente);
                printf("Nome: %s\n", atual->nome);
                printf("Email: %s\n", atual->email);
                printf("Data de Nascimento: %d/%d/%d\n", atual->nascimento.dia, atual->nascimento.mes, atual->nascimento.ano);
                printf("-----------------------\n");

                atual = atual->prox;
            }
        }
    }
    void consulta_Reserva(Reserva *iniFun) {
        Reserva *atual = iniFun;

        if (atual == NULL) {
            printf("Nenhuma reserva registrada.\n");
        } else {
            printf("Listagem de Reservas:\n");
             printf("\n-----------------------\n");
            while (atual != NULL) {
                printf("ID da Reserva: %d\n", atual->idReserva);
                printf("ID do Cliente: %d\n", atual->id_cliente);
                printf("total a ser pago: R$%2.f\n",atual->valorPago);
                printf("Data de Inicio: %d/%d/%d\n", atual->dataIni.dia, atual->dataIni.mes, atual->dataIni.ano);
                printf("Data de Fim: %d/%d/%d\n", atual->dataFim.dia, atual->dataFim.mes, atual->dataFim.ano);
                printf("Horario de Chegada: %d:%d:%d\n", atual->chegada.hora, atual->chegada.min, atual->chegada.seg);
                printf("Horario de Saida: %d:%d:%d\n", atual->saida.hora, atual->saida.min, atual->saida.seg);
                printf("-----------------------\n");

                atual = atual->prox;
            }
        }
    }

    void consulta_Quarto(Quarto *iniFun) {
        Quarto *atual = iniFun;

        if (atual == NULL) {
            printf("Nenhum quarto registrado.\n");
        } else {
            printf("Listagem de Quartos:\n");
             printf("\n-----------------------\n");
            while (atual != NULL) {
                printf("Numero do Quarto: %d\n", atual->numeroQuarto);
                printf("Capacidade: %d pessoas\n", atual->capacidade);
                printf("Preco da Diaria: %.2f\n", atual->preco_diaria);
                printf("Disponibilidade: %s\n", (atual->disponibilidade == 1) ? "Disponivel" : "Indisponivel");
                printf("-----------------------\n");

                atual = atual->prox;
            }
        }
    }

    int clienteExiste(Cliente *iniFun, Reserva reserva) {
        Cliente *atual = iniFun;

        while (atual != NULL) {
            if (atual->idCliente == reserva.id_cliente) {
                return 1;
            }
            atual = atual->prox;
        }

        return 0;
    }
    void atualizarDisponibilidadeQuarto(Quarto *iniQ, int numeroQuarto, int disponibilidade) {
        Quarto *atual = iniQ;
        while (atual != NULL) {
            if (atual->numeroQuarto == numeroQuarto) {
                atual->disponibilidade = disponibilidade;
                return;
            }
            atual = atual->prox;
        }
    }


    int verificarDisponibilidade(Reserva *iniR, Quarto *iniQ, int numeroQuarto, Datacheck data) {
        Reserva *atual = iniR;
        while (atual != NULL) {
            if (atual->numeroQ == numeroQuarto) {
                if (compararDatas(data, atual->dataIni) >= 0 && compararDatas(data, atual->dataFim) <= 0) {


                    return 0;
                }
            }
            atual = atual->prox;
        }


        return 1;
    }



    int compararDatas(Datacheck data1, Datacheck data2) {
        if (data1.ano > data2.ano ||
            (data1.ano == data2.ano && data1.mes > data2.mes) ||
            (data1.ano == data2.ano && data1.mes == data2.mes && data1.dia > data2.dia)) {
            return 1;
        } else if (data1.ano == data2.ano && data1.mes == data2.mes && data1.dia == data2.dia) {
            return 0;
        }
    }




    int QuartoExiste(Quarto *iniFun, Reserva reserva) {
        Quarto *atual = iniFun;

        while (atual != NULL) {
            if (atual->numeroQuarto == reserva.numeroQ) {
                return 1;
            }
            atual = atual->prox;
        }

        return 0;
    }

    int calcularNumeroDias(Datacheck dataIni, Datacheck dataFim) {
        int numeroDias = 0;

        numeroDias += (dataFim.ano - dataIni.ano) * 360;
        numeroDias += (dataFim.mes - dataIni.mes) * 30;
        numeroDias += dataFim.dia - dataIni.dia + 1;

        return numeroDias;
    }



    float calcularCustoReserva(Quarto *iniQ, Datacheck dataIni, Datacheck dataFim, int numeroQuarto) {
        Quarto *atual = iniQ;
        float preco_diaria = 0.0;
        int numeroDias = 0;

        while (atual != NULL) {
            if (atual->numeroQuarto == numeroQuarto) {
                preco_diaria = atual->preco_diaria;
                break;
            }
            atual = atual->prox;
        }

        numeroDias = calcularNumeroDias(dataIni, dataFim);

        float custo_total = preco_diaria * numeroDias;

        return custo_total;
    }

    int ehBissexto(int ano) {
        if ((ano % 4 == 0 && ano % 100 != 0) || ano % 400 == 0) {
            return 1;
        }
        return 0;
    }
    void atualizarValorReservas(Reserva **inicioReserva, int numeroQuarto, float novoPrecoDiaria) {
    Reserva *atual = *inicioReserva;

    while (atual != NULL) {
        if (atual->numeroQ == numeroQuarto) {

            int numeroDias = calcularNumeroDias(atual->dataIni, atual->dataFim);
            float novoValorTotal = novoPrecoDiaria * numeroDias;

            atual->valorPago = novoValorTotal;
        }
        atual = atual->prox;
    }
}

    void alterar_cliente(Cliente **inicio, int idC) {
        Cliente *atual = *inicio;

        while (atual != NULL && atual->idCliente != idC) {
            atual = atual->prox;
        }

        if (atual == NULL) {
            printf("Cliente com ID %d nao encontrado.\n", idC);
            return;
        }

        int opcao;
        do{
        printf("\nCliente encontrado! O que deseja alterar?\n");
        printf("[1]Nome\n");
        printf("[2]Email\n");
        printf("[3]Data de Nascimento\n");
        printf("[0]voltar na main\n");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o novo nome: ");
                setbuf(stdin, NULL);
                gets(atual->nome);

                printf("\nnome alterado com sucesso!!!");
                break;
            case 2:
                printf("Digite o novo email: ");
                setbuf(stdin, NULL);
                gets(atual->email);
                 printf("\nemail alterado com sucesso!!!");
                break;
            case 3:
                printf("Digite o novo dia de nascimento: ");
                scanf("%d", &atual->nascimento.dia);

                printf("Digite o novo mes de nascimento: ");
                scanf("%d", &atual->nascimento.mes);

                printf("Digite o novo ano de nascimento: ");
                scanf("%d", &atual->nascimento.ano);

                 int bissexto = ehBissexto(atual->nascimento.ano);
                if (atual->nascimento.mes < 1 || atual->nascimento.mes > 12 ||
                    atual->nascimento.dia < 1 || atual->nascimento.dia > 31 ||
                    (atual->nascimento.mes == 2 && atual->nascimento.dia > 29 && bissexto) ||
                    (atual->nascimento.mes == 2 && atual->nascimento.dia > 28 && !bissexto) ||
                    ((atual->nascimento.mes == 4 || atual->nascimento.mes == 6 ||
                      atual->nascimento.mes == 9 || atual->nascimento.mes == 11) && atual->nascimento.dia > 30)) {
                    printf("\nData de nascimento invalida!\n");
                    printf("Certifique-se de que o dia, mes e ano sao validos.\n");
                } else {
                    printf("\nData alterada com sucesso!!!");
                }
                break;
            default:
                printf("Opcao invalida.\n");
                break;
        }
        }while(opcao!=0);
    }
    void alterar_quarto(Quarto **inicio, int numeroQuarto,Reserva *iniR) {
        Quarto *atual = *inicio;

        while (atual != NULL && atual->numeroQuarto != numeroQuarto) {
            atual = atual->prox;
        }

        if (atual == NULL) {
            printf("Quarto com numero %d nao encontrado.\n", numeroQuarto);
            return;
        }

        int opcao;
        do {
            printf("\nQuarto encontrado! O que deseja alterar?\n");
            printf("[1]Preco da Diaria\n");
            printf("[2]Capacidade\n");
            printf("[0]Voltar ao menu\n");
            scanf("%d", &opcao);

            switch (opcao) {
                case 1:
                    printf("Digite o novo preco da diaria: ");
                    scanf("%f", &atual->preco_diaria);
                    atualizarValorReservas(&iniR, numeroQuarto, atual->preco_diaria);
                    printf("\nPreco da diaria alterado com sucesso!!!\n");

                    break;
                case 2:
                    printf("Digite a nova capacidade: ");
                    scanf("%d", &atual->capacidade);
                    printf("\nCapacidade alterada com sucesso!!!\n");
                    break;
                case 0:
                    printf("\nRetornando ao menu...\n");
                    break;
                default:
                    printf("Opcao invalida.\n");
                    break;
            }
        } while (opcao != 0);
    }


    void altera_reserva(Reserva **inicio, int idReserva,Quarto *iniQ) {
        Reserva *atual = *inicio;
        Quarto *atuaQuarto =iniQ;
        int flag=0;
        while (atual != NULL && atual->idReserva != idReserva) {
            atual = atual->prox;
        }

        if (atual == NULL) {
            printf("Reserva com ID %d nao encontrada.\n", idReserva);
            return;
        }

        int opcao;
        do {
            printf("\nReserva encontrada! O que deseja alterar?\n");
            printf("[1]Data de Fim\n");
            printf("[2]Horario de Chegada\n");
            printf("[3]Horario de Saida\n");
            printf("[0]Voltar ao menu\n");
            scanf("%d", &opcao);

            switch (opcao) {
                case 1:
                     printf("Digite o novo dia de fim: ");
                scanf("%d", &atual->dataFim.dia);

                printf("Digite o novo mes de fim: ");
                scanf("%d", &atual->dataFim.mes);

                printf("Digite o novo ano de fim: ");
                scanf("%d", &atual->dataFim.ano);

                // Verificar se a nova data de fim é posterior à data de início
                if (compararDatas(atual->dataFim, atual->dataIni) < 0) {
                    printf("\nA nova data de fim nao pode ser anterior a data de inicio.\n");
                    break;
                }

                // Calcular a diferença de dias entre a data de início e a nova data de fim
                int numeroDias = calcularNumeroDias(atual->dataIni, atual->dataFim);
                 while (atuaQuarto != NULL) {
                    if (atuaQuarto->numeroQuarto == atual->numeroQ) {
                        // Atualizar o valor total da reserva com o preço da diária do quarto encontrado
                        int numeroDias = calcularNumeroDias(atual->dataIni, atual->dataFim);
                        float novoValorTotal = atuaQuarto->preco_diaria * numeroDias;
                        atual->valorPago = novoValorTotal;
                        printf("\nData de fim alterada com sucesso!!!\n");
                        flag = 1;
                        break;
                    }
                    atuaQuarto = atuaQuarto->prox;
                }

                    break;
                case 2:
                    printf("Digite o novo horario de chegada (hora minuto segundo): ");
                    scanf("%d %d %d", &atual->chegada.hora, &atual->chegada.min, &atual->chegada.seg);
                    printf("\nHorario de chegada alterado com sucesso!!!\n");
                    break;
                case 3:
                    printf("Digite o novo horario de saida (hora minuto segundo): ");
                    scanf("%d %d %d", &atual->saida.hora, &atual->saida.min, &atual->saida.seg);
                    printf("\nHorario de saida alterado com sucesso!!!\n");

                    break;
                case 0:
                    printf("\nRetornando ao menu...\n");
                    break;
                default:
                    printf("Opcao invalida.\n");
                    break;
            }
        } while (opcao != 0);
    }




    int main()
    {
        Cliente *iniC =NULL;
        Reserva *iniR =NULL;
        Quarto *iniQ =NULL;
        Cliente cliente;
        Reserva reserva;
        Quarto quarto;

        int sw,sw1,sw2,sw3,s4;
        int contCli=0,contRes=0;
        int re,flag=0;
        int idC,idQ,idR;

        do{
            printf("\n--------Menu--------\n");
            printf("[1]Menu Cliente\n");
            printf("[2]Menu Quarto\n");
            printf("[3]Menu Reserva\n");
            printf("[0]fechar o programa\n");
            printf("-----------------------\n");
            scanf("%d",&sw);
            switch(sw){
          case 1:
              do{
                    printf("\n--------Menu Cliente--------\n");
                    printf("[1]Registro ->Cliente\n");
                    printf("[2]Alteracao ->Cliente\n");
                    printf("[3]Exclusao ->Cliente\n");
                    printf("[4]Consulta ->Cliente\n");
                    printf("[0]Sair menu ->Cliente\n");
                    printf("-----------------------\n");
                   scanf("%d",&sw1);
                   switch(sw1){
                      case 1:
                            printf("Registo Cliente\n");
                            printf("\nDigite o id do Cliente:\n");
                            scanf("%d",&cliente.idCliente);
                            for(int i=0;i<iniC;i++){
                                if(iniC->idCliente ==cliente.idCliente){
                                    printf("id ja existente e cadastrado, digite outro!!: ");
                                    scanf("%d",&cliente.idCliente);
                                }
                            }

                            printf("Digite o nome do Cliente:\n");
                            setbuf(stdin,NULL);
                            gets(cliente.nome);
                            printf("Digite o email de contato do  cliente:\n");
                            gets(cliente.email);
                            printf("Digite o dia do nascimento:\n");
                            scanf("%d",&cliente.nascimento.dia);
                            printf("Digite o mes do nascimento:\n");
                            scanf("%d",&cliente.nascimento.mes);
                            printf("Digite o ano do nascimento:\n");
                            scanf("%d",&cliente.nascimento.ano);
                            insere_Cliente(&iniC,cliente);
                            printf("Cliente cadastrado com Sucesso!\n");

                        break;
                      case 2:
                          printf("\nALTERAR CLIENTE!!!\n");
                          printf("Digite o id do clinte que voce deseja alterar!!!\n");
                          scanf("%d",&idC);
                          for(int i=0;i<iniC;i++){
                            if(idC ==cliente.idCliente){
                                flag =1;
                                break;
                            }
                          }
                          if(flag){
                            printf("Encontrado!!, comecar alteracao...\n");
                            alterar_cliente(&iniC,idC);
                          }else{
                            while(idC !=cliente.idCliente){
                            printf("id[%d] do clinte que voce deseja alterar nao foi encontrado, digite um valor valido!!!\n",idC);
                          scanf("%d",&idC);
                            }

                          }


                        break;
                      case 3:
                           printf("Remocao de cliente:\n");
                          printf("\nDigite o id do cliente: \n");
                          scanf("%d",&cliente.idCliente);
                          remove_Cliente(&iniC,iniR,cliente.idCliente);
                          break;
                          break;
                      case 4:
                          consulta_Cliente(iniC);
                        break;
                      default:
                         printf("\nDigite um valor valido por favor!!\n");
                        break;
                   }


              }while(sw1!=0);//Cliente
            break;
        case 2:
            do{

                    printf("\n--------Menu Quarto--------\n");
                    printf("[1]Registro ->Reserva Quarto\n");
                    printf("[2]Alteracao ->Reserva Quarto\n");
                    printf("[3]Exclusao ->Reserva Quarto\n");
                    printf("[4]Consulta ->Reserva Quarto\n");
                    printf("[0]Sair menu ->Quarto\n");
                    printf("-----------------------\n");
                   scanf("%d",&sw2);
                   switch(sw2){
                      case 1:
                            printf("Registro Quarto\n");
                            printf("Digite o numero do quarto\n");
                            scanf("%d",&quarto.numeroQuarto);

                            printf("Digite a capacidade max do quarto:\n");
                            scanf("%d",&quarto.capacidade);
                            printf("Digite a diaria do quarto: ");
                            scanf("%f",&quarto.preco_diaria);
                            printf("Digite a disponibilidade do quarto: [set como 1/padrao]\n");
                            scanf("%d",&quarto.disponibilidade);
                            while (quarto.disponibilidade !=0 &&quarto.disponibilidade != 1) {
                                printf("Digite um valor valido para disponibilidade (1 para Disponivel):\n");
                                scanf("%d", &quarto.disponibilidade);
                            }
                            insere_quarto(&iniQ,quarto);
                            printf("Quarto registrado!!!!");

                        break;
                      case 2:
                          printf("\nAlterar Quarto\n");
                          printf("Digite o numero do quarto que voce deseja alterar: ");
                          scanf("%d",&idQ);
                          for(int i=0;i<iniQ;i++){
                            if(idQ ==quarto.numeroQuarto){
                                flag =1;
                                break;
                            }
                          }
                          if(flag){
                            printf("Encontrado!!, comecar alteracao...\n");
                            alterar_quarto(&iniQ, idQ,iniR);
                          }else{
                            printf("Nao Encontrado!!digite um numero de quarto valido\n");
                          }
                        break;
                      case 3:
                          printf("\nRemover quarto!!!\n");
                          printf("Digite o numero do quarto que voce deseja remover!!!\n:");
                          scanf("%d",&quarto.numeroQuarto);
                          for(int i=0; i<iniQ;i++){
                            if(quarto.numeroQuarto ==quarto.numeroQuarto){
                                flag =1;
                                break;
                            }
                          }
                          if(flag){
                            remove_quarto(&iniQ,iniR,quarto.numeroQuarto);
                          }
                          break;
                      case 4:
                          consulta_Quarto(iniQ);
                        break;
                      default:
                         printf("\nDigite um valor valido por favor!!\n");
                        break;
                   }




            }while(sw2!=0);//quarto
            break;
        case 3:
            do{


                    printf("\n--------Menu Reserva--------\n");
                    printf("[1]Registro ->Reserva\n");
                    printf("[2]Alteracao ->Reserva\n");
                    printf("[3]Exclusao->Reserva\n");
                    printf("[4]Consulta ->Reserva\n");
                    printf("[0]Sair menu ->Reserva\n");
                    printf("-----------------------\n");
                   scanf("%d",&sw3);
                   switch(sw3){
                      case 1:
                          printf("Registo Reserva\n");
                          printf("\nDigite o id da Reserva:\n");
                          scanf("%d",&reserva.idReserva);
                          for(int i=0;i<iniR;i++){
                                if(iniR->idReserva ==reserva.idReserva){
                                    printf("id ja existente e cadastrado, digite outro!!: ");
                                    scanf("%d",&reserva.idReserva);
                                }
                            }

                          printf("Digite o id do cliente: \n");
                          scanf("%d",&reserva.id_cliente);
                          while(clienteExiste(iniC,reserva)!=1){
                            printf("id de cliente nao existente!!!, Digite corretamente!!\n");
                            scanf("%d",&reserva.id_cliente);
                          }
                          //verifi quarto

                            printf("Digite a data inicio da reserva: \n");
                            scanf("%d", &reserva.dataIni.dia);
                            while (reserva.dataIni.dia < 1 || reserva.dataIni.dia > 30) {
                                printf("Digite a data inicio da reserva [1-30]: \n");
                                scanf("%d", &reserva.dataIni.dia);
                            }

                            printf("digite o mes de inicio\n");
                            scanf("%d", &reserva.dataIni.mes);
                            while (reserva.dataIni.mes < 1 || reserva.dataIni.mes > 12) {
                                printf("digite o mes de inicio [1-12]\n");
                                scanf("%d", &reserva.dataIni.mes);
                            }

                            printf("digite o ano de inicio [2023 a 2030]\n");
                            scanf("%d", &reserva.dataIni.ano);
                            while (reserva.dataIni.ano < 2023 || reserva.dataIni.ano > 2030) {
                                printf("digite o ano de inicio [2023 a 2030]\n");
                                scanf("%d", &reserva.dataIni.ano);
                            }

                          printf("Digite a data fim da reserva: \n");
                          scanf("%d",&reserva.dataFim.dia);
                          printf("digite o mes de fim\n");
                          scanf("%d",&reserva.dataFim.mes);
                          printf("digite o ano de fim\n");
                          scanf("%d",&reserva.dataFim.ano);
                            while (reserva.dataFim.ano < reserva.dataIni.ano ||
                           (reserva.dataFim.ano == reserva.dataIni.ano && reserva.dataFim.mes < reserva.dataIni.mes) ||
                           (reserva.dataFim.ano == reserva.dataIni.ano && reserva.dataFim.mes == reserva.dataIni.mes && reserva.dataFim.dia < reserva.dataIni.dia)) {
                            printf("A data de termino nao pode ser menor ou igual a data de inicio. Digite uma nova data de fim:\n");
                            printf("dia\n");
                            scanf("%d", &reserva.dataFim.dia);
                            printf("mes\n");
                            scanf("%d",&reserva.dataFim.mes);
                            printf("ano\n");
                            scanf("%d",&reserva.dataFim.ano);
                    }

                          printf("Digite o numero do quarto: \n");
                          scanf("%d",&reserva.numeroQ);
                           while(QuartoExiste(iniQ,reserva)!=1){
                            printf("esse quarto nao existe, por favor digite outro: \n");
                            scanf("%d",&reserva.numeroQ);
                           }

                           int disponivel = verificarDisponibilidade(iniR, iniQ, reserva.numeroQ, reserva.dataIni);

                            while(!disponivel) {
                                printf("Quarto não disponível para as datas solicitadas. Escolha outro quarto ou datas.\n");
                                scanf("%d",&reserva.numeroQ);

                            }
                            atualizarDisponibilidadeQuarto(iniQ,reserva.numeroQ,0);


                          printf("Digite a hora de cheking(Chegada): \n");
                          scanf("%d",&reserva.chegada.hora);
                           printf("Digite a minutos de cheking(Chegada): \n");
                          scanf("%d",&reserva.chegada.min);
                           printf("Digite a segundos de cheking(Chegada): \n");
                          scanf("%d",&reserva.chegada.seg);

                          printf("Digite a hora de cheking(saida): \n");
                          scanf("%d",&reserva.saida.hora);
                           printf("Digite a minutos de cheking(saida): \n");
                          scanf("%d",&reserva.saida.min);
                           printf("Digite a segundos de cheking(saida): \n");
                          scanf("%d",&reserva.saida.seg);
                        float total = calcularCustoReserva(iniQ, reserva.dataIni, reserva.dataFim, reserva.numeroQ);
                        reserva.valorPago = total;

                        insere_Reserva(&iniR, reserva);



                        break;
                      case 2:
                          printf("\nAlteracao\n");
                          printf("Digite o id da reserva!!\n");
                          scanf("%d",&idR);
                          for(int i=0;i<iniR;i++){
                            if(idR ==reserva.idReserva){
                                flag =1;
                                break;
                            }
                          }
                          if(flag){
                            printf("\nEncontrado!!, comeca alteracao....");
                            altera_reserva(&iniR,idR,iniQ);

                          }
                        break;
                      case 3:

                          printf("Remove reserva!!!!!\n");
                          printf("\nDigite o id da reserva que voce quer excluir :\n");
                          scanf("%d",&reserva.idReserva);
                          for(int i=0; i<iniR;i++){
                            if(reserva.idReserva==reserva.idReserva){
                                flag =1;
                                break;
                            }
                          }
                          if(flag){
                            remove_reserva(&iniR, reserva.idReserva, &iniQ);
                          }

                          break;
                      case 4:
                          consulta_Reserva(iniR);
                        break;
                      default:
                         printf("\nDigite um valor valido por favor!!\n");
                        break;
                   }


            }while(sw3!=0);//reserva
                      break;
            default:
            printf("\nDigite um valor valido por favor!!\n");
            break;



            }//primeiro menu;

        }while(sw!=0);


        return 0;
    }
