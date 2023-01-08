package task3.src.UI;

import java.util.*;

public class Menu {

    // Interfaces auxiliares

    /** Functional interface para handlers. */
    public interface Handler {
        void execute();
    }

    /** Functional interface para pré-condições. */
    public interface PreCondition {
        boolean validate();
    }

    // Varíável de classe para suportar leitura

    private static Scanner is = new Scanner(System.in);

    // Variáveis de instância

    private String titulo;                  // Titulo do menu (opcional)
    private List<String> opcoes;            // Lista de opções
    private List<PreCondition> disponivel;  // Lista de pré-condições
    private List<Handler> handlers;         // Lista de handlers

    // Construtor

    /**
     * Constructor vazio para objectos da classe Menu.
     *
     * Cria um menu vazio, ao qual se podem adicionar opções.
     */
    public Menu() {
        this.titulo = "Menu";
        this.opcoes = new ArrayList<>();
        this.disponivel = new ArrayList<>();
        this.handlers = new ArrayList<>();
    }

    /**
     * Constructor para objectos da classe Menu.
     *
     * Cria um menu de opções sem event handlers.
     * Utilização de listas é útil para definir menus dinâmicos.
     *
     * @param titulo O titulo do menu
     * @param opcoes Uma lista de Strings com as opções do menu.
     */
    public Menu(String titulo, List<String> opcoes) {
        this.titulo = titulo;
        this.opcoes = new ArrayList<>(opcoes);
        this.disponivel = new ArrayList<>();
        this.handlers = new ArrayList<>();
        this.opcoes.forEach(s-> {
            this.disponivel.add(()->true);
            this.handlers.add(()->System.out.println("\nATENÇÃO: Opção não implementada!"));
        });
    }

    /**
     * Constructor para objectos da classe Menu.
     *
     * Cria um menu de opções sem event handlers.
     * Utilização de listas é útil para definir menus estáticos. P.e.:
     * Utilização de listas é útil para definir menus dinâmicos.
     *
     * @param opcoes Uma lista de Strings com as opções do menu.
     */
    public Menu(List<String> opcoes) { this("Menu", opcoes); }

    /**
     * Constructor para objectos da classe Menu.
     *
     * Cria um menu de opções sem event handlers.
     * Utilização de arrays é útil para definir menus estáticos. P.e.:
     *
     * new Menu(String[]{
     *     "Opção 1",
     *     "Opção 2",
     *     "Opção 3"
     * })
     *
     * @param titulo O titulo do menu
     * @param opcoes Um array de Strings com as opções do menu.
     */
    public Menu(String titulo, String[] opcoes) {
        this(titulo, Arrays.asList(opcoes));
    }

    /**
     * Constructor para objectos da classe Menu.
     *
     * Cria um menu de opções sem event handlers.
     * Utilização de arrays é útil para definir menus estáticos. P.e.:
     *
     * new Menu(String[]{
     *     "Opção 1",
     *     "Opção 2",
     *     "Opção 3"
     * })
     *
     * @param opcoes Um array de Strings com as opções do menu.
     */
    public Menu(String[] opcoes) {
        this(Arrays.asList(opcoes));
    }

    // Métodos de instância

    /**
     * Adicionar opções a um Menu.
     *
     * @param name A opção a apresentar.
     * @param p A pré-condição da opção.
     * @param h O event handler para a opção.
     */
    public void option(String name, PreCondition p, Handler h) {
        this.opcoes.add(name);
        this.disponivel.add(p);
        this.handlers.add(h);
    }

    /**
     * Correr o menu uma vez.
     */
    public void runOnce() {
        int op;
        show();
        op = readOption();
        // testar pré-condição
        if (op>0 && !this.disponivel.get(op-1).validate()) {
            System.out.println("Opção indisponível!");
        } else if (op>0) {
            // executar handler
            this.handlers.get(op-1).execute();
        }
    }

    /**
     * Correr o menu multiplas vezes.
     *
     * Termina com a opção 0 (zero).
     */
    public void run() {
        int op;
        do {
            show();
            op = readOption();
            // testar pré-condição
            if (op>0 && !this.disponivel.get(op-1).validate()) {
                System.out.println("Opção indisponível! Tente novamente.");
            } else if (op>0) {
                // executar handler
                this.handlers.get(op-1).execute();
            }
        } while (op != 0);
    }

    /**
     * Método que regista uma uma pré-condição numa opção do menu.
     *
     * @param i índice da opção (começa em 1)
     * @param b pré-condição a registar
     */
    public void setPreCondition(int i, PreCondition b) {
        this.disponivel.set(i-1,b);
    }

    /**
     * Método para registar um handler numa opção do menu.
     *
     * @param i indice da opção  (começa em 1)
     * @param h handlers a registar
     */
    public void setHandler(int i, Handler h) {
        this.handlers.set(i-1, h);
    }

    // Métodos auxiliares

    /** Apresentar o menu */
    private void show() {
        System.out.println("\n *** "+this.titulo+" *** ");
        for (int i=0; i<this.opcoes.size(); i++) {
            System.out.print(i+1);
            System.out.print(" - ");
            System.out.println(this.disponivel.get(i).validate()?this.opcoes.get(i):"---");
        }
        System.out.println("0 - Sair");
    }

    /** Ler uma opção válida */
    private int readOption() {
        int op;

        System.out.print("Opção: ");
        try {
            String line = is.nextLine();
            op = Integer.parseInt(line);
        }
        catch (NumberFormatException e) { // Não foi inscrito um int
            op = -1;
        }
        if (op<0 || op>this.opcoes.size()) {
            System.out.println("Opção Inválida!!!");
            op = -1;
        }
        return op;
    }
}