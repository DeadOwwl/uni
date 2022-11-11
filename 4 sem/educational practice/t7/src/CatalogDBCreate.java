import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.Statement;

public class CatalogDBCreate {
	static String driver = "org.apache.derby.jdbc.EmbeddedDriver";
	static String connect = "jdbc:derby:CatalogDB;create=true";
	public static Boolean isCreated = true;
	public static void createDB() throws Exception {

		// ������� ������� ��� Derby
		System.setProperty("DERBY_HOME", "C:\\Users\\aowl2\\OneDrive\\������� ����\\bsu\\4 s\\ep\\t7\\src" );

			// ������������ ������� JDBC
			Class.forName( driver );
			// ������������ � �� 
			Connection conn = DriverManager.getConnection(connect);
			// ��������� ������� 
			Statement st = conn.createStatement();
			st.executeUpdate("CREATE TABLE Camera " +
				"(Name VARCHAR(32) PRIMARY KEY," +
					"Company VARCHAR(32) ,Type VARCHAR(32),Cost REAL )");
			st.executeUpdate("CREATE TABLE Buyer " +
				"(FIO VARCHAR(32) PRIMARY KEY, Sex INT, " + 
				"BirthDate DATE )");
			st.executeUpdate("CREATE TABLE ShoppingBasket " +
				"(FIO VARCHAR(32) REFERENCES Buyer (FIO), " +
				"Name VARCHAR(32) REFERENCES Camera (Name), " +
				"Date DATE, isPaied BOOLEAN )");
			st.close();
			isCreated = true;
	}
}
