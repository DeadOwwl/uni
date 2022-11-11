import java.sql.*;

class transportItem {
	String transportNumber;
	String transportType;
	String transportWay;
	Float cost;
	transportItem(String transportNumber, String transportType, String transportWay, float cost) {
		this.transportNumber = transportNumber;
		this.transportType = transportType;
		this.transportWay = transportWay;
		this.cost = cost;
	}
}

class driverItem {
	String fio;
	Integer sex;
	Date birthDate;
	driverItem(String fio, int sex, Date birthDate ) {
		this.fio = fio;
		this.sex = sex;
		this.birthDate = birthDate;		
	}
}

class roadItem {
	String fio;
	String name;
	Boolean isPaied;

	roadItem(String fio, String name, boolean isPaied ) {
		this.fio = fio;
		this.name = name;
		this.isPaied = isPaied;		
	}

}

public class CatalogDBFill {

	static String driver = "org.apache.derby.jdbc.EmbeddedDriver";
	static String connect = "jdbc:derby:CatalogDB";
	
	static String mIns = "INSERT INTO Camera(Name,Company, Type, Cost) VALUES(?,?,?,?)";
	static String buyerIns = "INSERT INTO Buyer(FIO, Sex, BirthDate) VALUES(?,?,?)";
	static String shoppingBasketIns = "INSERT INTO ShoppingBasket(FIO, Name, isPaied) VALUES(?,?,?)";
	
	static transportItem[] arrTransports = {
            new transportItem( "0999 BP-6", "Пригородный автобус","441УЭ",(float)2.5),
            new transportItem( "4299 EC-4","Международный автобус", "Минск - Москва",50 ),
            new transportItem( "4883 ЕТ-5","Междугородный автобус", "Минск - Брест",10 ),
	        new transportItem( "1303 AI-5", "Междугородный автобус", "92",10),
            new transportItem( "9669 КТ-6", "Междугородный автобус","44",9),
            new transportItem( "0240 AA-7","Международный автобус", "Минск - Рига",100),
            new transportItem( "1914 АА-7","Пригородный автобус", "82",(float) 1.2),
	        new transportItem( "8090 AA-7", "Пригородный автобус", "4474Э",(float)2.6),
	};

        static driverItem[] arrDrivers = {
            new driverItem( "Володина Ульяна", 0, new Date( 80, 1, 1 )),
            new driverItem( "Возовиков Никита", 1, new Date( 77, 4, 6 )),
            new driverItem( "Вакулич Денис", 1, new Date( 91, 2, 7 )),
            new driverItem( "Крагель Алина", 0, new Date( 83, 9, 11 )),
            new driverItem( "Дугинов Олег", 1, new Date( 90, 0, 10 )),
            new driverItem( "Досова Анна", 0, new Date( 79, 5, 21 )),
            new driverItem( "Березовик Глеб", 1, new Date( 88, 7, 31 )),
            new driverItem( "Гутников Сергей", 1, new Date( 89, 1, 27 ))
        };

        static roadItem[] arrShoppingBasket = {
            new roadItem( "Вакулич Денис", "0999 BP-6", true ),
           new roadItem( "Возовиков Никита", "4299 EC-4", false ),
            new roadItem( "Вакулич Денис", "8090 AA-7", true ),
            new roadItem( "Дугинов Олег", "0999 BP-6", false ),
            new roadItem( "Крагель Алина", "0240 AA-7", true ),
            new roadItem( "Володина Ульяна", "1303 AI-5",false ),
            new roadItem( "Досова Анна", "1914 АА-7", true ),
            new roadItem( "Возовиков Никита", "1303 AI-5", true ),
        };

	public static void FillDB() throws Exception {

		// Текущий каталог для Derby
		System.setProperty("DERBY_HOME", "C:\\Users\\aowl2\\OneDrive\\Рабочий стол\\bsu\\4 s\\ep\\t7\\src" );

		// Регистрируем драйвер JDBC
			Class.forName( driver );
			// Подключаемся к БД 
			Connection conn = DriverManager.getConnection(connect);
			// Выполняем запросы 
			
                        PreparedStatement st = conn.prepareStatement(mIns);
			for ( transportItem si : arrTransports) {
                                st.setString( 1, si.transportNumber);
                                st.setString(2,si.transportType);
                                st.setString(3,si.transportWay);
                                st.setFloat( 4, si.cost);
                                st.executeUpdate();

		            }

			st.close();

                        st = conn.prepareStatement(buyerIns);
			for ( driverItem pi : arrDrivers) {
                            try {
                                st.setString( 1, pi.fio );
                                st.setInt( 2, pi.sex );
                                st.setDate( 3, pi.birthDate );
                                st.executeUpdate();
                            } catch (SQLException e) {
			        System.err.println("Insert error: " + e );
		            }
                        }			
			st.close();

                        st = conn.prepareStatement(shoppingBasketIns);
			for ( roadItem hc : arrShoppingBasket ) {

                                st.setString( 1, hc.fio );
                                st.setString( 2, hc.name );
                                st.setBoolean( 3, hc.isPaied );
                                st.executeUpdate();
                        }			
			st.close();

			conn.close();


	}
}
