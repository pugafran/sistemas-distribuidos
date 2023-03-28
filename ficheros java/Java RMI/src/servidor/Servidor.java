package servidor;

import java.rmi.Naming;
import java.rmi.RemoteException;
import  java.lang.SecurityManager;

public class Servidor {

 public static void main(String[] args) {
   String mibase;

   // Hacer que la seguridad de RMI nos permita acceder a clases
   // remotas, si se necesitaran
   if (System.getSecurityManager() == null) {
        System.setSecurityManager(new SecurityManager());
   }
   try{
      // Fijar dónde está el codebase
      mibase=System.getenv("HOME");
      mibase="file:"+mibase+"/Rsistemas-distribuidos/ficheros java/Java RMI/src/servidor";
      System.setProperty ("java.rmi.server.codebase", mibase);

      // Crear el objeto que implementa los servicios
      CalculadoraImpl obj=new CalculadoraImpl();
      // Registrarlo
      Naming.rebind("CalculadoraServer",obj);
      System.out.println("CalculadoraServer registrada");
   }
   catch (Exception e)
   {
      System.out.println("Error en CalculadoraImpl:"+e.getMessage());
      e.printStackTrace();
   }
 }
}