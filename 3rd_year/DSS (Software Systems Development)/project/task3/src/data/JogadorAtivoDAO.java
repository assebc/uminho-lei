package task3.src.data;

import java.util.Collection;
import java.util.HashSet;
import java.util.Map;
import java.util.Set;
import java.sql.*;

import task3.src.SubSimulacao.DadosJogador;
import task3.src.SubSimulacao.JogadorAtivo;

public class JogadorAtivoDAO implements Map<JogadorAtivoKey,JogadorAtivo> {

	private static JogadorAtivoDAO singleton = null;

	private JogadorAtivoDAO(){
		try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             Statement stm = conn.createStatement()) {
            conn.setAutoCommit(false);

            String sql = "CREATE TABLE IF NOT EXISTS dados_jogador (" +
                "DadosJogadorId int NOT NULL AUTO_INCREMENT," +
                "CampeonatoAtivoId int NOT NULL," +
                "JogadorId varchar(45) NOT NULL," +
                "CarroId varchar(45) NOT NULL," +
                "PilotoId varchar(45) NOT NULL," +
                "FOREIGN KEY (CarroId) REFERENCES carros(ID)," +
                "FOREIGN KEY (PilotoId) REFERENCES pilotos(Nome)," +
                "FOREIGN KEY (CampeonatoAtivoId) REFERENCES campeonatos_ativos(CampeonatoAtivoId)," +
                "PRIMARY KEY(DadosJogadorId, JogadorId));";

            stm.execute(sql);

            sql = "CREATE TABLE IF NOT EXISTS jogador_ativo (" +
                "CampeonatoAtivoId int NOT NULL," +
                "JogadorId varchar(45) NOT NULL," +
                "DadosJogadorId int NOT NULL," +
                "Pronto boolean DEFAULT false," +
                "NrAfinacoes int DEFAULT 0," +
                "FOREIGN KEY (JogadorId, DadosJogadorId) REFERENCES dados_jogador(JogadorId, DadosJogadorId)," +
                "FOREIGN KEY (CampeonatoAtivoId) REFERENCES campeonatos_ativos(CampeonatoAtivoId)," +
                "PRIMARY KEY(JogadorId, CampeonatoAtivoId));";

            stm.execute(sql);

            conn.commit();
        } catch (SQLException e) {
            // Erro a criar tabela...
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
	}

	public static JogadorAtivoDAO getInstance() {
        if (JogadorAtivoDAO.singleton == null) {
            JogadorAtivoDAO.singleton = new JogadorAtivoDAO();
        }
        return JogadorAtivoDAO.singleton;
    }

    public static void buildInstance(){
        if (JogadorAtivoDAO.singleton == null) {
            JogadorAtivoDAO.singleton = new JogadorAtivoDAO();
        }
    }

	@Override
	public int size() {
		int i = 0;
        try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             Statement stm = conn.createStatement();
             ResultSet rs = stm.executeQuery("SELECT count(*) FROM jogadores_ativos")) {
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
        JogadorAtivoKey keyC = (JogadorAtivoKey) key;
        String sql = "SELECT Nome FROM jogadores_ativos WHERE CampeonatoAtivoId='"+keyC.campeonatoAtivoId()+
                "' AND JogadorId='" + keyC.jogadorId() + "';";
        try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             Statement stm = conn.createStatement();
             ResultSet rs =
                     stm.executeQuery(sql)) {
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
		JogadorAtivo a = (JogadorAtivo) value;
        return this.containsKey(new JogadorAtivoKey(a.getCampeonatoAtivoId(), a.get_dados().get_jogadorID()));
	}

