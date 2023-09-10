package part1;

import java.io.*;
import java.util.*;

public class Patient implements Serializable {
    private final String name;
    private final Doctor attendingDoctor;
    private final Doctor doctor;
    private final Nurse nurse;
    private final State state;

    private enum State {STATIONARY, MILD, MODERATE, SERIOUS, COMA, AT_DEATH_DOOR}

    public Patient() {
        name = "";
        attendingDoctor = new Doctor();
        doctor = new Doctor();
        nurse = new Nurse();
        state = State.MILD;
    }

    public String getName() {
        return name;
    }
    public Patient (String n, Doctor adn, Doctor d, Nurse nu, State s) {
        this.name = n;
        this.attendingDoctor = adn;
        this.doctor = d;
        this.nurse = nu;
        this.state = s;
    }

    public State getState() {
        return state;
    }

    public static String toString(Patient p) {
        return "\nName: " + p.getName() +
                "\nAttending Doctor: " + p.attendingDoctor.getName() +
                "\nDoctor's specialty: " + p.attendingDoctor.getSpecialty() +
                "\nAssistant Doctor: " + p.doctor.getName() +
                "\nNurse: " + p.nurse.getName() +
                "\nState: " + p.getState();
    }
}