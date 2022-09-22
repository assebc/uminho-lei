package uminho.turmas3l.data;

import uminho.turmas3l.business.Sala;

import java.sql.*;
import java.util.Collection;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

public class SalaDAO implements Map<String, Sala> {

    private static SalaDAO singleton = null;

    private SalaDAO() {
        try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             Statement stm = conn.createStatement()) {
            String sql = "CREATE TABLE IF NOT EXISTS salas (" +
                    "Num varchar(10) NOT NULL PRIMARY KEY," +
                    "Edificio varchar(45) DEFAULT NULL," +
                    "Capacidade int(4) DEFAULT 0)";
            stm.executeUpdate(sql);
        } catch (SQLException e) {
            // Erro a criar tabela...
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
    }

    public static SalaDAO getInstance() {
        if (SalaDAO.singleton == null) {
            SalaDAO.singleton = new SalaDAO();
        }
        return SalaDAO.singleton;
    }

    @Override
    public int size() {
        int i = 0;
        try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             Statement stm = conn.createStatement();
             ResultSet rs = stm.executeQuery("SELECT count(*) FROM salas")) {
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
                     stm.executeQuery("SELECT Num FROM salas WHERE Num='"+key.toString()+"'")) {
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
        Sala s = (Sala) value;
        return this.containsKey(s.getNumero());
    }

    @Override
    public Sala get(Object key) {
        Sala s = null;
        try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             Statement stm = conn.createStatement();
             ResultSet rs = stm.executeQuery("SELECT * FROM salas WHERE Num='"+key+"'")) {
            if (rs.next()) {  // A chave existe na tabela
                s = new Sala(rs.getString("Num"),
                        rs.getString("Edificio"),
                        rs.getInt("Capacidade"));
            }
        } catch (SQLException e) {
            // Database error!
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
        return s;
    }

    @Override
    public Sala put(String key, Sala value) {
        return null;
    }

    @Override
    public Sala remove(Object key) {
        Sala s = this.get(key);
        try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             Statement stm = conn.createStatement()){
            // apagar a sala
            stm.executeUpdate("DELETE FROM salas WHERE Num='"+key+"'");
        } catch (Exception e) {
            // Database error!
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
        return s;
    }

    @Override
    public void putAll(Map<? extends String, ? extends Sala> m) {
        for(Sala s: m.values()){
            this.put(s.getNumero(),s);
        }
    }

    @Override
    public void clear() {
        try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             Statement stm = conn.createStatement()) {
            stm.executeUpdate("UPDATE salas SET Sala=NULL");
            stm.executeUpdate("TRUNCATE salas");
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
    public Collection<Sala> values() {
        Collection<Sala> res = new HashSet<>();
        try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             Statement stm = conn.createStatement();
             ResultSet rs = stm.executeQuery("SELECT Num FROM salas")) { // ResultSet com os numeros de todos os alunos
            while (rs.next()) {
                String idt = rs.getString("Num"); // Obtemos um numero de sala do ResultSet
                Sala s = this.get(idt);                    // Utilizamos o get para construir as salas
                res.add(s);                                 // Adiciona a sala ao resultado.
            }
        } catch (Exception e) {
            // Database error!
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
        return res;
    }

    @Override
    public Set<Entry<String, Sala>> entrySet() {
        throw new NullPointerException("public Set<Map.Entry<String,Sala>> entrySet() not implemented!");
    }
}
