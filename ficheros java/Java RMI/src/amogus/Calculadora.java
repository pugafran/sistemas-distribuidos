import java.rmi.Remote;
import java.rmi.RemoteException;

public interface Calculadora extends Remote {
    float suma (float op1, float op2) throws RemoteException;
    float resta (float op1, float op2) throws RemoteException;
    float multiplicacion (float op1, float op2) throws RemoteException;
    float division (float op1, float op2) throws RemoteException, DivisionPorCero;
}