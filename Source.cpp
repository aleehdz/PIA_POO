#include <Windows.h>
#include <iostream>
#include <string.h>
#include <string>
#include "resource.h"
#include <fstream>
#include <Commctrl.h>
#include <CommDlg.h>
#include <stdio.h>
#include <ctime>
#include <cstdlib
#define _CRT_SECURE_NO_WARNINGS
using namespace std;

struct fecha {
	char dia[3];
	char mes[3];
	char anio[5];
};

struct usuarios {
	usuarios* ant;
	char usuario[70];
	char contrasena[70];
	char nombre[70];
	char empresa[70];
	char fotouser[500];
	usuarios* sig;
};
usuarios* inicio, * aux, * fin, * user = nullptr;

struct cliente {
	int id;
	char nombres[100];         // Nombres
	char apellidoPaterno[50];  
	char apellidoMaterno[50];  
	char correo[100];
	char telefono[15];
	char estatus[20];
	char fechaRegistro[11];     // (YYYY-MM-DD)
	char fechaCambio[11];
	cliente* sig;
	cliente* ant;
};
cliente* inicioCliente = nullptr, * auxCliente = nullptr, * finCliente = nullptr;

struct Tienda {
	int id;
	char nombreT[50];
	char IDT[15];
	char correo[50];
	char estatusT[20];
	char fechaCambioT[11];
	Tienda* sig;  
	Tienda* ant;
};
Tienda* iniciot = nullptr, * auxt = nullptr, * fint = nullptr;

struct productos {
	productos* sig;
	char propietario[200];
	char nombreprod[200];
	char marca[200];
	char descripcion[100];
	int cantidad;
	int codigo;
	char foto1[500] = " ";
	char foto2[500] = " ";
	char estatus[20];
	float monto = 0;    
	float costo = 0;  
	int idTienda;
	productos* ant;
};
productos* iniciop, * auxp, * finp, * prod = nullptr;

struct compra {
	int idC;
	int idCliente;             // ID del que realiza la compra
	int idTienda;              // ID donde se realiza la compra
	int cantidad;              // Productos comprados
	float totalPago;           // Total a pagar
	char fechaCompraC[11];
	char fechaEntregaC[11];
	char estatusC[20];
	compra* sig;
	compra* ant;
};
compra* inicioCompra = nullptr, * auxCompra = nullptr, * finCompra = nullptr;


struct envios {
	envios* sig;
	int id;               
	int idCliente;        
	char estatus[20];
	char repartidor[100] = "";
	char calle[100] = "";
	char colonia[100] = "";
	char ciudad[100] = "";
	char estado[100] = "";
	char mensaje[100] = "";
	float precio = 0;
	int cantidad = 0;
	char producto[100] = "null";
	fecha fechaenvio;
	envios* ant;
};
char flotante[70];
string flot;
envios* inicioe, * auxe, * fine = nullptr;

SYSTEMTIME st;
HBITMAP bmp, bmp1, bmp2;

HINSTANCE instGlobal;
HWND hInsesion;
HWND hInfovendedor, hRegisusua, hNvprod, hEliprod, hEditprod, hMisprod, hRealizarenvi, hCanenvio, hEditenvio, hMisenvio;
WNDPROC lpEditWndProc;

BOOL CALLBACK insesion(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK infovendedor(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK regisusua(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK nvproducto(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK eliproducto(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK editproducto(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK misproducto(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK realizarenvi(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK canenvio(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK editenvio(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK misenvio(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK Numeros(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

void registrousuario(usuarios* nuevo);
void registropr(productos* nuevo);
void registroenvio(envios* nuevo);
void escribirusuarios();
void leerusuario();
void escribirproducto();
void leerproductos();
void escribirenvios();
void leerenvios();
void eliminarprod(productos* auxp);
void eliminarend(envios* auxe);
void quickSort(envios* iniL, envios* finL);
char usuarioinicio[100];
char passwordi[100];

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstPrev, PSTR cmdline, int cmdshow) {
	instGlobal = hInstance;
	leerusuario();
	leerproductos();
	leerenvios();
	hInsesion = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_INSESION), 0, insesion);

	ShowWindow(hInsesion, cmdshow);
	MSG Mensaje;
	ZeroMemory(&Mensaje, sizeof(Mensaje));

	while (GetMessage(&Mensaje, 0, 0, 0)) {
		TranslateMessage(&Mensaje);
		DispatchMessage(&Mensaje);
	}
	return Mensaje.wParam;
}

BOOL CALLBACK insesion(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_INITDIALOG: {}
					  break;
	case WM_COMMAND: {
		switch (LOWORD(wParam)) {
		case IDC_INICIAR_SESION:
			if (aux = inicio) {
				GetDlgItemText(hWnd, IDC_USUARIO, usuarioinicio, 100);
				GetDlgItemText(hWnd, IDC_CONTRASENA, passwordi, 100);
				while (aux != nullptr && strcmp(usuarioinicio, aux->usuario) != 0) {
					aux = aux->sig;
				}
			}
			if (aux == nullptr) {
				MessageBox(hWnd, "No se pudo encontrar su usuario", "", MB_OK | MB_ICONEXCLAMATION);
			}else {
				if (strcmp(passwordi, aux->contrasena) == 0) { 
					user = aux;
					prod = auxp;
					MessageBox(hWnd, "Sesion Iniciada", "", MB_OK);
					hMisenvio = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_MISENVI), 0, misenvio);
					ShowWindow(hMisenvio, SW_SHOW);
					DestroyWindow(hWnd);
				}else {
					MessageBox(hWnd, "Contraseña incorrecta", "", MB_OK | MB_ICONERROR);
				}
			}
			break;
			hInfovendedor = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_INFOVENDEDOR), 0, infovendedor);
			ShowWindow(hInfovendedor, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case IDC_REGISTRARSE:
			hRegisusua = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_REGISUSUA), 0, regisusua);
			ShowWindow(hRegisusua, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		}
	}break;

	case WM_CLOSE: {
		int opc = MessageBox(0, "Seguro que desea salir?", "AVISO", MB_YESNO | MB_ICONQUESTION);
		switch (opc) {
		case IDYES:
			escribirenvios();
			escribirproducto();
			escribirusuarios();
			DestroyWindow(hWnd);
			PostQuitMessage(0);
			break;
		}break;
	}break;
	}
	return 0;
}

BOOL CALLBACK regisusua(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	usuarios* registro = new usuarios;
	int a = 0;

	switch (msg) {
	case WM_INITDIALOG: {
		lpEditWndProc = (WNDPROC)SetWindowLong(GetDlgItem(hWnd, IDC_NVUSUA), GWL_WNDPROC, (LONG)Numeros);
	}break;
	case WM_COMMAND: {
		switch (LOWORD(wParam)) {
		case IDC_BTNREGRESAR:
			hInsesion = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_INSESION), 0, insesion);
			ShowWindow(hInsesion, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case IDC_BTNREGISTRRAR:
			char prueba[100];
			GetDlgItemText(hWnd, IDC_NVUSUA, prueba, 70);
			GetDlgItemText(hWnd, IDC_NVUSUA, registro->usuario, 70);
			GetDlgItemText(hWnd, IDC_NVCONTRA, registro->contrasena, 70);
			aux = inicio;
			while (aux != nullptr && a == 0) {
				if (strcmp(prueba, aux->usuario) == 0) {
					MessageBox(hWnd, "Usuario Repetido", " ", MB_OK);
					a = 1;
				}else {
					aux = aux->sig;
				}
			}
			if (aux == nullptr) {
				registrousuario(registro);
				escribirusuarios();
				MessageBox(hWnd, "Se registro con exito", " ", MB_OK);
				hInfovendedor = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_INFOVENDEDOR), 0, infovendedor);
				ShowWindow(hInfovendedor, SW_SHOW);
				DestroyWindow(hWnd);
			}break;
		}

	}break;
	}
	return 0;
}

BOOL CALLBACK infovendedor(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
	case WM_INITDIALOG: {
		lpEditWndProc = (WNDPROC)SetWindowLong(GetDlgItem(hWnd, IDC_NMBCOMPLETO), GWL_WNDPROC, (LONG)Numeros);
		SetDlgItemText(hWnd, IDC_NMBCOMPLETO, user->nombre);
		SetDlgItemText(hWnd, IDC_ALIASEMPRESA, user->empresa);
		bmp = (HBITMAP)LoadImage(NULL, user->fotouser, IMAGE_BITMAP, 60, 60, LR_LOADFROMFILE);
		SendDlgItemMessage(hWnd, IDC_FOTOIV, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp);	
	}break;
	case WM_COMMAND: {
		switch (LOWORD(wParam)) {
		case IDC_BTNEDITARDATOS:
			EnableWindow(GetDlgItem(hWnd, IDC_NMBCOMPLETO), true);
			EnableWindow(GetDlgItem(hWnd, IDC_ALIASEMPRESA), true);
			EnableWindow(GetDlgItem(hWnd, IDC_BTNFOTOIV), true);
			EnableWindow(GetDlgItem(hWnd, IDC_BTNGUARDARDATOS), true);
			EnableWindow(GetDlgItem(hWnd, IDC_BTNEDITARDATOS), false);
			break;
		case IDC_BTNGUARDARDATOS:
			GetDlgItemText(hWnd, IDC_NMBCOMPLETO, user->nombre, 70);
			GetDlgItemText(hWnd, IDC_ALIASEMPRESA, user->empresa, 70);
			GetDlgItemText(hWnd, IDC_STATICIV, user->fotouser, sizeof(user->fotouser));

			escribirusuarios();

			MessageBox(hWnd, "Informacion guardada correctamente", " ", MB_OK);
			hMisenvio = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_MISENVI), 0, misenvio);
			ShowWindow(hMisenvio, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case IDC_BTNFOTOIV: {
			OPENFILENAME ofn;
			char zFile[MAX_PATH];
			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hWnd;
			ofn.lpstrFilter = "ALL\0*.*\0Bitmaps\0*.bmp\0";
			ofn.lpstrFile = zFile;
			ofn.lpstrFile[0] = '\0';
			ofn.nMaxFile = sizeof(zFile);
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
			ofn.nFilterIndex = 2;

			if (GetOpenFileName(&ofn) == TRUE) {
				SetDlgItemText(hWnd, IDC_STATICIV, zFile);
				bmp = (HBITMAP)LoadImage(NULL, zFile, IMAGE_BITMAP, 60, 60, LR_LOADFROMFILE);
				SendDlgItemMessage(hWnd, IDC_FOTOIV, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp);
			}else {
				MessageBox(0, "No selecciono", "AVISO", MB_OK);
			}
		}break;
		case ID_PRODUCTOS_NUEVOPRODUCTO:
			hNvprod = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_NUEVOPROD), 0, nvproducto);
			ShowWindow(hNvprod, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_PRODUCTOS_ELIMINARPRODUCTO:
			hEliprod = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_ELIMINARPROD), 0, eliproducto);
			ShowWindow(hEliprod, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_PRODUCTOS_EDITARPRODUCTO:
			hEditprod = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_EDITPROD), 0, editproducto);
			ShowWindow(hEditprod, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_PRODUCTOS_MISPRODUCTOS:
			hMisprod = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_MISPROD), 0, misproducto);
			ShowWindow(hMisprod, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_ENVIOS_REALIZARENVIO:
			hRealizarenvi = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_REALIZARENVI), 0, realizarenvi);
			ShowWindow(hRealizarenvi, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_ENVIOS_CANCELARENVIO:
			hCanenvio = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_CANCENVI), 0, canenvio);
			ShowWindow(hCanenvio, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_ENVIOS_EDITARENVIO:
			hEditenvio = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_EDITENVI), 0, editenvio);
			ShowWindow(hEditenvio, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_ENVIOS_MISENVIOS:
			hMisenvio = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_MISENVI), 0, misenvio);
			ShowWindow(hMisenvio, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_SALIR_CERRARSESION:
			hInsesion = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_INSESION), 0, insesion);
			ShowWindow(hInsesion, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_SALIR_GUARDARYSALIR:
			int opc = MessageBox(hWnd, "¿Seguro que desea salir y guardar todo lo modificado?", "AVISO", MB_YESNO | MB_ICONQUESTION);
			switch (opc) {
			case IDYES:
				escribirenvios();
				escribirproducto();
				escribirusuarios();
				DestroyWindow(hWnd);
				PostQuitMessage(0);
			}break;
		}

	}break;
	}
	return 0;
}

