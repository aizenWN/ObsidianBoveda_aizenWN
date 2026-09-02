#include <chrono>     //Libreria de C++ estandar (Controlar/manejar tiempos como los timmers, 100ms, 1s, std::chrono::milliseconds(100);)
#include <functional> //Libreria de C++ estandar (Permite usar funciones como callbacks, std::bind(&MiNodo::callback, this))
#include <memory>     //Libreria de C++ estandar (Para usar punteros inteligentes como std::shared_ptr, std::make_shared<MiNodo>())

//Nota: Esto aparecera como error hasta que no se añada como nodo a CMakeLists.txt
#include "rclcpp/rclcpp.hpp"  //Libreria de ROS2 (Permite crear nodos, publicar/suscribirse a temas, usar servicios, etc.)
                              /* 
                                Obtienes acceso a todas las funciones y clases de ROS2 como:
                                rclcpp::Node
                                rclcpp::Publisher
                                rclcpp::Subscription
                                rclcpp::Timer
                                rclcpp::spin()
                                rclcpp::init()
                                rclcpp::shutdown()
                              */

using namespace std::chrono_literals; //Libreria de C++ estandar (Permite usar sufijos de tiempo como 100ms, 1s, etc. 
                                      //En lugar de std::chrono::milliseconds(100))

// A partir de aqui comienza ROS ============================================================================================================

class MiNodo : public rclcpp::Node  //Definición de una clase que hereda de rclcpp::Node, lo que la convierte en un nodo de ROS2
                                    // class MiNodo (Llamada asi por nosotros, puede ser cualquier nombre [SeguirLinea, ControlMotor, PIDControl, etc]) 
                                    //  : public rclcpp::Node (Indica que esta clase es un nodo de ROS2)
{
public:
  MiNodo() : Node("nombre_del_nodo")  // C++ + ROS, MiNodo() es el contructor normal en C++
                                      // :Node("nombre_del_nodo") es la forma de llamar al constructor de la clase base (rclcpp::Node) para inicializar el nodo con un nombre específico ("nombre_del_nodo")
                                      // Ejemplo : Node("adelante"), a partir de este nodo, se creara su Topico /adelante.
  {
  }

private:  //C++ Puro, la logica en general de lo que queremos que haga nuestro Nodo, va aqui dentro de la seccion privada, como funciones privadas, variables privadas, etc.
          //Aqui se podra: 
          /*
            Publisher
            Subscriber
            Timer
            Variables
            Funciones
            Ejemplo: rclcpp::Publisher<...>::SharedPtr publisher_;
          */

};

int main(int argc, char * argv[]) // Comienza el ciclo de vida de Nodo
{                                  
  rclcpp::init(argc, argv);                 // Antes de esto, ROS no existe, es el equivalente a Serial.begin(115200); en Arduino, o a la función setup() en Arduino, es el punto de entrada del programa.
                                            // Estas ordenando de ROS inicie, crea el nodo std::make_shared<MiNodo>(), crea un objeto MiNodo nodo;, pero usando punteros inteligentes   

  rclcpp::spin(std::make_shared<MiNodo>()); // Estos es ROS, le dice, manten vivo el nodo, escucha topicos, ejecuta callbacks, ejecuta timmers, etc. Es el equivalente a la función loop() en Arduino,
                                            // sin esto, el programa terminaria inmediatamente, se mantiene ejecutando hasta que se detenga el programa o se llame a rclcpp::shutdown().

  rclcpp::shutdown();                       //Apaga ROS, libera recursos, cierra comunicaciones, etc. Es el equivalente a apagar el programa, o a la función de limpieza en Arduino.

  return 0;
}