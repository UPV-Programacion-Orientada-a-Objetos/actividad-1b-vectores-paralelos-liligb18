#include <iostream>
#include <iomanip>
#include <string>

// tamaño máximo de los arreglos
const int MAX_PRODUCTOS = 100;
int numProductos = 0; 
// Contador de productos actuales en el sistema

// Arreglos paralelos para almacenar los datos
int codigos[MAX_PRODUCTOS];
std::string nombres[MAX_PRODUCTOS];
int stocks[MAX_PRODUCTOS];
float precios[MAX_PRODUCTOS];


// funciones

void cargarDatosIniciales();
void mostrarMenu();
void consultarProducto();
void actualizarInventario();
void generarReporte();
void encontrarProductoMasCaro();
int buscarProductoPorCodigo(int codigo);
void limpiarBuffer();

int main() {
    cargarDatosIniciales();
    int opcion;

    do {
        mostrarMenu();
        std::cout << "Opcion seleccionada: ";
        std::cin >> opcion;
        limpiarBuffer();

        switch (opcion) {
            case 1:
                consultarProducto();
                break;
            case 2:
                actualizarInventario();
                break;
            case 3:
                generarReporte();
                break;
            case 4:
                encontrarProductoMasCaro();
                break;
            case 5:
                std::cout << "Saliendo del sistema." << std::endl;
                break;
            default:
                std::cout << "Opcion inválida. Por favor, intente de nuevo." << std::endl;
                break;
        }

        if (opcion != 5) {
            std::cout << "\n--- Menu principal ---\n" << std::endl;
        }
    } while (opcion != 5);

    return 0;
}


/**
 *  Inicializa los arreglos paralelos con datos predefinidos.
 */

void cargarDatosIniciales() {
    // productos predefinidos
    codigos[0] = 101;
    nombres[0] = "Martillo de bola";
    stocks[0] = 50;
    precios[0] = 15.50;

    codigos[1] = 102;
    nombres[1] = "Destornillador";
    stocks[1] = 120;
    precios[1] = 8.75;

    codigos[2] = 103;
    nombres[2] = "Cinta metrica";
    stocks[2] = 75;
    precios[2] = 20.00;

    codigos[3] = 104;
    nombres[3] = "Llave inglesa";
    stocks[3] = 45;
    precios[3] = 25.99;

    codigos[4] = 105;
    nombres[4] = "Taladro inalambrico";
    stocks[4] = 10;
    precios[4] = 120.00;

    numProductos = 5;
    std::cout << "--- Sistema de Inventario de \"El Martillo\" ---\n" << std::endl;
}

/**
 * Muestra el menú principal de opciones.
 */

void mostrarMenu() {
    std::cout << "Seleccione una opcion:" << std::endl;
    std::cout << "1. Consultar un producto" << std::endl;
    std::cout << "2. Actualizar inventario" << std::endl;
    std::cout << "3. Generar reporte completo" << std::endl;
    std::cout << "4. Encontrar el producto más caro" << std::endl;
    std::cout << "5. Salir" << std::endl;
    std::cout << std::endl;
}

/**
 * Busca un producto por su código y mostrar su información.
 */

void consultarProducto() {
    int codigoBuscado;
    std::cout << "Ingrese el codigo del producto a consultar: ";
    std::cin >> codigoBuscado;

    int indice = buscarProductoPorCodigo(codigoBuscado);

    if (indice != -1) {
        std::cout << "\nInformación del Producto:" << std::endl;
        std::cout << "Codigo: " << codigos[indice] << std::endl;
        std::cout << "Nombre: " << nombres[indice] << std::endl;
        std::cout << "Cantidad en stock: " << stocks[indice] << std::endl;
        std::cout << "Precio unitario: $" << std::fixed << std::setprecision(2) << precios[indice] << std::endl;
    } else {
        std::cout << "Error: Producto con codigo " << codigoBuscado << " no encontrado." << std::endl;
    }
}

/**
 *  Actualiza el stock de un producto existente.
 */

void actualizarInventario() {
    int codigoBuscado, cantidadCambio;
    std::cout << "Ingrese el codigo del producto a actualizar: ";
    std::cin >> codigoBuscado;

    int indice = buscarProductoPorCodigo(codigoBuscado);

    if (indice != -1) {
        std::cout << "Ingrese la cantidad a agregar o restar (positivo para agregar, negativo para restar): ";
        std::cin >> cantidadCambio;

        int nuevoStock = stocks[indice] + cantidadCambio;
        if (nuevoStock >= 0) {
            stocks[indice] = nuevoStock;
            std::cout << "Inventario actualizado exitosamente. Nuevo stock para " << nombres[indice] << ": " << stocks[indice] << std::endl;
        } else {
            std::cout << "Error: La cantidad en stock no puede ser inferior a cero." << std::endl;
        }
    } else {
        std::cout << "Error: Producto con codigo " << codigoBuscado << " no encontrado." << std::endl;
    }
}

/**
 * Genera y muestra un reporte completo de todos los productos.
 */
void generarReporte() {
    std::cout << "\n--- Reporte de Inventario ---" << std::endl;
    std::cout << std::left << std::setw(10) << "Codigo" << "|"
              << std::left << std::setw(20) << "Nombre" << "|"
              << std::left << std::setw(8) << "Stock" << "|"
              << std::left << "Precio" << std::endl;
    std::cout << "---------------------------------------------------" << std::endl;

    for (int i = 0; i < numProductos; ++i) {
        std::cout << std::left << std::setw(10) << codigos[i] << "|"
                  << std::left << std::setw(20) << nombres[i] << "|"
                  << std::left << std::setw(8) << stocks[i] << "|"
                  << "$" << std::fixed << std::setprecision(2) << precios[i] << std::endl;
    }

    std::cout << "---------------------------------------------------" << std::endl;
    std::cout << "--- Fin del Reporte ---\n" << std::endl;
}

/**
 * Encuentra y muestra el producto con el precio más alto.
 */
void encontrarProductoMasCaro() {
    if (numProductos == 0) {
        std::cout << "No hay productos en el inventario para encontrar el mas caro." << std::endl;
        return;
    }

    int indiceMasCaro = 0;
    for (int i = 1; i < numProductos; ++i) {
        if (precios[i] > precios[indiceMasCaro]) {
            indiceMasCaro = i;
        }
    }

    std::cout << "El producto mas caro es: " << nombres[indiceMasCaro]
              << " con un precio de $" << std::fixed << std::setprecision(2) << precios[indiceMasCaro] << std::endl;
}


int buscarProductoPorCodigo(int codigo) {
    for (int i = 0; i < numProductos; ++i) {
        if (codigos[i] == codigo) {
            return i;
        }
    }
    return -1;
}

/**
 * Limpia el buffer de entrada
 */
void limpiarBuffer() {
    std::cin.ignore(1000, '\n');
}