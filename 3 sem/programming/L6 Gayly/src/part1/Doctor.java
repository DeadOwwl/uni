package part1;

import java.io.Serializable;

public class Doctor implements Serializable{
    private final String name;
    private final Specialty specialty;

    public enum Specialty {THERAPIST, PEDIATRICIAN, CARDIOLOGIST, SURGEON, ONCOLOGIST, OPHTALMOLOGIST,
    OTALARYNGOLOGIST, NEUROLOGIST, DERMATO_VENEROLOGIST, OTHER}

    public Doctor() {
        name = null;
        specialty = Specialty.OTHER;
    }

    public Doctor(String n, Specialty s) {
        this.name = n;
        this.specialty = s;
    }

    public String getName() {
        return name;
    }

    public Specialty getSpecialty() {
        return specialty;
    }
}
