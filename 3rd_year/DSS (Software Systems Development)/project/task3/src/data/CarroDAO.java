package EntregaFinal.src.data;

import EntregaFinal.src.SubCarros.Carro;

import java.sql.*;
import java.util.Collection;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

public class CarroDAO implements Map<Integer,Carro> {

	private static CarroDAO singleton = null;

	private CarroDAO(){
		try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
			 Statement stm = conn.createStatement()) {
			String sql = "CREATE TABLE IF NOT EXISTS carros (" +
					"ID int NOT NULL AUTO_INCREMENT PRIMARY KEY," +
					"Marca varchar(45) DEFAULT ''," +
					"Modelo varchar(45) DEFAULT ''," +
					"Cilindrada int DEFAULT 0," +
					"Potencia int DEFAULT 0," +
					"Fiabilidade int DEFAULT 0);";
			stm.executeUpdate(sql);
		} catch (SQLException e) {
			// Erro a criar tabela...
			e.printStackTrace();
			throw new NullPointerException(e.getMessage());
		}
	}

	public static CarroDAO getInstance() {
		if (CarroDAO.singleton == null) {
			CarroDAO.singleton = new CarroDAO();
		}
		return CarroDAO.singleton;
	}

	public static void buildInstance(){
		if (CarroDAO.singleton == null) {
			CarroDAO.singleton = new CarroDAO();
		}
	}

	@Override
	public int size() {
		int i = 0;
		try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
			 Statement stm = conn.createStatement();
			 ResultSet rs = stm.executeQuery("SELECT count(*) FROM carros")) {
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
					 stm.executeQuery("SELECT Nome FROM carros WHERE Nome='"+key.toString()+"'")) {
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
		Carro a = (Carro) value;
		return this.containsKey(a.get_iD());
	}

	@Override
	public Carro get(Object key) {
		Carro a = null;
		try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
			 Statement stm = conn.createStatement();
			 ResultSet rs = stm.executeQuery("SELECT * FROM carros WHERE Nome='"+key+"'")) {
			if (rs.next()) {  // A chave existe na tabela
				a = new Carro(rs.getString("Marca"),
						rs.getString("Modelo"),
						rs.getInt("Cilindrada"),
						rs.getInt("Potencia"),
						rs.getInt("Fiabilidade"));
			}
		} catch (SQLException e) {
			// Database error!
			e.printStackTrace();
			throw new NullPointerException(e.getMessage());
		}
		return a;
	}

	@Override
	public Carro put(Integer key, Carro value) {
		Carro res = null;
		try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
			 Statement stm = conn.createStatement()) {
			try(PreparedStatement pstm = conn.prepareStatement("INSERT INTO carros(Marca,Modelo,Cilindrada,Potencia,Fiabilidade)" + "VALUES (?,?,?,?,?)")) {
				pstm.setString(1,value.get_marca());
				pstm.setString(2,value.get_modelo());
				pstm.setInt(3,value.get_cilindrada());
				pstm.setInt(4,value.get_potencia());
				pstm.setInt(5,value.get_fiabilidade());
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
	public Carro remove(Object key) {
		Carro a = this.get(key);
		try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
			 Statement stm = conn.createStatement()){
			// apagar o aluno
			stm.executeUpdate("DELETE FROM carros WHERE Num='"+key+"'");
		} catch (Exception e) {
			// Database error!
			e.printStackTrace();
			throw new NullPointerException(e.getMessage());
		}
		return a;
	}

	@Override
	public void putAll(Map<? extends Integer, ? extends Carro> m) {
		for(Carro a : m.values()) {
			this.put(a.get_iD(), a);
		}
	}

	@Override
	public void clear() {
		try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
			 Statement stm = conn.createStatement()) {
			stm.executeUpdate("UPDATE carros SET Carro=NULL");
			stm.executeUpdate("TRUNCATE carros");
		} catch (SQLException e) {
			// Database error!
			e.printStackTrace();
			throw new NullPointerException(e.getMessage());
		}
	}

	@Override
	public Set<Integer> keySet() {
		Set<Integer> res = new HashSet<>();
        try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             Statement stm = conn.createStatement();
             ResultSet rs = stm.executeQuery("SELECT Id FROM carros")) { // ResultSet com os nomes de todos os campeonatos
             while (rs.next()) {
                Integer idt = rs.getInt("Id"); // Obtemos um nome de carros do ResultSet
                res.add(idt);                                 // Adiciona o carros ao resultado.
            }
        } catch (Exception e) {
            // Database error!
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
        return res;
	}

	@Override
	public Collection<Carro> values() {
		Collection<Carro> res = new HashSet<>();
		try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
			 Statement stm = conn.createStatement();
			 ResultSet rs = stm.executeQuery("SELECT Nome FROM campeonatos")) { // ResultSet com os nomes de todos os campeonatos
			while (rs.next()) {
				String idt = rs.getString("Nome"); // Obtemos um nome de campeonato do ResultSet
				Carro a = this.get(idt);                    // Utilizamos o get para construir os campeonatos
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
	public Set<Entry<Integer, Carro>> entrySet() {
		throw new NullPointerException("public Set<Map.Entry<String,Carro>> entrySet() not implemented!");
	}
}