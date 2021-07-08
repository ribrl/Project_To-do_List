#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "map.h"
#include "functions.h"
#include "menu.h"

void mostrarMenu (Map* mapTask) {
	bool salir = false;
	while (salir != true)
	{
		printf("\n»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»\n");
		printf("\n        Bienvenido a Monthly To-do list \n\n");
		printf("Seleccione una opcion: \n\n");
		printf("1. Ingresar mes \n");
		printf("2. Agregar tareas \n");
		printf("3. Mostrar tareas \n");
		printf("4. Modificar tarea \n");
		printf("5. Eliminar tarea \n");
		printf("6. Actualizar estado de una tarea \n");
		printf("7. Mostrar lista de tareas ordenadas por prioridad \n");
		printf("8. Mostrar lista de tareas hasta fecha ingresada\n");
		printf("9. Mostrar lista de tareas por estado \n");
		printf("10.Mostrar progreso \n");
		printf("11.Mostrar calendario de tareas \n");
    	printf("0. Salir \n\n");
		printf("\n»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»»\n");

		int opcion;
		scanf("%d", &opcion);
		
		switch (opcion) {
			case 1: ingresarMes (mapTask); break;
    		case 2: agregarTareas (mapTask); break;
			case 3: mostrarTareas (mapTask); break;
			case 4: modificarTarea (mapTask); break;
			case 5: eliminarTarea (mapTask); break;
			case 6: actualizarEstadoDeTarea (mapTask); break;
			case 7: mostrarTareasOrdenadosPorPrioridad (mapTask); break;
			case 8: mostrarTareasHastaXFecha (mapTask); break;
			case 9: mostrarListaPorEstado (mapTask); break;
			case 10: mostrarPorcentajeDeProgreso (mapTask); break;
			case 11: mostrarCalendario (mapTask); break;
      		case 0: salir = true; break;
			default: printf("Opcion no valida, intente nuevamente.\n");
		}
	}
}