BOOL CALLBACK nvproducto(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	productos* registroprod = new productos;
	char nomprod[100];
	int b = 0;

	switch (msg) {
	case WM_INITDIALOG: {
		SetDlgItemText(hWnd, IDC_USUANP, user->nombre);
		bmp = (HBITMAP)LoadImage(NULL, user->fotouser, IMAGE_BITMAP, 60, 60, LR_LOADFROMFILE);
		SendDlgItemMessage(hWnd, IDC_FTUSUARIONP, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp);
	}break;
	case WM_COMMAND: {
		switch (LOWORD(wParam)) {
		case IDC_BTNGRDNP:
			GetDlgItemText(hWnd, IDC_NMBPRNP, registroprod->nombreprod, 70);
			GetDlgItemText(hWnd, IDC_NMBPRNP, nomprod, 100);
			registroprod->cantidad = GetDlgItemInt(hWnd, IDC_CINP, NULL, FALSE);
			registroprod->codigo = GetDlgItemInt(hWnd, IDC_CPNP, NULL, FALSE);
			GetDlgItemText(hWnd, IDC_MNP, registroprod->marca, 70);
			GetDlgItemText(hWnd, IDC_DNP, registroprod->descripcion, 70);
			GetDlgItemText(hWnd, IDC_PNP, flotante, 70);
			flot = flotante;
			registroprod->monto = stof(flot.c_str());
			GetDlgItemText(hWnd, IDC_STATICNP, registroprod->foto1, sizeof(registroprod->foto1));
			GetDlgItemText(hWnd, IDC_STATIC2NP, registroprod->foto2, sizeof(registroprod->foto2));

			auxp = iniciop;
			while (auxp != nullptr && b == 0) {
				if (strcmp(nomprod, auxp->nombreprod) == 0 && strcmp(user->usuario, auxp->propietario) == 0) {
					MessageBox(hWnd, "Producto repetido", " ", MB_OK);
					b = 1;
				}else {
					auxp = auxp->sig;
				}
			}
			if (auxp == nullptr) {
				registropr(registroprod);
				escribirproducto();
				MessageBox(hWnd, "Se registro con exito", " ", MB_OK);
				hNvprod = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_NUEVOPROD), 0, nvproducto);
				ShowWindow(hNvprod, SW_SHOW);
				DestroyWindow(hWnd);
			}
			break;

		case IDC_BTNFOTO1NP: {
			OPENFILENAME ofn;
			char zFile[MAX_PATH];
			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hWnd;
			ofn.lpstrFilter = "ALL\0*.*\0Bitmaps\0*.bmp\0";
			ofn.lpstrFile = zFile;
			ofn.lpstrFile[0] = '\0';
			ofn.nMaxFile = sizeof(zFile);
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
			ofn.nFilterIndex = 2;

			if (GetOpenFileName(&ofn) == TRUE) {
				SetDlgItemText(hWnd, IDC_STATICNP, zFile);
				bmp1 = (HBITMAP)LoadImage(NULL, zFile, IMAGE_BITMAP, 60, 60, LR_LOADFROMFILE);
				SendDlgItemMessage(hWnd, IDC_FOTO1NP, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp1);
			}else {
				MessageBox(0, "No selecciono", "AVISO", MB_OK);
			}
		}break;
		case IDC_BTNFOTO2NP: {
			OPENFILENAME ofn;
			char zFile[MAX_PATH];
			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hWnd;
			ofn.lpstrFilter = "ALL\0*.*\0Bitmaps\0*.bmp\0";
			ofn.lpstrFile = zFile;
			ofn.lpstrFile[0] = '\0';
			ofn.nMaxFile = sizeof(zFile);
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
			ofn.nFilterIndex = 2;

			if (GetOpenFileName(&ofn) == TRUE) {
				SetDlgItemText(hWnd, IDC_STATIC2NP, zFile);
				bmp2 = (HBITMAP)LoadImage(NULL, zFile, IMAGE_BITMAP, 60, 60, LR_LOADFROMFILE);
				SendDlgItemMessage(hWnd, IDC_FOTO2NP, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp2);
			}else {
				MessageBox(0, "No selecciono", "AVISO", MB_OK);
			}
		}break;
		case ID_INFORMACIONDELVENDEDOR:
			hInfovendedor = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_INFOVENDEDOR), 0, infovendedor);
			ShowWindow(hInfovendedor, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_PRODUCTOS_ELIMINARPRODUCTO:
			hEliprod = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_ELIMINARPROD), 0, eliproducto);
			ShowWindow(hEliprod, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_PRODUCTOS_EDITARPRODUCTO:
			hEditprod = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_EDITPROD), 0, editproducto);
			ShowWindow(hEditprod, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_PRODUCTOS_MISPRODUCTOS:
			hMisprod = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_MISPROD), 0, misproducto);
			ShowWindow(hMisprod, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_ENVIOS_REALIZARENVIO:
			hRealizarenvi = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_REALIZARENVI), 0, realizarenvi);
			ShowWindow(hRealizarenvi, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_ENVIOS_CANCELARENVIO:
			hCanenvio = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_CANCENVI), 0, canenvio);
			ShowWindow(hCanenvio, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_ENVIOS_EDITARENVIO:
			hEditenvio = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_EDITENVI), 0, editenvio);
			ShowWindow(hEditenvio, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_ENVIOS_MISENVIOS:
			hMisenvio = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_MISENVI), 0, misenvio);
			ShowWindow(hMisenvio, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_SALIR_CERRARSESION:
			hInsesion = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_INSESION), 0, insesion);
			ShowWindow(hInsesion, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_SALIR_GUARDARYSALIR:
			int opc = MessageBox(hWnd, "¿Seguro que desea salir y guardar todo lo modificado?", "AVISO", MB_YESNO | MB_ICONQUESTION);
			switch (opc) {
			case IDYES:
				escribirenvios();
				escribirproducto();
				escribirusuarios();
				DestroyWindow(hWnd);
				PostQuitMessage(0);
			}break;
		}
	}break;
	}
	return 0;
}

BOOL CALLBACK misproducto(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	char nombreproducto[200] = { 0 };
	int v = 0;

	switch (msg) {
	case WM_INITDIALOG: {
		SetDlgItemText(hWnd, IDC_USUAMP, user->nombre);
		bmp = (HBITMAP)LoadImage(NULL, user->fotouser, IMAGE_BITMAP, 60, 60, LR_LOADFROMFILE);
		SendDlgItemMessage(hWnd, IDC_FTUSUARIOMP, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp);
		auxp = iniciop;
		while (auxp != nullptr) {
			if (strcmp(user->usuario, auxp->propietario) == 0 && auxp->cantidad > 0 ) {

				strcpy_s(nombreproducto, auxp->nombreprod);
				SendMessage(GetDlgItem(hWnd, IDC_LISTMP), LB_INSERTSTRING, 0, (LPARAM)nombreproducto);

				strcpy_s(nombreproducto, " ");
				auxp = auxp->sig;
			}else {
				auxp = auxp->sig;
			}
		}
	}break;

	case WM_COMMAND: {
		switch (LOWORD(wParam)) {
		case IDC_LISTMP: {
			switch (HIWORD(wParam)) {
			case  LBN_DBLCLK: {
				char textoList[40];
				int indice = 0;
				indice = SendDlgItemMessage(hWnd, IDC_LISTMP, LB_GETCURSEL, 0, 0);
				SendDlgItemMessage(hWnd, IDC_LISTMP, LB_GETTEXT, indice, (LPARAM)textoList);
				auxp = iniciop;
				while (auxp != nullptr && strcmp(textoList, auxp->nombreprod) != 0) {
					auxp = auxp->sig;
				}
				SetDlgItemText(hWnd, IDC_NMBPRODMP, auxp->nombreprod);
				SetDlgItemInt(hWnd, IDC_CANTIDADMP, (UINT)auxp->cantidad, FALSE);
				SetDlgItemInt(hWnd, IDC_CODIGOMP, (UINT)auxp->codigo, FALSE);
				SetDlgItemText(hWnd, IDC_MARCAMP, auxp->marca);
				sprintf_s(flotante, "% .2f", auxp->monto);
				SetDlgItemText(hWnd, IDC_PRECIOMP, flotante);
				SetDlgItemText(hWnd, IDC_DESCRIPCIONMP, auxp->descripcion);
				/// /////////////////////////////////////
				bmp1 = (HBITMAP)LoadImage(NULL, auxp->foto1, IMAGE_BITMAP, 60, 60, LR_LOADFROMFILE);
				SendDlgItemMessage(hWnd, IDC_FOTOMP1, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp1);
				///////////////////////////////////////////////
				bmp2 = (HBITMAP)LoadImage(NULL, auxp->foto2, IMAGE_BITMAP, 60, 60, LR_LOADFROMFILE);
				SendDlgItemMessage(hWnd, IDC_FOTOMP2, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp2);
			}break;
			}
		}break;

		case IDC_BTNMPMP:
			SendMessage(GetDlgItem(hWnd, IDC_LISTMP), LB_RESETCONTENT, 0, 0);
			auxp = iniciop;
			while (auxp != nullptr) {

				if (strcmp(user->usuario, auxp->propietario) == 0 && auxp->cantidad > 0) {

					strcpy_s(nombreproducto, auxp->nombreprod);
					SendMessage(GetDlgItem(hWnd, IDC_LISTMP), LB_INSERTSTRING, 0, (LPARAM)nombreproducto);

					strcpy_s(nombreproducto, " ");
					auxp = auxp->sig;
				}else {

					auxp = auxp->sig;
				}
			}
			break;
		case IDC_BTNTLPMP:
			SendMessage(GetDlgItem(hWnd, IDC_LISTMP), LB_RESETCONTENT, 0, 0);
			auxp = iniciop;
			while (auxp != nullptr) {
				if (auxp->cantidad > 0) {
					strcpy_s(nombreproducto, auxp->nombreprod);
					SendMessage(GetDlgItem(hWnd, IDC_LISTMP), LB_INSERTSTRING, 0, (LPARAM)nombreproducto);

					strcpy_s(nombreproducto, " ");
				}
				auxp = auxp->sig;
			}
			break;
		case ID_INFORMACIONDELVENDEDOR:
			hInfovendedor = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_INFOVENDEDOR), 0, infovendedor);
			ShowWindow(hInfovendedor, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_PRODUCTOS_NUEVOPRODUCTO:
			hNvprod = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_NUEVOPROD), 0, nvproducto);
			ShowWindow(hNvprod, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_PRODUCTOS_EDITARPRODUCTO:
			hEditprod = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_EDITPROD), 0, editproducto);
			ShowWindow(hEditprod, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_PRODUCTOS_ELIMINARPRODUCTO:
			hEliprod = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_ELIMINARPROD), 0, eliproducto);
			ShowWindow(hEliprod, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_ENVIOS_REALIZARENVIO:
			hRealizarenvi = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_REALIZARENVI), 0, realizarenvi);
			ShowWindow(hRealizarenvi, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_ENVIOS_CANCELARENVIO:
			hCanenvio = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_CANCENVI), 0, canenvio);
			ShowWindow(hCanenvio, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_ENVIOS_EDITARENVIO:
			hEditenvio = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_EDITENVI), 0, editenvio);
			ShowWindow(hEditenvio, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_ENVIOS_MISENVIOS:
			hMisenvio = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_MISENVI), 0, misenvio);
			ShowWindow(hMisenvio, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_SALIR_CERRARSESION:
			hInsesion = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_INSESION), 0, insesion);
			ShowWindow(hInsesion, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_SALIR_GUARDARYSALIR:
			int opc = MessageBox(hWnd, "¿Seguro que desea salir y guardar todo lo modificado?", "AVISO", MB_YESNO | MB_ICONQUESTION);
			switch (opc) {
			case IDYES:
				escribirenvios();
				escribirproducto();
				escribirusuarios();
				DestroyWindow(hWnd);
				PostQuitMessage(0);
			}break;
		}

	}break;
	}
	return 0;
}

