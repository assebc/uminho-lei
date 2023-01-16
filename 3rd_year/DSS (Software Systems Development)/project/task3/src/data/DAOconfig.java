package EntregaFinal.src.data;

public class DAOconfig {
    public static final String USERNAME = "karton";                       // Actualizar
    public static final String PASSWORD = "karton";                       // Actualizar
    private static final String DATABASE = "RacingManager";          // Actualizar
    private static final String DRIVER = "jdbc:mariadb";        // Usar para MariaDB
    //private static final String DRIVER = "jdbc:mysql";        // Usar para MySQL
    public static final String URL = DRIVER+"://localhost:3306/"+DATABASE;

}
