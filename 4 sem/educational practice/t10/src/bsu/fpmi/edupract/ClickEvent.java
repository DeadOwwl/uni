package bsu.fpmi.edupract;/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */


public class ClickEvent extends java.util.EventObject {
    protected String text;
    
    public ClickEvent(Object source, String text) {
	super(source);
	this.text = text;
    }
    
    public String getText() {
        return text;
    }
}
