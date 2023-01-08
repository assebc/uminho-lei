package task3.src.data;

import java.util.*;
import java.sql.*;

import task3.src.SubCampeonatos.Campeonato;
import task3.src.SubCampeonatos.Circuito;
import task3.src.SubSimulacao.CampeonatoAtivo;
import task3.src.SubSimulacao.DadosJogador;
public class CampeonatoAtivoDAO implements Map<Integer,CampeonatoAtivo> {

	private static CampeonatoAtivoDAO singleton = null;

	private CampeonatoAtivoDAO(){
		try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             Statement stm = conn.createStatement()) {
            conn.setAutoCommit(false);

            String sql = "CREATE TABLE IF NOT EXISTS campeonatos_ativos (" +
                "CampeonatoAtivoId int NOT NULL PRIMARY KEY AUTO_INCREMENT," +
                "NrCorridaAtual int DEFAULT 0," +
                "NomeCampeonato varchar(45) NOT NULL," +
                "FOREIGN KEY (NomeCampeonato) REFERENCES campeonatos(Nome));";

            stm.execute(sql);

            sql = "CREATE TABLE IF NOT EXISTS dados_jogador (" +
                "DadosJogadorId int NOT NULL PRIMARY KEY AUTO_INCREMENT," +
                "CampeonatoAtivoId int NOT NULL," +
                "JogadorId varchar(45) NOT NULL," +
                "CarroId varchar(45) NOT NULL," + 
                "PilotoId varchar(45) NOT NULL," + 
                "FOREIGN KEY (CarroId) REFERENCES carros(ID)," +
                "FOREIGN KEY (PilotoId) REFERENCES pilotos(Nome)," +
                "FOREIGN KEY (CampeonatoAtivoId) REFERENCES campeonatos_ativos(CampeonatoAtivoId));";

            stm.execute(sql);

            sql = "CREATE TABLE IF NOT EXISTS posicoes_campeonatos_ativos (" +
                    "DadosJogadorId int NOT NULL," +
                    "NrCorrida int NOT NULL," +
                    "CampeonatoAtivoId int NOT NULL," +
                    "Posicao int NOT NULL," +
                    "FOREIGN KEY (DadosJogadorId) REFERENCES dados_jogador(DadosJogadorId)," +
                    "FOREIGN KEY (CampeonatoAtivoId) REFERENCES campeonatos_ativos(CampeonatoAtivoId)," +
                    "PRIMARY KEY(DadosJogadorId, NrCorrida, CampeonatoAtivoId));";

            stm.execute(sql);

            sql = "CREATE TABLE IF NOT EXISTS circuitos_campeonatos_ativos (" +
                "NrCircuito int NOT NULL," +
                "CampeonatoAtivoId int NOT NULL," +
                "CircuitoNome varchar(45) NOT NULL," +
                "FOREIGN KEY (CampeonatoAtivoId) REFERENCES campeonatos_ativos(CampeonatoAtivoId)," +
                "FOREIGN KEY (CircuitoNome) REFERENCES circuitos(Nome)," +
                "PRIMARY KEY(NrCircuito, CampeonatoAtivoId));";
            
            stm.execute(sql);
            conn.commit();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
	}

	public static CampeonatoAtivoDAO getInstance() {
        if (CampeonatoAtivoDAO.singleton == null) {
            CampeonatoAtivoDAO.singleton = new CampeonatoAtivoDAO();
        }
        return CampeonatoAtivoDAO.singleton;
    }

    public static void buildInstance(){
        if(CampeonatoAtivoDAO.singleton == null)
            CampeonatoAtivoDAO.singleton = new CampeonatoAtivoDAO();
    }

	@Override
	public int size() {
		int i = 0;
        try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             Statement stm = conn.createStatement();
             ResultSet rs = stm.executeQuery("SELECT count(*) FROM campeonatos_ativos;")) {
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
                     stm.executeQuery("SELECT Id FROM campeonatos_ativos WHERE CampeonatoAtivoId='"+(int)key+"';")) {
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
		CampeonatoAtivo a = (CampeonatoAtivo) value;
        for(CampeonatoAtivo as: values()){
            if(as.equals(a)) return true; 
        }
        return false;
	}

