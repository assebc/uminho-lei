package uminho.turmas3l.data;

import uminho.turmas3l.business.Aluno;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.Collection;
import java.util.Map;
import java.util.Set;

public class AlunoDAO implements Map<String, Aluno> {

    private static AlunoDAO singleton = null;

    private AlunoDAO() {
        try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             Statement stm = conn.createStatement()) {
            String sql = "CREATE TABLE IF NOT EXISTS alunos (" +
                    "Numero int(10) NOT NULL PRIMARY KEY," +
                    "Nome varchar(10) DEFAULT NULL," +
                    "Email varchar(20) DEFAULT NULL)";
            stm.executeUpdate(sql);
            sql = "CREATE TABLE IF NOT EXISTS alunos (" +
                    "Num varchar(10) NOT NULL PRIMARY KEY," +
                    "Nome varchar(45) DEFAULT NULL," +
                    "Email varchar(45) DEFAULT NULL," +
                    "Turma varchar(10), foreign key(Turma) references turmas(Id))";
            stm.executeUpdate(sql);
        } catch (SQLException e) {
            // Erro a criar tabela...
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
    }

    public static AlunoDAO getInstance() {
        if (AlunoDAO.singleton == null) {
            AlunoDAO.singleton = new AlunoDAO();
        }
        return AlunoDAO.singleton;
    }

    @Override
    public int size() {
        return 0;
    }

    @Override
    public boolean isEmpty() {
        return false;
    }

    @Override
    public boolean containsKey(Object key) {
        return false;
    }

    @Override
    public boolean containsValue(Object value) {
        return false;
    }

    @Override
    public Aluno get(Object key) {
        return null;
    }

    @Override
    public Aluno put(String key, Aluno value) {
        return null;
    }

    @Override
    public Aluno remove(Object key) {
        return null;
    }

    @Override
    public void putAll(Map<? extends String, ? extends Aluno> m) {

    }

    @Override
    public void clear() {

    }

    @Override
    public Set<String> keySet() {
        return null;
    }

    @Override
    public Collection<Aluno> values() {
        return null;
    }

    @Override
    public Set<Entry<String, Aluno>> entrySet() {
        return null;
    }
}
