package jni;

import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

public class WindowsProcessManager {

	static {
		System.loadLibrary("windows_process_manager");
	}
	

	HashMap<String, String> processes;
	public static void main(String[] args) {
		Scanner scan = new Scanner(System.in);
		WindowsProcessManager win = new WindowsProcessManager();
		win.fetchProcesses();
		win.getStoredProcesses();
		win.printRunningProcess();
		while(true) {
			System.out.println("Enter the PID to stop");
			String spid = scan.nextLine();
			int pid = Integer.parseInt(spid);
			if(win.stopProcess(pid)) {
				System.out.println("Process stopped");
				win.processes.remove(spid);
				win.printRunningProcess();
			}
			else {
				System.out.println("Unable to stop process");
			}
		}
//		scan.close();
	}
	
	public void printRunningProcess() {
		System.out.println("Printing Processes");
		for (Map.Entry<String, String> process : this.processes.entrySet()) {
			System.out.println("PID : " + process.getKey() + "		Name : " + process.getValue());
		}
	}
	public native void fetchProcesses();
	public native boolean stopProcess(int PID);
	public native void getStoredProcesses();
}