	@Override
	public JogadorAtivo get(Object key) {
		JogadorAtivo a = null;
        JogadorAtivoKey keyC = (JogadorAtivoKey) key;
        String sql = "SELECT * FROM jogadores_ativos" +
                "NATURAL JOIN dados_jogador" +
                "WHERE CampeonatoAtivoId='"+keyC.campeonatoAtivoId()+"' AND JogadorId='"+keyC.jogadorId()+"';";

        try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             Statement stm = conn.createStatement();
             ResultSet rs = stm.executeQuery(sql)) {
            if (rs.next()) {  // A chave existe na tabela
                DadosJogador dj = new DadosJogador(
                        rs.getString("JogadorId"),
                        CarroDAO.getInstance().get(rs.getString("CarroId")),
                        PilotoDAO.getInstance().get(rs.getString("PilotoId")),
                        rs.getInt("DadosJogadorId")
                );
                a = new JogadorAtivo(
                        dj,
                        rs.getBoolean("Pronto"),
                        rs.getInt("NrAfinacoes"),
                        rs.getInt("CampeonatoAtivoId")
                );
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        return a;
	}

	@Override
	public JogadorAtivo put(JogadorAtivoKey key, JogadorAtivo value) {
		JogadorAtivo res = null;
        try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             Statement stm = conn.createStatement()) {
            conn.setAutoCommit(false);

            DadosJogador dj = value.get_dados();
            String sql = "INSERT INTO dados_jogador VALUES ("+dj.getId()+","+key.campeonatoAtivoId()+","+
                    dj.get_jogadorID()+","+dj.get_carro().get_iD()+","+dj.get_piloto().get_nome()+");";

            stm.executeUpdate(sql);

            sql = "INSERT INTO jogador_ativo ("+value.getCampeonatoAtivoId()+","+dj.get_jogadorID()+","+
                    value.get_pronto()+","+value.get_nAfinaçoes()+");";

            stm.executeUpdate(sql);

            conn.commit();
            res = value;
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        return res;
	}

	@Override
	public JogadorAtivo remove(Object key) {
		JogadorAtivo a = this.get(key);
        JogadorAtivoKey keyC = (JogadorAtivoKey) key;
        try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             Statement stm = conn.createStatement()){
            conn.setAutoCommit(false);

            // se calhar n removemos os DadosJogador associados aqui?
            // apagar o JogadorAtivo
            stm.executeUpdate("DELETE FROM jogadores_ativos WHERE CampeonatoAtivoId='"+keyC.campeonatoAtivoId()
                    +"'"+" AND JogadorId='"+keyC.jogadorId()+"';");
            conn.commit();
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
        return a;
	}

	@Override
	public void putAll(Map<? extends JogadorAtivoKey, ? extends JogadorAtivo> m) {
		for(JogadorAtivo a : m.values()) {
            this.put(new JogadorAtivoKey(a.getCampeonatoAtivoId(), a.get_dados().get_jogadorID()), a);
        }
	}

	@Override
	public void clear() {
		try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
		Statement stm = conn.createStatement()) {
	   stm.executeUpdate("UPDATE jogadores_ativos SET JogadoresAtivo=NULL");
	   stm.executeUpdate("TRUNCATE jogadores_ativos");
   } catch (SQLException e) {
	   // Database error!
	   e.printStackTrace();
	   throw new NullPointerException(e.getMessage());
   }
	}

	@Override
	public Set<JogadorAtivoKey> keySet() {
		Set<JogadorAtivoKey> res = new HashSet<>();
        try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             Statement stm = conn.createStatement();
             ResultSet rs = stm.executeQuery("SELECT (CampeonatoAtivoId,JogadorId) FROM jogadores_ativos;")) { // ResultSet com os nomes de todos os campeonatos
             while (rs.next()) {
                res.add(new JogadorAtivoKey(rs.getInt("CampeonatoAtivoId"), rs.getString("JogadorId")));
            }
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
        return res;
	}

	@Override
	public Collection<JogadorAtivo> values() {
		Collection<JogadorAtivo> res = new HashSet<>();
        try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             Statement stm = conn.createStatement();
             ResultSet rs = stm.executeQuery("SELECT (CampeonatoAtivoId, JogadorId) FROM jogadores_ativos;")) { // ResultSet com os nomes de todos os campeonatos
            while (rs.next()) {
                JogadorAtivo a = this.get(new JogadorAtivoKey(rs.getInt("CampeonatoAtivoId"),rs.getString("JogadorId"))); // Utilizamos o get para construir os campeonatos
                res.add(a);                                 // Adiciona o campeonato ao resultado.
            }
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        return res;
	}

	@Override
	public Set<Entry<JogadorAtivoKey, JogadorAtivo>> entrySet() {
		throw new NullPointerException("public Set<Map.Entry<String,JogadorAtivo>> entrySet() not implemented!");
	}
}