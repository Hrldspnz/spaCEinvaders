package socket;



import java.io.*;
import java.util.logging.Level;
import java.util.logging.Logger;

/**
 * Dato para enviar por el socket. Sus atributos son simples y una Clase Atributo
 */
public class DatoSocket implements Serializable
 {
   /**
   * Constructor. Guarda la cadena en el atributo d y calcula su longitud para guardarla
   * en el atricuto c.
   */
   public DatoSocket ()
   {
      // Si la cadena no es null, se guarda la cadena y su longitud 
     
   }
    
  
     
    public void escribirTXT(java.lang.String saludo){

try
{
//Crear un objeto File se encarga de crear o abrir acceso a un archivo que se especifica en su constructor
    File archivo=new File("C:\\Users\\hrlds\\Documents\\GitHub\\spaCEinvaders\\socket\\DatosR.txt");

//Crear objeto FileWriter que sera el que nos ayude a escribir sobre archivo
    FileWriter escribir = new FileWriter(archivo,true);

//Escribimos en el archivo con el metodo write
    escribir.write(saludo);

//Cerramos la conexion
    escribir.close();
}catch (Exception e)
        {
            e.printStackTrace();
        }

    }
    
    /**
     * Funci�n para leer los datos que se reciben del socket
     * @return String con los datos del cliente
     */
     
  public java.lang.String leerTXT(){
         
    java.lang.String texto="";
    FileReader lector;
    BufferedReader contenido;
    java.lang.String resultado = "";

try
{
//Creamos un archivo FileReader que obtiene lo que tenga el archivo
   lector=new FileReader("C:\\Users\\hrlds\\Documents\\GitHub\\spaCEinvaders\\socket\\DatosR.txt");

//El contenido de lector se guarda en un BufferedReader
   contenido=new BufferedReader(lector);

//Con el siguiente ciclo extraemos todo el contenido del objeto "contenido" y lo mostramos
    while((texto=contenido.readLine())!= null)
{
    resultado = resultado + texto + " ";
}
}

//Si se causa un error al leer cae aqui
    catch(Exception e)
{
System.out.println("Error al leer");
}

    
      
    return resultado;
     }
  
  /**
   * Metodo que lee los datos de las balas, que se pasar�n al cliente observador
   * @return String con los datos de las balas
   */
  
  public java.lang.String leerDatosBalas(){
      
    java.lang.String texto="";
    FileReader lector;
    BufferedReader contenido;
    java.lang.String resultado = "";
    java.lang.Integer indice = 0;

try
{
//Creamos un archivo FileReader que obtiene lo que tenga el archivo
   lector=new FileReader("C:\\Users\\hrlds\\Documents\\GitHub\\spaCEinvaders\\socket\\DatosR.txt");

//El contenido de lector se guarda en un BufferedReader
   contenido=new BufferedReader(lector);

//Con el siguiente ciclo extraemos todo el contenido del objeto "contenido" y lo mostramos
    while((texto=contenido.readLine())!= null)
{
    if(indice >= 45){
            resultado = resultado + texto + "\n";

    }
    indice++;
}
}

//Si se causa un error al leer cae aqui
    catch(Exception e)
{
System.out.println("Error al leer");
}
    
  
     

       return resultado;

}
   public void escribirTXTEnviar(java.lang.String saludo){

try
{
//Crear un objeto File se encarga de crear o abrir acceso a un archivo que se especifica en su constructor
    File archivo=new File("C:\\Users\\hrlds\\Documents\\GitHub\\spaCEinvaders\\socket\\DatosE.txt");

//Crear objeto FileWriter que sera el que nos ayude a escribir sobre archivo
    FileWriter escribir = new FileWriter(archivo,true);
    saludo = saludo + "\n";
//Escribimos en el archivo con el metodo write
    escribir.write(saludo);

//Cerramos la conexion
    escribir.close();
}catch (Exception e)
        {
            e.printStackTrace();
        }

    }
   
   public void BorrarDatosE(){
       BufferedWriter bw = null;
       try {
           bw = new BufferedWriter(new FileWriter("C:\\Users\\hrlds\\Documents\\GitHub\\spaCEinvaders\\socket\\DatosE.txt"));
           bw.write("");
           bw.close();
       } catch (IOException ex) {
           Logger.getLogger(DatoSocket.class.getName()).log(Level.SEVERE, null, ex);
       } finally {
           try {
               bw.close();
           } catch (IOException ex) {
               Logger.getLogger(DatoSocket.class.getName()).log(Level.SEVERE, null, ex);
           }
       }
   }
  
  
  
  
}