BOOL CALLBACK eliproducto(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	int c = 0;
	char  buscar[100];

	switch (msg) {
	case WM_INITDIALOG: {
		SetDlgItemText(hWnd, IDC_USUAEP, user->nombre);
		bmp = (HBITMAP)LoadImage(NULL, user->fotouser, IMAGE_BITMAP, 60, 60, LR_LOADFROMFILE);
		SendDlgItemMessage(hWnd, IDC_FTUSUARIOEP, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp);
	}break;
	case WM_COMMAND: {
		switch (LOWORD(wParam)) {
		case IDC_BTNBSCARELP:
			GetDlgItemText(hWnd, IDC_BSCRELP, buscar, 70);
			auxp = iniciop;

			while (auxp != nullptr && c == 0) {
				if (strcmp(user->usuario, auxp->propietario) == 0 && strcmp(buscar, auxp->nombreprod) == 0) {
					SetDlgItemText(hWnd, IDC_NMBELP, auxp->nombreprod);
					SetDlgItemInt(hWnd, IDC_CIELP, (UINT)auxp->cantidad, FALSE);
					SetDlgItemInt(hWnd, IDC_CPELP, (UINT)auxp->codigo, FALSE);
					SetDlgItemText(hWnd, IDC_MELP, auxp->marca);
					sprintf_s(flotante, "% .2f", auxp->monto);
					SetDlgItemText(hWnd, IDC_PELP, flotante);
					SetDlgItemText(hWnd, IDC_DELP, auxp->descripcion);
					/////////////////////////
					bmp1 = (HBITMAP)LoadImage(NULL, auxp->foto1, IMAGE_BITMAP, 60, 60, LR_LOADFROMFILE);
					SendDlgItemMessage(hWnd, IDC_FOTO1ELP, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp1);
					///////////////////////////////////////////////
					bmp2 = (HBITMAP)LoadImage(NULL, auxp->foto2, IMAGE_BITMAP, 60, 60, LR_LOADFROMFILE);
					SendDlgItemMessage(hWnd, IDC_FOTO2ELP, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp2);
					SetWindowText(GetDlgItem(hWnd, IDC_BSCRELP), "");
					/*EnableWindow(GetDlgItem(hWnd, IDC_EPBE), true);
					EnableWindow(GetDlgItem(hWnd, IDC_EPBC), true);
					EnableWindow(GetDlgItem(hWnd, IDC_EPCP), true);
					EnableWindow(GetDlgItem(hWnd, IDC_EPM), true);
					EnableWindow(GetDlgItem(hWnd, IDC_EPPU), true);
					EnableWindow(GetDlgItem(hWnd, IDC_EPD), true);
					EnableWindow(GetDlgItem(hWnd, IDC_EPC), true);*/
					c = 1;
				}else {
					auxp = auxp->sig;
				}
			}
			if (auxp == nullptr) {

				SetWindowText(GetDlgItem(hWnd, IDC_NMBELP), "");
				SetWindowText(GetDlgItem(hWnd, IDC_CIELP), "");
				SetWindowText(GetDlgItem(hWnd, IDC_CPELP), "");
				SetWindowText(GetDlgItem(hWnd, IDC_MELP), "");
				SetWindowText(GetDlgItem(hWnd, IDC_PELP), "");
				SetWindowText(GetDlgItem(hWnd, IDC_DELP), "");
				SetWindowText(GetDlgItem(hWnd, IDC_FOTO1ELP), "null");
				SetWindowText(GetDlgItem(hWnd, IDC_FOTO2ELP), "null");
				MessageBox(hWnd, "No se pudo encontrar su producto", "", MB_OK | MB_ICONEXCLAMATION);
			}
			break;
		case IDC_BTNCNELP:
			hEliprod = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_ELIMINARPROD), 0, eliproducto);
			ShowWindow(hEliprod, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case IDC_BTNELPELP:
			SetWindowText(GetDlgItem(hWnd, IDC_NMBELP), "");
			SetWindowText(GetDlgItem(hWnd, IDC_CIELP), "");
			SetWindowText(GetDlgItem(hWnd, IDC_CPELP), "");
			SetWindowText(GetDlgItem(hWnd, IDC_MELP), "");
			SetWindowText(GetDlgItem(hWnd, IDC_PELP), "");
			SetWindowText(GetDlgItem(hWnd, IDC_DELP), "");
			SetWindowText(GetDlgItem(hWnd, IDC_FOTO1ELP), "null");
			SetWindowText(GetDlgItem(hWnd, IDC_FOTO2ELP), "null");
			eliminarprod(auxp);
			escribirproducto();
			break;
		case ID_INFORMACIONDELVENDEDOR:
			hInfovendedor = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_INFOVENDEDOR), 0, infovendedor);
			ShowWindow(hInfovendedor, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_PRODUCTOS_NUEVOPRODUCTO:
			hNvprod = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_NUEVOPROD), 0, nvproducto);
			ShowWindow(hNvprod, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_PRODUCTOS_EDITARPRODUCTO:
			hEditprod = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_EDITPROD), 0, editproducto);
			ShowWindow(hEditprod, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_PRODUCTOS_MISPRODUCTOS:
			hMisprod = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_MISPROD), 0, misproducto);
			ShowWindow(hMisprod, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_ENVIOS_REALIZARENVIO:
			hRealizarenvi = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_REALIZARENVI), 0, realizarenvi);
			ShowWindow(hRealizarenvi, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_ENVIOS_CANCELARENVIO:
			hCanenvio = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_CANCENVI), 0, canenvio);
			ShowWindow(hCanenvio, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_ENVIOS_EDITARENVIO:
			hEditenvio = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_EDITENVI), 0, editenvio);
			ShowWindow(hEditenvio, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_ENVIOS_MISENVIOS:
			hMisenvio = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_MISENVI), 0, misenvio);
			ShowWindow(hMisenvio, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_SALIR_CERRARSESION:
			hInsesion = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_INSESION), 0, insesion);
			ShowWindow(hInsesion, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_SALIR_GUARDARYSALIR:
			int opc = MessageBox(hWnd, "¿Seguro que desea salir y guardar todo lo modificado?", "AVISO", MB_YESNO | MB_ICONQUESTION);
			switch (opc) {
			case IDYES:
				escribirenvios();
				escribirproducto();
				escribirusuarios();
				DestroyWindow(hWnd);
				PostQuitMessage(0);
			}break;
		}
	} break;
	}
	return 0;
}

