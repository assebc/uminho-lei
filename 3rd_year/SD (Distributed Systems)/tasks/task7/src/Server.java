import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.HashMap;
import java.util.concurrent.locks.ReentrantLock;
import java.io.DataInputStream;
import static java.util.Arrays.asList;


class ContactManager {
    private HashMap<String, Contact> contacts;
    private ReentrantLock lck = new ReentrantLock();

    public ContactManager() {
        contacts = new HashMap<>();
        // example pre-population
        this.update(new Contact("John", 20, 253123321, null, asList("john@mail.com")));
        this.update(new Contact("Alice", 30, 253987654, "CompanyInc.", asList("alice.personal@mail.com", "alice.business@mail.com")));
        this.update(new Contact("Bob", 40, 253123456, "Comp.Ld", asList("bob@mail.com", "bob.work@mail.com")));
    }
    public void update(Contact c) {
        try {
            lck.lock();
            contacts.put(c.name(), c);
        }
        finally {
            lck.unlock();
        }
    }

}

class ServerWorker implements Runnable {
    private Socket socket;
    private ContactManager manager;

    public ServerWorker (Socket socket, ContactManager manager) {
        this.socket = socket;
        this.manager = manager;
    }

    @Override
    public void run() {
        try {
            DataInputStream in = new DataInputStream(socket.getInputStream());

            while (true) {
                Contact c = Contact.deserialize(in);
                System.out.println(c);
                this.manager.update(c);
            }
        }
        catch (IOException e) {
            e.printStackTrace();
        }
    }
}



public class Server {

    public static void main (String[] args) throws IOException {
        try (ServerSocket serverSocket = new ServerSocket(12345)) {
            ContactManager manager = new ContactManager();

            while (true) {
                Socket socket = serverSocket.accept();
                Thread worker = new Thread(new ServerWorker(socket, manager));
                worker.start();
            }
        }
    }

}
