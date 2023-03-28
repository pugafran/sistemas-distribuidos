

import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;


public class CalculadoraImpl extends UnicastRemoteObject implements Calculadora {

	private static final long serialVersionUID = 1L;

	public CalculadoraImpl() throws RemoteException {
        super();
    }

    @Override
    public float suma(float op1, float op2) throws RemoteException {
        return op1 + op2;
    }

    @Override
    public float resta(float op1, float op2) throws RemoteException {
        return op1 - op2;
    }

    @Override
    public float multiplicacion(float op1, float op2) throws RemoteException {
        return op1 * op2;
    }

    @Override
    public float division(float op1, float op2) throws RemoteException, DivisionPorCero {
        if (op2 == 0) 
            throw new DivisionPorCero();
        
        return op1 / op2;
    }

}