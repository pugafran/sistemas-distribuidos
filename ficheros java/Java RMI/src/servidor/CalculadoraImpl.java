package servidor;

import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import interfaz.Calculadora;

public class CalculadoraImpl extends UnicastRemoteObject implements Calculadora {

	private static final long serialVersionUID = 1L;

	public CalculadoraImpl() throws RemoteException {
        super();
    }

    public int suma (int op1, int op2) {
        return op1 + op2;
    }

    public int resta (int op1, int op2) {
        return op1 - op2;
    }
}