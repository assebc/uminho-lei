package EntregaFinal.src.data;

import EntregaFinal.src.SubCampeonatos.Campeonato;

import java.sql.*;
import java.util.ArrayList;
import java.util.Collection;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;

public class CampeonatoDAO implements Map<String,Campeonato> {

    private static CampeonatoDAO singleton = null;

	private CampeonatoDAO(){
		try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             Statement stm = conn.createStatement()) {
            String sql = "CREATE TABLE IF NOT EXISTS campeonatos (" +
                    "Nome varchar(45) NOT NULL PRIMARY KEY," +
                    "Nr_circuitos int DEFAULT 0," +
                    "Disponibilidade boolean DEFAULT false);";
            stm.executeUpdate(sql);
        } catch (SQLException e) {
            // Erro a criar tabela...
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
	}

	public static CampeonatoDAO getInstance() {
        if (CampeonatoDAO.singleton == null) {
            CampeonatoDAO.singleton = new CampeonatoDAO();
        }
        return CampeonatoDAO.singleton;
    }

    public static void buildInstance(){
        if (CampeonatoDAO.singleton == null) {
            CampeonatoDAO.singleton = new CampeonatoDAO();
        }
    }

	public List<Campeonato> getCampeonatosDisponiveis() {
        List<Campeonato> camps = new ArrayList<>();
        for(Campeonato c: values()){
            if (c.get_disponibilidade()) camps.add(c);
        }
        return camps;
	}

	public List<Campeonato> getCampeonatosIndisponiveis() {
		List<Campeonato> camps = new ArrayList<>();
        for(Campeonato c: values()){
            if (!c.get_disponibilidade()) camps.add(c);
        }
        return camps;
	}

	@Override
	public int size() {
		int i = 0;
        try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             Statement stm = conn.createStatement();
             ResultSet rs = stm.executeQuery("SELECT count(*) FROM campeonatos")) {
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
                     stm.executeQuery("SELECT Nome FROM campeonatos WHERE Nome='"+key.toString()+"'")) {
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
		Campeonato a = (Campeonato) value;
        return this.containsKey(a.get_nome());
	}

	@Override
	public Campeonato get(Object key) {
		Campeonato a = null;
        try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             Statement stm = conn.createStatement();
             ResultSet rs = stm.executeQuery("SELECT * FROM campeonatos WHERE Nome='"+key+"'")) {
            if (rs.next()) {  // A chave existe na tabela
                a = new Campeonato(rs.getString("Nome"),
                            Integer.parseInt(rs.getString("Nr_circuitos")),
                        Boolean.parseBoolean(rs.getString("Disponibilidade")));
            }
        } catch (SQLException e) {
            // Database error!
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
        return a;
	}

	@Override
	public Campeonato put(String key, Campeonato value) {
		Campeonato res = null;
        try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             Statement stm = conn.createStatement()) {
            try(PreparedStatement pstm = conn.prepareStatement("INSERT INTO campeonatos(Nome,Nr_circuitos,Disponibilidade)" + "VALUES (?,?,?)")) {
                pstm.setString(1,value.get_nome());
                pstm.setString(2,String.valueOf(value.get_nr_circuitos()));
                pstm.setString(3,String.valueOf(value.get_disponibilidade()));
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
	public Campeonato remove(Object key) {
		Campeonato a = this.get(key);
        try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             Statement stm = conn.createStatement()){
            // apagar o campeonato
            stm.executeUpdate("DELETE FROM campeonatos WHERE Num='"+key+"'");
        } catch (Exception e) {
            // Database error!
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
        return a;
	}

	@Override
	public void putAll(Map<? extends String, ? extends Campeonato> m) {
		for(Campeonato a : m.values()) {
            this.put(a.get_nome(), a);
        }
	}

	@Override
	public void clear() {
		try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             Statement stm = conn.createStatement()) {
            stm.executeUpdate("UPDATE campeonatos SET Campeonato=NULL");
            stm.executeUpdate("TRUNCATE campeonatos");
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
             ResultSet rs = stm.executeQuery("SELECT Nome FROM campeonatos")) { // ResultSet com os nomes de todos os campeonatos
             while (rs.next()) {
                String idt = rs.getString("Nome"); // Obtemos um nome de campeonato do ResultSet
                                   // Utilizamos o get para construir os campeonatos
                res.add(idt);                                 // Adiciona o campeonato ao resultado.
            }
        } catch (Exception e) {
            // Database error!
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
        return res;
	}

	@Override
	public Collection<Campeonato> values() {
		Collection<Campeonato> res = new HashSet<>();
        try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             Statement stm = conn.createStatement();
             ResultSet rs = stm.executeQuery("SELECT Nome FROM campeonatos")) { // ResultSet com os nomes de todos os campeonatos
            while (rs.next()) {
                String idt = rs.getString("Nome"); // Obtemos um nome de campeonato do ResultSet
                Campeonato a = this.get(idt);                    // Utilizamos o get para construir os campeonatos
                res.add(a);                                 // Adiciona o campeonato ao resultado.
            }
        } catch (Exception e) {
            // Database error!
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
        return res;
	}

	@Override
	public Set<Entry<String, Campeonato>> entrySet() {
		throw new NullPointerException("public Set<Map.Entry<String,Campeonato>> entrySet() not implemented!");
	}

}