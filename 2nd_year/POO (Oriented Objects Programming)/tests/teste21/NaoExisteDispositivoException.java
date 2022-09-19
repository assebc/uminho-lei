package teste21;

public class NaoExisteDispositivoException extends Throwable {
    public NaoExisteDispositivoException(String id) {
        super(id);
    }
}