	@Override
	public CampeonatoAtivo get(Object key) {
		CampeonatoAtivo a = null;
        try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             Statement stm = conn.createStatement();
             ResultSet rs = stm.executeQuery("SELECT * FROM campeonatos_ativos WHERE CampeonatoAtivoId='"+key+"';")) {
            if (rs.next()) {  // A chave existe na tabela
                Campeonato camp = CampeonatoDAO.getInstance().get(rs.getString("NomeCampeonato"));
                int id = rs.getInt("Id");
                int nrCorridaAtual = rs.getInt("NrCorridaAtual");

                String sql = "SELECT * FROM posicoes_campeonatos_ativos" +
                    "NATURAL JOIN dados_jogador" + 
                    "WHERE CampeonatoAtivoId='"+key+"';";

                Map<Integer, Map<Integer, List<DadosJogador>>> corrMap = new HashMap<>();
                try(ResultSet rsDj = stm.executeQuery(sql)){
                    while(rsDj.next()){
                        int posFinal = rsDj.getInt("PosicaoFinal");
                        int nrCorrida = rsDj.getInt("NrCorrida");
                        DadosJogador dj = new DadosJogador(rsDj.getString("JogadorId"), 
                                        CarroDAO.getInstance().get(rsDj.getString("CarroId")),
                                        PilotoDAO.getInstance().get(rsDj.getString("PilotoId")));
                        
                        if(corrMap.containsKey(nrCorrida)){
                            Map<Integer,List<DadosJogador>> posMap = corrMap.get(nrCorrida);
                            if(posMap.containsKey(posFinal))
                                posMap.get(posFinal).add(dj);
                            else{
                                List<DadosJogador> djList = new ArrayList<>();
                                djList.add(dj);
                                posMap.put(posFinal, djList);
                            }
                        }
                        else{
                            Map<Integer, List<DadosJogador>> posMap = new HashMap<>();
                            List<DadosJogador> djList = new ArrayList<>();
                            djList.add(dj);
                            posMap.put(posFinal, djList);
                            corrMap.put(nrCorrida, posMap);
                        }
                    }
                }
                
                Map<Integer, Circuito> circMap = new HashMap<>();
                sql = "SELECT * FROM circuitos_campeonatos_ativos WHERE CampeonatoAtivoId='"+key+"';";
                try(ResultSet resCirc = stm.executeQuery(sql)){
                    while(resCirc.next()){
                        circMap.put(resCirc.getInt("NrCircuito"), CircuitoDAO.getInstance().get(resCirc.getString("CircuitoNome")));
                    }
                }
                List<List<DadosJogador>> djCorrList = new ArrayList<>();
                for(int i=0;i<corrMap.size();++i){
                    List<DadosJogador> djList = new ArrayList<>();
                    Map<Integer, List<DadosJogador>> posMap = corrMap.get(i);
                    for(int j=0;j<posMap.size();++j){
                        djList.addAll(posMap.get(j));
                    }
                    djCorrList.add(djList);
                }

                List<Circuito> circList = new ArrayList<>();
                for(int i=0;i< circMap.size();++i){
                    circList.add(circMap.get(i));
                }

                a = new CampeonatoAtivo(camp, id, nrCorridaAtual, djCorrList, circList);
                
            }
        } catch (SQLException e) {
            // Database error!
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
        return a;
	}

