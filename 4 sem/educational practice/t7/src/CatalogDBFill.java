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
            new transportItem( "0999 BP-6", "����������� �������","441��",(float)2.5),
            new transportItem( "4299 EC-4","������������� �������", "����� - ������",50 ),
            new transportItem( "4883 ��-5","������������� �������", "����� - �����",10 ),
	        new transportItem( "1303 AI-5", "������������� �������", "92",10),
            new transportItem( "9669 ��-6", "������������� �������","44",9),
            new transportItem( "0240 AA-7","������������� �������", "����� - ����",100),
            new transportItem( "1914 ��-7","����������� �������", "82",(float) 1.2),
	        new transportItem( "8090 AA-7", "����������� �������", "4474�",(float)2.6),
	};

        static driverItem[] arrDrivers = {
            new driverItem( "�������� ������", 0, new Date( 80, 1, 1 )),
            new driverItem( "��������� ������", 1, new Date( 77, 4, 6 )),
            new driverItem( "������� �����", 1, new Date( 91, 2, 7 )),
            new driverItem( "������� �����", 0, new Date( 83, 9, 11 )),
            new driverItem( "������� ����", 1, new Date( 90, 0, 10 )),
            new driverItem( "������ ����", 0, new Date( 79, 5, 21 )),
            new driverItem( "��������� ����", 1, new Date( 88, 7, 31 )),
            new driverItem( "�������� ������", 1, new Date( 89, 1, 27 ))
        };

        static roadItem[] arrShoppingBasket = {
            new roadItem( "������� �����", "0999 BP-6", true ),
           new roadItem( "��������� ������", "4299 EC-4", false ),
            new roadItem( "������� �����", "8090 AA-7", true ),
            new roadItem( "������� ����", "0999 BP-6", false ),
            new roadItem( "������� �����", "0240 AA-7", true ),
            new roadItem( "�������� ������", "1303 AI-5",false ),
            new roadItem( "������ ����", "1914 ��-7", true ),
            new roadItem( "��������� ������", "1303 AI-5", true ),
        };

	public static void FillDB() throws Exception {

		// ������� ������� ��� Derby
		System.setProperty("DERBY_HOME", "C:\\Users\\aowl2\\OneDrive\\������� ����\\bsu\\4 s\\ep\\t7\\src" );

		// ������������ ������� JDBC
			Class.forName( driver );
			// ������������ � �� 
			Connection conn = DriverManager.getConnection(connect);
			// ��������� ������� 
			
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
