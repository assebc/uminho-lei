package task3.src.data;

import java.sql.*;
import java.util.*;

import task3.src.SubCampeonatos.Circuito;

public class CircuitoDAO implements Map<String,Circuito> {

	private static CircuitoDAO singleton = null;

	private CircuitoDAO(){
		try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             Statement stm = conn.createStatement()) {
            String sql = "CREATE TABLE IF NOT EXISTS circuitos (" +
                    "Nome varchar(45) NOT NULL PRIMARY KEY," +
                    "Nr_voltas int DEFAULT 0," +
					"Nr_curvas int DEFAULT 0," +
					"Nr_chicanes int DEFAULT 0);";
            stm.executeUpdate(sql);
        } catch (SQLException e) {
            // Erro a criar tabela...
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
	}

	public static CircuitoDAO getInstance() {
        if (CircuitoDAO.singleton == null) {
            CircuitoDAO.singleton = new CircuitoDAO();
        }
        return CircuitoDAO.singleton;
    }


    public static void buildInstance() {
        if (CircuitoDAO.singleton == null) {
            CircuitoDAO.singleton = new CircuitoDAO();
        }
    }

	@Override
	public int size() {
		int i = 0;
        try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             Statement stm = conn.createStatement();
             ResultSet rs = stm.executeQuery("SELECT count(*) FROM circuitos")) {
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
                     stm.executeQuery("SELECT Nome FROM circuitos WHERE Nome='"+key.toString()+"'")) {
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
		Circuito a = (Circuito) value;
        return this.containsKey(a.get_nome());
	}

	@Override
	public Circuito get(Object key) {
		Circuito a = null;
        try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             Statement stm = conn.createStatement();
             ResultSet rs = stm.executeQuery("SELECT * FROM circuitos WHERE Nome='"+key+"'")) {
            if (rs.next()) {  // A chave existe na tabela
                a = new Circuito(rs.getString("Nome"),
                            Integer.parseInt(rs.getString("Nr_voltas")),
							Integer.parseInt(rs.getString("Nr_curvas")),
							Integer.parseInt(rs.getString("Nr_chicanes")));
            }
        } catch (SQLException e) {
            // Database error!
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
        return a;
	}

	@Override
	public Circuito put(String key, Circuito value) {
		Circuito res = null;
        try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             Statement stm = conn.createStatement()) {
            try(PreparedStatement pstm = conn.prepareStatement("INSERT INTO circuitos(Nome,Nr_voltas,Nr_curvas,Nr_chicanes)" + "VALUES (?,?,?,?)")) {
                pstm.setString(1,value.get_nome());
                pstm.setString(2,String.valueOf(value.get_nr_voltas()));
                pstm.setString(3,String.valueOf(value.get_nr_curvas()));
				pstm.setString(4,String.valueOf(value.get_nr_chicanes()));
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
	public Circuito remove(Object key) {
		Circuito a = this.get(key);
        try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             Statement stm = conn.createStatement()){
            // apagar o aluno
            stm.executeUpdate("DELETE FROM circuitos WHERE Nome='"+key+"'");
        } catch (Exception e) {
            // Database error!
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
        return a;
	}

	@Override
	public void putAll(Map<? extends String, ? extends Circuito> m) {
		for(Circuito a : m.values()) {
            this.put(a.get_nome(), a);
        }
	}

	@Override
	public void clear() {
		try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             Statement stm = conn.createStatement()) {
            stm.executeUpdate("UPDATE circuitos SET Circuito=NULL");
            stm.executeUpdate("TRUNCATE circuitos");
        } catch (SQLException e) {
            // Database error!
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
	}

	@Override
	public Set<String> keySet() {
		Set<String> res = new HashSet<>();
        try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             Statement stm = conn.createStatement();
             ResultSet rs = stm.executeQuery("SELECT Nome FROM circuitos")) { // ResultSet com os nomes de todos os campeonatos
             while (rs.next()) {
                String idt = rs.getString("Nome"); // Obtemos um nome de circuito do ResultSet
                res.add(idt);                                 // Adiciona o circuito ao resultado.
            }
        } catch (Exception e) {
            // Database error!
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
        return res;
	}

	@Override
	public Collection<Circuito> values() {
		Collection<Circuito> res = new HashSet<>();
        try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             Statement stm = conn.createStatement();
             ResultSet rs = stm.executeQuery("SELECT Nome FROM circuitos")) { // ResultSet com os nomes de todos os circuitos
            while (rs.next()) {
                String idt = rs.getString("Nome"); // Obtemos um nome de circuito do ResultSet
                Circuito a = this.get(idt);                    // Utilizamos o get para construir os circuitos
                res.add(a);                                 // Adiciona o circuito ao resultado.
            }
        } catch (Exception e) {
            // Database error!
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
        return res;
	}

	@Override
	public Set<Entry<String, Circuito>> entrySet() {
		throw new NullPointerException("public Set<Map.Entry<String,Circuito>> entrySet() not implemented!");
	}
}