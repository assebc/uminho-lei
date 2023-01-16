package EntregaFinal.src.data;

import java.sql.*;
import java.util.Collection;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;

import EntregaFinal.src.SubContas.Conta;
import EntregaFinal.src.SubContas.userType;

public class ContasDAO implements Map<String,Conta> {

	private static ContasDAO singleton = null;

	private ContasDAO(){
		try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
			 Statement stm = conn.createStatement()) {
			String sql = "CREATE TABLE IF NOT EXISTS contas (" +
					"Nome varchar(45) NOT NULL PRIMARY KEY," +
					"Password varchar(45) NOT NULL," +
					"Tipo int DEFAULT " + userType.JogadorBase.num + "," +
					"Pontos int DEFAULT 0);";
			stm.executeUpdate(sql);
		} catch (SQLException e) {
			// Erro a criar tabela...
			e.printStackTrace();
			throw new NullPointerException(e.getMessage());
		}
	}

	public static ContasDAO getInstance() {
		if (ContasDAO.singleton == null) {
			ContasDAO.singleton = new ContasDAO();
		}
		return ContasDAO.singleton;
	}


	public static void buildInstance() {
		if (ContasDAO.singleton == null) {
			ContasDAO.singleton = new ContasDAO();
		}
	}

	@Override
	public int size() {
		int i = 0;
		try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
			 Statement stm = conn.createStatement();
			 ResultSet rs = stm.executeQuery("SELECT count(*) FROM contas")) {
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
					 stm.executeQuery("SELECT Nome FROM contas WHERE Nome='"+key.toString()+"'")) {
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
		Conta c = (Conta) value;
		return this.containsKey(c.get_nome());
	}

	@Override
	public Conta get(Object key) {
		Conta a = null;
		try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
			 Statement stm = conn.createStatement();
			 ResultSet rs = stm.executeQuery("SELECT * FROM contas WHERE Nome='"+key+"'")) {
			if (rs.next()) {  // A chave existe na tabela
				a = new Conta(rs.getString("Nome"),
						rs.getString("Password"),
						userType.fromInt(rs.getInt("Tipo")),
						rs.getInt("Pontos"));
			}
		} catch (SQLException e) {
			// Database error!
			e.printStackTrace();
			throw new NullPointerException(e.getMessage());
		}
		return a;
	}

	@Override
	public Conta put(String key, Conta value) {
		Conta res = null;
		try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
			 Statement stm = conn.createStatement()) {
			try(PreparedStatement pstm = conn.prepareStatement("INSERT INTO contas(Nome,Password,Tipo,Pontos)" + "VALUES (?,?,?,?)")) {
				pstm.setString(1,value.get_nome());
				pstm.setString(2,value.get_password());
				pstm.setInt(3, value.get_type().num);
				pstm.setInt(4,value.get_pontos());
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
	public Conta remove(Object key) {
		Conta a = this.get(key);
		try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
			 Statement stm = conn.createStatement()){

			stm.executeUpdate("DELETE FROM contas WHERE Nome='"+key+"'");
		} catch (Exception e) {
			// Database error!
			e.printStackTrace();
			throw new NullPointerException(e.getMessage());
		}
		return a;
	}

	@Override
	public void putAll(Map<? extends String, ? extends Conta> m) {
		for(Conta a : m.values()) {
			this.put(a.get_nome(), a);
		}
	}

	@Override
	public void clear() {
		try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
			 Statement stm = conn.createStatement()) {
			stm.executeUpdate("UPDATE contas SET Contas=NULL");
			stm.executeUpdate("TRUNCATE contas");
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
                String idt = rs.getString("Nome"); // Obtemos um nome de contas do ResultSet
                res.add(idt);                                 // Adiciona o contas ao resultado.
            }
        } catch (Exception e) {
            // Database error!
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
        return res;
	}

	@Override
	public Collection<Conta> values() {
		Collection<Conta> res = new HashSet<>();
		try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
			 Statement stm = conn.createStatement();
			 ResultSet rs = stm.executeQuery("SELECT Nome FROM contas")) { // ResultSet com os nomes de todos as contas
			while (rs.next()) {
				String idt = rs.getString("Nome"); // Obtemos um nome de conta do ResultSet
				Conta a = this.get(idt);                    // Utilizamos o get para construir as contas
				res.add(a);                                 // Adiciona a conta ao resultado.
			}
		} catch (Exception e) {
			// Database error!
			e.printStackTrace();
			throw new NullPointerException(e.getMessage());
		}
		return res;
	}

	@Override
	public Set<Entry<String, Conta>> entrySet() {
		throw new NullPointerException("public Set<Map.Entry<String,Campeonato>> entrySet() not implemented!");
	}
}