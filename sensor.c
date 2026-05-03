//Proyecto: Sistema SCADA Industrial
//Autor: Ivan Rodriguez Nuñez
//Fecha: Mayo 2026
#include <stdio.h>
#include <string.h>

//se define el struct de la planta
typedef struct{
    char nombre[20];
    float temperatura;
    float humedad;
    int activo;
}Planta;


//Muestra las plantas con una temperatura mayor a 30°C

int EvaluarSensor(Planta *c, int indice){
    if(c[indice].temperatura < 25){
        return 0;
      }
     else if(c[indice].temperatura  >= 25 && c[indice].temperatura < 30 ){
        return 1;
     }
     else if(c[indice].temperatura >=30 && c[indice].temperatura < 40 ){
        return 2;
     }
     else{
         return 3;
     }
}

//Indica el estado de cada uno de los sensores
void ReportePlanta(Planta *s, int cantidad){
    for(int i=0;i<cantidad;i++){
        printf("Nombre: %s\n",s[i].nombre);
        printf("Temperatura: %.2f °C\n",s[i].temperatura);
        printf("Humedad: %.2f\n",s[i].humedad);
        printf("Activo: %d\n\n", s[i].activo);
    	switch(EvaluarSensor(s, i)){
            case 0:
                printf("Nivel NORMAL\n");
                printf("Accion TODO BIEN\n\n");
                break;
            case 1:
                printf("Nivel ADVERTENCIA\n");
                printf("Accion MONITOREAR\n\n");
                break;
            case 2:
                printf("Nivel CRITICO\n");
                printf("Accion INTERVENIR\n\n");
                break;
            case 3:
                printf("Nivel EMERGENCIA\n");
                printf("Accion PARAR PLANTA\n");
                break;

        }

    }
}

//funcion que genera un reporte
void reporteResumen(Planta *r,int indice){

//variables de la funcion
    float Temp_Max= r[0].temperatura;
    int normales=0;
    int advertencia=0;
    int criticos=0;
    int emergencia=0;

    for(int i=0;i<indice;i++){
	if(Temp_Max < r[i].temperatura){
            Temp_Max=r[i].temperatura;
}
	switch(EvaluarSensor(r, i)){
            case 0:
		normales ++;
                break;
            case 1:
                advertencia++;
                break;
            case 2:
                criticos ++;
                break;
            case 3:
                emergencia ++;
                break;
}
}
    printf("Sensores Normales: %d\n", normales);
    printf("Sensores con Advertencia: %d\n", advertencia);
    printf("Sensores Criticos: %d\n", criticos);
    printf("Sensores con Emergencia: %d\n", emergencia);
    printf("Temperatura Maxima: %.2f °C\n", Temp_Max);

};

int main(){

    //int Num_Evaluador=0;

    //se crea el arreglo sensor
    Planta Sensor[]= {
        {"S1", 27.5, 65.20, 1},
        {"S2", 30.53, 80.50, 0},
        {"S3", 36.5, 90.50, 1},
        {"S4", 25.5, 30.50, 0},
        {"S5", 21.3, 20.50, 1}
    };//valores de los sensores

    //Numero de sensores
    int Num_sensores = sizeof(Sensor) / sizeof(Sensor[0]);

    ReportePlanta(Sensor,Num_sensores);
    reporteResumen(Sensor,Num_sensores);
    return 0;
}