BOOL CALLBACK editproducto(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	int c = 0;
	char  buscar[100];

	switch (msg) {
	case WM_INITDIALOG: {
		SetDlgItemText(hWnd, IDC_USUAEDP, user->nombre);
		bmp = (HBITMAP)LoadImage(NULL, user->fotouser, IMAGE_BITMAP, 60, 60, LR_LOADFROMFILE);
		SendDlgItemMessage(hWnd, IDC_FTUSUARIOEDP, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp);
	}break;
	case WM_COMMAND: {
		switch (LOWORD(wParam)) {
		case IDC_BTNBSCEP:
			GetDlgItemText(hWnd, IDC_BSCEP, buscar, 70);
			auxp = iniciop;

			while (auxp != nullptr && c == 0) {
				if (strcmp(user->usuario, auxp->propietario) == 0 && strcmp(buscar, auxp->nombreprod) == 0) {
					SetDlgItemText(hWnd, IDC_NMBPRODEP, auxp->nombreprod);
					SetDlgItemInt(hWnd, IDC_CIEP, (UINT)auxp->cantidad, FALSE);
					SetDlgItemInt(hWnd, IDC_CPEP, (UINT)auxp->codigo, FALSE);
					SetDlgItemText(hWnd, IDC_MEP, auxp->marca);
					sprintf_s(flotante, "% .2f", auxp->monto);
					SetDlgItemText(hWnd, IDC_PEP, flotante);
					SetDlgItemText(hWnd, IDC_DEP, auxp->descripcion);
					/////////////////////////
					bmp1 = (HBITMAP)LoadImage(NULL, auxp->foto1, IMAGE_BITMAP, 60, 60, LR_LOADFROMFILE);
					SendDlgItemMessage(hWnd, IDC_FOTO1EP, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp1);
					///////////////////////////////////////////////
					bmp2 = (HBITMAP)LoadImage(NULL, auxp->foto2, IMAGE_BITMAP, 60, 60, LR_LOADFROMFILE);
					SendDlgItemMessage(hWnd, IDC_FOTO2EP, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp2);
					SetWindowText(GetDlgItem(hWnd, IDC_BSCEP), "");
					EnableWindow(GetDlgItem(hWnd, IDC_BTNFOTO1EP), true);
					EnableWindow(GetDlgItem(hWnd, IDC_BTNFOTO2EP), true);
					EnableWindow(GetDlgItem(hWnd, IDC_BTNGUARDAREP), true);
					EnableWindow(GetDlgItem(hWnd, IDC_NMBPRODEP), true);
					EnableWindow(GetDlgItem(hWnd, IDC_CPEP), true);
					EnableWindow(GetDlgItem(hWnd, IDC_MEP), true);
					EnableWindow(GetDlgItem(hWnd, IDC_PEP), true);
					EnableWindow(GetDlgItem(hWnd, IDC_DEP), true);
					EnableWindow(GetDlgItem(hWnd, IDC_BTNCANCELAREP), true);

					c = 1;
				}else {
					auxp = auxp->sig;
				}
			}
			if (auxp == nullptr) {
				SetWindowText(GetDlgItem(hWnd, IDC_BSCEP), "");
				SetWindowText(GetDlgItem(hWnd, IDC_NMBPRODEP), "");
				SetWindowText(GetDlgItem(hWnd, IDC_CIEP), "");
				SetWindowText(GetDlgItem(hWnd, IDC_CPEP), "");
				SetWindowText(GetDlgItem(hWnd, IDC_MEP), "");
				SetWindowText(GetDlgItem(hWnd, IDC_PEP), "");
				SetWindowText(GetDlgItem(hWnd, IDC_DEP), "");
				MessageBox(hWnd, "No se pudo encontrar su producto", "", MB_OK | MB_ICONEXCLAMATION);
			}
			break;

		case IDC_BTNCANCELAREP:
			hEditprod = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_EDITPROD), 0, editproducto);
			ShowWindow(hEditprod, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case IDC_BTNGUARDAREP:
			GetDlgItemText(hWnd, IDC_NMBPRODEP, auxp->nombreprod, 70);
			auxp->codigo = GetDlgItemInt(hWnd, IDC_CPEP, NULL, FALSE);
			GetDlgItemText(hWnd, IDC_MEP, auxp->marca, 70);
			GetDlgItemText(hWnd, IDC_DEP, auxp->descripcion, 70);
			GetDlgItemText(hWnd, IDC_PEP, flotante, 70);
			flot = flotante;
			auxp->monto = stof(flot.c_str());
			GetDlgItemText(hWnd, IDC_STATIC1EP, auxp->foto1, sizeof(auxp->foto1));
			GetDlgItemText(hWnd, IDC_STATIC2NP, auxp->foto2, sizeof(auxp->foto2));
			escribirproducto();
			MessageBox(hWnd, "Producto modificado", "", MB_OK | MB_ICONEXCLAMATION);
			hEditprod = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_EDITPROD), 0, editproducto);
			ShowWindow(hEditprod, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case IDC_BTNFOTO1EP: {
			OPENFILENAME ofn;
			char zFile[MAX_PATH];
			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hWnd;
			ofn.lpstrFilter = "ALL\0*.*\0Bitmaps\0*.bmp\0";
			ofn.lpstrFile = zFile;
			ofn.lpstrFile[0] = '\0';
			ofn.nMaxFile = sizeof(zFile);
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
			ofn.nFilterIndex = 2;

			if (GetOpenFileName(&ofn) == TRUE) {
				SetDlgItemText(hWnd, IDC_STATIC1EP, zFile);
				bmp1 = (HBITMAP)LoadImage(NULL, zFile, IMAGE_BITMAP, 60, 60, LR_LOADFROMFILE);
				SendDlgItemMessage(hWnd, IDC_FOTO1EP, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp1);
			}else {
				MessageBox(0, "No selecciono", "AVISO", MB_OK);
			}
		}break;
		case IDC_BTNFOTO2EP: {
			OPENFILENAME ofn;
			char zFile[MAX_PATH];
			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = hWnd;
			ofn.lpstrFilter = "ALL\0*.*\0Bitmaps\0*.bmp\0";
			ofn.lpstrFile = zFile;
			ofn.lpstrFile[0] = '\0';
			ofn.nMaxFile = sizeof(zFile);
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
			ofn.nFilterIndex = 2;

			if (GetOpenFileName(&ofn) == TRUE) {
				SetDlgItemText(hWnd, IDC_STATIC2NP, zFile);
				bmp2 = (HBITMAP)LoadImage(NULL, zFile, IMAGE_BITMAP, 60, 60, LR_LOADFROMFILE);
				SendDlgItemMessage(hWnd, IDC_FOTO2EP, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp2);
			}else {
				MessageBox(0, "No selecciono", "AVISO", MB_OK);
			}
		}break;
		case ID_INFORMACIONDELVENDEDOR:
			hInfovendedor = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_INFOVENDEDOR), 0, infovendedor);
			ShowWindow(hInfovendedor, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_PRODUCTOS_NUEVOPRODUCTO:
			hNvprod = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_NUEVOPROD), 0, nvproducto);
			ShowWindow(hNvprod, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_PRODUCTOS_ELIMINARPRODUCTO:
			hEliprod = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_ELIMINARPROD), 0, eliproducto);
			ShowWindow(hEliprod, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_PRODUCTOS_MISPRODUCTOS:
			hMisprod = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_MISPROD), 0, misproducto);
			ShowWindow(hMisprod, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_ENVIOS_REALIZARENVIO:
			hRealizarenvi = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_REALIZARENVI), 0, realizarenvi);
			ShowWindow(hRealizarenvi, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_ENVIOS_CANCELARENVIO:
			hCanenvio = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_CANCENVI), 0, canenvio);
			ShowWindow(hCanenvio, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_ENVIOS_EDITARENVIO:
			hEditenvio = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_EDITENVI), 0, editenvio);
			ShowWindow(hEditenvio, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_ENVIOS_MISENVIOS:
			hMisenvio = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_MISENVI), 0, misenvio);
			ShowWindow(hMisenvio, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_SALIR_CERRARSESION:
			hInsesion = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_INSESION), 0, insesion);
			ShowWindow(hInsesion, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_SALIR_GUARDARYSALIR:
			int opc = MessageBox(hWnd, "¿Seguro que desea salir y guardar todo lo modificado?", "AVISO", MB_YESNO | MB_ICONQUESTION);
			switch (opc) {
			case IDYES:
				escribirenvios();
				escribirproducto();
				escribirusuarios();
				DestroyWindow(hWnd);
				PostQuitMessage(0);
			}break;
		}

	}break;
	}
	return 0;
}

BOOL CALLBACK realizarenvi(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	envios* enviore = new envios;
	SYSTEMTIME fechaenvio;
	int indice;
	char nombreproducto[200] = { 0 };
	int m = 0;
	float r = 0;

	switch (msg) {
	case WM_INITDIALOG: {
		SetDlgItemText(hWnd, IDC_USUARE, user->nombre);
		bmp = (HBITMAP)LoadImage(NULL, user->fotouser, IMAGE_BITMAP, 60, 60, LR_LOADFROMFILE);
		SendDlgItemMessage(hWnd, IDC_FTUSUARIORE, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp);
		auxp = iniciop;
		while (auxp != nullptr) {
			if (auxp->cantidad > 0) {
				strcpy_s(nombreproducto, auxp->nombreprod);
				SendMessage(GetDlgItem(hWnd, IDC_LISTPRRE), LB_INSERTSTRING, 0, (LPARAM)nombreproducto);
				strcpy_s(nombreproducto, " ");
			}
			auxp = auxp->sig;
		}
	}break;

	case WM_COMMAND: {
		switch (LOWORD(wParam)) {
		case IDC_LISTPRRE: {
			switch (HIWORD(wParam)) {
			case  LBN_DBLCLK: {
				char textoList[40];
				int indice = 0;
				indice = SendDlgItemMessage(hWnd, IDC_LISTPRRE, LB_GETCURSEL, 0, 0);
				SendDlgItemMessage(hWnd, IDC_LISTPRRE, LB_GETTEXT, indice, (LPARAM)textoList);
				auxp = iniciop;
				while (auxp != nullptr && strcmp(textoList, auxp->nombreprod) != 0) {
					auxp = auxp->sig;
				}
				SetDlgItemInt(hWnd, IDC_CIRE, (UINT)auxp->cantidad, FALSE);
			}break;
			}
		}break;

		case IDC_BTNCCRE:
			m = GetDlgItemInt(hWnd, IDC_CERE, NULL, FALSE);
			r = m * auxp->monto;
			sprintf_s(flotante, "% .2f", r);
			SetDlgItemText(hWnd, IDC_CCRE, flotante);
			break;
		case IDC_BTNGUARE:
			ZeroMemory(&fechaenvio, sizeof(fechaenvio));
			SendDlgItemMessage(hWnd, IDC_DATETIMEPICKER1, DTM_GETSYSTEMTIME, 0, (LPARAM)&fechaenvio);
			sprintf_s(enviore->fechaenvio.dia, "%d", fechaenvio.wDay);
			sprintf_s(enviore->fechaenvio.mes, "%d", fechaenvio.wMonth);
			sprintf_s(enviore->fechaenvio.anio, "%d", fechaenvio.wYear);
			GetDlgItemText(hWnd, IDC_CALLERE, enviore->calle, 100);
			GetDlgItemText(hWnd, IDC_COLONIARE, enviore->colonia, 100);
			GetDlgItemText(hWnd, IDC_CIUDADRE, enviore->ciudad, 100);
			GetDlgItemText(hWnd, IDC_ESTADORE, enviore->estado, 100);
			GetDlgItemText(hWnd, IDC_MENSAJERE, enviore->mensaje, 100);
			enviore->cantidad = GetDlgItemInt(hWnd, IDC_CERE, NULL, FALSE);
			GetDlgItemText(hWnd, IDC_CCRE, flotante, 70);
			flot = flotante;
			enviore->precio = stof(flot.c_str());

			auxp->cantidad = auxp->cantidad - enviore->cantidad;

			registroenvio(enviore);
			escribirproducto();
			escribirenvios();

			MessageBox(hWnd, "Se registro con exito", " ", MB_OK);
			hRealizarenvi = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_REALIZARENVI), 0, realizarenvi);
			ShowWindow(hRealizarenvi, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_INFORMACIONDELVENDEDOR:
			hInfovendedor = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_INFOVENDEDOR), 0, infovendedor);
			ShowWindow(hInfovendedor, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_PRODUCTOS_NUEVOPRODUCTO:
			hNvprod = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_NUEVOPROD), 0, nvproducto);
			ShowWindow(hNvprod, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_PRODUCTOS_EDITARPRODUCTO:
			hEditprod = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_EDITPROD), 0, editproducto);
			ShowWindow(hEditprod, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_PRODUCTOS_ELIMINARPRODUCTO:
			hEliprod = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_ELIMINARPROD), 0, eliproducto);
			ShowWindow(hEliprod, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_PRODUCTOS_MISPRODUCTOS:
			hMisprod = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_MISPROD), 0, misproducto);
			ShowWindow(hMisprod, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_ENVIOS_CANCELARENVIO:
			hCanenvio = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_CANCENVI), 0, canenvio);
			ShowWindow(hCanenvio, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_ENVIOS_EDITARENVIO:
			hEditenvio = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_EDITENVI), 0, editenvio);
			ShowWindow(hEditenvio, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_ENVIOS_MISENVIOS:
			hMisenvio = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_MISENVI), 0, misenvio);
			ShowWindow(hMisenvio, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_SALIR_CERRARSESION:
			hInsesion = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_INSESION), 0, insesion);
			ShowWindow(hInsesion, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_SALIR_GUARDARYSALIR:
			int opc = MessageBox(hWnd, "¿Seguro que desea salir y guardar todo lo modificado?", "AVISO", MB_YESNO | MB_ICONQUESTION);
			switch (opc) {
			case IDYES:
				escribirenvios();
				escribirproducto();
				escribirusuarios();
				DestroyWindow(hWnd);
				PostQuitMessage(0);
			}break;
		}
	} break;
	}
	return 0;
}

