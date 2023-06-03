#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <string>

#define FILE_NAME "/srv/utem/supermercado.csv"

using namespace std;

string ObtenerMes(string ISO8601){

    stringstream separar(ISO8601);
    string fecha, hora, zonaHoraria;

    getline(separar, fecha, 'T');

    stringstream fechaSS(fecha);
    string ano, mes, dia;

    getline(fechaSS,ano,'-');
    getline(fechaSS,mes,'-');
    getline(fechaSS,dia);

    return mes;
}

string QuitarComillas(string Con_comilla){
        Con_comilla.erase(0, 1);
        Con_comilla.erase(Con_comilla.length() - 1);
        return Con_comilla;
}

int main(){
    char Separador = ';';
    string Linea;
    ifstream file(FILE_NAME);

    int i = 1;
    int PrecioAccMes[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
    int CantAccMes[12] = {0,0,0,0,0,0,0,0,0,0,0,0};
    float FLOAT_IPC[12],FLOAT_INFLACION[12], Promedio = 0;

    int SKU, Monto, Descuento,Num_Mes;
    string Nombre, Fecha, Estado, S_SKU, S_Monto, S_Descuento, Mes;

    getline(file,Linea);
     for(;getline(file, Linea);){

        stringstream stream(Linea);

        getline(stream,S_SKU,Separador);
        getline(stream,Nombre,Separador);
        getline(stream,S_Monto,Separador);
        getline(stream,S_Descuento,Separador);
        getline(stream,Fecha,Separador);
        getline(stream,Estado,Separador);

        S_SKU = QuitarComillas(S_SKU);
        S_Monto = QuitarComillas(S_Monto);
        S_Descuento = QuitarComillas(S_Descuento);
        Estado = QuitarComillas(Estado);

        istringstream(S_SKU)>>SKU;
        istringstream(S_Monto)>>Monto;
        istringstream(S_Descuento)>>Descuento;

        Mes = ObtenerMes(Fecha);
        istringstream(Mes)>>Num_Mes;
        if(Estado == "FINALIZED" || Estado == "AUTHORIZED"){
            CantAccMes[Num_Mes-1]++;
            if((-Descuento) > Monto){
                PrecioAccMes[Num_Mes-1] = PrecioAccMes[Num_Mes-1] + (0 - PrecioAccMes[Num_Mes-1]) / CantAccMes[Num_Mes-1];
            }else{
                PrecioAccMes[Num_Mes-1] = PrecioAccMes[Num_Mes-1] + (Monto + Descuento - PrecioAccMes[Num_Mes-1]) / CantAccMes[Num_Mes-1];
            }
        }
    }

    cout<<"Precios promedio en enero = "<<PrecioAccMes[0]<<endl;
    cout<<"Precios promedio en febrero = "<<PrecioAccMes[1]<<endl;
    cout<<"Precios promedio en marzo = "<<PrecioAccMes[2]<<endl;
    cout<<"Precios promedio en abril = "<<PrecioAccMes[3]<<endl;
    cout<<"Precios promedio en mayo = "<<PrecioAccMes[4]<<endl;
    cout<<"Precios promedio en junio = "<<PrecioAccMes[5]<<endl;
    cout<<"Precios promedio en julio = "<<PrecioAccMes[6]<<endl;
    cout<<"Precios promedio en agosto = "<<PrecioAccMes[7]<<endl;
    cout<<"Precios promedio en septiembre = "<<PrecioAccMes[8]<<endl;
    cout<<"Precios promedio en octubre = "<<PrecioAccMes[9]<<endl;
    cout<<"Precios promedio en noviembre = "<<PrecioAccMes[10]<<endl;
    cout<<"Precios promedio en Diciembre = "<<PrecioAccMes[11]<<endl<<endl;

    FLOAT_IPC[0] = 100;
    for(i = 1;i < 12;i++){
        FLOAT_IPC[i] = 100*(float)PrecioAccMes[i]/(float)PrecioAccMes[0];

        FLOAT_INFLACION[i] = 100*(FLOAT_IPC[i] - FLOAT_IPC[i-1])/FLOAT_IPC[i-1];

    }
    cout<<"El IPC de enero es 100% (IPC base) = "<<100<<"%"<<endl;
    cout<<"El IPC de febrero es = "<<FLOAT_IPC[1]<<"%"<<endl;
    cout<<"El IPC de marzo es = "<<FLOAT_IPC[2]<<"%"<<endl;
    cout<<"El IPC de abril es = "<<FLOAT_IPC[3]<<"%"<<endl;
    cout<<"El IPC de mayo es = "<<FLOAT_IPC[4]<<"%"<<endl;
    cout<<"El IPC de junio es = "<<FLOAT_IPC[5]<<"%"<<endl;
    cout<<"El IPC de julio es = "<<FLOAT_IPC[6]<<"%"<<endl;
    cout<<"El IPC de agosto es = "<<FLOAT_IPC[7]<<"%"<<endl;
    cout<<"El IPC de septiembre es = "<<FLOAT_IPC[8]<<"%"<<endl;
    cout<<"El IPC de octubre es = "<<FLOAT_IPC[9]<<"%"<<endl;
    cout<<"El IPC de noviembre es = "<<FLOAT_IPC[10]<<"%"<<endl;
    cout<<"El IPC de diciembre es = "<<FLOAT_IPC[11]<<"%"<<endl<<endl;

    cout<<fixed<<setprecision(4)<<endl;
    cout<<"Tasa inflacion de febrero = "<<FLOAT_INFLACION[1]<<"%"<<endl;
    cout<<"Tasa inflacion de marzo = "<<FLOAT_INFLACION[2]<<"%"<<endl;
    cout<<"Tasa inflacion de abril = "<<FLOAT_INFLACION[3]<<"%"<<endl;
    cout<<"Tasa inflacion de mayo = "<<FLOAT_INFLACION[4]<<"%"<<endl;
    cout<<"Tasa inflacion de junio = "<<FLOAT_INFLACION[5]<<"%"<<endl;
    cout<<"Tasa inflacion de julio = "<<FLOAT_INFLACION[6]<<"%"<<endl;
    cout<<"Tasa inflacion de agosto = "<<FLOAT_INFLACION[7]<<"%"<<endl;
    cout<<"Tasa inflacion de septiembre = "<<FLOAT_INFLACION[8]<<"%"<<endl;
    cout<<"Tasa inflacion de octubre = "<<FLOAT_INFLACION[9]<<"%"<<endl;
    cout<<"Tasa inflacion de noviembre = "<<FLOAT_INFLACION[10]<<"%"<<endl;
    cout<<"Tasa inflacion de diciembre = "<<FLOAT_INFLACION[11]<<"%"<<endl;

    for(i=1;i < 12;i++){
        Promedio += FLOAT_INFLACION[i];
    }
    Promedio = Promedio/11;

    cout<<"Tasa inflacion acumulada en referencia al mes base = "<<100*(FLOAT_IPC[11]-FLOAT_IPC[0])/FLOAT_IPC[0]<<"%"<<endl;
    cout<<"Tasa inflacion mensual en diciembre = "<<FLOAT_INFLACION[11]<<"%"<<endl;
    cout<<"Tasa inflacion promedio = "<<Promedio<<"%"<<endl;


    file.close();
    return 0;
}
