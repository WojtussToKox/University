package lab7.java;

import lab7.scala.*;
import java.util.LinkedList;
import java.util.List;


public class KitchenSorter implements IVisitor {
    private List<Spoon> spoons = new LinkedList<>();
    private List<Plate> plates = new LinkedList<>();


    public void sort(List<KitchenItem> items) {
        for (KitchenItem item : items) {
            item.accept(this);
        }
    }

    @Override
    public void visit(Spoon spoon) {
        System.out.println(spoon.toString());
        spoons.add(spoon);
    }

    @Override
    public void visit(Plate plate) {
        System.out.println(plate.toString());
        plates.add(plate);
    }

    public List<Spoon> getSpoons() { return spoons; }
    public List<Plate> getPlates() { return plates; }
}