	@Override
	public CampeonatoAtivo put(Integer key, CampeonatoAtivo value) {
		CampeonatoAtivo res = null;
        try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             Statement stm = conn.createStatement()) {
            
            conn.setAutoCommit(false);
            int id = value.getId();
            int nrCorridaAtual = value.get_nCorridaAtual();
            Campeonato camp = value.get_campeonato();
            List<List<DadosJogador>> corrList = value.getPosPorCorridaJogadores();
            List<Circuito> circList = value.getListaOrdCircuitos();

            String sql = "INSERT INTO campeonatos_ativos(CampeonatoAtivoId, NrCorridaAtual, NomeCampeonato)" +
                        "VALUES (" + id + "," + nrCorridaAtual + "," + camp.get_nome() + ");";

            stm.execute(sql);

            sql = "INSERT INTO dados_jogador VALUES(?,?,?,?,?);";
            try(PreparedStatement djStm = conn.prepareStatement(sql)){
                for(List<DadosJogador> djList : corrList){
                    for(DadosJogador dj : djList){
                        djStm.setInt(0, dj.getId());
                        djStm.setInt(1, key);
                        djStm.setString(2, dj.get_jogadorID());
                        djStm.setString(3, dj.get_carro().get_iD());
                        djStm.setString(4, dj.get_piloto().get_nome());
                        djStm.execute();
                    }
                }

            }

            sql = "INSERT INTO posicoes_campeonatos_ativos VALUES (?,?,?,?);";
            try(PreparedStatement posStm = conn.prepareStatement(sql)){
                for(int i=0;i<corrList.size();++i){
                    List<DadosJogador> djList = corrList.get(0);
                    for(int j=0;j<djList.size();++j){
                        posStm.setInt(0, djList.get(j).getId());
                        posStm.setInt(1, i);
                        posStm.setInt(2, key);
                        posStm.setInt(3, j);
                        posStm.execute();
                    }
                }
            }

            sql = "INSERT INTO circuitos_campeonatos_ativos VALUES (?,?,?);";
            try(PreparedStatement circStm = conn.prepareStatement(sql)){
                for(int i=0;i< circList.size();++i){
                    circStm.setInt(0, i);
                    circStm.setInt(1, key);
                    circStm.setString(2, circList.get(i).get_nome());
                    circStm.execute();
                }
            }

            conn.commit();
            res = value;
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        return res;
	}

	@Override
	public CampeonatoAtivo remove(Object key) {
		CampeonatoAtivo a = this.get(key);
        try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             Statement stm = conn.createStatement()){
            conn.setAutoCommit(false);
            // apagar o campeonato_ativo
            stm.executeUpdate("DELETE FROM campeonatos_ativos WHERE CampeonatoAtivoId='"+key+"';");
            stm.executeUpdate("DELETE FROM circuitos_campeonatos_ativos WHERE CampeonatoAtivoId='"+key+"';");
            stm.executeUpdate("DELETE FROM posicoes_campeonatos_ativos WHERE CampeonatoAtivoId='"+key+"';");
            // TODO delete dados_jogador
            conn.commit();
        } catch (Exception e) {
            // Database error!
            e.printStackTrace();
            throw new NullPointerException(e.getMessage());
        }
        return a;
	}

	@Override
	public void putAll(Map<? extends Integer, ? extends CampeonatoAtivo> m) {
		for(CampeonatoAtivo a : m.values()) {
            this.put(a.getId(), a);
        }
	}

	@Override
	public void clear() {
		try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             Statement stm = conn.createStatement()) {
            stm.executeUpdate("UPDATE campeonatos_ativos SET CampeonatoAtivo=NULL");
            stm.executeUpdate("TRUNCATE campeonatos_ativos");
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
             ResultSet rs = stm.executeQuery("SELECT CampeonatoAtivoId FROM campeonatos_ativos")) { // ResultSet com os nomes de todos os campeonatos
             while (rs.next()) {
                res.add(rs.getInt("CampeonatoAtivoId"));                                 // Adiciona o campeonato ao resultado.
            }
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
        return res;
	}

	@Override
	public Collection<CampeonatoAtivo> values() {
		Collection<CampeonatoAtivo> res = new HashSet<>();
        try (Connection conn = DriverManager.getConnection(DAOconfig.URL, DAOconfig.USERNAME, DAOconfig.PASSWORD);
             Statement stm = conn.createStatement();
             ResultSet rs = stm.executeQuery("SELECT CampeonatoAtivoId FROM campeonatos_ativos")) { // ResultSet com os nomes de todos os campeonatos_ativos
            while (rs.next()) {
                Integer idt = rs.getInt("CampeonatoAtivoId"); // Obtemos um nome de campeonato_ativo do ResultSet
                CampeonatoAtivo a = this.get(idt);                    // Utilizamos o get para construir os campeonatos_ativos
                res.add(a);                                 // Adiciona o campeonato_ativo ao resultado.
            }
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
        return res;
	}

	@Override
	public Set<Entry<Integer, CampeonatoAtivo>> entrySet() {
		throw new NullPointerException("public Set<Map.Entry<Integer,CampeonatoAtivo>> entrySet() not implemented!");
	}
}