/**
 * Classe que implementa um Ponto num plano2D.
 * As coordenadas do Ponto sao inteiras.
 *
 * @author  MaterialPOO
 * @version 20180212
 * @version 20210305
 * @version 20220314
 */
public class Ponto {
    
  //variaveis de instancia
  private int x;
  private int y;
  
  /**
   * Construtores da classe Ponto.
   * Declaraçao dos construtores por omissao (vazio),
   * parametrizado e de copia.
   */
  
  /**
   * Construtor por omissao de Ponto.
   */
  public Ponto() {
    this.x = 0;  
    this.y = 0;
  }
  
  /**
   * Construtor parametrizado de Ponto.
   * Aceita como parametros os valores para cada coordenada.
   */
  public Ponto(int x, int y) {
    this.x = x;
    this.y = y;
  }
  
  public Ponto(int cx) {
    this.x = cx;
    this.y = 0;
  }
  
  
  /**
   * Construtor de copia de Ponto.
   * Aceita como parametro outro Ponto e utiliza os metodos
   * de acesso aos valores das variaveis de instancia.
   */
  public Ponto(Ponto umPonto) {
    this.x = umPonto.getX();   // this.x = umPonto.x; -- nao faz parte do alfabeto definido
    this.y = umPonto.getY();
  }
  
  /**
   * metodos de instancia
   */
  
  /**
   * Devolve o valor da coordenada em x.
   * 
   * @return valor da coordenada x.
   */
  public int getX() {
    return this.x;
  }
  
  /**
   * Devolve o valor da coordenada em y.
   * 
   * @return valor da coordenada y.
   */
  public int getY() {
    return this.y;
  }
  
  /**
   * Actualiza o valor da coordenada em x.
   * 
   * @param novoX novo valor da coordenada em X
   */
  public void setX(int novoX) {
    this.x = novoX;
  }
  
  /**
   * Actualiza o valor da coordenada em y.
   * 
   * @param novoY novo valor da coordenada em Y
   */
  public void setY(int novoY) {
    this.y = novoY;
  }
  
  /**
   * Metodo que desloca um ponto somando um delta às coordenadas
   * em x e y.
   * 
   * @param deltaX valor de deslocamento do x
   * @param deltaY valor de deslocamento do y
   */
  public void deslocamento(int deltaX, int deltaY) {
    this.x += deltaX;
    this.y += deltaY;
  }
  
  /**
   * Metodo que soma as componentes do Ponto passado como parametro.
   * @param umPonto ponto que é somado ao ponto receptor da mensagem.
   */
  public void somaPonto(Ponto umPonto) {
    this.x += umPonto.getX();
    this.y += umPonto.getY();
  }
  
  /**
   * Metodo que move o Ponto para novas coordenadas.
   * @param novoX novo valor de x.
   * @param novoY novo valor de y.
   */
  public void movePonto(int cx, int cy) {
    this.x = cx;  // ou setX(cx)
    this.y = cy;  // ou this.setY(cy)
  }
  
  /**
   * Metodo que determina se o ponto estao no quadrante positivo de x e y
   * @return booleano que é verdadeiro se x>0 e y>0
   */
  public boolean ePositivo() {
    return (this.x > 0 && this.y > 0);
  }
  
  /**
   * Metodo que determina a distancia de um Ponto a outro. 
   * Determina a distancia entre this e o ponto passado por parametro.
   * 
   * 
   * @param umPonto ponto ao qual se quer determinar a distÃ¢ncia
   * @return double com o valor da distÃ¢ncia
   */
  public double distancia(Ponto umPonto) {      
      
    return Math.sqrt(Math.pow(this.x - umPonto.getX(), 2) +
                     Math.pow(this.y - umPonto.getY(), 2));
  }
  
  
  /**
   * Metodo que determina se dois pontos sÃ£o iguais.
   * @return booleano que Ã© verdadeiro se os valores das duas 
   * coordenadas forem iguais
   */
  public boolean iguais(Ponto umPonto) {
    return (this.x == umPonto.getX() && this.y == umPonto.getY());
  }   
  
  
  /**
   * Metodo que determina se o mÃ³dulo das duas coordenadas Ã© o mesmo.
   * @return true, se as coordenadas em x e y 
   * forem iguais em valor absoluto.
   */
  private boolean xIgualAy() {
    return (Math.abs(this.x) == Math.abs(this.y));
  }
  
  /**
   * Metodo que devolve a representaçao em String do Ponto.
   * @return String com as coordenadas x e y
   */
  public String toString() {
    return "Ponto: --> Cx = " + this.x + " -  Cy = " + this.y;
  }
  
  public boolean equals(Object o) {
    if (this == o)
      return true;
    if ((o == null) || (this.getClass() != o.getClass()))
      return false;
    Ponto p = (Ponto) o;
    return (this.x == p.getX() && this.y == p.getY());
      
  }
  
  
  /**
   * Metodo que faz uma copia do objecto receptor da mensagem.
   * Para tal invoca o construtor de copia.
   * 
   * @return objecto clone do objecto que recebe a mensagem.
   */
  
  public Ponto clone() {
    return new Ponto(this);    
  }    
}