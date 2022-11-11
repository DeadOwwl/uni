import java.sql.Connection;
import java.sql.Date;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;
import java.util.ArrayList;


public class CatalogDB {
	
	static String driver = "org.apache.derby.jdbc.EmbeddedDriver";
	static String connect = "jdbc:derby:CatalogDB";
	
	public static ArrayList<transportItem> ReadMonumentDB() {
		ArrayList<transportItem> transportItems = new ArrayList<>();
		if(!CatalogDBCreate.isCreated)
			return transportItems;
		// Текущий каталог для Derby
		System.setProperty("DERBY_HOME", "C:\\Users\\aowl2\\OneDrive\\Рабочий стол\\bsu\\4 s\\ep\\t7\\src" );

		try {
			// Регистрируем драйвер JDBC
			Class.forName( driver );
			// Подключаемся к БД 
			Connection conn = DriverManager.getConnection(connect);
			// Выполняем запрос 
			Statement st = conn.createStatement(); 
			ResultSet rec = st.executeQuery("SELECT * FROM Camera ORDER BY Name");
			// Просматриваем и печатаем записи результирующей таблицы			
			while (rec.next()) {
				String company = rec.getString("Name");
				String Type = rec.getString("Company");
				String Name = rec.getString("Type");
				float price = rec.getFloat("Cost");
				System.out.println( " Company: " + company + " Type: " + Type + " Name: " + Name + " Cost: " + price );
				transportItems.add(new transportItem(company,Type,Name,price));
			}
			rec.close();
			st.close();			
		} catch (Exception e) {
			System.err.println("Run-time error: " + e );
		}
		return transportItems;

	}

	public static ArrayList<driverItem> ReadBuyerDB() {
		ArrayList<driverItem> arrBuyer = new ArrayList<>();
		if(!CatalogDBCreate.isCreated)
			return arrBuyer;
		// Текущий каталог для Derby
		System.setProperty("DERBY_HOME", "C:\\Users\\aowl2\\OneDrive\\Рабочий стол\\bsu\\4 s\\ep\\t7\\src" );

		try {
			// Регистрируем драйвер JDBC
			Class.forName( driver );
			// Подключаемся к БД
			Connection conn = DriverManager.getConnection(connect);
			// Выполняем запрос
			Statement st = conn.createStatement();
			ResultSet rec = st.executeQuery("SELECT * FROM Buyer ORDER BY FIO");
			// Просматриваем и печатаем записи результирующей таблицы
			while (rec.next()) {
				String fio = rec.getString("FIO");
				Integer sex = rec.getInt("Sex");
				Date birthDate = rec.getDate("BirthDate");

				System.out.println( " FIO: " + fio + " Sex: " + sex + " BirthDate: " + birthDate );
				arrBuyer.add(new driverItem(fio,sex,birthDate));
			}
			rec.close();
			st.close();
		} catch (Exception e) {
			System.err.println("Run-time error: " + e );
		}
		return arrBuyer;

	}

	public static ArrayList<roadItem> ReadShoppingBasketDB() {
		ArrayList<roadItem> arrShoppingBasket = new ArrayList<>();
		if(!CatalogDBCreate.isCreated)
			return arrShoppingBasket;
		// Текущий каталог для Derby
		System.setProperty("DERBY_HOME", "C:\\Users\\aowl2\\OneDrive\\Рабочий стол\\bsu\\4 s\\ep\\t7\\src" );

		try {
			// Регистрируем драйвер JDBC
			Class.forName( driver );
			// Подключаемся к БД
			Connection conn = DriverManager.getConnection(connect);
			// Выполняем запрос
			Statement st = conn.createStatement();
			ResultSet rec = st.executeQuery("SELECT * FROM ShoppingBasket ORDER BY FIO");
			// Просматриваем и печатаем записи результирующей таблицы
			while (rec.next()) {


				String fio = rec.getString("FIO");
				String name = rec.getString("Name");
				Boolean isPaied = rec.getBoolean("isPaied");

				System.out.println( " FIO: " + fio + " Name: " + name + " isPaied: " + isPaied );
				arrShoppingBasket.add(new roadItem(fio,name,isPaied));
			}
			rec.close();
			st.close();
		} catch (Exception e) {
			System.err.println("Run-time error: " + e );
		}
		return arrShoppingBasket;

	}

}
