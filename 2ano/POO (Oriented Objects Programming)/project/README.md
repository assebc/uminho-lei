<h1>POO-Pratico</h1>

<h2>Funcionamento e Desenvolvimento do Trabalho</h2>
    <p>Neste repositório é visível a existência de 2(duas) diretorias, sendo elas as library utilizadas (lib) e
respetiva diretoria com o conteúdo e código de desenvolvimento (src).</p>
<p>Todo este projeto é possível ser executado através do ficheiro Main.java</p>
<p>Neste projeto obtém uma parte de Frontend realizada no GUI(View), e uma parte de backend geral em UI(Controller/View) e uma SmartCity(Model)</p>
<p>Para ajudar no planeamento e desenvolvimento do projeto recorremos ao Trello de modo a seguirmos um plano de forma mais ordeira.</p>


<h2>API da Smart City</h2>

<h3>Cidade</h3>
    <p>Cada casa contém o comercializador de energia, proprietário com o respetivo nome e NIF, Map de dispositivos por divisão.</p>
<h4>Casa</h4>
    <p>Cada smartDevice deve ser identificado por um código do fabricante proveniente de um HashMap.</p>
    <p>Vários smartDevices e todos eles foram pagos para instalar quer sejam usados ou não.</p>
    <p>Cada smartDevices regista informações de gastos elétricos.</p>
    <p>Cada dispositivo ligado a um smartdevice pode ser ligado ou desligado remotamente.</p>
    <p>Também deve ser possível desligar todos os dispositivos de uma divisão de uma só vez.</p>

    Coleção de SmartCity(Map <Set <String Morada, Integer NIF>,SmartHouse> SmartCity))
    Coleção de SmartDevices(Map(String divisao, Map <identifier,Map<SmartDevices> SmartDevs))

    Métodos de cada casa:
        Ligar e desligar todos os dispositivos
        Ligar e desligar dispositivos especificos
        Adicionar dispostivo a divisão
        Obter consumo por divisão

    SmartDevices:

        SmartBulbs:
            Três modos de cor (Neutral, Warm e Cold)
            Dimensão em centimetros
            Consumo diário
            Consumo (fórmula de cada grupo = const+tipoDeLuz)

        SmartSpeaker:
            Volume 
            Estacao 
            Marca das colunas
            Consumo Diário *
                *(fórmula de cada grupo = val_Marca_Colunas + fator_Volume_Atual (Deve ser a média diária) )

        SmartCamera:
            Resolução
            Tamanho do ficheiro onde guardam as gravações
            Consumo energético (tamanho_do_video * res_de_imagem)

<h3>Comercializantes</h3>

    Comercializadores de Energia:
        
        Time Related:
            Criar uma espécie de instância temporal (talvez var por smartDevice)
            Ligar e desligar devices só ocorre quando passa tempo
            Mudando a data, obter periodo elapsed, consumo e custo por casa
            Não é possível mudar de comercializador na mesma instância tempo
            Mudar as taxas somente quando o muda o tempo

<h3>Overall Outputs</h3>

    Queries:
        
        Quueries Estatísticas:
            Casa que gastou mais energia em determinado periodo de tempo
            Comercializador com maior faturação
    
        Outras Queries:
            Lista de faturas emitidas por comercializador
            Sort dos maiores consumidores em determinado periodo de tempo
        