BOOL CALLBACK canenvio(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	int dia;
	int mes;
	int anio;
	char fechaCompleta[30] = { 0 };
	SYSTEMTIME fechaHoy;
	ZeroMemory(&fechaHoy, sizeof(fechaHoy));
	GetSystemTime(&fechaHoy);

	switch (msg) {
	case WM_INITDIALOG: {
		SetDlgItemText(hWnd, IDC_USUACE, user->nombre);
		bmp = (HBITMAP)LoadImage(NULL, user->fotouser, IMAGE_BITMAP, 60, 60, LR_LOADFROMFILE);
		SendDlgItemMessage(hWnd, IDC_FTUSUARIOCE, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp);
		quickSort(inicioe, fine);
		auxe = inicioe;
		while (auxe != nullptr) {
			if (strcmp(user->usuario, auxe->repartidor) == 0) {
				int dia = atoi(auxe->fechaenvio.dia);
				int mes = atoi(auxe->fechaenvio.mes);
				int anio = atoi(auxe->fechaenvio.anio);

				strcat_s(fechaCompleta, auxe->fechaenvio.dia);
				strcat_s(fechaCompleta, "/");
				strcat_s(fechaCompleta, auxe->fechaenvio.mes);
				strcat_s(fechaCompleta, "/");
				strcat_s(fechaCompleta, auxe->fechaenvio.anio);
				SendMessage(GetDlgItem(hWnd, IDC_LISTFECHENCE), LB_ADDSTRING, 0, (LPARAM)fechaCompleta);
				strcpy_s(fechaCompleta, "");

			}
			auxe = auxe->sig;
		}
	}break;

	case WM_COMMAND: {
		switch (LOWORD(wParam)) {
		case IDC_LISTFECHENCE: {
			switch (HIWORD(wParam)) {
			case  LBN_DBLCLK: {
				char textoList[40] = { 0 };
				int indice = 0;
				char fechacomp[20] = { 0 };

				indice = SendDlgItemMessage(hWnd, IDC_LISTFECHENCE, LB_GETCURSEL, 0, 0);
				SendDlgItemMessage(hWnd, IDC_LISTFECHENCE, LB_GETTEXT, indice, (LPARAM)textoList);
				auxe = inicioe;
				strcat_s(fechacomp, auxe->fechaenvio.dia);
				strcat_s(fechacomp, "/");
				strcat_s(fechacomp, auxe->fechaenvio.mes);
				strcat_s(fechacomp, "/");
				strcat_s(fechacomp, auxe->fechaenvio.anio);
				while (auxe != nullptr && strcmp(textoList, fechacomp) != 0) {
					strcpy_s(fechacomp, "");
					auxe = auxe->sig;
					strcat_s(fechacomp, auxe->fechaenvio.dia);
					strcat_s(fechacomp, "/");
					strcat_s(fechacomp, auxe->fechaenvio.mes);
					strcat_s(fechacomp, "/");
					strcat_s(fechacomp, auxe->fechaenvio.anio);
				}
				SetDlgItemText(hWnd, IDC_PRODCE, auxe->producto);
				SetDlgItemInt(hWnd, IDC_CANTIDADCE, (UINT)auxe->cantidad, FALSE);
				SetDlgItemText(hWnd, IDC_CALLECE, auxe->calle);
				SetDlgItemText(hWnd, IDC_COLONIACE, auxe->colonia);
				SetDlgItemText(hWnd, IDC_ESTADOCE, auxe->estado);
				SetDlgItemText(hWnd, IDC_CIUDADCE, auxe->ciudad);
			}break;
			}
		}break;

		case IDC_CANCELARCE:
			dia = atoi(auxe->fechaenvio.dia);
			mes = atoi(auxe->fechaenvio.mes);
			anio = atoi(auxe->fechaenvio.anio);
			if (fechaHoy.wYear <= anio) {
				if (fechaHoy.wMonth <= mes) {
					if (fechaHoy.wDay <= dia) {
						eliminarend(auxe);
						MessageBox(hWnd, "Se elimino con exito", " ", MB_OK);
						SetWindowText(GetDlgItem(hWnd, IDC_PRODCE), "");
						SetWindowText(GetDlgItem(hWnd, IDC_CANTIDADCE), "");
						SetWindowText(GetDlgItem(hWnd, IDC_CALLECE), "");
						SetWindowText(GetDlgItem(hWnd, IDC_ESTADOCE), "");
						SetWindowText(GetDlgItem(hWnd, IDC_COLONIACE), "");
						SetWindowText(GetDlgItem(hWnd, IDC_CIUDADCE), "");

					}else {
						MessageBox(hWnd, "No se puede cancelar", " ", MB_OK);
						SetWindowText(GetDlgItem(hWnd, IDC_PRODCE), "");
						SetWindowText(GetDlgItem(hWnd, IDC_CANTIDADCE), "");
						SetWindowText(GetDlgItem(hWnd, IDC_CALLECE), "");
						SetWindowText(GetDlgItem(hWnd, IDC_ESTADOCE), "");
						SetWindowText(GetDlgItem(hWnd, IDC_COLONIACE), "");
						SetWindowText(GetDlgItem(hWnd, IDC_CIUDADCE), "");
					}
				}else {
					MessageBox(hWnd, "No se puede cancelar", " ", MB_OK);
					SetWindowText(GetDlgItem(hWnd, IDC_PRODCE), "");
					SetWindowText(GetDlgItem(hWnd, IDC_CANTIDADCE), "");
					SetWindowText(GetDlgItem(hWnd, IDC_CALLECE), "");
					SetWindowText(GetDlgItem(hWnd, IDC_ESTADOCE), "");
					SetWindowText(GetDlgItem(hWnd, IDC_COLONIACE), "");
					SetWindowText(GetDlgItem(hWnd, IDC_CIUDADCE), "");
				}
			}else {
				MessageBox(hWnd, "No se puede cancelar", " ", MB_OK);
				SetWindowText(GetDlgItem(hWnd, IDC_PRODCE), "");
				SetWindowText(GetDlgItem(hWnd, IDC_CANTIDADCE), "");
				SetWindowText(GetDlgItem(hWnd, IDC_CALLECE), "");
				SetWindowText(GetDlgItem(hWnd, IDC_ESTADOCE), "");
				SetWindowText(GetDlgItem(hWnd, IDC_COLONIACE), "");
				SetWindowText(GetDlgItem(hWnd, IDC_CIUDADCE), "");
			}break;
		case IDC_CANCCE:
			SetWindowText(GetDlgItem(hWnd, IDC_PRODCE), "");
			SetWindowText(GetDlgItem(hWnd, IDC_CANTIDADCE), "");
			SetWindowText(GetDlgItem(hWnd, IDC_CALLECE), "");
			SetWindowText(GetDlgItem(hWnd, IDC_ESTADOCE), "");
			SetWindowText(GetDlgItem(hWnd, IDC_COLONIACE), "");
			SetWindowText(GetDlgItem(hWnd, IDC_CIUDADCE), "");
			hCanenvio = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_CANCENVI), 0, canenvio);
			ShowWindow(hCanenvio, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_INFORMACIONDELVENDEDOR:
			hInfovendedor = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_INFOVENDEDOR), 0, infovendedor);
			ShowWindow(hInfovendedor, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_PRODUCTOS_NUEVOPRODUCTO:
			hNvprod = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_NUEVOPROD), 0, nvproducto);
			ShowWindow(hNvprod, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_PRODUCTOS_EDITARPRODUCTO:
			hEditprod = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_EDITPROD), 0, editproducto);
			ShowWindow(hEditprod, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_PRODUCTOS_ELIMINARPRODUCTO:
			hEliprod = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_ELIMINARPROD), 0, eliproducto);
			ShowWindow(hEliprod, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_PRODUCTOS_MISPRODUCTOS:
			hMisprod = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_MISPROD), 0, misproducto);
			ShowWindow(hMisprod, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_ENVIOS_REALIZARENVIO:
			hRealizarenvi = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_REALIZARENVI), 0, realizarenvi);
			ShowWindow(hRealizarenvi, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_ENVIOS_EDITARENVIO:
			hEditenvio = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_EDITENVI), 0, editenvio);
			ShowWindow(hEditenvio, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_ENVIOS_MISENVIOS:
			hMisenvio = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_MISENVI), 0, misenvio);
			ShowWindow(hMisenvio, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_SALIR_CERRARSESION:
			hInsesion = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_INSESION), 0, insesion);
			ShowWindow(hInsesion, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_SALIR_GUARDARYSALIR:
			int opc = MessageBox(hWnd, "¿Seguro que desea salir y guardar todo lo modificado?", "AVISO", MB_YESNO | MB_ICONQUESTION);
			switch (opc) {
			case IDYES:
				escribirenvios();
				escribirproducto();
				escribirusuarios();
				DestroyWindow(hWnd);
				PostQuitMessage(0);
			}break;
		}

	} break;
	}
	return 0;
}

