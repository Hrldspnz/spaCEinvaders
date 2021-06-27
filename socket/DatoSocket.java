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
   lector=new FileReader("C:\\Users\\hrlds\\Documents\\GitHub\\spaCEinvaders\\socket\\DatosE.txt");

//El contenido de lector se guarda en un BufferedReader
   contenido=new BufferedReader(lector);

//Con el siguiente ciclo extraemos todo el contenido del objeto "contenido" y lo mostramos
    while((texto=contenido.readLine())!= null)
{
    resultado = resultado + texto + "\n";
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
   
   /**
    * Funci�n que restaura el archivo de enviar
    */
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
   
        
  public java.lang.String leerTXTRecibido(){
         
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
  
     public void BorrarDatosR(){
        BufferedWriter bw = null;
        try {
            bw = new BufferedWriter(new FileWriter("C:\\Users\\hrlds\\Documents\\GitHub\\spaCEinvaders\\socket\\DatosR.txt"));
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

    public void RellenarTXT(){
        BorrarDatosR();
        
        try
  {
  //Crear un objeto File se encarga de crear o abrir acceso a un archivo que se especifica en su constructor
      File archivo=new File("C:\\Users\\hrlds\\Documents\\GitHub\\spaCEinvaders\\socket\\DatosR.txt");
  
  //Crear objeto FileWriter que sera el que nos ayude a escribir sobre archivo
      FileWriter escribir = new FileWriter(archivo,true);
      java.lang.String saludo = ("JPosx: 453 JHP: 3\n" +
  "PosX: 32 PosY: 244\n" +
  "PosX: 112 PosY: 244\n" +
  "PosX: 192 PosY: 244\n" +
  "PosX: 272 PosY: 244\n" +
  "PosX: 352 PosY: 244\n" +
  "PosX: 432 PosY: 244\n" +
  "PosX: 512 PosY: 244\n" +
  "PosX: 592 PosY: 244\n" +
  "PosX: 32 PosY: 294\n" +
  "PosX: 3 PosY: 95\n" +
  "PosX: 7 PosY: 63\n" +
  "PosX: 272 PosY: 294\n" +
  "PosX: 8 PosY: 127\n" +
  "PosX: 432 PosY: 294\n" +
  "PosX: 512 PosY: 294\n" +
  "PosX: 592 PosY: 294\n" +
  "PosX: 32 PosY: 344\n" +
  "PosX: 112 PosY: 344\n" +
  "PosX: 9 PosY: 63\n" +
  "PosX: 45 PosY: 95\n" +
  "PosX: 67 PosY: 191\n" +
  "PosX: 432 PosY: 344\n" +
  "PosX: 512 PosY: 344\n" +
  "PosX: 592 PosY: 344\n" +
  "PosX: 32 PosY: 394\n" +
  "PosX: 6 PosY: 63\n" +
  "PosX: 4 PosY: 159\n" +
  "PosX: 87 PosY: 95\n" +
  "PosX: 3 PosY: 63\n" +
  "PosX: 12 PosY: 127\n" +
  "PosX: 512 PosY: 394\n" +
  "PosX: 592 PosY: 394\n" +
  "PosX: 32 PosY: 444\n" +
  "PosX: 1 PosY: 63\n" +
  "PosX: 1 PosY: 191\n" +
  "PosX: 1 PosY: 191\n" +
  "PosX: 1 PosY: 159\n" +
  "PosX: 1 PosY: 127\n" +
  "PosX: 1 PosY: 159\n" +
  "PosX: 1 PosY: 127\n" +
  "HP: 3\n" +
  "HP: 3\n" +
  "HP: 3\n" +
  "HP: 3\n" +
  "ABalaPosx: -1 ABalaPosy: -1\n" +
  "ABalaPosx: -1 ABalaPosy: -1\n" +
  "ABalaPosx: -1 ABalaPosy: -1\n" +
  "ABalaPosx: -1 ABalaPosy: -1\n" +
  "ABalaPosx: -1 ABalaPosy: -1\n" +
  "ABalaPosx: -1 ABalaPosy: -1\n" +
  "ABalaPosx: -1 ABalaPosy: -1\n" +
  "ABalaPosx: -1 ABalaPosy: -1\n" +
  "ABalaPosx: -1 ABalaPosy: -1\n" +
  "ABalaPosx: -1 ABalaPosy: -1\n" +
  "BalaPosx: -1 BalaPosy: -1\n" +
  "BalaPosx: -1 BalaPosy: -1\n" +
  "BalaPosx: -1 BalaPosy: -1");
  //Escribimos en el archivo con el metodo write
      escribir.write(saludo);
  
  //Cerramos la conexion
      escribir.close();
  }catch (Exception e)
          {
              e.printStackTrace();
          }
    }
  
  
}
