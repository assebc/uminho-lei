interface Votacao{

    boolean verifica(int identidade);
    int esperaPorCabine();
    void vota(int escolha);
    void desocupaCabine(int i);

    int vencedor(); // apenas para a alínea de Valorização
}