BOOL CALLBACK editenvio(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	int dia;
	int mes;
	int anio;
	char fechaCompleta[30] = { 0 };
	SYSTEMTIME fechaHoy;
	ZeroMemory(&fechaHoy, sizeof(fechaHoy));
	GetSystemTime(&fechaHoy);

	switch (msg) {
	case WM_INITDIALOG: {SetDlgItemText(hWnd, IDC_USUAEDE, user->nombre);
		bmp = (HBITMAP)LoadImage(NULL, user->fotouser, IMAGE_BITMAP, 60, 60, LR_LOADFROMFILE);
		SendDlgItemMessage(hWnd, IDC_FTUSUARIOEDE, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp);
		quickSort(inicioe, fine);
		auxe = inicioe;
		while (auxe != nullptr) {
			if (strcmp(user->usuario, auxe->repartidor) == 0) {
				int dia = atoi(auxe->fechaenvio.dia);
				int mes = atoi(auxe->fechaenvio.mes);
				int anio = atoi(auxe->fechaenvio.anio);

				strcat_s(fechaCompleta, auxe->fechaenvio.dia);
				strcat_s(fechaCompleta, "/");
				strcat_s(fechaCompleta, auxe->fechaenvio.mes);
				strcat_s(fechaCompleta, "/");
				strcat_s(fechaCompleta, auxe->fechaenvio.anio);
				SendMessage(GetDlgItem(hWnd, IDC_LISTEE), LB_ADDSTRING, 0, (LPARAM)fechaCompleta);
				strcpy_s(fechaCompleta, "");
			}
			auxe = auxe->sig;
		}
	}break;

	case WM_COMMAND: {
		switch (LOWORD(wParam)) {
		case IDC_LISTEE: {
			switch (HIWORD(wParam)) {
			case  LBN_DBLCLK: {
				char textoList[40] = { 0 };
				int indice = 0;
				char fechacomp[20] = { 0 };

				indice = SendDlgItemMessage(hWnd, IDC_LISTEE, LB_GETCURSEL, 0, 0);
				SendDlgItemMessage(hWnd, IDC_LISTEE, LB_GETTEXT, indice, (LPARAM)textoList);
				auxe = inicioe;
				strcat_s(fechacomp, auxe->fechaenvio.dia);
				strcat_s(fechacomp, "/");
				strcat_s(fechacomp, auxe->fechaenvio.mes);
				strcat_s(fechacomp, "/");
				strcat_s(fechacomp, auxe->fechaenvio.anio);
				while (auxe != nullptr && strcmp(textoList, fechacomp) != 0) {
					strcpy_s(fechacomp, "");
					auxe = auxe->sig;
					strcat_s(fechacomp, auxe->fechaenvio.dia);
					strcat_s(fechacomp, "/");
					strcat_s(fechacomp, auxe->fechaenvio.mes);
					strcat_s(fechacomp, "/");
					strcat_s(fechacomp, auxe->fechaenvio.anio);
				}
				SetDlgItemText(hWnd, IDC_PRODUCTEE, auxe->producto);
				SetDlgItemInt(hWnd, IDC_CANTIDADEE, (UINT)auxe->cantidad, FALSE);
				SetDlgItemText(hWnd, IDC_CALLEEE, auxe->calle);
				SetDlgItemText(hWnd, IDC_COLONIAEE, auxe->colonia);
				SetDlgItemText(hWnd, IDC_ESTADOEE, auxe->estado);
				SetDlgItemText(hWnd, IDC_CIUDADEE, auxe->ciudad);

			}break;
			}
		}break;

		case IDC_BTNGEEE:
			GetDlgItemText(hWnd, IDC_CALLEEE, auxe->calle, 70);
			GetDlgItemText(hWnd, IDC_COLONIAEE, auxe->colonia, 70);
			GetDlgItemText(hWnd, IDC_ESTADOEE, auxe->estado, 70);
			GetDlgItemText(hWnd, IDC_CIUDADEE, auxe->ciudad, 70);
			MessageBox(hWnd, "Envio modificado", "", MB_OK | MB_ICONEXCLAMATION);
			hEditenvio = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_EDITENVI), 0, editenvio);
			ShowWindow(hEditenvio, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case IDC_BTNCANEE:
			hEditenvio = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_EDITENVI), 0, editenvio);
			ShowWindow(hEditenvio, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_INFORMACIONDELVENDEDOR:
			hInfovendedor = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_INFOVENDEDOR), 0, infovendedor);
			ShowWindow(hInfovendedor, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_PRODUCTOS_NUEVOPRODUCTO:
			hNvprod = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_NUEVOPROD), 0, nvproducto);
			ShowWindow(hNvprod, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_PRODUCTOS_EDITARPRODUCTO:
			hEditprod = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_EDITPROD), 0, editproducto);
			ShowWindow(hEditprod, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_PRODUCTOS_ELIMINARPRODUCTO:
			hEliprod = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_ELIMINARPROD), 0, eliproducto);
			ShowWindow(hEliprod, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_PRODUCTOS_MISPRODUCTOS:
			hMisprod = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_MISPROD), 0, misproducto);
			ShowWindow(hMisprod, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_ENVIOS_REALIZARENVIO:
			hRealizarenvi = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_REALIZARENVI), 0, realizarenvi);
			ShowWindow(hRealizarenvi, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_ENVIOS_CANCELARENVIO:
			hCanenvio = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_CANCENVI), 0, canenvio);
			ShowWindow(hCanenvio, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_ENVIOS_MISENVIOS:
			hMisenvio = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_MISENVI), 0, misenvio);
			ShowWindow(hMisenvio, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_SALIR_CERRARSESION:
			hInsesion = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_INSESION), 0, insesion);
			ShowWindow(hInsesion, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_SALIR_GUARDARYSALIR:
			int opc = MessageBox(hWnd, "¿Seguro que desea salir y guardar todo lo modificado?", "AVISO", MB_YESNO | MB_ICONQUESTION);
			switch (opc) {
			case IDYES:
				escribirenvios();
				escribirproducto();
				escribirusuarios();
				DestroyWindow(hWnd);
				PostQuitMessage(0);
			}break;
		}
	}break;
	}
	return 0;
}

BOOL CALLBACK misenvio(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	char fechaCompleta[30] = { 0 };
	SYSTEMTIME fechaHoy;
	ZeroMemory(&fechaHoy, sizeof(fechaHoy));
	GetSystemTime(&fechaHoy);
	switch (msg) {
	case WM_INITDIALOG: {
		SetDlgItemText(hWnd, IDC_USUAME, user->nombre);
		bmp = (HBITMAP)LoadImage(NULL, user->fotouser, IMAGE_BITMAP, 60, 60, LR_LOADFROMFILE);
		SendDlgItemMessage(hWnd, IDC_FTUSUARIOME, STM_SETIMAGE, IMAGE_BITMAP, (LPARAM)bmp);
		quickSort(inicioe, fine);
		auxe = inicioe;
		while (auxe != nullptr) {
			if (strcmp(user->usuario, auxe->repartidor) == 0) {
				int dia = atoi(auxe->fechaenvio.dia);
				int mes = atoi(auxe->fechaenvio.mes);
				int anio = atoi(auxe->fechaenvio.anio);

				strcat_s(fechaCompleta, auxe->fechaenvio.dia);
				strcat_s(fechaCompleta, "/");
				strcat_s(fechaCompleta, auxe->fechaenvio.mes);
				strcat_s(fechaCompleta, "/");
				strcat_s(fechaCompleta, auxe->fechaenvio.anio);
				SendMessage(GetDlgItem(hWnd, IDC_LISTFECHAME), LB_ADDSTRING, 0, (LPARAM)fechaCompleta);
				strcpy_s(fechaCompleta, "");
			}
			auxe = auxe->sig;
		}
	}break;

	case WM_COMMAND: {
		switch (LOWORD(wParam)) {
		case IDC_LISTFECHAME: {
			switch (HIWORD(wParam)) {
			case  LBN_DBLCLK: {
				char textoList[40] = { 0 };
				int indice = 0;
				char fechacomp[20] = { 0 };

				indice = SendDlgItemMessage(hWnd, IDC_LISTFECHAME, LB_GETCURSEL, 0, 0);
				SendDlgItemMessage(hWnd, IDC_LISTFECHAME, LB_GETTEXT, indice, (LPARAM)textoList);
				auxe = inicioe;
				strcat_s(fechacomp, auxe->fechaenvio.dia);
				strcat_s(fechacomp, "/");
				strcat_s(fechacomp, auxe->fechaenvio.mes);
				strcat_s(fechacomp, "/");
				strcat_s(fechacomp, auxe->fechaenvio.anio);
				while (auxe != nullptr && strcmp(textoList, fechacomp) != 0) {
					strcpy_s(fechacomp, "");
					auxe = auxe->sig;
					strcat_s(fechacomp, auxe->fechaenvio.dia);
					strcat_s(fechacomp, "/");
					strcat_s(fechacomp, auxe->fechaenvio.mes);
					strcat_s(fechacomp, "/");
					strcat_s(fechacomp, auxe->fechaenvio.anio);
				}
				SetDlgItemText(hWnd, IDC_PRODUCTOME, auxe->producto);
				SetDlgItemInt(hWnd, IDC_CANTIDADME, (UINT)auxe->cantidad, FALSE);
				SetDlgItemText(hWnd, IDC_CALLEME, auxe->calle);
				SetDlgItemText(hWnd, IDC_COLONIAME, auxe->colonia);
				SetDlgItemText(hWnd, IDC_ESTADOME, auxe->estado);
				SetDlgItemText(hWnd, IDC_CIUDADME, auxe->ciudad);

				int dia = atoi(auxe->fechaenvio.dia);
				int mes = atoi(auxe->fechaenvio.mes);
				int anio = atoi(auxe->fechaenvio.anio);

				if (fechaHoy.wYear <= anio) {
					if (fechaHoy.wMonth <= mes) {
						if (fechaHoy.wDay <= dia) {
							SetDlgItemText(hWnd, IDC_ESTATUSME, "POR ATENDER");
						} else {
							SetDlgItemText(hWnd, IDC_ESTATUSME, "ATENDIDA");
						}
					} else {
						SetDlgItemText(hWnd, IDC_ESTATUSME, "ATENDIDA");
					}
				} else {
					SetDlgItemText(hWnd, IDC_ESTATUSME, "ATENDIDA");
				}
			}break;
			}
		}break;

		case ID_INFORMACIONDELVENDEDOR:
			hInfovendedor = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_INFOVENDEDOR), 0, infovendedor);
			ShowWindow(hInfovendedor, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_PRODUCTOS_NUEVOPRODUCTO:
			hNvprod = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_NUEVOPROD), 0, nvproducto);
			ShowWindow(hNvprod, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_PRODUCTOS_EDITARPRODUCTO:
			hEditprod = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_EDITPROD), 0, editproducto);
			ShowWindow(hEditprod, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_PRODUCTOS_ELIMINARPRODUCTO:
			hEliprod = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_ELIMINARPROD), 0, eliproducto);
			ShowWindow(hEliprod, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_PRODUCTOS_MISPRODUCTOS:
			hMisprod = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_MISPROD), 0, misproducto);
			ShowWindow(hMisprod, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_ENVIOS_REALIZARENVIO:
			hRealizarenvi = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_REALIZARENVI), 0, realizarenvi);
			ShowWindow(hRealizarenvi, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_ENVIOS_CANCELARENVIO:
			hCanenvio = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_CANCENVI), 0, canenvio);
			ShowWindow(hCanenvio, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_ENVIOS_EDITARENVIO:
			hEditenvio = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_EDITENVI), 0, editenvio);
			ShowWindow(hEditenvio, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_SALIR_CERRARSESION:
			hInsesion = CreateDialog(instGlobal, MAKEINTRESOURCE(IDD_INSESION), 0, insesion);
			ShowWindow(hInsesion, SW_SHOW);
			DestroyWindow(hWnd);
			break;
		case ID_SALIR_GUARDARYSALIR:
			int opc = MessageBox(hWnd, "¿Seguro que desea salir y guardar todo lo modificado?", "AVISO", MB_YESNO | MB_ICONQUESTION);
			switch (opc) {
			case IDYES:
				escribirenvios();
				escribirproducto();
				escribirusuarios();
				DestroyWindow(hWnd);
				PostQuitMessage(0);
			} break;
		}
	} break;
	}
	return 0;
}

