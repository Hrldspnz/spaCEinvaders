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
   public DatoSocket (java.lang.String cadena)
   {
      // Si la cadena no es null, se guarda la cadena y su longitud 
      if (cadena != null)
      {
         c = cadena.length();
         d = cadena;
      }
   }

   /** Primer atributo, un int */
   public int c = 0;
     
   /** Segundo atributo, un String */
   public java.lang.String d = "";
     
   /** Método para devolver un String en el que se represente el valor de
    * todos los atributos. */
   public String toString ()
   {
       java.lang.String resultado;
       resultado = d;
       return resultado;
   }

   /**
   * Método para escribir los atributos de esta clase en un DataOutputStream de forma
   * que luego pueda entenderlos un programa en C.
   */
   public void writeObject(java.io.DataOutputStream out)
         throws IOException
     {
         // Se envía la longitud de la cadena + 1 por el \0 necesario en C
         out.writeInt (leerTXT().length()+1);

         // Se envía la cadena como bytes.
         out.writeBytes (leerTXT());

         // Se envía el \0 del final
         out.writeByte ('\0');
     }
   
    
      /**
      * Método que lee los atributos de esta clase de un DataInputStream tal cual nos los
      * envía un programa en C.
      * Este método no contempla el caso de que se envíe una cadena "", es decir, un
      * único \0.
      */
     public void readObject(java.io.DataInputStream in)
     throws IOException
     {
         // Se lee la longitud de la cadena y se le resta 1 para eliminar el \0 que
         // nos envía C.
         c = in.readInt() - 1;
         
         // Array de bytes auxiliar para la lectura de la cadena.
         byte [] aux = null;
         
         aux = new byte[c];    // Se le da el tamaño 
         in.read(aux, 0, c);   // Se leen los bytes
         d = new String (aux); // Se convierten a String
         in.read(aux,0,1);     // Se lee el \0
     }
     
    public void escribirTXT(java.lang.String saludo){

try
{
//Crear un objeto File se encarga de crear o abrir acceso a un archivo que se especifica en su constructor
    File archivo=new File("C:\\Users\\arman\\OneDrive\\Escritorio\\Server\\src\\socket\\DatosR.txt");

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
     
    public java.lang.String leerTXT(){
         
    java.lang.String texto="";
    FileReader lector;
    BufferedReader contenido;

try
{
//Creamos un archivo FileReader que obtiene lo que tenga el archivo
   lector=new FileReader("C:\\Users\\arman\\OneDrive\\Escritorio\\Server\\src\\socket\\DatosE.txt");

//El contenido de lector se guarda en un BufferedReader
   contenido=new BufferedReader(lector);

//Con el siguiente ciclo extraemos todo el contenido del objeto "contenido" y lo mostramos
    while((texto=contenido.readLine())!=null)
{
    return texto;
}
}

//Si se causa un error al leer cae aqui
    catch(Exception e)
{
System.out.println("Error al leer");
}
      
    return texto;
     }
}