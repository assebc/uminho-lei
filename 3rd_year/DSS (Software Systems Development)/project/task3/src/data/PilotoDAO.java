package EntregaFinal.src.data;

import java.sql.*;
import java.util.Collection;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

import EntregaFinal.src.SubPilotos.Piloto;

public class PilotoDAO implements Map<String,Piloto> {

	private static PilotoDAO singleton = null;

	private PilotoDAO(){
		try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             Statement stm = conn.createStatement()) {
            String sql = "CREATE TABLE IF NOT EXISTS pilotos (" +
                    "Nome varchar(45) NOT NULL PRIMARY KEY," +
                    "Cts float DEFAULT 0," +
					"Sva float DEFAULT 0);";
            stm.executeUpdate(sql);
        } catch (SQLException e) {
            // Erro a criar tabela...
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
	}

	public static PilotoDAO getInstance() {
        if (PilotoDAO.singleton == null) {
            PilotoDAO.singleton = new PilotoDAO();
        }
        return PilotoDAO.singleton;
    }

    public static void buildInstance(){
        if (PilotoDAO.singleton == null) {
            PilotoDAO.singleton = new PilotoDAO();
        }
    }

	public int hashCode() {
		int lHashCode = 0;
		if ( lHashCode == 0 ) {
			lHashCode = super.hashCode();
		}
		return lHashCode;
	}

	@Override
	public int size() {
		int i = 0;
        try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             Statement stm = conn.createStatement();
             ResultSet rs = stm.executeQuery("SELECT count(*) FROM pilotos")) {
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
                     stm.executeQuery("SELECT Nome FROM pilotos WHERE Nome='"+key.toString()+"'")) {
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
		Piloto a = (Piloto) value;
        return this.containsKey(a.get_nome());
	}

	@Override
	public Piloto get(Object key) {
		Piloto a = null;
        try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             Statement stm = conn.createStatement();
             ResultSet rs = stm.executeQuery("SELECT * FROM pilotos WHERE Nome='"+key+"'")) {
            if (rs.next()) {  // A chave existe na tabela
                a = new Piloto(rs.getString("Nome"),
							rs.getFloat("Cts"),
							rs.getFloat("Sva"));
            }
        } catch (SQLException e) {
            // Database error!
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
        return a;
	}

	@Override
	public Piloto put(String key, Piloto value) {
		Piloto res = null;
        try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             Statement stm = conn.createStatement()) {
            try(PreparedStatement pstm = conn.prepareStatement("INSERT INTO pilotos(Nome,Cts,Sva)" + "VALUES (?,?,?)")) {
                pstm.setString(1,value.get_nome());
                pstm.setFloat(2,value.get_cts());
                pstm.setFloat(3,value.get_sva());
                pstm.execute();
            }
            res = value;
        } catch (SQLException e) {
            // Database error!
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
        return res;
	}

	@Override
	public Piloto remove(Object key) {
		Piloto a = this.get(key);
        try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             Statement stm = conn.createStatement()){
            // apagar o aluno
            stm.executeUpdate("DELETE FROM pilotos WHERE Nome='"+key+"'");
        } catch (Exception e) {
            // Database error!
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
        return a;
	}

	@Override
	public void putAll(Map<? extends String, ? extends Piloto> m) {
			for(Piloto a : m.values()) {
				this.put(a.get_nome(), a);
			}
	}

	@Override
	public void clear() {
		try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             Statement stm = conn.createStatement()) {
            stm.executeUpdate("UPDATE pilotos SET Piloto=NULL");
            stm.executeUpdate("TRUNCATE pilotos");
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
             ResultSet rs = stm.executeQuery("SELECT Nome FROM pilotos")) { // ResultSet com os nomes de todos os campeonatos
             while (rs.next()) {
                String idt = rs.getString("Nome"); // Obtemos um nome de piloto do ResultSet
                res.add(idt);                                 // Adiciona o piloto ao resultado.
            }
        } catch (Exception e) {
            // Database error!
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
        return res;
	}

	@Override
	public Collection<Piloto> values() {
		Collection<Piloto> res = new HashSet<>();
        try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             Statement stm = conn.createStatement();
             ResultSet rs = stm.executeQuery("SELECT Nome FROM pilotos")) { // ResultSet com os nomes de todos os circuitos
            while (rs.next()) {
                String idt = rs.getString("Nome"); // Obtemos um nome de circuito do ResultSet
                Piloto a = this.get(idt);                    // Utilizamos o get para construir os circuitos
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
	public Set<Entry<String, Piloto>> entrySet() {
		return null;
	}
}