LRESULT CALLBACK Numeros(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam){
	if ((uMsg == WM_CHAR) && (wParam >= '0' && wParam <= '9')){
		MessageBox(hWnd, "No se aceptan numeros.", "AVISO", MB_OK | MB_ICONEXCLAMATION);
		return 0;
	}
	return CallWindowProc(lpEditWndProc, hWnd, uMsg, wParam, lParam);
}


void registrousuario(usuarios* nuevo) {
	if (inicio == nullptr) { 
		inicio = new usuarios;
		aux = inicio;
		aux->sig = nullptr;
		aux->ant = nullptr;
		strcpy_s(aux->usuario, nuevo->usuario);
		strcpy_s(aux->contrasena, nuevo->contrasena);
		strcpy_s(aux->nombre, " ");
		strcpy_s(aux->empresa, " ");
		fin = aux;
		user = aux;
	} else {
		aux = inicio;

		while (aux->sig != nullptr) {
			aux = aux->sig;
		}
		aux->sig = new usuarios;
		aux->sig->sig = nullptr;
		aux->sig->ant = aux;
		aux = aux->sig;
		strcpy_s(aux->usuario, nuevo->usuario);
		strcpy_s(aux->contrasena, nuevo->contrasena);
		strcpy_s(aux->nombre, " ");
		strcpy_s(aux->empresa, " ");
		fin = aux;
		user = aux;
	}
}

void leerusuario() {
	ifstream archivoUs;
	archivoUs.open("C:Usuarios.bin", ios::in | ios::binary);

	aux = inicio;
	if (archivoUs.is_open()) {
		usuarios* usLeido = new usuarios;

		while (!archivoUs.read((char*)usLeido, sizeof(usuarios)).eof()) {

			while (aux != nullptr && aux->sig != nullptr) {
				aux = aux->sig;
			}
			if (aux == nullptr) {
				inicio = usLeido;
				inicio->sig = nullptr;
				inicio->ant = nullptr;
				aux = inicio;
			} else {
				aux->sig = usLeido;
				aux->sig->ant = aux;
				aux = aux->sig;
				aux->sig = nullptr;
			}
			usLeido = new usuarios;
		}
		archivoUs.close();
	} else {
		//MessageBox(hwnd, "El archivo no se pudo abrir, intente de nuevo", " ", MB_OK | MB_ICONEXCLAMATION);
	}
}

void escribirusuarios() {
	aux = inicio;

	ofstream archivoUs;
	archivoUs.open("Usuarios.bin", ios::out | ios::binary | ios::trunc);

	if (archivoUs.is_open()) {
		while (aux != nullptr) {
			archivoUs.write((char*)aux, sizeof(usuarios));
			aux = aux->sig;
		}
		archivoUs.close();
	} else{
		//cout << "No se pudo abrir el archivo.";
	}
}


void registrarCliente(int id, const char* nombres, const char* apellidoPaterno, const char* apellidoMaterno, const char* correo, const char* telefono, const char* estatus, const char* fechaRegistro, const char* fechaCambio) {
	cliente* nuevoCliente = new cliente;
	nuevoCliente->id = id;
	strcpy_s(nuevoCliente->nombres, sizeof(nuevoCliente->nombres), nombres);
	strcpy_s(nuevoCliente->apellidoPaterno, sizeof(nuevoCliente->apellidoPaterno), apellidoPaterno);
	strcpy_s(nuevoCliente->apellidoMaterno, sizeof(nuevoCliente->apellidoMaterno), apellidoMaterno);
	strcpy_s(nuevoCliente->correo, sizeof(nuevoCliente->correo), correo);
	strcpy_s(nuevoCliente->telefono, sizeof(nuevoCliente->telefono), telefono);
	strcpy_s(nuevoCliente->estatus, sizeof(nuevoCliente->estatus), estatus);
	strcpy_s(nuevoCliente->fechaRegistro, sizeof(nuevoCliente->fechaRegistro), fechaRegistro);
	strcpy_s(nuevoCliente->fechaCambio, sizeof(nuevoCliente->fechaCambio), fechaCambio);
	nuevoCliente->sig = nullptr;
	nuevoCliente->ant = finCliente;

	if (finCliente != nullptr) {
		finCliente->sig = nuevoCliente;
	}
	finCliente = nuevoCliente;
	if (inicioCliente == nullptr) {
		inicioCliente = nuevoCliente;
	}
}

void guardarClientes() {
	ofstream archivo("clientes.txt", ios::out);
	if (archivo.is_open()) {
		auxCliente = inicioCliente;
		while (auxCliente != nullptr) {
			archivo << auxCliente->id << ' ' << auxCliente->nombres << ' ' << auxCliente->apellidoPaterno << ' '
				<< auxCliente->apellidoMaterno << ' ' << auxCliente->correo << ' '
				<< auxCliente->telefono << ' ' << auxCliente->estatus << ' '
				<< auxCliente->fechaRegistro << ' ' << auxCliente->fechaCambio << '\n';
			auxCliente = auxCliente->sig;
		}
		archivo.close();
	}
	else {
		cout << "Error al abrir el archivo." << endl;
	}
}

void cargarClientes() {
	ifstream archivo("clientes.txt", ios::in);
	if (archivo.is_open()) {
		while (!archivo.eof()) {
			cliente* nuevoCliente = new cliente;
			archivo >> nuevoCliente->id >> nuevoCliente->nombres >> nuevoCliente->apellidoPaterno
				>> nuevoCliente->apellidoMaterno >> nuevoCliente->correo >> nuevoCliente->telefono
				>> nuevoCliente->estatus >> nuevoCliente->fechaRegistro >> nuevoCliente->fechaCambio;
			nuevoCliente->sig = nullptr;
			nuevoCliente->ant = finCliente;
			if (finCliente != nullptr) {
				finCliente->sig = nuevoCliente;
			}
			finCliente = nuevoCliente;
			if (inicioCliente == nullptr) {
				inicioCliente = nuevoCliente;
			}
		}
		archivo.close();
	}
	else {
		cout << "Error al abrir el archivo." << endl;
	}
}

void modificarCliente(int id, const char* nombres, const char* apellidoPaterno, const char* apellidoMaterno, const char* correo, const char* telefono, const char* estatus, const char* fechaRegistro, const char* fechaCambio) {
	auxCliente = inicioCliente;
	while (auxCliente != nullptr) {
		if (auxCliente->id == id) {
			strcpy_s(auxCliente->nombres, sizeof(auxCliente->nombres), nombres);
			strcpy_s(auxCliente->apellidoPaterno, sizeof(auxCliente->apellidoPaterno), apellidoPaterno);
			strcpy_s(auxCliente->apellidoMaterno, sizeof(auxCliente->apellidoMaterno), apellidoMaterno);
			strcpy_s(auxCliente->correo, sizeof(auxCliente->correo), correo);
			strcpy_s(auxCliente->telefono, sizeof(auxCliente->telefono), telefono);
			strcpy_s(auxCliente->estatus, sizeof(auxCliente->estatus), estatus);
			strcpy_s(auxCliente->fechaRegistro, sizeof(auxCliente->fechaRegistro), fechaRegistro);
			strcpy_s(auxCliente->fechaCambio, sizeof(auxCliente->fechaCambio), fechaCambio);
			return;
		}
		auxCliente = auxCliente->sig;
	}
	cout << "Cliente no encontrado." << endl;
}

void eliminarCliente(int id) {
	auxCliente = inicioCliente;
	while (auxCliente != nullptr) {
		if (auxCliente->id == id) {
			if (auxCliente->ant != nullptr) {
				auxCliente->ant->sig = auxCliente->sig;
			}
			else {
				inicioCliente = auxCliente->sig; // Eliminar el primer nodo
			}
			if (auxCliente->sig != nullptr) {
				auxCliente->sig->ant = auxCliente->ant;
			}
			delete auxCliente;
			return;
		}
		auxCliente = auxCliente->sig;
	}
	cout << "Cliente no encontrado." << endl;
}


void registrarTienda(int id, const char* nombreT, const char* IDT, const char* correo, const char* estatusT, const char* fechaCambioT) {
	Tienda* nuevaTienda = new Tienda;
	nuevaTienda->id = id;
	strcpy_s(nuevaTienda->nombreT, sizeof(nuevaTienda->nombreT), nombreT);
	strcpy_s(nuevaTienda->IDT, sizeof(nuevaTienda->IDT), IDT);
	strcpy_s(nuevaTienda->correo, sizeof(nuevaTienda->correo), correo);
	strcpy_s(nuevaTienda->estatusT, sizeof(nuevaTienda->estatusT), estatusT);
	strcpy_s(nuevaTienda->fechaCambioT, sizeof(nuevaTienda->fechaCambioT), fechaCambioT);
	nuevaTienda->sig = nullptr;
	nuevaTienda->ant = fint;

	if (fint != nullptr) {
		fint->sig = nuevaTienda;
	}
	fint = nuevaTienda;
	if (iniciot == nullptr) {
		iniciot = nuevaTienda;
	}
}

void guardarTiendas() {
	ofstream archivo("tiendas.txt", ios::out);
	if (archivo.is_open()) {
		auxt = iniciot;
		while (auxt != nullptr) {
			archivo << auxt->id << ' ' << auxt->nombreT << ' ' << auxt->IDT << ' '
				<< auxt->correo << ' ' << auxt->estatusT << ' ' << auxt->fechaCambioT << '\n';
			auxt = auxt->sig;
		}
		archivo.close();
	}
	else {
		cout << "Error al abrir el archivo." << endl;
	}
}

void cargarTiendas() {
	ifstream archivo("tiendas.txt", ios::in);
	if (archivo.is_open()) {
		while (!archivo.eof()) {
			Tienda* nuevaTienda = new Tienda;
			archivo >> nuevaTienda->id >> nuevaTienda->nombreT >> nuevaTienda->IDT >> nuevaTienda->correo
				>> nuevaTienda->estatusT >> nuevaTienda->fechaCambioT;
			nuevaTienda->sig = nullptr;
			nuevaTienda->ant = fint;
			if (fint != nullptr) {
				fint->sig = nuevaTienda;
			}
			fint = nuevaTienda;
			if (iniciot == nullptr) {
				iniciot = nuevaTienda;
			}
		}
		archivo.close();
	}
	else {
		cout << "Error al abrir el archivo." << endl;
	}
}

