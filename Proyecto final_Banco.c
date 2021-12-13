#include<stdio.h>
#include<locale.h>
#include<stdbool.h>
#include<windows.h>
#include<stdlib.h>
#include<string.h>
typedef struct{
	int iNumCuenta;
}regContacto;

typedef struct{
	int iCuentaRemitente;
	int iCuentaDestino;
	float fImporte;
}regTransaccion;

typedef struct{
	int iNumCuenta;
	char *cNombre;
	char *cPassword;
	float fDinero;
	int iNumAmigos;
	int iNumTransferencias;
	regContacto *vtrAmigos;
	regTransaccion *vtrHistorial;
}regUsuario;


void vMenu();
void vRegistro();
void vRegistrar(char *, char *, int);
void vVerUsuarios();
void vMenuUsuario();

char *cObtenerTexto(char *, int);
int iObtenerNumero(char *);
float fObtenerNumero(char *);
int iGenerarNumeroCuenta();
void vAgregarContacto();
bool bContactoExiste(int, regUsuario *);
void vVerContactos();

char op;
int nombre,cont;
float i,a,c,m,r;
void menu();
void depositar(int cantidad);
void retirar(int cantidad);



int saldoa = 0.00;
int cantidad;

bool bLogin();

regUsuario *vtrBaseUsuarios;
int iNumeroUsuarios=0;
int iSessionNumUsuario;

void vMenuUsuario()
{
    while(1)
{


    int opc;

printf("\nBIENVENIDOS AL CAJERO BANCARIO");
	printf("\n1. Consultar saldo");
	printf("\n2. Depositar");
	printf("\n3. Retirar");
	printf("\n4. Salir");
	printf("\nDigite su opcion: ");
	scanf("%i" , &opc);
	switch(opc)
	{
		case 1: printf("\nTu saldo actual es de %i " , saldoa);
		break;
system("cls");
		case 2:
		printf("\nCuanto dinero desea depositar: ");
		scanf("%i" , &cantidad);
		depositar(cantidad);
		break;

		case 3:
		printf("\nCuanto dinero desea retirar: ");
		scanf("%i" , &cantidad);
		retirar(cantidad);
		break;

		case 4:
		    printf("Salir\n");
 exit(0);
			break; // CERRAMOS EL PROGRAMA

		default:
			printf("\nOpcion no valida");


	}


}
printf("Presione una tecla para regresar al menu principal.\n");
getch();
}
void depositar(int cantidad)
{

	saldoa += cantidad; // ACTUALIZAMOS EL SALDO ACTUAL
	printf("\nHas depositado exitosamente %i pesos, tu saldo actual es de %i pesos" , cantidad , saldoa );

}

void retirar(int cantidad)
{
	if (cantidad <= saldoa)
	{

	saldoa -= cantidad;

	printf("\nHas retirado exitosamente %i pesos, tu saldo actual es de %i pesos" , cantidad , saldoa );

	}
	else
	{
		printf("\nNo tienes suficiente dinero, tu saldo actual es de %i", saldoa);
	}

}
int main()
{
	setlocale(LC_ALL, "");

	vtrBaseUsuarios=(regUsuario *)malloc(sizeof(regUsuario));
	vRegistrar("Zayma", "Contraseña", 1);

	vMenu();

	return 0;
}

