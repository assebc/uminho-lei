package exame21;

public class PodcastNaoExisteException extends Throwable{

    public PodcastNaoExisteException (String id) {
        super(id);
    }
}
