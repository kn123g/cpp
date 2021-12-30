package com;

import java.util.HashMap;
import java.util.Map;

public class HashMapPrint {

	HashMap<String, String> employees;

	static {
		System.loadLibrary("HashMapPrint");
	}

	public static void main(String[] args) {
		HashMapPrint obj = new HashMapPrint();
		obj.hashMapPrintCPP();

	}

	public void print() {
		for (Map.Entry<String, String> employee : this.employees.entrySet()) {
			System.out.println("Printing Employee name");
			System.out.println("Id : " + employee.getKey());
			System.out.println("Name : " + employee.getValue());
		}

	}

	public native int hashMapPrintCPP();
}
