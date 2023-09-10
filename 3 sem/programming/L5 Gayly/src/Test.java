import java.util.*;

public class Test {

    static void sortAndPrint(Account[] A, int sortBy )  {
        System.out.println( "\n-Sorted by: " + Account.getSortByName(sortBy));
        Arrays.sort( A, Account.getComparator(sortBy));
        System.out.print( Account.format() );
        System.out.println();
        for (Account tIt : A)
            System.out.println(Account.format(tIt));
    }

    public static void main(String[] args) {
        try {
            Account[] accounts = new Account[7];
            accounts[0] = new Account("Steve Global", 12145, "BYN", 2.4, 1928.43);
            accounts[1] = new Account("Aaron Eagle", 31233, "USD", 9.7, 11209.03);
            accounts[2] = new Account("Barbara Smith", 88786, "EUR", 10.23, 909.4);
            accounts[3] = new Account("Monica Geller 35467 USD 8.93 7093.4");
            accounts[4] = new Account("Paul Cross 53802 BYN 0.1 15.33");
            accounts[5] = new Account("Mark Parrish 65436 EUR 8.8 54324.5");
            accounts[6] = new Account("Eric Flaming 09382 USD 12.9 9932.01");

            Arrays.sort(accounts);

            // D E M O
            System.out.println( "\nAccount balances before changes:");
            sortAndPrint(accounts, 0);
            sortAndPrint(accounts, 1);
            sortAndPrint(accounts, 2);
            sortAndPrint(accounts, 3);

            Account.swinthdrawAmount(accounts[4], 1000);
            System.out.println( "\nAaron Eagle's account after swinthdrawing 1000USD:");
            System.out.println(Account.format(accounts[4]));
            Account.addAmount(accounts[0], 1450);
            System.out.println( "\nPaul Cross's account after adding 1450BYN:");
            System.out.println(Account.format(accounts[0]));
            Account.interestAccrual(accounts[2], 0.5);
            System.out.println( "\nMark Parrish's account after accrualling interest for 6 months:");
            System.out.println(Account.format(accounts[2]));

        } catch (Exception e) {
            System.out.println( "Exception: " + e );
        }
    }
}
