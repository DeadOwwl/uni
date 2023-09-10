package part1;

import java.io.Serializable;

public class Nurse implements Serializable {
    String name;

    public Nurse() {
        name = null;
    }

    public Nurse(String name) {
        this.name = name;
    }

    public String getName() {
        return name;
    }
}
