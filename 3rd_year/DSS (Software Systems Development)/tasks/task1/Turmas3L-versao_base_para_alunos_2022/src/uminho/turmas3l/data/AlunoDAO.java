package uminho.turmas3l.data;

import uminho.turmas3l.business.Aluno;

import java.sql.*;
import java.util.Collection;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

public class AlunoDAO implements Map<String, Aluno> {

    private static AlunoDAO singleton = null;

    private AlunoDAO() {
        try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             Statement stm = conn.createStatement()) {
            String sql = "CREATE TABLE IF NOT EXISTS alunos (" +
                    "Num varchar(10) NOT NULL PRIMARY KEY," +
                    "Nome varchar(45) DEFAULT NULL," +
                    "Email varchar(45) DEFAULT NULL)";
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
        int i = 0;
        try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             Statement stm = conn.createStatement();
             ResultSet rs = stm.executeQuery("SELECT count(*) FROM alunos")) {
            if(rs.next()) {
                i = rs.getInt(1);
            }
        }
        catch (Exception e) {
            // Erro a criar tabela...
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
        return i;
    }

    @Override
    public boolean isEmpty() {
        return this.size() == 0;
    }

    @Override
    public boolean containsKey(Object key) {
        boolean r;
        try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             Statement stm = conn.createStatement();
             ResultSet rs =
                     stm.executeQuery("SELECT Num FROM alunos WHERE Num='"+key.toString()+"'")) {
             r = rs.next();
        } catch (SQLException e) {
            // Database error!
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
        return r;
    }

    @Override
    public boolean containsValue(Object value) {
        Aluno a = (Aluno) value;
        return this.containsKey(a.getNumero());
    }

    @Override
    public Aluno get(Object key) {
        Aluno a = null;
        try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             Statement stm = conn.createStatement();
             ResultSet rs = stm.executeQuery("SELECT * FROM alunos WHERE Num='"+key+"'")) {
            if (rs.next()) {  // A chave existe na tabela
                a = new Aluno(rs.getString("Num"),
                            rs.getString("Nome"),
                        rs.getString("Email"));
            }
        } catch (SQLException e) {
            // Database error!
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
        return a;
    }

    @Override
    public Aluno put(String key, Aluno value) {
        Aluno res = null;
        try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             Statement stm = conn.createStatement()) {
            try(PreparedStatement pstm = conn.prepareStatement("INSERT INTO alunos(Num,Nome,Email)" + "VALUES (?,?,?)")) {
                pstm.setString(1,value.getNumero());
                pstm.setString(2,value.getNome());
                pstm.setString(3,value.getEmail());
                pstm.execute();
            }
        } catch (SQLException e) {
            // Database error!
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
        return res;
    }

    @Override
    public Aluno remove(Object key) {
        Aluno a = this.get(key);
        try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             Statement stm = conn.createStatement()){
            // apagar o aluno
            stm.executeUpdate("DELETE FROM alunos WHERE Num='"+key+"'");
        } catch (Exception e) {
            // Database error!
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
        return a;
    }

    @Override
    public void putAll(Map<? extends String, ? extends Aluno> m) {
        for(Aluno a : m.values()) {
            this.put(a.getNumero(), a);
        }
    }

    @Override
    public void clear() {
        try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             Statement stm = conn.createStatement()) {
            stm.executeUpdate("UPDATE alunos SET Aluno=NULL");
            stm.executeUpdate("TRUNCATE alunos");
        } catch (SQLException e) {
            // Database error!
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
    }

    @Override
    public Set<String> keySet() {
        throw new NullPointerException("Not implemented!");
    }

    @Override
    public Collection<Aluno> values() {
        Collection<Aluno> res = new HashSet<>();
        try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             Statement stm = conn.createStatement();
             ResultSet rs = stm.executeQuery("SELECT Num FROM alunos")) { // ResultSet com os numeros de todos os alunos
            while (rs.next()) {
                String idt = rs.getString("Num"); // Obtemos um numero de aluno do ResultSet
                Aluno a = this.get(idt);                    // Utilizamos o get para construir os alunos
                res.add(a);                                 // Adiciona o aluno ao resultado.
            }
        } catch (Exception e) {
            // Database error!
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
        return res;
    }

    @Override
    public Set<Entry<String, Aluno>> entrySet() {
        throw new NullPointerException("public Set<Map.Entry<String,Aluno>> entrySet() not implemented!");
    }
}
