#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "map.h"
#include "functions.h"

/*
función para comparar claves de tipo string, retorna 1 si son iguales
*/
int is_equal_string(void * key1, void * key2) {
	if(strcmp((char*)key1, (char*)key2)==0) return 1;
    return 0;
}

/*
función para comparar claves de tipo string, retorna 1 si son key1<key2
*/
int lower_than_string(void * key1, void * key2) {
	if(strcmp((char*)key1, (char*)key2) < 0) return 1;
    return 0;
}

/*
función para comparar claves de tipo int, retorna 1 si son iguales
*/
int is_equal_int(void * key1, void * key2) {
	if(*(int*)key1 == *(int*)key2) return 1;
    return 0;
}

/*
función para comparar claves de tipo int, retorna 1 si son key1<key2
*/
int lower_than_int(void * key1, void * key2) {
	if(*(int*)key1 < *(int*)key2) return 1;
    return 0;
}
/*
función que verifica que se ingresa el mes correctamente y retora el numero correspondiente para mostrar calendario
*/
int ingresarMes (Map* mapTask) {
	int month = 0;
	int monthAux = 0;
	printf("Ingrese número de mes para aplicacion:\n");
	printf("\n1. enero\n2. febrero\n3. marzo\n4. abril\n5. mayo\n6. junio\n7. julio\n8. agosto\n9. septiembre\n10. octubre\n11. noviembre\n12. diciembre\n");
	scanf("%d", &monthAux);
	if ((monthAux >= 1) && (monthAux <= 12)) {	
		month = monthAux;
	}
	else 
	{
		printf("mes invalido, ingrese nuevamente");
	}
	return month;
}
/*
función para leer csv (task.csv) 
*/
char *get_csv_field (char * tmp, int k) {
	int open_mark = 0;
	char* ret=(char*) malloc (100*sizeof(char));
	int ini_i=0, i=0;
	int j=0;
	while(tmp[i+1]!='\0' && tmp[i+1]!='\n'){
		if(tmp[i]== '\"'){
			open_mark = 1-open_mark;
			if(open_mark) ini_i = i+1;
			i++;
			continue;
		}
		if(open_mark || tmp[i]!= ','){
			if(k==j) ret[i-ini_i] = tmp[i];
			i++;
			continue;
		}
		if(tmp[i]== ','){
			if(k==j) {
				ret[i-ini_i] = 0;
				return ret;
			}
			j++; ini_i = i+1;
		}
		i++;
	}
	if(k==j) {
		ret[i-ini_i] = 0;
		return ret;
	}
	return NULL;
}
/*
función para importar los datos desde el archivo csv a mapTask y retorna la cantidad de elementos que este posee
*/
int importarTareasDesdeUnArchivo (Map* mapTask) {
	FILE *fp = fopen ("task.csv", "r");
	int contTask = 0;
	char linea[1024];
	while(fgets (linea, 1023, fp) != NULL) {
		char *aux;
		task* t = (task*) malloc (sizeof(task));		
		t->number = atoi(get_csv_field(linea,0));
		aux = get_csv_field(linea,1);
		strcpy(t->name,aux);
		aux = get_csv_field(linea,2);
    	strcpy(t->description,aux);
		t->priority = atoi(get_csv_field(linea,3));
		t->day = atoi(get_csv_field(linea,4));
		t->category = atoi(get_csv_field(linea, 5));
		t->state = atoi(get_csv_field(linea, 6));
		insertMap (mapTask, &t->number, t);
		contTask++;	
	}
	return contTask;
}
/*
función para agregar tareas a mapTask e importa las tareas del archivo csv si el usuario desea usar tareas predefinidas para utilizar la aplicacion
*/
void agregarTareas (Map* mapTask) {
	int option = 0;
	int contTask = 0;
	printf("¿Desea ingresar tareas predefinidas a calendario?\n Ingrese opcion numerica:\n1. si\n2. no\n");
	scanf("%d", &option);
	if ( option == 1) {
		contTask = importarTareasDesdeUnArchivo(mapTask);
	}
	int tasks;
	printf("Ingrese cantidad de tareas que desea agregar: \n");
	scanf("%d", &tasks);
	tasks = tasks + contTask;
	int i = contTask + 1;
	int auxNumber = contTask + 1;
	char auxName[20];
	char auxDescription[100];
	int auxPriority = 0;
	int auxDay = 0;
	int auxCategory = 0;
	int auxState = 0;
	while (i <= tasks) {
		task* t = (task*) malloc (sizeof(task));
		t->number = auxNumber;
		printf("Ingrese nombre tarea: \n");
		getchar();
		scanf("%[^\n]s",auxName);
		getchar();
		strcpy(t->name, auxName);
		printf("Ingrese descripcion tarea: \n");
		scanf("%[^\n]s",auxDescription);
		getchar();
		printf("%s %s\n", auxName, auxDescription);
		strcpy(t->description, auxDescription);
		printf("Ingrese numero correspondiente a prioridad de tarea: \n");
		printf("1. Urgente / Importante \n");
		printf("2. No Urgente / Importante \n");
		printf("3. Urgente / No Importante \n");
		printf("4. No Urgente / No Importante \n");
		scanf("%d", &auxPriority);
		t->priority = auxPriority;
		printf("Ingrese dia a realizar tarea: \n");
		printf("Solo se puede ingresar una tarea por dia");
		scanf("%d", &auxDay);
		t->day = auxDay;
		printf("Ingrese numero correspondiente a categoria de tarea: \n");
		printf("1. universidad \n2. casa\n3. salud/bienestar\n4. estudio personal\n5. compras\n6. social\n7. ocio/recreación\n8. otro\n");
		scanf("%d", &auxCategory);
		t->category = auxCategory;
		printf("Ingrese numero correspondiente a estado de la tarea: \n");
		printf("1. en proceso \n2. realizada\n3. no realizada\n");
		scanf("%d", &auxState);
		t->state = auxState;
		insertMap (mapTask, &t->number, t);
		auxNumber++;
		i++;
	}
}
/*
funcion que recibe el numero correspondiente a estado y retorna la palabra para imprimirla
*/
char* convertidorDeNumeroAEstado (int number) {
	char* AuxState = (char*) malloc (sizeof(char )*15);
	if (number == 1) strcpy(AuxState,"en progreso");
	if (number == 2) strcpy(AuxState,"realizada");
	if (number == 3) strcpy(AuxState,"no realizada");
	return AuxState;
}
/*
funcion que recibe el numero correspondiente a prioridad y retorna la palabra para imprimirla
*/
char* convertidorDeNumeroAPrioridad (int number) {
	char* AuxState = (char*) malloc (sizeof(char )*15);
	if (number == 1) strcpy(AuxState,"urgente/importante");
	if (number == 2) strcpy(AuxState,"no urgente/importante");
	if (number == 3) strcpy(AuxState,"urgente/no importante");
	if (number == 4) strcpy(AuxState,"no urgente/no importante");
	return AuxState;
}
/*
funcion que recibe el numero correspondiente a categoria y retorna la palabra para imprimirla
*/
char* convertidorDeNumeroACategoria (int number) {
	char* AuxState = (char*) malloc (sizeof(char )*15);
	if (number == 1) strcpy(AuxState,"universidad");
	if (number == 2) strcpy(AuxState,"casa");
	if (number == 3) strcpy(AuxState,"salud/bienestar");
	if (number == 4) strcpy(AuxState,"estudio personal");
	if (number == 5) strcpy(AuxState,"compras");
	if (number == 6) strcpy(AuxState,"social");
	if (number == 7) strcpy(AuxState,"ocio/recreación");
	if (number == 8) strcpy(AuxState,"otro");
	return AuxState;
}
/*
función que muestra todos los datos de las tareas ingresadas.
*/
void mostrarTareas (Map* mapTask) {
	task *Tarea = (task *) firstMap(mapTask);
	printf("numero |       nombre        |          prioridad       |dia|   categoria   |   estado   |    descripcion    \n");	
	while (Tarea != NULL) {
		printf("%7d| %20s| %25s|%3d|%15s|%12s| %s\n", Tarea->number, Tarea->name, convertidorDeNumeroAPrioridad(Tarea->priority), Tarea->day, convertidorDeNumeroACategoria(Tarea->category), convertidorDeNumeroAEstado(Tarea->state), Tarea->description);
		Tarea = (task *) nextMap(mapTask);
	}
}
/*
función que busca la tarea por numero en mapTask y permite al usuario modificar nombre, descripcion, prioridad, dia y categoria de una tarea 
*/
void modificarTarea (Map* mapTask) {
	int taskId;
	task *t;
	printf("\nIngrese numero de tarea que desea modificar: \n");
  	scanf("%d",&taskId);
	t = searchMap(mapTask, &taskId);
	if (t != NULL) {
		printf("Ingrese el número de la opción que desea modificar: \n");
		printf("1. nombre\n2. descripcion\n3. prioridad\n4. dia \n5. categoria\n");
		int option;
		char AuxName [20];
		char AuxDescription [100];
		int AuxPriority;
		int AuxDay;
		int AuxCategory;
		scanf("%d", &option);
		if (option == 1) {
			printf("Ingrese nuevo nombre: \n");
			scanf("%s",AuxName);
			strcpy(t->name, AuxName);
		}
		if (option == 2) {
			printf("Ingrese nueva descripcion: \n");
			scanf("%s",AuxDescription);
			strcpy(t->description, AuxDescription);
		}
		if (option == 3) {
			printf("Ingrese nuevo numero correspondiente a prioridad de tarea: \n");
			printf("1. Urgente / Importante \n");
			printf("2. No Urgente / Importante \n");
			printf("3. Urgente / No Importante \n");
			printf("4. No Urgente / No Importante \n");
			scanf("%d", &AuxPriority);
			t->priority = AuxPriority;
		}
		if (option == 4) {
			printf("Ingrese nuevo dia a realizar tarea: \n");
			scanf("%d", &AuxDay);
			t->day = AuxDay;	
		}
		if (option == 5) {
			printf("Ingrese nuevo numero correspondiente a categoria de tarea: \n");
			printf("1. universidad \n2. casa\n3. salud/bienestar\n4. estudio personal\n5. compras\n6. social\n7. ocio/recreación\n8. otro\n");
			scanf("%d", &AuxCategory);
			t->category = AuxCategory;
		}
		printf("Modificacion realizada exitosamente");
	}
	else printf ("Tarea no encontrada");
}
/*
función que busca la tarea por numero en mapTask y elimina tarea mostrando si se elimina correctamente o no fue encontrada
*/
void eliminarTarea (Map* mapTask) {
	int taskId;
	task *t;
	printf("\nIngrese numero de tarea que desea eliminar: \n");
  	scanf("%d",&taskId);
	t = searchMap(mapTask, &taskId);
	if (t != NULL) {
		t = eraseMap(mapTask, &taskId);
		printf("Tarea eliminada exitosamente");
	}
	else printf ("Tarea no encontrada");
}
/*
función que busca la tarea por numero en mapTask y actualiza el estado de la tarea a: en proceso, realizada o no realizada y muestra mensaje si actualizacion fue exitosa o la tarea no fue encontrada
*/
void actualizarEstadoDeTarea (Map* mapTask) {
	int taskId;
	task *t;
	printf("\nIngrese numero de tarea que desea actualizar (estado): \n");
  	scanf("%d",&taskId);
	t = searchMap(mapTask, &taskId);
	if (t != NULL) {
		int AuxState;
		printf("Ingrese numero correspondiente a estado de la tarea: \n");
		printf("1. en proceso \n2. realizada\n3. no realizada\n");
		scanf("%d", &AuxState);
		if (t->state == AuxState) {
			printf("Tarea ya se encuentra en estado que se desea modificar");
		}
		else t->state = AuxState; printf("Estado modificado exitosamente");
	}
	else printf ("Tarea no encontrada");
}
/*
funcion que recorre mapTask e imprime todas las tareas que pertenezcan a la prioridad ingresada
*/
void mostrarTareasDeUnaPrioridad(Map *mapTask, int prioridad) {
	task *Task = (task *) firstMap (mapTask);
	while (Task != NULL) {
		if (Task->priority == prioridad ) {
			printf("|%6d|%20s|%25s|\n", Task->number, Task->name, convertidorDeNumeroAPrioridad(Task->priority));
		}
		Task = (task *) nextMap (mapTask);
	}
}
/*
funcion que sirve para mostrar tareas ordenadas por prioridad, en donde se muestra el numero, nombre y prioridad de la tarea
*/
void mostrarTareasOrdenadosPorPrioridad (Map* mapTask) {
	printf(" -----------------------------------------------------\n");
	printf("|numero|       nombre       |         prioridad       |\n");
	printf(" -----------------------------------------------------\n");
	for (int i = 0; i <= 4; ++i) {
		mostrarTareasDeUnaPrioridad(mapTask, i);
	}
	printf(" -----------------------------------------------------\n");
}
/*
funcion qsort que se usa para ordenar el vector de tareas por día de manera ascendente
*/
int compararDias(const void *a, const void *b) {
	task **A = (task **) a;
	task **B = (task **) b;

	return (*A)->day - (*B)->day;
}
/*
funcion que pide al usuario que ingrese numero correspondiente a fecha que desea buscar y retorna el dia, numero, fecha y estado de las tareas.
*/
void mostrarTareasHastaXFecha (Map* mapTask) {
	if (firstMap(mapTask) == NULL) {
		printf("No existen tareas\n");
		return ;
	}
	int day;
	printf("\nIngrese fecha hasta la cúal desea buscar: \n");
  	scanf("%d",&day);

	task *Task = (task *) firstMap (mapTask);
	task *vector_aux[100];
	int cantidad = 0;

	while (Task != NULL) {
		vector_aux[cantidad] = Task;
		cantidad++;
		Task = (task *) nextMap (mapTask);
	}
	
	qsort(vector_aux, cantidad, sizeof(task *), compararDias);
	printf(" --------------------------------------------\n");
	printf("|dia|numero|       nombre       |   estado   |\n");
	printf(" --------------------------------------------\n");
	for (int i = 0; i < cantidad && vector_aux[i]->day <= day; ++i)
	{	
		printf("|%3d|%6d|%20s|%12s|\n", vector_aux[i]->day, vector_aux[i]->number, vector_aux[i]->name, convertidorDeNumeroAEstado(vector_aux[i]->state));
	}
	printf(" --------------------------------------------\n");
}
/*
funcion que calcula el porcentaje de tareas realizadas y muestra mensaje dependiendo del rango en que se encuentre e imprime graficamnete el avance.
*/
void mostrarPorcentajeDeProgreso (Map* mapTask){
	task *Tarea = (task *) firstMap(mapTask);
	int contTask = 0;
	int taskDone = 0;

	while (Tarea != NULL) {
		if (Tarea->state == 2) {
			taskDone++;
		}
		Tarea = (task *) nextMap(mapTask);
		contTask++;
	}

	double percent = 0;
	percent = (taskDone * 100)/contTask;

	for (int i = 0; i < percent; i++) {
		printf("▓");
	}
	for (int i = 0; i < (100-percent); i++) {
		
		printf("░");
	}
	printf("%0.f/100 \n",percent);
	if (percent < 50) {
		printf("Aun queda camino por recorrer, keep going\n");
	}
	if ((percent > 75) && (percent < 100)) {
		printf("Buen trabajo, sigue así\n");
	}
	if (percent == 100) {
		printf("Felicidades, nos alegramos de contribuir a que logres tus metas\n");
	}
}
/*
funcion que muestra lista de tareas ordenadas por fecha de acuerdo a estado ingresado, del cual se muestra, el numero, dia y nombre
*/
void mostrarListaPorEstado (Map* mapTask) {
	int state;
	printf("Ingrese numero correspondiente a estado de la tarea: \n");
	printf("1. en proceso \n2. realizada\n3. no realizada\n");
	scanf("%d", &state);

	task *Task = (task *) firstMap (mapTask);
	task *vector_aux[100];
	int cantidad = 0;

	while (Task != NULL) {
		vector_aux[cantidad] = Task;
		cantidad++;
		Task = (task *) nextMap (mapTask);
	}
	
	qsort(vector_aux, cantidad, sizeof(task *), compararDias);
	printf("Tareas en estado: %s\n",convertidorDeNumeroAEstado(state));
	printf(" -------------------------------\n");
	printf("|dia|numero|       nombre       |\n");
	printf(" -------------------------------\n");
	if ((state >= 1) && (state <= 3)) {
		for (int i = 1; i < cantidad; i++) {	
			if (vector_aux[i]->state == state) {
				printf("|%3d|%6d|%20s|\n", vector_aux[i]->day, vector_aux[i]->number, vector_aux[i]->name);
			}
		}
	printf(" -------------------------------\n");
	}
	else
	{
		printf("Estado ingresado no es valido\n");
	}
}
/*
funcion que imprime el nombre del mes en el que se utiiza la aplicacion en el calendario
*/
char* imprimirMes (int number) {
	char* AuxState = (char*) malloc (sizeof(char )*15);
	if (number == 1) strcpy(AuxState,"enero");
	if (number == 2) strcpy(AuxState,"febrero");
	if (number == 3) strcpy(AuxState,"marzo");
	if (number == 4) strcpy(AuxState,"abril");
	if (number == 5) strcpy(AuxState,"mayo");
	if (number == 6) strcpy(AuxState,"junio");
	if (number == 7) strcpy(AuxState,"julio");
	if (number == 8) strcpy(AuxState,"agosto");
	if (number == 9) strcpy(AuxState,"septiembre");
	if (number == 10) strcpy(AuxState,"octubre");
	if (number == 11) strcpy(AuxState,"noviembre");
	if (number == 12) strcpy(AuxState,"diciembre");
	return AuxState;
}
/*
funcion que sirve para saber si existen tareas pertenecientes al dia ingresado
*/
int existenTareas (Map *mapTask, int day) {
	int cont = 0;
	task *Task = (task *) firstMap (mapTask);
	while (Task != NULL) {
		if (Task->day == day ) {
			cont++;
		}
		Task = (task *) nextMap (mapTask);
	}
	return cont;
}
/*
funcion que escribe la tarea perteneciente al dia ingresado
*/
void imprimirTareas (Map *mapTask, int day) {
	task *Task = (task *) firstMap (mapTask);
	while (Task != NULL) {
		if (Task->day == day ) {
			printf("%20s", Task->name);
		}
		Task = (task *) nextMap (mapTask);
	}
}
/*
funcion que recibe el mes y retorna cuantos espacios debe imprimir para que cuadre con el dia en que comienza el mes
*/
int espaciosDesplazadosInicio (int numero){
int spaces = 0;
	switch (numero) {
		case 1: spaces = 4; break;
		case 2: spaces = 0; break;
		case 3: spaces = 0; break;
		case 4: spaces = 3; break;
		case 5: spaces = 5; break;
		case 6: spaces = 1; break;
		case 7: spaces = 3; break;
		case 8: spaces = 6; break;
		case 9: spaces = 2; break;
		case 10: spaces = 4; break;
		case 11: spaces = 0; break;
		case 12: spaces = 2; break;
	}
return spaces;
}
/*
funcion que retorna cuantos dias tiene el mes 
*/
int diasMes (int numero) {
int days = 0;
	switch (numero) {
		case 1: days = 31; break;
		case 2: days = 28; break;
		case 3: days = 31; break;
		case 4: days = 30; break;
		case 5: days = 31; break;
		case 6: days = 30; break;
		case 7: days = 31; break;
		case 8: days = 31; break;
		case 9: days = 30; break;
		case 10: days = 31; break;
		case 11: days = 30; break;
		case 12: days = 31; break;
	}
return days;
}
/*
funcion que muestra nombre de las tareas del mes ingresado en la aplicacion 
*/
void mostrarCalendario(Map* mapTask) {
	int month = ingresarMes(mapTask);
	printf
	("Montly To-do List %s\n",imprimirMes(month));
	printf
	("--------------------------------------------------------------------------------------------------------------------------------------------\n");
	printf
	("      lunes             martes             miercoles            jueves              viernes              sabado             domingo    \n");
	printf
	("--------------------------------------------------------------------------------------------------------------------------------------------\n");
	int startDay = espaciosDesplazadosInicio(month); 
	int cont = 0;
	for (int i = 1; i <= startDay; i++){
			printf("                    ");
		}
	for (int i = 1; i <= diasMes(month); ++i) {
		cont = existenTareas (mapTask, i);
		if (cont == 0) {
			printf ("%2i                  ",i);
		}
		else {
			imprimirTareas(mapTask, i);
		}
		int border = 7-startDay; 
		if ((i == border) || (i == border+7) || (i == border+14) || (i == border+21) || (i == border +28) ){
			printf ("\n");
		}
	}
}
