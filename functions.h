#ifndef functions_h
#define functions_h

typedef struct task {
	int number;
	char name[20];
	char description[100];
	int priority;
	int day;
	int category;
	int state;
} task;

int is_equal_int(void * key1, void * key2);

int lower_than_int(void * key1, void * key2);

int is_equal_string(void * key1, void * key2);

int lower_than_string(void * key1, void * key2);

int ingresarMes (Map* mapTask);

char *get_csv_field (char * tmp, int k);

int importarTareasDesdeUnArchivo (Map* mapTask);

void agregarTareas (Map* mapTask);

char* convertidorDeNumeroAEstado (int);

char* convertidorDeNumeroAPrioridad (int);

char* convertidorDeNumeroACategoria (int);

void mostrarTareas (Map* mapTask);

void modificarTarea (Map* mapTask);

void eliminarTarea (Map* mapTask);

void actualizarEstadoDeTarea (Map* mapTask);

void mostrarTareasDeUnaPrioridad(Map *mapTask, int prioridad);

void mostrarTareasOrdenadosPorPrioridad (Map* mapTask);

int compararDias(const void *a, const void *b);

void mostrarTareasHastaXFecha (Map* mapTask);

void mostrarPorcentajeDeProgreso (Map* mapTask);

void mostrarListaPorEstado (Map* mapTask);

char* imprimirMes (int number);

int existenTareas (Map *mapTask, int day);

void imprimirTareas (Map *mapTask, int day);

int espaciosDesplazadosInicio (int numero);

int diasMes (int numero);

void mostrarCalendario(Map* mapTask);

#endif
