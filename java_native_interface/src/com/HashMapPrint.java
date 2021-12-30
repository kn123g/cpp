package com;

import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class HashMapPrint {

	HashMap<String, String> employees;

	static {
		System.loadLibrary("HashMapPrint");
	}

	public static void main(String[] args) {

		HashMapPrint obj = new HashMapPrint();
		Scanner scan = new Scanner(System.in);
		System.out.println("Enter string to pass into native and return same value");
		String str = scan.nextLine();
		System.out.println("Returned from native : "+ obj.passAndReturn(str));

		System.out.println("Printing HashMap from Native");
		obj.hashMapPrintCPP();

	}

	public void print() {
		for (Map.Entry<String, String> employee : this.employees.entrySet()) {
			System.out.println("Printing Employee name");
			System.out.println("Id : " + employee.getKey());
			System.out.println("Name : " + employee.getValue());
		}

	}
	public native String passAndReturn(String value);
	public native int hashMapPrintCPP();
}
