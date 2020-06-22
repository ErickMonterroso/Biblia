/*
ERICK MONTERROSO
*/



#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <string.h>
#include <cstdlib>
#include <math.h>
#include <windows.h>
#include <locale.h>



using namespace std;
void busqueda();
void cargararchivo();
void carga();
void menu();


void gotoxy(int x, int y)
{
    setlocale(LC_ALL,"");
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD dwPos;
    dwPos.X = x;
    dwPos.Y = y;
    SetConsoleCursorPosition(hcon, dwPos);
}

bool string_comparacion(string s1, string s2){
    setlocale(LC_ALL,"");
   if(s1.size() == s2.size()){
       for(int i = 0; i < s1.size(); ++i){
           if(tolower(s1[i]) != tolower(s2[i]))
               return false;
       }
       return true;
   }
   return false;
}


bool comienzo(string s1, string s2){
    setlocale(LC_ALL,"");
   if(s1.size() > s2.size()){
       for(int i = 0; i < s2.size(); ++i){
           if(tolower(s1[i]) != tolower(s2[i]))
               return false;
       }
       return true;
   }
   return false;
}

string buscar_verso(ifstream &biblia, string libro, string numero_capitulo, string numero_versiculo, bool &encontrar_libro,
                  bool &encontrar_capitulo, bool &encontrar_verso){
                      setlocale(LC_ALL,"");
   encontrar_libro = false, encontrar_capitulo = false, encontrar_verso = false;
   string linea;
   // search for book
   while(getline(biblia, linea)){
       if(string_comparacion(linea, libro)){
           encontrar_libro = true;
           break;
       }
   }
   if(encontrar_libro){
       // search for chapter
       string capitulo = "CAPITULO " + numero_capitulo;
       while(getline(biblia, linea)){
           if(string_comparacion(linea, capitulo)){
               encontrar_capitulo = true;
               break;
           }
       }
       if(encontrar_capitulo){
           // search for verse
           while(getline(biblia, linea)){
               if(comienzo(linea, numero_versiculo)){
                   encontrar_verso = true;
                   break;
               }
           }
           if(encontrar_verso){
               return linea;
           }
       }
   }
   return "";
}

int main()
{
    setlocale(LC_ALL,"");
    menu();
    return 0;
}
void busqueda(){
    system("cls");
    setlocale(LC_ALL,"");
    gotoxy(20, 1);
    system("Color A");
    string libro, capitulo, versiculo;
   bool encontrarlibro, encontrarcapitulo, encontrarversiculo;
   ifstream DataBiblia;
   ofstream bibleOutput;
   // open the input and output files
   DataBiblia.open("nombreLibroSinEspacios.dat");
   if (DataBiblia.fail()){
       cout << "\n\t\tError abriendo, sin registros...\n\n\n";
       system("pause");
       exit(1);
   }


   // book,chapter, and verse
   cin.ignore();
   cout<< "INGRESE LA CITA A BUSCAR\n"<<endl;
   cout<<"Libro: ";
   getline(cin, libro);
   cout<<"capitulo: ";
   getline (cin,capitulo);
   cout<<"versiculo:";
   getline (cin, versiculo);
   cout<<" "<<endl;
   cout << ""<<libro << " " << capitulo <<" "<< versiculo << endl;
   string versiculo_completo = buscar_verso(DataBiblia, libro, capitulo, versiculo, encontrarlibro, encontrarcapitulo, encontrarversiculo);

   if(!encontrarlibro){
       cout << "ese libro no existe en la base de datos \"" << libro << "\"" << endl;
       system("pause");
       exit(1);
   }
   if(!encontrarcapitulo){
       cout << "El libro " << libro << " no tiene el capitulo " << capitulo << endl;
       system("pause");
       exit(1);
   }
   if(!encontrarversiculo){
       cout << "CAPITULO " << capitulo << " DEL LIBRO " << libro << " NO TIENE El VERSICULO " << versiculo << endl;
       system("pause");
       exit(1);
   }
   cout<<" " <<versiculo_completo << endl;
   system("pause");
   system("cls");
   menu();

}

void menu(){
    setlocale(LC_ALL,"");
    system("Color A");
    gotoxy(20, 1);
    cout <<"\n\t\t\tMENU"<<endl;
    cout<<"\t\t1.Leer y cargar archivo"<<endl;
    cout<<"\t\t2.Buscar cita biblica"<<endl;
    cout<<"\t\t3.Salir"<<endl;

    cout << "\n\t Que opcion desea ejecutar?: ";
    int opcion = 0;
    cin >> opcion;

    switch(opcion)
    {
        case 1: system("cls");cout << " \t\tCARGA DE ARCHIVO\n";
        carga();
        break;
        case 2: cout << "2. BUSQUEDA\n";
        busqueda();
        break;
        case 3: system("cls");cout << "\n\n\t\tSaliendo... \n"; break;
        default: cout << "Usted ha ingresado una opción incorrecta";
    }
}

void carga(){
setlocale(LC_ALL,"");
gotoxy(20, 1);
system("Color A");
ifstream origen;
    char linea[100000]; //char linea2 = linea.substr (3,80);
    char cap[10]="CAPITULO";
    string libro= "";
    string nombreArchivo;
    char buffer[8]="";// SCYP
    cin.ignore();
    int len=0,capitulo;

    cout<<"\n\nDigite el nombre de archivo a cargar:\n ";
	getline(cin,nombreArchivo);

	origen.open(nombreArchivo.c_str(),ios::in);

    if(!origen.fail()){
    cout<<"\n\nPara cargar este archivo por favor llenar los siguientes datos:\n\n"<<endl;
    cout<<"Ingrese nombre del libro a guardar?"<<endl;
    getline(cin,libro);
    cout<<"Que capitulo del libro es? "<<endl;
    cin>>capitulo;
    len = (log10(capitulo) + 2);
    }

    if(origen.fail()){
		cout<<"\nNo se pudo abrir el archivo\n";
		system("pause");
		exit(1);
	}
    else
    {
        ofstream destino("nombreLibroSinEspacios.dat", ios::out|ios::app| ios::binary);
        destino<<libro<<endl;
        destino<<cap;
        destino<<" "<<capitulo<<endl;
        if(destino.fail()){
        cout << "\n\nError al crear el archivo: base de datos" << endl;
        system("pause");
        }
        else
        {
            while(!origen.eof())
            {
                origen.getline(linea, sizeof(linea));
                if(origen.good()) // si lectura ok y
                if(origen.eof())  // si eof, -> termina
                exit(1);          // el programa
                else
                destino << linea <<endl;
                //printf("%s\n", strcpy(buffer, &linea[2]));//imprime?
                destino << strcpy(buffer, &linea[len]) <<endl; //25:1SE ELIMINA LOS PRIMEROS DIGITOS PARA FACILITAR BUSQUEDA 2,3
                if(destino.fail())
                {
                    cerr << "\n\nFallo de escritura en archivo" << endl;
                    system("pause");
                    exit(1);
                }
            }

            cout<<"\n\tArchivo Cargado Correctamente"<<endl;
            system("pause");
        }
        destino.close();
    }
    origen.close();
    system("pause");
    system("cls");
    menu();
}