void vMenu()
{
	bool bSalir=false;
	char cOpcion[2];
	int iOpcion;
	do
	{
		system("CLS");
		printf("\nBIENVENIDO AL CAJERO BANCARIO\nElija una opción:\n");
		printf("1:Registrarse\n2:Iniciar Cesión\n3:Ver Usuarios\n4:Salir\n");
		scanf("%s", cOpcion);
		iOpcion=atoi(cOpcion);
		switch(iOpcion)
		{
			case 1:
					vRegistro();
				break;
			case 2:{
					if(bLogin()==true)
					vMenuUsuario();
				}
				break;
			case 3:
					vVerUsuarios();
				break;
			case 4:
					bSalir=true;
				break;
			default: printf("Parametro Invalido\n");
		}
	}while(bSalir==false);
	system("PAUSE");
}
void vRegistro(){
		char *cNombre=cObtenerTexto("Ingrese su nombre", 0);
		char *cPassword=cObtenerTexto("Ingrese su contraseña (Minimo 8 Caracteres)", 8);
		int iNumeroCuenta=iGenerarNumeroCuenta();

		vRegistrar(cNombre, cPassword, iNumeroCuenta);

		printf("Su numero de cuenta es: %d\n", iNumeroCuenta);
		system("PAUSE");
}
void vRegistrar(char *cNombre, char *cPassword, int iNumCuenta)
{

	vtrBaseUsuarios[iNumCuenta-1].cNombre=(char *)malloc(sizeof(char));
	vtrBaseUsuarios[iNumCuenta-1].cPassword=(char *)malloc(sizeof(char));

	regUsuario *vtrUsuario;
	vtrUsuario=&vtrBaseUsuarios[iNumCuenta-1];

	strcpy(vtrUsuario->cNombre, cNombre);
	strcpy(vtrUsuario->cPassword, cPassword);

	vtrUsuario->iNumCuenta=iNumCuenta;
	vtrUsuario->fDinero=0;
	vtrUsuario->iNumAmigos=0;
	vtrUsuario->iNumTransferencias=0;
	iNumeroUsuarios++;
}
void vVerUsuarios()
{
	int i;

	if(iNumeroUsuarios>0)
	{
		for(i=0; i<iNumeroUsuarios; i++)
		{
			printf("Nombre: %s \t Número de Cuenta: %d\n", vtrBaseUsuarios[i].cNombre, vtrBaseUsuarios[i].iNumCuenta);
		}
	}
	else
		printf("Aún no hay usuarios registrados\n");

	system("PAUSE");
}

char *cObtenerTexto(char *cPeticion, int iLongitud)
{
	char *cTexto;
	bool bValido=false;
	cTexto=(char *)malloc(sizeof(char));
	do
	{
		fflush(stdin);
		system("CLS");
		printf("%s: ", cPeticion);
		scanf("%[^\n]", cTexto);

		if(strcmp(cTexto, ""))
		{
			bValido=(iLongitud<=0)?true:false;
			if(bValido==false)
			{
				bValido=(strlen(cTexto)>=iLongitud)?true:false;
			}
		}
	}while(!bValido);
	return cTexto;
}

int iObtenerNumero(char *peticion)
{
	char *cNumero;
	int iNumero;
	cNumero=(char *)malloc(sizeof(char));
	do
	{
		fflush(stdin);
		printf("%s: ", peticion);
		scanf("%s", cNumero);
		iNumero=atoi(cNumero);
	}while(iNumero<=0);
	return iNumero;
}

float fObtenerNumero(char *peticion)
{
	char *cNumero;
	float fNumero;
	cNumero=(char *)malloc(sizeof(char));
	do
	{
		fflush(stdin);
		printf("%s: ", peticion);
		scanf("%s", cNumero);
		fNumero=atof(cNumero);
	}while(fNumero<=0);
	return fNumero;
}

int iGenerarNumeroCuenta()
{
	if(iNumeroUsuarios==0)
	{
		vtrBaseUsuarios=(regUsuario *)malloc(sizeof(regUsuario));
		return iNumeroUsuarios+1;
	}
	else{
		vtrBaseUsuarios=(regUsuario *)realloc(vtrBaseUsuarios, sizeof(regUsuario)*(iNumeroUsuarios+1));
		return iNumeroUsuarios+1;
	}
}

bool bLogin()
{
	bool logged=false;
	int iNumCuenta=iObtenerNumero("Ingrese su número de cuenta");
	if(iNumCuenta<=iNumeroUsuarios)
	{
		char *cPassword=cObtenerTexto("Ingrese su contraseña", 0);
		logged=(strcmp(cPassword, vtrBaseUsuarios[iNumCuenta-1].cPassword)==0)?true:false;
		if(logged==true)
		{
			printf("Las contraseñas coinciden\n");
			iSessionNumUsuario=iNumCuenta;
		}
		else
			printf("Las contraseñas no coinciden\n");
	}
	else
		printf("Numero de cuenta inexistente\n");

	system("PAUSE");
	return logged;

}