void modificarTienda(int id, const char* nombreT, const char* IDT, const char* correo, const char* estatusT, const char* fechaCambioT) {
	auxt = iniciot;
	while (auxt != nullptr) {
		if (auxt->id == id) {
			strcpy_s(auxt->nombreT, sizeof(auxt->nombreT), nombreT);
			strcpy_s(auxt->IDT, sizeof(auxt->IDT), IDT);
			strcpy_s(auxt->correo, sizeof(auxt->correo), correo);
			strcpy_s(auxt->estatusT, sizeof(auxt->estatusT), estatusT);
			strcpy_s(auxt->fechaCambioT, sizeof(auxt->fechaCambioT), fechaCambioT);
			return;
		}
		auxt = auxt->sig;
	}
	cout << "Tienda no encontrada." << endl;
}

void eliminarTienda(int id) {
	auxt = iniciot;
	while (auxt != nullptr) {
		if (auxt->id == id) {
			if (auxt->ant != nullptr) {
				auxt->ant->sig = auxt->sig;
			}
			else {
				iniciot = auxt->sig; // Eliminar el primer nodo
			}
			if (auxt->sig != nullptr) {
				auxt->sig->ant = auxt->ant;
			}
			delete auxt;
			return;
		}
		auxt = auxt->sig;
	}
	cout << "Tienda no encontrada." << endl;
}


void registropr(productos* nuevo) {
	if (iniciop == nullptr) {
		iniciop = new productos;
		auxp = iniciop;
		auxp->sig = nullptr;
		auxp->ant = nullptr;
		strcpy_s(auxp->propietario, user->usuario);
		strcpy_s(auxp->nombreprod, nuevo->nombreprod);
		strcpy_s(auxp->marca, nuevo->marca);
		strcpy_s(auxp->descripcion, nuevo->descripcion);
		auxp->cantidad = nuevo->cantidad;
		auxp->codigo = nuevo->codigo;
		auxp->monto = nuevo->monto;
		strcpy_s(auxp->foto1, nuevo->foto1);
		strcpy_s(auxp->foto2, nuevo->foto2);
		finp = auxp;
		prod = auxp;
	} else {
		auxp = iniciop;

		while (auxp->sig != nullptr) {
			auxp = auxp->sig;
		}
		auxp->sig = new productos;
		auxp->sig->sig = nullptr;
		auxp->sig->ant = auxp;
		auxp = auxp->sig;
		strcpy_s(auxp->propietario, user->usuario);
		strcpy_s(auxp->nombreprod, nuevo->nombreprod);
		strcpy_s(auxp->marca, nuevo->marca);
		strcpy_s(auxp->descripcion, nuevo->descripcion);
		auxp->cantidad = nuevo->cantidad;
		auxp->codigo = nuevo->codigo;
		auxp->monto = nuevo->monto;
		strcpy_s(auxp->foto1, nuevo->foto1);
		strcpy_s(auxp->foto2, nuevo->foto2);
		finp = auxp;
		prod = auxp;
	}
}

void leerproductos() {
	ifstream archivoPr;
	archivoPr.open("Productos.bin", ios::in | ios::binary);

	auxp = iniciop;
	if (archivoPr.is_open()) {
		productos* prLeido = new productos;

		while (!archivoPr.read((char*)prLeido, sizeof(productos)).eof()) {

			while (auxp != nullptr && auxp->sig != nullptr) {
				auxp = auxp->sig;
			}
			if (auxp == nullptr) {
				iniciop = prLeido;
				iniciop->sig = nullptr;
				iniciop->ant = nullptr;
				auxp = iniciop;
			} else {
				auxp->sig = prLeido;
				auxp->sig->ant = auxp;
				auxp = auxp->sig;
				auxp->sig = nullptr;
			}
			prLeido = new productos;
		}
		archivoPr.close();
	} else {
		MessageBox(hInsesion, "El archivo no se pudo abrir, intente de nuevo", " ", MB_OK | MB_ICONEXCLAMATION);
	}
}

void escribirproducto() {
	auxp = iniciop;

	ofstream archivoPr;
	archivoPr.open("Productos.bin", ios::out | ios::binary | ios::trunc);

	if (archivoPr.is_open()) {
		while (auxp != nullptr){
			archivoPr.write((char*)auxp, sizeof(productos));
			auxp = auxp->sig;
		}
		archivoPr.close();
	} else{
		//cout << "No se pudo abrir el archivo.";
	}
}

void eliminarprod(productos* auxp) {
	if (auxp == iniciop) {	
		if (auxp->sig == nullptr) { 
			delete auxp;		

			iniciop = nullptr;
			auxp = iniciop;
		} else { 

			iniciop = auxp->sig; 

			delete auxp;		

			auxp = iniciop;	
			auxp->ant = nullptr;
		}
		MessageBox(hEliprod, "Producto eliminado", "AVISO", MB_OK | MB_ICONINFORMATION);
	} else {
		if (auxp->sig == nullptr) { 
			auxp->ant->sig = nullptr;	
		} else {
			auxp->sig->ant = auxp->ant;
			auxp->ant->sig = auxp->sig;
		}
		delete auxp;
		auxp = iniciop;	

		MessageBox(hEliprod, "Producto eliminado", "AVISO", MB_OK | MB_ICONINFORMATION);
	}
}



void registroenvio(envios* nuevo) {
	if (inicioe == nullptr) { //lista vacia, se crea
		inicioe = new envios;
		auxe = inicioe;
		auxe->sig = nullptr;
		auxe->ant = nullptr;
		strcpy_s(auxe->repartidor, user->usuario);
		strcpy_s(auxe->calle, nuevo->calle);
		strcpy_s(auxe->ciudad, nuevo->ciudad);
		strcpy_s(auxe->colonia, nuevo->colonia);
		strcpy_s(auxe->estado, nuevo->estado);
		strcpy_s(auxe->mensaje, nuevo->mensaje);

		strcpy_s(auxe->producto, auxp->nombreprod);
		auxe->cantidad = nuevo->cantidad;
		auxe->precio = nuevo->precio;
		strcpy_s(auxe->fechaenvio.dia, nuevo->fechaenvio.dia);
		strcpy_s(auxe->fechaenvio.mes, nuevo->fechaenvio.mes);
		strcpy_s(auxe->fechaenvio.anio, nuevo->fechaenvio.anio);
		fine = auxe;
	
	}else {
		auxe = inicioe;

		while (auxe->sig != nullptr) {
			auxe = auxe->sig;
		}
		auxe->sig = new envios;
		auxe->sig->sig = nullptr;
		auxe->sig->ant = auxe;
		auxe = auxe->sig;
		strcpy_s(auxe->repartidor, user->usuario);
		strcpy_s(auxe->calle, nuevo->calle);
		strcpy_s(auxe->colonia, nuevo->colonia);
		strcpy_s(auxe->ciudad, nuevo->ciudad);
		strcpy_s(auxe->estado, nuevo->estado);
		strcpy_s(auxe->mensaje, nuevo->mensaje);
		strcpy_s(auxe->producto, auxp->nombreprod);
		auxe->cantidad = nuevo->cantidad;
		auxe->precio = nuevo->precio;
		strcpy_s(auxe->fechaenvio.dia, nuevo->fechaenvio.dia);
		strcpy_s(auxe->fechaenvio.mes, nuevo->fechaenvio.mes);
		strcpy_s(auxe->fechaenvio.anio, nuevo->fechaenvio.anio);
		fine = auxe;	
	}
}

void escribirenvios() {
	auxe = inicioe;

	ofstream archivoEn;
	archivoEn.open("Envios.bin", ios::out | ios::binary | ios::trunc);

	if (archivoEn.is_open()) {
		while (auxe != nullptr){
			archivoEn.write((char*)auxe, sizeof(envios));
			auxe = auxe->sig;
		}
		archivoEn.close();
	}else
	{
		//cout << "No se pudo abrir el archivo.";
	}
}

void leerenvios() {
	ifstream archivoEn;
	archivoEn.open("Envios.bin", ios::in | ios::binary);

	auxe = inicioe;
	if (archivoEn.is_open()) {
		envios* enLeido = new envios;

		while (!archivoEn.read((char*)enLeido, sizeof(envios)).eof()) {

			while (auxe != nullptr && auxe->sig != nullptr) {
				auxe = auxe->sig;
			}

			if (auxe == nullptr) {
				inicioe = enLeido;
				inicioe->sig = nullptr;
				inicioe->ant = nullptr;
				auxe = inicioe;
			}else {
				auxe->sig = enLeido;
				auxe->sig->ant = auxe;
				auxe = auxe->sig;
				auxe->sig = nullptr;
			}
			enLeido = new envios;
		}
		archivoEn.close();
	} else {
		/*MessageBox(hInsesion, "El archivo no se pudo abrir, intente de nuevo", " ", MB_OK | MB_ICONEXCLAMATION);*/
	}
}


void swap(envios* a, envios* b){
	envios t = *a;
	*a = *b;
	*b = t;

	b->sig = a->sig; b->ant = a->ant;
	a->sig = t.sig; a->ant = t.ant;
}

envios* partition(envios* l, envios* h){	
	SYSTEMTIME DateSh;
	ZeroMemory(&DateSh, sizeof(DateSh));

	DateSh.wDay = atoi(h->fechaenvio.dia);
	DateSh.wMonth = atoi(h->fechaenvio.mes);
	DateSh.wYear = atoi(h->fechaenvio.anio);

	envios* i = l->ant;

	for (envios* j = l; j != h; j = j->sig){
		SYSTEMTIME DateSj;
		ZeroMemory(&DateSj, sizeof(DateSj));
		FILETIME DateFj;
		ZeroMemory(&DateFj, sizeof(DateFj));

		DateSj.wDay = atoi(j->fechaenvio.dia);
		DateSj.wMonth = atoi(j->fechaenvio.mes);
		DateSj.wYear = atoi(j->fechaenvio.anio);

		if (DateSj.wYear <= DateSh.wYear && DateSj.wMonth <= DateSh.wMonth && DateSj.wDay < DateSh.wDay){
			if (i == NULL) {
				i = l;
			} else {
				i = i->sig;
			}
			swap((i), (j));
		}
	}
	if (i == NULL) {
		i = l;
	} else {
		i = i->sig;
	}
	swap((i), (h));
	return i;
}

void quickSort(envios* iniL, envios* finL){
	if (finL != NULL && iniL != finL && iniL != finL->sig){
		envios* p = partition(iniL, finL);
		quickSort(iniL, p->ant);
		quickSort(p->sig, finL);
	}
}

void eliminarend(envios* auxe) {
	if (auxe == inicioe) {	
		if (auxe->sig == nullptr) { 

			delete auxe;		

			inicioe = nullptr;
			auxe = inicioe;
		} else { 

			inicioe = auxe->sig; 

			delete auxe;		

			auxe = inicioe;	
			auxe->ant = nullptr;
		}

		MessageBox(hCanenvio, "Producto eliminado", "AVISO", MB_OK | MB_ICONINFORMATION);
	} else {
		if (auxe->sig == nullptr) {
			auxe->ant->sig = nullptr;	
		} else {
			auxe->sig->ant = auxe->ant;
			auxe->ant->sig = auxe->sig;
		}

		delete auxe;
		auxe = inicioe;	

		MessageBox(hCanenvio, "Producto eliminado", "AVISO", MB_OK | MB_ICONINFORMATION);
	}
}
